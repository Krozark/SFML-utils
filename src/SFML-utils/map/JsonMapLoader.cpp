#include <SFML-utils/map/JsonMapLoader.hpp>

#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/VLayer.hpp>
#include <SFML-utils/map/geometry/GeometryHexaIso.hpp>
#include <SFML-utils/map/geometry/GeometryHexa.hpp>
#include <SFML-utils/map/geometry/GeometrySquare.hpp>
#include <SFML-utils/map/geometry/GeometrySquareIso.hpp>
#include <SFML-utils/map/geometry/GeometrySquareStaggered.hpp>
#include <SFML-utils/map/geometry/GeometrySquareIsoStaggered.hpp>

#include <utils/json/Driver.hpp>
#include <utils/string.hpp>
#include <functional>

namespace sfutils
{
    namespace map
    {
        JsonMapLoader::JsonMapLoader(const std::string& mapDirectory) : _mapDir(mapDirectory)
        {
        }

        Map* JsonMapLoader::_loadMap()
        {

            auto value = utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"map.json"));

            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<_mapDir<<"/map.json"<<std::endl;
                return nullptr;
            }

            std::string name;

            std::string tile_geometry;
            float tile_size;

            sf::Vector2i areaSize;

            std::list<MetaLayer> layers;

            try
            {
                utils::json::Object& root = value->asObject();

                utils::json::Object& json_map = root["map"].asObject();

                name = json_map["name"].asString();

                { //map.tile
                    utils::json::Object& json_tile = json_map["tile"].asObject();
                    tile_geometry = json_tile["geometry"].asString();
                    tile_size = json_tile["size"].asFloat();
                }
                {//map.area
                    utils::json::Object& json_area = json_map["area"].asObject();
                    areaSize.x = json_area["width"].asInt();
                    areaSize.y = json_area["height"].asInt();
                }

                {//map.layers
                    utils::json::Array& json_layers = json_map["layers"].asArray();

                    for(utils::json::Value& value : json_layers)
                    {
                        utils::json::Object& json_obj = value.asObject();
                        int z = json_obj["z-buffer"].asInt();
                        std::string content_type = json_obj["content-type"].asString();
                        bool isStatic = false;
                        try{
                            isStatic = json_obj["static"].asBool();
                        }catch(...){};

                        layers.emplace_back(z,content_type,true,isStatic);
                    }
                }
            }
            catch (std::exception& e)
            {
                std::cerr<<"Exception when parsing file '"<<_mapDir<<"/map.json : "<<e.what()<<std::endl;
            }


            Map* res = nullptr;
            geometry::Geometry* geo = geometry::Geometry::factory(tile_geometry,tile_size);

            if(geo == nullptr)
            {
                std::cerr<<"Unknown geometry '"<<tile_geometry<<"'"<<std::endl;
                return nullptr;
            }
            res = new Map(geo,areaSize);

            ResourceManager<sf::Texture,std::string>* textureManager = nullptr; //should not be used on map creation (empty layers only)
            for(MetaLayer& layer : layers)
            {
                if(not layer.addToMap(res,*textureManager,sf::Vector2i(0,0)))
                {
                    std::cerr<<"Impossible to add layer ["<<layer<<"] to map"<<std::endl;
                    delete res;
                    res = nullptr;
                    break;
                }
            }

            return res;

        }

        std::unique_ptr<MetaArea> JsonMapLoader::_loadArea(int x,int y,Map* const map)
        {
            auto value = utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"areas.json"));
            std::unique_ptr<MetaArea> res;
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<_mapDir<<"/areas.json"<<std::endl;
                return res;
            }

            utils::json::Object& root = value->asObject();
            utils::json::Array& json_areas = root["areas"].asArray();

            try {
                for(utils::json::Value& json_area : json_areas)
                {
                    utils::json::Object& area = json_area.asObject();
                    sf::Vector2i area_pos;
                    area_pos.x = area["position-x"].asInt();
                    area_pos.y = area["position-y"].asInt();

                    if(area_pos.x != x or area_pos.y != y)
                    {
                        continue;
                    }

                    std::string name = area["name"].asString();
                    utils::json::Array& layers = area["layers"].asArray();
                    res.reset(new MetaArea(area_pos,name));

                    for(utils::json::Value& json_layer : layers)
                    {
                        if(not _parseLayer(map,json_layer.asObject(),res))
                        {
                            return nullptr;
                        }
                    }
                }

            }
            catch(std::exception& e)
            {
                std::cerr<<"Exception when parsing file '"<<_mapDir<<"/areas.json : "<<e.what()<<std::endl;
            };

            return res;
        }

        bool JsonMapLoader::_parseLayer(Map* map,utils::json::Object& root,std::unique_ptr<MetaArea>& meta)
        {
            int z = root["z-buffer"].asInt();
            VLayer* layer_ptr = map->atZ(z);
            if(not layer_ptr)
            {
                std::cerr<<"Map doesn't contain a layer a z-buffer "<<z<<std::endl;
                return false;
            }

            std::string type = layer_ptr->getType();

            std::function<std::shared_ptr<MetaLayerData>(Map* const, utils::json::Object&)> f;

            if(type == "tile")
            {
                f = &JsonMapLoader::_createTile;
            }
            else if(type == "sprite")
            {
                f = std::bind(&JsonMapLoader::_createSprite,std::placeholders::_1,std::placeholders::_2,false);
            }
            else if(type == "sprite_ptr")
            {
                f = std::bind(&JsonMapLoader::_createSprite,std::placeholders::_1,std::placeholders::_2,true);
            }
            else if(type == "entity")
            {
                f = &JsonMapLoader::_createEntity;
            }
            else
            {
                std::cerr<<"Unknow layer type "<<type<<std::endl;
                return false;
            }

            MetaLayer metaLayer(z,type,true,layer_ptr->isStatic());
            utils::json::Array& data = root["data"].asArray();

            for(utils::json::Value& value : data)
            {
                std::shared_ptr<MetaLayerData> d = f(map,value.asObject());
                if(not d)
                {
                    std::cerr<<"Imposible to create MetaData with json: "<<value<<std::endl;
                    return false;
                }

                metaLayer.add(d);
            }

            meta->add(std::move(metaLayer));

            return true;
        }

        std::shared_ptr<MetaLayerData> JsonMapLoader::_createTile(Map* const map,utils::json::Object& root)
        {
            std::string texture = root["texture"].asString();

            sf::IntRect rect(0,0,1,1);

            try{
                //point
                rect.left = root["position-x"].asInt();
                rect.top = root["position-y"].asInt();

                try //is it an area
                {
                    rect.width = root["width"].asInt();
                    rect.height = root["height"].asInt();
                } catch (...) { //or a point
                }
            }catch(...){ //all
                sf::Vector2i s = map->getAreaSize();
                rect.width = s.x;
                rect.height = s.y;
            }

            std::shared_ptr<MetaLayerData> res(new MetaLayerDataTileRect(texture,rect));

            return res;

        }

        std::shared_ptr<MetaLayerData> JsonMapLoader::_createSprite(Map* const map,utils::json::Object& root,bool isPtr)
        {
            std::string texture = root["texture"].asString();

            sf::Vector2i pos;
            {//position
                pos.x = root["position-x"].asInt();
                pos.y = root["position-y"].asInt();
            }

            sf::IntRect tex_rect;
            try{//texture rect
                utils::json::Object& rect = root["texture-rect"].asObject();
                tex_rect.top =  rect["top"].asInt();
                tex_rect.left = rect["left"].asInt();
                tex_rect.width = rect["width"].asInt();
                tex_rect.height = rect["height"].asInt();
            } catch(...){}

            sf::Vector2f tex_origin(0.5,1);
            try{//texture-center
                utils::json::Object& rect = root["texture-center"].asObject();
                tex_origin.x = rect["left"].asFloat();
                tex_origin.y = rect["top"].asFloat();
            }catch(...){}


            MetaLayerDataSprite* res = new MetaLayerDataSprite(texture,pos);
            res->setIsPtr(isPtr);
            res->setTextureOrigin(tex_origin);
            res->setTextureRect(tex_rect);

            return std::shared_ptr<MetaLayerData>(res);
        }

        std::shared_ptr<MetaLayerData> JsonMapLoader::_createEntity(Map* const map,utils::json::Object& root)
        {
            std::string texture = root["texture"].asString();

            sf::Vector2i pos;
            {//position
                pos.x = root["position-x"].asInt();
                pos.y = root["position-y"].asInt();
            }

            sf::IntRect tex_rect;
            try{//texture rect
                utils::json::Object& rect = root["texture-rect"].asObject();
                tex_rect.top =  rect["top"].asInt();
                tex_rect.left = rect["left"].asInt();
                tex_rect.width = rect["width"].asInt();
                tex_rect.height = rect["height"].asInt();
            } catch(...){}

            sf::Vector2f tex_origin(0.5,1);
            try{//texture-center
                utils::json::Object& rect = root["texture-center"].asObject();
                tex_origin.x = rect["left"].asFloat();
                tex_origin.y = rect["top"].asFloat();
            }catch(...){}


            MetaLayerDataEntity* res = new MetaLayerDataEntity(texture,pos);
            res->setTextureOrigin(tex_origin);
            res->setTextureRect(tex_rect);

            return std::shared_ptr<MetaLayerData>(res);
        }

    }
}
