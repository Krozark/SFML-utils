#include <SFML-utils/map-editor/Editor.hpp>

#include <cassert>
#include <iostream>

namespace sfutils
{
    namespace editor
    {
        Editor::Editor():
            _window(sf::VideoMode(1600,900),"SFML-utils map editor"),
            _gui(_window.getSize()),
            _map(nullptr),
            _mapManager(std::shared_ptr<sfutils::map::VMapLoader>(new sfutils::map::JsonMapLoader("./media"))),
            _mapViewer(_window)
        {
            _window.setFramerateLimit(65);
            _window.setMouseCursorVisible(false);

            _map = _mapManager.getMap();
            _mapViewer.setMap(_map);

            _highlight = _map->getGeometry().getShape();
            _highlight.setFillColor(sf::Color(0,255,0,127));

            _mapManager.loadArea(1,0);
            _mapManager.loadArea(0,0);
            _mapManager.loadArea(-1,-1);
            _mapManager.loadArea(-1,0);
            _mapManager.loadArea(0,-1);

        }

        Editor::~Editor()
        {
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

        ////////////////////// PRIVATE ////////////////////
        void Editor::_processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed ) 
                {
                    _window.close();
                }
                else if(not _gui.processEvent(event) and not _mapViewer.processEvent(event))
                {
                }

            }
            _mapViewer.processEvents();

            {
                sf::Vector2i coord = _mapViewer.mapScreenToCoords(sf::Mouse::getPosition(_window));
                sf::Vector2i pixels = _mapViewer.mapCoordsToScreen(coord);
                _highlight.setPosition(pixels.x,pixels.y);
            }
        }

        void Editor::_update()
        {
            sf::Time deltaTime = _clock.restart();
            _gui.update(deltaTime);

            _mapViewer.update(deltaTime);
        }

        void Editor::_render()
        {
            _window.setActive(true);

            _window.clear();

            _mapViewer.draw();
            _window.draw(_highlight);

            _gui.render(_window);
            
            _window.display();
        }


    }
}
