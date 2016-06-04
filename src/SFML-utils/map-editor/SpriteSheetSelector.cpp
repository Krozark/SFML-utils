#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <utils/json/Driver.hpp>


namespace sfutils
{
    namespace editor
    {
        
        SpriteSheetSelector::SpriteSheetSelector() : 
            _window(sf::VideoMode(800,600),"SpriteSheet Selector")
        {
            _context = &cegui::GuiManager::createGUIContext();
        }

        SpriteSheetSelector::~SpriteSheetSelector()
        {
            cegui::GuiManager::destroyGUIContext(*_context);
        }

        bool SpriteSheetSelector::setFile(const std::string& file)
        {
            auto root = utils::json::Driver::parse_file(file);
            std::cout<<(*root)<<std::endl;
            
            return false;
        }

        void SpriteSheetSelector::processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                cegui::GuiManager::processEvent(event,*_context);
            }
        }

        void SpriteSheetSelector::update(const sf::Time& deltaTime)
        {
            cegui::GuiManager::update(deltaTime,*_context);
        }

        void SpriteSheetSelector::render()
        {
            _window.setActive(true);
            _window.pushGLStates();
            cegui::GuiManager::render(*_context);
            _window.popGLStates();
        }
    }
}
