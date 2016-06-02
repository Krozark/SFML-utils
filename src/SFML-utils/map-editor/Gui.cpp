#include <SFML-utils/map-editor/Gui.hpp>
#include <SFML-utils/map-editor/Editor.hpp>

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
            _root(nullptr),
            _layerList(nullptr)
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

        void Gui::setTitle(const std::string& text)
        {
            CEGUI::Window* txt = _root->getChild("MenuBar/Title");
            txt->setText(text);
        }

        void Gui::addLayer(sfutils::map::LayerModel::pointer& layer)
        {
            assert(_layerList);
            CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("");


            newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
            newItem->setSelectionColours(CEGUI::Colour(1,0,0));
            newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
            newItem->setAutoDeleted(true);
            newItem->setUserData(layer.get());
            _layerList->addItem(newItem);

            unsigned int size = _layerList->getItemCount();
            for(unsigned int i = 0; i < size; ++i)
            {
                CEGUI::ListboxItem* item = _layerList->getListboxItemFromIndex(i);
                _setLayerListItemName(item);
            }
        }

        void Gui::delLayer(sfutils::map::LayerModel::pointer& layer)
        {
            //TODO
        }

        void Gui::reset()
        {
            setMainInfo("");
            setTitle("");
            _clearLayerList();
        }

        ////////////////////// PRIVATE ///////////////////

        void Gui::_clearLayerList()
        {
            assert(_layerList);
            _layerList->resetList();
        }

        void Gui::_setLayerListItemName(CEGUI::ListboxItem* item)
        {
            sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
            item->setText(layer->name.getValue() + " (" + std::to_string(layer->zBuffer.getValue()) + ")");
        }


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
            for(auto& map :  sfutils::map::MapModel::all())
            {
                list.emplace_back(map->name);
            }

            sfutils::cegui::DialogBox::getItem(_root,
                                               "Map to load",
                                               "Choose the map to load",
                                               list,
                                               [this](const std::string& value){
                                                   for(auto& map :  sfutils::map::MapModel::all())
                                                   {
                                                       if(map->name == value)
                                                       {
                                                           this->_owner.setMap(map);
                                                           break;
                                                       }
                                                   }

                                               },
                                               [](){}
                                              );


            return true;
        }
        bool Gui::_event_menuBar_file_save()
        {
            std::cout<<"MenuBar/File/Menu/Save clicked"<<std::endl;

            CEGUI::Window* box = _root->getChild("MenuBar/Title");
            std::string title = box->getText().c_str();

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

                //TODO TEST
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
                    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    list->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,list](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_NPC_selected(list);
                    });

                    //TODO TEST
                    for(int i=0; i< 25; ++i)
                    {
                        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                        newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                        newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                        newItem->setAutoDeleted(true);

                        list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    }

                    bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_NPC_add();
                    });
                    bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_NPC_remove();
                    });
                }

                {//Creature
                    CEGUI::Window* tab = box->getChild("Creatures");
                    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    list->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,list](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_creature_selected(list);
                    });

                    //TODO TEST
                    for(int i=0; i< 25; ++i)
                    {
                        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                        newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                        newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                        newItem->setAutoDeleted(true);

                        list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    }

                    bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_creature_add();
                    });
                    bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_creature_remove();
                    });
                }

                {//Building
                    CEGUI::Window* tab = box->getChild("Bulding");
                    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(tab->getChild("List"));
                    CEGUI::Window* bottom = tab->getChild("Bottom");

                    list->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,list](const CEGUI::EventArgs& e){
                        return this->_event_leftPanel_tab_bulding_selected(list);
                    });

                    //TODO TEST
                    for(int i=0; i< 25; ++i)
                    {
                        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                        newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                        newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                        newItem->setAutoDeleted(true);

                        list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    }

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
            std::cout<<"_event_leftPanel_tab_changed"<<std::endl;
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

        bool Gui::_event_leftPanel_tab_NPC_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_NPC_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

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

        bool Gui::_event_leftPanel_tab_creature_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_creature_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

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

        bool Gui::_event_leftPanel_tab_bulding_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_bulding_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }
        
        //void Gui::_event_top_titleChanged();
        
        void Gui::_registerMiniMapCallbacks()
        {
            CEGUI::Window* bar = _root->getChild("MiniMap");

            {//Zoom slider
                CEGUI::Scrollbar* box = static_cast<CEGUI::Scrollbar*>(bar->getChild("Slider"));
                assert(box);

                box->setPageSize(0);
                box->setDocumentSize(3); //max zoom
                box->setStepSize(0.2); //step

                box->setScrollPosition(1); //initial

                box->subscribeEvent(CEGUI::Scrollbar::EventScrollPositionChanged,[this,box](const CEGUI::EventArgs& e){
                    return this->_event_miniMap_zoom(box->getScrollPosition());
                });
            }
        }

        bool Gui::_event_miniMap_zoom(float value)
        {
            if(value > 0)
            {
                _owner.setMiniMapZoom(value);
            }
            return true;
        }

        void Gui::_registerRightPanelCallbacks()
        {
            CEGUI::Window* bar = _root->getChild("Right");

            {//layers
                CEGUI::Window* layers = bar->getChild("Layers");
                _layerList = static_cast<CEGUI::Listbox*>(layers->getChildRecursive("List"));
                assert(_layerList);

                _layerList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layer_selected();
                });

                CEGUI::Window* bottom = layers->getChildRecursive("Bottom");
                assert(bottom);

                bottom->getChild("Add")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layers_add();
                });

                bottom->getChild("Up")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layers_up();
                });

                bottom->getChild("Down")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layers_down();
                });

                bottom->getChild("Remove")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                   return this->_event_rightPanel_layers_remove();
               });
            }

            {//Tab
                CEGUI::TabControl* box = static_cast<CEGUI::TabControl*>(bar->getChild("Tab"));

                box->subscribeEvent(CEGUI::TabControl::EventSelectionChanged,[this,box](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_tab_changed(box->getTabContentsAtIndex(box->getSelectedTabIndex())->getName().c_str());
                });


                {//Brush
                    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(box->getChild("Brush")->getChildRecursive("List"));
                    assert(list);

                    list->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,list](const CEGUI::EventArgs& e){
                        return this->_event_rightPanel_tab_brush_selected(list);
                    });

                    //TODO load brush
                    for(int i=0; i< 25; ++i)
                    {
                        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                        newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                        newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                        newItem->setAutoDeleted(true);

                        list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    }

                }

                {//NPC
                    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(box->getChild("NPC")->getChildRecursive("List"));
                    assert(list);


                    list->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this,list](const CEGUI::EventArgs& e){
                        return this->_event_rightPanel_tab_NPC_selected(list);
                    });

                    //TODO load edit mode
                    for(int i=0; i< 25; ++i)
                    {
                        CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem("Item #"+std::to_string(i));

                        newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
                        newItem->setSelectionColours(CEGUI::Colour(1,0,0));
                        newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
                        newItem->setAutoDeleted(true);

                        list->addItem(newItem); // Add the new ListBoxTextItem to the ListBox
                    }
                }
                
            }

        }

        bool Gui::_event_rightPanel_layer_selected()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_rightPanel_layer_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_rightPanel_layers_add()
        {
            std::cout<<"_event_rightPanel_layers_add"<<std::endl;
            return true;
        }

        bool Gui::_event_rightPanel_layers_up()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item == nullptr)
            {
                return true;
            }

            unsigned int size = _layerList->getItemCount();
            unsigned int index = _layerList->getItemIndex(item);
            if(size == 1 or index == 0) //already on top
            {
                return true;
            }

            sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
            assert(layer);

            int from = layer->zBuffer.getValue();
            if(_owner.requestMoveLayer(from,from+1) == false)
            {
                return true;
            }

             CEGUI::ListboxItem* itemTop = _layerList->getListboxItemFromIndex(index -1);
             assert(itemTop);

            //remove move item
            item->setAutoDeleted(false);
            _layerList->removeItem(item);

            //readd it at new place
             _layerList->insertItem(item,itemTop);
            item->setAutoDeleted(true);


            return true;
        }

        bool Gui::_event_rightPanel_layers_down()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item == nullptr)
            {
                return true;
            }

            unsigned int size = _layerList->getItemCount();
            unsigned int index = _layerList->getItemIndex(item);

            if(size == 1 or index == size - 1) //already on bottom
            {
                return true;
            }
            
            sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
            assert(layer);

            int from = layer->zBuffer.getValue();
            if(_owner.requestMoveLayer(from,from-1) == false)
            {
                return true;
            }


            CEGUI::ListboxItem* itemBottom = _layerList->getListboxItemFromIndex(index + 1);
            assert(itemBottom);

            //remove move item
            itemBottom->setAutoDeleted(false);
            _layerList->removeItem(itemBottom);

            //readd it at new place
            _layerList->insertItem(itemBottom,item);
            itemBottom->setAutoDeleted(true);

            return true;
        }

        bool Gui::_event_rightPanel_layers_remove()
        {
            std::cout<<"_event_rightPanel_layers_remove"<<std::endl;
            return true;
        }

        bool Gui::_event_rightPanel_tab_changed(const std::string& name)
        {
            std::cout<<"_event_rightPanel_tab_changed("<<name<<")"<<std::endl;
            return true;
        }

        bool Gui::_event_rightPanel_tab_brush_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_rightPanel_tab_brush_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_rightPanel_tab_NPC_selected(CEGUI::Listbox* box)
        {
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_rightPanel_tab_NPC_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

    }
}
