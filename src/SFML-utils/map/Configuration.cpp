#include <SFML-utils/map/Configuration.hpp>

namespace sfutils
{
namespace map {
    ActionMap<int> Configuration::defaultMapInputs;
    Configuration::__Initiatiser Configuration::__initiatiser__;

    void Configuration::initEvents()
    {
        defaultMapInputs.map(MapInputs::InputViewMoveUp,Action(sf::Keyboard::Up));
        defaultMapInputs.map(MapInputs::InputViewMoveDown,Action(sf::Keyboard::Down));
        defaultMapInputs.map(MapInputs::InputViewMoveLeft,Action(sf::Keyboard::Left));
        defaultMapInputs.map(MapInputs::InputViewMoveRight,Action(sf::Keyboard::Right)); 

        sf::Event e;
        e.type = sf::Event::EventType::MouseWheelMoved;
        e.mouseWheel.delta = -1;

        defaultMapInputs.map(MapInputs::InputViewZoomIn,Action(e));
        e.mouseWheel.delta = 1;

        defaultMapInputs.map(MapInputs::InputViewZoomOut,Action(e));
    }

    void Configuration::init()
    {
        initEvents();
    }
}
}
