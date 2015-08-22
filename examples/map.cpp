#include <SFML-utils/Map.hpp>

#include <SFML-utils/Core.hpp>
#include <SFML-utils/map/es/Components.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

enum Textures{
    Eye
};

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");
    window.setFramerateLimit(65);

    sfutils::MapManager mapManager(std::shared_ptr<sfutils::VMapLoader>(new sfutils::JsonMapLoader("./media")));

    sfutils::VMap* map = mapManager.getMap();
    mapManager.loadArea(0,0);
    mapManager.loadArea(-1,-1);
    mapManager.loadArea(-1,0);
    mapManager.loadArea(0,-1);

    sfutils::MapViewer viewer(window,*map);

    sfutils::Layer<sf::ConvexShape>* mouse_layer = new sfutils::Layer<sf::ConvexShape>("ConvexShape",1);

    sf::ConvexShape* mouse_light = mouse_layer->add(map->getShape());
    mouse_light->setFillColor(sf::Color(255,255,255,64));
    map->addLayer(mouse_layer);


    sfutils::ResourceManager<sf::Texture,int> textures; 
    textures.load(Eye,"media/img/eye.png");

    sfutils::Animation walkLeft(&textures.get(Eye));
    walkLeft.addFramesLine(4,2,0);

    sfutils::Animation walkRight(&textures.get(Eye));
    walkRight.addFramesLine(4,2,1);


    sfutils::map::Entity& user = map->createEntity();
    user.add<sfutils::map::CompSkinDynamic>(&walkLeft,sfutils::AnimatedSprite::Playing,sf::seconds(0.15));
    sfutils::map::CompSkinDynamic::Handle skin = user.component<sfutils::map::CompSkinDynamic>();

    sf::FloatRect rec = skin->_sprite.getLocalBounds();
    skin->_sprite.setOrigin(rec.width*0.5,rec.height*0.8);
    skin->_sprite.setScale(0.3,0.3);



    sf::Clock clock;

    sf::Vector2i last;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Key::D)
            {
                std::cout<<"deleting (0,0)"<<std::endl;
                mapManager.unloadArea(0,0);
            }
            else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Key::L)
            {
                std::cout<<"loading (0,0)"<<std::endl;
                mapManager.loadArea(0,0);
            }
            else if(not viewer.processEvent(event))
            {
                if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseButton.x,event.mouseButton.y);
                    std::cout<<"Click on: "<<coord.x<<":"<<coord.y<<std::endl;
                    std::cout<<"Distance between "<<coord.x<<":"<<coord.y<<" and "<<last.x<<":"<<last.y<<" = "<<map->getDistance(coord,last)<<std::endl;
                    last = coord;

                }
                else if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseButton.x,event.mouseButton.y);
                    sf::Vector2f pixels = viewer.mapCoordsToPixel(coord);
                    pixels.y += 1; //to be display on top on the tree on the same tile

                    user.setPosition(pixels);
                }
                else if(event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseMove.x,event.mouseMove.y);
                    sf::Vector2f pos = viewer.mapCoordsToPixel(coord.x,coord.y);
                    mouse_light->setPosition(pos);
                }
            }
        }

        viewer.processEvents();

        sf::Time deltaTime = clock.restart();

        viewer.update(deltaTime);
        window.setTitle("Example Tile ("+std::to_string(int(1/deltaTime.asSeconds()))+")");


        window.clear();

        viewer.draw();
        
        window.display();
    }


    return 0;
};
