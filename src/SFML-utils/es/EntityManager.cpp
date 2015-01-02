#include <SFML-utils/es/EntityManager.hpp>
#include <algorithm>

namespace sfutils
{
    namespace es
    {
        EntityManager::EntityManager()
        {
            next_entity_id = Entity::invalidId;
        }

        Entity& EntityManager::create()
        {
            if(not _entities_free.empty())
            {
                Entity& e(_entities_free.front());
                _entities_free.pop_front();
                _entities.emplace_front(e);
            }
            else
            {
                _entities.emplace_front(this,++next_entity_id);
            }
            return _entities.front();
        }

        void EntityManager::remove(Entity& e)
        {
            auto it = std::find(_entities.begin(),_entities.end(),e);
            if(it != _entities.end())
            {
                _entities_free.emplace_front(e);
                _entities.remove(e);
            }
        }
    }
}
