#include <SFML-utils/cegui/PopupBox.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <cassert>

namespace sfutils
{
    namespace cegui
    {
        
        PopupBox::PopupBox(CEGUI::GUIContext* context,const std::string& title,const sf::Vector2u& size) :
            _parent(context),
            _root(nullptr),
            _mainLayout(nullptr),
            _data(nullptr),
            _buttonLayout(nullptr)
        {
            if(_parent == nullptr)
            {
                _parent = &CEGUI::System::getSingleton().getDefaultGUIContext();
            }

            _root =  CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/FrameWindow");
            _parent->getRootWindow()->addChild(_root);

            //main layout
            _mainLayout = CEGUI::WindowManager::getSingleton().createWindow("VerticalLayoutContainer");
            _root->addChild(_mainLayout);

            _setTitle(title);
            _setSize(size);

            //remove close button
            _root->setProperty("CloseButtonEnabled","false");
        }

        PopupBox::~PopupBox()
        {
            CEGUI::WindowManager::getSingleton().destroyWindow(_root);
        }

        void PopupBox::show()
        {
            assert(_root);
            _root->show();
        }

        void PopupBox::hide()
        {
            assert(_root);
            _root->hide();
        }

        void PopupBox::destroy()
        {
            delete this;
        }

        void PopupBox::setModalState(bool state)
        {
            _root->setModalState(true);
        }

        //////////////////// Protected ///////////////////////
        
        void PopupBox::_setTitle(const std::string& title)
        {
            assert(_root);
            _root->setText(title);
        }

        void PopupBox::_setData(CEGUI::Window* data)
        {
            if(_data)
            {
                _data->destroy();
            }
            _data = data;

            _data->setSize(CEGUI::USize(CEGUI::UDim(1,0),CEGUI::UDim(1,-35)));
            _mainLayout->addChild(_data);
        }

        void PopupBox::_setSize(const sf::Vector2u& size)
        {
            assert(_root);

            _root->setMinSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
            _root->setSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
        }

        void PopupBox::_addButton(const std::string& label,const Callback& callback)
        {
            if(_buttonLayout == nullptr)
            {
                _buttonLayout = CEGUI::WindowManager::getSingleton().createWindow("HorizontalLayoutContainer");
                _buttonLayout->setSize(CEGUI::USize(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
                _buttonLayout->setProperty("HorizontalAlignment","Right");
                _mainLayout->addChild(_buttonLayout);
            }

            CEGUI::Window* btn =  CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Button");
            btn->setText(label);
            btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                                CEGUI::Event::Subscriber([this,callback](const CEGUI::EventArgs& e){
                                                         callback(*this);
                                                         return true;
                                                         }));

            _buttonLayout->addChild(btn);

        }

    }
}

