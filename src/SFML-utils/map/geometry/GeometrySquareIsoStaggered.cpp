#include <SFML-utils/map/geometry/GeometrySquareIsoStaggered.hpp>

namespace sfutils
{
    namespace geometry
    {
        GeometrySquareIsoStaggered::GeometrySquareIsoStaggered(float scale) :
            GeometrySquareIsoBase(scale)
        {
        }

        GeometrySquareIsoStaggered::~GeometrySquareIsoStaggered()
        {
        }

        sf::Vector2f GeometrySquareIsoStaggered::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            static float sw = _scale * _width/2.0;
            static float sh = _scale * _height/2.0;

            return sf::Vector2f((coord.x-coord.y + (coord.y&1)/2.0) * sw,
                                (coord.x+coord.y + (coord.y&1)/2.0) * sh);

        }

        sf::Vector2i GeometrySquareIsoStaggered::mapPixelToCoords(const sf::Vector2f& coord) const
        {

            float y = (-coord.x/_width + coord.y/_height)/_scale;
            if(y>=0)
                y+=0.5;
            else
                y-=0.5;

            float x = (coord.x/_width + coord.y/_height)/ _scale  - ((static_cast<int>(y)&1)?0.5:0);
            if(x>=0)
                x+=0.5;
            else
                x-=0.5;

            return sf::Vector2i(x,y);

        }
    }
}
