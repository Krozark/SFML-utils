#ifndef SFUTILS_GEOMETRY_SQUAREISOSTAGGERED_HPP
#define SFUTILS_GEOMETRY_SQUAREISOSTAGGERED_HPP

#include <SFML-utils/map/tileShapes/BaseTile.hpp>

namespace sfutils
{
    namespace geometry
    {
        struct SquareIsoStaggered : public BaseSquareIso<SquareIsoStaggered>
        {
            static sf::Vector2f mapCoordsToPixel(int x,int y,float scale);
            static sf::Vector2i mapPixelToCoords(float x,float y,float scale);

        };

    }
}
#endif
