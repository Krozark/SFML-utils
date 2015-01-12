#ifndef SFUTILS_MAP_VMAP_HPP
#define SFUTILS_MAP_VMAP_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <string>
#include <utils/json/Driver.hpp>

#include <SFML-utils/core/ResourceManager.hpp>

namespace sfutils
{
    namespace map
    {
        class VMap
        {
            public:
                VMap(const VMap&) = delete;
                VMap& operator=(const VMap&) = delete;

                VMap(float size);
                virtual ~VMap();

                virtual void loadFromJson(const utils::json::Object& root) = 0;
                bool loadFromFile(const std::string& filename);

                void addLayer(VLayer* layer,bool sort=true);
                void removeLayer(VLayer* layer);
                void removeLayer(size_t index);

                size_t size()const;
                VLayer* at(size_t index)const;


            protected:
                void sortLayers();
                const float tile_size;
                
                ResourceManager<sf::Texture,std::string> _textures;
                
            private:
                friend class MapViewer;
                void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const;
                std::vector<VLayer*> _layers;
        };

        VMap* createMapFromFile(const std::string& filename);
    }
}
#endif
