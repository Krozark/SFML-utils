#ifndef SFUTILS_MAP_MAPMANAGER_HPP
#define SFUTILS_MAP_MAPMANAGER_HPP

#include <memory>

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

                MapManager(const std::shared_ptr<VMapLoader>& maploader);
                VMap* getMap()const;

                bool loadArea(int x,int y);
                bool unloadArea(int x,int y);

            private:
                std::shared_ptr<VMapLoader> _mapLoader;
                VMap* _map;
        };
    }
}
#endif
