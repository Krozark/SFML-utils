#include <SFML-utils/map/geometry/GeometrySquareIso.hpp>

namespace sfutils
{
    namespace geometry
    {
        GeometrySquareIso::GeometrySquareIso(float scale) :
            GeometrySquareIsoBase(scale)
        {
        }

        GeometrySquareIso::~GeometrySquareIso()
        {
        }

        sf::Vector2f GeometrySquareIso::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            const float sw = _scale * _width/2.0;
            const float sh = _scale * _height/2.0;

            return sf::Vector2f((coord.x-coord.y) * sw,
                                (coord.x + coord.y) * sh);
        }

        sf::Vector2i GeometrySquareIso::mapPixelToCoords(const sf::Vector2f& coord) const
        {
            return round(sf::Vector2f(
                                      (coord.x/_width + coord.y/_height)/ _scale,
                                      (-coord.x/_width + coord.y/_height)/_scale)
                         );
        }
        
    }
}
