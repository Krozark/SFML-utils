#ifndef SMFL_UTILS_GUI_FRAME_HPP
#define SMFL_UTILS_GUI_FRAME_HPP

#include <SFML-utils/gui/Container.hpp>
#include <SFML-utils/core/ActionTarget.hpp>


namespace sfutils
{
    namespace gui
    {
        class Frame : public Container, protected ActionTarget<int>
        {
            public:
                Frame(const Frame&) = delete;
                Frame& operator=(const Frame&) = delete;
                
                /**
                 * \Constructor
                 * \param window the window to dispaly in
                 * use sfutils::gui::Constructor::default_gui_inputs as Action map
                 */
                explicit Frame(sf::RenderWindow& window);

                /**
                 * \Constructor
                 * \param window the window to dispaly in
                 * \param map the ActionMap to use for events
                 */
                explicit Frame(sf::RenderWindow& window,const ActionMap<int>& map);

                virtual ~Frame();

                /**
                 * \brief check for real time events
                 */
                void processEvents();

                /**
                 * \brief check for polling events
                 * \param event event to compare
                 * \return true is the event as been used
                 */
                bool processEvent(const sf::Event& event);

                using ActionTarget<int>::FuncType;
                using ActionTarget::bind;
                using ActionTarget::unbind;

                /**
                 * \brief alias for window.draw(*this)
                 */
                void draw();

                /**
                 * \brief change the size of the frame.
                 * Default is window.getSize() or construction
                 */ 
                void setSize(const sf::Vector2f& size);

            protected:
                virtual sf::Vector2f getSize()const override;

            private:
                sf::RenderWindow& _window;
                sf::View _view;
                sf::Vector2f _size;


                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
                virtual void processEvents(const sf::Vector2f& parent_pos)override;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
