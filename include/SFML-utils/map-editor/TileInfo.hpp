#ifndef SFUTILS_EDITOR_TileInfo_HPP
#define SFUTILS_EDITOR_TileInfo_HPP

#include <string>

#include <SFML/Graphics.hpp>


namespace sfutils
{
    namespace editor
    {
        class TileInfo
        {
            public:

                TileInfo(int z,const sf::Vector2i& coord);

                int z;
                sf::Vector2i coord;
                sf::IntRect textureRect;
                std::string texture;

                bool operator<(const TileInfo& other)const;
                bool operator==(const TileInfo& other)const;
            
        };
    }
}

#endif
