#ifndef SFUTILS_MAP_MAP_HPP
#define SFUTILS_MAP_MAP_HPP


#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include <SFML-utils/es/Application.hpp>

#include <SFML-utils/map/es/Entity.hpp>
#include <SFML-utils/map/geometry/Geometry.hpp>

namespace sfutils
{
    namespace map
    {
        class Tile;
        class VLayer;

        template<typename> class Layer;

        class Map : protected sfutils::es::Application<Entity>
        {
            public:
                Map(const Map&) = delete;
                Map& operator=(const Map&) = delete;

                Map(::sfutils::geometry::Geometry* geometry,const sf::Vector2i& areaSize); 

                virtual ~Map();

                Entity& createEntity();
                void removeEntity(Entity& e);

                void update(const sf::Time& deltaTime);

                es::SystemManager<Entity>& getSystemManager();

                void addLayer(VLayer* layer,bool sort=true);
                void removeLayer(VLayer* layer);

                VLayer* atZ(int z)const;

                const sf::Vector2i& getAreaSize()const;

                const ::sfutils::geometry::Geometry& getGeometry() const;

                /*virtual VLayer* createLayerOfGeometry(const std::string& content, int z, bool isStatic)const = 0;
                virtual Tile* createTileToLayer(int pos_x,int pos_y,float scale,sf::Texture* texture,VLayer* layer)const = 0;

                virtual sf::Vector2i mapPixelToCoords(float x,float y) const = 0;
                sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;
                
                virtual sf::Vector2f mapCoordsToPixel(int x,int y) const =0;
                sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;

                virtual const sf::ConvexShape getShape()const = 0;

                //virtual std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const = 0;
                //virtual sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const =0;
                virtual int getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest)const = 0;*/

            private:
                ::sfutils::geometry::Geometry* _geometry;
                sf::Vector2i _areaSize;

                void sortLayers();
                void _clear();
                
                friend class MapViewer;

                void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const;

                std::vector<VLayer*> _layers;
                std::vector<Layer<Entity*>*> _entityLayers;
                //TODO cache the entities position
        };

    }
}
#endif
