#include <SFML-utils/map/VTile.hpp>
#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace map
    {
        VTile::VTile(const geometry::Geometry& geometry,const sf::Vector2i& pos)
        {
            _shape = geometry.getShape();

            _shape.setOutlineColor(sf::Color(128,128,128,100));
            _shape.setOutlineThickness(2.f/geometry.getScale());

            sf::Vector2f p = geometry.mapCoordsToPixel(pos);
            _shape.setPosition(p);
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
