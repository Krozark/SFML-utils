#include <SFML-utils/es/Entity.hpp>
#include <cassert>

namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT>
        void Component<COMPONENT>::remove()
        {
            _owner.remove<COMPONENT>();
        }

        template<typename COMPONENT>
        Family Component<COMPONENT>::family()
        {
            static Family family = _familyCounter++;
            assert(family > MAX_COMPONENTS);
            return family;
        }
    }
}
