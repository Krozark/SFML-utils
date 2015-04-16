#ifndef SFUTILS_GEOMETRY_SQUARE_HPP
#define SFUTILS_GEOMETRY_SQUARE_HPP

#include <SFML-utils/map/tileShapes/BaseTile.hpp>

namespace sfutils
{
    namespace geometry
    {
        struct Square : BaseSquare<Square>
        {
            static sf::Vector2f mapCoordsToPixel(int x,int y,float scale);
            static sf::Vector2i mapPixelToCoords(float x,float y,float scale);
        };
    }
}
#endif
