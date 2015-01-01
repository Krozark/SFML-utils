#include <SFML-utils/map/Configuration.hpp>

namespace sfutils
{
namespace map {
    ActionMap<int> Configuration::default_map_inputs;
    Configuration::__Initiatiser Configuration::__initiatiser__;

    void Configuration::initEvents()
    {
        default_map_inputs.map(MapInputs::MoveUp,Action(sf::Keyboard::Up));
        default_map_inputs.map(MapInputs::MoveDown,Action(sf::Keyboard::Down));
        default_map_inputs.map(MapInputs::MoveLeft,Action(sf::Keyboard::Left));
        default_map_inputs.map(MapInputs::MoveRight,Action(sf::Keyboard::Right));
    }

    void Configuration::init()
    {
        initEvents();
    }
}
}
