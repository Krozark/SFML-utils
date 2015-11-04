#include <SFML-utils/map/models/TileModel.hpp>

REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(sfutils::map,TileModel,"Tile",
                                      texture,"texture",
                                      textureFrame,"textureFrame",
                                      x,"x",
                                      y,"y",
                                      layer,"layer_fk")

namespace sfutils
{
    namespace map
    {
    }
}
