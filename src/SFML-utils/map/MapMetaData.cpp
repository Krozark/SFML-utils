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

        bool MetaLayerDataTileRect::addToLayer(VLayer* layer,VMap* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord)
        {
            if(layer->getType() != "tile")
            {
                std::cerr<<"unsuported layer type '"<<layer->getType()<<"' for MetaLayerDataTileRect (should be 'tile')"<<std::endl;
                return false;
            }

            sf::Texture& tex = textureManager.getOrLoad(_texture,_texture);
            tex.setRepeated(true);

            sf::Vector2i size = map->getAreaSize();

            for(int y = _rect.top; y<_rect.top + _rect.height && y < size.y;++y)
            {
                for(int x = _rect.left; x< _rect.left + _rect.width && x < size.x; ++x)
                {
                    VTile* tile = map->createTileToLayer(areaCoord.x + x, areaCoord.y + y,map->getTileSize(),&tex,layer);
                    if(not tile)
                        return false;
                }
            }

            return true;
        }



        //////////////////// METALAYERDATASPRITE //////////////////
        MetaLayerDataSprite::MetaLayerDataSprite(const std::string& tex,const sf::Vector2i& pos) :
            _texture(tex),
            _position(pos)
        {
            _texCenter = sf::Vector2f(0.5,1);
            _isPtr = false;
        }

        MetaLayerDataSprite::~MetaLayerDataSprite()
        {
        }

        bool MetaLayerDataSprite::addToLayer(VLayer* layer,VMap* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord)
        {
            if(_isPtr and layer->getType() != "sprite_ptr")
            {
                std::cerr<<"unsuported layer type '"<<layer->getType()<<"' for MetaLayerDataTileRect (should be 'sprite_ptr')"<<std::endl;
                return false;
            }
            else if(not _isPtr and layer->getType() != "sprite")
            {
                std::cerr<<"unsuported layer type '"<<layer->getType()<<"' for MetaLayerDataTileRect (should be 'sprite')"<<std::endl;
                return false;
            }

            sf::Texture& tex = textureManager.getOrLoad(_texture,_texture);
            tex.setRepeated(false);

            if(_texRect == sf::IntRect()) //default == all the texture
            {
                _texRect.width = tex.getSize().x;
                _texRect.height = tex.getSize().y;
            }

            sf::Sprite spr(tex,_texRect);

            std::cout<<"_texRect: "<<_texRect.width<<";"<<_texRect.height
                <<" position: "<<_position.x<<";"<<_position.y
                <<" _texCenter: "<<_texCenter.x<<";"<<_texCenter.y
                <<std::endl;

            spr.setPosition(map->mapCoordsToPixel(areaCoord.x + _position.x,areaCoord.y + _position.y));

            spr.setOrigin(_texRect.width * _texCenter.x,
                          _texRect.height * _texCenter.y);

            sf::Sprite* s_ptr = nullptr;
            if(_isPtr)
            {
                auto l = dynamic_cast<Layer<sf::Sprite*>*>(layer);
                if(not l)
                    return false;

                s_ptr = l->add(new sf::Sprite(std::move(spr)),false);
            }
            else
            {
                auto l = dynamic_cast<Layer<sf::Sprite>*>(layer);
                if(not l)
                    return false;

                s_ptr = l->add(std::move(spr),false);
            }

            return (s_ptr != nullptr);
        }

        void MetaLayerDataSprite::setIsPtr(bool ptr)
        {
            _isPtr = ptr;
        }

        void MetaLayerDataSprite::setTextureOrigin(const sf::Vector2f& o)
        {
            _texCenter = o;
        }
        void MetaLayerDataSprite::setTextureRect(const sf::IntRect& rect)
        {
            _texRect = rect;
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

        bool MetaLayer::addToMap(VMap* map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord)
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
                if(not data->addToLayer(layer,map,textureManager,areaCoord))
                    return false;
            }
            layer->sort();
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
        MetaArea::MetaArea(const sf::Vector2i& pos,const std::string& name):
            _name(name),
            _position(pos)
        {
        }

        void MetaArea::add(MetaLayer&& layer)
        {
            return _layers.emplace_back(layer);
        }

        bool MetaArea::addToMap(VMap* map,ResourceManager<sf::Texture,std::string>& textureManager)
        {
            sf::Vector2i coord = _position;
            coord.x *= map->getAreaSize().x;
            coord.y *= map->getAreaSize().y;

            for(MetaLayer& layer : _layers)
            {
                if(not layer.addToMap(map,textureManager,coord))
                    return false;
            }
            return true;
        }

    }
}
