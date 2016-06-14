#ifndef SFUTILS_MAP_MAPMETADATA_HPP
#define SFUTILS_MAP_MAPMETADATA_HPP

#include <list>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include <SFML-utils/core/ResourceManager.hpp>

namespace sfutils
{
    namespace map
    {
        class VLayer;
        class Map;

        class MetaLayerData
        {
            public:
                virtual ~MetaLayerData();
                virtual bool addToLayer(VLayer* layer,Map* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord,std::list<void*>& createdData) = 0;
        };

        class MetaLayerDataTileRect : public MetaLayerData
        {
            public:
                MetaLayerDataTileRect(const std::string& tex, const sf::IntRect& rect);
                virtual ~MetaLayerDataTileRect();

                virtual bool addToLayer(VLayer* layer,Map* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord,std::list<void*>& createdData) override;

            private:
                std::string _texture;
                sf::IntRect _rect;
        };

        class MetaLayerDataSprite : public MetaLayerData
        {
            public:
                MetaLayerDataSprite(const std::string& tex,const sf::Vector2i& pos);
                virtual ~MetaLayerDataSprite();

                virtual bool addToLayer(VLayer* layer,Map* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord,std::list<void*>& createdData) override;

                void setIsPtr(bool ptr);
                void setTextureOrigin(const sf::Vector2f& o);
                void setTextureRect(const sf::IntRect& rect);

            private:

                std::string _texture;
                sf::Vector2i _position;
                //optional
                sf::Vector2f _texCenter; ///< default is (0.5,1)
                bool _isPtr; ///< default is false
                sf::IntRect _texRect;
        };

        class MetaLayerDataEntity : public MetaLayerData
        {
            public:
                MetaLayerDataEntity(const std::string& tex,const sf::Vector2i& pos);
                virtual ~MetaLayerDataEntity();

                virtual bool addToLayer(VLayer* layer,Map* const map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord,std::list<void*>& createdData) override;

                void setTextureOrigin(const sf::Vector2f& o);
                void setTextureRect(const sf::IntRect& rect);

            private:

                std::string _texture;
                sf::Vector2i _position;
                //optional
                sf::Vector2f _texCenter; ///< default is (0.5,1)
                sf::IntRect _texRect;
        };


        class MetaLayer
        {
            public:
                MetaLayer(int z,const std::string& type, bool isVisble,bool isStatic);
                virtual ~MetaLayer();

                void add(std::shared_ptr<MetaLayerData> data);

                bool addToMap(Map* map,ResourceManager<sf::Texture,std::string>& textureManager,const sf::Vector2i& areaCoord);

                bool removeFromMap(Map* map)const;

                friend std::ostream& operator<<(std::ostream& stream,const MetaLayer& self);

            private:
                int _z;
                const std::string _type;
                bool _static;
                bool _isVisible;
                std::list<std::shared_ptr<MetaLayerData>> _data;
                std::list<void*> _createdData;
        };

        /***
         * \brief class that hold metaData of a Area
         */
        class MetaArea
        {
            public:
                MetaArea(const sf::Vector2i& pos,const std::string& name);

                void add(MetaLayer&& layer);

                bool addToMap(Map* map,ResourceManager<sf::Texture,std::string>& textureManager);

                bool removeFromMap(Map* map)const;

            private:
                std::string _name;
                sf::Vector2i _position;
                std::list<MetaLayer> _layers;
        };

    }
}
#endif
