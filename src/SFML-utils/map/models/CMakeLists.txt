set(INCROOT ${INCROOT}/models)
set(SRCROOT ${SRCROOT}/models)


list(APPEND FILES_HEADER
    ${INCROOT}/GeometryModel.hpp
    ${INCROOT}/LayerModel.hpp
    ${INCROOT}/LayerTypeModel.hpp
    ${INCROOT}/MapModel.hpp
    ${INCROOT}/TileModel.hpp
)

list(APPEND FILES_SRC
    ${SRCROOT}/GeometryModel.cpp
    ${SRCROOT}/LayerModel.cpp
    ${SRCROOT}/LayerTypeModel.cpp
    ${SRCROOT}/MapModel.cpp
    ${SRCROOT}/TileModel.cpp
)

set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
