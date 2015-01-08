#ifndef SFUTILS_ES_APPLICATION_HPP
#define SFUTILS_ES_APPLICATION_HPP

#include <SFML-utils/es/Entity.hpp>
#include <SFML-utils/es/System.hpp>

namespace sfutils
{
    namespace es
    {
        class Application
        {
            public:
                Application(const Application&) = delete;
                Application& operator=(const Application&) = delete;

                Application();

                EntityManager entites;
                SystemManager systems;

        };
    }
}
#endif
