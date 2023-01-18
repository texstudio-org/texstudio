#ifndef LATEXTOTEXT_H
#define LATEXTOTEXT_H
#include "mostQtHeaders.h"
#include "latexparser.h"

struct LineInfo {
	QDocumentLineHandle* line;
	QString text;
	LineInfo(): line(nullptr){};
	LineInfo(QDocumentLineHandle* line);
};

struct TokenizedBlock {
	QStringList words;
	QList<int> indices, endindices, lines;
	QString toString() const;
	struct StringOffsetIterator{
		const TokenizedBlock& tb;
		int curOffset;
		int curWord;
		QList<LineInfo> inlines;
		StringOffsetIterator(const TokenizedBlock& tb, const QList<LineInfo>& inlines): tb(tb), curOffset(0), curWord(0), inlines(inlines) {
		}
		//converts a position in the string returned by toString() to a position in the original inlines/document
		bool map(int offset, int length, int * lineIndex, int * trueoffset, int* truelength);
	};
};

QList<TokenizedBlock> tokenizeWords(LatexParser *latexParser, const QList<LineInfo>& inlines);


Q_DECLARE_METATYPE(LineInfo)
Q_DECLARE_METATYPE(QList<LineInfo>)

#endif // LATEXTOTEXT_H
