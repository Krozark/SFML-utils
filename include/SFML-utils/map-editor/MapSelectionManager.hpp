#ifndef SFUTILS_EDITOR_MAPSELECTIONMANAGER_HPP
#define SFUTILS_EDITOR_MAPSELECTIONMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>

namespace sfutils
{
    namespace editor
    {
        class Editor;
        class MapSelectionManager
        {
            public:
                MapSelectionManager(const MapSelectionManager&) = delete;
                MapSelectionManager& operator=(const MapSelectionManager&) = delete;

                MapSelectionManager(Editor& owner);

                void reset();

                bool processEvent(const sf::Event& event, sfutils::map::MapViewer& viewer);

                void render(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default);

                void setMap(sfutils::map::Map* map);


            protected:

            private:
                Editor& _owner;

                sfutils::map::Map* _map;
                sf::ConvexShape* _cursorHighlight;
                sfutils::map::Layer<sf::ConvexShape>* _highlightLayer;

                sf::Vector2i _clickPressedCoord;
                sf::Vector2i _clickReleasedCoord;
                bool _isPressed;

                sf::VertexArray _clickIndicator;

                void _updateSelectionArea(sfutils::map::MapViewer& viewer);
                void _valideSelectedArea();
                void _resetSelection();
                void _squareSelection(sfutils::map::MapViewer& viewer);

                std::list<sf::Vector2i> _selectedCoords;
                std::list<sf::ConvexShape*> _selectionHighlight;

        };
    }
}
#endif
