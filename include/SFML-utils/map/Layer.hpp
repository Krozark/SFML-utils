#ifndef SFUTILS_MAP_LAYER_HPP
#define SFUTILS_MAP_LAYER_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <vector>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY,typename CONTENT>
        class Layer : public VLayer
        {
            public:
                Layer(const Layer&) = delete;
                Layer& operator=(const Layer&) = delete;

                Layer();
                virtual ~Layer();

                void add(CONTENT&& content);

                //load

            private:
                std::vector<CONTENT> _content;
                
                virtual void sort() override;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#include <SFML-utils/map/Layer.tpl>
#endif
