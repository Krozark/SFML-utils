#include <SFML-utils/es/EntityManager.hpp>

namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT_TYPE, typename ... Args>
        void Entity::add(Args&& ... args)
        {
            _manager->addComponent<COMPONENT_TYPE>(args ...);    
        }

        template<typename COMPONENT_TYPE>
        void Entity::remove()
        {
        }
    }
}
