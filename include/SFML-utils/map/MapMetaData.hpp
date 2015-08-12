#ifndef SFUTILS_MAP_MAPMETADATA_HPP
#define SFUTILS_MAP_MAPMETADATA_HPP

namespace sfutils
{
    namespace map
    {
        class VLayer;
        class MetaLayerData
        {
            public:
                virtual ~MetaLayerData();
                virtual void addToLayer(VLayer* layer) = 0;
        };

        class MetaLayerDataTileRect : public MetaLayerData
        {
            public:
                virtual void addToLayer(VLayer* layer) = 0;

                std::string texture;
                sf::IntRect rect;
        };

        class MetaLayeDataSprite : public MetaLayeDataSprite
        {
            public:
                virtual void addToLayer(VLayer* layer) = 0;
                MetaLayeDataSprite();

                std::string texture;
                sf::Vector2i position;
                //optional
                sf::Vector2f texCenter; ///< default is (0.5,1)
                bool isPtr; ///< default is false
        };


        class MetaLayer
        {
            public:
                MetaLayer(int z,MetaLayerDataType type,bool isStatic = false);
                virtual ~MetaLayer();

                std::list<MetaLayerData*> data;

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

    }
}
#endif
