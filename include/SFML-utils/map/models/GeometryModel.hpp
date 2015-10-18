#ifndef SFUTILS_MAP_GEOMETRYMODEL_HPP
#define SFUTILS_MAP_GEOMETRYMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>
#include <ORM/fields/ManyToMany.hpp>

#include <SFML-utils/map/models/LayerModel.hpp>

namespace sfutils
{
    namespace map
    {
        class GeometryModel : public orm::SqlObject<GeometryModel>
        {
            public:
                GeometryModel();

                orm::CharField<255> name;

                orm::ManyToMany<GeometryModel,LayerModel> layers;

                MAKE_STATIC_COLUMN(name);
        };
    }
}
#endif
