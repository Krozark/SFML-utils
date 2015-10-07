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

        GeometryHexa::GeometryHexa(float scale) : Geometry(scale,WIDTH,HEIGHT)
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

        sf::IntRect GeometryHexa::getTextureRect(const sf::Vector2i& pos) const
        {
            sf::Vector2f p = mapCoordsToPixel(pos);
            sf::IntRect res(p.x,
                          p.y,
                          _width * _scale,
                          _height * _scale);
            return res;
        }

        sf::Vector2i GeometryHexa::round(const sf::Vector2f& pos) const
        {
            const float z = -pos.y - pos.x;

            float rx = std::round(pos.x);
            float ry = std::round(pos.y);
            float rz = std::round(z);

            const float diff_x = std::abs(rx - pos.x);
            const float diff_y = std::abs(ry - pos.y);
            const float diff_z = std::abs(rz - z);

            if(diff_x > diff_y and diff_x > diff_z)
                rx = -ry-rz;
            else if (diff_y > diff_z)
                ry = -rx-rz;

            return sf::Vector2i(rx,ry);
        }

        int GeometryHexa::distance(const sf::Vector2i& p1, const sf::Vector2i& p2) const
        {
            return (std::abs(p1.x - p2.x)
                    + std::abs(p1.y - p2.y)
                    + std::abs((-p1.x - p1.y) - (-p2.x - p2.y))) / 2;
        }
    }
}
