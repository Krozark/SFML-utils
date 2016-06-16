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

        sfutils::map::LayerModel::pointer MapStateChanger::newLayer(const std::string& name, const std::string& layerType,bool isStatic, bool isVisible)
        {
            sfutils::map::LayerTypeModel::pointer_array array;
            sfutils::map::LayerTypeModel::query()
                .filter(layerType,orm::op::exact,sfutils::map::LayerTypeModel::$name)
                .get(array);
            if(array.size() <= 0)
            {
                return nullptr;
            }

            sfutils::map::LayerModel::pointer_array array2;
            sfutils::map::LayerModel::query()
                .filter(_owner._dbMap->getPk(),orm::op::exact,sfutils::map::LayerModel::$map)
                .get(array2);

            auto layer = sfutils::map::LayerModel::create();
            layer->name = name;
            layer->zBuffer = array2.size() + 1;
            layer->isStatic = isStatic;
            layer->isVisible =isVisible;
            layer->type = array.front();
            layer->map = _owner._dbMap;

            layer->save();

            return layer;
        }

        bool MapStateChanger::delLayer(int index)
        {
            std::cout<<"Deleting layer "<<index<<std::endl;

            {
                //internal data
                auto tileFunc = [index](const TileInfo& i){
                    return index == i.z;
                };

                _tileToRemove.remove_if(tileFunc);
                _tileToAdd.remove_if(tileFunc);
            }

            {
                //visual
                sfutils::map::VLayer* current = _owner._map->atZ(index);
                assert(current);
                _owner._map->removeLayer(current);
            }

            {
                //database
                auto current = _getLayer(index);
                assert(current.get());

                sfutils::map::TileModel::pointer_array tiles;
                sfutils::map::TileModel::query()
                    .filter(current->getPk(),orm::op::exact,sfutils::map::TileModel::$layer)
                    .get(tiles);
                
                //remove tiles
                for(auto& t : tiles)
                {
                    std::cout<<"deleting tile "<<t->x.getValue()<<":"<<t->y.getValue()<<std::endl;
                    t->del();
                }
                //remove layer
                current->del();

                //decrease other layer z buffer
                sfutils::map::LayerModel::pointer_array layers;
                sfutils::map::LayerModel::query()
                    .filter(
                            orm::Q<sfutils::map::LayerModel>(current->zBuffer.getValue(),orm::op::gte,sfutils::map::LayerModel::$zBuffer)
                            && orm::Q<sfutils::map::LayerModel>(current->map->getPk(),orm::op::gte,sfutils::map::LayerModel::$map)
                    )
                    .get(layers);

                int z = current->zBuffer.getValue();
                for(auto& l : layers)
                {
                    //visual
                    sfutils::map::VLayer* other = _owner._map->atZ(l->zBuffer.getValue());
                    assert(other);
                    other->setZ(z);

                    //db
                    l->zBuffer = z;
                    ++z;
                    l->save();
                }
            }


            return true;
        }

        bool MapStateChanger::moveLayer(int from,int to)
        {
            std::cout<<"Move layer "<<from<<" to "<<to<<std::endl;
            if(from == to)
            {
                return false;
            }

            {
                //DB objects
                sfutils::map::LayerModel::pointer currentLayer = _getLayer(from);
                assert(currentLayer.get());

                sfutils::map::LayerModel::pointer_array layers;
                sfutils::map::LayerModel::query()
                    .filter(
                            orm::Q<sfutils::map::LayerModel>(to,orm::op::exact,sfutils::map::LayerModel::$zBuffer)
                           )
                    .get(layers);

                for(auto& layer : layers)
                {
                    layer->zBuffer = currentLayer->zBuffer;
                    layer->save();
                }
                currentLayer->zBuffer = to;
                currentLayer->save();
            }

            {
                //update visual map
                sfutils::map::VLayer* current = _owner._map->atZ(from);
                assert(current);
                _owner._map->removeLayer(current,false);
                current->setZ(to);
                _owner._map->addLayer(current);

                sfutils::map::VLayer* other = _owner._map->atZ(to);
                if(other != nullptr)
                {
                    _owner._map->removeLayer(other,false);
                    other->setZ(from);
                    _owner._map->addLayer(other);
                }
            }

            {
                //update internal data
                for(auto& t : _tileToAdd)
                {
                    if(t.z == from)
                    {
                        t.z = to;
                    }
                    else if(t.z == to)
                    {
                        t.z = from;
                    }
                }

                for(auto& t : _tileToRemove)
                {
                    if(t.z == from)
                    {
                        t.z = to;
                    }
                    else if(t.z == to)
                    {
                        t.z = from;
                    }
                }
            }

            return true;
        }

        bool MapStateChanger::changeVisibilityLayer(int index)
        {
            auto l = _getLayer(index);
            if(l == nullptr)
            {
                return false;
            }

            l->isVisible = not l->isVisible.getValue();
            l->save();

            sfutils::map::VLayer* current = _owner._map->atZ(index);

            assert(current);

            current->setVisible(l->isVisible.getValue());

            return true;
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
                }

                TileInfo tmp(layer.getZ(),coord,_delTile);
                _tileToRemove.remove(tmp);
                _tileToRemove.emplace_back(std::move(tmp));
            }

            if(textureFile.empty() == false)
            {
                {
                    sfutils::map::Tile tmp(_owner._map->getGeometry(),coord);
                    tmp.setTexture(&_owner._mapManager->getTextureManager().get(textureFile));
                    tmp.setTextureRect(_owner._map->getGeometry().getTextureRect(coord));
                    layer.add(std::move(tmp));
                }

                {
                    TileInfo tmp(layer.getZ(),coord,_addTile);
                    tmp.texture = textureFile;

                    _tileToAdd.remove(tmp);
                    _tileToAdd.emplace_back(std::move(tmp));
                }
            }
        }

        void MapStateChanger::addSprite(sfutils::map::Layer<sf::Sprite>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;
            std::cout<<"Sprite"<<std::endl;
        }

        void MapStateChanger::addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;
            std::cout<<"SpritePtr"<<std::endl;
        }

        void MapStateChanger::addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const sf::Vector2i& coord,const std::string& textureFile)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;
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
                std::cout<<"deleting tile "<<info.coord.x<<":"<<info.coord.y<<std::endl;
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

            std::cout<<"adding tile "<<info.coord.x<<":"<<info.coord.y<<std::endl;
        }
    }
}
