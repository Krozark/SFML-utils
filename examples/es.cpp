#include <SFML-utils/ES.hpp>

#include <iostream>

using namespace sfutils;

struct ComponentTest : Component<ComponentTest>
{
    explicit ComponentTest(float f) : _f(f){};

    float _f;
};

int main(int argc,char* argv[])
{
    EntityManager manager;

    {
        std::uint32_t id = manager.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 
        Entity& e = manager.get(id);
        e.add<ComponentTest>(42);
        ComponentHandle<ComponentTest> comp = e.component<ComponentTest>();
        std::cout<<"Component content: "<<comp->_f<<std::endl;

    }
    return 0;
};
