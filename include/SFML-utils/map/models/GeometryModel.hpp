#ifndef SFUTILS_MAP_GEOMETRYMODEL_HPP
#define SFUTILS_MAP_GEOMETRYMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

namespace sfutils
{
    namespace map
    {
        class GeometryModel : public orm::SqlObject<GeometryModel>
        {
            public:
                GeometryModel();

                orm::CharField<255> name;

                MAKE_STATIC_COLUMN(name);
        };
    }
}
#endif
