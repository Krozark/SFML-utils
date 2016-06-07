#include <SFML-utils/map-editor/MapSelectionManager.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

namespace sfutils
{
    namespace editor
    {
        
        MapSelectionManager::MapSelectionManager(Editor& owner) :
            _owner(owner)
        {
            reset();
        }

        void MapSelectionManager::reset()
        {
            _map = nullptr;
            _cursorHighlight = nullptr;
            _highlightLayer = nullptr;
            _clickPressedCoord = sf::Vector2i(0,0);
            _clickReleasedCoord = sf::Vector2i(0,0);
            _lastCoord = sf::Vector2i(0,0);
            _isPressed = false;
        }

        bool MapSelectionManager::processEvent(const sf::Event& event, sfutils::map::MapViewer& viewer)
        {
            if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickPressedCoord = _clickReleasedCoord = _lastCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                _isPressed = true;
            }
            else if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickReleasedCoord = _lastCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                _isPressed = true;

                //TODO for(...) owner.resquestFillTile();

                sf::Vector2i coord = _clickReleasedCoord;
                _owner.fillTile(coord);
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i coord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                sf::Vector2f pixels = viewer.mapCoordsToPixel(coord);
                _cursorHighlight->setPosition(pixels);

                if(_isPressed && (_lastCoord != coord))
                {
                    _lastCoord = coord;
                    //TODO calculate the selection area
                }
            }

            return false;
        }

        void MapSelectionManager::setMap(sfutils::map::Map* map)
        {
            assert(map);

            _map = map;

            //special layers
            _highlightLayer = new sfutils::map::Layer<sf::ConvexShape>("ConvexShape",100);

            _cursorHighlight = _highlightLayer->add(_map->getGeometry().getShape());
            _cursorHighlight->setFillColor(sf::Color(0,255,0,127));
            _map->addLayer(_highlightLayer);
        }
    }
}
