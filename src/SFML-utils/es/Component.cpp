#include <SFML-utils/es/Component.hpp>
#include <SFML-utils/es/Entity.hpp>


namespace sfutils
{
    namespace es
    {
        Family VComponent::_familyCounter = 0;

        VComponent::VComponent(Entity& owner) : _owner(owner)
        {
        }

        VComponent::~VComponent()
        {
        }

        Entity& VComponent::owner()const
        {
            return _owner;
        }
    }
}
