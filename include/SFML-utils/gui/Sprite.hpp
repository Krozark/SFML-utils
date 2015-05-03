#ifndef SFUTILS_GUI_SPRITE_HPP
#define SFUTILS_GUI_SPRITE_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A class to display a sprite as widget
         */
        class Sprite : virtual public Widget
        {
            public:
                Sprite(const Sprite&) = delete;
                Sprite& operator=(const Sprite&) = delete;

                /**
                 * \brief Constructor
                 * \param tex Texture of the image to use
                 * \param parent parent Widget
                 */
                explicit Sprite(const sf::Texture& tex,Widget* parent=nullptr);

                virtual ~Sprite();

                /**
                 * \brief Change the texture of the sprite
                 * \param texture the new texture to use
                 * \param resetRect reset the texture rect
                 */
                void setTexture(const sf::Texture& texture,bool resetRect=false);

                /**
                 * \brief Change the texture rect to use
                 * \param rectangle the rect to use
                 */
                void setTextureRect(const sf::IntRect& rectangle);

                /**
                 * \brief change the color mask
                 * \param color the color mask to use
                 */
                virtual void setColor(const sf::Color& color);

            protected:
                virtual sf::Vector2f getSize()const override;

            private:
                friend class SpriteButton;
                sf::Sprite _sprite;
                sf::Color _color;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
