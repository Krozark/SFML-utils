#ifndef SFUTILS_CEGUI_DIALOGBOX_HPP
#define SFUTILS_CEGUI_DIALOGBOX_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

namespace CEGUI
{
    class GUIContext;
    class Window;
}

namespace sfutils
{
    namespace cegui
    {
        class DialogBox
        {
            public:
                DialogBox(const DialogBox&) = delete;
                DialogBox& operator=(const DialogBox&) = delete;

                DialogBox(CEGUI::GUIContext& parent,const std::string& title,const std::string& text = "",const sf::Vector2u& size={500,300});

                virtual ~DialogBox();

                void setTitle(const std::string& title);

                void setText(const std::string& text);

                void setSize(const sf::Vector2u& size);

                void addButton(const std::string& label,const std::function<void(DialogBox& self)>& callback);

                void show();

                void hide();

                void destroy();

            protected:
                CEGUI::GUIContext& _parent;

            private:
                CEGUI::Window* _root;
                CEGUI::Window* _text;
                CEGUI::Window* _buttonLayout;
        };
    }
}
#endif
