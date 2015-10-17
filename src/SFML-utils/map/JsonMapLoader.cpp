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

        Map* JsonMapLoader::_createMap()
        {

            std::unique_ptr<utils::json::Value> value(utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"map.json")));

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
                utils::json::Object& root = value->as_object();

                utils::json::Object& json_map = root["map"].as_object();

                name = json_map["name"].as_string();

                { //map.tile
                    utils::json::Object& json_tile = json_map["tile"].as_object();
                    tile_geometry = json_tile["geometry"].as_string();
                    tile_size = json_tile["size"].as_float();
                }
                {//map.area
                    utils::json::Object& json_area = json_map["area"].as_object();
                    areaSize.x = json_area["width"].as_int();
                    areaSize.y = json_area["height"].as_int();
                }

                {//map.layers
                    utils::json::Array& json_layers = json_map["layers"].as_array();

                    for(utils::json::Value& value : json_layers)
                    {
                        utils::json::Object& json_obj = value.as_object();
                        int z = json_obj["z-buffer"].as_int();
                        std::string content_type = json_obj["content-type"].as_string();
                        bool isStatic = false;
                        try{
                            isStatic = json_obj["static"].as_bool();
                        }catch(...){};

                        layers.emplace_back(z,content_type,isStatic);
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
            std::unique_ptr<utils::json::Value> value(utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"areas.json")));
            std::unique_ptr<MetaArea> res;
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<_mapDir<<"/areas.json"<<std::endl;
                return res;
            }

            utils::json::Object& root = value->as_object();
            utils::json::Array& json_areas = root["areas"].as_array();

            try {
                for(utils::json::Value& json_area : json_areas)
                {
                    utils::json::Object& area = json_area.as_object();
                    sf::Vector2i area_pos;
                    area_pos.x = area["position-x"].as_int();
                    area_pos.y = area["position-y"].as_int();

                    if(area_pos.x != x or area_pos.y != y)
                        continue;

                    std::string name = area["name"].as_string();
                    utils::json::Array& layers = area["layers"].as_array();
                    res.reset(new MetaArea(area_pos,name));

                    for(utils::json::Value& json_layer : layers)
                        if(not _parseLayer(map,json_layer.as_object(),res))
                            return nullptr;
                    break;
                }

            } catch(std::exception& e){
                std::cerr<<"Exception when parsing file '"<<_mapDir<<"/areas.json : "<<e.what()<<std::endl;
            };

            return res;
        }

        bool JsonMapLoader::_parseLayer(Map* map,utils::json::Object& root,std::unique_ptr<MetaArea>& meta)
        {
            int z = root["z-buffer"].as_int();
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

            MetaLayer metaLayer(z,type,layer_ptr->isStatic());
            utils::json::Array& data = root["data"].as_array();

            for(utils::json::Value& value : data)
            {
                std::shared_ptr<MetaLayerData> d = f(map,value.as_object());
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
            std::string texture = root["texture"].as_string();

            sf::IntRect rect(0,0,1,1);

            try{
                //point
                rect.left = root["position-x"].as_int();
                rect.top = root["position-y"].as_int();

                try //is it an area
                {
                    rect.width = root["width"].as_int();
                    rect.height = root["height"].as_int();
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
            std::string texture = root["texture"].as_string();

            sf::Vector2i pos;
            {//position
                pos.x = root["position-x"].as_int();
                pos.y = root["position-y"].as_int();
            }

            sf::IntRect tex_rect;
            try{//texture rect
                utils::json::Object& rect = root["texture-rect"].as_object();
                tex_rect.top =  rect["top"].as_int();
                tex_rect.left = rect["left"].as_int();
                tex_rect.width = rect["width"].as_int();
                tex_rect.height = rect["height"].as_int();
            } catch(...){}

            sf::Vector2f tex_origin(0.5,1);
            try{//texture-center
                utils::json::Object& rect = root["texture-center"].as_object();
                tex_origin.x = rect["left"].as_float();
                tex_origin.y = rect["top"].as_float();
            }catch(...){}


            MetaLayerDataSprite* res = new MetaLayerDataSprite(texture,pos);
            res->setIsPtr(isPtr);
            res->setTextureOrigin(tex_origin);
            res->setTextureRect(tex_rect);

            return std::shared_ptr<MetaLayerData>(res);
        }

        std::shared_ptr<MetaLayerData> JsonMapLoader::_createEntity(Map* const map,utils::json::Object& root)
        {
            std::string texture = root["texture"].as_string();

            sf::Vector2i pos;
            {//position
                pos.x = root["position-x"].as_int();
                pos.y = root["position-y"].as_int();
            }

            sf::IntRect tex_rect;
            try{//texture rect
                utils::json::Object& rect = root["texture-rect"].as_object();
                tex_rect.top =  rect["top"].as_int();
                tex_rect.left = rect["left"].as_int();
                tex_rect.width = rect["width"].as_int();
                tex_rect.height = rect["height"].as_int();
            } catch(...){}

            sf::Vector2f tex_origin(0.5,1);
            try{//texture-center
                utils::json::Object& rect = root["texture-center"].as_object();
                tex_origin.x = rect["left"].as_float();
                tex_origin.y = rect["top"].as_float();
            }catch(...){}


            MetaLayerDataEntity* res = new MetaLayerDataEntity(texture,pos);
            res->setTextureOrigin(tex_origin);
            res->setTextureRect(tex_rect);

            return std::shared_ptr<MetaLayerData>(res);
        }

    }
}
