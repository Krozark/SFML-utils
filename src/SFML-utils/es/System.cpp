#include <SFML-utils/es/System.hpp>

namespace sfutils
{
    namespace es
    {
        ///////////////// Virtual SYSTEM ///////////////
        Family VSystem::_familyCounter = 0;

        VSystem::VSystem()
        {
        }

        VSystem::~VSystem()
        {
        }


        ///////////////// SYSTEM MANAGER ///////////////
        SystemManager::SystemManager(EntityManager& manager) : _manager(manager)
        {
        }

        SystemManager::~SystemManager()
        {
        }

        void SystemManager::updateAll(float deltaTime)
        {
            for(auto& pair : _systems)
                pair.second->update(_manager,deltaTime);
        }
    }
}
