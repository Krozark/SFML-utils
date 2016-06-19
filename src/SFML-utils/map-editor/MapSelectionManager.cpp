#include <SFML-utils/map-editor/MapSelectionManager.hpp>

#include <SFML-utils/map-editor/Editor.hpp>
#include <SFML-utils/map-editor/path.hpp>

#include <algorithm>

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <luabind/tag_function.hpp>


namespace sfutils
{
    namespace editor
    {
        
        MapSelectionManager::MapSelectionManager(Editor& owner) :
            _owner(owner),
            _clickIndicator(sf::PrimitiveType::Lines,2),
            _luaState(nullptr)
        {
            reset();

            for(int i = 0; i < 2; ++i)
            {
                _clickIndicator[i].color = sf::Color(255,20,125);
            }
        }

        MapSelectionManager::~MapSelectionManager()
        {
            if(_luaState != nullptr)
            {
                lua_close(_luaState);
            }
        }

        void MapSelectionManager::reset()
        {
            _map = nullptr;
            _cursorHighlight = nullptr;
            _highlightLayer = nullptr;


            _clickPressedCoord = sf::Vector2i(0,0);
            _clickReleasedCoord = sf::Vector2i(0,0);
            _isPressed = false;

            _resetSelection();

        }

        bool MapSelectionManager::processEvent(const sf::Event& event)
        {
            const sfutils::map::MapViewer& viewer = _owner.getMapViewer();

            if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickPressedCoord = _clickReleasedCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                _isPressed = true;

                _updateSelectionArea();
            }
            else if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _clickReleasedCoord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                _updateSelectionArea();

                _valideSelectedArea();

                _isPressed = false;
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i coord = viewer.mapScreenToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                sf::Vector2f pixels = viewer.mapCoordsToPixel(coord);
                _cursorHighlight->setPosition(pixels);

                if(_isPressed && (_clickReleasedCoord != coord))
                {
                    _clickReleasedCoord = coord;

                    _updateSelectionArea();
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
            _highlightLayer = new sfutils::map::Layer<sf::ConvexShape>("ConvexShape",100,false,true);

            _cursorHighlight = _highlightLayer->add(_map->getGeometry().getShape(),false);
            _cursorHighlight->setFillColor(sf::Color(0,255,0,127));
            _map->addLayer(_highlightLayer);
        }

        bool MapSelectionManager::setSelectionBrush(const std::string& brush)
        {
            if(_luaState != nullptr)
            {
                lua_close(_luaState);
            }

            _luaState = luaL_newstate();

            luaL_openlibs(_luaState);
            luabind::open(_luaState);

            luabind::module(_luaState)[
                luabind::def("addToSelection",luabind::tag_function<void(int,int)>([this](int x,int y){
                             _addSelectedCood(sf::Vector2i(x,y));
                }))
            ];

            if(luaL_dofile(_luaState,(path::DIRECTORY_BRUSH + brush).c_str()))
            {
                std::cerr<<"ERROR while loading \""<<path::DIRECTORY_BRUSH + brush<<"\" : "<<lua_tostring(_luaState, -1)<<std::endl;;
                return false;
            }

            return true;

        }

        ///////////////////////////// PRIVATE /////////////////////////////////
        void MapSelectionManager::_updateSelectionArea()
        {
            assert(_luaState);

            _resetSelection();

            const sfutils::map::MapViewer& viewer = _owner.getMapViewer();

            _clickIndicator[0].position = sf::Vector2f(viewer.mapCoordsToScreen(_clickPressedCoord));
            _clickIndicator[1].position = sf::Vector2f(viewer.mapCoordsToScreen(_clickReleasedCoord));

            luabind::call_function<void>(_luaState, "getSelection",
                                         _clickPressedCoord.x,_clickPressedCoord.y,
                                         _clickReleasedCoord.x,_clickReleasedCoord.y);
            //_squareSelection(viewer);

            _highlightLayer->sort();

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
            if(_highlightLayer != nullptr)
            {
                for(auto& ptr : _selectionHighlight)
                {
                    _highlightLayer->remove(ptr,false);
                }
            }

            _selectedCoords.clear();
        }

        void MapSelectionManager::_addSelectedCood(const sf::Vector2i& coord)
        {
            _selectedCoords.emplace_back(coord);

            sf::Vector2f pixels = _owner.getMapViewer().mapCoordsToPixel(_selectedCoords.back());

            sf::ConvexShape* ptr = _highlightLayer->add(_map->getGeometry().getShape(),false);

            ptr->setFillColor(sf::Color(133,202,215,127));
            ptr->setPosition(pixels);

            _selectionHighlight.emplace_back(ptr);
        }
    }
}
