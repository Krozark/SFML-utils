#ifndef SFUTILS_ANIMATEDSPRITE_HPP
#define SFUTILS_ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <functional>

namespace sfutils
{
    class Animation;
    class AnimatedSprite : public sf::Drawable, public sf::Transformable
    {
        public:
            AnimatedSprite(const AnimatedSprite&) = default;
            AnimatedSprite& operator=(const AnimatedSprite&) = default;

            AnimatedSprite(AnimatedSprite&&) = default;
            AnimatedSprite& operator=(AnimatedSprite&&) = default;

            using FuncType = std::function<void(AnimatedSprite& self)>;
            static FuncType defaultFunc;

            enum Status
            {
                Stopped,
                Paused,
                Playing
            };

            AnimatedSprite(Animation* animation = nullptr,Status status= Playing,sf::Time deltaTime = sf::seconds(0.15),bool loop = true);

            void setAnimation(Animation* animation);
            Animation* getAnimation()const;

            void setFrameTime(sf::Time deltaTime);
            sf::Time getFrameTime()const;

            void setLoop(bool loop);
            bool getLoop()const;

            void play();
            void pause();
            void stop();

            FuncType on_finished;

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
