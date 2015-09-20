#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>

//#include <CEGUI/CEGUI.h>

namespace CEGUI
{
    class OpenGLRenderer;
    class System;
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
        };
    }
}
#endif
