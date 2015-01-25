set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/gui)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/gui)

set(LIBS ${LIBS} ${CMAKE_PROJECT_NAME}-core)

set(FILES_HEADER
    ${INCROOT}/Button.hpp
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Container.hpp
    ${INCROOT}/Frame.hpp
    ${INCROOT}/Label.hpp
    ${INCROOT}/Layout.hpp
    ${INCROOT}/TextButton.hpp
    ${INCROOT}/SpriteButton.hpp
    ${INCROOT}/Sprite.hpp
    ${INCROOT}/HLayout.hpp
    ${INCROOT}/VLayout.hpp
    ${INCROOT}/Widget.hpp
)

set(FILES_SRC
    ${SRCROOT}/Button.cpp
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/Container.cpp
    ${SRCROOT}/Frame.cpp
    ${SRCROOT}/Label.cpp
    ${SRCROOT}/Layout.cpp
    ${SRCROOT}/TextButton.cpp
    ${SRCROOT}/SpriteButton.cpp
    ${SRCROOT}/Sprite.cpp
    ${SRCROOT}/HLayout.cpp
    ${SRCROOT}/VLayout.cpp
    ${SRCROOT}/Widget.cpp

)

Compile("${CMAKE_PROJECT_NAME}-gui" "" "")
