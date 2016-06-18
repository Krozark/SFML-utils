#include <SFML-utils/map/models/TileModel.hpp>

ORM_REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(sfutils::map,TileModel,"Tile",
                                      texture,"texture",
                                      textureFrame,"textureFrame",
                                      posX,"posX",
                                      posY,"posY",
                                      textureRectTop,"textureRectTop",
                                      textureRectLeft,"textureRectLeft",
                                      textureRectWidth,"textureRectWidth",
                                      textureRectHeigh,"textureRectHeigh",

                                      texureCenterLeft,"texureCenterLeft",
                                      texureCenterTop,"texureCenterTop",
                                      
                                      layer,"layer_fk")

namespace sfutils
{
    namespace map
    {
    }
}
