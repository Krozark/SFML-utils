#ifndef SFUTILS_MAP_MAP_HPP
#define SFUTILS_MAP_MAP_HPP

#include <string>
#include <SFML-utils/map/VLayer.hpp>

#include <utils/json/Driver.hpp>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        class Map : public sf::Drawable
        {
            public:
                Map(const Map&) = delete;
                Map& operator=(const Map&) = delete;

                Map();
                ~Map();

                bool loadFromFile(const std::string &filename);

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                void sortLayers();

                std::vector<VLayer<GEOMETRY>*> _layers;
        };
    }
}
#include <SFML-utils/map/Map.tpl>
#endif
