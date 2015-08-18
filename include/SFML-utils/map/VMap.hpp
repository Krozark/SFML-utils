#ifndef SFUTILS_MAP_VMAP_HPP
#define SFUTILS_MAP_VMAP_HPP


#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include <SFML-utils/es/Application.hpp>

#include <SFML-utils/map/es/Entity.hpp>

namespace sfutils
{
    namespace map
    {
        class VTile;
        class VLayer;

        class VMap : protected sfutils::es::Application<MapEntity>
        {
            public:
                VMap(const VMap&) = delete;
                VMap& operator=(const VMap&) = delete;

                VMap(float tileSize,const sf::Vector2i& areaSize);
                virtual ~VMap();

                void addLayer(VLayer* layer,bool sort=true);
                void removeLayer(VLayer* layer);

                size_t size()const;
                VLayer* at(size_t index)const;
                VLayer* atZ(int z)const;
                void clear();

                float getTileSize()const;
                const sf::Vector2i& getAreaSize()const;

                virtual VLayer* createLayerOfGeometry(const std::string& content, int z, bool isStatic)const = 0;
                virtual VTile* createTileToLayer(int pos_x,int pos_y,float scale,sf::Texture* texture,VLayer* layer)const = 0;

                virtual sf::Vector2i mapPixelToCoords(float x,float y) const = 0;
                sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;
                
                virtual sf::Vector2f mapCoordsToPixel(int x,int y) const =0;
                sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;

                virtual const sf::ConvexShape getShape()const = 0;

                //virtual std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const = 0;
                //virtual sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const =0;
                virtual int getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest)const = 0;

            protected:
                void sortLayers();
                const float _tileSize;
                sf::Vector2i _areaSize;
                
            private:
                friend class MapViewer;
                void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const;
                std::vector<VLayer*> _layers;

        };

    }
}
#endif
