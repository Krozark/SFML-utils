#ifndef SFUTILS_CEGUI_POPUPBOX_HPP
#define SFUTILS_CEGUI_POPUPBOX_HPP

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
        class PopupBox
        {
            public:
                PopupBox(const PopupBox&) = delete;
                PopupBox& operator=(const PopupBox&) = delete;

                using Callback = const std::function<void(PopupBox& self)>;

                PopupBox(CEGUI::GUIContext* parent,const std::string& title,const sf::Vector2u& size={350,250});

                virtual ~PopupBox();

                void show();

                void hide();

                void destroy();                

                void setModalState(bool state);
                
            protected:
                void _setTitle(const std::string& title);

                void _setSize(const sf::Vector2u& size);

                void _setData(CEGUI::Window* data);

                void _addButton(const std::string& label,const Callback& callback);

            private:
                CEGUI::GUIContext* _parent;

                CEGUI::Window* _root;
                CEGUI::Window* _mainLayout;
                CEGUI::Window* _data;
                CEGUI::Window* _buttonLayout;
        };
    }
}
#endif
