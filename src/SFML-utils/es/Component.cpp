#include <SFML-utils/es/Component.hpp>
#include <SFML-utils/es/Entity.hpp>


namespace sfutils
{
    namespace es
    {
        Family BaseComponent::_familyCounter = 0;

        BaseComponent::BaseComponent(Entity& owner) : _owner(owner)
        {
        }

        BaseComponent::~BaseComponent()
        {
        }

        Entity& BaseComponent::owner()const
        {
            return _owner;
        }
    }
}
