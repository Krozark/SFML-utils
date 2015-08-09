#include <SFML-utils/map/VMapLoader.hpp>


namespace sfutils
{
    namespace map
    {

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


        //////////////// VMAPLOADER //////////////////////

        VMapLoader::~VMapLoader()
        {
        }

    }
}
