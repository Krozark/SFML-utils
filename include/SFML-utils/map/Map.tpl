namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        Map<GEOMETRY>::Map(float size) : VMap(size)
        {
        }

        template<typename GEOMETRY>
        void Map<GEOMETRY>::loadFromJson(const utils::json::Object& root)
        {
            const utils::json::Array& layers = root["layers"];
            for(const utils::json::Value& value : layers)
            {
                const utils::json::Object& layer = value;
                std::string content = layer["content"].as_string();

                int z = 0;
                try{
                    z = layer["z"].as_int();
                } catch(...){}

                bool isStatic = false;
                try {
                    isStatic = layer["static"].as_bool();
                }catch(...){}
                
                if(content == "tile")
                {
                    auto current_layer = new Layer<GEOMETRY,Tile<GEOMETRY>>(content,z,isStatic);
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

                        for(int y=tex_y;y< tex_y + height;++y)
                        {
                            for(int x=tex_x;x<tex_x + width;++x)
                            {
                                Tile<GEOMETRY> tile(x,y,_tile_size);
                                tile.setTexture(&tex);
                                tile.setTextureRect(GEOMETRY::getTextureRect(x,y,_tile_size));

                                current_layer->add(std::move(tile),false);
                            }
                        }
                    }
                    add(current_layer,false);
                }
                else if(content == "sprite")
                {
                    auto current_layer = new Layer<GEOMETRY,sf::Sprite>(content,z,isStatic);
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
                        spr.setPosition(GEOMETRY::mapCoordsToPixel(x,y)*_tile_size);

                        sf::FloatRect rec = spr.getLocalBounds();
                        spr.setOrigin(rec.width*ox,rec.height*oy);

                        current_layer->add(std::move(spr),false);

                    }
                    add(current_layer,false);
                }
            }
            sortLayers();
        }

        template<typename GEOMETRY>
        sf::Vector2i Map<GEOMETRY>::mapPixelToCoords(int x,int y)const
        {
            return GEOMETRY::mapPixelToCoords(x,y);
        }

        template<typename GEOMETRY>
        sf::Vector2i Map<GEOMETRY>::mapPixelToCoords(const sf::Vector2i& pos)const
        {
            return GEOMETRY::mapPixelToCoords(pos.x,pos.y);
        }

        template<typename GEOMETRY>
        sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(int x,int y)const
        {
            return GEOMETRY::mapCoordsToPixel(x,y);
        }

        template<typename GEOMETRY>
        sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(const sf::Vector2i& pos)const
        {
            return GEOMETRY::mapCoordsToPixel(pos.x,pos.y);
        }

    }
}
