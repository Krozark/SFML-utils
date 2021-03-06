#include <SFML-utils/map-editor/Gui.hpp>
#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>
#include <SFML-utils/cegui/DialogBox.hpp>

#include <utils/string.hpp>

#include <iostream>


namespace sfutils
{
    namespace editor
    {

        ////////////////////// PRIVATE ///////////////////

        ////File
        bool Gui::_event_menuBar_file_new()
        {
            std::list<std::string> list;
            for(auto& map :  sfutils::map::GeometryModel::all())
            {
                list.emplace_back(map->name);
            }

            sfutils::cegui::DialogBox::getStringAndItem(
                _root,
                "Create a new map",
                "Enter the title, and choose the tile format",
                list,
                [this](const std::string& title,const std::string& geometry){
                    for(auto& geo :  sfutils::map::GeometryModel::all())
                    {
                        if(geo->name == geometry)
                        {
                            sfutils::map::MapModel::pointer tmp = sfutils::map::MapModel::create();
                            tmp->name = title;
                            tmp->geometry = geo;
                            tmp->scale = 50;
                            tmp->areaWidth = 10;
                            tmp->areaHeight = 10;
                            tmp->save();

                            this->_owner.setMap(tmp);
                            break;
                        }
                    }

                });
            return true;
        }

        bool Gui::_event_menuBar_file_open()
        {
            std::list<std::string> list;
            for(auto& map :  sfutils::map::MapModel::all())
            {
                list.emplace_back(map->name);
            }

            sfutils::cegui::DialogBox::getItem(
                   _root,
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

                   });

            return true;
        }

        bool Gui::_event_menuBar_file_save()
        {
            //TODO
            std::cout<<"MenuBar/File/Menu/Save clicked"<<std::endl;

            CEGUI::Window* box = _root->getChild("MenuBar/Title");
            std::string title = box->getText().c_str();
            _owner.getMapStateChanger().setTitle(title);

            return _owner.requestSaveMap();
        }

        ////Edit
        bool Gui::_event_menuBar_edit_undo()
        {
            //TODO
            std::cout<<"MenuBar/Edit/Menu/Undo clicked"<<std::endl;
            return true;
        }

        bool Gui::_event_menuBar_edit_redo()
        {
            //TODO
            std::cout<<"MenuBar/Edit/Menu/Redo clicked"<<std::endl;
            return true;
        }

        //Map
        bool Gui::_event_menuBar_map_resize()
        {
            std::stringstream ss;
            ss<<_owner.getMap()->scale.getValue()<<" "
                <<_owner.getMap()->areaWidth.getValue() << " "
                <<_owner.getMap()->areaHeight.getValue();

            sfutils::cegui::DialogBox::getString(
                 _root,
                 "Change map size",
                 "Choose a new size\nScale Width Height",
                 [this](const std::string& size){
                      auto split = utils::string::split(size," ");
                      _owner.getMapStateChanger().setSize(std::stoi(split[0]),std::stoi(split[1]),std::stoi(split[2]));
                 },
                 [](){},
                 ss.str(),
                 "\\d(\\d)* \\d(\\d)* \\d(\\d)*"
                 );
            return true;
        }

        bool Gui::_event_menuBar_map_shape()
        {
            std::list<std::string> list;
            for(auto& map :  sfutils::map::GeometryModel::all())
            {
                list.emplace_back(map->name);
            }

            sfutils::cegui::DialogBox::getItem(
                   _root,
                   "Change map shape",
                   "Choose the new geometry",
                   list,
                   [this](const std::string& geometry){
                       for(auto& geo :  sfutils::map::GeometryModel::all())
                       {
                           if(geo->name == geometry)
                           {
                               this->_owner.getMapStateChanger().setGeometry(geo);
                               break;
                           }
                       }
                   });
            return true;
        }

        bool Gui::_event_menuBar_map_position()
        {
            //TODO
            std::cout<<"MenuBar/Map/Menu/Position clicked"<<std::endl;
            return true;
        }

        ////LeftPanel
        bool Gui::_event_leftPanel_texture_selected()
        {
            CEGUI::ListboxItem* item = _textureList->getFirstSelectedItem();
            if(item)
            {
                _owner.requestTextureSelected(item->getText().c_str());
            }

            return true;
        }

        bool Gui::_event_leftPanel_tab_changed(const std::string& name)
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_changed"<<std::endl;
            std::cout<<"_event_leftPanel_tab_changed :"<<name<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_NPC_add()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_NPC_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_NPC_remove()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_NPC_remove()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_NPC_selected(CEGUI::Listbox* box)
        {
            //TODO
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_NPC_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_leftPanel_tab_creature_add()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_creature_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_creature_remove()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_creature_remove()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_creature_selected(CEGUI::Listbox* box)
        {
            //TODO
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_creature_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_leftPanel_tab_bulding_add()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_bulding_add()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_bulding_remove()
        {
            //TODO
            std::cout<<"_event_leftPanel_tab_bulding_remove()"<<std::endl;
            return true;
        }

        bool Gui::_event_leftPanel_tab_bulding_selected(CEGUI::Listbox* box)
        {
            //TODO
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_leftPanel_tab_bulding_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }
        
        //void Gui::_event_top_titleChanged();
        
        bool Gui::_event_miniMap_zoom(float value)
        {
            if(value > 0)
            {
                _owner.setMiniMapZoom(value);
            }
            return true;
        }

        /*bool Gui::_event_rightPanel_layer_selected()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item)
            {
                sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
                assert(layer);
                _owner.requestSetCurrentLayer(layer->zBuffer.getValue());
            }

            return true;
        }*/

        bool Gui::_event_rightPanel_layers_add()
        {
            _showNewLayerPopup();
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

            _setLayerListItemNames();

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

            _setLayerListItemNames();

            return true;
        }

        bool Gui::_event_rightPanel_layers_check()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item == nullptr)
            {
                return true;
            }

            sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
            assert(layer);

            if(_owner.requestVisibilityLayer(layer->zBuffer.getValue()) == false)
            {
                return false;
            }

            _setLayerListItemNames();

            return true;
        }

        bool Gui::_event_rightPanel_layers_remove()
        {
            sfutils::cegui::DialogBox::message(_root,
                                               "Are you sure?",
                                               "Do you realy want to delete this layer forever?",
                                               [this](){//Ok
                                                   CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
                                                   if(item == nullptr)
                                                   {
                                                       return;
                                                   }
                                                   sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
                                                   assert(layer);

                                                   if(_owner.requestDelLayer(layer->zBuffer.getValue()) == false)
                                                   {
                                                       return;
                                                   }

                                                   _layerList->removeItem(item);
                                                   _setLayerListItemNames();
                                               }
                                              );
            return true;

        }

        bool Gui::_event_rightPanel_tab_changed(const std::string& name)
        {
            //TODO
            std::cout<<"_event_rightPanel_tab_changed("<<name<<")"<<std::endl;
            return true;
        }

        bool Gui::_event_rightPanel_tab_brush_selected()
        {
            CEGUI::ListboxItem* item = _brushList->getFirstSelectedItem();
            if(item)
            {
                return _owner.requestBrushSelected(item->getText().c_str());
            }

            return false;
        }

        bool Gui::_event_rightPanel_tab_NPC_selected(CEGUI::Listbox* box)
        {
            //TODO
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_rightPanel_tab_NPC_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
        }

        bool Gui::_event_newLayer_ok(CEGUI::Window* newLayerPopup)
        {
            std::string name;
            std::string layerType;
            bool isStatic;
            bool isVisible;
            
            CEGUI::Window* layer = newLayerPopup->getChild("Layer");
            {
                CEGUI::Window* w = layer->getChild("Name");
                name = w->getText().c_str();
            }

            {
                CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(layer->getChild("TypeList"));
                CEGUI::ListboxItem* type = list->getFirstSelectedItem();
                layerType = type->getText().c_str();
            }

            {
                CEGUI::ToggleButton* btn = dynamic_cast<CEGUI::ToggleButton*>(layer->getChild("isStatic"));
                assert(btn);
                isStatic = btn->isSelected();
            }

            {
                CEGUI::ToggleButton* btn = dynamic_cast<CEGUI::ToggleButton*>(layer->getChild("isVisible"));
                assert(btn);
                isVisible = btn->isSelected();
            }
            
            _owner.requestNewLayer(name,layerType,isStatic,isVisible);
            return true;
        }

    }
}
