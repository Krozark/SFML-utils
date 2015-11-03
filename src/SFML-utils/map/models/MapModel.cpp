#include <SFML-utils/map/models/MapModel.hpp>

M2M_REGISTER(sfutils::map::MapModel,layers,sfutils::map::LayerModel,"Map_layers","map_id","layer_id");
REGISTER(sfutils::map::MapModel,"Map",
         name,"name",
         geometry, "geometry_fk",
         scale, "scale",
         areaWidth,"areaWidth",
         areaHeight,"areaHeight");

namespace sfutils
{
    namespace map
    {
        MapModel::MapModel() :
            name(MapModel::$name),
            geometry(MapModel::$geometry),
            scale(MapModel::$scale),
            areaWidth(MapModel::$areaWidth),
            areaHeight(MapModel::$areaHeight),
            layers(*this)
        {
            name.registerAttr(*this);
            geometry.registerAttr(*this);
            scale.registerAttr(*this);
            areaWidth.registerAttr(*this);
            areaHeight.registerAttr(*this);
        }
    }
}
