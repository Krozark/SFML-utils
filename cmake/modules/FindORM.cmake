# This script locates the ORM library.
#
# USAGE
# find_package(ORM)
#
# If ORM is not installed in a standard path, you can use
# ORM_ROOT CMake (or environment) variables to tell CMake where to look for
# ORM.
#
#
# OUTPUT
#
# This script defines the following variables:
#   - ORM_LIBRARY:         the path to the library to link to
#   - ORM_FOUND:           true if the ORM library is found
#   - ORM_INCLUDE_DIR:     the path where ORM headers are located
#
#
# EXAMPLE
#
# find_package( ORM REQUIRED )
# include_directories( ${ORM_INCLUDE_DIR} )
# add_executable( myapp ... )
# target_link_libraries( myapp ${ORM_LIBRARY} ... )

set( ORM_FOUND false )

if(NOT DEFINED ORM_USE_CACHE)
    set(ORM_USE_CACHE TRUE)
endif()

if(ORM_USE_CACHE)
    add_definitions("-DORM_USE_CACHE")
endif()

set(ORM_USE_CACHE ${ORM_USE_CACHE} CACHE BOOL "use ORM cache" FORCE)


find_path(
	ORM_INCLUDE_DIR
    ORM/models.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${ORMDIR}
		${ORM_ROOT}
		$ENV{ORM_ROOT}
		$ENV{ORMDIR}
)

find_library(
	ORM_LIBRARY
	orm
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${ORMDIR}
		${ORM_ROOT}
		$ENV{ORM_ROOT}
		$ENV{ORMDIR}
)

if( NOT ORM_INCLUDE_DIR OR NOT ORM_LIBRARY )
	message( FATAL_ERROR "cpp-utils not found. Set ORM_ROOT to the installation root directory (containing inculde/ and lib/)" )
else()
	message( STATUS "cpp-utils found: ${ORM_INCLUDE_DIR}" )
endif()
