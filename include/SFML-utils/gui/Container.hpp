#ifndef SMFL_UTILS_GUI_CONTAINER_HPP
#define SMFL_UTILS_GUI_CONTAINER_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        class Layout;

        /**
         * \brief Class representing a basic container
         */
        class Container  : virtual public Widget
        {
            public:
                Container(const Container&) = delete;
                Container& operator=(const Container&) = delete;

                /**
                 * \brief Constructor
                 * \param parent parent Widget
                 */
                explicit Container(Widget* parent=nullptr);
                virtual ~Container();
                
                /**
                 * \brief set the layout to use to stor the objects
                 */
                void setLayout(Layout* layout);

                /**
                 * \return the layout used to stor the objects
                 */
                Layout* getLayout()const;

                /**
                 * \brief remove all the attached objects
                 */
                void clear();

                /**
                 * \brief change the fill color
                 * \param color new color
                 */
                void setFillColor(const sf::Color& color);

                /**
                 * \brief change the outline color
                 * \param color new color
                 */
                void setOutlineColor(const sf::Color& color);

                /**
                 * \brief change the outline thickness
                 * \param thickness new thickness
                 */
                void setOutlineThickness(float thickness);
                

            protected:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
                virtual void processEvents(const sf::Vector2f& parent_pos)override;

                sf::RectangleShape _shape;

                virtual void updateShape()override;
                virtual sf::Vector2f getSize()const override;

            private:
                Layout* _layout;


        };
    }
}
#endif
