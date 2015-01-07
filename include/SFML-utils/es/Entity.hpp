#ifndef SFUTILS_ES_ENTITY_HPP
#define SFUTILS_ES_ENTITY_HPP

#include <cstdint>
#include <tuple>
#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {

        class EntityManager;
        template<typename T> class Component;
        template<typename T> class ComponentHandle;
        class Entity
        {
            public:
                Entity(Entity&&) = default;
                Entity& operator=(Entity&&) = default;

                Entity(EntityManager* manager,std::uint32_t id);
                ~Entity() ;

                std::uint32_t id()const;

                bool operator==(const Entity& other)const;
                bool operator!=(const Entity& other)const;

                void remove();
                void reset();

                template<typename COMPONENT,typename ... Args>
                void add(Args&& ... args);

                template<typename COMPONENT>
                void remove();

                template<typename COMPONENT>
                bool has();

                template<typename COMPONENT>
                ComponentHandle<COMPONENT> component();

                template<typename ... COMPONENT>
                std::tuple<ComponentHandle<COMPONENT>...> components();

            private:
                std::uint32_t _id;    
                EntityManager* _manager;
        };
    }
}
#include <SFML-utils/es/Entity.tpl>
#endif
