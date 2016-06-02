set(INCROOT ${INCROOT}/map-editor)
set(SRCROOT ${SRCROOT}/map-editor)

set(FILES_HEADER
    ${INCROOT}/Editor.hpp
    ${INCROOT}/Gui.hpp
    ${INCROOT}/GuiWindow.hpp
)

set(FILES_SRC
    ${SRCROOT}/Editor.cpp
    ${SRCROOT}/Gui.cpp
    ${SRCROOT}/GuiCallbacks.cpp
    ${SRCROOT}/GuiWindow.cpp
)


set(LIBS ${LIBS} ${LIBS_EDITOR})

build_library(${PROJECT_NAME}-editor
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-map ${PROJECT_NAME}-cegui
    EXTERNAL_LIBS ${LIBS} ${LIBS_CEGUI}
)
