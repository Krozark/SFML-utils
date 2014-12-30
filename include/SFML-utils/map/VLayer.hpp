#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY> class Map;
        template<typename GEOMETRY>
        class VLayer : public sf::Drawable
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer();
                virtual ~VLayer();

            private:
                friend class Map<GEOMETRY>;
                virtual void sort() = 0;
        };
    }
}
#include <SFML-utils/map/VLayer.tpl>
#endif
