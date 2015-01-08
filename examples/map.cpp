#include <SFML-utils/Map.hpp>

#include <list>
#include <iostream>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");

    sfutils::VMap* map = sfutils::createMapFromFile("./map.json");
    if(not map)
    {
        std::cerr<<"unable to load map"<<std::endl;
        return 0;
    }

    sfutils::MapViewer viewer(*map);
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
            else
                viewer.processEvent(event);
        }
        viewer.processEvents();

        float deltaTime = clock.restart().asSeconds();

        viewer.update(deltaTime);
        window.setTitle("Example Tile ("+std::to_string(int(1/deltaTime))+")");


        window.draw(viewer);
        
        window.display();
    }


    return 0;
};
