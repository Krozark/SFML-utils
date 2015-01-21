#include <SFML-utils/Map.hpp>
#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <iostream>

enum TEXTURES
{
    EYE
};

sfutils::ResourceManager<sf::Texture,int> textures;

enum ANIMATION
{
    EYE_LEFT,
    EYE_RIGHT
};


class E : public sfutils::Entity<E>, public sfutils::AnimatedSprite
{
    public:
        E(sfutils::EntityManager<E>* manager,std::uint32_t id, sfutils::Animation* animation=nullptr) : 
            Entity(manager,id),
            sfutils::AnimatedSprite(animation)
        {
        };
};

sfutils::ResourceManager<sfutils::Animation,int> animations;

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");
    window.setFramerateLimit(65);

    textures.load(TEXTURES::EYE,"media/img/eye.png");
    animations.getOrLoad(ANIMATION::EYE_LEFT,&textures.get(TEXTURES::EYE)).addFramesLine(4,2,0);
    animations.load(ANIMATION::EYE_RIGHT,&textures.get(TEXTURES::EYE)).addFramesLine(4,2,1);

    sfutils::EntityManager<E> manager;

    sfutils::VMap* map = sfutils::createMapFromFile("./map.json");
    if(not map)
    {
        std::cerr<<"unable to load map"<<std::endl;
        return 0;
    }

    sf::ConvexShape* mouse_light;
    {
        sfutils::Layer<sfutils::HexaIso,sf::ConvexShape>* mouse_layer = new sfutils::Layer<sfutils::HexaIso,sf::ConvexShape>("ConvexShape",1);
        mouse_light = mouse_layer->add(map->getShape());
        map->add(mouse_layer);
    }
    mouse_light->setFillColor(sf::Color(255,255,255,64));

    sfutils::Layer<sfutils::HexaIso,E*>* entities_layer = new sfutils::Layer<sfutils::HexaIso,E*>("Entity",2);
    {
        for(int i=0;i<4;++i)
        {
            uint32_t id = manager.create(&animations.get(ANIMATION::EYE_LEFT));
            E* e = entities_layer->add(manager.getPtr(id));
            e->setPosition(map->mapCoordsToPixel(i,i));
        }
    }
    map->add(entities_layer);

    map->loadFromFile("./map2.json");


    sfutils::MapViewer viewer(window,*map);
    viewer.setSize(1600,900);

    sf::Clock clock;

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if(not viewer.processEvent(event))
            {
                if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i coord = viewer.mapPixelToCoords(event.mouseButton.x,event.mouseButton.y);
                    std::cout<<coord.x<<" "<<coord.y<<std::endl;
                }
                else if(event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2i coord = viewer.mapPixelToCoords(event.mouseMove.x,event.mouseMove.y);
                    sf::Vector2f pos = viewer.mapCoordsToPixel(coord.x,coord.y);
                    mouse_light->setPosition(pos);
                }
            }
        }

        viewer.processEvents();

        float deltaTime = clock.restart().asSeconds();

        viewer.update(deltaTime);
        window.setTitle("Example Tile ("+std::to_string(int(1/deltaTime))+")");


        viewer.draw();
        
        window.display();
    }


    return 0;
};
