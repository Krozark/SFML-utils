#include <SFML-utils/map-editor/MapStateChanger.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

namespace sfutils
{
    namespace editor
    {
        MapStateChanger::MapStateChanger(Editor& owner) : 
            _owner(owner)
        {
        }

        void MapStateChanger::reset()
        {
            _tileToAdd.clear();
            _tileToRemove.clear();
        }

        void MapStateChanger::save()
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _tileToRemove.sort();
            _tileToRemove.unique();
            //TODO remove from DB
            

            int lastZ = -99999;
            sfutils::map::LayerModel::pointer layer;
            for(TileInfo& tile: _tileToRemove)
            {
                if(tile.z != lastZ)
                {
                    lastZ = tile.z;
                    layer = _getLayer(lastZ);
                    if(layer == nullptr)
                    {
                        assert(false && "this should never apear");
                        continue;
                    }
                }
                tile.func(layer,tile);                    
            }

            _tileToAdd.sort();
            _tileToAdd.unique();
            //TODO insert into DB
            lastZ = -99999;
            for(TileInfo& tile: _tileToAdd)
            {
                if(tile.z != lastZ)
                {
                    lastZ = tile.z;
                    layer = _getLayer(lastZ);
                    if(layer == nullptr)
                    {
                        assert(false && "this should never apear");
                        continue;
                    }
                }
                tile.func(layer,tile);                    
            }

            _owner._dbMap->save();
        }

        void MapStateChanger::setTitle(const std::string& title)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->name = title;
        }

        void MapStateChanger::setSize(int scale,int width, int height)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->scale = scale;;
            _owner._dbMap->areaWidth = width;
            _owner._dbMap->areaHeight = height;

        }

        void MapStateChanger::setGeometry(sfutils::map::GeometryModel::pointer& geo)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->geometry = geo;
        }

        bool MapStateChanger::newLayer()
        {
            //TODO
            return false;
        }

        bool MapStateChanger::delLayer(int index)
        {
            auto tileFunc = [index](const TileInfo& i){
                return index == i.z;
            };

            _tileToRemove.remove_if(tileFunc);
            _tileToAdd.remove_if(tileFunc);

            //TODO remove from _map

            return true;
        }

        bool MapStateChanger::moveLayer(int from,int to)
        {
            //TODO change zbuffer of it, and all others to be sure that no z index is duplicated
            //TODO update _tileToXXX
            return false;
        }

        void MapStateChanger::addTile(sfutils::map::Layer<sfutils::map::Tile>& layer,const sf::Vector2i& coord,const std::string& textureFile)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            std::cout<<"Tile"<<std::endl;

            auto objs = layer.getByCoords(coord,*_owner._map);
            if(objs.size() > 0)
            {
                std::cout<<objs.size()<<" objects here in "<<coord.x<<" "<<coord.y<<std::endl;
                for(auto ptr : objs)
                {
                    layer.remove(ptr,false);
                    _tileToRemove.emplace_back(layer.z(),coord,_delTile);
                }
            }

            if(textureFile.empty() == false)
            {
                sfutils::map::Tile tmp(_owner._map->getGeometry(),coord);
                tmp.setTexture(&_owner._mapManager->getTextureManager().get(textureFile));
                tmp.setTextureRect(_owner._map->getGeometry().getTextureRect(coord));

                layer.add(std::move(tmp));
                _tileToAdd.emplace_back(layer.z(),coord,_addTile);
                _tileToAdd.back().texture = textureFile;
            }
        }

        void MapStateChanger::addSprite(sfutils::map::Layer<sf::Sprite>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"Sprite"<<std::endl;
        }

        void MapStateChanger::addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"SpritePtr"<<std::endl;
        }

        void MapStateChanger::addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const sf::Vector2i& coord,const std::string& textureFile)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"Entity"<<std::endl;
        }


        ///////////////////// PRIVATE ////////////////////////////
        sfutils::map::LayerModel::pointer MapStateChanger::_getLayer(int zbuffer)
        {
            sfutils::map::LayerModel::pointer_array layers;
            sfutils::map::LayerModel::query()
                .filter(
                        orm::Q<sfutils::map::LayerModel>(_owner._dbMap->getPk(),orm::op::exact,sfutils::map::LayerModel::$map)
                        && orm::Q<sfutils::map::LayerModel>(zbuffer,orm::op::exact,sfutils::map::LayerModel::$zBuffer)
                       )
                .get(layers);

            if(layers.size()> 0)
            {
                return layers.front();
            }
            return nullptr;
        }

        void MapStateChanger::_delTile(sfutils::map::LayerModel::pointer& layer,const TileInfo& info)
        {
            sfutils::map::TileModel::pointer_array tiles;
            sfutils::map::TileModel::query()
                .filter(
                        orm::Q<sfutils::map::TileModel>(layer->getPk(),orm::op::exact,sfutils::map::TileModel::$layer)
                        && orm::Q<sfutils::map::TileModel>(info.coord.x,orm::op::exact,sfutils::map::TileModel::$x)
                        && orm::Q<sfutils::map::TileModel>(info.coord.y,orm::op::exact,sfutils::map::TileModel::$y)
                )
                .get(tiles);

            if(tiles.size()> 0)
            {
                std::cout<<"deleting "<<*tiles.front()<<std::endl;
                tiles.front()->del();
            }
        }

        void MapStateChanger::_addTile(sfutils::map::LayerModel::pointer& layer,const TileInfo& info)
        {
            auto tile = sfutils::map::TileModel::create();
            tile->texture = info.texture;
            tile->x = info.coord.x;
            tile->y = info.coord.y;
            tile->layer = layer;

            tile->save();

            std::cout<<"adding "<<*tile<<std::endl;
        }
    }
}
