#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        class VLayer
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer();
                virtual ~VLayer();

            private:
                friend class VMap;
                virtual void sort() = 0;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const = 0;
        };
    }
}
#endif
