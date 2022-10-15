set(INC_DIRECTORIES
	${INC_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)

set(HUNSPELL_HEADER_FILES
    affentry.hxx
    affixmgr.hxx
    atypes.hxx
    baseaffix.hxx
    csutil.hxx
    filemgr.hxx
    hashmgr.hxx
    htypes.hxx
    hunspell.hxx
    hunspell.h
    hunvisapi.h
    hunzip.hxx
    langnum.hxx
    phonet.hxx
    replist.hxx
    suggestmgr.hxx
    utf_info.hxx
    w_char.hxx
)

set(HUNSPELL_SOURCE_FILES
    affentry.cxx
    affixmgr.cxx
    csutil.cxx
    filemgr.cxx
    hashmgr.cxx
    hunspell.cxx
    hunzip.cxx
    phonet.cxx
    replist.cxx
    suggestmgr.cxx
)

add_library(hunspell STATIC ${HUNSPELL_HEADER_FILES} ${HUNSPELL_SOURCE_FILES})
target_compile_definitions(hunspell PUBLIC -DHUNSPELL_STATIC)
