#ifndef SFUTILS_EDITOR_MAPSTATECHANGER_HPP
#define SFUTILS_EDITOR_MAPSTATECHANGER_HPP

#include <SFML-utils/map-editor/TileInfo.hpp>

#include <SFML-utils/Map.hpp>
#include <SFML-utils/map/Models.hpp>

namespace sfutils
{
    namespace editor
    {
        class Editor;
        class MapStateChanger
        {
            public:
                MapStateChanger(const MapStateChanger&) = delete;
                MapStateChanger& operator=(const MapStateChanger&) = delete;

                MapStateChanger(Editor& owner);

                void reset();

                void save();

                //map infos
                void setTitle(const std::string& title);

                void setSize(int scale,int width, int height);

                void setGeometry(sfutils::map::GeometryModel::pointer& geo);
                
                //layers
                bool newLayer();

                bool delLayer(int index);

                bool moveLayer(int from,int to);

                //adding tiles contents
                void addTile(sfutils::map::Layer<sfutils::map::Tile>& layer,const sf::Vector2i& coord,const std::string& textureFile);
                void addSprite(sfutils::map::Layer<sf::Sprite>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect);
                void addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect);
                void addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const sf::Vector2i& coord,const std::string& textureFile);

            protected:

            private:
                Editor& _owner;


                std::list<TileInfo> _tileToRemove;
                std::list<TileInfo> _tileToAdd;

                sfutils::map::LayerModel::pointer _getLayer(int zbuffer);
                static void _delTile(sfutils::map::LayerModel::pointer& layer,const TileInfo& info);
                static void _addTile(sfutils::map::LayerModel::pointer& layer,const TileInfo& info);


        };
    }
}
#endif
