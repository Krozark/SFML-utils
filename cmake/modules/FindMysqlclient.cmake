# This script locates the Mysqlclient library.
#
# USAGE
# find_package( Mysqlclient )
#
# If Mysqlclient is not installed in a standard path, you can use
# Mysqlclient_ROOT CMake (or environment) variables to tell CMake where to look for
# Mysqlclient.
#
#
# OUTPUT
#
# This script defines the following variables:
#   - Mysqlclient_LIBRARY:         the path to the library to link to
#   - Mysqlclient_FOUND:           true if the UTILS library is found
#   - Mysqlclient_INCLUDE_DIR:     the path where UTILS headers are located
#
#
# EXAMPLE
#
# find_package( Mysqlclient REQUIRED )
# include_directories( ${Mysqlclient_INCLUDE_DIR} )
# add_executable( myapp ... )
# target_link_libraries( myapp ${Mysqlclient_LIBRARY} ... )

set( Mysqlclient_FOUND false )

find_path(
    Mysqlclient_INCLUDE_DIR
	my_config.h
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
        ${Mysqlclient_DIR}
        ${Mysqlclient_ROOT}
        $ENV{Mysqlclient_ROOT}
        $ENV{Mysqlclient_DIR}
)

find_library(
	Mysqlclient_LIBRARY
	mysqlclient
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${Mysqlclient_DIR}
        ${Mysqlclient_ROOT}
        $ENV{Mysqlclient_ROOT}
        $ENV{Mysqlclient_DIR}
)

if( NOT Mysqlclient_INCLUDE_DIR OR NOT Mysqlclient_LIBRARY )
    message( FATAL_ERROR "mysqlclient not found. Set Mysqlclient_ROOT to the installation root directory (containing include/ and lib/)" )
else()
    message( STATUS "mysqlclient found: ${Mysqlclient_INCLUDE_DIR}" )
endif()
