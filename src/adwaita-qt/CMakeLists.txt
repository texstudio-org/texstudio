project(Adwaita)

cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)
add_definitions(-std=c++11)

option(USE_QT4 "Use Qt4 instead of Qt5" OFF)
if (USE_QT4)
    find_package(Qt4 REQUIRED)
    set(QT_VERSION_NUMBER "4")
else()
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5DBus REQUIRED)
    set(QT_QTGUI_LIBRARY Qt5::Gui Qt5::Widgets)
    set(QT_QTCORE_LIBRARY Qt5::Core)
    set(QT_QTDBUS_LIBRARY Qt5::DBus)
    #target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
    set(QT_VERSION_NUMBER "5")
    get_target_property(REAL_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE}
                       IMPORTED_LOCATION)
    if (NOT QT_PLUGINS_DIR)
        execute_process(COMMAND "${REAL_QMAKE_EXECUTABLE}" -query QT_INSTALL_PLUGINS
                        OUTPUT_VARIABLE QT_PLUGINS_DIR
                        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif()
endif()

if (NOT CMAKE_INSTALL_PREFIX)
    set (CMAKE_INSTALL_PREFIX "/usr/local")
endif()

if (NOT DATA_INSTALL_DIR)
    set (DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share")
endif()
if (NOT THEME_INSTALL_DIR)
    set (THEME_INSTALL_DIR "${DATA_INSTALL_DIR}/themes")
endif()

set(ADWAITA_THEME_DIR "${THEME_INSTALL_DIR}/Adwaita/qt")

option(BUILD_EXAMPLE "Build an example widget factory app" OFF)
if (BUILD_EXAMPLE)
    if (USE_QT4)
        error("It's not possible to build the example using Qt4 yet, sorry.")
    else()
        add_subdirectory(demo)
    endif()
endif()

add_subdirectory(style)
