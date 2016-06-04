#ifndef SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP
#define SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <SFML-utils/core/ResourceManager.hpp>



/*namespace CEGUI
{
    //class OpenGLRenderer;
    //class System;
    class Window;
    //class Listbox;
    //class ListboxItem;
    class GUIContext;
}*/

namespace sfutils
{
    namespace editor
    {
        class Editor;
        class SpriteSheetSelector
        {
            public:
                SpriteSheetSelector(const SpriteSheetSelector&) = delete;
                SpriteSheetSelector& operator=(const SpriteSheetSelector&) = delete;

                SpriteSheetSelector(Editor& owner);
                ~SpriteSheetSelector();

                bool setFile(const std::string& file,sfutils::ResourceManager<sf::Texture,std::string>& textureManager);

                void setVisible(bool);

                void processEvents();
                void update(const sf::Time& deltaTime);
                void render();

            private:
                Editor& _owner;
                sf::RenderWindow _window;
                //CEGUI::GUIContext* _context;

                sf::Sprite _background;

                std::unordered_map<std::string,sf::IntRect> _rect;
                std::string _imageFile;

        };
    }
}
#endif
