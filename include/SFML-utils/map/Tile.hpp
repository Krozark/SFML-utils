#ifndef SFUTILS_MAP_TILE_HPP
#define SFUTILS_MAP_TILE_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace geometry
    {
        class Geometry;
    }

    namespace map
    {
        class Tile : public sf::Drawable
        {
            public:
                Tile(const Tile&) = delete;
                Tile& operator=(const Tile&) = delete;

                Tile(Tile&&) = default;
                Tile& operator=(Tile&&) = default;

                Tile(const geometry::Geometry& geometry,const sf::Vector2i& pos);
                virtual ~Tile();

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
