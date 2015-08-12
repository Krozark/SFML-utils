#include <SFML-utils/map/MapMetaData.hpp>

namespace sfutils
{
    namespace map
    {
        
        MapMetaData::~MapMetaData()
        {
        }

        //////////////////// METALAYERDATASPRITE //////////////////
        MetaLayeDataSprite::MetaLayeDataSprite()
        {
            texCenter = sf::Vector2f(0.5,1);
            isPtr = false;
        }

        ///////////////// METALAYER //////////////////////
        
        MetaLayer::MetaLayer(int z,MetaLayerDataType type,bool isStatic) :
            _z(z),
            _type(type),
            _static(isStatic)
        {
        }
        

        ///////////////// METAAREA ///////////////////////
        MetaArea::MetaArea(int x,int y,const std::string& name):
            _name(name),
            _position(x,y)
        {
        }
    }
}
