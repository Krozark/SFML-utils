#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace geometry
    {
        Geometry::Geometry(float scale,float width, float height) :
            _scale(scale),
            _width(width),
            _height(height)
        {
        }

        Geometry::~Geometry()
        {
        }

        const sf::ConvexShape& Geometry::getShape() const
        {
            return _shape;
        }

        float Geometry::getScale()const
        {
            return _scale;
        }

        //////////////// _GeometrySquareBase_helper ////////////////

        _GeometrySquareBase_helper::_GeometrySquareBase_helper(float scale,float width, float height) : Geometry(scale,width,height)
        {
        }

        _GeometrySquareBase_helper::~_GeometrySquareBase_helper()
        {
        }


        sf::IntRect _GeometrySquareBase_helper::getTextureRect(const sf::Vector2i& pos) const
        {
            sf::Vector2f p = mapCoordsToPixel(pos);
            return sf::IntRect(p.x,
                               p.y,
                               _width * _scale,
                               _height * _scale);
        }

        sf::Vector2i _GeometrySquareBase_helper::round(const sf::Vector2f& pos) const
        {
            sf::Vector2f res = pos;
            if(res.x>=0)
                res.x+=0.5;
            else
                res.x-=0.5;

            if(res.y>=0)
                res.y+=0.5;
            else
                res.y-=0.5;

            return sf::Vector2i(res.x,res.y);
        }

        int _GeometrySquareBase_helper::distance(const sf::Vector2i& p1, const sf::Vector2i& p2) const
        {
            float x = p1.x - p2.x;
            x = x*x;

            float y = p1.y - p2.y;
            y = y*y;

            return std::ceil(sqrt(x + y));
        }


        ///////////////////// GeometrySquareBase //////////////////
        
        GeometrySquareBase::GeometrySquareBase(float scale) : 
            _GeometrySquareBase_helper(scale,2,2)
        {
            _shape.setPointCount(4);

            _shape.setPoint(0,sf::Vector2f(0,0));
            _shape.setPoint(1,sf::Vector2f(0,_height));
            _shape.setPoint(2,sf::Vector2f(_width,_height));
            _shape.setPoint(3,sf::Vector2f(_width,0));

            _shape.setOrigin(_width/2.0,_height/2.0);

            _shape.setScale(scale,scale);
        }

        GeometrySquareBase::~GeometrySquareBase()
        {
        }

        ///////////////// GeometrySquareIsoBase /////////////////
        
        GeometrySquareIsoBase::GeometrySquareIsoBase(float scale) : 
            _GeometrySquareBase_helper(scale,2,1)
        {

            _shape.setPointCount(4);
            _shape.setPoint(0,sf::Vector2f(_width/2,0));
            _shape.setPoint(1,sf::Vector2f(_width,_height/2.0));
            _shape.setPoint(2,sf::Vector2f(_width/2.0,_height));
            _shape.setPoint(3,sf::Vector2f(0,_height/2.0));

            _shape.setOrigin(_width/2.0,_height/2.0);

            _shape.setScale(scale,scale);
        }

        GeometrySquareIsoBase::~GeometrySquareIsoBase()
        {
        }

    }
}
