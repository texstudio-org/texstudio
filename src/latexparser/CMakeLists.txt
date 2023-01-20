set(INC_DIRECTORIES
	${INC_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)

set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/argumentlist.h
    ${CMAKE_CURRENT_SOURCE_DIR}/latextokens.h
    ${CMAKE_CURRENT_SOURCE_DIR}/latexparser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/latexparsing.h
    ${CMAKE_CURRENT_SOURCE_DIR}/latexreader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/latex2text.h
    ${CMAKE_CURRENT_SOURCE_DIR}/commanddescription.h
	PARENT_SCOPE
)

set(SOURCE_FILES ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/argumentlist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/latextokens.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/latexparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/latexparsing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/latexreader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/latex2text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/commanddescription.cpp
    PARENT_SCOPE
)
