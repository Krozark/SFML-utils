#ifndef SFUTILS_VMAPLOADER_HPP
#define SFUTILS_VMAPLOADER_HPP

#include <SFML-utils/map/VMap.hpp>
#include <SFML-utils/map/MapMetaData.hpp>


namespace sfutils
{
    namespace map
    {
        class VMapLoader
        {
            public:
                virtual ~VMapLoader();

            protected:
                friend class MapManager;
                virtual MetaArea _loadArea(int x,int y) = 0;

        };
    }
}

#endif
