
namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        Tile<GEOMETRY>::Tile(int pos_x,int pos_y,float scale)
        {
            _shape = GEOMETRY::getShape();

            _shape.setOutlineColor(sf::Color(128,128,128,100));
            _shape.setOutlineThickness(2.f/scale);

            _shape.setScale(scale,scale);

            setCoords(pos_x,pos_y);
        }

        template<typename GEOMETRY>
        Tile<GEOMETRY>::~Tile()
        {
        }

        template<typename GEOMETRY>
        inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(float x,float y,float scale)
        {
            return GEOMETRY::mapPixelToCoords(x,y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(const sf::Vector2f& pos,float scale)
        {
            return GEOMETRY::mapPixelToCoords(pos.x,pos.y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(int x,int y,float scale)
        {
            return GEOMETRY::mapCoordsToPixel(x,y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(const sf::Vector2i& pos,float scale)
        {
            return GEOMETRY::mapCoordsToPixel(pos.x,pos.y,scale);
        }



        template<typename GEOMETRY>
        inline void Tile<GEOMETRY>::setCoords(int x,int y)
        {
            sf::Vector2f pos = mapCoordsToPixel(x,y,_shape.getScale().x);
            _shape.setPosition(pos);
        }
    }
}
