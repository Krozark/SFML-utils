#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <utils/json/Driver.hpp>
#include <utils/string.hpp>


namespace sfutils
{
    namespace editor
    {
        
        SpriteSheetSelector::SpriteSheetSelector(Editor& owner) : 
            _owner(owner),
            _window(sf::VideoMode(800,600),"SpriteSheet Selector")
        {
            //_context = &cegui::GuiManager::createGUIContext();
            setVisible(false);

            _selectionShape.setFillColor(sf::Color::White);
            _highlightShape.setFillColor(sf::Color(0,255,0,127));
        }

        SpriteSheetSelector::~SpriteSheetSelector()
        {
            //cegui::GuiManager::destroyGUIContext(*_context);
        }

        bool SpriteSheetSelector::setFile(const std::string& file, sfutils::ResourceManager<sf::Texture,std::string>& textureManager)
        {
            auto value = utils::json::Driver::parse_file(file);
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<file<<std::endl;
                return false;
            }

            std::unordered_map<std::string,sf::IntRect> tmpRect;
            sf::IntRect size;
            std::string imageFile;
            bool res = true;

            sf::Texture* spriteSheetTexture = nullptr;

            try
            {
                utils::json::Object& root = value->as_object();
                //frames
                utils::json::Array& json_frames = root["frames"].as_array();
                for(utils::json::Value& value : json_frames)
                {
                    utils::json::Object& obj = value.as_object();
                    std::string name = obj["filename"].as_string();

                    utils::json::Object& frame = obj["frame"].as_object();
                    sf::IntRect rect;
                    rect.left = frame["x"].as_int();
                    rect.top = frame["y"].as_int();
                    rect.width = frame["w"].as_int();
                    rect.height = frame["h"].as_int();

                    tmpRect.emplace(name,rect);
                }

                //meta
                utils::json::Object& meta = root["meta"].as_object();
                utils::json::Object& jsonSize = meta["size"].as_object();

                imageFile = meta["image"].as_string();
                size.width = jsonSize["w"].as_int();
                size.height = jsonSize["h"].as_int();

                auto sp = utils::string::split(file,"/");
                sp.pop_back();
                sp.push_back(imageFile);
                imageFile = utils::string::join("/",sp);

                //_imageTexture file
                spriteSheetTexture = &textureManager.getOrLoad(imageFile,imageFile);

                //transparent background
                sf::Texture& backgroundTexture = textureManager.getOrLoad("media/gui/bg-transparent.png","media/gui/bg-transparent.png");
                backgroundTexture.setRepeated(true);
                _backgroundSprite.setTexture(backgroundTexture);
                _backgroundSprite.setTextureRect(size);

            }
            catch(std::exception& e)
            {
                std::cerr<<"Exception when parsing file '"<<file<<"' : "<<e.what()<<std::endl;
                res = false;
            }

            std::swap(_imageFile,imageFile);
            std::swap(_rect,tmpRect);

            //set background futur image
            _imageTexture.create(size.width,size.height);
            _imageTexture.clear(sf::Color::Transparent);

            //sprite sheet image
            _imageSprite.setTexture(*spriteSheetTexture,true);
            _imageTexture.draw(_imageSprite);
            //borders
            sf::RectangleShape tmpShape;
            tmpShape.setFillColor(sf::Color::Transparent);
            tmpShape.setOutlineColor(sf::Color::Black);
            tmpShape.setOutlineThickness(1);
            for(auto& pair : _rect)
            {
                auto& rect = pair.second;
                tmpShape.setSize(sf::Vector2f(rect.width,rect.height));
                tmpShape.setPosition(sf::Vector2f(rect.left,rect.top));
                _imageTexture.draw(tmpShape);
            }
            _imageTexture.display();

            _imageSprite.setTexture(_imageTexture.getTexture(),true);

            _window.create(sf::VideoMode(size.width,size.height),"SpriteSheet Selector ("+_imageFile+")");

            return res;
        }

        void SpriteSheetSelector::setVisible(bool visible)
        {
            _window.setVisible(visible);
        }

        void SpriteSheetSelector::processEvents()
        {
            sf::Vector2i coord = sf::Mouse::getPosition(_window);
            for(auto& pair : _rect)
            {
                auto& rect = pair.second;
                if(rect.contains(coord))
                {
                    _highlightShape.setPosition(sf::Vector2f(rect.left,rect.top));
                    _highlightShape.setSize(sf::Vector2f(rect.width,rect.height));
                    break;
                }
            }


            sf::Event event;
            while(_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed )
                { 
                    setVisible(false);
                }
                else if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    _selectionShape.setPosition(_highlightShape.getPosition());
                    _selectionShape.setSize(_highlightShape.getSize());
                }
                /*else
                {
                    cegui::GuiManager::processEvent(event,*_context);
                }*/
            }
        }

        void SpriteSheetSelector::update(const sf::Time& deltaTime)
        {
            //cegui::GuiManager::update(deltaTime,*_context);
        }

        void SpriteSheetSelector::render()
        {
            _window.setActive(true);
            _window.clear(sf::Color::White);

            _window.draw(_backgroundSprite);
            _window.draw(_selectionShape);
            _window.draw(_highlightShape);
            _window.draw(_imageSprite);

            /*_window.pushGLStates();
            cegui::GuiManager::render(*_context);
            _window.popGLStates();*/
            _window.display();
        }

    }
}
