#ifndef SFUTILS_MAP_LAYERMODEL_HPP
#define SFUTILS_MAP_LAYERMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-utils/map/models/LayerTypeModel.hpp>

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
                orm::FK<LayerTypeModel> type;
                orm::BooleanField isStatic;

                MAKE_STATIC_COLUMN(name,zBuffer,type,isStatic);

            protected:

            private:
        };
    }
}
#endif
