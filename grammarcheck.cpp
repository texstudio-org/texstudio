#include "grammarcheck.h"
#include "smallUsefulFunctions.h"

GrammarError::GrammarError(){}
GrammarError::GrammarError(int offset, int length, const GrammarErrorType& error):offset(offset),length(length), error(error){}


GrammarCheck::GrammarCheck(QObject *parent) :
    QObject(parent)
{
	latexParser = new LatexParser();
}

GrammarCheck::~GrammarCheck(){
	if (latexParser) delete latexParser;
}

void GrammarCheck::init(LatexParser lp){
	*latexParser = lp;
}

void GrammarCheck::check(const void * doc, QList<LineInfo> lines, int firstLineNr, int linesToSkipDelta){
	const int MAX_REP_DELTA = 3;
	
	REQUIRE(latexParser);
	QHash<QString, int> repeatedWordCheck;
	int totalWords = 0;
	for (int l = 0; l < lines.size(); l++, firstLineNr++) {
		//gather words
		LatexReader lr(*latexParser, lines[l].text);
		int type;
		QStringList words;
		QList<int> indices, lengths;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) continue;
			if (type == LatexReader::NW_TEXT) words << lr.word;
			else if (type == LatexReader::NW_PUNCTATION) words << lr.word;
			else break;
			indices << lr.wordStartIndex;
			lengths << lr.index - lr.wordStartIndex;
		}

		//check words
		bool realCheck = l >= linesToSkipDelta;

		QList<GrammarError> errors;
		
		for (int i=0;i<words.length();i++) {
			if (words[i].length() == 1 && getCommonEOW().contains(words[i][0])) continue; //punctation
			totalWords++;
			QString normalized = words[i].toLower();
			if (realCheck) {
				int lastSeen = repeatedWordCheck.value(normalized, -1);
				if (lastSeen > -1 && totalWords - lastSeen <= MAX_REP_DELTA) 
					errors << GrammarError(indices[i], lengths[i], GET_WORD_REPETITION);
			}
			repeatedWordCheck.insert(normalized, totalWords);
		}
		if (!realCheck) continue;
			
		emit checked(doc, lines[l].line, lines[l].lineNr, errors);

//		qDebug() << words.join(" ");
	}
}
