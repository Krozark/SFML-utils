#include <algorithm>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY,typename CONTENT>
        Layer<GEOMETRY,CONTENT>::Layer(const std::string& type,int z,bool isStatic) : VLayer(type,z), _isStatic(isStatic)
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
        void Layer<GEOMETRY,CONTENT>::draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport)
        {
            if(_isStatic)
            {
                if(_lastViewport != viewport)
                {
                    std::cout<<viewport.left<<" "<<viewport.top<<" "<<viewport.width<<" "<<viewport.height<<std::endl;
                    sf::Vector2u size(viewport.width+0.5,viewport.height+0.5);
                    if(_renderTexture.getSize() != size)
                    {
                        _renderTexture.create(size.x,size.y);
                        _sprite.setTexture(_renderTexture.getTexture(),true);
                    }

                    _renderTexture.setView(sf::View(viewport));

                    _renderTexture.clear();
                    auto end = _content.end();
                    for(auto it = _content.begin();it != end;++it)
                    {
                        CONTENT& content = *it;
                        auto pos = content.getPosition();
                        if(viewport.contains(pos.x,pos.y))
                        {
                            _renderTexture.draw(content/*,states*/);
                        }
                    }
                    _renderTexture.display();
                    _lastViewport = viewport;
                    //states.transform.translate(viewport.left,viewport.top);
                    
                    _sprite.setPosition(viewport.left,viewport.top);

                }
                //target.draw(_sprite,states);
                target.draw(_sprite,states);
            }
            else
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

        template<typename GEOMETRY,typename CONTENT>
        bool Layer<GEOMETRY,CONTENT>::isStatic()const
        {
            return _isStatic;
        }
    }
}
