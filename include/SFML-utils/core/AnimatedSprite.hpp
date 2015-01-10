#ifndef SFUTILS_ANIMATEDSPRITE_HPP
#define SFUTILS_ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace sfutils
{
    class Animation;
    class AnimatedSprite : public sf::Drawable, public sf::Transformable
    {
        public:
            AnimatedSprite(const AnimatedSprite&) = delete;
            AnimatedSprite& operator=(const AnimatedSprite&) = delete;

            enum Status
            {
                Stopped,
                Paused,
                Playing
            };

            AnimatedSprite(Animation* animation = nullptr,sf::Time deltaTime = sf::seconds(0.2),bool loop = true,Status status= Playing);

            void setAnimation(Animation* animation);
            Animation* getAnimation()const;

            void setFrameTime(sf::Time deltaTime);
            sf::Time getFrameTime()const;

            void setLoop(bool loop);
            bool getLoop()const;

            void play();
            void pause();
            void stop();

            Status getStatus()const;

            void setFrame(size_t index);


            void setColor(const sf::Color& color);

            void update(const sf::Time& deltaTime);

        private:
            Animation* _animation;
            sf::Time _delta;
            sf::Time _elapsed;
            bool _loop;
            Status _status;
            size_t _currentFrame;
            sf::Vertex _vertices[4];

            void setFrame(size_t index,bool resetTime);

            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    };
}
#endif
