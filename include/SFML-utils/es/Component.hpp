#ifndef SFUTILS_ES_COMPONENT_HPP
#define SFUTILS_ES_COMPONENT_HPP

#include <SFML-utils/es/defines.hpp>
#include <cstdint>

namespace sfutils
{
    namespace es
    {
        class EntityManager;
        
        template<typename COMPONENT>
        class ComponentHandle
        {
            public:
                ComponentHandle();

                bool isValid()const;

                COMPONENT* get();
                const COMPONENT* get()const;

                COMPONENT* operator->();
                const COMPONENT* operator->()const;

            private:
                friend class EntityManager;

                ComponentHandle(EntityManager* manager,std::uint32_t entity_id);

                EntityManager* _manager;
                std::uint32_t _entity_id;    

                //friend void setEntyId<COMPONENT>(std::uint32_t,ComponentHandle&);
        };

        class VComponent
        {

            public:
                virtual ~VComponent();

                std::uint32_t ownerId()const;

            protected:
                static Family _familyCounter;
                VComponent();

            private:
                friend class EntityManager;
                EntityManager* _manager;
                std::uint32_t _owner_id;    
        };

        template<typename COMPONENT>
        class Component : public VComponent
        {
            public:
                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;

                Component();
                virtual ~Component();
                
                void remove();
                static Family family();

                typedef ComponentHandle<COMPONENT> Handle;
        };

    }
}
#include <SFML-utils/es/Component.tpl>
#endif
