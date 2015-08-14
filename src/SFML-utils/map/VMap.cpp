#include <SFML-utils/map/VMap.hpp>

#include <SFML-utils/map/VLayer.hpp>
#include <SFML-utils/map/Map.hpp>


#include <algorithm>

namespace sfutils
{
    namespace map
    {
        VMap::VMap(float size,const sf::Vector2i& areaSize) : 
            _tileSize(size),
            _areaSize(areaSize)
        {
        }

        VMap::~VMap()
        {
            clear();
        }


        void VMap::add(VLayer* layer,bool sort)
        {
            _layers.emplace_back(layer);
            if(sort)
                sortLayers();
        }

        void VMap::remove(size_t index)
        {
            delete _layers.at(index);
            _layers.erase(_layers.begin()+index);
        }

        void VMap::remove(VLayer* layer)
        {
            auto it = std::find(_layers.begin(),_layers.end(),layer);
            if(it != _layers.end())
            {
                delete *it;
                _layers.erase(it);
            }
        }

        size_t VMap::size()const
        {
            return _layers.size();
        }

        VLayer* VMap::at(size_t index)const
        {
            return _layers.at(index);
        }

        VLayer* VMap::atZ(int z)const
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                if(_layers[i]->z() == z)
                    return _layers[i];
            return nullptr;
        }

        void VMap::clear()
        {
            const size_t size = _layers.size();
            for(size_t i=0;i<size;++i)
                delete(_layers[i]);

            _layers.clear();
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
