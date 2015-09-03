#ifndef SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP
#define SFUTILS_EDITOR_SPRITESHEETSELECTOR_HPP

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

                void processEvents();
                void update(const sf::Time& deltaTime);
                void render(sfg::SFGUI& sfgui);

            private:
                sf::RenderWindow _window;

        };
    }
}
#endif
