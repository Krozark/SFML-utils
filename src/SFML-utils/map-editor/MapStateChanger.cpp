#include <SFML-utils/map-editor/MapStateChanger.hpp>

#include <SFML-utils/map-editor/Editor.hpp>

namespace sfutils
{
    namespace editor
    {
        MapStateChanger::MapStateChanger(Editor& owner) : 
            _owner(owner)
        {
        }

        void MapStateChanger::reset()
        {
            _tileToAdd.clear();
            _tileToRemove.clear();
        }

        void MapStateChanger::save()
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->save();

            _tileToRemove.sort();
            _tileToRemove.unique();
            //TODO remove from DB

            _tileToAdd.sort();
            _tileToAdd.unique();
            //TODO insert into DB

            _owner._dbMap->save();
        }

        void MapStateChanger::setTitle(const std::string& title)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->name = title;
        }

        void MapStateChanger::setSize(int scale,int width, int height)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->scale = scale;;
            _owner._dbMap->areaWidth = width;
            _owner._dbMap->areaHeight = height;

        }

        void MapStateChanger::setGeometry(sfutils::map::GeometryModel::pointer& geo)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            _owner._dbMap->geometry = geo;
        }

        bool MapStateChanger::newLayer()
        {
            //TODO
            return false;
        }

        bool MapStateChanger::delLayer(int index)
        {
            auto tileFunc = [index](const TileInfo& i){
                return index == i.z;
            };

            _tileToRemove.remove_if(tileFunc);
            _tileToAdd.remove_if(tileFunc);

            //TODO remove from _map

            return true;
        }

        bool MapStateChanger::moveLayer(int from,int to)
        {
            //TODO change zbuffer of it, and all others to be sure that no z index is duplicated
            //TODO update _tileToXXX
            return false;
        }

        void MapStateChanger::addTile(sfutils::map::Layer<sfutils::map::Tile>& layer,const sf::Vector2i& coord,const std::string& textureFile)
        {
            assert(_owner._map);
            assert(_owner._dbMap);

            std::cout<<"Tile"<<std::endl;

            auto objs = layer.getByCoords(coord,*_owner._map);
            if(objs.size() > 0)
            {
                std::cout<<objs.size()<<" objects here in "<<coord.x<<" "<<coord.y<<std::endl;
                for(auto ptr : objs)
                {
                    layer.remove(ptr,false);
                    _tileToRemove.emplace_back(layer.z(),coord);
                }
            }

            sfutils::map::Tile tmp(_owner._map->getGeometry(),coord);
            tmp.setTexture(&_owner._mapManager->getTextureManager().get(textureFile));
            tmp.setTextureRect(_owner._map->getGeometry().getTextureRect(coord));

            layer.add(std::move(tmp));
            _tileToAdd.emplace_back(layer.z(),coord);
        }

        void MapStateChanger::addSprite(sfutils::map::Layer<sf::Sprite>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"Sprite"<<std::endl;
        }

        void MapStateChanger::addSpritePtr(sfutils::map::Layer<sf::Sprite*>& layer,const sf::Vector2i& coord,const std::string& textureFile,const sf::IntRect& textureRect)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"SpritePtr"<<std::endl;
        }

        void MapStateChanger::addEntity(sfutils::map::Layer<sfutils::map::Entity*>& layer,const sf::Vector2i& coord,const std::string& textureFile)
        {
            assert(_owner._map);
            assert(_owner._dbMap);
            //TODO
            std::cout<<"Entity"<<std::endl;
        }
    }
}
