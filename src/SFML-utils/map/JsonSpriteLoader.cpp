#include <SFML-utils/map/JsonSpriteLoader.hpp>

#include <utils/json/Driver.hpp>
#include <memory>

namespace sfutils
{
    namespace map
    {
        std::unordered_map<std::string,sf::IntRect> JsonSpriteLoader::parse(const std::string& filename)
        {
            std::unordered_map<std::string,sf::IntRect> res;
            std::unique_ptr<utils::json::Value> value(utils::json::Driver::parse_file(filename));
            if(not value)
            {
                std::cerr<<"Impossible to parse file "<<filename<<std::endl;
                return res;
            }

            try
            {
                utils::json::Object& root = value->as_object();
                utils::json::Array& json_frames = root["frames"].as_array();
                for(utils::json::Value& value : json_frames)
                {
                    utils::json::Object& obj = value.as_object();
                    std::string name = obj["filename"].as_string();

                    utils::json::Object& frame = obj["frame"].as_object();
                    sf::IntRect rect;
                    rect.left = frame["x"].as_int();
                    rect.top = frame["y"].as_int();
                    rect.width = frame["w"].as_int();
                    rect.height = frame["h"].as_int();

                    res.emplace(name,rect);
                    
                }
            }
            catch(std::exception& e)
            {
                std::cerr<<"Exception when parsing file '"<<filename<<"' : "<<e.what()<<std::endl;
            }
            
            return res;
        }
    }
}
