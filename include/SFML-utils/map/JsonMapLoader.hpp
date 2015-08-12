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

                virtual bool addArea(int y,int y,VMap* map) override;


            protected:
                virtual MetaArea _loadArea(int x,int y) override;
                std::string _mapDir;
        };
    }
}
#endif
