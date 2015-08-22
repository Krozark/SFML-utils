#include <SFML-utils/map/VMap.hpp>

//#include <SFML-utils/map/Map.hpp>

#include <SFML-utils/map/VLayer.hpp>
#include <SFML-utils/map/Layer.hpp>
#include <SFML-utils/map/es/Systems.hpp>


#include <algorithm>

namespace sfutils
{
    namespace map
    {
        VMap::VMap(float size,const sf::Vector2i& areaSize) : 
            _tileSize(size),
            _areaSize(areaSize),
            _entityLayer(new Layer<Entity*>("entity",2))
        {
            addLayer(_entityLayer,false);
            systems.add<SysSkinDynamic>();
        }

        VMap::~VMap()
        {
            _clear();
        }

        Entity& VMap::createEntity()
        {
            std::uint32_t id = this->entities.create();
            Entity& e = entities.get(id);

            _entityLayer->add(&e);

            return e;
        }

        void VMap::removeEntity(Entity& e)
        {
            _entityLayer->remove(&e,false);
            e.remove();
        }

        void VMap::update(const sf::Time& deltaTime)
        {
            _entityLayer->sort();
            Application<Entity>::update(deltaTime);
        }

        es::SystemManager<Entity>& VMap::getSystemManager()
        {
            return systems;
        }

        void VMap::addLayer(VLayer* layer,bool sort)
        {
            _layers.emplace_back(layer);
            if(sort)
                sortLayers();
        }

        void VMap::removeLayer(VLayer* layer)
        {
            auto it = std::find(_layers.begin(),_layers.end(),layer);
            if(it != _layers.end())
            {
                delete *it;
                _layers.erase(it);
            }
        }

        VLayer* VMap::atZ(int z)const
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                if(_layers[i]->z() == z)
                    return _layers[i];
            return nullptr;
        }

        void VMap::_clear()
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
            {
                delete(_layers[i]);
            }

            _layers.clear();
            _entityLayer = nullptr;

        }

        float VMap::getTileSize()const
        {
            return _tileSize;
        }

        const sf::Vector2i& VMap::getAreaSize()const
        {
            return _areaSize;
        }

        sf::Vector2i VMap::mapPixelToCoords(const sf::Vector2f& pos) const
        {
            return mapPixelToCoords(pos.x,pos.y);
        }

        sf::Vector2f VMap::mapCoordsToPixel(const sf::Vector2i& pos) const
        {
            return mapCoordsToPixel(pos.x,pos.y);
        }

        void VMap::sortLayers()
        {
            std::sort(_layers.begin(),_layers.end(),[](const VLayer* a, const VLayer* b)->bool{
                      return a->z() < b->z();
                    });

            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->sort();
        }


        void VMap::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const
        {
            sf::FloatRect delta_viewport(viewport.left - _tileSize,
                                        viewport.top - _tileSize,
                                        viewport.width + _tileSize*2,
                                        viewport.height + _tileSize*2); 
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                _layers[i]->draw(target,states,delta_viewport);
        }

    }
}
