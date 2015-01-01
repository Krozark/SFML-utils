#ifndef SFUTILS_MAP_MAPVIEWER_HPP
#define SFUTILS_MAP_MAPVIEWER_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/core/ActionTarget.hpp>
#include <SFML-utils/map/Configuration.hpp>

namespace sfutils
{
    namespace map
    {
        class VMap;
        class MapViewer : public sf::Drawable, protected ActionTarget<int>
        {
            public:
                MapViewer(const MapViewer&) = delete;
                MapViewer& operator=(const MapViewer&) = delete;

                MapViewer(const VMap& map,const ActionMap<int>& action_map = Configuration::default_map_inputs);
                
                using ActionTarget::bind;
                using ActionTarget::unbind;
                using ActionTarget::processEvent;
                using ActionTarget::processEvents;

                void move(float offsetX, float offsetY);
                void move(const sf::Vector2f& offset);
                void zoom(float factor);
                void setSize(float width,float height);
                void setSize(const sf::Vector2f& size);

            private:
                const VMap& _map;
                sf::View _view;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
