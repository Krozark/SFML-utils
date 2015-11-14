#include <SFML-utils/cegui/DialogBox.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

namespace sfutils
{
    namespace cegui
    {
        void DialogBox::getInt(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,
                               const std::function<void(int)>& ok, const std::function<void()>& cancel)
        {
            CEGUI::Editbox* edit = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Editbox"));
            edit->setSize(CEGUI::USize(cegui_reldim(1.f), CEGUI::UDim(0,30)));
            edit->setValidationString("\\d+");

            DialogBox* box = new DialogBox(parent,title,text,edit);

            box->_addButton("Ok",[&ok,edit](PopupBox& self){
                            ok(std::atoi(edit->getText().c_str()));
                            self.destroy();
            });

            box->_addButton("Close",[&cancel](PopupBox& self){
                            cancel();
                            self.destroy();
            });
        }

        void DialogBox::getDouble(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,
                               const std::function<void(double)>& ok, const std::function<void()>& cancel)
        {
            CEGUI::Editbox* edit = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Editbox"));
            edit->setSize(CEGUI::USize(cegui_reldim(1.f), CEGUI::UDim(0,30)));
            edit->setValidationString("\\d+(\\.\\d*)?");

            DialogBox* box = new DialogBox(parent,title,text,edit);

            box->_addButton("Ok",[&ok,edit](PopupBox& self){
                            ok(std::atof(edit->getText().c_str()));
                            self.destroy();
            });

            box->_addButton("Close",[&cancel](PopupBox& self){
                            cancel();
                            self.destroy();
            });
        }

        void DialogBox::getString(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,
                               const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel)
        {
            CEGUI::Editbox* edit = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Editbox"));
            edit->setSize(CEGUI::USize(cegui_reldim(1.f), CEGUI::UDim(0,30)));
            edit->setValidationString(".*");

            DialogBox* box = new DialogBox(parent,title,text,edit);

            box->_addButton("Ok",[&ok,edit](PopupBox& self){
                            ok(edit->getText().c_str());
                            self.destroy();
            });

            box->_addButton("Close",[&cancel](PopupBox& self){
                            cancel();
                            self.destroy();
            });
        }

        void DialogBox::getItem(CEGUI::GUIContext* parent,const std::string title,const std::string& text,const std::list<std::string>& choices,
                               const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel)
        {
            CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Listbox"));
            list->setSize(CEGUI::USize(cegui_reldim(1.f), CEGUI::UDim(1,-95)));
            list->setShowVertScrollbar(false);

            for(const std::string& str : choices)
            {
                CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(str);
                //newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                //newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                newItem->setSelectionBrushImage(GuiManager::getLook()+"/ListboxSelectionBrush");
                newItem->setAutoDeleted(true);

                list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
            }

            if(CEGUI::ListboxItem* item = list->getListboxItemFromIndex(0))
            {
                list->setItemSelectState(item, true);
            }

            DialogBox* box = new DialogBox(parent,title,text,list,sf::Vector2u(300,250));

            box->_addButton("Ok",[&ok,list](PopupBox& self){
                            if(CEGUI::ListboxItem* item = list->getFirstSelectedItem())
                            {
                                ok(item->getText().c_str());
                            }
                            else
                            {
                                ok("");
                            }
                            self.destroy();
            });

            box->_addButton("Close",[&cancel](PopupBox& self){
                            cancel();
                            self.destroy();
            });
        }

        void DialogBox::message(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,const std::function<void()>& ok, const std::function<void()>& cancel)
        {

            PopupBox* dial = new PopupBox(parent,title,sf::Vector2u(300,250));

            CEGUI::MultiLineEditbox* box = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/MultiLineEditbox"));

            box->setText(text);

            box->setReadOnly(true);
            box->setWordWrapping(true);

            dial->_setData(box);

            dial->_addButton("Ok",[](PopupBox& self){
                             self.destroy();
            });
            dial->_addButton("Close",[](PopupBox& self){
                             self.destroy();
                             });
            dial->setModalState(true);
        }


        ////////////// Private ///////////////
        DialogBox::DialogBox(CEGUI::GUIContext* parent,const std::string& title,const std::string& text,CEGUI::Window* object, const sf::Vector2u& size) :
            PopupBox(parent,title,size),
            _layout(nullptr)
        {
            _layout = CEGUI::WindowManager::getSingleton().createWindow("VerticalLayoutContainer");
            _layout->setSize(CEGUI::USize(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));

            _box = CEGUI::WindowManager::getSingletonPtr()->createWindow( "TaharezLook/MultiLineEditbox");
            _box->setSize(CEGUI::USize(cegui_reldim(1.f), CEGUI::UDim(0,60)));
            _box->setText(text);
            static_cast<CEGUI::MultiLineEditbox*>(_box)->setReadOnly(true);
            static_cast<CEGUI::MultiLineEditbox*>(_box)->setWordWrapping(true);
            _layout->addChild(_box);

            _layout->addChild(object);

            _setData(_layout);
            

            setModalState(true);
        }
    }
}
