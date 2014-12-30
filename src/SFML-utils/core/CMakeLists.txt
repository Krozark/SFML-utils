set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/core)

set(FILES_HEADER
    ${INCROOT}/Action.hpp
    ${INCROOT}/ActionMap.hpp
    ${INCROOT}/ActionMap.tpl
    ${INCROOT}/ActionTarget.hpp
    ${INCROOT}/ActionTarget.tpl
    ${INCROOT}/ResourceManager.hpp
    ${INCROOT}/ResourceManager.tpl
)

set(FILES_SRC
    ${SRCROOT}/Action.cpp
)

Compile("${CMAKE_PROJECT_NAME}-core" "" "")
