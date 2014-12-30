#include <iostream>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        Map<GEOMETRY>::Map(const utils::json::Object& root,float size) : VMap(root,size)
        {
            const utils::json::Array& layers = root["layers"];
            for(const utils::json::Value& value : layers)
            {
                const utils::json::Object& layer = value;
                std::string content = layer["content"].as_string();
                
                if(content == "tile")
                {
                    int height = layer["height"];
                    int width = layer["width"];
                    const utils::json::Object& texture = layer["texture"];

                    int tex_x = texture["x"];
                    int tex_y = texture["y"];
                    std::string img = texture["img"];

                    sf::Texture& tex = _textures.getOrLoad(img,img);
                    tex.setRepeated(true);

                    sf::Vector2u tex_size = tex.getSize();
                    int tex_size_tile_x = tex_size.x/tex_x;
                    int tex_size_tile_y = tex_size.y/tex_y;

                    auto current_layer = new Layer<GEOMETRY,Tile<GEOMETRY>>;

                    for(int y=0;y<height;++y)
                    {
                        for(int x=0;x<width;++x)
                        {
                            Tile<GEOMETRY> tile(x,y,tile_size);
                            sf::FloatRect rect = tile.getBounds();
                            std::cout<<y<<":"<<x<<" = "<<rect.top<<" : "<<rect.left<<" : "<<rect.width<<" : "<<rect.height<<std::endl;
                            tile.setTexture(&tex);
                            /*tile.setTextureRect(sf::IntRect(x*tex_size_tile_x,
                                                            y*tex_size_tile_y,
                                                            tex_size_tile_x,
                                                            tex_size_tile_y));*/
                            tile.setTextureRect(sf::IntRect(rect.top*tex_size_tile_y,
                                                            rect.left*tex_size_tile_x,
                                                            tex_size_tile_y,
                                                            tex_size_tile_y));
                            current_layer->add(std::move(tile));
                        }
                    }
                    _layers.emplace_back(current_layer);
                }
                else if(content == "sprite")
                {
                    auto current_layer = new Layer<GEOMETRY,sf::Sprite>;
                    const utils::json::Array& datas = layer["datas"].as_array();

                    for(const utils::json::Value& value : datas)
                    {
                        const utils::json::Object& data = value;
                        int x = data["x"];
                        int y = data["y"];
                        float ox = data["ox"].as_float();
                        float oy = data["oy"].as_float();

                        std::string img = data["img"];

                        sf::Sprite spr(_textures.getOrLoad(img,img));
                        spr.setPosition(GEOMETRY::mapCoordsToPixel(x,y)*tile_size);

                        sf::FloatRect rec = spr.getLocalBounds();
                        spr.setOrigin(rec.width*ox,rec.height*oy);

                        current_layer->add(std::move(spr));

                    }
                    _layers.emplace_back(current_layer);
                }
            }
            sortLayers();
        }

    }
}
