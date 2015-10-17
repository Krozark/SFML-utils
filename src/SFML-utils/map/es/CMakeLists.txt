set(INCROOT ${INCROOT}/es)
set(SRCROOT ${SRCROOT}/es)


list(APPEND FILES_HEADER
    ${INCROOT}/Components.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/Systems.hpp
)

list(APPEND FILES_SRC
    ${SRCROOT}/Entity.cpp
    ${SRCROOT}/Systems.cpp
)


set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
