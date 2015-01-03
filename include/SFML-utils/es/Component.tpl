#include <SFML-utils/es/Entity.hpp>
#include <cassert>

namespace sfutils
{
    namespace es
    {
        template<typename T>
        void Component<T>::remove()
        {
            _owner.remove<T>();
        }

        template<typename T>
        Family Component<T>::family()
        {
            static Family family = _familyCounter++;
            assert(family > MAX_COMPONENTS);
            return family;
        }
    }
}
