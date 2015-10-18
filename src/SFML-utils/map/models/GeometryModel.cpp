#include <SFML-utils/map/models/GeometryModel.hpp>

M2M_REGISTER(sfutils::map::GeometryModel,layers,sfutils::map::LayerTypeModel,"Geometry_layers","geometry_id","layer_id")
REGISTER(sfutils::map::GeometryModel,"Geometry",name,"name")

namespace sfutils
{
    namespace map
    {
        GeometryModel::GeometryModel() :
            name(GeometryModel::$name),
            layers(*this)
        {
            name.registerAttr(*this);
        }
    }
}
