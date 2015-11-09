#include <SFML-utils/cegui/DialogBox.hpp>

#include <CEGUI/CEGUI.h>

namespace sfutils
{
    namespace cegui
    {
        int DialogBox::getInt(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text)
        {
            DialogBox* box = new DialogBox(parent,title,text,ok);
            ok = false;
            return 0;
        }

        bool DialogBox::getDouble(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text)
        {
            DialogBox* box = new DialogBox(parent,title,text,ok);
            ok = false;
            return 0;
        }

        std::string DialogBox::getString(CEGUI::GUIContext* parent,bool& ok,const std::string& title,const std::string& text)
        {
            DialogBox* box = new DialogBox(parent,title,text,ok);
            ok = false;
            return "";
        }

        std::string DialogBox::getItem(CEGUI::GUIContext* parent,bool& ok,const std::string title,const std::string& text,const std::list<std::string>& choices)
        {
            DialogBox* box = new DialogBox(parent,title,text,ok);
            ok = false;
            return "";
        }

        ////////////// Private ///////////////
        DialogBox::DialogBox(CEGUI::GUIContext* parent,const std::string& title,const std::string& text, bool& ok, const sf::Vector2u& size) :
            PopupBox(parent,title,size),
            _layout(nullptr)
        {
            _layout = CEGUI::WindowManager::getSingleton().createWindow("VerticalLayoutContainer","layout");
            _setData(_layout);

            _addText(text);
            
            _addButton("Ok",[&ok](PopupBox& self){
                       ok = true;
                       self.destroy();
            });

            _addButton("Close",[&ok](PopupBox& self){
                       ok = false;
                       self.destroy();
            });

            setModalState(true);
        }

        void DialogBox::_addText(const std::string& text)
        {
            CEGUI::MultiLineEditbox* box = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::WindowManager::getSingletonPtr()->createWindow( "TaharezLook/MultiLineEditbox"));

            box->setText(text);

            box->setReadOnly(true);
            box->setWordWrapping(true);

            _layout->addChild(box);

        }
    }
}
