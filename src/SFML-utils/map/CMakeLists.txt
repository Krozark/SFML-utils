set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)


set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/JsonMapLoader.hpp
    ${INCROOT}/JsonSpriteLoader.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/MapManager.hpp
    ${INCROOT}/MapMetaData.hpp
    ${INCROOT}/MapViewer.hpp
    #${INCROOT}/Tile.hpp
    #${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMapLoader.hpp
    ${INCROOT}/Tile.hpp


    ${INCROOT}/es/Components.hpp
    ${INCROOT}/es/Entity.hpp
    ${INCROOT}/es/Systems.hpp

    ${INCROOT}/geometry/Geometry.hpp
    ${INCROOT}/geometry/GeometryHexa.hpp
    ${INCROOT}/geometry/GeometryHexaIso.hpp
    ${INCROOT}/geometry/GeometrySquare.hpp
    ${INCROOT}/geometry/GeometrySquareIso.hpp
    ${INCROOT}/geometry/GeometrySquareStaggered.hpp
    ${INCROOT}/geometry/GeometrySquareIsoStaggered.hpp
)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/JsonMapLoader.cpp
    ${SRCROOT}/JsonSpriteLoader.cpp
    ${SRCROOT}/Map.cpp
    ${SRCROOT}/MapManager.cpp
    ${SRCROOT}/MapMetaData.cpp
    ${SRCROOT}/MapViewer.cpp
    ${SRCROOT}/VLayer.cpp
    ${SRCROOT}/VMapLoader.cpp
    ${SRCROOT}/Tile.cpp

    ${SRCROOT}/es/Entity.cpp
    ${SRCROOT}/es/Systems.cpp

    ${SRCROOT}/geometry/Geometry.cpp
    ${SRCROOT}/geometry/GeometryHexaIso.cpp
    ${SRCROOT}/geometry/GeometryHexa.cpp
    ${SRCROOT}/geometry/GeometrySquare.cpp
    ${SRCROOT}/geometry/GeometrySquareIso.cpp
    ${SRCROOT}/geometry/GeometrySquareStaggered.cpp
    ${SRCROOT}/geometry/GeometrySquareIsoStaggered.cpp
)

build_library(${PROJECT_NAME}-map
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-core
    EXTERNAL_LIBS ${LIBS} ${UTILS_LIBRARY} ${UTILS_JSON_LIBRARY}
)
