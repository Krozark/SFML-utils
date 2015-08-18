#include <SFML-utils/map/es/Entity.hpp>

#include <cassert>

#include <SFML-utils/map/es/Components.hpp>

namespace sfutils
{
namespace map
{
    
    Entity::Entity(sfutils::es::EntityManager<Entity>* manager,std::uint32_t id) : sfutils::es::Entity<Entity>(manager,id)
    {
    }

    sf::Vector2f Entity::getPosition()const
    {
        sf::Vector2f res;
        if(has<CompSkinStatic>())
            res = component<CompSkinStatic>()->_sprite.getPosition();
        else if(has<CompSkinDynamic>())
            res = component<CompSkinDynamic>()->_sprite.getPosition();

        return res;
    }

    void Entity::setPosition(const sf::Vector2f& pos)
    {
        if(has<CompSkinStatic>())
            component<CompSkinStatic>()->_sprite.setPosition(pos);
        else if(has<CompSkinDynamic>())
            component<CompSkinDynamic>()->_sprite.setPosition(pos);
        //TODO cache the position
    }

    void Entity::draw(sf::RenderTarget& target,sf::RenderStates states)const
    {
        if(has<CompSkinStatic>())
            target.draw(component<CompSkinStatic>()->_sprite,states);
        else if(has<CompSkinDynamic>())
            target.draw(component<CompSkinDynamic>()->_sprite,states);

        /*CompHp::Handle hp = component<CompHp>();
        if(hp.isValid())
        {
            hp->draw(target,states);
        }*/
    }
}
}
