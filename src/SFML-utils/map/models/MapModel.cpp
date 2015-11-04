#include <SFML-utils/map/models/MapModel.hpp>

REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(sfutils::map,MapModel,"Map",
                                      name,"name",
                                      geometry, "geometry_fk",
                                      scale, "scale",
                                      areaWidth,"areaWidth",
                                      areaHeight,"areaHeight");

namespace sfutils
{
    namespace map
    {
    }
}
