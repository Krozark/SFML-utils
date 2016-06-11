cmake_minimum_required (VERSION 2.8.8)

include(cmake/macro.cmake)

# project name
set(PROJECT_NAME SFML-utils)
project (${PROJECT_NAME})

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 3)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules;${CMAKE_SOURCE_DIR}")



# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#add an option for building the examples
set_option(SFML_UTILS_BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(SFML_UTILS_BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")


set_option(SFML_UTILS_USE_SYSTEM_CPP_UTILS TRUE BOOL "Use cpp-utils from system, false to compile it from dependencies")

set_option(SFML_UTILS_BUILD_STATIC FALSE BOOL "Build as STATIC library")
set_option(SFML_UTILS_BUILD_SHARED TRUE BOOL "Build as SHARED library")

set_option(SFML_UTILS_BUILD_MODULE_MAP_DATABASE TRUE BOOL "TRUE the DATABSE support for the map system")

####################$ MODULES ########################

set_option(SFML_UTILS_BUILD_MODULE_ENTITY_SYSTEM TRUE BOOL "TRUE to build the entity system")

set_option(SFML_UTILS_BUILD_MODULE_GUI TRUE BOOL "TRUE to build the GUI")

set_option(SFML_UTILS_BUILD_MODULE_MAP TRUE BOOL "TRUE to build the map module")

set_option(SFML_UTILS_BUILD_MODULE_CEGUI TRUE BOOL "TRUE to build cegui wrapper for SFML")
if(SFML_UTILS_BUILD_MODULE_CEGUI)
    find_package(CEGUI REQUIRED)
    include_directories(${CEGUI_INCLUDE_DIR})

    set(LIBS_CEGUI
        ${CEGUI_LIBRARIES}
        ${CEGUI_LIBRARY_REL}
        ${CEGUI_ExpatParser_LIBRARY_REL} expat
        ${CEGUI_OpenGLRenderer_LIBRARY_REL} GL GLU
        ${CEGUI_FreeImageImageCodec_LIBRARY_REL} freeimage
        )
endif()

if(SFML_UTILS_BUILD_MODULE_MAP AND SFML_UTILS_BUILD_MODULE_CEGUI AND SFML_UTILS_BUILD_MODULE_MAP_DATABASE)
    set_option(SFML_UTILS_BUILD_MODULE_MAP_EDITOR TRUE BOOL "TRUE to build the map module EDITOR")
    set_option(ORM_BUILD_SUPPORT_MYSQL TRUE BOOL "TRUE to support Mysql backends, else, Sqlite3")
    add_definitions("-DORM_BUILD_SUPPORT_MYSQL=${ORM_BUILD_SUPPORT_MYSQL}")
endif()

set_option(SFML_UTILS_BUILD_MODULE_BOX2D TRUE BOOL "TRUE to build box2d wrapper for SFML")

if(SFML_UTILS_BUILD_MODULE_BOX2D)
    find_package(Box2D REQUIRED)
    include_directories(${BOX2D_INCLUDE_DIR})
endif()


######################

set(SFML_UTILS_BUILD_TYPE "")
if(SFML_UTILS_BUILD_SHARED)
    list(APPEND SFML_UTILS_BUILD_TYPE SHARED)
    set(SFML_UTILS_BUILD_SUFIX shared)
endif()

if(SFML_UTILS_BUILD_STATIC)
    list(APPEND SFML_UTILS_BUILD_TYPE STATIC)
    set(SFML_UTILS_BUILD_SUFIX static)
endif()


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
	set(UTILS_LIBRARY utils-shared)
	set(UTILS_JSON_LIBRARY utils-json-shared)
	include_directories(extlibs/cpp-utils/include)
endif()

if(SFML_UTILS_BUILD_MODULE_MAP_DATABASE)
    find_package(ORM REQUIRED)
    include_directories(${ORM_INCLUDE_DIR})
    add_definitions("-DSFML_UTILS_BUILD_MODULE_MAP_DATABASE")
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

deploy(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
    DESTINATION include
)
