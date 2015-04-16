#include <SFML-utils/map/tileShapes/SquareStaggered.hpp>

namespace sfutils
{
    namespace geometry
    {
        SFML_UTILS_BASE_SQUARE_INIT(SquareStaggered);

        sf::Vector2f SquareStaggered::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f((X + (Y&1)/2.0 )*scale*height,
                                Y*scale*height);
        }

        sf::Vector2i SquareStaggered::mapPixelToCoords(float X,float Y,float scale)
        {
            float y = Y/scale/height;

            if(y>=0)
                y+=0.5;
            else
                y-=0.5;

            float x = X/scale/height - ((static_cast<int>(y)&1)?0.5:0);

            if(x>=0)
                x+=0.5;
            else
                x-=0.5;


            return sf::Vector2i(x,y);
        }

    }
}
