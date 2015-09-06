#include <SFML-utils/cegui/GuiManager.hpp>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800,600),"cegui");

    window.setFramerateLimit(65);
    window.setMouseCursorVisible(false);

    sfutils::cegui::GuiManager::init("media/datafiles/","DejaVuSans-10");

    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme", "schemes");


    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");


    CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("TabControlDemo.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(window.getSize().x,window.getSize().y));

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
