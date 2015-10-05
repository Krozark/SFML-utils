#ifndef SFUTILS_MAP_MAPVIEWER_HPP
#define SFUTILS_MAP_MAPVIEWER_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/core/ActionTarget.hpp>

namespace sfutils
{
    namespace map
    {
        class Map;
        class MapViewer : public sf::Drawable, protected ActionTarget<int>
        {
            public:
                MapViewer(const MapViewer&) = delete;
                MapViewer& operator=(const MapViewer&) = delete;

                MapViewer(sf::RenderWindow& window,Map& map,bool bindDefault = true);
                MapViewer(sf::RenderWindow& window,Map& map,const ActionMap<int>& action_map,bool bindDefault = true);
                
                using ActionTarget::bind;
                using ActionTarget::unbind;
                using ActionTarget::processEvent;
                using ActionTarget::processEvents;

                void bindDefault();

                void move(float offsetX, float offsetY);
                void move(const sf::Vector2f& offset);

                void setPosition(float posX, float posY);
                void setPosition(const sf::Vector2f& pos);

                sf::Vector2f getPosition()const;

                void zoom(float factor);
                float getZoom()const;

                void setSize(float width,float height);
                void setSize(const sf::Vector2f& size);

                void update(const sf::Time& deltaTime);

                void setSpeed(float speed);

                void draw(sf::RenderStates states = sf::RenderStates::Default) const;

                sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

                sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos) const;

                sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;
                
                sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;


            private:
                Map& _map;
                sf::View _view;
                float _zoom;
                
                sf::Vector2f _move;
                float _movementSpeed;
                sf::RenderWindow& _window;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
