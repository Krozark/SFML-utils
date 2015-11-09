#include <SFML-utils/cegui/DialogBox.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <cassert>

namespace sfutils
{
    namespace cegui
    {
        
        DialogBox::DialogBox(CEGUI::GUIContext& context,const std::string& title,const std::string& text,const sf::Vector2u& size) :
            _parent(context),
            _root(nullptr),
            _text(nullptr)
        {
            _root =  CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/FrameWindow");
            context.getRootWindow()->addChild(_root);

            //main layout
            CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().createWindow("VerticalLayoutContainer","mainlayout");
            _root->addChild(layout);

            {//text
                CEGUI::MultiLineEditbox* box = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::WindowManager::getSingletonPtr()->createWindow( "TaharezLook/MultiLineEditbox"));
                _text = box;

                box->setReadOnly(true);
                box->setWordWrapping(true);

                _text->setSize(CEGUI::USize(CEGUI::UDim(1,0),CEGUI::UDim(1,-35)));
                layout->addChild(_text);
            }

            {//button layout
                _buttonLayout = CEGUI::WindowManager::getSingleton().createWindow("HorizontalLayoutContainer","btnLayout");
                _buttonLayout->setSize(CEGUI::USize(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
                _buttonLayout->setProperty("HorizontalAlignment","Right");
                layout->addChild(_buttonLayout);
            }

            setText(text);
            setTitle(title);
            setSize(size);

            //remove close button
            _root->setProperty("CloseButtonEnabled","false");
            
            addButton("Close",[](DialogBox& self){self.destroy();});
        }

        DialogBox::~DialogBox()
        {
            _root->destroy();
        }

        void DialogBox::setTitle(const std::string& title)
        {
            assert(_root);
            _root->setText(title);
        }

        void DialogBox::setText(const std::string& text)
        {
            assert(_text);
            _text->setText(text);
        }

        void DialogBox::setSize(const sf::Vector2u& size)
        {
            assert(_root);

            _root->setMinSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
            _root->setSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
        }

        void DialogBox::addButton(const std::string& label,const std::function<void(DialogBox& self)>& callback)
        {
            CEGUI::Window* btn =  CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/Button",label);
            btn->setText(label);
            btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                                CEGUI::Event::Subscriber([this,callback](const CEGUI::EventArgs& e){
                                                         callback(*this);
                                                         return true;
                                                         }));

            _buttonLayout->addChild(btn);

        }

        void DialogBox::show()
        {
            assert(_root);
            _root->show();
        }

        void DialogBox::hide()
        {
            assert(_root);
            _root->hide();
        }

        void DialogBox::destroy()
        {
            delete this;
        }
    }
}
