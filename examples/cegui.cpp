#include <SFML-utils/cegui/GuiManager.hpp>

#include <iostream>

#include <SFML-utils/cegui/DialogBox.hpp>

int main(int argc,char* argv[])
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////// window1  ////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window1(sf::VideoMode(1200,800),"cegui");
    window1.setFramerateLimit(65);
    window1.setMouseCursorVisible(false);



    /////////////// Cegui //////////////
    //initialize cegui
    sfutils::cegui::GuiManager::init("media/cegui/","TaharezLook","DejaVuSans-10");


    /////////// Window 1 cegui context /////////////////
    ///get cegui context
    CEGUI::GUIContext& context1 = CEGUI::System::getSingleton().getDefaultGUIContext();

    //set the cursor image
    context1.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    context1.setDefaultTooltipType("TaharezLook/Tooltip");

    //load a layout
    CEGUI::Window* root1 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Static");
    root1->setProperty("FrameEnabled", "false");
    //root->setSize(CEGUI::USize(CEGUI::UDim(0,window.getSize().x), CEGUI::UDim(0,window.getSize().y)));
    root1->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
    root1->setProperty("BackgroundColours", "tl:FFBFBFBF tr:FFBFBFBF bl:FFBFBFBF br:FFBFBFBF");
    context1.setRootWindow(root1);

    CEGUI::Window* layout1 = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Console.layout");
    root1->addChild(layout1);

    ///////////// CEGUI + Winow 1 ////////////////
    //resize the cegui window
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(window1.getSize().x,window1.getSize().y));


    //event handlers
    {
        auto f = [layout1](const CEGUI::EventArgs& e) -> bool{
            CEGUI::String msg = layout1->getChild("EditBox")->getText();
            if(msg.size() > 0)
            {
                CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(layout1->getChild("ChatBox"));
                CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(msg);
                newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
	            outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                outputWindow->ensureItemIsVisible(newItem);
                layout1->getChild("EditBox")->setText("");
            }
            return true;
        };
        //send button
        layout1->getChild("SendButton")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(f));
        //return key pressed
        layout1->getChild("EditBox")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,CEGUI::Event::Subscriber(f));

        //close button
        layout1->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
                             CEGUI::Event::Subscriber([&window1](const CEGUI::EventArgs& e){
                                window1.close();
                                return true;
                             }));
    }

    //add one line
    {
        CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(layout1->getChild("ChatBox"));
        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("enter a text, or press F1..F6 key");
        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
        outputWindow->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
        outputWindow->ensureItemIsVisible(newItem);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////// Window 2 //////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window2(sf::VideoMode(1200,800),"window 2");
    window2.setFramerateLimit(65);
    window1.setMouseCursorVisible(false);

    /////////// Window 2 cegui context /////////////////
    ///create new cegui context
    CEGUI::GUIContext& context2 = sfutils::cegui::GuiManager::createGUIContext();

    //set the cursor image
    context2.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    context2.setDefaultTooltipType("TaharezLook/Tooltip");

    //load a layout
    CEGUI::Window* root2 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Static");
    root2->setProperty("FrameEnabled", "false");
    root2->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
    root2->setProperty("BackgroundColours", "tl:FFBFBFBF tr:FFBFBFBF bl:FFBFBFBF br:FFBFBFBF");

    context2.setRootWindow(root2);

    CEGUI::Window* layout2 = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Demo8.layout");
    root2->addChild(layout2);




    //main loop
    sf::Clock clock;
    while(window1.isOpen() && window2.isOpen())
    {
        //////////////////////////////////////////////////////////
        //////////////////////// Events //////////////////////////
        //////////////////////////////////////////////////////////

        //////////////// window 1 ////////////
        sf::Event event;
        while(window1.pollEvent(event))
        {
            if(event.type == sf::Event::Closed )
            { 
                window1.close();
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F1)
            {
                sfutils::cegui::DialogBox::getInt(root1,
                                                  "Type a number",
                                                  "Enter an Integer",
                                                  [](int value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F2)
            {
                sfutils::cegui::DialogBox::getDouble(root1,
                                                  "Type a number",
                                                  "Enter a floating point number",
                                                  [](double value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F3)
            {
                sfutils::cegui::DialogBox::getString(root1,
                                                  "Type a text",
                                                  "Enter a string",
                                                  [](const std::string& value){std::cout<<"Ok: "<<value<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F4)
            {
                sfutils::cegui::DialogBox::getItem(root1,
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
                sfutils::cegui::DialogBox::getStringAndItem(root1,
                                                  "Text + Choose",
                                                  "Type a text + Choose an option",
                                                  {"item 1","item 2","another item","#4","#5","#6","#7","#8","#9","#10"},
                                                  [](const std::string& text,const std::string& item){std::cout<<"Ok: "<<text<<" item : "<<item<<std::endl;},
                                                  [](){std::cout<<"Cancel"<<std::endl;});
            }
            else
            {
                sfutils::cegui::GuiManager::processEvent(event,context1);
            }

        }

        /////////// Window 2 //////////////

        while(window2.pollEvent(event))
        {
            if(event.type == sf::Event::Closed )
            { 
                window2.close();
            }
            else
            {
                sfutils::cegui::GuiManager::processEvent(event,context2);
            }
        }
        /////////////////////////////////////////////////
        ///////////////////// update ////////////////////
        /////////////////////////////////////////////////
        
        sf::Time deltaTime = clock.restart();

        //////////////// window 1 ////////////
        sfutils::cegui::GuiManager::update(deltaTime,context1);
        //////////////// window 2 ////////////
        sfutils::cegui::GuiManager::update(deltaTime,context2);
        
        /////////////////////////////////////////////////
        ////////////////// Rendering ///////////////////
        /////////////////////////////////////////////////

        /////////// Window 1 //////////////
        window1.setActive(true);
        window1.clear();

        window1.pushGLStates();
        sfutils::cegui::GuiManager::render(context1);
        window1.popGLStates();

        window1.display();

        //////////////// window 2 ////////////

        window2.setActive(true);
        window2.clear();

        window2.pushGLStates();
        sfutils::cegui::GuiManager::render(context2);
        window2.popGLStates();

        window2.display();

    }

    return 0;
}
