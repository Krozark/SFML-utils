#ifndef SFUTILS_MAP_MAPMETADATA_HPP
#define SFUTILS_MAP_MAPMETADATA_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        class VLayer;
        class VMap;

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

        class MetaLayeDataSprite : public MetaLayerData
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
                MetaLayer(int z,const std::string& type,bool isStatic = false);
                virtual ~MetaLayer();
                
                bool add(MetaLayerData* data);

                bool addToMap(VMap* map);

            private:
                int _z;
                const std::string _type;
                bool _static;
                std::list<MetaLayerData*> _data;
        };

        /***
         * \brief class that hold metaData of a Area
         */
        class MetaArea
        {
            public:
                MetaArea(int x,int y,const std::string& name);
                virtual ~MetaArea();

                void addLayer(MetaLayer&& layer);
                
                bool addToMap(VMap* map);

            private:
                std::string _name;
                sf::Vector2i _position;
                std::list<MetaLayer> _layers;

        };

    }
}
#endif
