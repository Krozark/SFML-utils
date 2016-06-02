#include <SFML-utils/cegui/GuiManager.hpp>

#include <iostream>

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

    //add one line
    {
        CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(console->getChild("ChatBox"));
        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("enter a text, or press F1..F6 key");
        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
        outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
        outputWindow->ensureItemIsVisible(newItem);
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
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F1)
            {
                sfutils::cegui::DialogBox::getInt(root,
                                                  "Type a number",
                                                  "Enter an Integer",
                                                  [](int value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F2)
            {
                sfutils::cegui::DialogBox::getDouble(root,
                                                  "Type a number",
                                                  "Enter a floating point number",
                                                  [](double value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F3)
            {
                sfutils::cegui::DialogBox::getString(root,
                                                  "Type a text",
                                                  "Enter a string",
                                                  [](const std::string& value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F4)
            {
                sfutils::cegui::DialogBox::getItem(root,
                                                  "Choose",
                                                  "Choose an option",
                                                  {"item 1","item 2","another item","#4","#5","#6","#7","#8","#9","#10"},
                                                  [](const std::string& value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F5)
            {
                sfutils::cegui::DialogBox::message(nullptr,
                                                   "This is a message",
                                                   "Lorem ipsum dolor sit amet, consectetur adipiscing elit.Fusce volutpat purus ac elit malesuada, varius vehicula ipsum mattis. Morbi blandit lorem a risus scelerisque vulputate. Vestibulum ligula nulla, efficitur a faucibus ullamcorper, faucibus a lectus. Pellentesque pretium ante ut pretium mattis. Aliquam leo tellus, suscipit non mauris feugiat, rhoncus eleifend ex. Aliquam velit massa, venenatis sed nulla eget, facilisis accumsan magna. Nullam sagittis, risus vitae pharetra varius, est ipsum condimentum ante, vitae rhoncus neque dui a magna. Integer vehicula sagittis massa, non convallis mauris hendrerit in. In semper, mauris nec blandit blandit, nibh risus egestas ipsum, eget cursus enim sapien at eros. Ut nec ante vel risus elementum pulvinar. Integer nibh sem, ullamcorper luctus ex sit amet, finibus efficitur nisi. Mauris libero dui, imperdiet sed mollis eu, mattis non massa. Sed vitae justo vel ante dignissim bibendum ut nec lectus. Duis egestas mollis tincidunt.",
                                                    [](){std::cout<<"Ok"<<std::endl;},
                                                    [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F6)
            {
                sfutils::cegui::DialogBox::getStringAndItem(root,
                                                  "Text + Choose",
                                                  "Type a text + Choose an option",
                                                  {"item 1","item 2","another item","#4","#5","#6","#7","#8","#9","#10"},
                                                  [](const std::string& text,const std::string& item){std::cout<<"Ok: "<<text<<" item : "<<item<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
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
