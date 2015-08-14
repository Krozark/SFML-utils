#include <SFML-utils/map/VMapLoader.hpp>


namespace sfutils
{
    namespace map
    {

        VMapLoader::~VMapLoader()
        {
        }

        bool VMapLoader::loadArea(int x,int y,VMap* map)
        {
            bool res = false;
            std::unique_ptr<MetaArea> area = _loadArea(x,y);
            if(area)
            {
                res = area->addToMap(map);
            }
            return res;
        }
    }
}
