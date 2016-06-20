#ifndef SFUTILS_EDITOR_PATH_PATH_HPP
#define SFUTILS_EDITOR_PATH_PATH_HPP

#include <utils/string.hpp>

namespace sfutils
{
    namespace editor
    {
        namespace path
        {
            const std::string DIRECTORY_MEDIA_NAME = "media/editor";
            const std::string DIRECTORY_MEDIA = DIRECTORY_MEDIA_NAME + "/";

            const std::string DIRECTORY_LUA_NAME = "lua";
            const std::string DIRECTORY_LUA = DIRECTORY_MEDIA + DIRECTORY_LUA_NAME + "/";

            const std::string DIRECTORY_SPRITES_NAME = "sprites";
            const std::string DIRECTORY_SPRITES = DIRECTORY_MEDIA + DIRECTORY_SPRITES_NAME + "/";

            const std::string DIRECTORY_BRUSH_NAME = "brush";
            const std::string DIRECTORY_BRUSH = DIRECTORY_MEDIA + DIRECTORY_BRUSH_NAME + "/";

            const std::string DIRECTORY_SPRITES__SHEETS_NAME = "sheets";
            const std::string DIRECTORY_SPRITES_SHEETS = DIRECTORY_SPRITES + DIRECTORY_SPRITES__SHEETS_NAME + "/";
        }
    }
}
#endif
