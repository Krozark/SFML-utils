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
            static float sh = _scale * _height;
            static float sw = _scale * _width;

            return sf::Vector2f(coord.x*sw,coord.y*sh);
        }

        sf::Vector2i GeometrySquare::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            static float sh = _scale / _height;
            static float sw = _scale / _width;

            return round(sf::Vector2f(pos.x/sw,pos.y/sh));
        }
    }
}
