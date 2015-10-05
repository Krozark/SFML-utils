#ifndef SFUTILS_MAP_VTILE_HPP
#define SFUTILS_MAP_VTILE_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace geometry
    {
        class Geometry;
    }

    namespace map
    {
        class VTile : public sf::Drawable
        {
            public:
                VTile(const VTile&) = delete;
                VTile& operator=(const VTile&) = delete;

                VTile(VTile&&) = default;
                VTile& operator=(VTile&&) = default;

                VTile(const geometry::Geometry& geometry,const sf::Vector2i& pos);
                virtual ~VTile();

                void setFillColor(const sf::Color &color);

                void setPosition(float x,float y);
                void setPosition(const sf::Vector2f& pos);

                sf::Vector2f getPosition()const;

                void setTexture(const sf::Texture *texture,bool resetRect=false);
                void setTextureRect(const sf::IntRect& rect);

                sf::FloatRect getGlobalBounds()const;
                sf::FloatRect getLocalBounds()const;


            protected:
                sf::ConvexShape _shape;

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
        };
    }
}
#endif
