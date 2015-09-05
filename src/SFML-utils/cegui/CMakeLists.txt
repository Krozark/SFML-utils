set(INCROOT ${INCROOT}/cegui)
set(SRCROOT ${SRCROOT}/cegui)

#FILES
set(FILES_HEADER
    ${INCROOT}/GuiManager.hpp
)

set(FILES_SRC
    ${SRCROOT}/GuiManager.cpp
)

build_library(${PROJECT_NAME}-cegui
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    EXTERNAL_LIBS ${LIBS} ${LIBS_CEGUI}
)
