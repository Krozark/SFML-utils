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
        void Layer<GEOMETRY,CONTENT>::sort()
        {
            std::sort(_content.begin(),_content.end(),[](const CONTENT& a,const CONTENT& b)->bool{
                      auto pos_a = a.getPosition();
                      auto pos_b = b.getPosition();
                      return (pos_a.y < pos_b.y) or (pos_a.y == pos_b.y and pos_a.x < pos_b.x);
                    });
        }
    }
}
