#ifndef SFUTILS_MAP_MAPMODEL_HPP
#define SFUTILS_MAP_MAPMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-utils/map/models/GeometryModel.hpp>
#include <SFML-utils/map/models/LayerModel.hpp>

namespace sfutils
{
    namespace map
    {
        class MapModel : public orm::SqlObject<MapModel>
        {
            public:
                MapModel();
            
                orm::CharField<255> name;
                orm::FK<GeometryModel> geometry;
                orm::IntegerField scale;
                orm::IntegerField areaWidth;
                orm::IntegerField areaHeight;

                orm::ManyToMany<MapModel,LayerModel> layers;

                MAKE_STATIC_COLUMN(name,geometry,scale,areaWidth,areaHeight);

            protected:

            private:
        };
    }
}
#endif
