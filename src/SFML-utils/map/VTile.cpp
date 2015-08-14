#include <SFML-utils/map/VTile.hpp>

namespace sfutils
{
    namespace map
    {
        VTile::VTile()
        {
        }

        VTile::~VTile()
        {
        }

        void VTile::setFillColor(const sf::Color& color)
        {
            _shape.setFillColor(color);
        }

        void VTile::setPosition(float x,float y)
        {
            _shape.setPosition(x,y);
        }

        void VTile::setPosition(const sf::Vector2f& pos)
        {
            _shape.setPosition(pos);
        }

        sf::Vector2f VTile::getPosition()const
        {
            return _shape.getPosition();
        }

        void VTile::setTexture(const sf::Texture *texture,bool resetRect)
        {
            _shape.setTexture(texture,resetRect);
        }

        void VTile::setTextureRect(const sf::IntRect& rect)
        {
            _shape.setTextureRect(rect);
        }

        sf::FloatRect VTile::getGlobalBounds()const
        {
            return _shape.getGlobalBounds();
        }

        sf::FloatRect VTile::getLocalBounds()const
        {
            return _shape.getLocalBounds();
        }
        
        void VTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(_shape,states);
        }
    }
}
