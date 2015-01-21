#include <SFML-utils/gui/Frame.hpp>
#include <SFML-utils/gui/Layout.hpp>

namespace sfutils
{
    namespace gui
    {
        Frame::Frame(sf::RenderWindow& window,const ActionMap<int>& map) : Container(nullptr), ActionTarget(map), _window(window), _view(_window.getDefaultView())
        {
            ActionTarget::bind(Action(sf::Event::Resized),[this](const sf::Event& event){

                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                this->_view = sf::View(visibleArea);

                if(Layout* layout = getLayout())
                    layout->updateShape();
           });
        }

        Frame::~Frame()
        {
        }

        void Frame::draw()
        {
            _window.draw(*this);
        }

        void Frame::processEvents()
        {
            sf::Vector2f parent_pos(0,0);
            processEvents(parent_pos);
        }

        bool Frame::processEvent(const sf::Event& event)
        {
            sf::Vector2f parent_pos(0,0);
            return processEvent(event,parent_pos);
        }

        void Frame::bind(int key,const FuncType& callback)
        {
            ActionTarget::bind(key,callback);
        }

        void Frame::unbind(int key)
        {
            ActionTarget::unbind(key);
        }


        sf::Vector2f Frame::getSize()const
        {
            sf::Vector2u size = _window.getSize();
            return sf::Vector2f(size.x,size.y);
        }

        bool Frame::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = false;
            if(_is_visible)
            {
                res = ActionTarget::processEvent(event);
                if(not res)
                    res = Container::processEvent(event,parent_pos);
            }
            return res;
        }

        void Frame::processEvents(const sf::Vector2f& parent_pos)
        {
            if(_is_visible)
            {
                ActionTarget::processEvents();
                Container::processEvents(parent_pos);

                sf::Event event;
                while(_window.pollEvent(event))
                {
                    if(not ActionTarget::processEvent(event))
                        Container::processEvent(event,parent_pos);
                }
            }
        }

        void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_is_visible)
            {
                sf::View view = target.getView();
                target.setView(_view);

                Container::draw(target,states);

                target.setView(view);
            }
        }
    }
}
