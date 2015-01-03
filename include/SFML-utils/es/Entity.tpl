#include <SFML-utils/es/EntityManager.hpp>

namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT, typename ... Args>
        void Entity::add(Args&& ... args)
        {
            _manager->addComponent<COMPONENT>(*this,args ...);    
        }

        template<typename COMPONENT>
        void Entity::remove()
        {
            _manager->removeComponent<COMPONENT>(*this);
        }

        inline std::uint32_t Entity::id()const
        {
            return _id;
        }
    }
}
