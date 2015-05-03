#ifndef SFUTILS_GUI_SPRITEBUTTON_HPP
#define SFUTILS_GUI_SPRITEBUTTON_HPP

#include <SFML-utils/gui/Button.hpp>
#include <SFML-utils/gui/Sprite.hpp>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A clicable image
         */
        class SpriteButton : virtual public Widget, public Button, public Sprite
        {
            public:
                SpriteButton(const SpriteButton&) = delete;
                SpriteButton& operator=(const SpriteButton&) = delete;

                /**
                 * \brief Constructor
                 * \param tex Texture of the image to use
                 * \param parent parent Widget
                 */
                explicit SpriteButton(const sf::Texture& tex,Widget* parent=nullptr);
                ~SpriteButton();

                /**
                 * \brief set the color mask
                 * \param colo mask
                 */
                void setColor(const sf::Color& color)override;

            private:
                sf::Color _color;

                virtual void onMouseEntered()override;
                virtual void onMouseLeft()override;

                void updateShape()override;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
