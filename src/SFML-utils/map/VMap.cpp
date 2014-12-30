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

        void VMap::sortLayers()
        {
            for(VLayer* layer : _layers)
                layer->sort();
        }

        void VMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for(VLayer* layer : _layers)
                target.draw(*layer,states);
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
