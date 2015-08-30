#ifndef SFUTILS_VMAPLOADER_HPP
#define SFUTILS_VMAPLOADER_HPP

#include <memory>

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


            private:
                friend class MapManager;

                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y,VMap* const map) = 0;
                virtual VMap* _createMap() = 0;


        };
    }
}

#endif
