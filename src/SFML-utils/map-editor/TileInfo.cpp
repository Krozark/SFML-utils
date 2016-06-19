#include <SFML-utils/map-editor/TileInfo.hpp>

namespace sfutils
{
    namespace editor
    {
        TileInfo::TileInfo(int p_z,const sf::Vector2i& p_coord,const std::string& p_textureFile,const sf::IntRect& p_textRect,const sf::Vector2f& p_textureCenterCoord):
            z(p_z),
            coord(p_coord),
            texture(p_textureFile),
            textureRect(p_textRect),
            textureCenterCoord(p_textureCenterCoord)
        {
        }


        bool TileInfo::operator<(const TileInfo& other)const
        {
            if(z == other.z)
            {
                if(coord.x == other.coord.x)
                {
                    return coord.y < other.coord.y;
                }
                return coord.x < other.coord.x;
            }
            return z < other.z;

        }

        bool TileInfo::operator==(const TileInfo& other)const
        {
            return (z == other.z) && (coord == other.coord);
        }
    }
}

