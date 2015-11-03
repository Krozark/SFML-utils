#ifndef SFUTILS_VMAPLOADER_HPP
#define SFUTILS_VMAPLOADER_HPP

#include <memory>

#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/MapMetaData.hpp>


namespace sfutils
{
    namespace map
    {
        class Map;
        class VMapLoader
        {
            public:
                virtual ~VMapLoader();


            private:
                friend class MapManager;

                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y,Map* const map) = 0;
                virtual Map* _loadMap() = 0;


        };
    }
}

#endif
