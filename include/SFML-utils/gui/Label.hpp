#ifndef SMFL_UTILS_GUI_LABEL_HPP
#define SMFL_UTILS_GUI_LABEL_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A class to display text as zidget
         */
        class Label : virtual public Widget
        {
            public:
                Label(const Label&) = delete;
                Label& operator=(const Label&) = delete;

                /**
                 * \brief constructor
                 * \param text Text to dispaly
                 * default gui font is use as text font (Configuration::default_fonts.get(Configuration::Gui))
                 * \param parent Parent widget
                 */
                explicit Label(const std::string& text,Widget* parent=nullptr);

                /**
                 * \brief constructor
                 * \param text Text to dispaly
                 * \param font font to use
                 * \param parent Parent widget
                 */
                explicit Label(const std::string& text,sf::Font& font,Widget* parent=nullptr);

                virtual ~Label();

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
                 * \return the character size
                 */
                unsigned int getCharacterSize()const;

                /**
                 * \brief Change the text color
                 * \param color new color
                 */
                void setTextColor(const sf::Color& color);

            protected:
                friend class TextButton;
                virtual sf::Vector2f getSize()const override;

            private:
                sf::Text _text;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
