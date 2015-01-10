#ifndef SFUTILS_ANIMATION_HPP
#define SFUTILS_ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

namespace sfutils
{
    class Animation
    {
        public:
            Animation(const Animation&) = delete;
            Animation& operator=(const Animation&) = delete;

            Animation(sf::Texture* texture=nullptr);
            ~Animation();

            void setTexture(sf::Texture* texture);
            void addFrame(const sf::IntRect& rect);
            void addFramesLine(int number_x,int number_y,int line);
            void addFramesColumn(int number_x,int number_y,int column);

            size_t size()const;
            const sf::IntRect& getRect(size_t index)const;

        private:
            friend class AnimatedSprite;
            std::vector<sf::IntRect> _frames;
            sf::Texture* _texture;

    };
}
#endif
