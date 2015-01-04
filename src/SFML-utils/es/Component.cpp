#include <SFML-utils/es/Component.hpp>

namespace sfutils
{
    namespace es
    {
        Family VComponent::_familyCounter = 0;

        VComponent::VComponent() : _manager(nullptr), _owner_id(-1)
        {
        }

        VComponent::~VComponent()
        {
        }

        std::uint32_t VComponent::ownerId()const
        {
            return _owner_id;
        }
    }
}
