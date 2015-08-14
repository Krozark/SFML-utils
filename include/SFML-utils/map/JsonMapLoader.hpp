#ifndef SFUTILS_MAP_JSONMAPLOADER_HPP
#define SFUTILS_MAP_JSONMAPLOADER_HPP

#include <SFML-utils/map/VMapLoader.hpp>

namespace utils{
    namespace json {
        class Object;
    }
}

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
                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y,VMap* const map) override;

                std::string _mapDir;

                static bool _parseLayer(VMap* map,utils::json::Object& root,std::unique_ptr<MetaArea>& meta);
                static std::shared_ptr<MetaLayerData> _createTile(VMap* const map,utils::json::Object& root);
                static std::shared_ptr<MetaLayerData> _createSprite(VMap* const map,utils::json::Object& root,bool isPtr);

        };
    }
}
#endif
