#ifndef SFUTILS_VMAPLOADER_HPP
#define SFUTILS_VMAPLOADER_HPP

#include <SFML-utils/map/VMap.hpp>

#include <list>

namespace sfutils
{
    namespace map
    {
        struct MetaLayerDataTileRect
        {
            //std::string texture;
            sf::IntRect rect;
        };

        struct MetaLayeDataSprite
        {
            MetaLayeDataSprite();

            //std::string texture;
            //sf::Vector2i position;
            //optional
            sf::Vector2f texCenter; ///< default is (0.5,1)
            bool isPtr; ///< default is false
        };


        enum MetaLayerDataType
        {
            META_TILE_RECT,
            META_SPRITE
        };

        struct MetaLayerData
        {
            MetaLayerDataType type;

            union
            {
                MetaLayerDataTileRect metaTileRect;
                MetaLayeDataSprite metaSprite;
            };
        };

        class MetaLayer
        {
            public:
                MetaLayer(int z,MetaLayerDataType type,bool isStatic = false);
                virtual ~MetaLayer();

                std::list<MetaLayerData> data;

            private:
                int _z;
                MetaLayerDataType _type;
                bool _static;
        };

        /***
         * \brief class that hold metaData of a Area
         */
        class MetaArea
        {
            public:
                MetaArea(int x,int y,const std::string& name);
                virtual ~MetaArea();

                std::list<MetaLayer> layers;
            private:
                std::string _name;
                sf::Vector2i _position;

        };

        class VMapLoader
        {
            public:
                virtual ~VMapLoader();

            protected:
                friend class MapManager;
                virtual MetaArea _loadArea(int x,int y) = 0;

        };
    }
}

#endif
