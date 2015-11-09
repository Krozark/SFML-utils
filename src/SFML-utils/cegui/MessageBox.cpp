#include <SFML-utils/cegui/MessageBox.hpp>

#include <CEGUI/CEGUI.h>

namespace sfutils
{
    namespace cegui
    {
        
        MessageBox::MessageBox(CEGUI::GUIContext& context,const std::string& title,const std::string& text,const sf::Vector2u& size) :
            PopupBox(context,title,size)
        {
            CEGUI::MultiLineEditbox* box = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::WindowManager::getSingletonPtr()->createWindow( "TaharezLook/MultiLineEditbox"));

            box->setText(text);

            box->setReadOnly(true);
            box->setWordWrapping(true);

            _setData(box);

            _addButton("Ok",[](PopupBox& self){self.destroy();});
            _addButton("Close",[](PopupBox& self){self.destroy();});
        }
    }
}
