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

            _selectionShape.setFillColor(sf::Color(127,127,127));
            _highlightShape.setFillColor(sf::Color(0,127,0));
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

                sf::Texture& tex = textureManager.getOrLoad(imageFile,imageFile);
                _background.setTexture(tex,true);
            }
            catch(std::exception& e)
            {
                std::cerr<<"Exception when parsing file '"<<file<<"' : "<<e.what()<<std::endl;
                res = false;
            }

            std::swap(_imageFile,imageFile);
            std::swap(_rect,tmpRect);

            _borders.clear();
            for(auto& pair : _rect)
            {
                //TODO, change  	VertexArray
                auto& rect = pair.second;
                sf::RectangleShape tmpShape(sf::Vector2f(rect.width,rect.height));
                tmpShape.setPosition(sf::Vector2f(rect.left,rect.top));
                tmpShape.setOutlineColor(sf::Color::Black);
                tmpShape.setOutlineThickness(1);
                _borders.emplace_back(std::move(tmpShape));
            }

            std::vector<sf::RectangleShape> _borders;

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

            for(auto& border : _borders)
            {
                _window.draw(border);
            }

            _window.draw(_selectionShape);
            _window.draw(_highlightShape);
            _window.draw(_background);

            /*_window.pushGLStates();
            cegui::GuiManager::render(*_context);
            _window.popGLStates();*/
            _window.display();
        }

    }
}
