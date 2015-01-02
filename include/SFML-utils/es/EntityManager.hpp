#ifndef SFUTILS_ES_ENTITYMANAGER_HPP
#define SFUTILS_ES_ENTITYMANAGER_HPP

#include <forward_list>
#include <SFML-utils/es/Entity.hpp>

namespace sfutils
{
    namespace es
    {
        class EntityManager
        {
            public:
                EntityManager();
                EntityManager(const EntityManager&) = delete;
                EntityManager& operator=(const EntityManager&) = delete;

                Entity& create();
                void remove(Entity& e);
                
            private:
                std::forward_list<Entity> _entities;
                std::forward_list<Entity> _entities_free;

                static std::uint64_t next_entity_id;
        };
    }
}
#endif
