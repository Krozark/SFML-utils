#ifndef SFUTILS_CEGUI_DIALOGBOX_HPP
#define SFUTILS_CEGUI_DIALOGBOX_HPP

#include <SFML-utils/cegui/PopupBox.hpp>

#include <list>
#include <string>

namespace sfutils
{
    namespace cegui
    {
        class DialogBox : public PopupBox
        {
            public:
                static void getInt(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,const std::function<void(int)>& ok, const std::function<void()>& cancel);

                static void getDouble(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,const std::function<void(double)>& ok, const std::function<void()>& cancel);

                static void getString(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel);

                static void getItem(CEGUI::GUIContext* parent,const std::string title,const std::string& text,const std::list<std::string>& choices,const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel);

            private:
                DialogBox(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,CEGUI::Window* object,const sf::Vector2u& size={300,150});

                CEGUI::Window* _layout;
                CEGUI::Window* _box;
        };
    }
}
#endif
