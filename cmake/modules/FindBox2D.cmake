# USAGE
#
# find_package(BOX2D)
#
# If Box2D is not installed in a standard path, you can use the BOX2DDIR or
# BOX2D_ROOT CMake (or environment) variables to tell CMake where to look for
# Box2D.
#
#
# OUTPUT
#
# This script defines the following variables:
#   - BOX2D_LIBRARY_DEBUG:   the path to the debug library
#   - BOX2D_LIBRARY_RELEASE: the path to the release library
#   - BOX2D_LIBRARY:         the path to the library to link to
#   - BOX2D_FOUND:           true if the Box2D library is found
#   - BOX2D_INCLUDE_DIR:     the path where Box2D headers are located (the directory containing the Box2D/Box2D.hpp file)
#
#
# EXAMPLE
#
# find_package(Box2D REQUIRED)
# include_directories(${BOX2D_INCLUDE_DIR})
# add_executable(myapp ...)
# target_link_libraries(myapp ${BOX2D_LIBRARY} ...)

set(BOX2D_FOUND FALSE)

find_path(
	BOX2D_INCLUDE_DIR
	Box2D/Box2D.h
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${BOX2DDIR}
		${BOX2D_ROOT}
		$ENV{BOX2DDIR}
		$ENV{BOX2D_ROOT}
)

find_library(
	BOX2D_LIBRARY_RELEASE
    Box2D
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${BOX2DDIR}
		${BOX2D_ROOT}
		$ENV{BOX2DDIR}
		$ENV{BOX2D_ROOT}
)

find_library(
	BOX2D_LIBRARY_DEBUG
    Box2D-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${BOX2DDIR}
		${BOX2D_ROOT}
		$ENV{BOX2DDIR}
		$ENV{BOX2D_ROOT}
)

if(BOX2D_LIBRARY_RELEASE AND BOX2D_LIBRARY_DEBUG)
	set(BOX2D_LIBRARY debug ${BOX2D_LIBRARY_DEBUG} optimized ${BOX2D_LIBRARY_RELEASE})
endif()

if(BOX2D_LIBRARY_RELEASE AND NOT BOX2D_LIBRARY_DEBUG)
	set(BOX2D_LIBRARY_DEBUG ${BOX2D_LIBRARY_RELEASE})
	set(BOX2D_LIBRARY ${BOX2D_LIBRARY_RELEASE})
endif()

if(BOX2D_LIBRARY_DEBUG AND NOT BOX2D_LIBRARY_RELEASE)
	set(BOX2D_LIBRARY_RELEASE ${BOX2D_LIBRARY_DEBUG})
	set(BOX2D_LIBRARY ${BOX2D_LIBRARY_DEBUG})
endif()

if(NOT BOX2D_INCLUDE_DIR OR NOT BOX2D_LIBRARY)
	if(BOX2D_FIND_REQUIRED)
		message(FATAL_ERROR "Box2D not found.")
	elseif(NOT BOX2D_FIND_QUIETLY)
		message("Box2D not found.")
	endif()
else()
	set(BOX2D_FOUND true)
	if (NOT BOX2D_FIND_QUIETLY)
		message(STATUS "Box2D found: ${BOX2D_INCLUDE_DIR}")
	endif()
endif()
