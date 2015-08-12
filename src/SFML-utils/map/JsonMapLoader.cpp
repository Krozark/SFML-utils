#include <SFML-utils/map/JsonMapLoader.hpp>

namespace sfutils
{
    namespace map
    {
        JsonMapLoader::JsonMapLoader(const std::string& mapDirectory) : _mapDir(mapDirectory)
        {
        }

        VMap* JsonMapLoader::createMap()
        {
            //#error TODO
            return nullptr;
        }

        MetaArea JsonMapLoader::_loadArea(int x,int y)
        {
            //#error TODO
            return MetaArea(x,y,"ERROR");
        }
    }
}
