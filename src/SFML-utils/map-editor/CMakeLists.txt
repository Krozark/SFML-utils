set(INCROOT ${INCROOT}/map-editor)
set(SRCROOT ${SRCROOT}/map-editor)

set(FILES_HEADER
    ${INCROOT}/Editor.hpp
)

set(FILES_SRC
    ${SRCROOT}/Editor.cpp
)

find_package(SFGUI REQUIRED)
include_directories(${SFGUI_INCLUDE_DIR})
set(LIBS ${LIBS} ${SFGUI_LIBRARY})


build_library(${PROJECT_NAME}-editor
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-map
    EXTERNAL_LIBS ${LIBS}
)
