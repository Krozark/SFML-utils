#include <SFML-utils/map/JsonMapLoader.hpp>

#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/tileShapes/HexaIso.hpp>
#include <SFML-utils/map/tileShapes/Hexa.hpp>
#include <SFML-utils/map/tileShapes/Square.hpp>
#include <SFML-utils/map/tileShapes/SquareIso.hpp>
#include <SFML-utils/map/tileShapes/SquareStaggered.hpp>
#include <SFML-utils/map/tileShapes/SquareIsoStaggered.hpp>

#include <utils/json/Driver.hpp>
#include <utils/string.hpp>

namespace sfutils
{
    namespace map
    {
        JsonMapLoader::JsonMapLoader(const std::string& mapDirectory) : _mapDir(mapDirectory)
        {
        }

        VMap* JsonMapLoader::createMap()
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


            VMap* res = nullptr;

            if(tile_geometry == "Hexa")
            {
                res = new Map<geometry::Hexa>(tile_size,areaSize);
            }
            else if(tile_geometry == "HexaIso")
            {
                res = new Map<geometry::HexaIso>(tile_size,areaSize);
            }
            else if(tile_geometry == "Square")
            {
                res = new Map<geometry::Square>(tile_size,areaSize);
            }
            else if(tile_geometry == "SquareIso")
            {
                res = new Map<geometry::SquareIso>(tile_size,areaSize);
            }
            else if(tile_geometry == "SquareStaggered")
            {
                res = new Map<geometry::SquareStaggered>(tile_size,areaSize);
            }
            else if(tile_geometry == "SquareIsoStaggered")
            {
                res = new Map<geometry::SquareIsoStaggered>(tile_size,areaSize);
            }
            else
            {
                std::cerr<<"Unknown geometry '"<<tile_geometry<<"'"<<std::endl;
                return nullptr;
            }

            for(MetaLayer& layer : layers)
            {
                if(not layer.addToMap(res))
                {
                    std::cerr<<"Impossible to add layer ["<<layer<<"] to map"<<std::endl;
                    delete res;
                    res = nullptr;
                    break;
                }
            }

            return res;

        }

        std::unique_ptr<MetaArea> JsonMapLoader::_loadArea(int x,int y)
        {
            std::unique_ptr<utils::json::Value> value(utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"areas.json")));
            std::unique_ptr<MetaArea> res;
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<_mapDir<<"/map.json"<<std::endl;
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
                    {
                        utils::json::Object& json_layer_obj = json_layer.as_object();
                        int z = json_layer_obj["z-buffer"].as_int();
                        VLayer* layer_ptr = map->atZ(z);
                        if(not layer_ptr)
                        {
                            std::cerr<<"Error when parsing file '"<<_mapDir<<"/areas.json : Map doesn't contain a layer a z-buffer "<<z<<std::endl;
                            return nullptr;
                        }
                        utils::json::Array& layers

                    }
                }

            } catch(std::exception& e){
                std::cerr<<"Exception when parsing file '"<<_mapDir<<"/areas.json : "<<e.what()<<std::endl;
            };

            return res;
        }
    }
}
