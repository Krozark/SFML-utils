#include <SFML-utils/map/MapEntity.hpp>

#include <cassert>

#include <SFML-utils/map/CompSkin.hpp>

namespace sfutils
{
namespace map
{
    
    MapEntity::MapEntity(sfutils::es::EntityManager<MapEntity>* manager,std::uint32_t id) : sfutils::es::Entity<MapEntity>(manager,id)
    {
    }

    sf::Vector2f MapEntity::getPosition()const
    {
        if(has<CompSkinStatic>())
            return component<CompSkinStatic>()->_sprite.getPosition();
        else if(has<CompSkinDynamic>())
            return component<CompSkinDynamic>()->_sprite.getPosition();

        assert(false and "Should never apear");
        return {0,0};
    }

    void MapEntity::setPosition(const sf::Vector2f& pos)
    {
        if(has<CompSkinStatic>())
            component<CompSkinStatic>()->_sprite.setPosition(pos);
        else if(has<CompSkinDynamic>())
            component<CompSkinDynamic>()->_sprite.setPosition(pos);
    }

    void MapEntity::draw(sf::RenderTarget& target,sf::RenderStates states)const
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
