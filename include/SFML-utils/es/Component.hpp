#ifndef SFUTILS_ES_COMPONENT_HPP
#define SFUTILS_ES_COMPONENT_HPP

#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {
        class Entity;

        class BaseComponent
        {

            public:
                BaseComponent(Entity& owner);
                virtual ~BaseComponent();

                Entity& owner()const;

            protected:
                static Family _familyCounter;

            private:
                Entity& _owner;
        };

        template<typename T>
        class Component : public BaseComponent
        {
            public:
                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;
                
                using BaseComponent::BaseComponent;

                void remove();
                static Family family();
        };
    }
}
#include <SFML-utils/es/Component.tpl>
#endif
