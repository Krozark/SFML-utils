#ifndef SFUTILS_MAP_LAYERMODEL_HPP
#define SFUTILS_MAP_LAYERMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-utils/map/models/LayerTypeModel.hpp>
#include <SFML-utils/map/models/MapModel.hpp>

namespace sfutils
{
    namespace map
    {
        class LayerModel : public orm::SqlObject<LayerModel>
        {
            public:
                LayerModel();

                orm::CharField<255> name;
                orm::IntegerField zBuffer;
                orm::BooleanField isStatic;
                orm::FK<LayerTypeModel> type;
                orm::FK<MapModel> map;

                ORM_MAKE_STATIC_COLUMN(name,zBuffer,isStatic,type,map);

            private:
        };
    }
}
#endif
