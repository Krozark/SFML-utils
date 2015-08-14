#ifndef SFUTILS_MAP_TILE_HPP
#define SFUTILS_MAP_TILE_HPP

#include <SFML-utils/map/VTile.hpp>


namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        class Tile : public VTile
        {
            public:
                Tile(const Tile&) = delete;
                Tile& operator=(const Tile&) = delete;

                Tile(Tile&&) = default;
                Tile& operator=(Tile&&) = default;

                Tile(int pos_x,int pos_y,float scale);
                virtual ~Tile();

                //convert pixel to word coord 
                static sf::Vector2i mapPixelToCoords(float x,float y,float scale);
                static sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos,float scale);
                
                //return the center of the tile position in pixel relative to the openGL world
                static sf::Vector2f mapCoordsToPixel(int x,int y,float scale);
                static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos,float scale);

            private:
                virtual void setCoords(int x, int y) override;
        };
    }
}
#include <SFML-utils/map/Tile.tpl>
#endif
