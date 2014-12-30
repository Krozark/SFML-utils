
namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(int x,int y)
        {
            return GEOMETRY::mapPixelToCoords(x,y);
        }

        template<typename GEOMETRY>
        sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(const sf::Vector2i& pos)
        {
            return GEOMETRY::mapPixelToCoords(pos.x,pos.y);
        }

        template<typename GEOMETRY>
        sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(int x,int y)
        {
            return GEOMETRY::mapCoordsToPixel(x,y);
        }

        template<typename GEOMETRY>
        sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(const sf::Vector2i& pos)
        {
            return GEOMETRY::mapCoordsToPixel(pos.x,pos.y);
        }

        template<typename GEOMETRY>
        Tile<GEOMETRY>::Tile(int pos_x,int pos_y)
        {
            _shape = GEOMETRY::getShape();

            _shape.setOutlineColor(sf::Color(0,0,0,175));
            _shape.setOutlineThickness(2);

            setPosition(pos_x,pos_y);
        }

        template<typename GEOMETRY>
        template< typename ...Args>
        void Tile<GEOMETRY>::setFillColor(Args&& ... args)
        {
            _shape.setFillColor(std::forward<Args&>(args)...);
        }

        template<typename GEOMETRY>
        template< typename ...Args>
        void Tile<GEOMETRY>::setPosition(Args&& ... args)
        {
            _shape.setPosition(mapCoordsToPixel(std::forward<Args&>(args)...));
        }

        template<typename GEOMETRY>
        void Tile<GEOMETRY>::setTexture(const sf::Texture *texture,bool resetRect)
        {
            _shape.setTexture(texture,resetRect);
        }

        template<typename GEOMETRY>
        void Tile<GEOMETRY>::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(_shape,states);
        }
    }
}
