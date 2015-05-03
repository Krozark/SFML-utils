#include <SFML-utils/gui/event/ButtonReleased.hpp>

namespace sfutils
{
    namespace gui
    {
        namespace event
        {
            
            ButtonReleased::ButtonReleased(Button& owner) : _owner(owner)
            {
            }

            Button& ButtonReleased::getOwner()const
            {
                return _owner;
            }

        }
    }
}
