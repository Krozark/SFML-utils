#include <SFML-utils/map/geometry/GeometrySquareStaggered.hpp>

namespace sfutils
{
    namespace geometry
    {
        GeometrySquareStaggered::GeometrySquareStaggered(float scale) :
            GeometrySquareBase(scale)
        {
        }

        GeometrySquareStaggered::~GeometrySquareStaggered()
        {
        }

        sf::Vector2f GeometrySquareStaggered::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            static float sw = _scale * _width;
            static float sh = _scale * _height;

            return sf::Vector2f((coord.x + (coord.y&1)/2.0 ) * sw,
                                coord.y*sh);
        }

        sf::Vector2i GeometrySquareStaggered::mapPixelToCoords(const sf::Vector2f& coord) const
        {
            float y = coord.y/_scale/_height;

            if(y>=0)
                y+=0.5;
            else
                y-=0.5;

            float x = coord.x/_scale/_width - ((static_cast<int>(y)&1)?0.5:0);

            if(x>=0)
                x+=0.5;
            else
                x-=0.5;


            return sf::Vector2i(x,y);
        }

    }
}
