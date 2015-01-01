#include <SFML-utils/map/VMap.hpp>

#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/HexaIso.hpp>

namespace sfutils
{
    namespace map
    {
        VMap::VMap(const utils::json::Object& root,float size) : tile_size(size)
        {
            name = root["name"].as_string();
        }

        VMap::~VMap()
        {
            for(VLayer* layer : _layers)
                delete(layer);
        }

        void VMap::addLayer(VLayer* layer)
        {
            _layers.emplace_back(layer);
        }

        void VMap::sortLayers()
        {
            for(VLayer* layer : _layers)
                layer->sort();
        }

        void VMap::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const
        {
            sf::FloatRect delta_viewport(viewport.left - tile_size,
                                        viewport.top - tile_size,
                                        viewport.width + tile_size*2,
                                        viewport.height + tile_size*2); 
            for(VLayer* layer : _layers)
                layer->draw(target,states,delta_viewport);
        }

        
        VMap* createMapFromFile(const std::string& filename)
        {
            VMap* res = nullptr;
            utils::json::Value* value = utils::json::Driver::parse_file(filename);
            if(value)
            {
                utils::json::Object& root = *value;
                utils::json::Object& geometry = root["geometry"];
                std::string geometry_name = geometry["name"].as_string();
                float size = geometry["size"].as_float();

                if(geometry_name == "HexaIso")
                {
                    res = new Map<geometry::HexaIso>(root,size);
                }
                delete value;
            }
            return res;
        }
    }
}
