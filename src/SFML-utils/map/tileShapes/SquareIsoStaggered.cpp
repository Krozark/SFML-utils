#include <SFML-utils/map/tileShapes/SquareIsoStaggered.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        sf::ConvexShape SquareIsoStaggered::_shape;
        SquareIsoStaggered::__Initiatiser SquareIsoStaggered::__initiatiser__;

        const float height = 1;
        const float width = 2;

        const sf::ConvexShape& SquareIsoStaggered::getShape()
        {
            return _shape;
        }

        sf::Vector2f SquareIsoStaggered::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f((X-Y + (Y&1)/2.0)* width/2 * scale,
                                (X+Y + (Y&1)/2.0)* height/2 * scale);

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

        sf::Vector2i SquareIsoStaggered::round(float x, float y)
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

        sf::IntRect SquareIsoStaggered::getTextureRect(int x,int y,float scale)
        {
            sf::Vector2f pos = mapCoordsToPixel(x,y,scale);
            sf::IntRect res(pos.x,
                          pos.y,
                          width * scale,
                          height * scale);
            return res;
        }

        int SquareIsoStaggered::distance(int x1,int y1, int x2,int y2)
        {
            float x = x1 - x2;
            x = x*x;

            float y = y1 - y2;
            y = y*y;

                return ceil(sqrt(x + y));
          }

        void SquareIsoStaggered::init()
        {
            _shape.setPointCount(4);
            _shape.setPoint(0,sf::Vector2f(width/2,0));
            _shape.setPoint(1,sf::Vector2f(width,height/2));
            _shape.setPoint(2,sf::Vector2f(width/2,height));
            _shape.setPoint(3,sf::Vector2f(0,height/2));

            _shape.setOrigin(width/2,height/2);
        }
        
    }
}
