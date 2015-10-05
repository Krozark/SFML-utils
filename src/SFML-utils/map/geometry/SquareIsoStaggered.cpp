#include <SFML-utils/map/tileShapes/SquareIsoStaggered.hpp>

namespace sfutils
{
    namespace geometry
    {
        SFML_UTILS_BASE_SQUARE_ISO_INIT(SquareIsoStaggered);

        sf::Vector2f SquareIsoStaggered::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f((X-Y + (Y&1)/2.0)* width/2.0 * scale,
                                (X+Y + (Y&1)/2.0)* height/2.0 * scale);

        }

        sf::Vector2i SquareIsoStaggered::mapPixelToCoords(float X,float Y,float scale)
        {

            float y = (-X/width + Y/height)/scale;
            if(y>=0)
                y+=0.5;
            else
                y-=0.5;

            float x = (X/width + Y/height)/ scale  - ((static_cast<int>(y)&1)?0.5:0);
            if(x>=0)
                x+=0.5;
            else
                x-=0.5;

            return sf::Vector2i(x,y);

        }
    }
}
