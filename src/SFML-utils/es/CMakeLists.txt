set(INCROOT ${INCROOT}/es)
set(SRCROOT ${SRCROOT}/es)

set(FILES_HEADER
    ${INCROOT}/Application.hpp
    ${INCROOT}/Component.hpp
    ${INCROOT}/Component.tpl
    ${INCROOT}/Entity.hpp
    ${INCROOT}/Entity.tpl
    ${INCROOT}/EntityManager.hpp
    ${INCROOT}/EntityManager.tpl
    ${INCROOT}/System.hpp
    ${INCROOT}/System.tpl
)

set(FILES_SRC
    ${SRCROOT}/Entity.cpp
)

build_library(${PROJECT_NAME}-es
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    EXTERNAL_LIBS ${LIBS} ${UTILS_LIBRARY}
)
