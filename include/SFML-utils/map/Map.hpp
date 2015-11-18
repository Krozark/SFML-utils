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

                sf::Vector2i mapPixelToArea(const sf::Vector2f& pixels) const;
                sf::Vector2i mapCoordsToArea(const sf::Vector2i& coords) const;


                void draw(sf::RenderTarget& target,const sf::RenderStates& states,const sf::FloatRect& viewport) const;

            private:
                ::sfutils::geometry::Geometry* _geometry;
                sf::Vector2i _areaSize;

                void sortLayers();
                void _clear();
                

                std::vector<VLayer*> _layers;
                std::vector<Layer<Entity*>*> _entityLayers;
                //TODO cache the entities position
        };

    }
}
#endif
