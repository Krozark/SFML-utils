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
        class VMap : public sf::Drawable
        {
            public:
                VMap(const VMap&) = delete;
                VMap& operator=(const VMap&) = delete;

                VMap(const utils::json::Object& root,float size);
                virtual ~VMap();


            protected:
                std::string name;
                std::vector<VLayer*> _layers;
                void sortLayers();
                const float tile_size;
                
                ResourceManager<sf::Texture,std::string> _textures;
                
            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };

        VMap* createMapFromFile(const std::string& filename);
    }
}
#endif
