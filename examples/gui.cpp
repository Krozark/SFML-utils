#include <SFML-utils/Core.hpp>
#include <SFML-utils/Gui.hpp>

enum Fonts {Gui};
sfutils::ResourceManager<sf::Font,int> fonts;

enum GuiInputs {Escape};
sfutils::ActionMap<int> gui_inputs;


int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(600,800),"Example GUI");
    sfutils::Frame frame(window,gui_inputs);

    fonts.load(Fonts::Gui,"media/font/trs-million.ttf");
    gui_inputs.map(GuiInputs::Escape,sfutils::Action(sf::Keyboard::Escape,sfutils::Action::Type::Pressed));

    {
        sfutils::VLayout* layout = new sfutils::VLayout;
        layout->setSpace(70);

        sfutils::Label* label = new sfutils::Label("Hello World !",fonts.get(Fonts::Gui));
        label->setCharacterSize(72);
        layout->add(label);

        sfutils::TextButton* exit = new sfutils::TextButton("Exit",fonts.get(Fonts::Gui));
        exit->on_click = [&window](const sf::Event&, sfutils::Button& button){
            window.close();
        };
        layout->add(exit);

        sfutils::Label* label2 = new sfutils::Label("This text can be hide",fonts.get(Fonts::Gui));
        label2->setCharacterSize(72);
        layout->add(label2);

        sfutils::TextButton* button2 = new sfutils::TextButton("Hide/Show text",fonts.get(Fonts::Gui));
        button2->on_click = [label2](const sf::Event&, sfutils::Button& button){
            label2->toggle();
        };
        layout->add(button2);


        frame.setLayout(layout);
    }

    
    while (window.isOpen())
    {
        window.clear();

        frame.processEvents();

        frame.draw();
        //equivalent to : window.draw(frame);

        window.display();
    }

    return 0;
};
