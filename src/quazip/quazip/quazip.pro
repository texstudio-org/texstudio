TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui

# Creating pkgconfig .pc file
CONFIG += create_prl no_install_prl create_pc

QMAKE_PKGCONFIG_PREFIX = $$PREFIX
QMAKE_PKGCONFIG_INCDIR = $$headers.path
QMAKE_PKGCONFIG_REQUIRES = Qt5Core

# The ABI version.

!win32:VERSION = 1.0.0

# 1.0.0 is the first stable ABI.
# The next binary incompatible change will be 2.0.0 and so on.
# The existing QuaZIP policy on changing ABI requires to bump the
# major version of QuaZIP itself as well. Note that there may be
# other reasons for chaging the major version of QuaZIP, so
# in case where there is a QuaZIP major version bump but no ABI change,
# the VERSION variable will stay the same.

# For example:

# QuaZIP 1.0 is released after some 0.x, keeping binary compatibility.
# VERSION stays 1.0.0.
# Then some binary incompatible change is introduced. QuaZIP goes up to
# 2.0, VERSION to 2.0.0.
# And so on.


# This one handles dllimport/dllexport directives.
DEFINES += QUAZIP_BUILD

# You'll need to define this one manually if using a build system other
# than qmake or using QuaZIP sources directly in your project.
CONFIG(staticlib): DEFINES += QUAZIP_STATIC

# Input
include(quazip.pri)


CONFIG(debug, debug|release) {
     mac: TARGET = $$join(TARGET,,,_debug) 
     win32: TARGET = $$join(TARGET,,,d)
}

unix:!symbian {
    headers.path=$$PREFIX/include/quazip
    headers.files=$$HEADERS
    target.path=$$PREFIX/lib/$${LIB_ARCH}
    QMAKE_PKGCONFIG_DESTDIR = pkgconfig
    INSTALLS += headers target

	OBJECTS_DIR=.obj
	MOC_DIR=.moc
	
}

win32 {
    headers.path=$$PREFIX/include/quazip
    headers.files=$$HEADERS
    INSTALLS += headers target
    CONFIG(staticlib){
        target.path=$$PREFIX/lib
        QMAKE_PKGCONFIG_LIBDIR = $$PREFIX/lib/
    } else {
        target.path=$$PREFIX/bin
        QMAKE_PKGCONFIG_LIBDIR = $$PREFIX/bin/
    }

    ## odd, this path seems to be relative to the
    ## target.path, so if we install the .dll into
    ## the 'bin' dir, the .pc will go there as well,
    ## unless have hack the needed path...
    ## TODO any nicer solution?
    QMAKE_PKGCONFIG_DESTDIR = ../lib/pkgconfig
    # workaround for qdatetime.h macro bug
    DEFINES += NOMINMAX
}


symbian {

    # Note, on Symbian you may run into troubles with LGPL.
    # The point is, if your application uses some version of QuaZip,
    # and a newer binary compatible version of QuaZip is released, then
    # the users of your application must be able to relink it with the
    # new QuaZip version. For example, to take advantage of some QuaZip
    # bug fixes.

    # This is probably best achieved by building QuaZip as a static
    # library and providing linkable object files of your application,
    # so users can relink it.

    CONFIG += staticlib
    CONFIG += debug_and_release

    LIBS += -lezip

    #Export headers to SDK Epoc32/include directory
    exportheaders.sources = $$HEADERS
    exportheaders.path = quazip
    for(header, exportheaders.sources) {
        BLD_INF_RULES.prj_exports += "$$header $$exportheaders.path/$$basename(header)"
    }
}
