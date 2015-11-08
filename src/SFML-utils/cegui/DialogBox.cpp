#include <SFML-utils/cegui/DialogBox.hpp>

namespace sfutils
{
    namespace cegui
    {
        
        DialogBox::DialogBox(CEGUI::GUIContext& context,const std::string& text,const std::string& title) :
            _parent(context)
        {
            setText(text);
            setTitle(title);
        }

        DialogBox::~DialogBox()
        {
        }

        void DialogBox::setTitle(const std::string& title)
        {
        }

        void DialogBox::setText(const std::string& text)
        {
        }

        void DialogBox::setSize(int x,int y)
        {
        }

        void DialogBox::addButton(const std::string& label,const std::function<void(DialogBox& self)>& callback)
        {
        }

        void DialogBox::show()
        {
        }

        void DialogBox::hide()
        {
        }
    }
}
