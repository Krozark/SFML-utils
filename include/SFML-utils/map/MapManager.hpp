#ifndef SFUTILS_MAP_MAPMANAGER_HPP
#define SFUTILS_MAP_MAPMANAGER_HPP

#include <SFML-utils/map/VMapLoader.hpp>

namespace sfutils
{
    namespace map
    {
        class MapManager
        {
            public:
                MapManager(const MapManager&) = delete;
                MapManager& operator=(const MapManager&) = delete;

                MapManager(VMapLoader* maploader);

                bool loadArea(int x,int y);
            private:
                VMapLoader* _mapLoader;
        };
    }
}
#endif
