#ifndef SFUTILS_MAP_MAP_HPP
#define SFUTILS_MAP_MAP_HPP

namespace sfutils
{
    namespace map
    {
        class Map
        {
            public:
                Map(const Map&) = delete;
                Map& operator=(const Map&) = delete;

                Map();

            protected:

            private:
        };
    }
}
#include <SFML-utils/map/Map.tpl>
#endif
