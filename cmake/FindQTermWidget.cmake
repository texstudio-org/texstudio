# - Try to find QTermWidget5
# cmake varaint fails on ubuntu for missing libutf8proc.so
# Once done this will define
#
#  QTERMWIDGET_FOUND - system has QTermWidget5
#  QTERMWIDGET_INCLUDE_DIR - the QTermWidget5 include directory
#  QTERMWIDGET_LIBRARIES - Link these to use QTermWidget5
#
if(QTERMWIDGET_INCLUDE_DIR AND QTERMWIDGET_LIBRARIES)
	set(QTERMWIDGET_FIND_QUIETLY TRUE)
endif()


find_package(PkgConfig)
pkg_check_modules(QTERMWIDGET_PKG QUIET qtermwidget5)


find_path(QTERMWIDGET_INCLUDE_DIR NAMES qtermwidget.h
	PATHS
		/usr/local/include
		/usr/include
		include
		$ENV{QTERMWIDGET_HOME}/include
	HINTS
		${QTERMWIDGET_PKG_INCLUDE_DIRS}
	PATH_SUFFIXES
		qtermwidget5
)

find_library(QTERMWIDGET_LIBRARIES NAMES qtermwidget5 ${QTERMWIDGET_PKG_LIBRARIES}
	PATHS
		/usr/local
		/usr
		/opt/local/lib
		$ENV{QTERMWIDGET_HOME}/lib
	HINTS
		${QTERMWIDGET_PKG_LIBRARY_DIRS}
	PATH_SUFFIXES
		lib64
		lib
		x64
		x86
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QTermWidget DEFAULT_MSG QTERMWIDGET_LIBRARIES QTERMWIDGET_INCLUDE_DIR)
mark_as_advanced(QTERMWIDGET_INCLUDE_DIR QTERMWIDGET_LIBRARIES)
