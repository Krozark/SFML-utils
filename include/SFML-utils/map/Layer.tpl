#include <algorithm>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY,typename CONTENT>
        Layer<GEOMETRY,CONTENT>::Layer(int z) : VLayer(z)
        {
        }

        template<typename GEOMETRY,typename CONTENT>
        Layer<GEOMETRY,CONTENT>::~Layer()
        {
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::add(CONTENT&& content,bool resort)
        {
            _content.emplace_back(std::move(content));
            if(resort)
                sort();
        }

        template<typename GEOMETRY,typename CONTENT>
        bool Layer<GEOMETRY,CONTENT>::remove(CONTENT* content_ptr,bool resort)
        {
            auto& it = std::find_if(_content.begin(),_content.end(),[content_ptr](const CONTENT& content)->bool{
                                    return &content == content_ptr;
                                    });
            if(it != _content.end())
            {
                _content.erase(it);
                if(resort)
                    sort();
                return true;
            }
            return false;
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::sort()
        {
            _content.sort([](const CONTENT& a,const CONTENT& b)->bool{
                      auto pos_a = a.getPosition();
                      auto pos_b = b.getPosition();
                      return (pos_a.y < pos_b.y) or (pos_a.y == pos_b.y and pos_a.x < pos_b.x);
                    });
        }

        template<typename GEOMETRY,typename CONTENT>
        void Layer<GEOMETRY,CONTENT>::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const
        {
            auto end = _content.end();
            for(auto it = _content.begin();it != end;++it)
            {
                const CONTENT& content = *it;
                auto pos = content.getPosition();
                if(viewport.contains(pos.x,pos.y))
                    target.draw(content,states);
            }
        }
    }
}
