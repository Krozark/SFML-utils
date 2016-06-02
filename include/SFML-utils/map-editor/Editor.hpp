#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>
#include <SFML-utils/map/Models.hpp>

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

                void setMap(sfutils::map::MapModel::pointer& map);
                sfutils::map::MapModel::pointer getMap() const;
                void reloadMap();

                void setZoom(float value);
                void setMiniMapZoom(float value);

                bool requestNewLayer();
                bool requestDelLayer(int index);
                bool requestMoveLayer(int from,int to);

            private:
                sf::RenderWindow _window;
                sf::Clock _clock;

                Gui _gui;

                sfutils::map::Map* _map;
                sfutils::map::MapModel::pointer _dbMap;

                std::unique_ptr<sfutils::map::MapManager> _mapManager;
                sfutils::map::MapViewer _mapViewer;

                sf::ConvexShape* _highlight;
                sf::IntRect _lastVisibleRect;

                void _processEvents();
                void _update();
                void _render();

                void _onClick(const sf::Vector2i& Coord);


                void _loadVisiblesAreas(const sf::IntRect& rect);
                sf::IntRect _getVisibleAreaRect()const;

                sf::IntRect _selectionRect;
                std::vector<sf::ConvexShape> _selectionHighlight;

        };
    }
}
#endif
