set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/map)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/map)

find_library(LIB_UTILS_JSON utils-json)
set(LIBS ${LIBS} ${LIB_UTILS_JSON})

set(FILES_HEADER
    ${INCROOT}/HexaIso.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/Map.tpl
    ${INCROOT}/Tile.hpp
    ${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMap.hpp
)

set(FILES_SRC
    ${SRCROOT}/HexaIso.cpp
    ${SRCROOT}/VMap.cpp
    ${SRCROOT}/VLayer.cpp
)

Compile("${CMAKE_PROJECT_NAME}-map" "" "")
