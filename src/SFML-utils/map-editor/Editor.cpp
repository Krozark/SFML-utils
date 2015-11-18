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
            _mapViewer(_window)
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

        void Editor::setMap(sfutils::map::MapModel::type_ptr& map)
        {
            _mapManager.reset(new sfutils::map::MapManager(std::shared_ptr<sfutils::map::VMapLoader>(new sfutils::map::DatabaseMapLoader(map))));

            _map = _mapManager->getMap();
            _mapViewer.setMap(_map);

            sfutils::map::Layer<sf::ConvexShape>* mouse_layer = new sfutils::map::Layer<sf::ConvexShape>("ConvexShape",100);

            _highlight = mouse_layer->add(_map->getGeometry().getShape());
            _highlight->setFillColor(sf::Color(0,255,0,127));
            _map->addLayer(mouse_layer);

            sf::IntRect rect = _getVisibleAreaRect(); 
            _loadVisiblesAreas(rect);

        }

        ////////////////////// PRIVATE ////////////////////
        void Editor::_processEvents()
        {
            sf::Event event;

            bool reloadAreas = false;

            while(_window.pollEvent(event))
            {
                _gui.processEvent(event);

                if(event.type == sf::Event::Closed ) 
                {
                    _window.close();
                }
                else if(_mapViewer.processEvent(event))
                {
                    reloadAreas = true;
                    
                }
                else if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i coord = _mapViewer.mapScreenToCoords(sf::Vector2i(event.mouseButton.x,event.mouseButton.y));
                    std::cout<<"Click on ("<<coord.x<<":"<<coord.y<<")"<<std::endl;
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
