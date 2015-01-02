#include <SFML-utils/es/Entity.hpp>
#include <SFML-utils/es/EntityManager.hpp>

namespace sfutils
{
    namespace es
    {
        const std::uint64_t Entity::invalidId = 0;
        
        Entity::Entity(EntityManager* manager,std::uint64_t id) : _id(id), _manager(manager)
        {
        }

        bool Entity::operator==(const Entity& other)const
        {
            return _id == other._id and _manager == other._manager;
        }

        bool Entity::operator!=(const Entity& other)const
        {
            return _id != other._id or _manager != other._manager;
        }

        void Entity::remove()
        {
            _manager->remove(*this);
        }

        bool Entity::isValid()const
        {
            return _id != invalidId;
        }
    }
}
