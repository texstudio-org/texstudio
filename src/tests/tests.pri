!isEmpty(NO_TESTS) {
	message("tests are disabled")
	DEFINES += NO_TESTS
} else {
	message("tests are enabled")
	QT += testlib
	SOURCES += \
		src/tests/codesnippet_t.cpp \
		src/tests/encoding_t.cpp \
		src/tests/execprogram_t.cpp \
		src/tests/latexcompleter_t.cpp \
		src/tests/latexeditorview_bm.cpp \
		src/tests/latexeditorview_t.cpp \
		src/tests/latexoutputfilter_t.cpp \
		src/tests/latexparser_t.cpp \
		src/tests/latexparsing_t.cpp \
		src/tests/qcetestutil.cpp \
		src/tests/qdocumentcursor_t.cpp \
		src/tests/qdocumentline_t.cpp \
		src/tests/qdocumentsearch_t.cpp \
		src/tests/qeditor_t.cpp \
		src/tests/qsearchreplacepanel_t.cpp \
		src/tests/scriptengine_t.cpp \
		src/tests/smallUsefulFunctions_t.cpp \
		src/tests/structureview_t.cpp \
		src/tests/syntaxcheck_t.cpp \
		src/tests/tablemanipulation_t.cpp \
		src/tests/usermacro_t.cpp \
		src/tests/testmanager.cpp \
                src/tests/git_t.cpp \
                src/tests/testutil.cpp \
                src/tests/latexdocument_t.cpp
	HEADERS += \
		src/tests/execprogram_t.h \
		src/tests/qsearchreplacepanel_t.h \
		src/tests/updatechecker_t.h \
		src/tests/qdocumentcursor_t.h \
		src/tests/qdocumentline_t.h \
		src/tests/qdocumentsearch_t.h \
		src/tests/codesnippet_t.h \
		src/tests/latexcompleter_t.h \
		src/tests/latexeditorview_bm.h \
		src/tests/latexeditorview_t.h \
		src/tests/latexoutputfilter_t.h \
		src/tests/latexparser_t.h \
		src/tests/latexparsing_t.h \
		src/tests/latexstyleparser_t.h \
		src/tests/scriptengine_t.h \
		src/tests/qeditor_t.h \
		src/tests/buildmanager_t.h \
		src/tests/tablemanipulation_t.h \
		src/tests/smallUsefulFunctions_t.h \
		src/tests/utilsui_t.h \
		src/tests/utilsversion_t.h \
		src/tests/encoding_t.h \
		src/tests/help_t.h \
		src/tests/syntaxcheck_t.h \
		src/tests/qcetestutil.h \
		src/tests/testmanager.h \
		src/tests/testutil.h \
		src/tests/usermacro_t.h \
                src/tests/git_t.h \
                src/tests/structureview_t.h \
                src/tests/latexdocument_t.h
}

SOURCES += \
    $$PWD/latexstyleparser_t.cpp


