#ifndef SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP
#define SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP

#include <SFML/Graphics.hpp>

#include <unordered_map>

namespace CEGUI
{
    //class OpenGLRenderer;
    //class System;
    class Window;
    //class Listbox;
    //class ListboxItem;
    class GUIContext;
}

namespace sfutils
{
    namespace editor
    {
        class SpriteSheetSelector
        {
            public:
                SpriteSheetSelector(const SpriteSheetSelector&) = delete;
                SpriteSheetSelector& operator=(const SpriteSheetSelector&) = delete;

                SpriteSheetSelector();
                ~SpriteSheetSelector();

                bool setFile(const std::string& file);

                void setVisible(bool);

                void processEvents();
                void update(const sf::Time& deltaTime);
                void render();

            private:
                sf::RenderWindow _window;
                CEGUI::GUIContext* _context;

                std::unordered_map<std::string,sf::IntRect> _rect;
                std::string _imageFile;

        };
    }
}
#endif
