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

            utils::json::Value* value = utils::json::Driver::parse_file(utils::string::join("/",_mapDir,"map.json"));
            
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
                utils::json::Object& root = *value;

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
                std::cerr<<"Exeption whene parsing file '"<<_mapDir<<"/map.json : "<<e.what()<<std::endl;
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
                std::cerr<<"Unknow geometry '"<<tile_geometry<<"'"<<std::endl;
                return nullptr;
            }

            for(MetaLayer& layer : layers)
            {
                if(not layer.addToMap(res))
                {
                    std::cerr<<"Imposible to add layer ["<<layer<<"] to map"<<std::endl;
                    delete res;
                    res = nullptr;
                    break;
                }
            }

            return res;

        }

        MetaArea JsonMapLoader::_loadArea(int x,int y)
        {
            //#error TODO
            return MetaArea(x,y,"ERROR");
        }
    }
}
