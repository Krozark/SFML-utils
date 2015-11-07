#ifndef SFUTILS_EDITOR_GUIWINDOW_HPP
#define SFUTILS_EDITOR_GUIWINDOW_HPP

#include <SFML/Graphics.hpp>

namespace CEGUI
{
    class Window;
    class GUIContext;
}

namespace sfutils
{
    namespace editor
    {
        class GuiWindow
        {
            public:
                GuiWindow(const GuiWindow&) = delete;
                GuiWindow& operator=(const GuiWindow&) = delete;

                GuiWindow(const sf::VideoMode& videoMode,const std::string& title);
                virtual ~GuiWindow();

                virtual void processEvents();

                virtual void update(const sf::Time& deltaTime);

                virtual void render();

                void setRootWindow(CEGUI::Window* root);

            protected:
                sf::RenderWindow _window;
                CEGUI::GUIContext* _context;
        };
    }
}
#endif
