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

                using ActionTarget<int>::FuncType;
                
                Frame(sf::RenderWindow& window,const ActionMap<int>& map);

                virtual ~Frame();


                void processEvents();
                bool processEvent(const sf::Event& event);

                void bind(int key,const FuncType& callback);
                void unbind(int key);

                void draw();

                virtual sf::Vector2f getSize()const override;

            private:
                sf::RenderWindow& _window;
                sf::View _view;


                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
                virtual void processEvents(const sf::Vector2f& parent_pos)override;
        };
    }
}
#endif
