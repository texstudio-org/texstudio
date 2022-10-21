set(INC_DIRECTORIES
	${INC_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/quazip
	PARENT_SCOPE
)

set(QUAZIP_HEADER_FILES
	quazip/minizip_crypt.h
	quazip/ioapi.h
	quazip/JlCompress.h
	quazip/quaadler32.h
	quazip/quachecksum32.h
	quazip/quacrc32.h
	quazip/quagzipfile.h
	quazip/quaziodevice.h
	quazip/quazipdir.h
	quazip/quazipfile.h
	quazip/quazipfileinfo.h
	quazip/quazip_global.h
	quazip/quazip.h
	quazip/quazipnewinfo.h
	quazip/unzip.h
	quazip/zip.h
)

set(QUAZIP_SOURCE_FILES
	quazip/qioapi.cpp
	quazip/JlCompress.cpp
	quazip/quaadler32.cpp
	quazip/quacrc32.cpp
	quazip/quagzipfile.cpp
	quazip/quaziodevice.cpp
	quazip/quazip.cpp
	quazip/quazipdir.cpp
	quazip/quazipfile.cpp
	quazip/quazipfileinfo.cpp
	quazip/quazipnewinfo.cpp
	quazip/unzip.c
	quazip/zip.c
)

add_library(quazip STATIC ${QUAZIP_HEADER_FILES} ${QUAZIP_SOURCE_FILES})
target_compile_definitions(quazip PUBLIC -DQUAZIP_STATIC)
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
	target_include_directories(quazip PUBLIC ${ZLIB_INCLUDE_DIR})
	target_link_libraries(quazip PUBLIC ${ZLIB_LIBRARIES})
else()
	message(FATAL_ERROR "Could NOT find ZLIB")
endif()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
	target_link_libraries(quazip PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Core5Compat)
else()
	target_link_libraries(quazip PUBLIC Qt${QT_VERSION_MAJOR}::Core)
endif()

