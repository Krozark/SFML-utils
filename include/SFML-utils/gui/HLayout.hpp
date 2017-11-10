#ifndef SFUTILS_GUI_HLAYOUT_HPP
#define SFUTILS_GUI_HLAYOUT_HPP

#include <SFML-utils/gui/Layout.hpp>
#include <vector>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A horizontal Layout.
         * Display all the object horizontaly and center them
         */
        class HLayout : public Layout
        {
            public:
                HLayout(const HLayout&) = delete;
                HLayout& operator=(const HLayout&) = delete;

                /**
                 * \brief Constructor
                 * \param parent the parent Widget
                 */
                explicit HLayout(Widget* parent = nullptr);
                ~HLayout();

                /**
                 * \brief Add a new widget to the layout
                 */
                void add(Widget* widget);
                /**
                 * \return the Widget at the index index
                 */
                Widget* at(unsigned int index)const;

                
                /**
                 * \brief remove all attached widgets
                 */
                virtual void clear() override;

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos) override;
                virtual void processEvents(const sf::Vector2f& parent_pos) override;

                virtual sf::Vector2f getSize()const override;

            private:
                std::vector<Widget*> _widgets;

                virtual void updateShape() override;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
