#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>

#include <SFML-utils/map-editor/Gui.hpp>


namespace sfutils
{
    namespace editor
    {
        class Editor
        {
            public:
                Editor(const Editor&) = delete;
                Editor& operator=(const Editor&) = delete;

                explicit Editor();
                ~Editor();

                void run();

            private:
                sf::RenderWindow _window;
                sf::Clock _clock;
                Gui _gui;

                sfutils::map::Map* _map;
                sfutils::map::MapManager _mapManager;
                sfutils::map::MapViewer _mapViewer;

                sf::ConvexShape _highlight;

                void _processEvents();
                void _update();
                void _render();

        };
    }
}
#endif
