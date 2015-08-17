#ifndef SFUTILS_COMPSKIN_HPP
#define SFUTILS_COMPSKIN_HPP

#include <SFML-utils/ES.hpp>

#include <SFML-utils/map/MapEntity.hpp>

namespace sfutils
{
namespace map
{
    struct CompSkinStatic : sfutils::Component<CompSkinStatic,MapEntity>
    {
        explicit CompSkinStatic(){};
        sf::Sprite _sprite; 
    };

    struct CompSkinDynamic : sfutils::Component<CompSkinDynamic,MapEntity>
    {
        explicit CompSkinDynamic(){};
        sfutils::AnimatedSprite _sprite; 
    };
}
}
#endif
