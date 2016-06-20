#include <SFML-utils/map-editor/Editor.hpp>

#include <cassert>
#include <iostream>

#include <utils/maths.hpp>
#include <utils/sys.hpp>
#include <utils/string.hpp>

#include <SFML-utils/map-editor/path.hpp>

#include <SFML-utils/map/DatabaseMapLoader.hpp>

#include <ORM/all.hpp>


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
            _mapViewer(_window,nullptr,true)
        {

            _window.setFramerateLimit(65);
            _window.setMouseCursorVisible(false);

            {
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

            for(auto& file : _getBrushList())
            {
                _gui.addBrush(file);
            }

        }

        const sfutils::map::MapModel::pointer Editor::getMap()const
        {
            return _dbMap;
        }

        const sfutils::map::MapViewer& Editor::getMapViewer()const
        {
            return _mapViewer;
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
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;

            setZoom(value);
        }

        bool Editor::requestNewLayer(const std::string& name, const std::string& layerType,bool isStatic, bool isVisible)
        {
             sfutils::map::LayerModel::pointer ptr = _mapStateChanger.newLayer(name,layerType,isStatic,isVisible);
             if(ptr == nullptr)
             {
                 return false;
             }

             _gui.addLayer(ptr,true);

             sfutils::map::VLayer* layer = sfutils::map::VLayer::create(layerType,ptr->zBuffer.getValue(),isStatic);

             if(not layer)
             {
                 std::cerr<<"Unknow content-type "<<layerType<<std::endl;
                 return false;
             }

             _map->addLayer(layer);

             return true;
        }

        bool Editor::requestDelLayer(int index)
        {
            return _mapStateChanger.delLayer(index);
        }

        bool Editor::requestMoveLayer(int from,int to)
        {
            return _mapStateChanger.moveLayer(from,to);
        }

        bool Editor::requestVisibilityLayer(int index)
        {
            return _mapStateChanger.changeVisibilityLayer(index);
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
            _currentTileInfo = TileInfo();

            if(utils::string::endswith(texture,".json"))
            {
                //json file
                res = _spriteSheetSelector.setFile(path::DIRECTORY_SPRITES + texture,_mapManager->getTextureManager());
                _spriteSheetSelector.setVisible(res);
            }
            else
            {
                _spriteSheetSelector.setVisible(false);
                //image file
                res = setCurrentSprite(path::DIRECTORY_SPRITES + texture);
            }

            if(res == false)
            {
                _gui.delTexture(texture);
            }

            return res;
        }

        bool Editor::requestBrushSelected(const std::string& brush)
        {
            return _mapSelectionManager.setSelectionBrush(brush);
        }

        bool Editor::setCurrentSprite(const std::string& spr)
        {
            bool res = true;
            try
            {
                sf::Texture& tex = _mapManager->getTextureManager().getOrLoad(spr,spr);
                tex.setRepeated(true);
                _currentTileInfo.texture = spr;
                _currentTileInfo.textureRect = sf::IntRect();
                _currentTileInfo.textureCenterCoord = sf::Vector2f();
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
            _currentTileInfo.texture = spr;
            _currentTileInfo.textureRect = rect;
            _currentTileInfo.textureCenterCoord = sf::Vector2f(0.5,0.75);

            return true;
        }

        void Editor::fillTile(const sf::Vector2i& coord)
        {
            int currentLayerIndex = _gui.getCurrentLayerZIndex();
            std::cout<<"fill tile ("<<coord.x<<":"<<coord.y<<":"<<currentLayerIndex<<")"
                     <<", Current texture file : "<<_currentTileInfo.texture<<std::endl;

            sfutils::map::VLayer* currentLayer = _map->atZ(currentLayerIndex);

            if((currentLayer != nullptr) && (_currentTileInfo.texture.empty() == false))
            {
                std::string type = currentLayer->getType();
                
                TileInfo info = _currentTileInfo;
                info.z = currentLayer->getZ();
                info.coord = coord;

                if(type == "tile")
                {
                    _mapStateChanger.addTile(dynamic_cast<sfutils::map::Layer<sfutils::map::Tile>&>(*currentLayer),info);
                }
                else if(type == "sprite")
                {
                    _mapStateChanger.addSprite(dynamic_cast<sfutils::map::Layer<sf::Sprite>&>(*currentLayer),info);
                }
                else if(type == "sprite_ptr")
                {
                    _mapStateChanger.addSpritePtr(dynamic_cast<sfutils::map::Layer<sf::Sprite*>&>(*currentLayer),info);
                }
                else if(type == "entity")
                {
                    _mapStateChanger.addEntity(dynamic_cast<sfutils::map::Layer<sfutils::map::Entity*>&>(*currentLayer),info);
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
                else if(_mapViewer.processEvent(event))
                {
                    reloadAreas = true;
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
                else if(_mapSelectionManager.processEvent(event))
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
            //window 1
            _window.setActive(true);
            _window.clear();

            _mapViewer.draw();
            _gui.render();
            _mapSelectionManager.render(_window);

            _window.display();
            

            //window2
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
           std::list<std::string> list = utils::sys::dir::list_files(path::DIRECTORY_SPRITES);

           std::list<std::string> list2 = utils::sys::dir::list_files(path::DIRECTORY_SPRITES_SHEETS);

           for(std::string& f : list2)
           {
               if(utils::string::endswith(f,".json"))
               {
                   list.emplace_back(path::DIRECTORY_SPRITES__SHEETS_NAME + "/" + f);
               }
           }

           list.sort();

            return list;
        }

        std::list<std::string> Editor::_getBrushList()const
        {
           std::list<std::string> list = utils::sys::dir::list_files(path::DIRECTORY_BRUSH);

           list.sort();

            return list;
        }

        void Editor::_reset()
        {
            _currentTileInfo = TileInfo();

            _gui.reset();
            _mapStateChanger.reset();
            _mapSelectionManager.reset();
        }

    }
}
