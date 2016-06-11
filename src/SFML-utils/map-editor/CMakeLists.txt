set(INCROOT ${INCROOT}/map-editor)
set(SRCROOT ${SRCROOT}/map-editor)

set(FILES_HEADER
    ${INCROOT}/Editor.hpp
    ${INCROOT}/Gui.hpp
    ${INCROOT}/MapStateChanger.hpp
    ${INCROOT}/MapSelectionManager.hpp
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

find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
set(LIBS ${LIBS} ${MYSQL_LIBRARIES})


set(LIBS ${LIBS} ${LIBS_EDITOR})

build_library(${PROJECT_NAME}-editor
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-map ${PROJECT_NAME}-cegui
    EXTERNAL_LIBS ${LIBS} ${LIBS_CEGUI}
)
