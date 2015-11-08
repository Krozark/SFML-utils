#include <SFML-utils/cegui/GuiManager.hpp>

#include <SFML-utils/cegui/DialogBox.hpp>

int main(int argc,char* argv[])
{
    //initialize SFML window
    sf::RenderWindow window(sf::VideoMode(1200,800),"cegui");
    window.setFramerateLimit(65);
    window.setMouseCursorVisible(false);

    //initialize cegui
    sfutils::cegui::GuiManager::init("media/cegui/","TaharezLook","DejaVuSans-10");

    //set the cursor image
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

    //load a layout
    CEGUI::Window* root = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Static");
    root->setProperty("FrameEnabled", "false");
    //root->setSize(CEGUI::USize(CEGUI::UDim(0,window.getSize().x), CEGUI::UDim(0,window.getSize().y)));
    root->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
    root->setProperty("BackgroundColours", "tl:FFBFBFBF tr:FFBFBFBF bl:FFBFBFBF br:FFBFBFBF");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

    CEGUI::Window* console = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Console.layout");
    root->addChild(console);

    //resize the cegui window
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(window.getSize().x,window.getSize().y));


    //event handlers
    {
        auto f = [console](const CEGUI::EventArgs& e) -> bool{
            CEGUI::String msg = console->getChild("EditBox")->getText();
            if(msg.size() > 0)
            {
                CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(console->getChild("ChatBox"));
                CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(msg);
                newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
	            outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                outputWindow->ensureItemIsVisible(newItem);
                console->getChild("EditBox")->setText("");
            }
            return true;
        };
        //send button
        console->getChild("SendButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(f));
        //return key pressed
        console->getChild("EditBox")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,CEGUI::Event::Subscriber(f));

        //close button
        console->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
                             CEGUI::Event::Subscriber([&window](const CEGUI::EventArgs& e){
                                window.close();
                                return true;
                             }));
    }

    //main loop
    sf::Clock clock;
    while(window.isOpen())
    {
        //events
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed )
            { 
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {
                sfutils::cegui::DialogBox* dial = new sfutils::cegui::DialogBox(CEGUI::System::getSingleton().getDefaultGUIContext(),"Dialog","text");
            }
            else
            {
                sfutils::cegui::GuiManager::processEvent(event);
            }

        }
        
        //update
        sf::Time deltaTime = clock.restart();
        sfutils::cegui::GuiManager::update(deltaTime);

        //render
        window.setActive(true);
        window.clear();

        window.pushGLStates();
        sfutils::cegui::GuiManager::render();
        window.popGLStates();

        window.display();

    }

    return 0;
}
