cmake_minimum_required(VERSION 3.1.0)

project(TeXstudio VERSION 4.6.0 LANGUAGES C CXX)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(GitInfo)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	git_wc_info(${PROJECT_SOURCE_DIR} VARPREFIX)
	add_definitions(-DTEXSTUDIO_VERSION="${VARPREFIX_WC_LATEST_TAG_LONG}")
	message(STATUS "The current git hash is ${VARPREFIX_WC_REVISION_HASH}")
	message(STATUS "The current git describe is ${VARPREFIX_WC_LATEST_TAG_LONG}")
else()
	add_definitions(-DTEXSTUDIO_VERSION="${CMAKE_PROJECT_VERSION}")
	message(STATUS "No git present.")
    unset(GIT_FOUND)
	set(VARPREFIX_WC_LATEST_TAG_LONG "${CMAKE_PROJECT_VERSION}+0+0")
endif()
include(cmake/project_version.cmake)

if(MSVC)
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS -D_UNICODE -DUNICODE)
	add_compile_options(/wd4267 /wd4244)
	add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
else()
	add_compile_options(-Wno-deprecated-declarations)
endif()

if(WIN32 AND NOT MSVC)
	add_compile_options(-fpermissive)
        add_compile_options(-Wa,-mbig-obj)
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Xml Concurrent Widgets UiTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Svg Qml REQUIRED)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS LinguistTools QUIET)
endif()

message(STATUS "building for Qt ${QT_VERSION_MAJOR}")

# Source
add_subdirectory(src)

# qtsingleapplication
add_subdirectory(src/qtsingleapplication)

# main
set(RESOURCE_FILES 
	texstudio.qrc
	symbols.qrc
	completion.qrc
	images.qrc
)
if(APPLE)
    file(GLOB manual
        utilities/manual/build/html/*.html
    )
    set(manual ${manual} utilities/manual/build/html/searchindex.js)
    file(GLOB images
        utilities/manual/build/html/_images/*.png
    )
    file(GLOB static
        utilities/manual/build/html/_static/*
    )
    file(GLOB static_scripts
        utilities/manual/build/html/_static/scripts/*
    )
    file(GLOB static_styles
        utilities/manual/build/html/_static/styles/*
    )
    file(GLOB design_static
        utilities/manual/build/html/_sphinx_design_static/*
    )
    file(GLOB_RECURSE templates
       templates/*
    )
    file(GLOB_RECURSE translation
       translation/*.qm
    )
    file(GLOB_RECURSE dictionaries
       utilities/dictionaries/*
    )

    set(OSX_FILES
        texstudio.icns
        utilities/latex2e.html
        utilities/latex2e.css
		utilities/list.png
		utilities/manual/source/CHANGELOG.md
        ${templates}
        ${dictionaries}
        ${translation}
    )
else()
    set(OSX_FILES "")
endif()

set(TRANSLATION_FILES
	translation/texstudio_en.ts
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Generate translation source option.")
    qt6_add_lupdate(texstudio TS_FILES ${TRANSLATION_FILES})
endif()

if(WIN32)
	set(SOURCE_FILES ${SOURCE_FILES} win.rc)
endif()
if(UNIX AND NOT APPLE)
	add_subdirectory(src/xkb)
endif()

# Hunspell
find_package(Hunspell QUIET)
if(Hunspell_FOUND)
	message(STATUS "Using system Hunspell")
	set(HUNSPELL_SOURCE_LINK 0)
	get_filename_component(HUNSPELL_LIB_NAME ${HUNSPELL_LIBRARIES} NAME)
	string(FIND ${HUNSPELL_LIB_NAME} "static" HUNSPELL_IS_STATIC_POS)
	if(${HUNSPELL_IS_STATIC_POS} GREATER 0)
		set(HUNSPELL_SOURCE_LINK 1)
	endif()
	if(${HUNSPELL_SOURCE_LINK} GREATER 0)
		option(HUNSPELL_IS_STATIC "Hunspell is a static library" ON)
	else()
		option(HUNSPELL_IS_STATIC "Hunspell is a static library" OFF)
	endif()
else()
	message(STATUS "Using internal Hunspell")
	add_subdirectory(src/hunspell)
	set(HUNSPELL_SOURCE_LINK 2)
	set(HUNSPELL_IS_STATIC ON)
endif()
if(${HUNSPELL_IS_STATIC})
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DHUNSPELL_STATIC)
endif()

# qcodeedit
add_subdirectory(src/qcodeedit)

# debughelper
add_subdirectory(src/debug)

# latexparser
add_subdirectory(src/latexparser)

# symbolpanel
add_subdirectory(src/symbolpanel)

#qtermwidget
if(${QT_VERSION_MAJOR} LESS_EQUAL 5)
    find_package(QTermWidget QUIET)
    if(QTermWidget_FOUND)
        message(STATUS "Using QTermWidget5")
        set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DINTERNAL_TERMINAL)
    endif()
endif()

# QuaZIP
find_package(QuaZip-Qt${QT_VERSION_MAJOR} QUIET)
if(QuaZip-Qt${QT_VERSION_MAJOR}_FOUND)
	message(STATUS "quazip 1.x found")
else()
	find_package(QuaZip QUIET)
	if(QUAZIP_FOUND)
		message(STATUS "Using system QuaZIP")
		set(QUAZIP_SOURCE_LINK 0)
		get_filename_component(QUAZIP_LIB_NAME ${QUAZIP_LIBRARIES} NAME)
		string(FIND ${QUAZIP_LIB_NAME} "static" QUAZIP_IS_STATIC_POS)
		if(${QUAZIP_IS_STATIC_POS} GREATER 0)
			set(QUAZIP_SOURCE_LINK 1)
		endif()
		if(${QUAZIP_SOURCE_LINK} GREATER 0)
			option(QUAZIP_IS_STATIC "QuaZIP is a static library" ON)
		else()
			option(QUAZIP_IS_STATIC "QuaZIP is a static library" OFF)
		endif()
	else()
		message(STATUS "Using internal QuaZIP")
		option(TEXSTUDIO_USE_QT_ZLIB "Use Zlib from Qt" OFF)
		set(BUILD_SHARED_LIBS OFF)
  		set(QUAZIP_INSTALL OFF)
  		set(QUAZIP_USE_QT_ZLIB ${TEXSTUDIO_USE_QT_ZLIB})
  		set(QUAZIP_ENABLE_TESTS OFF)
		set(QUAZIP_BZIP2 OFF)
		set(QUAZIP_IS_STATIC ON)
		set(QUAZIP_SOURCE_LINK 2)
		add_subdirectory(src/quazip)
	endif()
	if(${QUAZIP_IS_STATIC})
		set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DQUAZIP_STATIC)
	endif()
endif()

# Options
if(NOT MSVC)
	option(TEXSTUDIO_ENABLE_CRASH_HANDLER "Enable/Disable internal crash handler" ON)
	if(NOT ${TEXSTUDIO_ENABLE_CRASH_HANDLER})
		message(STATUS "Internal crash handler disabled as you wish.")
		set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DNO_CRASH_HANDLER)
	endif()
else()
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DNO_CRASH_HANDLER)
endif()

option(TEXSTUDIO_BUILD_ADWAITA "Enable/Disable internal adwaita-qt style" ON)
if(TEXSTUDIO_BUILD_ADWAITA)
    find_package(Qt${QT_VERSION_MAJOR}DBus REQUIRED)
    set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DADWAITA)
    message(STATUS "integrate adwaita style")
endif()
add_subdirectory(src/adwaita-qt)

option(TEXSTUDIO_ENABLE_TESTS "Enable/Disable internal tests" OFF)
if(${TEXSTUDIO_ENABLE_TESTS})
	message(STATUS "tests enabled.")
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)
	set(HEADER_FILES ${HEADER_FILES}
		src/tests/buildmanager_t.h
		src/tests/codesnippet_t.h
		src/tests/encoding_t.h
		src/tests/execprogram_t.h
		src/tests/git_t.h
		src/tests/help_t.h
		src/tests/latexcompleter_t.h
		src/tests/latexdocument_t.h
		src/tests/latexeditorview_bm.h
		src/tests/latexeditorview_t.h
		src/tests/latexoutputfilter_t.h
		src/tests/latexparser_t.h
		src/tests/latexparsing_t.h
		src/tests/latexstyleparser_t.h
		src/tests/qcetestutil.h
		src/tests/qdocumentcursor_t.h
		src/tests/qdocumentline_t.h
		src/tests/qdocumentsearch_t.h
		src/tests/qeditor_t.h
		src/tests/qsearchreplacepanel_t.h
		src/tests/scriptengine_t.h
		src/tests/smallUsefulFunctions_t.h
		src/tests/structureview_t.h
		src/tests/syntaxcheck_t.h
		src/tests/tablemanipulation_t.h
		src/tests/testmanager.h
		src/tests/testutil.h
		src/tests/updatechecker_t.h
		src/tests/usermacro_t.h
		src/tests/utilsui_t.h
		src/tests/utilsversion_t.h
	)
	set(SOURCE_FILES ${SOURCE_FILES}
		src/tests/codesnippet_t.cpp
		src/tests/encoding_t.cpp
		src/tests/execprogram_t.cpp
		src/tests/git_t.cpp
		src/tests/latexcompleter_t.cpp
		src/tests/latexdocument_t.cpp
		src/tests/latexeditorview_bm.cpp
		src/tests/latexeditorview_t.cpp
		src/tests/latexoutputfilter_t.cpp
		src/tests/latexparser_t.cpp
		src/tests/latexparsing_t.cpp
		src/tests/latexstyleparser_t.cpp
		src/tests/qcetestutil.cpp
		src/tests/qdocumentcursor_t.cpp
		src/tests/qdocumentline_t.cpp
		src/tests/qdocumentsearch_t.cpp
		src/tests/qeditor_t.cpp
		src/tests/qsearchreplacepanel_t.cpp
		src/tests/scriptengine_t.cpp
		src/tests/smallUsefulFunctions_t.cpp
		src/tests/structureview_t.cpp
		src/tests/syntaxcheck_t.cpp
		src/tests/tablemanipulation_t.cpp
		src/tests/testmanager.cpp
		src/tests/testutil.cpp
		src/tests/usermacro_t.cpp
	)
else()
	message(STATUS "tests disabled.")
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DNO_TESTS)
endif()

option(TEXSTUDIO_ENABLE_MEDIAPLAYER "Enable/Disable the video player in pdf files" OFF)
if(${TEXSTUDIO_ENABLE_MEDIAPLAYER})
	message(STATUS "the video player in pdf files is enabled.")
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Multimedia MultimediaWidgets REQUIRED)
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DMEDIAPLAYER)
else()
	message(STATUS "the video player in pdf files is disabled.")
endif()

option(TEXSTUDIO_ENABLE_DEBUG_LOGGER "Enable/Disable debug logger" OFF)
if(${TEXSTUDIO_ENABLE_DEBUG_LOGGER})
	message(STATUS "Debug logger is built.")
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DDEBUG_LOGGER)
endif()

# poppler

find_package(PkgConfig)
pkg_check_modules(POPPLER QUIET IMPORTED_TARGET poppler-cpp poppler-qt${QT_VERSION_MAJOR})
if(POPPLER_FOUND)
    message(STATUS "Build internal pdf previewer.")
else()
    message(STATUS "Poppler not found, internal pdf previewer disabled.")
    set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DNO_POPPLER_PREVIEW)
    if(WIN32)
        set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -D_WIN32)
    endif()
endif()
add_subdirectory(src/pdfviewer)

# Build texstudio application
add_executable(texstudio ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} ${FORM_FILES} ${OSX_FILES} ${manual} ${images} ${static} ${static_scripts} ${static_styles} ${design_static})
target_link_libraries(texstudio PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::UiTools
)
if(NOT MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
    target_precompile_headers(texstudio PUBLIC src/mostQtHeaders.h)
endif()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(texstudio PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)
endif()
if(TEXSTUDIO_BUILD_ADWAITA)
    target_link_libraries(texstudio PRIVATE Qt${QT_VERSION_MAJOR}::DBus)
endif()

set_source_files_properties(${OSX_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${manual} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html")
set_source_files_properties(${images} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html/_images")
set_source_files_properties(${static} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html/_static")
set_source_files_properties(${static_scripts} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html/_static/scripts")
set_source_files_properties(${static_styles} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html/_static/styles")
set_source_files_properties(${design_static} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/html/_sphinx_design_static")

set_target_properties(texstudio PROPERTIES
    #MACOSX_BUNDLE_GUI_IDENTIFIER texstudio.org
    #MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    #MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    #MACOSX_BUNDLE_ICON_FILE texstudio.icns
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# debughelper -> pthread
if(${TEXSTUDIO_ENABLE_CRASH_HANDLER})
	set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
	set(THREADS_PREFER_PTHREAD_FLAG TRUE)
	find_package(Threads REQUIRED)
	target_link_libraries(texstudio PUBLIC Threads::Threads)
endif()

target_include_directories(texstudio PUBLIC ${INC_DIRECTORIES})
target_compile_definitions(texstudio PUBLIC ${ADDITIONAL_DEFINITIONS})
if(Hunspell_FOUND)
	target_include_directories(texstudio PUBLIC ${HUNSPELL_INCLUDE_DIR})
	target_link_libraries(texstudio PUBLIC ${HUNSPELL_LIBRARIES})
else()
	target_include_directories(texstudio PUBLIC src/hunspell)
	target_link_libraries(texstudio PUBLIC hunspell)
endif()
if(QuaZip-Qt${QT_VERSION_MAJOR}_FOUND)
	target_link_libraries(texstudio PUBLIC QuaZip::QuaZip)
else()
	if(QUAZIP_FOUND)
		target_include_directories(texstudio PUBLIC ${QUAZIP_INCLUDE_DIR})
		target_link_libraries(texstudio PUBLIC ${QUAZIP_LIBRARIES})
	else()
		target_link_libraries(texstudio PUBLIC QuaZip::QuaZip)
	endif()
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
	target_include_directories(texstudio PUBLIC ${ZLIB_INCLUDE_DIR})
	target_link_libraries(texstudio PUBLIC ${ZLIB_LIBRARIES})
endif()

if(UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
	target_include_directories(texstudio PUBLIC ${X11_INCLUDE_DIRS})
	target_link_libraries(texstudio PUBLIC ${X11_LIBRARIES})
endif()

#qtermwidget
if(QTERMWIDGET_FOUND AND ${QT_VERSION_MAJOR} LESS_EQUAL 5 )
   target_link_libraries(texstudio PUBLIC qtermwidget5)
endif()

#mediaplayer
if(Qt${QT_VERSION_MAJOR}Multimedia_FOUND)
	message(STATUS "${Qt${QT_VERSION_MAJOR}Multimedia_FOUND}")
	target_include_directories(texstudio PUBLIC ${Qt${QT_VERSION_MAJOR}Multimedia_INCLUDE_DIRS})
	target_include_directories(texstudio PUBLIC ${Qt${QT_VERSION_MAJOR}MultimediaWidgets_INCLUDE_DIRS})
	target_link_libraries(texstudio PUBLIC Qt${QT_VERSION_MAJOR}::Multimedia)
	target_link_libraries(texstudio PUBLIC Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
endif()

if(POPPLER_FOUND)
        target_link_libraries(texstudio PUBLIC PkgConfig::POPPLER)
endif()
if(${TEXSTUDIO_ENABLE_TESTS})
    target_link_libraries(texstudio PUBLIC Qt${QT_VERSION_MAJOR}::Test)
    target_include_directories(texstudio PUBLIC src/tests)
endif()
if(WIN32)
    target_link_libraries(texstudio PUBLIC Shlwapi)
endif()

## installation

install(TARGETS texstudio DESTINATION bin)

if(UNIX AND NOT APPLE)
        option(APPDATA "Install appdata" ON)
	install(FILES utilities/texstudio.desktop DESTINATION share/applications)
	install(FILES utilities/texstudio.svg DESTINATION share/icons/hicolor/scalable/apps)
        if(${APPDATA})
		install(FILES utilities/texstudio.metainfo.xml DESTINATION share/metainfo)
	endif()
endif()

if(UNIX)
	install(DIRECTORY translation/
		DESTINATION share/texstudio
		FILES_MATCHING
		PATTERN *.qm
	)
	install(DIRECTORY templates/
		DESTINATION share/texstudio
		FILES_MATCHING
		PATTERN *
	)
	install(DIRECTORY utilities/dictionaries/
		DESTINATION share/texstudio
		FILES_MATCHING
		PATTERN *
	)
	install(DIRECTORY utilities/manual/build/html/
		DESTINATION share/texstudio
		FILES_MATCHING
		PATTERN *.html
	)
	install(DIRECTORY utilities/manual/build/html/_images
		DESTINATION share/texstudio
		FILES_MATCHING
		PATTERN *.png
	)
	install(DIRECTORY utilities/manual/build/html/_sphinx_design_static
		DESTINATION share/texstudio
	)
	install(DIRECTORY utilities/manual/build/html/_static
		DESTINATION share/texstudio
	)
	install(FILES utilities/manual/build/html/searchindex.js DESTINATION share/texstudio)
	install(FILES utilities/latex2e.html DESTINATION share/texstudio)
	install(FILES utilities/latex2e.css DESTINATION share/texstudio)
	install(FILES utilities/list.png DESTINATION share/texstudio)
	install(FILES utilities/AUTHORS DESTINATION share/texstudio)
	install(FILES utilities/COPYING DESTINATION share/texstudio)
	install(FILES utilities/manual/source/CHANGELOG.md DESTINATION share/texstudio)
endif()
