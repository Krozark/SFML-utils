#ifndef SFUTILS_GEOMETRY_HEXA_HPP
#define SFUTILS_GEOMETRY_HEXA_HPP

#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        class GeometryHexa : public GeometryHexaBase
        {
            public:
                GeometryHexa(float scale);
                virtual ~GeometryHexa();

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const override;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const override;
        };
    }
}
#endif
