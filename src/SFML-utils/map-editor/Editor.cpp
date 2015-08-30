#include <SFML-utils/map-editor/Editor.hpp>

namespace sfutils
{
    namespace editor
    {
        Editor::Editor(const sf::VideoMode& mode):
            _window(mode,"SFML-utils map editor")
        {
            _window.setFramerateLimit(65);
        }

        void Editor::run()
        {
            while(_window.isOpen())
            {
                _processEvents();
                _update();
                _render();

            }
        }

        void Editor::_processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                _desktop.HandleEvent(event);

                if(event.type == sf::Event::Closed ) 
                    _window.close();
                
            }
        }

        void Editor::_update()
        {
            sf::Time deltaTime = _clock.restart();
            _desktop.Update(deltaTime.asSeconds());
        }

        void Editor::_render()
        {
            _window.setActive(true);
            _window.clear();
            
            _sfgui.Display(_window);

            _window.display();
        }

    }
}
