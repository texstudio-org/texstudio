# - Try to find Hunspell
# Once done this will define
#
#  HUNSPELL_FOUND - system has Hunspell
#  HUNSPELL_INCLUDE_DIR - the Hunspell include directory
#  HUNSPELL_LIBRARIES - Link these to use Hunspell
#
if(HUNSPELL_INCLUDE_DIR AND HUNSPELL_LIBRARIES)
	set(Hunspell_FIND_QUIETLY TRUE)
endif()

# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
if(WIN32)

else()
	find_package(PkgConfig)
	pkg_check_modules(HUNSPELL_PKG QUIET hunspell)
endif()

find_path(HUNSPELL_INCLUDE_DIR NAMES hunspell.h hunspell.hxx
	PATHS
		/usr/local/include
		/usr/include
		include
		$ENV{HUNSPELL_HOME}/include
	HINTS
		${HUNSPELL_PKG_INCLUDE_DIRS}
	PATH_SUFFIXES
		hunspell
)

find_library(HUNSPELL_LIBRARIES NAMES hunspell-1.7 hunspell-1.6 hunspell-1.5 hunspell-1.4 hunspell-1.3 hunspell-1.2 hunspell libhunspell libhunspell_static libhunspellstatic ${HUNSPELL_PKG_LIBRARIES}
	PATHS
		/usr/local
		/usr
		/opt/local/lib
		$ENV{HUNSPELL_HOME}/lib
	HINTS
		${HUNSPELL_PKG_LIBRARY_DIRS}
	PATH_SUFFIXES
		lib64
		lib
		x64
		x86
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Hunspell DEFAULT_MSG HUNSPELL_LIBRARIES HUNSPELL_INCLUDE_DIR)
mark_as_advanced(HUNSPELL_INCLUDE_DIR HUNSPELL_LIBRARIES)
