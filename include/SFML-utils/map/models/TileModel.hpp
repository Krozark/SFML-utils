#ifndef SFUTILS_MAP_TILEMODEL_HPP
#define SFUTILS_MAP_TILEMODEL_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-utils/map/models/LayerModel.hpp>

namespace sfutils
{
    namespace map
    {
        class TileModel : public orm::SqlObject<TileModel>
        {
            public:
                TileModel();

                orm::CharField<255> texture;
                orm::CharField<255> textureFrame;

                orm::IntegerField posX;
                orm::IntegerField posY;

                orm::FK<LayerModel> layer;
                
                ORM_MAKE_STATIC_COLUMN(texture,textureFrame,
                                       posX,posY,
                                       layer);

            private:
        };
    }
}
#endif
