#ifndef SFUTILS_EDITOR_EDITOR_HPP
#define SFUTILS_EDITOR_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>
#include <SFML-utils/map/Models.hpp>

#include <SFML-utils/map-editor/Gui.hpp>
#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>
#include <SFML-utils/map-editor/TileInfo.hpp>

#include <utility>


namespace sfutils
{
    namespace editor
    {
        class Editor
        {
            public:
                Editor(const Editor&) = delete;
                Editor& operator=(const Editor&) = delete;

                explicit Editor();
                ~Editor();

                void run();

                void setMap(sfutils::map::MapModel::pointer& map);
                sfutils::map::MapModel::pointer getMap() const;
                void reloadMap();

                void setZoom(float value);
                void setMiniMapZoom(float value);

                bool requestNewLayer();
                bool requestDelLayer(int index);
                bool requestMoveLayer(int from,int to);
                bool requestSetCurrentLayer(int index);

                bool requestSaveMap();


                bool requestTextureSelected(const std::string& texture);
                
                bool setCurrentSprite(const std::string& spr);
                bool setCurrentSprite(const std::string& spr,const sf::IntRect& rect);


            private:
                sf::RenderWindow _window;
                sf::Clock _clock;

                Gui _gui;
                SpriteSheetSelector _spriteSheetSelector;

                sfutils::map::Map* _map;
                sfutils::map::MapModel::pointer _dbMap;
                sfutils::map::LayerModel::pointer_array _getMapLayers()const;


                std::unique_ptr<sfutils::map::MapManager> _mapManager;
                sfutils::map::MapViewer _mapViewer;

                sf::ConvexShape* _highlight;
                sf::IntRect _lastVisibleRect;

                //sf::IntRect _selectionRect;
                //std::vector<sf::ConvexShape> _selectionHighlight;

                sf::IntRect _currentTextureRect;
                std::string _currentTextureFile;

                int _currentLayerIndex;

                void _processEvents();
                void _update();
                void _render();

                void _onClick(const sf::Vector2i& Coord);

                void _loadVisiblesAreas(const sf::IntRect& rect);
                sf::IntRect _getVisibleAreaRect()const;

                std::list<std::string> _getTextureList()const;

                void _reset();


                void _addTile(sfutils::map::Layer<sfutils::map::Tile>& layer,const sf::Vector2i& coord);

                std::list<TileInfo> _tileToRemove;
                std::list<TileInfo> _tileToAdd;


                void _addSprite(sfutils::map::Layer<sf::Sprite>& layer,const sf::Vector2i& coord);
                void _addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const sf::Vector2i& coord);
                void _addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const sf::Vector2i& coord);


        };
    }
}
#endif
