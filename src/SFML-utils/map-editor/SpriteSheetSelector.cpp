#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>

namespace sfutils
{
    namespace editor
    {
        
        SpriteSheetSelector::SpriteSheetSelector()
        {
        }

        void SpriteSheetSelector::processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                /*if(event.type == sf::Event::Closed ) 
                    _window.close();*/
                
            }
        }

        void SpriteSheetSelector::update(const sf::Time& deltaTime)
        {
        }

        void SpriteSheetSelector::render()
        {
            _window.setActive(true);
            _window.clear();
            
            _window.display();
        }
    }
}
