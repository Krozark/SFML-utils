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

        std::uint32_t EntityManager::create()
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
                index = _entities_allocated.size();
                _entities_allocated.emplace_back(this,index);

                _entities_components_mask.emplace_back();

                //resize components
                auto comp_size = _components_entities.size();
                for(std::size_t i=0;i<comp_size;++i)
                {
                    if(_components_entities[i] != nullptr)
                        _components_entities[i]->resize(index+1);
                }

            }
            _entities_index.emplace_front(index);

            return index;

        }


        void EntityManager::remove(std::size_t id)
        {
            Entity& e = _entities_allocated.at(id);
            auto it = std::find(_entities_allocated.begin(),_entities_allocated.end(),e);
            if(it != _entities_allocated.end())
            {
                _entities_index_free.emplace_front(id);
                _entities_index.remove(id);

                reset(id);
            }
        }

        const Entity& EntityManager::get(std::size_t id) const
        {
            return _entities_allocated.at(id);
        }

        Entity& EntityManager::get(std::size_t id)
        {
            return _entities_allocated.at(id);
        }

        void EntityManager::reset()
        {
            _entities_index_free.clear();
            _entities_index.clear();

            _entities_allocated.clear();
            _entities_components_mask.clear();
        }

        void EntityManager::reset(std::uint32_t id)
        {
            _entities_components_mask.at(id).reset();
        }

        bool EntityManager::isValid(std::uint32_t id)
        {
            return id < _entities_allocated.size();
        }

        std::forward_list<std::uint32_t>::const_iterator EntityManager::begin()const
        {
            return _entities_index.cbegin();
        }

        std::forward_list<std::uint32_t>::const_iterator EntityManager::end()const
        {
            return _entities_index.cend();
        }
    }
}
