#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        class VLayer : public sf::Drawable
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer();
                virtual ~VLayer();

            private:
                friend class VMap;
                virtual void sort() = 0;
        };
    }
}
#endif
