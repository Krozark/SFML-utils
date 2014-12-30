namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        Map<GEOMETRY>::Map()
        {
        }

        template<typename GEOMETRY>
        Map<GEOMETRY>::~Map()
        {
            for(VLayer<GEOMETRY>* layer : _layers)
                delete(layer);
        }

        template<typename GEOMETRY>
        bool Map<GEOMETRY>::loadFromFile(const std::string &filename)
        {
            sortLayers();
            return false;
        }

        template<typename GEOMETRY>
        void Map<GEOMETRY>::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for(VLayer<GEOMETRY>* layer : _layers)
                target.draw(*layer,states);
        }

        template<typename GEOMETRY>
        void Map<GEOMETRY>::sortLayers()
        {
            for(VLayer<GEOMETRY>* layer : _layers)
                layer->sort();
        }
    }
}
