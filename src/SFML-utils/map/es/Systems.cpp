#include <SFML-utils/map/es/Systems.hpp>
#include <SFML-utils/map/es/Components.hpp>

namespace sfutils
{
namespace map
{
    SysSkinDynamic::SysSkinDynamic()
    {
    }

    SysSkinDynamic::~SysSkinDynamic()
    {
    }

    void SysSkinDynamic::update(sfutils::es::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompSkinDynamic::Handle skin;
        auto view = manager.getByComponents(skin);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            skin->_sprite.update(dt);
        }
    }

}
}
