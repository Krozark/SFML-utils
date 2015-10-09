#ifndef SFUTILS_GEOMETRY_SQUAREISOSTAGGERED_HPP
#define SFUTILS_GEOMETRY_SQUAREISOSTAGGERED_HPP

#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        class GeometrySquareIsoStaggered : public GeometrySquareIsoBase
        {
            public:
                GeometrySquareIsoStaggered(float scale);
                virtual ~GeometrySquareIsoStaggered();

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const override;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const override;
        };

    }
}
#endif
