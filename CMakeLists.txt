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
set(PROJECT_NAME SFML-utils)
project (${PROJECT_NAME})

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)



# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#add an option for building the examples
set_option(SFML_UTILS_BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(SFML_UTILS_BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

set_option(SFML_UTILS_BUILD_BOX2D TRUE BOOL "TRUE to build box2d wrapper for SFML")

set_option(SFML_UTILS_USE_SYSTEM_CPP_UTILS TRUE BOOL "Use cpp-utils from system, false to compile it from dependencies")

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-g -std=c++11")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

#find SFML
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/../SFML PATH "The SFML root installation")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/SFML PATH "The SFML root installation")
else()
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/SFML PATH "The SFML root installation")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules;${CMAKE_SOURCE_DIR}")

find_package(SFML 2 COMPONENTS system graphics window audio network)
if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML Modules not find. Please set the SFML_ROOT variable to your SFML root installation directory and retry")
endif()

#add SFML
include_directories(${SFML_INCLUDE_DIR})
set(LIBS ${SFML_LIBRARIES})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)


#dependencies
if(SFML_UTILS_USE_SYSTEM_CPP_UTILS)
	find_package(utils REQUIRED)
	include_directories(${UTILS_INCLUDE_DIR})
else()
	add_subdirectory(extlibs/cpp-utils)
	include_directories(extlibs/cpp-utils/include)
endif()


# add the subdirectories
add_subdirectory(src)

if(SFML_UTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(SFML_UTILS_BUILD_DOC)
    add_subdirectory(doc)
endif()

