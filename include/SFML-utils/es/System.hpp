#ifndef SFUTILS_ES_SYSTEM_HPP
#define SFUTILS_ES_SYSTEM_HPP

#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {

        class BaseSystem
        {
            public:
                BaseSystem(const BaseSystem&) = delete;
                BaseSystem& operator=(const BaseSystem&) = delete;

                BaseSystem();
                virtual ~BaseSystem();

                virtual void update(float deltaTime) = 0;
            protected:
                static Family _familyCounter;

            private:
        };

        template<typename T>
        class System : public BaseSystem
        {
            public:
                System(const System&) = delete;
                System& operator=(const System&) = delete;

                using BaseSystem::BaseSystem;
                
                static Family family();
        };
    }
}
#include <SFML-utils/es/System.tpl>
#endif
