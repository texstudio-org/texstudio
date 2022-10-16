set(INC_DIRECTORIES
	${INC_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/synctex
	PARENT_SCOPE
)
set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/PDFDocument_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PDFDocument.h
)
if(POPPLER_FOUND)
    set(HEADER_FILES ${HEADER_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_parser_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_parser_advanced.h
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/PDFDocks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfrenderengine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfrendermanager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfannotationdlg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfannotation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/qsynctex.h
        PARENT_SCOPE
    )

    set(SOURCE_FILES ${SOURCE_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_parser.c
        ${CMAKE_CURRENT_SOURCE_DIR}/synctex/synctex_parser_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/PDFDocument.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PDFDocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfrenderengine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfrendermanager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfannotationdlg.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfannotation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qsynctex.cpp
        PARENT_SCOPE
    )

    set(FORM_FILES ${FORM_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/pdfannotationdlg.ui
        PARENT_SCOPE
    )
endif()
