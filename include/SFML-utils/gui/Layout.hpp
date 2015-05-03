#ifndef SMFL_UTILS_GUI_LAYOUT_HPP
#define SMFL_UTILS_GUI_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        /**
         * \brief A base class for all the Layout.
         */
        class Layout : virtual protected Widget
        {
            public:
                Layout(const Layout&) = delete;
                Layout& operator=(const Layout&) = delete;

                /**
                 * \brief Constructor
                 * \param parent the parent Widget
                 */
                explicit Layout(Widget* parent=nullptr);
                virtual ~Layout();

                /**
                 * \brief remove all attached widgets
                 */
                virtual void clear() = 0;

                /**
                 * \brief set the spacing betwenn two widgets
                 */
                void setSpacing(float pixels);

            protected:
                friend class Container;
                friend class Frame;

                float _spacing;
        };
    }
}
#endif
