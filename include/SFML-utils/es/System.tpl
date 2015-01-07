#include <cassert>

namespace sfutils
{
    namespace es
    {
        ///////////////// SYSTEM ///////////////
        template<typename COMPONENT>
        System<COMPONENT>::System()
        {
        }

        template<typename COMPONENT>
        System<COMPONENT>::~System()
        {
        }

        template<typename COMPONENT>
        Family System<COMPONENT>::family()
        {
            static Family family = _familyCounter++;
            assert(family < MAX_COMPONENTS);
            return family;
        }

        ///////////////// SYSTEM MANAGER ///////////////
        
        template<typename SYSTEM>
        bool SystemManager::add(std::shared_ptr<SYSTEM> ptr)
        {
            if(_systems.count(SYSTEM::family()) == 0)
            {
                _systems.insert(std::make_pair(SYSTEM::family(),ptr));
                return true;
            }
            return false;
        }

        template<typename SYSTEM,typename ... Args>
        bool SystemManager::add(Args&& ... args)
        {
            if(_systems.count(SYSTEM::family()) == 0)
            {
                _systems.emplace(SYSTEM::family(),std::shared_ptr<SYSTEM>(new SYSTEM(std::forward<Args>(args)...)));
                return true;
            }
            return false;
        }
        
        template<typename SYSTEM>
        bool SystemManager::remove()
        {
            if(_systems.count(SYSTEM::family()) == 0)
                return false;
            _systems.erase(SYSTEM::family());
            return true;
        }

        template<typename SYSTEM>
        inline std::shared_ptr<SYSTEM> SystemManager::system()
        {
            return std::static_pointer_cast<SYSTEM>(_systems.at(SYSTEM::family()));
        }

        template<typename SYSTEM>
        inline void SystemManager::update(float deltaTime)
        {
            system<SYSTEM>()->update(_manager,deltaTime);
        }
    }
}
