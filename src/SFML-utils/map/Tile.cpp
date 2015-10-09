#include <SFML-utils/map/Tile.hpp>
#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace map
    {
        Tile::Tile(const geometry::Geometry& geometry,const sf::Vector2i& pos)
        {
            _shape = geometry.getShape();

            _shape.setOutlineColor(sf::Color(128,128,128,100));
            _shape.setOutlineThickness(2.f/geometry.getScale());

            sf::Vector2f p = geometry.mapCoordsToPixel(pos);
            _shape.setPosition(p);
        }

        Tile::~Tile()
        {
        }

        void Tile::setFillColor(const sf::Color& color)
        {
            _shape.setFillColor(color);
        }

        void Tile::setPosition(float x,float y)
        {
            _shape.setPosition(x,y);
        }

        void Tile::setPosition(const sf::Vector2f& pos)
        {
            _shape.setPosition(pos);
        }

        sf::Vector2f Tile::getPosition()const
        {
            return _shape.getPosition();
        }

        void Tile::setTexture(const sf::Texture *texture,bool resetRect)
        {
            _shape.setTexture(texture,resetRect);
        }

        void Tile::setTextureRect(const sf::IntRect& rect)
        {
            _shape.setTextureRect(rect);
        }

        sf::FloatRect Tile::getGlobalBounds()const
        {
            return _shape.getGlobalBounds();
        }

        sf::FloatRect Tile::getLocalBounds()const
        {
            return _shape.getLocalBounds();
        }
        
        void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(_shape,states);
        }
    }
}
