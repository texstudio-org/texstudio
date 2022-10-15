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
    dictmgr.hxx
    hashmgr.hxx
    htypes.hxx
    hunspell.hxx
    hunspell.h
    langnum.hxx
    license.hunspell
    phonet.hxx
    suggestmgr.hxx
    license.myspell
    filemgr.hxx
    hunzip.hxx
    w_char.hxx
    replist.hxx
)

set(HUNSPELL_SOURCE_FILES
    affentry.cxx
    affixmgr.cxx
    csutil.cxx
    dictmgr.cxx
    hashmgr.cxx
    hunspell.cxx
    phonet.cxx
    replist.cxx
    suggestmgr.cxx
    #utf_info.cxx
    filemgr.cxx
    hunzip.cxx
)

add_library(hunspell STATIC ${HUNSPELL_HEADER_FILES} ${HUNSPELL_SOURCE_FILES})
target_compile_definitions(hunspell PUBLIC -DHUNSPELL_STATIC)
