set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/es)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/es)

#set(LIBS ${LIBS} ${CMAKE_PROJECT_NAME}-core)

set(FILES_HEADER
    ${INCROOT}/Component.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/EntityManager.hpp
    ${INCROOT}/System.hpp
)

set(FILES_SRC
    ${SRCROOT}/Component.cpp
    ${SRCROOT}/Entity.cpp
    ${SRCROOT}/EntityManager.cpp
    ${SRCROOT}/System.cpp
)

Compile("${CMAKE_PROJECT_NAME}-es" "" "")
