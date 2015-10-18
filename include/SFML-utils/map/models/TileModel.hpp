#ifndef SFUTILS_MAP_TILEMODEL_HPP
#define SFUTILS_MAP_TILEMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

namespace sfutils
{
    namespace map
    {
        class TileModel : public orm::SqlObject<TileModel>
        {
            public:
                TileModel();

                orm::CharField<255> name;
                
                MAKE_STATIC_COLUMN(name);

            private:
        };
    }
}
#endif
