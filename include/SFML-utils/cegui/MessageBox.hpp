#ifndef SFUTILS_CEGUI_MESSAGEBOX_HPP
#define SFUTILS_CEGUI_MESSAGEBOX_HPP

#include <SFML-utils/cegui/PopupBox.hpp>

namespace sfutils
{
    namespace cegui
    {
        class MessageBox : public PopupBox
        {
            public:
                MessageBox(CEGUI::GUIContext* parent,const std::string& title,const std::string& text = "",const sf::Vector2u& size={350,250});

                void setText(const std::string& text);
        };
    }
}
#endif
