#ifndef SFML_UTILS_GUI_BUTTON_HPP
#define SFML_UTILS_GUI_BUTTON_HPP

#include <utils/event/Emitter.hpp>

#include <SFML-utils/gui/Widget.hpp>
#include <SFML-utils/gui/event/ButtonPressed.hpp>
#include <SFML-utils/gui/event/ButtonReleased.hpp>


namespace sfutils
{
    namespace gui
    {
        class Button : virtual public Widget, public utils::event::Emitter<event::ButtonPressed>, public utils::event::Emitter<event::ButtonReleased>
        {
            public:
                Button(const Button&) = delete;
                Button& operator=(const Button&) = delete;

                Button(Widget* parent=nullptr);
                virtual ~Button();

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;

                virtual void onMouseEntered();
                virtual void onMouseLeft();

            private:

                enum Status {
                    Hover = 1
                };
                int _status;
        };
    }
}
#endif
