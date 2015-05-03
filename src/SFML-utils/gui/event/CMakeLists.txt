set(INCROOT ${INCROOT}/event)
set(SRCROOT ${SRCROOT}/event)

list(APPEND FILES_HEADER
    ${INCROOT}/ButtonPressed.hpp
    ${INCROOT}/ButtonReleased.hpp
)
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/ButtonPressed.cpp
    ${SRCROOT}/ButtonReleased.cpp
)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
