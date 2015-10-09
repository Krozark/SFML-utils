#include <SFML-utils/map/geometry/GeometryHexa.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        const float SQRT_3_2 = sqrt(3)/2.0;

        const float HEIGHT = 2;
        const float WIDTH = HEIGHT * SQRT_3_2;
        const float DELTA_X = WIDTH;
        const float DELTA_Y = HEIGHT*3.0/4.0;

        GeometryHexa::GeometryHexa(float scale) : GeometryHexaBase(scale,WIDTH,HEIGHT)
        {
            _shape.setPointCount(6);

            _shape.setPoint(0,sf::Vector2f(_width/2,0));
            _shape.setPoint(1,sf::Vector2f(_width,_height*0.25));
            _shape.setPoint(2,sf::Vector2f(_width,_height*0.75));
            _shape.setPoint(3,sf::Vector2f(_width/2,_height));
            _shape.setPoint(4,sf::Vector2f(0,_height*0.75));
            _shape.setPoint(5,sf::Vector2f(0,_height*0.25));
            
            _shape.setOrigin(_width/2,_height/2);

            _shape.setScale(_scale,_scale);
        }

        GeometryHexa::~GeometryHexa()
        {
        }

        sf::Vector2f GeometryHexa::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            return sf::Vector2f(_scale * DELTA_X * (coord.x + coord.y/2.0),
                                _scale * DELTA_Y * coord.y);
        }

        sf::Vector2i GeometryHexa::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            const float x = (pos.x / DELTA_X - pos.y/(2*DELTA_Y)) / _scale;
            const float y = (pos.y / DELTA_Y) / _scale;
            return round(sf::Vector2f(x,y));
        }

    }
}
