#ifndef SFUTILS_MAP_SYSTEMS_HPP
#define SFUTILS_MAP_SYSTEMS_HPP

#include <SFML-utils/es/EntityManager.hpp>
#include <SFML-utils/es/System.hpp>

#include <SFML-utils/map/es/Entity.hpp>

namespace sfutils
{
namespace map
{
    class SysSkinDynamic : public sfutils::es::System<SysSkinDynamic,Entity>
    {
        public:
            explicit SysSkinDynamic();
            virtual ~SysSkinDynamic();
            virtual void update(sfutils::es::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };
}
}

#endif
