#ifndef SFUTILS_ES_SYSTEM_HPP
#define SFUTILS_ES_SYSTEM_HPP

#include <SFML-utils/es/defines.hpp>
#include <memory>
#include <unordered_map>

namespace sfutils
{
    namespace es
    {
        class EntityManager;

        class VSystem
        {
            public:
                VSystem(const VSystem&) = delete;
                VSystem& operator=(const VSystem&) = delete;

                virtual ~VSystem();

                virtual void update(EntityManager& entity_manager,float deltaTime) = 0;
            protected:
                VSystem();

                static Family _familyCounter;

            private:
        };

        template<typename COMPONENT>
        class System : public VSystem
        {
            public:
                System(const System&) = delete;
                System& operator=(const System&) = delete;

                System();
                virtual ~System();

                static Family family();
        };


        class SystemManager
        {
            public:
                SystemManager(const SystemManager&) = delete;
                SystemManager& operator=(const SystemManager&) = delete;

                SystemManager(EntityManager& manager);
                ~SystemManager();

                template<typename SYSTEM>
                bool add(std::shared_ptr<SYSTEM> ptr);

                template<typename SYSTEM,typename ... Args>
                bool add(Args&& ... args);

                template<typename SYSTEM>
                bool remove();
                
                template<typename SYSTEM>
                std::shared_ptr<SYSTEM> system();

                template<typename SYSTEM>
                void update(float deltaTime);

                void updateAll(float deltaTime);
                
                
            private:
                EntityManager& _manager;
                std::unordered_map<Family,std::shared_ptr<VSystem>> _systems;
        };
    }
}
#include <SFML-utils/es/System.tpl>
#endif
