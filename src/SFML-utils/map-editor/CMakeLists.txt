set(INCROOT ${INCROOT}/map-editor)
set(SRCROOT ${SRCROOT}/map-editor)

############ QT ####################
if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.2.1/5.2.1/mingw48_32")
endif()
# Appeler automatique le moc quand nécessaire
SET(CMAKE_AUTOMOC ON)
# Les fichiers générés par le moc sont générés dans le dossier bin, dire à CMake de toujours 	
# inclure les entêtes de ce dossier
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Le module QtWidgets trouve ses propres dépendances
find_package(Qt5Widgets REQUIRED)
#include_directories(${Qt5Widgets_INCLUDES})
#add_definitions(${Qt5Widgets_DEFINITIONS})


######### END Qt ##########################


set(FILES_HEADER
    ${INCROOT}/Editor.hpp
)

set(FILES_SRC
    ${SRCROOT}/Editor.cpp
)

build_library(${PROJECT_NAME}-editor
    SOURCES ${FILES_HEADER} ${FILES_SRC}
    TYPE ${SFML_UTILS_BUILD_TYPE}
    DEPENDS ${PROJECT_NAME}-map
    EXTERNAL_LIBS ${LIBS}
)

foreach(type ${SFML_UTILS_BUILD_TYPE})
    if(type STREQUAL SHARED)
        set(sufix shared)
    elseif(type STREQUAL STATIC)
        set(sufix static)
    endif()

    QT5_USE_MODULES(${PROJECT_NAME}-editor-${sufix} Widgets)
endforeach()
