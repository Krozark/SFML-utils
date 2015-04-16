#include <SFML-utils/map/tileShapes/SquareIso.hpp>

namespace sfutils
{
    namespace geometry
    {
        SFML_UTILS_BASE_SQUARE_ISO_INIT(SquareIso);

        sf::Vector2f SquareIso::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f((X-Y)* width/2 * scale,
                                (X+Y)* height/2 * scale);

            //change the rotation
            /*return sf::Vector2f((X+Y)* width/2 * scale,
                                (-X+Y)* height/2 * scale);*/
        }

        sf::Vector2i SquareIso::mapPixelToCoords(float X,float Y,float scale)
        {

            return round((X/width + Y/height)/ scale,
                         (-X/width + Y/height)/scale);

            //change the rotation
            /*return round((X/width - Y/height)/scale,
                         (X/width + Y/height) / scale);*/
        }
        
    }
}
