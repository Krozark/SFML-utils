#ifndef SFUTILS_COMPSKIN_HPP
#define SFUTILS_COMPSKIN_HPP

#include <SFML-utils/es/Component.hpp>

#include <SFML-utils/map/es/Entity.hpp>

namespace sfutils
{
namespace map
{
    struct CompSkinStatic : sfutils::es::Component<CompSkinStatic,MapEntity>
    {
        explicit CompSkinStatic(){};
        sf::Sprite _sprite; 
    };

    struct CompSkinDynamic : sfutils::es::Component<CompSkinDynamic,MapEntity>
    {
        explicit CompSkinDynamic(){};
        sfutils::AnimatedSprite _sprite; 
    };
}
}
#endif
