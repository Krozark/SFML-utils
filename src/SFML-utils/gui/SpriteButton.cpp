#include <SFML-utils/gui/SpriteButton.hpp>

#include <SFML-utils/gui/Configuration.hpp>

namespace sfutils
{
    namespace gui
    {
        
        SpriteButton::SpriteButton(const sf::Texture& tex,Widget* parent) : Button(parent), _sprite(tex)
        {
            _color = _sprite.getColor();
            updateShape();
        }

        SpriteButton::~SpriteButton()
        {
        }

        void SpriteButton::setTexture(const sf::Texture& texture,bool resetRect)
        {
            _sprite.setTexture(texture,resetRect);
            updateShape();
        }

        void SpriteButton::setColor(const sf::Color& color)
        {
            _color = color;
            _sprite.setColor(color);
        }

        sf::Vector2f SpriteButton::getSize()const
        {
            sf::FloatRect rect = _sprite.getGlobalBounds();
            return sf::Vector2f(rect.width,rect.height);
        }

        void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform.translate(_position);
            target.draw(_sprite,states);
        }

        void SpriteButton::onMouseEntered()
        {
            const float light = Configuration::Colors::lighting;

            _sprite.setColor(sf::Color(_color.r*light,
                                          _color.b*light,
                                          _color.b*light));
        }

        void SpriteButton::onMouseLeft()
        {
            _sprite.setColor(_color);
        }
    }
}
