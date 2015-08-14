#ifndef SFUTILS_VMAPLOADER_HPP
#define SFUTILS_VMAPLOADER_HPP

#include <memory>

#include <SFML-utils/core/ResourceManager.hpp>

#include <SFML-utils/map/VMap.hpp>
#include <SFML-utils/map/MapMetaData.hpp>


namespace sfutils
{
    namespace map
    {
        class VMap;
        class VMapLoader
        {
            public:
                virtual ~VMapLoader();

                bool loadArea(int x,int y,VMap* map);
                virtual VMap* createMap() = 0;

            protected:
                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y) = 0;
                ResourceManager<sf::Texture,std::string> _textures;

        };
    }
}

#endif
