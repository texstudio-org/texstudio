#
# Sets PROJECT_VERSION and PACKAGE_VERSION
#

function(version_split version major minor patch extra)
    string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)(.*)?" version_valid ${version})
    if(version_valid)
        string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)(.*)?" "\\1;\\2;\\3;\\4" VERSION_MATCHES ${version})
        list(GET VERSION_MATCHES 0 version_major)
        set(${major} ${version_major} PARENT_SCOPE)
        list(GET VERSION_MATCHES 1 version_minor)
        set(${minor} ${version_minor} PARENT_SCOPE)
        list(GET VERSION_MATCHES 2 version_patch)
        set(${patch} ${version_patch} PARENT_SCOPE)
        list(GET VERSION_MATCHES 3 version_extra)
        set(${extra} ${version_extra} PARENT_SCOPE)
    else(version_valid)
        message(AUTHOR_WARNING "Bad version ${version}; falling back to 0 (have you made an initial release?)")
        set(${major} "0" PARENT_SCOPE)
        set(${minor} "0" PARENT_SCOPE)
        set(${patch} "0" PARENT_SCOPE)
        set(${extra} "" PARENT_SCOPE)
    endif(version_valid)
endfunction(version_split)

find_program(GIT_CMD git)
mark_as_advanced(GIT_CMD)
if (GIT_CMD)
    execute_process(COMMAND ${GIT_CMD} rev-parse --show-toplevel
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_TOPLEVEL
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()
if (GIT_CMD AND NOT "${GIT_TOPLEVEL}" STREQUAL "")
    execute_process(COMMAND ${GIT_CMD} rev-parse --short HEAD
            WORKING_DIRECTORY ${GIT_TOPLEVEL}
            OUTPUT_VARIABLE GIT_SHA1
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${GIT_CMD} describe --match "*[0-9].[0-9]*" HEAD
            WORKING_DIRECTORY ${GIT_TOPLEVEL}
            OUTPUT_VARIABLE GIT_DESCRIBE
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (GIT_DESCRIBE)
		set(TEXSTUDIO_GIT_REVISION ${GIT_DESCRIBE})
        string(REGEX REPLACE "v?([0-9.]+).*" "\\1" GIT_VERSION ${GIT_DESCRIBE})
        message(STATUS "GIT_VERSION: " ${GIT_VERSION})
        if (GIT_DESCRIBE MATCHES ".*-g.*")
            string(REGEX REPLACE "v?([0-9]*.[0-9.]*).*-([0-9]*)-([a-g0-9]*)" "\\1+\\2+\\3" GIT_FULL_VERSION ${GIT_DESCRIBE})
        else()
            set(GIT_FULL_VERSION ${GIT_VERSION})
        endif()
    else ()
        set(GIT_VERSION "0.0.0")
        execute_process(COMMAND ${GIT_CMD} rev-list --count HEAD
                WORKING_DIRECTORY ${GIT_TOPLEVEL}
                OUTPUT_VARIABLE GIT_COMMIT_COUNT
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(GIT_FULL_VERSION 0.0.0+${GIT_COMMIT_COUNT}+g${GIT_SHA1})
		set(TEXSTUDIO_GIT_REVISION ${GIT_FULL_VERSION})
    endif ()
endif ()

if (NOT PROJECT_VERSION)
    if (GIT_VERSION)
        set(PROJECT_VERSION ${GIT_VERSION})
        set(PACKAGE_VERSION ${GIT_FULL_VERSION})
    else ()
        message(WARNING "PROJECT_VERSION not set. Defaulting to 0.0.0")
        set(PROJECT_VERSION "0.0.0")
    endif ()
endif ()

if (GIT_VERSION AND NOT GIT_VERSION MATCHES ${PROJECT_VERSION})
    message(WARNING "Version from git (${GIT_VERSION}) doesn't match PROJECT_VERSION (${PROJECT_VERSION})")
endif()

version_split(${PROJECT_VERSION} PROJECT_VERSION_MAJOR PROJECT_VERSION_MINOR PROJECT_VERSION_PATCH extra)
math(EXPR PROJECT_VERSION_INT "${PROJECT_VERSION_MAJOR} * 10000 + ${PROJECT_VERSION_MINOR} * 100 + ${PROJECT_VERSION_PATCH}")

set(ADDITIONAL_DEFINITIONS -DPROJECT_VERSION="${PROJECT_VERSION}" -DPROJECT_VERSION_INT=${PROJECT_VERSION_INT})
if(TEXSTUDIO_GIT_REVISION)
	file(WRITE ${CMAKE_BINARY_DIR}/git_revision.cpp "const char * TEXSTUDIO_GIT_REVISION = \"${TEXSTUDIO_GIT_REVISION}\";")
else()
	file(WRITE ${CMAKE_BINARY_DIR}/git_revision.cpp "const char * TEXSTUDIO_GIT_REVISION = 0;")
endif()