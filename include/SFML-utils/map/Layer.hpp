#ifndef SFUTILS_MAP_LAYER_HPP
#define SFUTILS_MAP_LAYER_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <list>

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

                void add(CONTENT&& content,bool resort=true);

                bool remove(CONTENT* content_ptr,bool resort=true);

                //load

            private:
                std::list<CONTENT> _content;
                
                virtual void sort() override;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const override;
        };
    }
}
#include <SFML-utils/map/Layer.tpl>
#endif
