#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>

int main(int argc,char* argv[])
{

    sfutils::editor::Editor editor;
    sfutils::editor::SpriteSheetSelector selector;

    selector.setFile("media/spriteSheet/trees.json");

    editor.run();

    return 0;
    
};
