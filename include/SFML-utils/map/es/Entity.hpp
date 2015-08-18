#ifndef SFUTILS_MAP_ENTITY_HPP
#define SFUTILS_MAP_ENTITY_HPP

#include <SFML-utils/es/EntityManager.hpp>
#include <SFML-utils/es/Entity.hpp>

#include <SFML-utils/Core.hpp>

namespace sfutils
{
namespace map
{
    class Entity : public sfutils::es::Entity<Entity>, public sf::Drawable
    {

        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(sfutils::es::EntityManager<Entity>* manager,std::uint32_t id);

            sf::Vector2f getPosition()const;
            void setPosition(const sf::Vector2f& pos);

        private:
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    };
}

}
#endif
