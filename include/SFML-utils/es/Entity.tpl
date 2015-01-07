#include <SFML-utils/es/EntityManager.hpp>

namespace sfutils
{
    namespace es
    {
        inline std::uint32_t Entity::id()const
        {
            return _id;
        }
        
        template<typename COMPONENT, typename ... Args>
        inline void Entity::add(Args&& ... args)
        {
            _manager->addComponent<COMPONENT>(_id,std::forward<Args>(args)...);    
        }

        template<typename COMPONENT>
        inline void Entity::remove()
        {
            _manager->removeComponent<COMPONENT>(_id);
        }

        template<typename COMPONENT>
        inline bool Entity::has()
        {
            return _manager->hasComponent<COMPONENT>(_id);
        }

        template<typename COMPONENT>
        inline ComponentHandle<COMPONENT> Entity::component()
        {
            return _manager->getComponent<COMPONENT>(_id);
        }

        template<typename ... COMPONENT>
        inline std::tuple<ComponentHandle<COMPONENT>...> Entity::components()
        {
            return _manager->getComponents<COMPONENT ...>(_id);
        }

    }
}
