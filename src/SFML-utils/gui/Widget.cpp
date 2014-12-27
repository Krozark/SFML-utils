#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        Widget::Widget(Widget* parent) : _parent(parent), _is_visible(true)
        {
        }

        Widget::~Widget()
        {
        }

        void Widget::setPosition(const sf::Vector2f& pos)
        {
            _position = pos;
        }

        void Widget::setPosition(float x,float y)
        {
            _position.x = x;
            _position.y = y;
        }

        const sf::Vector2f& Widget::getPosition()const
        {
            return _position;
        }

        void Widget::hide()
        {
            if(_is_visible == true)
            {
                _is_visible = false;
                updateShape();
            }
        }

        void Widget::show()
        {
            if(_is_visible == false)
            {
                _is_visible = true;
                updateShape();
            }
        }

        bool Widget::isHidden()const
        {
            return not _is_visible;
        }

        bool Widget::isVisible()const
        {
            return _is_visible;
        }

        void Widget::toggle()
        {
            _is_visible = not _is_visible;
            updateShape();
        }


        bool Widget::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            return false;
        }

        void Widget::processEvents(const sf::Vector2f& parent_pos)
        {
        }

        void Widget::updateShape()
        {
            if(_parent)
                _parent->updateShape();
        }
    }
}
