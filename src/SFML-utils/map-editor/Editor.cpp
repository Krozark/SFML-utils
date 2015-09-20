#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

#include <cassert>
#include <iostream>

namespace sfutils
{
    namespace editor
    {
        Editor::Editor():
            _window(sf::VideoMode(1600,900),"SFML-utils map editor"),
            _root(nullptr)
        {
            _window.setFramerateLimit(65);
            _window.setMouseCursorVisible(false);

            cegui::GuiManager::init("media/editor/cegui/","DejaVuSans-10");
            _createGui();
        }

        Editor::~Editor()
        {
        }

        void Editor::run()
        {
            while(_window.isOpen())
            {
                _processEvents();
                _update();
                _render();

            }
        }

        ////////////////////// PRIVATE ////////////////////
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


        void Editor::_createGui()
        {
            //load skin
            CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpentFHD.scheme", "schemes");
            //set mouse
            CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");
            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpentFHD/Tooltip"); 
            //load main layout
            _root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main.layout");
            CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_root);
            //resize gui to the window size 
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(_window.getSize().x,_window.getSize().y));

            //register events
            _registerMenuBarCallbacks();
            _registerLeftPanelCallbacks();
            _registerMiniMapCallbacks();
            _registerRightPanelCallbacks();
        }


        //Menu
        void Editor::_registerMenuBarCallbacks()
        {
            CEGUI::Window* menuBar = _root->getChild("MenuBar");

            {//file
                CEGUI::Window* menu = menuBar->getChild("File/Menu");
                //open
                CEGUI::Window* btn = menu->getChild("Open");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_file_open();
                });
                //save
                btn = menu->getChild("Save");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_file_save();
                });

            }

            {//edit
                CEGUI::Window* menu = menuBar->getChild("Edit/Menu");

                CEGUI::Window* btn = menu->getChild("Undo");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_edit_undo();
                });

                btn = menu->getChild("Redo");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_edit_redo();
                });
            }

            {//map
                CEGUI::Window* menu = menuBar->getChild("Map/Menu");

                CEGUI::Window* btn = menu->getChild("Resize");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_map_resize();
                });

                btn = menu->getChild("Shape");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_map_shape();
                });

                btn = menu->getChild("Position");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_map_position();
                });
            }
        }
        ////File
        bool Editor::_event_menuBar_file_open()
        {
            std::cout<<"MenuBar/File/Menu/Open clicked"<<std::endl;
            return true;
        }
        bool Editor::_event_menuBar_file_save()
        {
            std::cout<<"MenuBar/File/Menu/Save clicked"<<std::endl;
            return true;
        }

        ////Edit
        bool Editor::_event_menuBar_edit_undo()
        {
            std::cout<<"MenuBar/Edit/Menu/Undo clicked"<<std::endl;
            return true;
        }
        bool Editor::_event_menuBar_edit_redo()
        {
            std::cout<<"MenuBar/Edit/Menu/Redo clicked"<<std::endl;
            return true;
        }

        //Map
        bool Editor::_event_menuBar_map_resize()
        {
            std::cout<<"MenuBar/Map/Menu/Resize clicked"<<std::endl;
            return true;
        }
        bool Editor::_event_menuBar_map_shape()
        {
            std::cout<<"MenuBar/Map/Menu/Shape clicked"<<std::endl;
            return true;
        }
        bool Editor::_event_menuBar_map_position()
        {
            std::cout<<"MenuBar/Map/Menu/Position clicked"<<std::endl;
            return true;
        }

        ////LeftPanel
        void Editor::_registerLeftPanelCallbacks()
        {
            CEGUI::Window* menuBar = _root->getChild("Left");

            {//textures
                CEGUI::Window* box = menuBar->getChild("Textures")->getChildRecursive("Listbox");
                assert(box);

                box->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this](const CEGUI::EventArgs& e){
                    return this->_event_leftPanel_texture_selected();
                });
            }
        }

        bool Editor::_event_leftPanel_texture_selected()
        {
            std::cout<<"_event_leftPanel_texture_selected"<<std::endl;
            return true;
        }
        //bool Editor::_event_leftPanel_tab_changed();
        //bool Editor::_event_leftPanel_tab_NPC_add();
        //bool Editor::_event_leftPanel_tab_NPC_remove();
        //bool Editor::_event_leftPanel_tab_NPC_selected();
        //bool Editor::_event_leftPanel_tab_creature_add();
        //bool Editor::_event_leftPanel_tab_creature_remove();
        //bool Editor::_event_leftPanel_tab_creature_selected();
        //bool Editor::_event_leftPanel_tab_bulding_add();
        //bool Editor::_event_leftPanel_tab_bulding_remove();
        //bool Editor::_event_leftPanel_tab_bulding_selected();

        void Editor::_registerMiniMapCallbacks()
        {
        }
        //bool Editor::_event_miniMap_zoom(float value);

        void Editor::_registerRightPanelCallbacks()
        {
        }
        //bool Editor::_event_rightPanel_layers_add();
        //bool Editor::_event_rightPanel_layers_up();
        //bool Editor::_event_rightPanel_layers_down();
        //bool Editor::_event_rightPanel_layers_remove();
        //bool Editor::_event_rightPanel_tab_changed();
        //bool Editor::_event_rightPanel_tab_brush_selected();
        //bool Editor::_event_rightPanel_tab_NPC_selected();

    }
}
