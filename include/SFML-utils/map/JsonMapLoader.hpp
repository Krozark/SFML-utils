#ifndef SFUTILS_MAP_JSONMAPLOADER_HPP
#define SFUTILS_MAP_JSONMAPLOADER_HPP

#include <SFML-utils/map/VMapLoader.hpp>

namespace sfutils
{
    namespace map
    {
        class JsonMapLoader : public VMapLoader
        {
            public:
                JsonMapLoader(const JsonMapLoader&) = delete;
                JsonMapLoader& operator=(const JsonMapLoader&) = delete;

                JsonMapLoader(const std::string& mapDirectory);
                virtual VMap* createMap() override;

            protected:
                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y) override;

                std::string _mapDir;
        };
    }
}
#endif
