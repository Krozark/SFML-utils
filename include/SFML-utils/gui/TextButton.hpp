#ifndef SMFL_UTILS_GUI_TEXTBUTTON_HPP
#define SMFL_UTILS_GUI_TEXTBUTTON_HPP

#include <SFML-utils/gui/Button.hpp>
#include <SFML-utils/gui/Label.hpp>


namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A class that represent a Button with some text inside it
         */
        class TextButton : public Button
        {
            public:
                TextButton(const TextButton&) = delete;
                TextButton& operator=(const TextButton&) = delete;

                /**
                 * \brief constructor
                 * \param text Text to dispaly
                 * default gui font is use as text font (Configuration::default_fonts.get(Configuration::Gui))
                 * \param parent Parent widget
                 */
                explicit TextButton(const std::string& text,Widget* parent=nullptr);

                /**
                 * \brief constructor
                 * \param text Text to dispaly
                 * \param font font to use
                 * \param parent Parent widget
                 */
                explicit TextButton(const std::string& text,sf::Font& font,Widget* parent=nullptr);

                virtual ~TextButton();

                /**
                 * \brief change the text
                 * \param text new text
                 */
                void setText(const std::string& text);

                /**
                 * \brief change the character size
                 * \param size new size
                 */
                void setCharacterSize(unsigned int size);

                /**
                 * \brief Change the text color
                 * \param color new color
                 */
                void setTextColor(const sf::Color& color);

                /**
                 * \brief change the fill color
                 * \param color new color
                 */
                void setFillColor(const sf::Color& color);

                /**
                 * \brief change the outline color
                 * \param color new color
                 */
                void setOutlineColor(const sf::Color& color);

                /**
                 * \brief change the outline thickness
                 * \param thickness new thickness
                 */
                void setOutlineThickness(float thickness);

            protected:
                virtual sf::Vector2f getSize()const override;


            private:
                sf::RectangleShape _shape;
                Label _label;

                void updateShape()override;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                sf::Color _fillColor;
                sf::Color _outlineColor;

                virtual void onMouseEntered()override;
                virtual void onMouseLeft()override;

        };
    }
}
#endif
