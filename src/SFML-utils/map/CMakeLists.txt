set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)


set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/JsonMapLoader.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/Map.tpl
    ${INCROOT}/MapManager.hpp
    ${INCROOT}/MapMetaData.hpp
    ${INCROOT}/MapViewer.hpp
    ${INCROOT}/Tile.hpp
    ${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMap.hpp
    ${INCROOT}/VMapLoader.hpp
    ${INCROOT}/VTile.hpp

    ${INCROOT}/tileShapes/BaseTile.hpp
    ${INCROOT}/tileShapes/HexaIso.hpp
    ${INCROOT}/tileShapes/Hexa.hpp
    ${INCROOT}/tileShapes/Square.hpp
    ${INCROOT}/tileShapes/SquareIso.hpp
    ${INCROOT}/tileShapes/SquareStaggered.hpp
    ${INCROOT}/tileShapes/SquareIsoStaggered.hpp
)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/JsonMapLoader.cpp
    ${SRCROOT}/MapManager.cpp
    ${SRCROOT}/MapMetaData.cpp
    ${SRCROOT}/MapViewer.cpp
    ${SRCROOT}/VLayer.cpp
    ${SRCROOT}/VMap.cpp
    ${SRCROOT}/VMapLoader.cpp
    ${SRCROOT}/VTile.cpp

    ${SRCROOT}/tileShapes/HexaIso.cpp
    ${SRCROOT}/tileShapes/Hexa.cpp
    ${SRCROOT}/tileShapes/Square.cpp
    ${SRCROOT}/tileShapes/SquareIso.cpp
    ${SRCROOT}/tileShapes/SquareStaggered.cpp
    ${SRCROOT}/tileShapes/SquareIsoStaggered.cpp
)

build_library(${PROJECT_NAME}-map
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-core
<<<<<<< HEAD
    EXTERNAL_LIBS ${LIBS} ${UTILS_LIBRARY} ${UTILS_JSON_LIBRARY}
=======
    EXTERNAL_LIBS ${LIBS} ${UTILS_JSON_LIBRARY}
>>>>>>> 23cde0d42703e55c7bc910398f368862fd76c991
)
