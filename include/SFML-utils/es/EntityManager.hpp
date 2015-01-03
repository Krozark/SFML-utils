#ifndef SFUTILS_ES_ENTITYMANAGER_HPP
#define SFUTILS_ES_ENTITYMANAGER_HPP

#include <forward_list>
#include <vector>
#include <bitset>
#include <cstdint>
#include <utils/memory.hpp>

#include <SFML-utils/es/defines.hpp>

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
                void remove(std::size_t id);

                const Entity& get(std::size_t id)const;
                Entity& get(std::size_t id);

                template<typename COMPONENT,typename ... Args>
                void addComponent(Entity& e,Args&& ... args);
                
                template<typename COMPONENT>
                void removeComponent(Entity& e);

                void reset();
                void reset(Entity& e);
                
            private:
                std::vector<Entity> _entities_alocated;

                std::vector<std::bitset<MAX_COMPONENTS>> _entities_components_mask;
                std::vector<utils::memory::VPool*> _components_entities;

                std::forward_list<std::uint32_t> _entities_index;
                std::forward_list<std::uint32_t> _entities_index_free;

                template<typename COMPONENT>
                inline void checkComponent();
        };
    }
}
#include <SFML-utils/es/EntityManager.tpl>
#endif
