#include <SFML-utils/map/MapManager.hpp>
#include <cassert>

#include <iostream>


namespace sfutils
{
    namespace map
    {
        
        MapManager::MapManager(const std::shared_ptr<VMapLoader>& loader) : 
            _mapLoader(loader),
            _map(nullptr)

        {
            assert(loader);
            _map = _mapLoader->_createMap();
            assert(_map);
        }

        VMap* MapManager::getMap()const
        {
            return _map;
        }

        bool MapManager::loadArea(int x,int y)
        {
            std::pair<int,int> key(x,y);

            bool res = _areas.count(key);
            if(res)
            {
                std::cerr<<"area ("<<x<<":"<<y<<") already loaded"<<std::endl;
                return false;
            }

            std::unique_ptr<MetaArea> area = _mapLoader->_loadArea(x,y,_map);
            if(area)
            {
                res = area->addToMap(_map,_textureManager);
                if(res)
                    _areas.emplace(key,std::move(area));
            }
            return res;
        }

        bool MapManager::unloadArea(int x,int y)
        {
            std::pair<int,int> key(x,y);

            auto find = _areas.find(key);
            if(find == _areas.end())
            {
                std::cerr<<"area ("<<x<<":"<<y<<") not already loaded"<<std::endl;
                return false;
            }

            if(not find->second->removeFromMap(_map))
                return false;

            _areas.erase(find);
            return true;
        }
    }
}
