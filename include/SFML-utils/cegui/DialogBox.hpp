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
                static int getInt(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text);

                static bool getDouble(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text);

                static std::string getString(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text);

                static std::string getItem(CEGUI::GUIContext* parent,bool& ok,const std::string title,const std::string& text,const std::list<std::string>& choices);

            private:
                DialogBox(CEGUI::GUIContext* parent,const std::string& title,const std::string& text, bool& ok,const sf::Vector2u& size={350,250});

                void _addText(const std::string& text);
                
                CEGUI::Window* _layout;
        };
    }
}
#endif
