set(INCROOT ${INCROOT}/core)
set(SRCROOT ${SRCROOT}/core)

set(FILES_HEADER
    ${INCROOT}/Action.hpp
    ${INCROOT}/ActionMap.hpp
    ${INCROOT}/ActionMap.tpl
    ${INCROOT}/ActionTarget.hpp
    ${INCROOT}/ActionTarget.tpl
    ${INCROOT}/ResourceManager.hpp
    ${INCROOT}/ResourceManager.tpl

    ${INCROOT}/Animation.hpp
    ${INCROOT}/AnimatedSprite.hpp
)

set(FILES_SRC
    ${SRCROOT}/Action.cpp

    ${SRCROOT}/Animation.cpp
    ${SRCROOT}/AnimatedSprite.cpp
)

build_library(${PROJECT_NAME}-core
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    EXTERNAL_LIBS ${LIBS}
)
