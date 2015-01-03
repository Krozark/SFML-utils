#ifndef SFUTILS_ES_SYSTEM_HPP
#define SFUTILS_ES_SYSTEM_HPP

#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {

        class VSystem
        {
            public:
                VSystem(const VSystem&) = delete;
                VSystem& operator=(const VSystem&) = delete;

                VSystem();
                virtual ~VSystem();

                virtual void update(float deltaTime) = 0;
            protected:
                static Family _familyCounter;

            private:
        };

        template<typename COMPONENT>
        class System : public VSystem
        {
            public:
                System(const System&) = delete;
                System& operator=(const System&) = delete;

                using VSystem::VSystem;
                
                static Family family();
        };
    }
}
#include <SFML-utils/es/System.tpl>
#endif
