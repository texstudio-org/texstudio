cmake_minimum_required(VERSION 3.1.0)

project(TeXstudio LANGUAGES C CXX)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

include(cmake/project_version.cmake)

if(MSVC)
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS -D_UNICODE -DUNICODE)
	add_compile_options(/wd4267 /wd4244)
endif()

find_package(Qt5 COMPONENTS Core Network Xml Svg Script PrintSupport Concurrent Widgets UiTools REQUIRED)

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

set(TRANSLATION_FILES
	translation/texstudio_ar.ts
	translation/texstudio_cs.ts
	translation/texstudio_de.ts
	translation/texstudio_el.ts
	translation/texstudio_es.ts
	translation/texstudio_fa.ts
	translation/texstudio_fr.ts
	translation/texstudio_hu.ts
	translation/texstudio_id_ID.ts
	translation/texstudio_it.ts
	translation/texstudio_ja.ts
	translation/texstudio_ko.ts
	translation/texstudio_ko_KR.ts
	translation/texstudio_nl.ts
	translation/texstudio_pl.ts
	translation/texstudio_pt_BR.ts
	translation/texstudio_ru_RU.ts
	translation/texstudio_tr_TR.ts
	translation/texstudio_uk.ts
	translation/texstudio_vi.ts
	translation/texstudio_zh_CN.ts
)

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

# latexparser
add_subdirectory(src/latexparser)

# symbolpanel
add_subdirectory(src/symbolpanel)

# QuaZIP
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
	add_subdirectory(src/quazip)
	set(QUAZIP_SOURCE_LINK 2)
	set(QUAZIP_IS_STATIC ON)
endif()
if(${QUAZIP_IS_STATIC})
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DQUAZIP_STATIC)
endif()

# pdfviewer
add_subdirectory(src/pdfviewer)

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
option(TEXSTUDIO_ENABLE_TESTS "Enable/Disable internal tests" OFF)
if(${TEXSTUDIO_ENABLE_TESTS})
	find_package(Qt5 COMPONENTS Test REQUIRED)
	set(HEADER_FILES ${HEADER_FILES}
		src/tests/qsearchreplacepanel_t.h
		src/tests/updatechecker_t.h
		src/tests/qdocumentcursor_t.h
		src/tests/qdocumentline_t.h
		src/tests/qdocumentsearch_t.h
		src/tests/codesnippet_t.h
		src/tests/latexcompleter_t.h
		src/tests/latexeditorview_bm.h
		src/tests/latexeditorview_t.h
		src/tests/latexoutputfilter_t.h
		src/tests/latexparser_t.h
		src/tests/latexparsing_t.h
		src/tests/latexstyleparser_t.h
		src/tests/scriptengine_t.h
		src/tests/qeditor_t.h
		src/tests/buildmanager_t.h
		src/tests/tablemanipulation_t.h
		src/tests/smallUsefulFunctions_t.h
		src/tests/utilsui_t.h
		src/tests/utilsversion_t.h
		src/tests/encoding_t.h
		src/tests/help_t.h
		src/tests/syntaxcheck_t.h
		src/tests/qcetestutil.h
		src/tests/testmanager.h
		src/tests/testutil.h
		src/tests/usermacro_t.h
		src/tests/structureview_t.h
	)
	set(SOURCE_FILES ${SOURCE_FILES}
		src/tests/codesnippet_t.cpp
		src/tests/encoding_t.cpp
		src/tests/latexcompleter_t.cpp
		src/tests/latexeditorview_bm.cpp
		src/tests/latexeditorview_t.cpp
		src/tests/latexoutputfilter_t.cpp
		src/tests/latexparser_t.cpp
		src/tests/latexparsing_t.cpp
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
		src/tests/usermacro_t.cpp
		src/tests/testmanager.cpp
		src/tests/testutil.cpp
	)
else()
	message(STATUS "tests disabled as you wish.")
	set(ADDITIONAL_DEFINITIONS ${ADDITIONAL_DEFINITIONS} -DNO_TESTS)
endif()

# Build texstudio application
add_executable(texstudio ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} ${FORM_FILES})
target_link_libraries(texstudio PUBLIC Qt5::Core Qt5::Network Qt5::Xml Qt5::Svg Qt5::Script Qt5::PrintSupport Qt5::Concurrent Qt5::Widgets Qt5::UiTools)
target_include_directories(texstudio PUBLIC ${INC_DIRECTORIES})
target_compile_definitions(texstudio PUBLIC ${ADDITIONAL_DEFINITIONS})
if(Hunspell_FOUND)
	target_include_directories(texstudio PUBLIC ${HUNSPELL_INCLUDE_DIR})
	target_link_libraries(texstudio PUBLIC ${HUNSPELL_LIBRARIES})
else()
	target_include_directories(texstudio PUBLIC src/hunspell)
	target_link_libraries(texstudio PUBLIC hunspell)
endif()
if(QUAZIP_FOUND)
	target_include_directories(texstudio PUBLIC ${QUAZIP_INCLUDE_DIR})
	target_link_libraries(texstudio PUBLIC ${QUAZIP_LIBRARIES})
else()
	target_include_directories(texstudio PUBLIC src/quazip/quazip)
	target_link_libraries(texstudio PUBLIC quazip)
endif()
if(ZLIB_FOUND)
	target_include_directories(texstudio PUBLIC ${ZLIB_INCLUDE_DIR})
	target_link_libraries(texstudio ${ZLIB_LIBRARIES})
endif()
find_package(Poppler)
if(Poppler_FOUND)
	message(STATUS "${Poppler_DEFINITIONS}")
	target_link_libraries(texstudio PUBLIC Poppler::Qt5)
	target_compile_options(texstudio PUBLIC ${Poppler_DEFINITIONS})
else()
	target_compile_options(texstudio PUBLIC -DNO_POPPLER_PREVIEW)
	message(STATUS "Internal pdf previewer disabled as you wish.")
endif()
if(${TEXSTUDIO_ENABLE_TESTS})
	target_link_libraries(texstudio PUBLIC Qt5::Test)
	target_include_directories(texstudio PUBLIC src/tests)
endif()
if(WIN32)
	target_link_libraries(texstudio PUBLIC Shlwapi)
	#if(MSVC)
	#	get_filename_component(QT_BIN ${Qt5_DIR}/../../../bin/ ABSOLUTE)
	#	file(TO_NATIVE_PATH "${QT_BIN}" QT_BIN)
	#	set(QT_MSVC_DEBUGGER_ENV ${CMAKE_BINARY_DIR}/texstudio.vcxproj.user)
	#	file(WRITE ${QT_MSVC_DEBUGGER_ENV} "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "<Project ToolsVersion=\"15.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "  <PropertyGroup>\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "    <LocalDebuggerEnvironment>PATH=${QT_BIN};%PATH% $(LocalDebuggerEnvironment)</LocalDebuggerEnvironment>\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "  </PropertyGroup>\n")
	#	file(APPEND ${QT_MSVC_DEBUGGER_ENV} "</Project>")
	#endif()
endif()

include(cmake/project_install.cmake)
