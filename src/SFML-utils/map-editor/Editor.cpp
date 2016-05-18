#include <SFML-utils/map-editor/Editor.hpp>

#include <cassert>
#include <iostream>

#include <utils/maths.hpp>
#include <SFML-utils/map/DatabaseMapLoader.hpp>

#include <ORM/all.hpp>
#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3DB def("./db.sqlite");
orm::DB& orm::DB::Default = def;

namespace sfutils
{
    namespace editor
    {
        Editor::Editor():
            _window(sf::VideoMode(1600,900),"SFML-utils map editor"),
            _gui(_window,*this),
            _map(nullptr),
            _mapViewer(_window,nullptr,false)
        {

            _window.setFramerateLimit(65);
            _window.setMouseCursorVisible(false);

            {
                orm::DB::Default.connect();
                orm::Tables::create();
                sfutils::map::loadInitialData();
            }

            auto map = sfutils::map::MapModel::get(1);
            setMap(map);
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

        void Editor::setMap(sfutils::map::MapModel::pointer& map)
        {
            _mapManager.reset(new sfutils::map::MapManager(std::shared_ptr<sfutils::map::VMapLoader>(new sfutils::map::DatabaseMapLoader(map))));

            _map = _mapManager->getMap();
            _mapViewer.setMap(_map);

            //special layers
            sfutils::map::Layer<sf::ConvexShape>* mouse_layer = new sfutils::map::Layer<sf::ConvexShape>("ConvexShape",100);

            _highlight = mouse_layer->add(_map->getGeometry().getShape());
            _highlight->setFillColor(sf::Color(0,255,0,127));
            _map->addLayer(mouse_layer);

            sf::IntRect rect = _getVisibleAreaRect(); 
            _loadVisiblesAreas(rect);

            ////////////// GUI ///////////
            _gui.reset();

            //map
            _gui.setTitle(map->name);

            //layers
            sfutils::map::LayerModel::pointer_array layers;
            sfutils::map::LayerModel::query()
                .filter(map->getPk(),orm::op::exact,sfutils::map::LayerModel::$map)
                .orderBy(sfutils::map::LayerModel::$zBuffer,'-')
                .get(layers);

            for(auto& layer : layers)
            {
                _gui.addLayer(layer);
            }

        }

        void Editor::setZoom(float value)
        {
            auto size = _window.getSize();
            _mapViewer.setSize(size.x * value, size.y * value);
        }

        void Editor::setMiniMapZoom(float value)
        {
            //TODO
            setZoom(value);
        }

        bool Editor::requestNewLayer()
        {
            //TODO
            return false;
        }

        bool Editor::requestDelLayer(int index)
        {
            //TODO
            return false;
        }

        bool Editor::requestMoveLayer(int from,int to)
        {
            //TODO change zbuffer of it, and all others to be sure that no z index is duplicated
            return false;
        }

        ////////////////////// PRIVATE ////////////////////
        void Editor::_processEvents()
        {
            sf::Event event;

            bool reloadAreas = false;

            while(_window.pollEvent(event))
            {
                if(_gui.processEvent(event))
                {
                    continue;
                }

                if(event.type == sf::Event::Closed ) 
                {
                    _window.close();
                }
                ///////////////////map viewer/////////////////////
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Up)
                {
                    _mapViewer.move(0,-20);
                }
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Down)
                {
                    _mapViewer.move(0,20);
                }
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Right)
                {
                    _mapViewer.move(20,0);
                }
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Left)
                {
                    _mapViewer.move(-20,0);
                }
                ///////////////////editor logics//////////////////
                else if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i coord = _mapViewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                    _onClick(coord);
                }
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F5)
                {
                    sf::IntRect rect = _getVisibleAreaRect(); 
                    if(_mapManager)
                    {
                        _mapManager->clear();
                    }
                    _loadVisiblesAreas(rect);
                }
            }
            
            reloadAreas |= _mapViewer.processEvents();

            if(reloadAreas)
            {
                sf::IntRect rect = _getVisibleAreaRect(); 
                if(_lastVisibleRect != rect)
                {
                    _loadVisiblesAreas(rect);
                }
            }

            if(_map)
            {
                sf::Vector2i coord = _mapViewer.mapScreenToCoords(sf::Mouse::getPosition(_window));
                sf::Vector2f pixels = _mapViewer.mapCoordsToPixel(coord);
                _highlight->setPosition(pixels);

                sf::Vector2i area = _map->mapCoordsToArea(coord);

                _gui.setMainInfo("(" + std::to_string(coord.x) + ":" + std::to_string(coord.y)
                                    + "),(" + std::to_string(area.x) + ":" + std::to_string(area.y) + ")");
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
            _gui.render();
            
            _window.display();
        }

        void Editor::_onClick(const sf::Vector2i& coord)
        {
            std::cout<<"Click on ("<<coord.x<<":"<<coord.y<<")"<<std::endl;
        }


        void Editor::_loadVisiblesAreas(const sf::IntRect& rect)
        {
            if(_mapManager == nullptr)
            {
                return;
            }

            _mapManager->removeIf([&rect](int x, int y){
                return not rect.contains(x,y);
            });
            
            for(int x = rect.left; x<= rect.width;++x)
            {
                for(int y = rect.top; y<= rect.height; ++y)
                {
                    _mapManager->loadArea(x,y);
                }
            }
            _lastVisibleRect = rect;

        }

        sf::IntRect Editor::_getVisibleAreaRect()const
        {
            if(_map == nullptr)
            {
                return sf::IntRect(0,0,0,0);
            }
            sf::Vector2u ws = _window.getSize();

            sf::Vector2i top_left_coord = _mapViewer.mapScreenToCoords(sf::Vector2i(0,0));
            top_left_coord = _map->mapCoordsToArea(top_left_coord);

            sf::Vector2i top_right_coord = _mapViewer.mapScreenToCoords(sf::Vector2i(ws.x,0));
            top_right_coord = _map->mapCoordsToArea(top_right_coord);

            sf::Vector2i bottom_right_coord = _mapViewer.mapScreenToCoords(sf::Vector2i(ws.x,ws.y));
            bottom_right_coord = _map->mapCoordsToArea(bottom_right_coord);

            sf::Vector2i bottom_left_coord = _mapViewer.mapScreenToCoords(sf::Vector2i(0,ws.y));
            bottom_left_coord = _map->mapCoordsToArea(bottom_left_coord);

            sf::Vector2i min(utils::maths::min(top_left_coord.x,top_right_coord.x,bottom_right_coord.x,bottom_left_coord.x),
                             utils::maths::min(top_left_coord.y,top_right_coord.y,bottom_right_coord.y,bottom_left_coord.y));

            sf::Vector2i max(utils::maths::max(top_left_coord.x,top_right_coord.x,bottom_right_coord.x,bottom_left_coord.x),
                             utils::maths::max(top_left_coord.y,top_right_coord.y,bottom_right_coord.y,bottom_left_coord.y));

            return sf::IntRect(min.x,min.y,max.x,max.y);
        }
    }
}
