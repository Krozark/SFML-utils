#ifndef SFUTILS_MAP_JSONSPRITELOADER_HPP
#define SFUTILS_MAP_JSONSPRITELOADER_HPP

namespace utils{
    namespace json {
        class Object;
    }
}

namespace sfutils
{
    namespace map
    {
        class JsonSpriteLoader
        {
            public:
                JsonMapLoader() =  delete;
                JsonMapLoader(const JsonMapLoader&) = delete;
                JsonMapLoader& operator=(const JsonMapLoader&) = delete;

                struct Data
                {
                    sf::Texture* texture;
                    sf::IntRect texRect;
                    sf::Vector2i texCenter;
                };

                //<filename/spriteId, Data>
                static std::unordered_map<std::string,Data> loadSpriteSheet(const std::string& filename);
        };
    }
}
#endif
