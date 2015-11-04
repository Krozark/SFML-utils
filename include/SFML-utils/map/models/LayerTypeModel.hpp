#ifndef SFUTILS_MAP_LAYERTYPEMODEL_HPP
#define SFUTILS_MAP_LAYERTYPEMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

namespace sfutils
{
    namespace map
    {
        class LayerTypeModel : public orm::SqlObject<LayerTypeModel>
        {
            public:
                LayerTypeModel();

                orm::CharField<255> name;

                MAKE_STATIC_COLUMN(name);

            private:
        };
    }
}
#endif
