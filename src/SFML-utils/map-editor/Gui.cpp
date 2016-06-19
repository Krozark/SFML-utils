#include <SFML-utils/map-editor/Gui.hpp>
#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>
#include <SFML-utils/cegui/DialogBox.hpp>

#include <utils/string.hpp>

#include <iostream>
#include <sstream>


namespace sfutils
{
    namespace editor
    {
        Gui::Gui(sf::RenderWindow& mainWindow,Editor& owner) :
            _owner(owner),
            _window(mainWindow),
            _root(nullptr),
            _textureList(nullptr),
            _layerList(nullptr),
            _brushList(nullptr),
            _newLayer(nullptr)
        {
            cegui::GuiManager::init("media/editor/cegui/","GlossySerpentFHD","DejaVuSans-10");
            //set mouse
            _context = &sfutils::cegui::GuiManager::createGUIContext();

            _context->getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");
            _context->setDefaultTooltipType("GlossySerpentFHD/Tooltip"); 
            //load main layout
            _root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Editor.layout");
            _context->setRootWindow(_root);
            //resize gui to the window size 
            
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(mainWindow.getSize().x,mainWindow.getSize().y));

            //register events
            _registerMenuBarCallbacks();
            _registerLeftPanelCallbacks();
            _registerMiniMapCallbacks();
            _registerRightPanelCallbacks();


        }

        Gui::~Gui()
        {
            _root->destroy();
            cegui::GuiManager::destroyGUIContext(*_context);
        }

        bool Gui::processEvent(const sf::Event& event)
        {
            return cegui::GuiManager::processEvent(event,*_context);
        }

        void Gui::update(const sf::Time& deltaTime)
        {
            cegui::GuiManager::update(deltaTime,*_context);
        }

        void Gui::render()
        {
            _window.setActive(true);
            _window.pushGLStates();
            cegui::GuiManager::render(*_context);
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

        void Gui::addLayer(sfutils::map::LayerModel::pointer& layer,bool begin)
        {
            assert(_layerList);

            auto item = _helperCreateTextItem("",layer.get());
            if(begin)
            {
                _layerList->insertItem(item,nullptr);
            }
            else
            {
                _layerList->addItem(item);
            }

            _layerList->setItemSelectState(size_t(0),true);

            _setLayerListItemNames();

        }

        void Gui::delLayer(sfutils::map::LayerModel::pointer& layer)
        {
            assert(_layerList);
            unsigned int size = _layerList->getItemCount();
            for(unsigned int i = 0; i < size; ++i)
            {
                CEGUI::ListboxItem* item = _layerList->getListboxItemFromIndex(i);
                if(item->getUserData() == layer.get())
                {
                    _layerList->removeItem(item);
                    break;
                }
            }
        }

        void Gui::addTexture(const std::string& text)
        {
            _addToList(_textureList,text);
        }

        void Gui::delTexture(const std::string& text)
        {
            _removeFromList(_textureList,text);
        }

        void Gui::addBrush(const std::string& text)
        {
            _addToList(_brushList,text);
        }

        void Gui::delBrush(const std::string& text)
        {
            _removeFromList(_brushList,text);
        }

        int Gui::getCurrentLayerZIndex() const
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item)
            {
                sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
                assert(layer);
                return layer->zBuffer.getValue();
            }
            return -1;
        }

        void Gui::reset()
        {
            setMainInfo("");
            setTitle("");
            _clearListBox(_layerList);
            _clearListBox(_textureList);
        }

        ////////////////////// PRIVATE ///////////////////

        void Gui::_clearListBox(CEGUI::Listbox* list)
        {
            assert(list);
            list->resetList();
        }

        void Gui::_addToList(CEGUI::Listbox* list,const std::string& text,void* userData)
        {
            assert(list);
            list->addItem(_helperCreateTextItem(text,userData));
            list->setItemSelectState(size_t(0),true);
        }

        void Gui::_removeFromList(CEGUI::Listbox* list,const std::string& text)
        {
            assert(list);
            CEGUI::ListboxItem* item = list->findItemWithText(text,nullptr);
            if(item)
            {
                list->removeItem(item);
            }
        }

        void Gui::_setLayerListItemNames()
        {
            unsigned int size = _layerList->getItemCount();
            for(unsigned int i = 0; i < size; ++i)
            {
                CEGUI::ListboxTextItem* item = reinterpret_cast< CEGUI::ListboxTextItem*>(_layerList->getListboxItemFromIndex(i));
                sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());

                if(layer->isVisible.getValue() == false)
                {
                    item->setTextColours(CEGUI::Colour(1,0,0,1));
                }
                else
                {
                    item->setTextColours(CEGUI::Colour(1,1,1,1));
                }
                std::stringstream ss;
                ss << std::to_string(layer->zBuffer.getValue())<< " "
                    <<layer->name.getValue();
                item->setText(ss.str());

            }

            _layerList->handleUpdatedItemData();
        }

        CEGUI::ListboxTextItem* Gui::_helperCreateTextItem(const std::string& txt, void* userData)
        {
            CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(txt);

            newItem->setTextColours(CEGUI::Colour( 0xFFFFFFFF));
            newItem->setSelectionColours(CEGUI::Colour(1,0,0));
            newItem->setSelectionBrushImage("GlossySerpentFHD/ListboxSelectionBrush");
            newItem->setAutoDeleted(true);
            newItem->setUserData(userData);

            return newItem;
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

        ////LeftPanel
        void Gui::_registerLeftPanelCallbacks()
        {
            CEGUI::Window* menuBar = _root->getChild("Left");

            {//textures
                _textureList = static_cast<CEGUI::Listbox*>(menuBar->getChild("Textures")->getChildRecursive("Listbox"));
                assert(_textureList);

                _textureList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this](const CEGUI::EventArgs& e){
                    return this->_event_leftPanel_texture_selected();
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
                        list->addItem(_helperCreateTextItem("Item #" + std::to_string(i)));
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
                        list->addItem(_helperCreateTextItem("Item #" + std::to_string(i)));
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
                        list->addItem(_helperCreateTextItem("Item #" + std::to_string(i)));
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

        void Gui::_registerRightPanelCallbacks()
        {
            CEGUI::Window* bar = _root->getChild("Right");

            {//layers
                CEGUI::Window* layers = bar->getChild("Layers");
                _layerList = static_cast<CEGUI::Listbox*>(layers->getChildRecursive("List"));
                assert(_layerList);

                /*_layerList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layer_selected();
                });*/

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

                bottom->getChild("Check")->subscribeEvent(CEGUI::PushButton::EventClicked,[this](const CEGUI::EventArgs& e){
                    return this->_event_rightPanel_layers_check();
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
                    _brushList = static_cast<CEGUI::Listbox*>(box->getChild("Brush")->getChildRecursive("List"));
                    assert(_brushList);

                    _brushList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,[this](const CEGUI::EventArgs& e){
                        return this->_event_rightPanel_tab_brush_selected();
                    });
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
                        list->addItem(_helperCreateTextItem("Item #" + std::to_string(i)));
                    }
                }
                
            }

        }

        void Gui::_showNewLayerPopup()
        {
            CEGUI::Window* newLayerPopup = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("NewLayer.layout");

            _root->addChild(newLayerPopup);
            newLayerPopup->show();
            newLayerPopup->setModalState(true);

            CEGUI::Window* layer = newLayerPopup->getChild("Layer");
            assert(layer);

            CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(layer->getChild("TypeList"));
            assert(list);

            for(auto& ptr : sfutils::map::LayerTypeModel::all())
            {
                list->addItem(_helperCreateTextItem(ptr->name.getValue(),ptr.get()));
            }
            list->setItemSelectState(list->getListboxItemFromIndex(0),true);

            {
                CEGUI::Window* layerBtns = layer->getChild("ValidButtonLayer");
                assert(layerBtns);

                CEGUI::Window* btnOk = layerBtns->getChild("Ok");
                assert(btnOk);
                btnOk->subscribeEvent(CEGUI::PushButton::EventClicked,
                                CEGUI::Event::Subscriber([this,newLayerPopup](const CEGUI::EventArgs& e){
                                                         bool res =  _event_newLayer_ok(newLayerPopup);
                                                         _root->destroyChild(newLayerPopup);
                                                         return res;
                                                         }));


                CEGUI::Window* btnCancel = layerBtns->getChild("Cancel");
                assert(btnCancel);
                btnCancel->subscribeEvent(CEGUI::PushButton::EventClicked,
                                CEGUI::Event::Subscriber([this,newLayerPopup](const CEGUI::EventArgs& e){
                                                         _root->destroyChild(newLayerPopup);
                                                         return true;
                                                         }));
            }
        }
    }
}
