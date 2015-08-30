#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

namespace sfutils
{
    namespace editor
    {
        class Editor
        {
            public:
                Editor(const Editor&) = delete;
                Editor& operator=(const Editor&) = delete;

                explicit Editor(const sf::VideoMode& mode);

                void run();

            private:
                sf::RenderWindow _window;
                sfg::SFGUI _sfgui;
                sfg::Desktop _desktop;

                void _processEvents();
                void _update();
                void _render();
        };
    }
}
#endif
