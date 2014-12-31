#ifndef SFUTILS_GEOMETRY_HEXAISO_HPP
#define SFUTILS_GEOMETRY_HEXAISO_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace geometry
    {
        struct HexaIso
        {
            static const sf::ConvexShape& getShape();
            static sf::Vector2f mapCoordsToPixel(int x,int y);
            static sf::Vector2i mapPixelToCoords(int x,int y);
            static sf::IntRect getTextureRect(int x,int y,float scale);


            private:
                static sf::ConvexShape _shape;
                static void init();
            
                static struct __Initiatiser {
                    __Initiatiser(){
                        HexaIso::init();
                    };
                } __initiatiser__;
        };
    }
}
#endif
