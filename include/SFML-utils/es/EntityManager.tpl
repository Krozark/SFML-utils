#include <SFML-utils/es/Entity.hpp>
namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT,typename ... Args>
        void EntityManager::addComponent(Entity& e,Args&& ... args)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();
            static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->emplace(e.id(),args...);
        }
        
        template<typename COMPONENT>
        void EntityManager::removeComponent(Entity& e)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();
            static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->erase(e.id());
        }

        template<typename COMPONENT>
        void EntityManager::checkComponent()
        {
            Family family = COMPONENT::family();
            //resize
            if( _components_entities.size() < family)
                _components_entities.resize(family+1,nullptr);
            //check Pool validity
            if(_components_entities[family] == nullptr)
            {
                auto pool = new utils::memory::Pool<COMPONENT>;
                pool.resize(_entities_alocated.size());
                _components_entities[family] = pool;
            }
        }
    }
}
