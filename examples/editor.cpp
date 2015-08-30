#include <SFML-utils/map-editor/Editor.hpp>

int main(int argc,char* argv[])
{
    sfutils::editor::Editor editor(sf::VideoMode(1600,900));

    editor.run();

    return 0;
    
};
