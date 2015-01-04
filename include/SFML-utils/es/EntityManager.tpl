#include <SFML-utils/es/Component.hpp>
#include <SFML-utils/es/Entity.hpp>
#include <cassert>
namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT,typename ... Args>
        void EntityManager::addComponent(std::uint32_t id,Args&& ... args)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(not _entities_components_mask[id].test(family));

            auto pool = static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family]);
            pool->emplace(id,args...);

            pool->at(id)._owner_id = id;
            pool->at(id)._manager = this;

            _entities_components_mask[id].set(family);
        }
        
        template<typename COMPONENT>
        void EntityManager::removeComponent(std::uint32_t id)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(_entities_components_mask[id].test(family));

            static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->erase(id);

            _entities_components_mask[id].reset(family);
        }

        template<typename COMPONENT>
        inline bool EntityManager::hasComponent(std::uint32_t id)const
        {
            Family family = COMPONENT::family();
            return _entities_components_mask.at(id).test(family);
        }

        template<typename COMPONENT>
        inline ComponentHandle<COMPONENT> EntityManager::getComponent(std::uint32_t id)
        {
            if(hasComponent<COMPONENT>(id))
                return ComponentHandle<COMPONENT>(this,id);
            return ComponentHandle<COMPONENT>();
        }

        template<typename COMPONENT>
        inline COMPONENT* EntityManager::getComponentPtr(std::uint32_t id)
        {
            Family family = COMPONENT::family();
            return &static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->at(id);
        }


        template<typename COMPONENT>
        inline void EntityManager::checkComponent()
        {
            Family family = COMPONENT::family();
            //resize
            if( _components_entities.size() <= family)
                _components_entities.resize(family+1,nullptr);
            //check Pool validity
            if(_components_entities[family] == nullptr)
            {
                auto pool = new utils::memory::Pool<COMPONENT>;
                pool->resize(_entities_alocated.size());
                _components_entities[family] = pool;
            }
        }
    }
}
