#include <SFML-utils/map/MapManager.hpp>


namespace sfutils
{
    namespace map
    {
        
        MapManager::MapManager(VMapLoader* loader) : _mapLoader(loader)
        {
        }

        bool MapManager::loadArea(int x,int y)
        {
            MetaArea meta_area = _mapLoader->_loadArea(x,y);
            return false;
        }
    }
}
