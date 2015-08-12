#include <SFML-utils/map/MapManager.hpp>
#include <cassert>


namespace sfutils
{
    namespace map
    {
        
        MapManager::MapManager(const std::shared_ptr<VMapLoader>& loader) : 
            _mapLoader(loader),
            _map(nullptr)

        {
            assert(loader);
            _map = _mapLoader->createMap();
            assert(_map);
        }

        VMap* MapManager::getMap()const
        {
            return _map;
        }

        bool MapManager::loadArea(int x,int y)
        {
            return _mapLoader->loadArea(x,y,_map);
        }
    }
}
