#include <SFML-utils/map/DatabaseMapLoader.hpp>

namespace sfutils
{
    namespace map
    {
        DatabaseMapLoader::DatabaseMapLoader(MapModel::type_ptr& map) : 
            _map(map)
        {
        }

        DatabaseMapLoader::~DatabaseMapLoader()
        {
        }

        std::unique_ptr<MetaArea> DatabaseMapLoader::_loadArea(int x,int y,Map* const map)
        {
            return nullptr;
        }

        Map* DatabaseMapLoader::_loadMap()
        {
            geometry::Geometry* geo = geometry::Geometry::factory(_map->geometry->name,_map->scale);
            sf::Vector2i areaSize(_map->areaWidth,_map->areaHeight);

            std::list<MetaLayer> layers;

            for(auto& layer : _map->layers.all())
            {
                layers.emplace_back(layer->zBuffer,layer->type->name,layer->isStatic);
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
