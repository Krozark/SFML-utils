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

            utils::json::Value* value = utils::json::Driver::parse_file(utils::string::join(_mapDir,"map.json"));
            
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<_mapDir<<"/map.json"<<std::endl;
                return nullptr;
            }

            std::string name;

            std::string tile_geometry;
            float tile_size;

            int area_x;
            int area_y;

            std::list<MetaLayer> layers;


            try
            {
                utils::json::Object& root = *value;

                utils::json::Object& json_map = root["map"].as_object();

                name = json_map["name"].as_string();

                { //map.tile
                    utils::json::Object& json_tile = json_map["tile"].as_object();
                    tile_geometry = json_map["geometry"].as_string();
                    tile_size = json_map["size"].as_int();
                }
                {//map.area
                    utils::json::Object& json_area = json_map["area"].as_object();
                }

                {//map.layers
                    utils::json::Array& json_layers = json_map["layers"].as_array();
                }
            }
            catch (std::exception& e)
            {
                std::cerr<<"Exeption whene parsing file '"<<_mapDir<<"/map.json : "<<e.what()<<std::endl;
            }


            VMap* res = nullptr;

            if(tile_geometry == "Hexa")
            {
                res = new Map<geometry::Hexa>(tile_size);
            }
            else if(tile_geometry == "HexaIso")
            {
                res = new Map<geometry::HexaIso>(tile_size);
            }
            else if(tile_geometry == "Square")
            {
                res = new Map<geometry::Square>(tile_size);
            }
            else if(tile_geometry == "SquareIso")
            {
                res = new Map<geometry::SquareIso>(tile_size);
            }
            else if(tile_geometry == "SquareStaggered")
            {
                res = new Map<geometry::SquareStaggered>(tile_size);
            }
            else if(tile_geometry == "SquareIsoStaggered")
            {
                res = new Map<geometry::SquareIsoStaggered>(tile_size);
            }
            else
            {
                std::cerr<<"Unknow geometry '"<<tile_geometry<<"'"<<std::endl;
                return false;
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
