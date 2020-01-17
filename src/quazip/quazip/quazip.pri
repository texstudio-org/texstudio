isEmpty(USE_SYSTEM_QUAZIP) {
	message(Static quazip5)
	DEFINES += QUAZIP_STATIC
	INCLUDEPATH += $$PWD
	DEPENDPATH += $$PWD

	LIBS *= -lz

	HEADERS += \
		$$PWD/minizip_crypt.h \
		$$PWD/ioapi.h \
		$$PWD/JlCompress.h \
		$$PWD/quaadler32.h \
		$$PWD/quachecksum32.h \
		$$PWD/quacrc32.h \
		$$PWD/quagzipfile.h \
		$$PWD/quaziodevice.h \
		$$PWD/quazipdir.h \
		$$PWD/quazipfile.h \
		$$PWD/quazipfileinfo.h \
		$$PWD/quazip_global.h \
		$$PWD/quazip.h \
		$$PWD/quazipnewinfo.h \
		$$PWD/unzip.h \
		$$PWD/zip.h

	SOURCES += $$PWD/qioapi.cpp \
		$$PWD/JlCompress.cpp \
		$$PWD/quaadler32.cpp \
		$$PWD/quacrc32.cpp \
		$$PWD/quagzipfile.cpp \
		$$PWD/quaziodevice.cpp \
		$$PWD/quazip.cpp \
		$$PWD/quazipdir.cpp \
		$$PWD/quazipfile.cpp \
		$$PWD/quazipfileinfo.cpp \
		$$PWD/quazipnewinfo.cpp \
		$$PWD/unzip.c \
		$$PWD/zip.c
} else {
	message(System quazip5)
	isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip5
	isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip5
	INCLUDEPATH += $${QUAZIP_INCLUDE}
	LIBS += $${QUAZIP_LIB}
}
