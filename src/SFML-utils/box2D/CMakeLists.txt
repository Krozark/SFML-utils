set(INCROOT ${INCROOT}/box2D)
set(SRCROOT ${SRCROOT}/box2D)

#FILES
set(FILES_HEADER
    ${INCROOT}/DebugDraw.hpp
    ${INCROOT}/converter.hpp
)

set(FILES_SRC
    ${SRCROOT}/DebugDraw.cpp
)

build_library(${PROJECT_NAME}-box2D
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    EXTERNAL_LIBS ${LIBS} ${BOX2D_LIBRARY}
)
