#include <SFML-utils/map/models/LayerModel.hpp>

ORM_REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(sfutils::map,LayerModel,"Layer",
                                      name,"name",
                                      zBuffer,"zBuffer",
                                      isStatic,"isStatic",
                                      type,"type_fk",
                                      map,"map_fk")

namespace sfutils
{
    namespace map
    {
    }
}
