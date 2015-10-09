#include <SFML-utils/map/Map.hpp>

//#include <SFML-utils/map/Map.hpp>

#include <SFML-utils/map/VLayer.hpp>
#include <SFML-utils/map/Layer.hpp>
#include <SFML-utils/map/es/Systems.hpp>


#include <algorithm>

namespace sfutils
{
    namespace map
    {
        Map::Map(::sfutils::geometry::Geometry* geometry,const sf::Vector2i& areaSize) : 
            _geometry(geometry),
            _areaSize(areaSize)
        {
            systems.add<SysSkinDynamic>();
        }

        Map::~Map()
        {
            delete _geometry;
            _clear();
        }

        Entity& Map::createEntity()
        {
            std::uint32_t id = this->entities.create();
            Entity& e = entities.get(id);

            return e;
        }

        void Map::removeEntity(Entity& e)
        {
            e.remove();
        }

        void Map::update(const sf::Time& deltaTime)
        {
            unsigned int size = _entityLayers.size();
            for(unsigned int i=0;i<size;++i)
                _entityLayers[i]->sort();

            Application<Entity>::update(deltaTime);
        }

        es::SystemManager<Entity>& Map::getSystemManager()
        {
            return systems;
        }

        void Map::addLayer(VLayer* layer,bool sort)
        {
            _layers.emplace_back(layer);
            if(sort)
                sortLayers();

            if(layer->getType() == "entity")
                _entityLayers.emplace_back(static_cast<Layer<Entity*>*>(layer));
        }

        void Map::removeLayer(VLayer* layer)
        {
            if(layer->getType() == "entity")
            {
                auto it = std::find(_entityLayers.begin(),_entityLayers.end(),layer);
                if(it != _entityLayers.end())
                {
                    _entityLayers.erase(it);
                }
            }

            auto it = std::find(_layers.begin(),_layers.end(),layer);
            if(it != _layers.end())
            {
                delete *it;
                _layers.erase(it);
            }

        }

        VLayer* Map::atZ(int z)const
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                if(_layers[i]->z() == z)
                    return _layers[i];
            return nullptr;
        }


        const sf::Vector2i& Map::getAreaSize()const
        {
            return _areaSize;
        }

        const ::sfutils::geometry::Geometry& Map::getGeometry() const
        {
            return *_geometry;
        }


        ////////////////////// PRIVATE ////////////////////

        void Map::sortLayers()
        {
            std::sort(_layers.begin(),_layers.end(),[](const VLayer* a, const VLayer* b)->bool{
                      return a->z() < b->z();
                    });

            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->sort();
        }

        void Map::_clear()
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
            {
                delete(_layers[i]);
            }

            _layers.clear();
            _entityLayers.clear();

        }


        void Map::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const
        {
            static float tileSize = getGeometry().getScale();
            sf::FloatRect delta_viewport(viewport.left - tileSize,
                                        viewport.top - tileSize,
                                        viewport.width + tileSize*2,
                                        viewport.height + tileSize*2);

            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->draw(target,states,delta_viewport);
        }

    }
}
