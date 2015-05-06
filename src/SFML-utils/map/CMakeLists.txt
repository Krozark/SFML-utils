set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)


set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/MapViewer.hpp
    ${INCROOT}/Map.tpl
    ${INCROOT}/Tile.hpp
    ${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMap.hpp

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
    ${SRCROOT}/VMap.cpp
    ${SRCROOT}/MapViewer.cpp
    ${SRCROOT}/VLayer.cpp

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
    EXTERNAL_LIBS ${LIBS} utils-json
)
