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
            return _loadArea(x,y).addToMap(map);
        }


    }
}
