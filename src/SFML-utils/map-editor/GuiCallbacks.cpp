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
            _owner.getMap()->name = title;

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
                <<_owner.getMap()->areaHeight.getValue()<<" "
                <<_owner.getMap()->areaWidth.getValue();

            sfutils::cegui::DialogBox::getString(
                 _root,
                 "Change map size",
                 "Choose a new size\nScale Height Width",
                 [this](const std::string& size){
                      std::cout<<"size : "<<size<<std::endl;
                      auto split = utils::string::split(size," ");
                      _owner.getMap()->scale = std::stoi(split[0]);
                      _owner.getMap()->areaHeight = std::stoi(split[1]);
                      _owner.getMap()->areaWidth = std::stoi(split[2]);

                      _owner.reloadMap();
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
                               this->_owner.getMap()->geometry = geo;
                               this->_owner.reloadMap();
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

        bool Gui::_event_rightPanel_layer_selected()
        {
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item)
            {
                sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
                assert(layer);
                _owner.requestSetCurrentLayer(layer->zBuffer.getValue());
            }

            return true;
        }

        bool Gui::_event_rightPanel_layers_add()
        {
            //TODO
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
            CEGUI::ListboxItem* item = _layerList->getFirstSelectedItem();
            if(item == nullptr)
            {
                return true;
            }
            sfutils::map::LayerModel* layer = static_cast<sfutils::map::LayerModel*>(item->getUserData());
            assert(layer);

            return _owner.requestDelLayer(layer->zBuffer.getValue());
        }

        bool Gui::_event_rightPanel_tab_changed(const std::string& name)
        {
            //TODO
            std::cout<<"_event_rightPanel_tab_changed("<<name<<")"<<std::endl;
            return true;
        }

        bool Gui::_event_rightPanel_tab_brush_selected(CEGUI::Listbox* box)
        {
            //TODO
            CEGUI::ListboxItem* item = box->getFirstSelectedItem();
            if(item)
            {
                std::cout<<"_event_rightPanel_tab_brush_selected : "<<item->getText().c_str()<<std::endl;
            }

            return true;
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

    }
}
