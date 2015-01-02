#ifndef SFUTILS_ES_COMPONENT_HPP
#define SFUTILS_ES_COMPONENT_HPP

namespace sfutils
{
    namespace es
    {
        class Component
        {
            public:
                Component();
                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;

            protected:

            private:
        };
    }
}
#endif