#include <SFML-utils/map/geometry/GeometrySquare.hpp>

namespace sfutils
{
    namespace geometry
    {
        GeometrySquare::GeometrySquare(float scale) : 
            GeometrySquareBase(scale)
        {
        }

        GeometrySquare::~GeometrySquare()
        {
        }

        sf::Vector2f GeometrySquare::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            return sf::Vector2f(coord.x * _scale * _width,
                                coord.y * _scale * _height);
        }

        sf::Vector2i GeometrySquare::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            return round(sf::Vector2f(pos.x/_scale / _width,
                                pos.y/_scale / _height));
        }
   }
}
