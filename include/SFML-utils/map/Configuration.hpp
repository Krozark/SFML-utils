#ifndef SFUTILS_GUI_CONFIGURATION_HPP
#define SFUTILS_GUI_CONFIGURATION_HPP

#include <SFML-utils/core/ResourceManager.hpp>
#include <SFML-utils/core/ActionMap.hpp>

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        class Configuration
        {
            public:
                Configuration() = delete;
                Configuration(const Configuration&) = delete;
                Configuration& operator=(const Configuration&) = delete;

                enum MapInputs {
                    MoveUp,
                    MoveDown,
                    MoveLeft,
                    MoveRight
                };

                static ActionMap<int> default_map_inputs;

            private:

                static void initEvents();

                static void init();

                static struct __Initiatiser {
                    __Initiatiser(){
                        Configuration::init();
                    };
                } __initiatiser__;
        };
    }
}
#endif
