#include <SFML-utils/map/geometry/GeometryHexaIso.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        const float PI = 3.14159265;

        const float SIN_15 = sin(15*PI/180);
        const float SIN_45 = sin(45*PI/180);
        const float SIN_75 = sin(75*PI/180);

        const float WIDTH = SIN_15 + SIN_45 + SIN_75;
        const float DELTA_X = SIN_45 - SIN_15;
        const float DELTA_Y = SIN_75 + SIN_45;


        GeometryHexaIso::GeometryHexaIso(float scale) : GeometryHexaBase(scale,WIDTH,WIDTH/2)
        {
            _shape.setPointCount(6);

            _shape.setPoint(0,sf::Vector2f(0,(SIN_15 + SIN_75)/2));
            _shape.setPoint(1,sf::Vector2f(SIN_15,SIN_15/2));
            _shape.setPoint(2,sf::Vector2f(SIN_15 + SIN_75,0));
            _shape.setPoint(3,sf::Vector2f(SIN_15 + SIN_75 + SIN_45,SIN_45/2));
            _shape.setPoint(4,sf::Vector2f(SIN_75 + SIN_45,(SIN_75 + SIN_45)/2));
            _shape.setPoint(5,sf::Vector2f(SIN_45,(SIN_15 + SIN_75 + SIN_45)/2));

            _shape.setOrigin(_width/2,_height/2);

            _shape.setScale(_scale,_scale);
        }

        GeometryHexaIso::~GeometryHexaIso()
        {
        }

        sf::Vector2f GeometryHexaIso::mapCoordsToPixel(const sf::Vector2i& coord) const
        {
            return sf::Vector2f((coord.y * DELTA_X + coord.x * DELTA_Y) * _scale,
                                (coord.y * DELTA_Y/2 + coord.x * DELTA_X/2) * _scale);
        }

        sf::Vector2i GeometryHexaIso::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            const float d_x = DELTA_X * _scale;
            const float d_y = DELTA_Y * _scale;

            const float y = (-pos.x * d_x + 2 * pos.y * d_y) / (d_y * d_y - d_x * d_x);
            const float x = -(y * d_x - pos.x) / d_y;

            return GeometryHexaIso::round(sf::Vector2f(x,y));
        }
    }
}
