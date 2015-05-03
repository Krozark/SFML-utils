#include <SFML-utils/Core.hpp>
#include <SFML-utils/Gui.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000,900),"Example GUI");
    window.setFramerateLimit(60);

    sfutils::Frame frame(window);

    sf::Texture texture;
    texture.loadFromFile("media/img/hello.png");

    {
        sfutils::VLayout* layout = new sfutils::VLayout;
        layout->setSpacing(70);

        sfutils::Label* label = new sfutils::Label("Hello World !");
        label->setCharacterSize(72);
        layout->add(label);

        sfutils::TextButton* exit = new sfutils::TextButton("Exit");
        exit->connect([&window](sfutils::event::ButtonPressed& event){
            window.close();
        });
        layout->add(exit);

        sfutils::Label* label2 = new sfutils::Label("This text can be hide");
        label2->setCharacterSize(72);
        layout->add(label2);

        sfutils::TextButton* button2 = new sfutils::TextButton("Hide/Show text");
        button2->connect([label2](sfutils::event::ButtonPressed& event){
            label2->toggle();
        });
        layout->add(button2);

        sfutils::Container* container = new sfutils::Container;
        {
            sfutils::HLayout* layout = new sfutils::HLayout;
            layout->setSpacing(20);

            sfutils::Label* label = new sfutils::Label("This is another text");
            label->setCharacterSize(36);
            layout->add(label);

            sfutils::TextButton* button = new sfutils::TextButton("I'm useless");
            layout->add(button);

            label = new sfutils::Label("blah blah");
            label->setCharacterSize(36);
            label->setTextColor(sf::Color(180,28,90));
            layout->add(label);

            sfutils::SpriteButton* sprbutton = new sfutils::SpriteButton(texture);
            sprbutton->connect([&window](sfutils::event::ButtonPressed& event){
                std::cout<<"hello"<<std::endl;
            });
            layout->add(sprbutton);

            container->setLayout(layout);
        }
        layout->add(container);

        frame.setLayout(layout);
    }

    
    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while(window.pollEvent(event))
        {
            frame.processEvent(event);
        }
        frame.processEvents();

        frame.draw();
        //equivalent to : window.draw(frame);

        window.display();
    }

    return 0;
};
