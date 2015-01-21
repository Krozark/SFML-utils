set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/es)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/es)

find_library(LIB_UTILS utils)
set(LIBS ${LIBS} ${LIB_UTILS})


set(FILES_HEADER
    ${INCROOT}/Application.hpp
    #${INCROOT}/Component.hpp
    #${INCROOT}/Component.tpl
    #${INCROOT}/Entity.hpp
    #${INCROOT}/Entity.tpl
    ${INCROOT}/EntityManager.hpp
    ${INCROOT}/EntityManager.tpl
    #${INCROOT}/System.hpp
    #${INCROOT}/System.tpl
)

set(FILES_SRC
)

