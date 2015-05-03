#ifndef SFUTILS_GUI_EVENT_BUTTONPRESSED_HPP
#define SFUTILS_GUI_EVENT_BUTTONPRESSED_HPP

#include <utils/event/Event.hpp>

namespace sfutils
{
    namespace gui
    {
        class Button;

        /**
         * \brief namespace that contain all the events
         */
        namespace event
        {
            /**
             * \brief Event trigger whene a button is pressed
             */
            class ButtonPressed : public utils::event::Event<ButtonPressed>
            {
                public:
                    /**
                     * \brief Constructor
                     * \param owner the source of the event
                     */
                    explicit ButtonPressed(Button& owner);

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
