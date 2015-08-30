#include <SpriteSheetSelector.hpp>

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
                _desktop.HandleEvent(event);

                /*if(event.type == sf::Event::Closed ) 
                    _window.close();*/
                
            }
        }

        void SpriteSheetSelector::update(const sf::Time& deltaTime)
        {
            _desktop.Update(detaTime.asSeconds());
        }

        void SpriteSheetSelector::render()
        {
            _window.setActive(true);
            _window.clear();
            
            sfgui.Display(_window);

            _window.display();
        }
    }
}
