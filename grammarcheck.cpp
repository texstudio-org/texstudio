#include "grammarcheck.h"
#include "smallUsefulFunctions.h"
GrammarCheck::GrammarCheck(QObject *parent) :
    QObject(parent)
{
}

GrammarCheck::~GrammarCheck(){
	if (latexParser) delete latexParser;
}

void GrammarCheck::init(){
	latexParser = new LatexParser();
}

void GrammarCheck::check(QList<LineInfo> lines, int firstLineNr, int linesToSkipDelta){
	REQUIRE(latexParser);
	for (int l = linesToSkipDelta; l < lines.size(); l++, firstLineNr++) {
		//while (latexParser->nextToken())
	}
}
