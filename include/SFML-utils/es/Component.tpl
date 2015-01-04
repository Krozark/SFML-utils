#include <SFML-utils/es/EntityManager.hpp>
#include <cassert>

namespace sfutils
{
    namespace es
    {
        //////////////// COMPONENT HANDLE ///////////////

        template<typename COMPONENT>
        inline bool ComponentHandle<COMPONENT>::isValid()const
        {
            return _manager and _manager->isValid(_entity_id) and _manager->hasComponent<COMPONENT>(_entity_id);
        }

        template<typename COMPONENT>
        ComponentHandle<COMPONENT>::ComponentHandle() : _manager(nullptr)
        {
        }

        template<typename COMPONENT>
        ComponentHandle<COMPONENT>::ComponentHandle(EntityManager* manager,std::uint32_t entity_id) : _manager(manager), _entity_id(entity_id)
        {
        }

        template<typename COMPONENT>
        inline COMPONENT* ComponentHandle<COMPONENT>::get()
        {
            assert(isValid());
            return _manager->getComponentPtr<COMPONENT>(_entity_id);
        }

        template<typename COMPONENT>
        inline const COMPONENT* ComponentHandle<COMPONENT>::get()const
        {
            assert(isValid());
            return _manager->getComponentPtr<COMPONENT>(_entity_id);
        }

        template<typename COMPONENT>
        inline COMPONENT* ComponentHandle<COMPONENT>::operator->()
        {
            assert(isValid());
            return _manager->getComponentPtr<COMPONENT>(_entity_id);
        }

        template<typename COMPONENT>
        inline const COMPONENT* ComponentHandle<COMPONENT>::operator->()const
        {
            assert(isValid());
            return _manager->getComponentPtr<COMPONENT>(_entity_id);
        }

        ////////////////// COMPONENT //////////////////
        template<typename COMPONENT>
        Component<COMPONENT>::Component()
        {
        }

        template<typename COMPONENT>
        inline void Component<COMPONENT>::remove()
        {
            _manager->removeComponent<COMPONENT>(_owner_id);
        }


        template<typename COMPONENT>
        Family Component<COMPONENT>::family()
        {
            static Family family = _familyCounter++;
            assert(family < MAX_COMPONENTS);
            return family;
        }
        
    }
}
