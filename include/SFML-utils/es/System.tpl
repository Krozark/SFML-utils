#include <cassert>

namespace sfutils
{
    namespace es
    {
        template<typename T>
        Family System<T>::family()
        {
            static Family family = _familyCounter++;
            assert(family > MAX_COMPONENTS);
            return family;
        }
    }
}
