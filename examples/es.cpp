#include <SFML-utils/ES.hpp>

#include <iostream>

#include <SFML/System.hpp>

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


struct System1 : System<System1>
{
    virtual void update(EntityManager& manager,float dt) override
    {
        std::cout<<"System1::update("<<dt<<") manage entities with Component1 only"<<std::endl;

        Component1::Handle component;
        auto view = manager.getByComponents(component);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component1(_f="<<component->_f<<")"<<std::endl;
            ++begin;
        }
    }
};

struct System2 : System<System2>
{
    virtual void update(EntityManager& manager,float dt) override
    {
        std::cout<<"System2::update("<<dt<<") manager entities with Component2 only"<<std::endl;
        Component2::Handle component;
        auto view = manager.getByComponents(component);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component2(_i="<<component->_i<<",_str="<<component->_str<<")"<<std::endl;
            ++begin;
        }
    }
};

struct System3 : System<System3>
{
    virtual void update(EntityManager& manager,float dt) override
    {
        std::cout<<"System3::update("<<dt<<") manager entities with Component1 and Component2"<<std::endl;
        Component1::Handle component1;
        Component2::Handle component2;
        auto view = manager.getByComponents(component1,component2);

        for(auto entity : view)
        {
            std::cout<<"Entity id: "<<entity->id()<<"\n"
            <<"\t Component1(_f="<<component1->_f<<")"
            <<"\t Component2(_i="<<component2->_i<<",_str="<<component2->_str<<")"<<std::endl;
        }
    }
};

struct System4 : System<System4>
{
    explicit System4(std::string str) : _str(str){};

    virtual void update(EntityManager& manager,float dt) override
    {
        int i =0;
        for(auto id : manager)
        {
            Entity& e = manager.get(id);
            ++i;
        }
        std::cout<<"Process to "<<i<<" entities in "<<dt<<" seconds. FPS: "<<(1/dt)<<std::endl;
    }

    private:
        std::string _str;
};

int main(int argc,char* argv[])
{

    EntityManager entities;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
       std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = entities.get(id);
        e.add<Component1>(42);
        /*auto comp =*/ e.component<Component1>();
        std::cout<<"Add Component1(_f=42)"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = entities.get(id);
        e.add<Component2>(72,"plop");
        /*auto comp =*/ e.component<Component2>();
        std::cout<<"Add Component2(_i=72,_str=\"plop\")"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        Entity& e = entities.get(id);
        e.add<Component1>(45.89);
        /*auto comp1 =*/ e.component<Component1>();
        std::cout<<"Add Component1(_f=45.89)"<<std::endl;
        e.add<Component2>(48.9,"test");
        /*auto comp2 =*/ e.component<Component2>();
        std::cout<<"Add Component2(_i=48.9,_str=\"test\")"<<std::endl;
        /*auto comp_all =*/ e.components<Component1,Component2>();
    }

    std::cout<<std::endl;

    for(int i = 0; i<1000000;++i)
    {
        std::uint32_t id = entities.create();
        //std::cout<<"Create entity of id: "<<id<<std::endl; 
    }

    std::cout<<std::endl;

    /*{
        std::cout<<"+++ All entity ids +++"<<std::endl;
        for(auto i : entities)
            std::cout<<i<<std::endl;
    }*/

    SystemManager systems(entities);
    systems.add<System1>();
    systems.add<System2>();
    systems.add(std::shared_ptr<System3>(new System3));
    systems.add<System4>("param");

    std::cout<<"=== update All systems ==="<<std::endl;
    systems.updateAll(0);

    std::cout<<"=== System1 ==="<<std::endl;
    systems.update<System1>(1);

    std::cout<<"=== System2 ==="<<std::endl;
    systems.update<System2>(2);

    std::cout<<"=== System3 ==="<<std::endl;
    systems.update<System3>(3);


    sf::Clock clock;
    while(true)
    {
        systems.update<System4>(clock.restart().asSeconds());
    }

    return 0;
};
