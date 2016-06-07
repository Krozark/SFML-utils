#include <SFML-utils/map-editor/Editor.hpp>

#include <cassert>
#include <iostream>

#include <utils/maths.hpp>
#include <utils/sys.hpp>
#include <utils/string.hpp>

#include <SFML-utils/map/DatabaseMapLoader.hpp>


#include <ORM/all.hpp>
#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3DB def("./db.sqlite");
orm::DB& orm::DB::Default = def;

const std::string DIRECTORY_MEDIA_NAME = "media";
const std::string DIRECTORY_MEDIA = DIRECTORY_MEDIA_NAME + "/";

const std::string DIRECTORY_SPRITES_NAME = "sprites";
const std::string DIRECTORY_SPRITES = DIRECTORY_MEDIA + DIRECTORY_SPRITES_NAME + "/";

const std::string DIRECTORY_SPRITES__SHEETS_NAME = "sheets";
const std::string DIRECTORY_SPRITES_SHEETS = DIRECTORY_SPRITES + DIRECTORY_SPRITES__SHEETS_NAME + "/";

namespace sfutils
{
    namespace editor
    {
        Editor::Editor():
            _window(sf::VideoMode(1600,900),"SFML-utils map editor"),
            _gui(_window,*this),
            _spriteSheetSelector(*this),
            _mapStateChanger(*this),
            _mapSelectionManager(*this),
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
            orm::DB::Default.disconnect();
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
            _reset();

            _dbMap = map;

            _mapManager.reset(new sfutils::map::MapManager(std::shared_ptr<sfutils::map::VMapLoader>(new sfutils::map::DatabaseMapLoader(map))));

            _map = _mapManager->getMap();
            _mapViewer.setMap(_map);

            _mapSelectionManager.setMap(_map);

            sf::IntRect rect = _getVisibleAreaRect(); 
            _loadVisiblesAreas(rect);

            ////////////// GUI ///////////
            _spriteSheetSelector.setVisible(false);

            //map
            _gui.setTitle(map->name);

            //layers
            sfutils::map::LayerModel::pointer_array layers = _getMapLayers();

            for(auto& layer : layers)
            {
                _gui.addLayer(layer);
            }


            for(auto& tex : _getTextureList())
            {
                _gui.addTexture(tex);
            }

        }

        const sfutils::map::MapModel::pointer Editor::getMap()const
        {
            return _dbMap;
        }

        MapStateChanger& Editor::getMapStateChanger()
        {
            return _mapStateChanger;
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
            return _mapStateChanger.newLayer();
        }

        bool Editor::requestDelLayer(int index)
        {
            return _mapStateChanger.delLayer(index);
        }

        bool Editor::requestMoveLayer(int from,int to)
        {
            return _mapStateChanger.moveLayer(from,to);
        }

        bool Editor::requestSetCurrentLayer(int index)
        {
            _currentLayerIndex = index;
            return true;
        }

        bool Editor::requestSaveMap()
        {
            _mapStateChanger.save();
            requestReloadMap();

            return true;
        }

        bool Editor::requestReloadMap()
        {
            setMap(_dbMap);

            return true;
        }

        bool Editor::requestTextureSelected(const std::string& texture)
        {
            bool res = true;
            //reset
            _currentTextureRect = sf::IntRect();
            _currentTextureFile.clear();

            if(utils::string::endswith(texture,".json"))
            {
                //json file
                res = _spriteSheetSelector.setFile(DIRECTORY_SPRITES + texture,_mapManager->getTextureManager());
                _spriteSheetSelector.setVisible(res);
            }
            else
            {
                _spriteSheetSelector.setVisible(false);
                //image file
                res = setCurrentSprite(DIRECTORY_SPRITES + texture);
            }

            if(res == false)
            {
                _gui.delTexture(texture);
            }

            return res;
        }

        bool Editor::setCurrentSprite(const std::string& spr)
        {
            //TODO
            bool res = true;
            try
            {
                sf::Texture& tex = _mapManager->getTextureManager().getOrLoad(spr,spr);
                tex.setRepeated(true);
                _currentTextureFile = spr;
            }
            catch(const std::exception& e)
            {
                std::cerr<<"Catch "<<e.what()<<std::endl;
                res = false;
            }

            return res;
        }

        bool Editor::setCurrentSprite(const std::string& spr,const sf::IntRect& rect)
        {
            //TODO
            _currentTextureFile = spr;
            _currentTextureRect = rect;
            return false;
        }

        void Editor::fillTile(const sf::Vector2i& coord)
        {
            //TODO
            std::cout<<"Click on ("<<coord.x<<":"<<coord.y<<")"<<std::endl;
            std::cout<<"Current texture file : "<<_currentTextureFile<<std::endl;
            std::cout<<"Current layer index : "<<_currentLayerIndex<<std::endl;

            sfutils::map::VLayer* currentLayer = _map->atZ(_currentLayerIndex);

            if((currentLayer != nullptr) && (_currentTextureFile.empty() == false))
            {
                std::string type = currentLayer->getType();

                if(type == "tile")
                {
                    _mapStateChanger.addTile(dynamic_cast<sfutils::map::Layer<sfutils::map::Tile>&>(*currentLayer),coord,_currentTextureFile);
                }
                else if(type == "sprite")
                {
                    _mapStateChanger.addSprite(dynamic_cast<sfutils::map::Layer<sf::Sprite>&>(*currentLayer),coord,_currentTextureFile,_currentTextureRect);
                }
                else if(type == "sprite_ptr")
                {
                    _mapStateChanger.addSpritePtr(dynamic_cast<sfutils::map::Layer<sf::Sprite*>&>(*currentLayer),coord,_currentTextureFile,_currentTextureRect);
                }
                else if(type == "entity")
                {
                    _mapStateChanger.addEntity(dynamic_cast<sfutils::map::Layer<sfutils::map::Entity*>&>(*currentLayer),coord,_currentTextureFile);
                }
                else
                {
                    std::cerr<<"Unknow layer type "<<type<<std::endl;
                }
            }

        }


        ////////////////////// PRIVATE ////////////////////
        sfutils::map::LayerModel::pointer_array Editor::_getMapLayers()const
        {
            assert(_dbMap);

            sfutils::map::LayerModel::pointer_array layers;
            sfutils::map::LayerModel::query()
                .filter(_dbMap->getPk(),orm::op::exact,sfutils::map::LayerModel::$map)
                .orderBy(sfutils::map::LayerModel::$zBuffer,'-')
                .get(layers);

            return layers;
        }

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
                else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F5)
                {
                    sf::IntRect rect = _getVisibleAreaRect(); 
                    if(_mapManager)
                    {
                        _mapManager->clear();
                    }
                    _loadVisiblesAreas(rect);
                }
                else if(_mapSelectionManager.processEvent(event,_mapViewer))
                {
                }
            }

            reloadAreas |= _mapViewer.processEvents();

            _spriteSheetSelector.processEvents();

            if(reloadAreas)
            {
                sf::IntRect rect = _getVisibleAreaRect(); 
                if(_lastVisibleRect != rect)
                {
                    _loadVisiblesAreas(rect);
                }
            }

        }

        void Editor::_update()
        {
            sf::Time deltaTime = _clock.restart();

            if(_map)
            {
                sf::Vector2i coord = _mapViewer.mapScreenToCoords(sf::Mouse::getPosition(_window));

                sf::Vector2i area = _map->mapCoordsToArea(coord);

                _gui.setMainInfo("(" + std::to_string(coord.x) + ":" + std::to_string(coord.y)
                                    + "),(" + std::to_string(area.x) + ":" + std::to_string(area.y) + ")");
            }

            _gui.update(deltaTime);
            _spriteSheetSelector.update(deltaTime);

            _mapViewer.update(deltaTime);
        }

        void Editor::_render()
        {
            _window.setActive(true);
            _window.clear();
            _mapViewer.draw();
            _gui.render();
            _window.display();

            _spriteSheetSelector.render();
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

        std::list<std::string> Editor::_getTextureList()const
        {
           std::list<std::string> list = utils::sys::dir::list_files(DIRECTORY_SPRITES);

           std::list<std::string> list2 = utils::sys::dir::list_files(DIRECTORY_SPRITES_SHEETS);

           for(std::string& f : list2)
           {
               if(utils::string::endswith(f,".json"))
               {
                   list.emplace_back( DIRECTORY_SPRITES__SHEETS_NAME + "/" + f);
               }
           }

           list.sort();

            return list;
        }

        void Editor::_reset()
        {
            _currentTextureRect = sf::IntRect();
            _currentTextureFile.clear();
            _currentLayerIndex = 0;

            _gui.reset();
            _mapStateChanger.reset();
            _mapSelectionManager.reset();
        }

    }
}
