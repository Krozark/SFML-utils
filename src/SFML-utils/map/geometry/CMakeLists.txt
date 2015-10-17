set(INCROOT ${INCROOT}/geometry)
set(SRCROOT ${SRCROOT}/geometry)


list(APPEND FILES_HEADER
    ${INCROOT}/Geometry.hpp
    ${INCROOT}/GeometryHexa.hpp
    ${INCROOT}/GeometryHexaIso.hpp
    ${INCROOT}/GeometrySquare.hpp
    ${INCROOT}/GeometrySquareIso.hpp
    ${INCROOT}/GeometrySquareStaggered.hpp
    ${INCROOT}/GeometrySquareIsoStaggered.hpp
)

list(APPEND FILES_SRC
    ${SRCROOT}/Geometry.cpp
    ${SRCROOT}/GeometryHexaIso.cpp
    ${SRCROOT}/GeometryHexa.cpp
    ${SRCROOT}/GeometrySquare.cpp
    ${SRCROOT}/GeometrySquareIso.cpp
    ${SRCROOT}/GeometrySquareStaggered.cpp
    ${SRCROOT}/GeometrySquareIsoStaggered.cpp
)

set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
