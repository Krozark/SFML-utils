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
                    auto current_layer = new Layer<GEOMETRY,Tile<GEOMETRY>>;
                    const utils::json::Array& textures = layer["texture"];
                    for(const utils::json::Object& texture : textures)
                    {
                        int tex_x = texture["x"];
                        int tex_y = texture["y"];
                        int height = std::max<int>(0,texture["height"].as_int());
                        int width = std::max<int>(0,texture["width"].as_int());
                        std::string img = texture["img"];

                        sf::Texture& tex = _textures.getOrLoad(img,img);
                        tex.setRepeated(true);

                        /*int tex_x = texture["x"];
                        int tex_y = texture["y"];
                        sf::Vector2u tex_size = tex.getSize();
                        int tex_size_tile_x = tex_size.x/tex_x;
                        int tex_size_tile_y = tex_size.y/tex_y;*/


                        for(int y=tex_y;y< tex_y + height;++y)
                        {
                            for(int x=tex_x;x<tex_x + width;++x)
                            {
                                Tile<GEOMETRY> tile(x,y,tile_size);
                                tile.setTexture(&tex);
                                tile.setTextureRect(GEOMETRY::getTextureRect(x,y,tile_size));

                                current_layer->add(std::move(tile));
                            }
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
                        float ox = 0.5;
                        float oy = 1;
                        try{
                            ox = data["ox"].as_float();
                        }catch(...){}

                        try{
                            oy = data["oy"].as_float();
                        }catch(...){}

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
