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

                Layer(const std::string& type,int z=0,bool isStatic=false);
                virtual ~Layer();

                CONTENT* add(const CONTENT& content,bool resort=true);
                CONTENT* add(CONTENT&& content,bool resort=true);

                bool remove(CONTENT* content_ptr,bool resort=true);

                virtual void sort() override;

                bool isStatic()const;
                

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) override;

                std::list<CONTENT> _content;

                const bool _isStatic;
                sf::RenderTexture _renderTexture;
                sf::Sprite _sprite;
                sf::FloatRect _lastViewport;
        };
    }
}
#include <SFML-utils/map/Layer.tpl>
#endif
