#include <SFML-utils/gui/event/ButtonPressed.hpp>

namespace sfutils
{
    namespace gui
    {
        namespace event
        {
            ButtonPressed::ButtonPressed(Button& owner) : _owner(owner)
            {
            }

            Button& ButtonPressed::getOwner()const
            {
                return _owner;
            }
        }
    }
}
