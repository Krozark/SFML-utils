#ifndef SFUTILS_EDITOR_MAPSELECTIONMANAGER_HPP
#define SFUTILS_EDITOR_MAPSELECTIONMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>

struct lua_State;

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
                ~MapSelectionManager();

                void reset();

                bool processEvent(const sf::Event& event);

                void render(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default);

                void setMap(sfutils::map::Map* map);

                void setSelectionBrush(const std::string& brush);


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

                lua_State* _luaState;

                void _updateSelectionArea();
                void _valideSelectedArea();
                void _resetSelection();
                void _addSelectedCood(const sf::Vector2i& coord);

                std::list<sf::Vector2i> _selectedCoords;
                std::list<sf::ConvexShape*> _selectionHighlight;

        };
    }
}
#endif
