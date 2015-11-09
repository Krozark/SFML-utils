set(INCROOT ${INCROOT}/cegui)
set(SRCROOT ${SRCROOT}/cegui)

#FILES
set(FILES_HEADER
    ${INCROOT}/DialogBox.hpp
    ${INCROOT}/GuiManager.hpp
    ${INCROOT}/MessageBox.hpp
    ${INCROOT}/PopupBox.hpp
)

set(FILES_SRC
    ${SRCROOT}/DialogBox.cpp
    ${SRCROOT}/GuiManager.cpp
    ${SRCROOT}/MessageBox.cpp
    ${SRCROOT}/PopupBox.cpp
)

build_library(${PROJECT_NAME}-cegui
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    EXTERNAL_LIBS ${LIBS} ${LIBS_CEGUI}
)
