#include <Box2D/Box2D.h>
#include <SFML-utils/box2D/converter.hpp>
#include <SFML-utils/box2D/DebugDraw.hpp>
#include <SFML/Graphics.hpp>

#include <list>

b2Body* create_box(b2World& world,int pos_x,int pos_y, int size_x,int size_y,b2BodyType type = b2_dynamicBody)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(sfutils::box2d::converter::pixel_to_meters<double>(pos_x),
                         sfutils::box2d::converter::pixel_to_meters<double>(pos_y));
    bodyDef.type = type;


    b2PolygonShape b2shape;
    b2shape.SetAsBox(sfutils::box2d::converter::pixel_to_meters<double>(size_x/2.0),
                     sfutils::box2d::converter::pixel_to_meters<double>(size_y/2.0));

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.4;
    fixtureDef.restitution= 0.5;
    fixtureDef.shape = &b2shape;

    b2Body* res = world.CreateBody(&bodyDef);
    res->CreateFixture(&fixtureDef);

    sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x,size_y));
    shape->setOrigin(size_x/2.0,size_y/2.0);
    shape->setPosition(sf::Vector2f(pos_x,pos_y));

    if(type == b2_dynamicBody)
        shape->setFillColor(sf::Color::Blue);
    else
        shape->setFillColor(sf::Color::White);

    res->SetUserData(shape);

    return res;
}

void display_world(b2World& world,sf::RenderWindow& render,sfutils::box2d::DebugDraw& debugDraw)
{
    world.Step(1.0/60,int32(8),int32(3));

    render.clear();

    for (b2Body* body=world.GetBodyList(); body!=nullptr; body=body->GetNext())
    {   
        sf::Shape* shape = static_cast<sf::Shape*>(body->GetUserData());
        shape->setPosition(sfutils::box2d::converter::meters_to_pixels(body->GetPosition().x),
                           sfutils::box2d::converter::meters_to_pixels(body->GetPosition().y));
        shape->setRotation(sfutils::box2d::converter::rad_to_deg<double>(body->GetAngle()));
        render.draw(*shape);
    }

    render.display();

    debugDraw.clear();
    world.DrawDebugData();
    debugDraw.display();
}

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML + Box2d");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    sfutils::box2d::DebugDraw debugDraw(sf::VideoMode(800, 600, 32),"SFML + BOX2D : DebugDraw");
    world.SetDebugDraw(&debugDraw);

    std::list<b2Body*> bodies;

    bodies.emplace_back(create_box(world,400,590,800,20,b2_staticBody));


    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;
            bodies.emplace_back(create_box(world,x,y,32,32));
        }
        display_world(world,window,debugDraw);
    }

    for(b2Body* body : bodies)
    {
        delete static_cast<sf::RectangleShape*>(body->GetUserData());
        world.DestroyBody(body);
    }

    return 0;
}
