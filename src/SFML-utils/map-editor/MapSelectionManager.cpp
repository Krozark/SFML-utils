#include <SFML-utils/map-editor/MapSelectionManager.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

#include <algorithm>

namespace sfutils
{
    namespace editor
    {
        
        MapSelectionManager::MapSelectionManager(Editor& owner) :
            _owner(owner),
            _clickIndicator(sf::PrimitiveType::Lines,2)
        {
            reset();

            for(int i = 0; i < 2; ++i)
            {
                _clickIndicator[i].color = sf::Color(255,20,125);
            }

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

            _resetSelection();
        }

        bool MapSelectionManager::processEvent(const sf::Event& event, sfutils::map::MapViewer& viewer)
        {
            if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickPressedCoord = _clickReleasedCoord = _lastCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                _isPressed = true;

                sf::Vector2i coordSreen = viewer.mapCoordsToScreen(_lastCoord);

                _clickIndicator[0].position = _clickIndicator[1].position = sf::Vector2f(coordSreen.x,coordSreen.y);
            }
            else if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickReleasedCoord = _lastCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));

                _valideSelectedArea();


                _isPressed = false;
                sf::Vector2i coordSreen = viewer.mapCoordsToScreen(_lastCoord);
                _clickIndicator[1].position = sf::Vector2f(coordSreen.x,coordSreen.y);
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i coord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                sf::Vector2f pixels = viewer.mapCoordsToPixel(coord);
                _cursorHighlight->setPosition(pixels);

                if(_isPressed && (_lastCoord != coord))
                {
                    _lastCoord = coord;

                    sf::Vector2i coordSreen = viewer.mapCoordsToScreen(_lastCoord);
                    _clickIndicator[1].position = sf::Vector2f(coordSreen.x,coordSreen.y);

                    _updateSelectionArea(viewer);
                }
            }

            return false;
        }
        
        void MapSelectionManager::render(sf::RenderTarget& target,sf::RenderStates states)
        {
            if(_isPressed)
            {
                target.draw(_clickIndicator,states);
            }
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

        ///////////////////////////// PRIVATE /////////////////////////////////
        void MapSelectionManager::_updateSelectionArea(sfutils::map::MapViewer& viewer)
        {
            _resetSelection();

            for(int y = std::min(_clickPressedCoord.y,_lastCoord.y); y <= std::max(_clickPressedCoord.y,_lastCoord.y);++y)
            {
                for(int x = std::min(_clickPressedCoord.x,_lastCoord.x); x <= std::max(_clickPressedCoord.x,_lastCoord.x);++x)
                {
                    _selectedCoords.emplace_back(x,y);

                    sf::Vector2f pixels = viewer.mapCoordsToPixel(_selectedCoords.back());

                    sf::ConvexShape* ptr = _highlightLayer->add(_map->getGeometry().getShape());

                    ptr->setFillColor(sf::Color(133,202,215,127));
                    ptr->setPosition(pixels);

                    _selectionHighlight.emplace_back(ptr);

                }
            }
        }

        void MapSelectionManager::_valideSelectedArea()
        {
            for(auto& coord : _selectedCoords)
            {
                _owner.fillTile(coord);
            }

            _resetSelection();
        }

        void MapSelectionManager::_resetSelection()
        {
            for(auto& ptr : _selectionHighlight)
            {
                _highlightLayer->remove(ptr,false);
            }

            _selectedCoords.clear();
        }
    }
}
