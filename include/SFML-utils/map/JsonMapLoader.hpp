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

            protected:

                std::string _mapDir;

                static bool _parseLayer(Map* map,utils::json::Object& root,std::unique_ptr<MetaArea>& meta);
                static std::shared_ptr<MetaLayerData> _createTile(Map* const map,utils::json::Object& root);
                static std::shared_ptr<MetaLayerData> _createSprite(Map* const map,utils::json::Object& root,bool isPtr);
                static std::shared_ptr<MetaLayerData> _createEntity(Map* const map,utils::json::Object& root);

            private:
                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y,Map* const map) override;
                virtual Map* _createMap() override;

        };
    }
}
#endif
