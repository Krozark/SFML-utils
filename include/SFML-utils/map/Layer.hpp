#ifndef SFUTILS_MAP_LAYER_HPP
#define SFUTILS_MAP_LAYER_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <vector>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY,typename CONTENT>
        class Layer : public VLayer<GEOMETRY>
        {
            public:
                Layer(const Layer&) = delete;
                Layer& operator=(const Layer&) = delete;

                Layer();
                virtual ~Layer();

                //load

            private:
                std::vector<CONTENT> _content;
                
                virtual void sort() override;
        };
    }
}
#include <SFML-utils/map/Layer.tpl>
#endif
