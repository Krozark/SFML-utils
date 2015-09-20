#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

//https://bitbucket.org/lucebac/cegui/src/ea8f8c814a4d5dbaa56344218659eb68ce173961/application_templates/SDL2.cpp?at=application-templates-devel

#include <iostream>

namespace sfutils
{
    namespace editor
    {
        Editor::Editor():
            _window(sf::VideoMode(1600,900),"SFML-utils map editor")
        {
            _window.setFramerateLimit(65);
            _window.setMouseCursorVisible(false);

            cegui::GuiManager::init("media/editor/cegui/","DejaVuSans-10");

            std::cout<<_window.getSize().x<<";"<<_window.getSize().y<<std::endl;

        }

        Editor::~Editor()
        {
        }

        void Editor::run()
        {
            // create (load) the TaharezLook scheme file
            // (this auto-loads the TaharezLook looknfeel and imageset files)
            CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpentFHD.scheme", "schemes");


            CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");
            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpentFHD/Tooltip");


            CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main.layout");
            CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
            
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(_window.getSize().x,_window.getSize().y));

            while(_window.isOpen())
            {
                _processEvents();
                _update();
                _render();

            }
        }

        void Editor::_processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed ) 
                    _window.close();
                else
                    cegui::GuiManager::processEvent(event);
                
            }
        }

        void Editor::_update()
        {
            sf::Time deltaTime = _clock.restart();
            cegui::GuiManager::update(deltaTime);
        }

        void Editor::_render()
        {
            _window.setActive(true);

            _window.clear();

            _window.pushGLStates();
            cegui::GuiManager::render();
            _window.popGLStates();

            
            _window.display();
        }

    }
}
