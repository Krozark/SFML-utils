namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        Map<GEOMETRY>::Map(float size,const sf::Vector2i& areaSize) : VMap(size,areaSize)
        {
        }
        
        template<typename GEOMETRY>
        VLayer* Map<GEOMETRY>::createLayerOfGeometry(const std::string& content, int z, bool isStatic)const
        {
            return new Layer<Tile<GEOMETRY>>(content,z,isStatic);
        }

        template<typename GEOMETRY>
        VTile* Map<GEOMETRY>::createTileToLayer(int pos_x,int pos_y,float scale,sf::Texture* texture,VLayer* layer)const
        {
            auto l = dynamic_cast<Layer<Tile<GEOMETRY>>*>(layer);

            if(not l)
                return nullptr;

            Tile<GEOMETRY> tile(pos_x,pos_y,_tileSize);
            tile.setTexture(texture);
            tile.setTextureRect(GEOMETRY::getTextureRect(pos_x,pos_y,_tileSize));

            return l->add(std::move(tile),false);
        }

        template<typename GEOMETRY>
        sf::Vector2i Map<GEOMETRY>::mapPixelToCoords(float x,float y)const
        {
            return GEOMETRY::mapPixelToCoords(x,y,_tileSize);
        }

        template<typename GEOMETRY>
        sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(int x,int y)const
        {
            return GEOMETRY::mapCoordsToPixel(x,y,_tileSize);
        }

        template<typename GEOMETRY>
        const sf::ConvexShape Map<GEOMETRY>::getShape()const
        {
            sf::ConvexShape shape = GEOMETRY::getShape();
            shape.setScale(_tileSize,_tileSize);
            return shape;
        }

        /*
        template<typename GEOMETRY>
        std::list<sf::Vector2i> Map<GEOMETRY>::getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const
        {
            int distance = GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
            std::list<sf::Vector2i> res;

            sf::Vector2f p(dest.x - origin.x,
                           dest.y - origin.y);
            float delta = 1.0/distance;
            float cumul = 0;
            res.emplace_back(origin);
            for(int i = 0; i<distance;++i)
            {

                sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul,origin.y + p.y * cumul);
                if(res.back() != pos)
                    res.emplace_back(pos);
                cumul +=delta;
            }
            if(res.back() != dest)
                res.emplace_back(dest);
            return res;
        }

        template<typename GEOMETRY>
        sf::Vector2i Map<GEOMETRY>::getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const
        {
            int distance = GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
            sf::Vector2i res = origin;

            sf::Vector2f p(dest.x - origin.x,
                           dest.y - origin.y);
            float delta = 1.0/distance;
            float cumul = 0;
            for(int i = 0; i<distance;++i)
            {

                sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul,origin.y + p.y * cumul);
                if(pos != res)
                {
                    res = pos;
                    break;
                }
                cumul +=delta;
            }
            return res;
        }
        */

        template<typename GEOMETRY>
        int Map<GEOMETRY>::getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest) const
        {
            return GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
        }
    }
}
