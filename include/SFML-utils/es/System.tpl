#include <cassert>

namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT>
        Family System<COMPONENT>::family()
        {
            static Family family = _familyCounter++;
            assert(family > MAX_COMPONENTS);
            return family;
        }
    }
}
