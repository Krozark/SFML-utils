#ifndef SFUTILS_GEOMETRY_SQUARESTAGGERED_HPP
#define SFUTILS_GEOMETRY_SQUARESTAGGERED_HPP

#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        class GeometrySquareStaggered : public GeometrySquareBase
        {
            public:
                GeometrySquareStaggered(float scale);
                virtual ~GeometrySquareStaggered();

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const override;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const override;

        };
    }
}
#endif
