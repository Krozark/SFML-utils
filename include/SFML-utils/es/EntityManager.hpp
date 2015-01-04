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
        template<typename T> class ComponentHandle;
        class EntityManager
        {
            public:
                EntityManager(const EntityManager&) = delete;
                EntityManager& operator=(const EntityManager&) = delete;

                EntityManager();
                ~EntityManager();

                std::uint32_t create();
                void remove(std::size_t id);

                void reset();
                void reset(std::uint32_t id);

                bool isValid(std::uint32_t id);

                const Entity& get(std::size_t id)const;
                Entity& get(std::size_t id);

                template<typename COMPONENT,typename ... Args>
                void addComponent(std::uint32_t id,Args&& ... args);
                
                template<typename COMPONENT>
                void removeComponent(std::uint32_t id);

                template<typename COMPONENT>
                bool hasComponent(std::uint32_t id)const;

                template<typename COMPONENT>
                ComponentHandle<COMPONENT> getComponent(std::uint32_t id);

            private:
                std::vector<Entity> _entities_alocated;

                std::vector<std::bitset<MAX_COMPONENTS>> _entities_components_mask;
                std::vector<utils::memory::VPool*> _components_entities;

                std::forward_list<std::uint32_t> _entities_index;
                std::forward_list<std::uint32_t> _entities_index_free;

                template<typename COMPONENT>
                inline void checkComponent();

                template<typename> friend class ComponentHandle;

                template<typename COMPONENT>
                COMPONENT* getComponentPtr(std::uint32_t id);
        };
    }
}
#include <SFML-utils/es/EntityManager.tpl>
#endif
