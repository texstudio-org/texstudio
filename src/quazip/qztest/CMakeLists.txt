set(QZTEST_SOURCES
        qztest.h
        testjlcompress.h
        testquachecksum32.h
        testquagzipfile.h
        testquaziodevice.h
        testquazip.h
        testquazipdir.h
        testquazipfile.h
        testquazipfileinfo.h
        testquazipnewinfo.h
        qztest.cpp
        testjlcompress.cpp
        testquachecksum32.cpp
        testquagzipfile.cpp
        testquaziodevice.cpp
        testquazip.cpp
        testquazipdir.cpp
        testquazipfile.cpp
        testquazipfileinfo.cpp
        testquazipnewinfo.cpp
)

add_executable(qztest ${QZTEST_SOURCES} qztest.qrc)
set_target_properties(qztest PROPERTIES AUTORCC ON)
target_include_directories(qztest PRIVATE ${QUAZIP_INC})
target_link_libraries(qztest
    ${QUAZIP_TEST_QT_LIBRARIES}
    QuaZip::QuaZip
)

add_test(NAME qztest_test
	COMMAND qztest
	WORKING_DIRECTORY ${QUAZIP_BINARY_DIR}/quazip # preliminary hack to find the dll on windows
)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS qztest)
