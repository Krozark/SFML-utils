#include <SFML-utils/map-editor/GuiWindow.hpp>

#include <SFML-utils/cegui/GuiManager.hpp>

namespace sfutils
{
    namespace editor
    {
        GuiWindow::GuiWindow(const sf::VideoMode& videoMode,const std::string& title) :
            _window(videoMode, title),
            _context(nullptr)
            
        {
            _context = &cegui::GuiManager::createGUIContext();
        }

        GuiWindow::~GuiWindow()
        {
        }

        void GuiWindow::processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                cegui::GuiManager::processEvent(event,*_context);
            }
        }

        void GuiWindow::update(const sf::Time& deltaTime)
        {
            cegui::GuiManager::update(deltaTime,*_context);
        }

        void GuiWindow::render()
        {
            _window.setActive(true);
            _window.pushGLStates();
            cegui::GuiManager::render(*_context);
            _window.popGLStates();
        }

        void GuiWindow::setRootWindow(CEGUI::Window* root)
        {
            _context->setRootWindow(root);
        }
    }
}
