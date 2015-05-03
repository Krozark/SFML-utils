#ifndef SMFL_UTILS_GUI_WIDGET_HPP
#define SMFL_UTILS_GUI_WIDGET_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    /**
     * \brief namespace that contain all the gui classes
     */
    namespace gui
    {
        /**
         * \brief A class representing any kind of widget
         */
        class Widget : public sf::Drawable
        {
            public:
                Widget(const Widget&) = delete;
                Widget& operator=(const Widget&) = delete;

                /**
                 * \brief The constructor
                 * \param parent the parent widget. Thit is use to automaticly delete
                 * all the widget attache to another one
                 */
                explicit Widget(Widget* parent=nullptr);
                virtual ~Widget();

                /**
                 * \brief Set the position of a widget relative to its parent
                 */
                void setPosition(const sf::Vector2f& pos);

                /**
                 * \brief Set the position of a widget relative to its parent
                 */
                void setPosition(float x,float y);

                /**
                 * \return the position of the widget relative to its parent
                 */
                const sf::Vector2f& getPosition()const;


                /**
                 * \brief hide a widget
                 */
                void hide();

                /**
                 * \return the hidden attribut
                 */
                bool isHidden()const;

                /**
                 * \brief Show the widget
                 */
                void show();

                /**
                 * \return the show attribut
                 */
                bool isVisible()const;

                /**
                 * \brief change the vilibility of the widget (hide to show or the reverse)
                 */
                void toggle();

            protected:
                friend class Containers;
                friend class VLayout;
                friend class HLayout;

                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos);
                virtual void processEvents(const sf::Vector2f& parent_pos);

                virtual void updateShape();

                /**
                 * \brief get the size on the widget
                 */
                virtual sf::Vector2f getSize()const = 0;

                Widget* _parent;
                sf::Vector2f _position;
                bool _isVisible;

            private:
        };
    }
}
#endif
