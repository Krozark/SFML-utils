#ifndef SFUTILS_ES_ENTITYMANAGER_HPP
#define SFUTILS_ES_ENTITYMANAGER_HPP

#include <forward_list>
#include <vector>
#include <cstdint>

namespace sfutils
{
    namespace es
    {
        class Entity;
        class EntityManager
        {
            public:
                EntityManager(const EntityManager&) = delete;
                EntityManager& operator=(const EntityManager&) = delete;

                EntityManager();
                ~EntityManager();

                Entity& create();
                void remove(Entity& e);

                template<typename COMPONENT_TYPE,typename ... Args>
                void addComponent(Entity& e,Args&& ... args);

                void reset();
                
            private:
                std::vector<Entity> _entities_alocated;
                std::forward_list<std::uint32_t> _entities_index;
                std::forward_list<std::uint32_t> _entities_index_free;
        };
    }
}
#endif
