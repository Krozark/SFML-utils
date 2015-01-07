#include <SFML-utils/ES.hpp>

#include <iostream>

using namespace sfutils;

struct Component1 : Component<Component1>
{
    explicit Component1(float f) : _f(f){};

    float _f;
};

struct Component2 : Component<Component2>
{
    explicit Component2(int i,const std::string& str) : _i(i), _str(str){};

    int _i;
    std::string _str;
};

int main(int argc,char* argv[])
{

    EntityManager manager;

    {
        std::uint32_t id = manager.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = manager.create();
       std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = manager.get(id);
        e.add<Component1>(42);
        auto comp = e.component<Component1>();
        std::cout<<"Add Component1(_f=42)"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = manager.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = manager.get(id);
        e.add<Component2>(72,"plop");
        auto comp = e.component<Component2>();
        std::cout<<"Add Component2(_i=72,_str=\"plop\")"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = manager.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = manager.get(id);
        e.add<Component1>(45.89);
        auto comp1 = e.component<Component1>();
        std::cout<<"Add Component1(_f=45.89)"<<std::endl;
        e.add<Component2>(48.9,"test");
        auto comp2 = e.component<Component2>();
        std::cout<<"Add Component2(_i=48.9,_str=\"test\")"<<std::endl;
        auto comp_all = e.components<Component1,Component2>();
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = manager.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 
    }

    std::cout<<std::endl;

    {
        std::cout<<"+++ All entity ids +++"<<std::endl;
        for(auto i : manager)
            std::cout<<i<<std::endl;
    }

    {
        std::cout<<"+++ Show entity with Component1 +++"<<std::endl;
        Component1::Handle component_test;
        auto view = manager.getByComponents(component_test);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component1(_f="<<component_test->_f<<")"<<std::endl;
            ++begin;
        }
    }

    std::cout<<std::endl;


    {
        std::cout<<"+++ Show entity with Component2 +++"<<std::endl;
        Component2::Handle component_test;
        auto view = manager.getByComponents(component_test);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component2(_i="<<component_test->_i<<",_str="<<component_test->_str<<")"<<std::endl;
            ++begin;
        }
    }

    std::cout<<std::endl;

    {
        std::cout<<"+++ Show entity with Component1 and Component2 +++"<<std::endl;
        Component1::Handle component_test1;
        Component2::Handle component_test2;
        auto view = manager.getByComponents(component_test1,component_test2);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component1(_f="<<component_test1->_f<<")\n"
            <<"\t Component2(_i="<<component_test2->_i<<",_str="<<component_test2->_str<<")"<<std::endl;
            ++begin;
        }
    }
    return 0;
};
