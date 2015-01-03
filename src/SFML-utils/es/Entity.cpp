#include <SFML-utils/es/Entity.hpp>
#include <SFML-utils/es/EntityManager.hpp>

namespace sfutils
{
    namespace es
    {
        Entity::Entity(EntityManager* manager,std::uint32_t id) : _id(id), _manager(manager)
        {
        }

        Entity::~Entity()
        {
            reset();
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

        void Entity::reset()
        {
            _manager->reset(*this);
        }
    }
}
