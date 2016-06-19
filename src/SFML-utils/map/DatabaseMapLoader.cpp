#include <SFML-utils/map/DatabaseMapLoader.hpp>

#include <SFML-utils/map/Models.hpp>

namespace sfutils
{
    namespace map
    {
        DatabaseMapLoader::DatabaseMapLoader(MapModel::pointer& map) : 
            _map(map)
        {
        }

        DatabaseMapLoader::~DatabaseMapLoader()
        {
        }

        std::unique_ptr<MetaArea> DatabaseMapLoader::_loadArea(int x,int y,Map* const map)
        {
            TileModel::pointer_array models;
            TileModel::query()
                .filter(orm::Q<TileModel>(x * _map->areaWidth, orm::op::gte, TileModel::$posX)
                         and orm::Q<TileModel>((x+1) * _map->areaWidth, orm::op::lt, TileModel::$posX)
                         and orm::Q<TileModel>(y * _map->areaHeight, orm::op::gte, TileModel::$posY)
                         and orm::Q<TileModel>((y+1) * _map->areaHeight, orm::op::lt, TileModel::$posY)
                         and orm::Q<TileModel>(_map->getPk(), orm::op::exact, TileModel::$layer, LayerModel::$map))
                .orderBy(TileModel::$layer)
                .get(models);

            std::unique_ptr<MetaArea> meta(new MetaArea(sf::Vector2i(x,y),""));

            LayerModel::pointer current;
            std::unique_ptr<MetaLayer> metaLayer;

            for(TileModel::pointer& tile : models)
            {
                if((current.get() == nullptr) or (current->getPk() != tile->layer->getPk()))
                {
                    current = tile->layer;
                    if(metaLayer)
                    {
                        meta->add(std::move(*metaLayer));
                    }
                    metaLayer.reset(new MetaLayer(tile->layer->zBuffer,
                                                  tile->layer->type->name,
                                                  tile->layer->isVisible,
                                                  tile->layer->isStatic
                                                  ));
                }
                std::shared_ptr<MetaLayerData> data;
                if(tile->layer->type->name == "tile")
                {
                    sf::IntRect textRect(tile->posX -x * _map->areaWidth,tile->posY - y * _map->areaHeight,1,1);
                    data.reset(new MetaLayerDataTileRect(tile->texture,textRect));
                }
                else if(tile->layer->type->name == "sprite" || tile->layer->type->name == "sprite_ptr")
                {
                    sf::Vector2i pos(tile->posX,tile->posY);
                    auto ptr = new MetaLayerDataSprite(tile->texture,pos);
                    data.reset(ptr);

                    sf::IntRect textRect(tile->textureRectLeft,tile->textureRectTop,tile->textureRectWidth,tile->textureRectHeigh);
                    if(textRect != sf::IntRect())
                    {
                        ptr->setTextureRect(textRect);
                    }

                    sf::Vector2f textCenter(tile->textureCenterLeft,tile->textureCenterTop);
                    if(textCenter != sf::Vector2f())
                    {
                        ptr->setTextureOrigin(textCenter);
                    }

                    if(tile->layer->type->name == "sprite_ptr")
                    {
                        ptr->setIsPtr(true);
                    }   
                }
                else if(tile->layer->type->name == "entity")
                {
                    sf::Vector2i pos(tile->posX,tile->posY);
                    auto ptr = new MetaLayerDataEntity(tile->texture,pos);
                    data.reset(ptr);

                    sf::IntRect textRect(tile->textureRectLeft,tile->textureRectTop,tile->textureRectWidth,tile->textureRectHeigh);
                    if(textRect != sf::IntRect())
                    {
                        ptr->setTextureRect(textRect);
                    }

                    sf::Vector2f textCenter(tile->textureCenterLeft,tile->textureCenterTop);
                    if(textCenter != sf::Vector2f())
                    {
                        ptr->setTextureOrigin(textCenter);
                    }
                }
                else
                {
                    std::cerr<<"Unknow layer type "<<tile->layer->type->name.getValue()<<std::endl;
                    continue;
                }

                metaLayer->add(data);
            }

            if(metaLayer)
            {
                meta->add(std::move(*metaLayer));
            }


            return meta;
        }

        Map* DatabaseMapLoader::_loadMap()
        {
            geometry::Geometry* geo = geometry::Geometry::factory(_map->geometry->name,_map->scale);
            sf::Vector2i areaSize(_map->areaWidth,_map->areaHeight);

            std::list<MetaLayer> layers;

            {
                LayerModel::pointer_array res;
                LayerModel::query()
                    .filter(_map->getPk(),orm::op::exact,LayerModel::$map)
                    .get(res);

                for(auto& layer : res)
                {
                    layers.emplace_back(layer->zBuffer,layer->type->name,layer->isVisible,layer->isStatic);
                }
            }

            Map* res = new Map(geo,areaSize);

            ResourceManager<sf::Texture,std::string>* textureManager = nullptr; //should not be used on map creation (empty layers only)
            for(MetaLayer& layer : layers)
            {
                if(not layer.addToMap(res,*textureManager,sf::Vector2i(0,0)))
                {
                    std::cerr<<"Impossible to add layer ["<<layer<<"] to map"<<std::endl;
                    delete res;
                    res = nullptr;
                    break;
                }
            }

            return res;
        }
    }
}
