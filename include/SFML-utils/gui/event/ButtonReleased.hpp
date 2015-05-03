#ifndef SFUTILS_GUI_EVENT_BUTTONRELEASED_HPP
#define SFUTILS_GUI_EVENT_BUTTONRELEASED_HPP

#include <utils/event/Event.hpp>

namespace sfutils
{
    namespace gui
    {
        class Button;

        namespace event
        {
            /**
             * \brief Event trigger whene a button is released
             */
            class ButtonReleased : public utils::event::Event<ButtonReleased>
            {
                public:
                    /**
                     * \brief Constructor
                     * \param owner the source of the event
                     */
                    explicit ButtonReleased(Button& owner);

                    /**
                     * \return the source of the event
                     */
                    Button& getOwner()const;
                private:
                    Button& _owner;
            };
        }
    }
}
#endif
