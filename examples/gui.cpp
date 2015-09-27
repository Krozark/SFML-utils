#include <SFML-utils/Core.hpp>
#include <SFML-utils/Gui.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000,900),"Example GUI");
    window.setFramerateLimit(60);

    sfutils::gui::Frame frame(window);

    sf::Texture texture;
    texture.loadFromFile("media/img/hello.png");

    sfutils::gui::Button::Handler guiEventHandler;

    {
        sfutils::gui::VLayout* layout = new sfutils::gui::VLayout;
        layout->setSpacing(70);

        sfutils::gui::Label* label = new sfutils::gui::Label("Hello World !");
        label->setCharacterSize(72);
        layout->add(label);

        sfutils::gui::TextButton* exit = new sfutils::gui::TextButton("Exit");
        exit->connect<sfutils::gui::event::ButtonPressed>(guiEventHandler,[&window](const sfutils::gui::event::ButtonPressed& event){
            window.close();
        });
        layout->add(exit);

        sfutils::gui::Label* label2 = new sfutils::gui::Label("This text can be hide");
        label2->setCharacterSize(72);
        layout->add(label2);

        sfutils::gui::TextButton* button2 = new sfutils::gui::TextButton("Hide/Show text");
        button2->connect<sfutils::gui::event::ButtonPressed>(guiEventHandler,[label2](const sfutils::gui::event::ButtonPressed& event){
            label2->toggle();
        });
        layout->add(button2);

        sfutils::gui::Container* container = new sfutils::gui::Container;
        {
            sfutils::gui::HLayout* layout = new sfutils::gui::HLayout;
            layout->setSpacing(20);

            sfutils::gui::Label* label = new sfutils::gui::Label("This is another text");
            label->setCharacterSize(36);
            layout->add(label);

            sfutils::gui::TextButton* button = new sfutils::gui::TextButton("I'm useless");
            layout->add(button);

            label = new sfutils::gui::Label("blah blah");
            label->setCharacterSize(36);
            label->setTextColor(sf::Color(180,28,90));
            layout->add(label);

            sfutils::gui::SpriteButton* sprbutton = new sfutils::gui::SpriteButton(texture);
            sprbutton->connect<sfutils::gui::event::ButtonPressed>(guiEventHandler,[&window](const sfutils::gui::event::ButtonPressed& event){
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
