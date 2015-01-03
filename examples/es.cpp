#include <SFML-utils/ES.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
    sfutils::EntityManager manager;

    {
        sfutils::Entity& e = manager.create();
        std::cout<<"Create entity of id: "<<e.id()<<std::endl; 
    }
    return 0;
};
