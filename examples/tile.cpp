#include <SFML-utils/Map.hpp>

#include <list>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");

    std::list<sfutils::Tile<sfutils::HexaIso>> tiles;

    for(int y = 0;y<10;++y)
        for(int x=0;x<10;++x)
            tiles.emplace_back(x,y);
    
    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto& tile : tiles)
            window.draw(tile);


        window.display();
    }

    return 0;
};
