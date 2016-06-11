#include <SFML-utils/map-editor/Editor.hpp>

#include <SFML-utils/map-editor/SpriteSheetSelector.hpp>

#ifdef ORM_BUILD_SUPPORT_MYSQL
#include <ORM/backends/MySql.hpp>
#else
#include <ORM/backends/Sqlite3.hpp>
#endif

int main(int argc,char* argv[])
{
#ifdef ORM_BUILD_SUPPORT_MYSQL
    orm::DB::Default.reset(new orm::MySqlDB("root","toor","sfml_utils"));
#else
    orm::DB::Default.reset(new orm::Sqlite3DB("./db.sqlite"));
#endif

    orm::DB::Default->connect();

    sfutils::editor::Editor editor;

    editor.run();

    orm::DB::Default->disconnect();

    return 0;
    
};
