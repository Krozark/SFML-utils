#ifndef SFUTILS_GEOMETRY_SQUAREISO_HPP
#define SFUTILS_GEOMETRY_SQUAREISO_HPP

#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        class GeometrySquareIso : public GeometrySquareIsoBase
        {
            public:
                GeometrySquareIso(float scale);
                virtual ~GeometrySquareIso();

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const override;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const override;
            
        };
    }
}
#endif
