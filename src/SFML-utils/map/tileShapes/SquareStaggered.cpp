#include <SFML-utils/map/tileShapes/SquareStaggered.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        sf::ConvexShape SquareStaggered::_shape;
        SquareStaggered::__Initiatiser SquareStaggered::__initiatiser__;

        const float height = 2;

        const sf::ConvexShape& SquareStaggered::getShape()
        {
            return _shape;
        }

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

        sf::Vector2i SquareStaggered::round(float x, float y)
        {
            if(x>=0)
                x+=0.5;
            else
                x-=0.5;

            if(y>=0)
                y+=0.5;
            else
                y-=0.5;
            return sf::Vector2i(x,y);
        }

        sf::IntRect SquareStaggered::getTextureRect(int x,int y,float scale)
        {
            sf::Vector2f pos = mapCoordsToPixel(x,y,scale);
            sf::IntRect res(pos.x,
                          pos.y,
                          height * scale,
                          height * scale);
            return res;
        }

        int SquareStaggered::distance(int x1,int y1, int x2,int y2)
        {
            float x = x1 - x2;
            x = x*x;

            float y = y1 - y2;
            y = y*y;

                return ceil(sqrt(x + y));
          }

        void SquareStaggered::init()
        {
            _shape.setPointCount(4);
            _shape.setPoint(0,sf::Vector2f(0,0));
            _shape.setPoint(1,sf::Vector2f(0,height));
            _shape.setPoint(2,sf::Vector2f(height,height));
            _shape.setPoint(3,sf::Vector2f(height,0));

            _shape.setOrigin(height/2,height/2);
        }
        
    }
}
