#include <algorithm>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY,typename CONTENT>
        Layer<GEOMETRY,CONTENT>::Layer()
        {
        }

        template<typename GEOMETRY,typename CONTENT>
        Layer<GEOMETRY,CONTENT>::~Layer()
        {
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::add(CONTENT&& content)
        {
            _content.emplace_back(std::move(content));
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::sort()
        {
            std::sort(_content.begin(),_content.end(),[](const CONTENT& a,const CONTENT& b)->bool{
                      auto pos_a = a.getPosition();
                      auto pos_b = b.getPosition();
                      return (pos_a.y < pos_b.y) or (pos_a.y == pos_b.y and pos_a.x < pos_b.x);
                    });
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for(const CONTENT& content : _content)
                target.draw(content,states);
        }
    }
}
