#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>

//#include <CEGUI/CEGUI.h>

namespace CEGUI
{
    class OpenGLRenderer;
    class System;
    class Window;
}

namespace sfutils
{
    namespace editor
    {
        class Editor
        {
            public:
                Editor(const Editor&) = delete;
                Editor& operator=(const Editor&) = delete;

                explicit Editor();
                ~Editor();

                void run();

            private:
                sf::RenderWindow _window;
                sf::Clock _clock;

                void _processEvents();
                void _update();
                void _render();

                void _createGui();
                CEGUI::Window* _root;

                /*menu*/
                void _registerMenuBarCallbacks();
                ////file
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
                bool _event_leftPanel_texture_selected();
                ////Tab
                bool _event_leftPanel_tab_changed();
                //////NPC
                bool _event_leftPanel_tab_NPC_add();
                bool _event_leftPanel_tab_NPC_remove();
                bool _event_leftPanel_tab_NPC_selected();
                //////creatures
                bool _event_leftPanel_tab_creature_add();
                bool _event_leftPanel_tab_creature_remove();
                bool _event_leftPanel_tab_creature_selected();
                //////buldings
                bool _event_leftPanel_tab_bulding_add();
                bool _event_leftPanel_tab_bulding_remove();
                bool _event_leftPanel_tab_bulding_selected();

                /*miniMap*/
                void _registerMiniMapCallbacks();
                bool _event_miniMap_zoom(float value);

                /*Right panel*/
                void _registerRightPanelCallbacks();
                ////Layers
                bool _event_rightPanel_layers_add();
                bool _event_rightPanel_layers_up();
                bool _event_rightPanel_layers_down();
                bool _event_rightPanel_layers_remove();
                ////tab
                bool _event_rightPanel_tab_changed();
                //////Brush
                bool _event_rightPanel_tab_brush_selected();
                //////NPC
                bool _event_rightPanel_tab_NPC_selected();

        };
    }
}
#endif
