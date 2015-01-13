#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace sfutils
{
    namespace map
    {
        class VLayer
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer(const std::string& type,int z=0);
                virtual ~VLayer();
                virtual void sort() = 0;

                int z()const;
                const std::string& getType()const;

            private:
                friend class VMap;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) = 0;

                const std::string _type;
                const int _z;
        };
    }
}
#endif
