#ifndef SFUTILS_MAPENTITY_HPP
#define SFUTILS_MAPENTITY_HPP

#include <SFML-utils/es/EntityManager.hpp>
#include <SFML-utils/es/Entity.hpp>

#include <SFML-utils/Core.hpp>

namespace sfutils
{
namespace map
{
    class MapEntity : public sfutils::es::Entity<MapEntity>, public sf::Drawable
    {

        public:
            MapEntity(const MapEntity&) = delete;
            MapEntity& operator=(const MapEntity&) = delete;

            MapEntity(sfutils::es::EntityManager<MapEntity>* manager,std::uint32_t id);

            sf::Vector2f getPosition()const;
            void setPosition(const sf::Vector2f& pos);

        private:
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    };
}

}
#endif
