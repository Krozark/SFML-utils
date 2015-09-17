#ifndef SFUTILS_CEGUI_GUIMANAGER_HPP
#define SFUTILS_CEGUI_GUIMANAGER_HPP

#include <array>

#include <SFML/Graphics.hpp>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

namespace sfutils
{
    namespace cegui
    {
        class GuiManager
        {
            public:
                GuiManager(const GuiManager&) = delete;
                GuiManager& operator=(const GuiManager&) = delete;

                static void init(const std::string& mediDirectory,const std::string& defaultFont = "DejaVuSans-10");

                static bool processEvent(const sf::Event& event); //< inject event to CEGUI::System::getSingleton().getDefaultGUIContext()
                static bool processEvent(const sf::Event& event,CEGUI::GUIContext& context);

                /**
                 * update BOTH of the system and the default GUIContext
                 */
                static void update(const sf::Time& deltaTime);

                /**
                 * update ONLY the context.
                 * You have to update the system yourself
                 */
                static void update(const sf::Time& deltaTime,CEGUI::GUIContext& context);

                /**
                 * Don't forget to [push/pop]GLStates
                 * render the default context
                 * */
                static void render();

                /**
                 * Don't forget to [push/pop]GLStates
                 * render the specified context
                 * */
                static void render(CEGUI::GUIContext& context);

                static CEGUI::OpenGLRenderer& getRenderer();


            protected:

            private:
                GuiManager();
                
	            typedef std::array<CEGUI::Key::Scan,sf::Keyboard::Key::KeyCount> KeyMap;
	            typedef std::array<CEGUI::MouseButton,sf::Mouse::Button::ButtonCount> MouseButtonMap;

	            static KeyMap _keyMap;
	            static MouseButtonMap _mouseButtonMap;
                static CEGUI::OpenGLRenderer* _renderer;

                static void _initMaps();
                static void _initRenderer();
                static void _initResources(const std::string& rootDir);

        };
    }
}
#endif
