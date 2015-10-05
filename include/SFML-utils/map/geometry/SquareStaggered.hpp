#ifndef SFUTILS_GEOMETRY_SQUARESTAGGERED_HPP
#define SFUTILS_GEOMETRY_SQUARESTAGGERED_HPP

#include <SFML-utils/map/tileShapes/BaseTile.hpp>

namespace sfutils
{
    namespace geometry
    {
        struct SquareStaggered : public BaseSquare<SquareStaggered>
        {
            static sf::Vector2f mapCoordsToPixel(int x,int y,float scale);
            static sf::Vector2i mapPixelToCoords(float x,float y,float scale);

        };
    }
}
#endif
