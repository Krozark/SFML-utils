#include <SFML-utils/map/MapMetaData.hpp>
#include <SFML-utils/map/VMap.hpp>

#include <SFML-utils/map/Tile.hpp>
#include <SFML-utils/map/Layer.hpp>

#include <iostream>

namespace sfutils
{
    namespace map
    {
        ////////////////////// METALAYERDATA ////////////////////////////// 
        MetaLayerData::~MetaLayerData()
        {
        }

        ///////////////////// METALAYERDATATILERECT //////////////////////
        MetaLayerDataTileRect::MetaLayerDataTileRect(const std::string& tex, const sf::IntRect& rect) :
            _texture(tex),
            _rect(rect)
        {
        }

        MetaLayerDataTileRect::~MetaLayerDataTileRect()
        {
        }

        bool MetaLayerDataTileRect::addToLayer(VLayer* layer)
        {
            //#error TODO
            return false;
        }



        //////////////////// METALAYERDATASPRITE //////////////////
        MetaLayeDataSprite::MetaLayeDataSprite(const std::string& tex,const sf::Vector2i& pos) : 
            _texture(tex),
            _position(pos)
        {
            _texCenter = sf::Vector2f(0.5,1);
            _isPtr = false;
        }

        MetaLayeDataSprite::~MetaLayeDataSprite()
        {
        }

        bool MetaLayeDataSprite::addToLayer(VLayer* layer)
        {
            //#error TODO
            return false;
        }

        void MetaLayeDataSprite::setIsPtr(bool ptr)
        {
            _isPtr = ptr;
        }

        void MetaLayeDataSprite::setTextureOrigin(sf::Vector2f& o)
        {
            _texCenter = o;
        }

        ///////////////// METALAYER //////////////////////
        
        MetaLayer::MetaLayer(int z,const std::string& type,bool isStatic) :
            _z(z),
            _type(type),
            _static(isStatic)
        {
        }

        MetaLayer::~MetaLayer()
        {
        }

        void MetaLayer::add(std::shared_ptr<MetaLayerData> data)
        {
            _data.emplace_back(data);
        }

        bool MetaLayer::addToMap(VMap* map)
        {
            VLayer* layer = map->atZ(_z);
            if(layer)
            {
                if(layer->getType() != _type)
                {
                    std::cerr<<"The already have a layer at the z-buffer "<<_z<<" with a different type ("<<layer->getType()<<"/"<<_type<<std::endl;
                    return false;
                }
            }
            else //need to create it
            {
                if(_type == "tile")
                {
                    layer = map->createLayerOfGeometry(_type,_z,_static);
                }
                else if(_type == "sprite")
                {
                    layer = new Layer<sf::Sprite>(_type,_z,_static);
                }
                else if(_type == "sprite_ptr")
                {
                    layer = new Layer<sf::Sprite*>(_type,_z,_static);
                }

                if(layer)
                {
                    std::cout<<"Add layer at the z-buffer "<<_z<<" with type "<<layer->getType()<<std::endl;
                    map->add(layer);
                }
                else
                {
                    std::cerr<<"Unknow content-type "<<_type<<std::endl;
                    return false;
                }
            }

            for(std::shared_ptr<MetaLayerData>& data : _data)
            {
                if(not data->addToLayer(layer))
                    return false;
            }
            return true;
        }

        std::ostream& operator<<(std::ostream& stream,const MetaLayer& self)
        {
            stream<<"\"z-buffer\": "<<self._z
                <<", \"content-type\":"<<self._type
                <<", \"static\":"<<(self._static?"true":"false");

            return stream;
        }

        

        ///////////////// METAAREA ///////////////////////
        MetaArea::MetaArea(int x,int y,const std::string& name):
            _name(name),
            _position(x,y)
        {
        }

        void MetaArea::addLayer(MetaLayer&& layer)
        {
            return _layers.emplace_back(layer);
        }

        bool MetaArea::addToMap(VMap* map)
        {
            for(MetaLayer& layer : _layers)
            {
                if(not layer.addToMap(map))
                    return false;
            }
            return true;
        }

    }
}
