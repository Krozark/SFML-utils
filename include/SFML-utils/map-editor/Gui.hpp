#ifndef SFUTILS_EDITOR_GUI_HPP
#define SFUTILS_EDITOR_GUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML-utils/map/Models.hpp>

namespace CEGUI
{
    class OpenGLRenderer;
    class System;
    class Window;
    class Listbox;
    class ListboxItem;
    class GUIContext;
}

namespace sfutils
{
    namespace editor
    {
        class Editor;
        class Gui
        {
            public:
                Gui(const Gui&) = delete;
                Gui& operator=(const Gui&) = delete;

                Gui(sf::RenderWindow& mainWindow,Editor& owner);

                bool processEvent(const sf::Event& event);
                void update(const sf::Time& deltaTime);
                void render();

                void setMainInfo(const std::string& text);
                void setTitle(const std::string& text);

                void addLayer(sfutils::map::LayerModel::pointer& layer);
                void delLayer(sfutils::map::LayerModel::pointer& layer);

                void reset();

            private:
                Editor& _owner;
                sf::RenderWindow& _window;
                CEGUI::Window* _root;
                CEGUI::GUIContext* _context;

                CEGUI::Listbox* _layerList;
                void _clearLayerList();
                void _setLayerListItemName(CEGUI::ListboxItem* item);

                /*menu*/
                void _registerMenuBarCallbacks();
                ////file
                bool _event_menuBar_file_new();
                bool _event_menuBar_file_open();
                bool _event_menuBar_file_save();
                ////edit
                bool _event_menuBar_edit_undo();
                bool _event_menuBar_edit_redo();
                ////map
                bool _event_menuBar_map_resize();
                bool _event_menuBar_map_shape();
                bool _event_menuBar_map_position();

                /*left panel*/
                void _registerLeftPanelCallbacks();
                ////texture
                bool _event_leftPanel_texture_selected(CEGUI::Listbox* box);
                ////Tab
                bool _event_leftPanel_tab_changed(const std::string& name);
                //////NPC
                bool _event_leftPanel_tab_NPC_selected(CEGUI::Listbox* box);
                bool _event_leftPanel_tab_NPC_add();
                bool _event_leftPanel_tab_NPC_remove();
                //////creatures
                bool _event_leftPanel_tab_creature_selected(CEGUI::Listbox* box);
                bool _event_leftPanel_tab_creature_add();
                bool _event_leftPanel_tab_creature_remove();
                //////buldings
                bool _event_leftPanel_tab_bulding_selected(CEGUI::Listbox* box);
                bool _event_leftPanel_tab_bulding_add();
                bool _event_leftPanel_tab_bulding_remove();


                /*top*/

                /*miniMap*/
                void _registerMiniMapCallbacks();
                bool _event_miniMap_zoom(float value);

                /*Right panel*/
                void _registerRightPanelCallbacks();
                ////Layers
                bool _event_rightPanel_layer_selected();
                bool _event_rightPanel_layers_add();
                bool _event_rightPanel_layers_up();
                bool _event_rightPanel_layers_down();
                bool _event_rightPanel_layers_remove();
                ////tab
                bool _event_rightPanel_tab_changed(const std::string& name);
                //////Brush
                bool _event_rightPanel_tab_brush_selected(CEGUI::Listbox* box);
                //////NPC
                bool _event_rightPanel_tab_NPC_selected(CEGUI::Listbox* box);

        };
    }
}
#endif
