cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

function(Compile arg shared_libs static_libs)
    #shared
    add_library(${arg} SHARED ${FILES_SRC} ${FILES_HEADER})
    SET_TARGET_PROPERTIES(${arg}
        PROPERTIES
        OUTPUT_NAME ${arg}
        CLEAN_DIRECT_OUTPUT 1
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
        )
    target_link_libraries(${arg} ${LIBS} ${shared_libs})
    INSTALL(TARGETS ${arg}
        DESTINATION lib
    )
    #static
    add_library(${arg}-static STATIC ${FILES_HEADER} ${FILES_SRC})
    SET_TARGET_PROPERTIES(${arg}-static
        PROPERTIES
        OUTPUT_NAME ${arg}
        CLEAN_DIRECT_OUTPUT 1
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
        )
    target_link_libraries(${arg}-static ${LIBS} ${static_libs})
    INSTALL(TARGETS ${arg}-static
    DESTINATION lib
    )
endfunction()



# project name
project (SFML-utils)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 2)



# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#add an option for building the examples
set_option(BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

set_option(BUILD_BOX2D FALSE BOOL "TRUE to build box2d wrapper for SFML")

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-o3 -std=c++11")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

find_library(LIB_SFML_SYSTEM sfml-system)
find_library(LIB_SFML_GRAPHICS sfml-graphics)
find_library(LIB_SFML_WINDOW sfml-window)
find_library(LIB_SFML_AUDIO sfml-audio)
set(LIBS ${LIB_SFML_SYSTEM} ${LIB_SFML_GRAPHICS} ${LIB_SFML_WINDOW} ${LIB_SFML_AUDIO})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)


# add the subdirectories
add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(BUILD_DOC)
    add_subdirectory(doc)
endif()

