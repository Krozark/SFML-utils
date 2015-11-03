set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)

if(SFML_UTILS_BUILD_MODULE_MAP_DATABASE)
    set(LIBS ${LIBS} ${ORM_LIBRARY})
endif()


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
)

if(SFML_UTILS_BUILD_MODULE_MAP_DATABASE)
    list(APPEND FILES_HEADER
        ${INCROOT}/DatabaseMapLoader.hpp
    )
    
list(APPEND FILES_SRC
        ${SRCROOT}/DatabaseMapLoader.cpp
    )
endif()

add_subdirectory(es)
add_subdirectory(geometry)

if(SFML_UTILS_BUILD_MODULE_MAP_DATABASE)
    add_subdirectory(models)
endif()

build_library(${PROJECT_NAME}-map
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-core
    EXTERNAL_LIBS ${LIBS} ${UTILS_LIBRARY} ${UTILS_JSON_LIBRARY}
)
