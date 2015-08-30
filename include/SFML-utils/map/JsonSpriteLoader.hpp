#ifndef SFUTILS_MAP_JSONSPRITELOADER_HPP
#define SFUTILS_MAP_JSONSPRITELOADER_HPP

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Rect.hpp>

namespace sfutils
{
    namespace map
    {
        class JsonSpriteLoader
        {
            public:
                JsonSpriteLoader(const JsonSpriteLoader&) = delete;
                JsonSpriteLoader& operator=(const JsonSpriteLoader&) = delete;
                JsonSpriteLoader() = delete;

                static std::unordered_map<std::string,sf::IntRect> parse(const std::string& filename);

            protected:

            private:
        };
    }
}
#endif
