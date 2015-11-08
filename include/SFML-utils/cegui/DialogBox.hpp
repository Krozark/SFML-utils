#ifndef SFUTILS_CEGUI_DIALOGBOX_HPP
#define SFUTILS_CEGUI_DIALOGBOX_HPP

#include <string>
#include <functional>

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

                DialogBox(CEGUI::GUIContext& parent,const std::string& text,const std::string& title = "");

                virtual ~DialogBox();


                void setTitle(const std::string& title);

                void setText(const std::string& text);

                void setSize(int x,int y);

                void addButton(const std::string& label,const std::function<void(DialogBox& self)>& callback);

                void show();

                void hide();

            protected:
                CEGUI::GUIContext& _parent;

            private:
                CEGUI::Window* _root;
        };
    }
}
#endif
