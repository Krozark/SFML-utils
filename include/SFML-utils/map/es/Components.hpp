#ifndef SFUTILS_MAP_COMPSKIN_HPP
#define SFUTILS_MAP_COMPSKIN_HPP

#include <SFML-utils/es/Component.hpp>

#include <SFML-utils/map/es/Entity.hpp>

namespace sfutils
{
namespace map
{
    struct CompSkinStatic : sfutils::es::Component<CompSkinStatic,Entity>
    {
        explicit CompSkinStatic(){};
        sf::Sprite _sprite; 
    };

    struct CompSkinDynamic : sfutils::es::Component<CompSkinDynamic,Entity>
    {
        explicit CompSkinDynamic(sfutils::Animation* animation = nullptr,
                                 sfutils::AnimatedSprite::Status status= sfutils::AnimatedSprite::Status::Playing,
                                 const sf::Time& deltaTime = sf::seconds(0.15),
                                 bool loop = true,
                                 int repeat=0) :
            _sprite(animation,status,deltaTime,loop,repeat)
        {
        };

        sfutils::AnimatedSprite _sprite; 
    };
}
}
#endif
