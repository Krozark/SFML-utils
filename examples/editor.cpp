#include <SFML/Graphics.hpp>

#include <SFML-utils/Core.hpp>
#include <SFML-utils/Map.hpp>


#include <iostream>

int sfml()
{

    sfutils::ResourceManager<sf::Texture,int> textures;     
    textures.load(0,"media/img/trees1/trees1.png");

    auto size = textures.get(0).getSize();
    sf::Sprite spriteSheet(textures.get(0));
    spriteSheet.setPosition(0,0);

    sf::RenderWindow window(sf::VideoMode(size.x,size.y),"Example Tile");
    window.setFramerateLimit(65);



    std::unordered_map<std::string,sf::IntRect> spriteSheetRect = sfutils::map::JsonSpriteLoader::parse("media/img/trees1/trees1.json");
    
    //sf::Clock clock;
    sf::RectangleShape shape;
    //shape.setOutlineThickness(1);
    //shape.setOutlineColor(sf::Color::Blue);
    shape.setFillColor(sf::Color(255,255,255,32));

    while (window.isOpen())
    {

        sf::Event event;
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                for(auto& pair : spriteSheetRect)
                {
                    if(pair.second.contains(pos.x,pos.y))
                    {
                        std::cout<<"Click on "<<pair.first<<std::endl;
                        break;
                    }
                }
            }
        }

        window.clear();
        window.draw(spriteSheet);


        for(auto& pair : spriteSheetRect)
        {

            sf::RectangleShape shape2;
            shape2.setSize(sf::Vector2f(pair.second.width,pair.second.height));
            shape2.setPosition(sf::Vector2f(pair.second.left,pair.second.top));
            shape2.setOutlineThickness(1);
            shape2.setOutlineColor(sf::Color(255,255,255,32));
            shape2.setFillColor(sf::Color::Transparent);
            window.draw(shape2);

            if(pair.second.contains(pos.x,pos.y))
            {
                shape.setSize(sf::Vector2f(pair.second.width,pair.second.height));
                shape.setPosition(sf::Vector2f(pair.second.left,pair.second.top));
            }
        }


        window.draw(shape);



        //float deltaTime = clock.restart().asSeconds();

        window.display();
    }

    return 0;

}

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>

int qt(int argc,char* argv[])
{
    QApplication App(argc, argv);

    QMainWindow MainFrame;
    MainFrame.setWindowTitle("Qt SFML");
    MainFrame.resize(800, 600);

    //menu
    {
        QMenu* menuFichier = MainFrame.menuBar()->addMenu("Fichier");
        QAction* actionOuvrir = new QAction("Ouvrir",&MainFrame);
        //connect(actionOuvrir,SIGNAL(triggered()),/*this*/,SLOT(OpenFile()));
        menuFichier->addAction(actionOuvrir);
    }


    //zone centrale
    {
        QWidget* zoneCentrale = new QScrollArea();
        QLayout* layout = new QHBoxLayout();
        zoneCentrale->setLayout(layout);
        MainFrame.setCentralWidget(zoneCentrale);

        //left
        {
            QWidget* widget = new QWidget();
            QLayout* layout2 = new QVBoxLayout();

            for(int i = 0; i<3;++i)
            {
                QTabWidget* tab = new QTabWidget();
                for(int j=0;j<4;++j)
                {
                    QLabel* page = new QLabel(("Page" + std::to_string(j)).c_str());
                    tab->addTab(page,std::to_string(j).c_str());
                }
                layout2->addWidget(tab);
            }
            widget->setLayout(layout2);
            layout->addWidget(widget);
        }

        //center
        {
            QWidget* widget = new QWidget();
            QLayout* layout2 = new QVBoxLayout();


            QLabel* label = new QLabel("SFML View");
            label->setMinimumSize(600,800);
            layout2->addWidget(label);

            widget->setLayout(layout2);
            layout->addWidget(widget);
        }

        //right
        {
            QWidget* widget = new QWidget();
            QLayout* layout2 = new QVBoxLayout();


            QLabel* label = new QLabel("minimap");
            layout2->addWidget(label);

            for(int i = 0; i<2;++i)
            {
                QTabWidget* tab = new QTabWidget();
                for(int j=0;j<4;++j)
                {
                    QLabel* page = new QLabel(("Page" + std::to_string(j)).c_str());
                    tab->addTab(page,std::to_string(j).c_str());
                }
                layout2->addWidget(tab);
            }
            widget->setLayout(layout2);
            layout->addWidget(widget);
        }
    }




    MainFrame.show();
    return App.exec();
}

int main(int argc,char* argv[])
{

    return sfml();
    
    //return qt(argc,argv);

};
