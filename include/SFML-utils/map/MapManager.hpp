#ifndef SFUTILS_MAP_MAPMANAGER_HPP
#define SFUTILS_MAP_MAPMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <utility>


#include <SFML-utils/map/VMapLoader.hpp>

#include <utils/hash.hpp>

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

                Map* getMap()const;

                bool loadArea(int x,int y);
                bool unloadArea(int x,int y);

            private:
                std::shared_ptr<VMapLoader> _mapLoader;
                std::unordered_map<std::pair<int,int>,std::unique_ptr<MetaArea>> _areas;
                std::unique_ptr<Map> _map;
                ResourceManager<sf::Texture,std::string> _textureManager;
        };
    }
}
#endif
