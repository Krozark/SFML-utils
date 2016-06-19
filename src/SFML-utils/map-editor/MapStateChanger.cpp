#include <SFML-utils/map-editor/MapStateChanger.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/map/es/Entity.hpp>
#include <SFML-utils/map/es/Components.hpp>


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
                    std::cout<<"deleting tile "<<t->posX.getValue()<<":"<<t->posY.getValue()<<std::endl;
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

        void MapStateChanger::addTile(sfutils::map::Layer<sfutils::map::Tile>& layer,const TileInfo& info)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            std::cout<<"Tile"<<std::endl;

            auto objs = layer.getByCoords(info.coord,*_owner._map);
            if(objs.size() > 0)
            {
                std::cout<<objs.size()<<" objects here in "<<info.coord.x<<" "<<info.coord.y<<std::endl;
                for(auto ptr : objs)
                {
                    layer.remove(ptr,false);
                }

                TileInfo tmp = info;
                tmp.func =_delTile;
                _tileToRemove.remove(tmp);
                _tileToRemove.emplace_back(std::move(tmp));
            }

            if(info.texture.empty() == false)
            {
                {
                    sfutils::map::Tile tmp(_owner._map->getGeometry(),info.coord);
                    tmp.setTexture(&_owner._mapManager->getTextureManager().get(info.texture));
                    tmp.setTextureRect(_owner._map->getGeometry().getTextureRect(info.coord));
                    layer.add(std::move(tmp));
                }

                {
                    TileInfo tmp = info;
                    tmp.func = _addTile;

                    _tileToAdd.remove(tmp);
                    _tileToAdd.emplace_back(std::move(tmp));
                }
            }
        }

        void MapStateChanger::addSprite(sfutils::map::Layer<sf::Sprite>& layer,const TileInfo& info)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;
            std::cout<<"Sprite"<<std::endl;
        }

        void MapStateChanger::addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const TileInfo& info)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"TODO : "<<__FILE__<<":"<<__LINE__<<std::endl;
            std::cout<<"SpritePtr"<<std::endl;
        }

        void MapStateChanger::addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const TileInfo& info)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            std::cout<<"Entity"<<std::endl;

            auto objs = layer.getByCoords(info.coord,*_owner._map);
            if(objs.size() > 0)
            {
                std::cout<<objs.size()<<" objects here in "<<info.coord.x<<" "<<info.coord.y<<std::endl;
                for(auto ptr : objs)
                {
                    layer.remove(ptr,false);
                }

                TileInfo tmp = info;
                tmp.func = _delEntity;
                _tileToRemove.remove(tmp);
                _tileToRemove.emplace_back(std::move(tmp));
            }

            if(info.texture.empty() == false)
            {
                {
                    //get texture
                    sf::Texture& tex = _owner._mapManager->getTextureManager().get(info.texture);
                    //texture rect
                    sf::IntRect textRect;
                    if(info.textureRect != sf::IntRect())
                    {
                        textRect = info.textureRect;
                    }
                    else
                    {
                        textRect = _owner._map->getGeometry().getTextureRect(info.coord);
                    }
                    //sprite
                    sf::Sprite spr(tex,textRect);
                    //sprite center
                    //
                    spr.setOrigin(textRect.width * info.textureCenterCoord.x,
                                  textRect.height * info.textureCenterCoord.y);

                    //entity
                    sfutils::map::Entity& e = _owner._map->createEntity();
                    e.add<sfutils::map::CompSkinStatic>(); //TODO
                    e.component<sfutils::map::CompSkinStatic>()->_sprite = spr;
                    e.component<sfutils::map::CompSkinStatic>()->_sprite.setPosition(_owner._map->getGeometry().mapCoordsToPixel(info.coord));

                    layer.add(&e);

                }

                {
                    TileInfo tmp = info;
                    tmp.func = _addEntity;

                    _tileToAdd.remove(tmp);
                    _tileToAdd.emplace_back(std::move(tmp));
                }
            }
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
                        && orm::Q<sfutils::map::TileModel>(info.coord.x,orm::op::exact,sfutils::map::TileModel::$posX)
                        && orm::Q<sfutils::map::TileModel>(info.coord.y,orm::op::exact,sfutils::map::TileModel::$posY)
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
            tile->posX = info.coord.x;
            tile->posY = info.coord.y;
            tile->layer = layer;

            tile->save();

            std::cout<<"adding tile "<<info.coord.x<<":"<<info.coord.y<<std::endl;
        }

        void MapStateChanger::_delEntity(sfutils::map::LayerModel::pointer& layer,const TileInfo& info)
        {
            sfutils::map::TileModel::pointer_array tiles;
            sfutils::map::TileModel::query()
                .filter(
                        orm::Q<sfutils::map::TileModel>(layer->getPk(),orm::op::exact,sfutils::map::TileModel::$layer)
                        && orm::Q<sfutils::map::TileModel>(info.coord.x,orm::op::exact,sfutils::map::TileModel::$posX)
                        && orm::Q<sfutils::map::TileModel>(info.coord.y,orm::op::exact,sfutils::map::TileModel::$posY)
                )
                .get(tiles);

            if(tiles.size()> 0)
            {
                std::cout<<"deleting entity "<<info.coord.x<<":"<<info.coord.y<<std::endl;
                tiles.front()->del();
            }
        }

        void MapStateChanger::_addEntity(sfutils::map::LayerModel::pointer& layer,const TileInfo& info)
        {
            auto tile = sfutils::map::TileModel::create();
            tile->texture = info.texture;
            tile->posX = info.coord.x;
            tile->posY = info.coord.y;
            tile->layer = layer;

            tile->textureRectTop = info.textureRect.top;
            tile->textureRectLeft = info.textureRect.left;
            tile->textureRectWidth = info.textureRect.width;
            tile->textureRectHeigh = info.textureRect.height;

            tile->textureCenterLeft = info.textureCenterCoord.x;
            tile->textureCenterTop = info.textureCenterCoord.y;

            tile->save();

            std::cout<<"adding Entity "<<info.coord.x<<":"<<info.coord.y<<std::endl;
        }
    }
}
