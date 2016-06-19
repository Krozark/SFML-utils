set(INCROOT ${INCROOT}/map-editor)
set(SRCROOT ${SRCROOT}/map-editor)

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

find_library(LIB_LUABIND luabind REQUIRED)

set(FILES_HEADER
    ${INCROOT}/Editor.hpp
    ${INCROOT}/Gui.hpp
    ${INCROOT}/MapStateChanger.hpp
    ${INCROOT}/MapSelectionManager.hpp
    ${INCROOT}/path.hpp
    ${INCROOT}/SpriteSheetSelector.hpp
    ${INCROOT}/TileInfo.hpp
)

set(FILES_SRC
    ${SRCROOT}/Editor.cpp
    ${SRCROOT}/Gui.cpp
    ${SRCROOT}/GuiCallbacks.cpp
    ${SRCROOT}/MapStateChanger.cpp
    ${SRCROOT}/MapSelectionManager.cpp
    ${SRCROOT}/SpriteSheetSelector.cpp
    ${SRCROOT}/TileInfo.cpp
)

set(LIBS ${LIBS} ${ORM_LIBRARY} ${LIBS_CEGUI} ${LUA_LIBRARY} ${LIB_LUABIND})

build_library(${PROJECT_NAME}-editor
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-map ${PROJECT_NAME}-cegui
    EXTERNAL_LIBS ${LIBS}
)
