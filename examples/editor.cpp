#include <SFML-utils/Map.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>



int sfml()
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");
    window.setFramerateLimit(65);

    sfutils::VMap* map = sfutils::VMap::createMapFromFile("./map.json");
    map->loadFromFile("./map2.json");

    sfutils::MapViewer viewer(window,*map,false);

    /*sfutils::Layer<sf::ConvexShape>* mouse_layer = new sfutils::Layer<sf::ConvexShape>("ConvexShape",1);

    sf::ConvexShape* mouse_light = mouse_layer->add(map->getShape());
    mouse_light->setFillColor(sf::Color(255,255,255,64));
    map->add(mouse_layer);*/

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
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseButton.x,event.mouseButton.y);
                    std::cout<<"Click on: "<<coord.x<<":"<<coord.y<<std::endl;

                }
                /*else if(event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseMove.x,event.mouseMove.y);
                    sf::Vector2f pos = viewer.mapCoordsToPixel(coord.x,coord.y);
                    mouse_light->setPosition(pos);
                }*/
            }
        }

        viewer.processEvents();

        float deltaTime = clock.restart().asSeconds();

        viewer.update(deltaTime);

        viewer.draw();
        
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

    //return sfml();
    
    return qt(argc,argv);

};
