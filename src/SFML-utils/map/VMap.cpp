#include <SFML-utils/map/VMap.hpp>

#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/HexaIso.hpp>

#include <algorithm>

namespace sfutils
{
    namespace map
    {
        VMap::VMap(float size) : tile_size(size)
        {
        }

        VMap::~VMap()
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                delete(_layers[i]);
        }

        bool VMap::loadFromFile(const std::string& filename)
        {
            utils::json::Value* value = utils::json::Driver::parse_file(filename);
            if(value)
            {
                utils::json::Object& root = *value;

                loadFromJson(root);
            }
            return value != nullptr;
        }


        void VMap::addLayer(VLayer* layer,bool sort)
        {
            _layers.emplace_back(layer);
            if(sort)
                sortLayers();
        }

        void VMap::sortLayers()
        {
            std::sort(_layers.begin(),_layers.end(),[](const VLayer* a, const VLayer* b)->bool{
                      return a->z() < b->z();
                    });

            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->sort();
        }


        void VMap::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const
        {
            sf::FloatRect delta_viewport(viewport.left - tile_size,
                                        viewport.top - tile_size,
                                        viewport.width + tile_size*2,
                                        viewport.height + tile_size*2); 
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->draw(target,states,delta_viewport);
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
                    res = new Map<geometry::HexaIso>(size);
                    res->loadFromJson(root);
                }
                delete value;
            }
            return res;
        }
    }
}
