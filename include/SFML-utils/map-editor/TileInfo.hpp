#ifndef SFUTILS_EDITOR_TileInfo_HPP
#define SFUTILS_EDITOR_TileInfo_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

#include <SFML-utils/map/Models.hpp>

namespace sfutils
{
    namespace editor
    {
        class TileInfo
        {
            public:
                using FuncType = std::function<void(sfutils::map::LayerModel::pointer&, const TileInfo&)>;

                TileInfo(int z,const sf::Vector2i& coord,FuncType func);

                int z;
                sf::Vector2i coord;
                sf::IntRect textureRect;
                sf::Vector2f textureCenterCoord;

                std::string texture;
                std::string type;
                FuncType func;

                

                bool operator<(const TileInfo& other)const;
                bool operator==(const TileInfo& other)const;
            
        };
    }
}

#endif
