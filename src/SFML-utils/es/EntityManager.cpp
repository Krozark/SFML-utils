#include <SFML-utils/es/EntityManager.hpp>
#include <algorithm>

#include <SFML-utils/es/Entity.hpp>

namespace sfutils
{
    namespace es
    {
        EntityManager::EntityManager()
        {
        }

        EntityManager::~EntityManager()
        {
            reset();
        }

        Entity& EntityManager::create()
        {
            std::uint32_t index = 0;
            if(not _entities_index_free.empty())
            {
                //reuse existing entity
                index = _entities_index_free.front();
                _entities_index_free.pop_front();
            }
            else
            {
                //create new entity
                index = _entities_alocated.size();
                _entities_alocated.emplace_back(this,index);
            }
            _entities_index.emplace_front(index);
            return _entities_alocated[index];
        }

        void EntityManager::remove(Entity& e)
        {
            auto it = std::find(_entities_alocated.begin(),_entities_alocated.end(),e);
            if(it != _entities_alocated.end())
            {
                _entities_index_free.emplace_front(e._id);
                _entities_index.remove(e._id);

                e.reset();
            }
        }

        void EntityManager::reset()
        {
            _entities_index_free.clear();
            _entities_index.clear();
            _entities_alocated.clear();
        }
    }
}
