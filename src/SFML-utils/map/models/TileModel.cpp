#include <SFML-utils/map/models/TileModel.hpp>

ORM_REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(sfutils::map,TileModel,"Tile",
                                      texture,"texture",
                                      posX,"posX",
                                      posY,"posY",
                                      textureRectTop,"textureRectTop",
                                      textureRectLeft,"textureRectLeft",
                                      textureRectWidth,"textureRectWidth",
                                      textureRectHeigh,"textureRectHeigh",

                                      textureCenterLeft,"textureCenterLeft",
                                      textureCenterTop,"textureCenterTop",
                                      
                                      layer,"layer_fk")

namespace sfutils
{
    namespace map
    {
    }
}
