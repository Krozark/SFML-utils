#ifndef SFUTILS_GUI_SPRITEBUTTON_HPP
#define SFUTILS_GUI_SPRITEBUTTON_HPP

#include <SFML-utils/gui/Button.hpp>

namespace sfutils
{
    namespace gui
    {
        class SpriteButton : public Button
        {
            public:
                SpriteButton(const SpriteButton&) = delete;
                SpriteButton& operator=(const SpriteButton&) = delete;

                SpriteButton(const sf::Texture& tex,Widget* parent=nullptr);
                ~SpriteButton();

                void setTexture(const sf::Texture& texture,bool resetRect=false);
                void setColor(const sf::Color& color);

                virtual sf::Vector2f getSize()const override;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            private:
                sf::Sprite _sprite;
                sf::Color _color;

                virtual void onMouseEntered()override;
                virtual void onMouseLeft()override;
        };
    }
}
#endif
