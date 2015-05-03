#ifndef SMFL_UTILS_GUI_VLAYOUT_HPP
#define SMFL_UTILS_GUI_VLAYOUT_HPP

#include <SFML-utils/gui/Layout.hpp>
#include <vector>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A vertical Layout.
         * Display all the object verticaly and center them
         */
        class VLayout : public Layout
        {
            public:
                VLayout(const VLayout&) = delete;
                VLayout& operator=(const VLayout&) = delete;

                /**
                 * \brief Constructor
                 * \param parent the parent Widget
                 */
                explicit VLayout(Widget* parent = nullptr);
                ~VLayout();

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
                virtual void clear();

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
