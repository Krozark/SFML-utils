#ifndef SFUTILS_GEOMETRY_BASETILE_HPP
#define SFUTILS_GEOMETRY_BASETILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        template<typename T>
        struct BaseTile
        {
            static const sf::ConvexShape& getShape() {return T::_shape;};
            protected:
                static sf::ConvexShape _shape;
        };

        #define SFML_UTILS_BASE_TILE_INIT(klass) \
        template <> sf::ConvexShape BaseTile<klass>::_shape = sf::ConvexShape();
        
        template<typename T>
        struct _BaseSquare : public BaseTile<T>
        {
            static sf::Vector2i round(float x,float y)
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


            static sf::IntRect getTextureRect(int x,int y,float scale)
            {
                sf::Vector2f pos = T::mapCoordsToPixel(x,y,scale);
                sf::IntRect res(pos.x,
                                pos.y,
                                T::width * scale,
                                T::height * scale);
                return res;
            }

            static int distance(int x1,int y1, int x2,int y2)
            {
                float x = x1 - x2;
                x = x*x;

                float y = y1 - y2;
                y = y*y;

                return std::ceil(sqrt(x + y));
            }
        };

        template<typename T>
        struct BaseSquare : public _BaseSquare<T>
        {
            static constexpr float height = 2;
            static constexpr float width = height;

            protected:
                static void init()
                {
                    T::_shape.setPointCount(4);
                    T::_shape.setPoint(0,sf::Vector2f(0,0));
                    T::_shape.setPoint(1,sf::Vector2f(0,T::height));
                    T::_shape.setPoint(2,sf::Vector2f(T::height,T::height));
                    T::_shape.setPoint(3,sf::Vector2f(T::height,0));

                    T::_shape.setOrigin(T::height/2.0,T::height/2.0);
                }

                static struct _Initiatiser {
                    _Initiatiser(){
                        T::init();
                    };
                } _initiatiser_;
        };
        #define SFML_UTILS_BASE_SQUARE_INIT(klass) \
        SFML_UTILS_BASE_TILE_INIT(klass);\
        template <> BaseSquare<klass>::_Initiatiser BaseSquare<klass>::_initiatiser_ = BaseSquare<klass>::_Initiatiser();

        template<typename T>
        struct BaseSquareIso : public _BaseSquare<T>
        {
            static constexpr float height = 1;
            static constexpr float width = 2;
            
            protected:
                static void init()
                {
                    T::_shape.setPointCount(4);
                    T::_shape.setPoint(0,sf::Vector2f(T::width/2,0));
                    T::_shape.setPoint(1,sf::Vector2f(T::width,T::height/2.0));
                    T::_shape.setPoint(2,sf::Vector2f(T::width/2.0,T::height));
                    T::_shape.setPoint(3,sf::Vector2f(0,T::height/2.0));

                    T::_shape.setOrigin(T::width/2.0,T::height/2.0);
                }
                static struct _Initiatiser {
                    _Initiatiser(){
                        T::init();
                    };
                } _initiatiser_;
        };

        #define SFML_UTILS_BASE_SQUARE_ISO_INIT(klass) \
        SFML_UTILS_BASE_TILE_INIT(klass);\
        template <> BaseSquareIso<klass>::_Initiatiser BaseSquareIso<klass>::_initiatiser_ = BaseSquareIso<klass>::_Initiatiser();
    }
}
#endif
