#ifndef SFUTILS_GEOMETRY_SQUARE_HPP
#define SFUTILS_GEOMETRY_SQUARE_HPP

#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        class GeometrySquare : public GeometrySquareBase
        {
            public:
                GeometrySquare(float scale);
                virtual ~GeometrySquare();

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const override;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const override;
        };
    }
}
#endif
