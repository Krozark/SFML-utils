#include <SFML-utils/cegui/DialogBox.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <cassert>

namespace sfutils
{
    namespace cegui
    {
        
        DialogBox::DialogBox(CEGUI::GUIContext& context,const std::string& text,const std::string& title,const sf::Vector2u& size) :
            _parent(context),
            _root(nullptr)
        {
            _root =  CEGUI::WindowManager::getSingleton().createWindow(GuiManager::getLook()+"/FrameWindow");
            context.getRootWindow()->addChild(_root);

            setText(text);
            setTitle(title);
            setSize(size);

            //remove close button
            static_cast<CEGUI::DefaultWindow*>(_root)->setProperty("CloseButtonEnabled","false");
        }

        DialogBox::~DialogBox()
        {
        }

        void DialogBox::setTitle(const std::string& title)
        {
            assert(_root);
            _root->setText(title);
        }

        void DialogBox::setText(const std::string& text)
        {
            assert(_root);
        }

        void DialogBox::setSize(const sf::Vector2u& size)
        {
            assert(_root);

            _root->setMinSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
            _root->setSize(CEGUI::USize(CEGUI::UDim(0,size.x),CEGUI::UDim(0,size.y)));
        }

        void DialogBox::addButton(const std::string& label,const std::function<void(DialogBox& self)>& callback)
        {
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
    }
}
