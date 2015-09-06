#include <iostream>

#include <SFML-utils/cegui/GuiManager.hpp>

int main(int argc,char* argv[])
{
    //initialize SFML window
    sf::RenderWindow window(sf::VideoMode(1200,800),"cegui");
    window.setFramerateLimit(65);
    window.setMouseCursorVisible(false);

    //initialize cegui
    sfutils::cegui::GuiManager::init("media/datafiles/","DejaVuSans-10");

    //load a scheme
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme", "schemes");

    //set the cursor image
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

    //load a layout
    CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Console.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

    //resize the cegui window
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(window.getSize().x,window.getSize().y));

    //event handlers
    {
        auto f = [root](const CEGUI::EventArgs& e) -> bool{
            std::cout<<"sendButtonPressed"<<std::endl;
            CEGUI::String msg = root->getChild("EditBox")->getText();
            if(msg.size() > 0)
            {
                CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(root->getChild("ChatBox"));
                CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(msg);
                newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
	            outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                outputWindow->ensureItemIsVisible(newItem);
                root->getChild("EditBox")->setText("");
            }
            return true;
        };
        //send button
        root->getChild("SendButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(f));
        //return key pressed
        root->getChild("EditBox")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,CEGUI::Event::Subscriber(f));

        //close button
        root->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
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
                window.close();
            else
                sfutils::cegui::GuiManager::processEvent(event);
        }
        
        //update
        sf::Time deltaTime = clock.restart();
        sfutils::cegui::GuiManager::update(deltaTime);

        //render
        window.clear();

        window.pushGLStates();
        sfutils::cegui::GuiManager::render();
        window.popGLStates();

        window.display();

    }

    return 0;
}
