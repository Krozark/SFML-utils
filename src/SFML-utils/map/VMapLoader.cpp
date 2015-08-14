#include <SFML-utils/map/VMapLoader.hpp>

#include <iostream>


namespace sfutils
{
    namespace map
    {

        VMapLoader::~VMapLoader()
        {
        }

        bool VMapLoader::loadArea(int x,int y,VMap* const map)
        {
            bool res = false;
            std::unique_ptr<MetaArea> area = _loadArea(x,y,map);
            if(area)
            {
                res = area->addToMap(map,_textureManager);
            }
            std::cout<<res<<std::endl;
            return res;
        }
    }
}
