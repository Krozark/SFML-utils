#ifndef SFUTILS_ES_COMPONENT_HPP
#define SFUTILS_ES_COMPONENT_HPP

#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {
        class Entity;

        class VComponent
        {

            public:
                VComponent(Entity& owner);
                virtual ~VComponent();

                Entity& owner()const;

            protected:
                static Family _familyCounter;

            private:
                Entity& _owner;
        };

        template<typename COMPONENT>
        class Component : public VComponent
        {
            public:
                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;
                
                using VComponent::VComponent;

                void remove();
                static Family family();
        };
    }
}
#include <SFML-utils/es/Component.tpl>
#endif
