#include <SFML-utils/map-editor/Gui.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>
#include <SFML-utils/cegui/DialogBox.hpp>

#include <iostream>

namespace sfutils
{
    namespace editor
    {
        Gui::Gui(sf::RenderWindow& mainWindow,Editor& owner) :
            _owner(owner),
            _window(mainWindow),
            _root(nullptr)
        {
            cegui::GuiManager::init("media/editor/cegui/","GlossySerpentFHD","DejaVuSans-10");
            //set mouse
            CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");
            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpentFHD/Tooltip"); 
            //load main layout
            _root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main.layout");
            CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_root);
            //resize gui to the window size 
            
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(mainWindow.getSize().x,mainWindow.getSize().y));

            //register events
            _registerMenuBarCallbacks();
            _registerLeftPanelCallbacks();
            _registerMiniMapCallbacks();
            _registerRightPanelCallbacks();
        }

        bool Gui::processEvent(const sf::Event& event)
        {
            return cegui::GuiManager::processEvent(event,CEGUI::System::getSingleton().getDefaultGUIContext());
        }

        void Gui::update(const sf::Time& deltaTime)
        {
            cegui::GuiManager::update(deltaTime,CEGUI::System::getSingleton().getDefaultGUIContext());
        }

        void Gui::render()
        {
            _window.setActive(true);
            _window.pushGLStates();
            cegui::GuiManager::render(CEGUI::System::getSingleton().getDefaultGUIContext());
            _window.popGLStates();
        }

        void Gui::setMainInfo(const std::string& text)
        {

            CEGUI::Window* txt = _root->getChild("MenuBar/Coordonates");
            txt->setText(text);
        }

        ////////////////////// PRIVATE ///////////////////

        //Menu
        void Gui::_registerMenuBarCallbacks()
        {
            CEGUI::Window* menuBar = _root->getChild("MenuBar");

            {//file
                CEGUI::Window* menu = menuBar->getChild("File/Menu");
                //new
                CEGUI::Window* btn = menu->getChild("New");
                btn->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_menuBar_file_new();
                });
                //open
                btn = menu->getChild("Open");
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
        bool Gui::_event_menuBar_file_new()
        {
            std::cout<<"MenuBar/File/Menu/New clicked"<<std::endl;
            return true;
        }
        bool Gui::_event_menuBar_file_open()
        {
            std::cout<<"MenuBar/File/Menu/Open clicked"<<std::endl;

            std::list<std::string> list;
            sfutils::cegui::DialogBox::getItem(_root,
                                               "Map to load",
                                               "Choose the map to load",
                                               list,
                                               [this](const std::string& value){},
                                               [](){}
                                               );

            return true;
        }
        bool Gui::_event_menuBar_file_save()
        {
            std::cout<<"MenuBar/File/Menu/Save clicked"<<std::endl;
            return true;
        }

        ////Edit
        bool Gui::_event_menuBar_edit_undo()
        {
            std::cout<<"MenuBar/Edit/Menu/Undo clicked"<<std::endl;
            return true;
        }
        bool Gui::_event_menuBar_edit_redo()
        {
            std::cout<<"MenuBar/Edit/Menu/Redo clicked"<<std::endl;
            return true;
        }

        //Map
        bool Gui::_event_menuBar_map_resize()
        {
            std::cout<<"MenuBar/Map/Menu/Resize clicked"<<std::endl;
            return true;
        }
        bool Gui::_event_menuBar_map_shape()
        {
            std::cout<<"MenuBar/Map/Menu/Shape clicked"<<std::endl;
            return true;
        }
        bool Gui::_event_menuBar_map_position()
        {
            std::cout<<"MenuBar/Map/Menu/Position clicked"<<std::endl;
            return true;
        }

        ////LeftPanel
        void Gui::_registerLeftPanelCallbacks()
        {
            CEGUI::Window* menuBar = _root->getChild("Left");

            {//textures
                CEGUI::Listbox* box = static_cast<CEGUI::Listbox*>(menuBar->getChild("Textures")->getChildRecursive("Listbox"));
                assert(box);

                //TEST
                for(int i=0; i< 25; ++i)
                {
                    CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                    newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                    newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                    newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                    newItem->setAutoDeleted(true);

                    box->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    //box->ensureItemIsVisible(newItem);
                }


                box->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,box](const CEGUI::EventArgs& e){
                    return this->_event_leftPanel_texture_selected(box);
                });
            }

            {//tab
                CEGUI::TabControl* box = static_cast<CEGUI::TabControl*>(menuBar->getChild("Tab"));
                box->subscribeEvent(CEGUI::TabControl::EventSelectionChanged,[this,box](const CEGUI::EventArgs& e){
                    return this->_event_leftPanel_tab_changed(box->getTabContentsAtIndex(box->getSelectedTabIndex())->getName().c_str());
                });

                {//NPC
                    CEGUI::Window* tab = box->getChild("NPC");
                    //CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_NPC_add();
                    });
                    bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_NPC_remove();
                    });
                }

                {//Creature
                    CEGUI::Window* tab = box->getChild("Creatures");
                    //CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_creature_add();
                    });
                    bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_creature_remove();
                    });
                }

                {//Building
                    CEGUI::Window* tab = box->getChild("Bulding");
                    //CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_bulding_add();
                    });
                    bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_bulding_remove();
                    });
                }
            }
        }

        bool Gui::_event_leftPanel_texture_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_texture_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_leftPanel_tab_changed(const std::string& name)
        {
            std::cout<<"_event_leftPanel_tab_changed :"<<name<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_NPC_add()
        {
            std::cout<<"_event_leftPanel_tab_NPC_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_NPC_remove()
        {
            std::cout<<"_event_leftPanel_tab_NPC_remove()"<<std::endl;
            return true;
        }
        //TODO bool Gui::_event_leftPanel_tab_NPC_selected();

        bool Gui::_event_leftPanel_tab_creature_add()
        {
            std::cout<<"_event_leftPanel_tab_creature_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_creature_remove()
        {
            std::cout<<"_event_leftPanel_tab_creature_remove()"<<std::endl;
            return true;
        }
        //TODO bool Gui::_event_leftPanel_tab_creature_selected();

        bool Gui::_event_leftPanel_tab_bulding_add()
        {
            std::cout<<"_event_leftPanel_tab_bulding_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_bulding_remove()
        {
            std::cout<<"_event_leftPanel_tab_bulding_remove()"<<std::endl;
            return true;
        }

        //TODO bool Gui::_event_leftPanel_tab_bulding_selected();

        void Gui::_registerMiniMapCallbacks()
        {
        }
        //bool Gui::_event_miniMap_zoom(float value);

        void Gui::_registerRightPanelCallbacks()
        {
        }
        //bool Gui::_event_rightPanel_layers_add();
        //bool Gui::_event_rightPanel_layers_up();
        //bool Gui::_event_rightPanel_layers_down();
        //bool Gui::_event_rightPanel_layers_remove();
        //bool Gui::_event_rightPanel_tab_changed();
        //bool Gui::_event_rightPanel_tab_brush_selected();
        //bool Gui::_event_rightPanel_tab_NPC_selected();

    }
}
