#ifndef GRAMMARCHECK_H
#define GRAMMARCHECK_H

#include <QObject>
#include <QVariant>

#include "smallUsefulFunctions.h"

struct LineInfo{
	const void* line;
	int lineNr;
	QString text;
};

enum GrammarErrorType { GET_UNKNOWN, GET_WORD_REPETITION };

struct GrammarError{
	int offset;
	int length;
	GrammarErrorType error;
	GrammarError();
	GrammarError(int offset, int length, const GrammarErrorType& error);
};

struct LineResult{
	const void* doc;
	const void* line;
	int lineNr;
	QList<GrammarError> errors;
};

Q_DECLARE_METATYPE(LineInfo)
Q_DECLARE_METATYPE(GrammarError)
Q_DECLARE_METATYPE(GrammarErrorType)
Q_DECLARE_METATYPE(QList<LineInfo>)
Q_DECLARE_METATYPE(QList<GrammarError>)

class GrammarCheck : public QObject
{
    Q_OBJECT
public:
	explicit GrammarCheck(QObject *parent = 0);
	~GrammarCheck();
signals:
	void checked(const void* doc, const void* line, int lineNr, QList<GrammarError> errors);
public slots:
	void init(LatexParser lp);
	void check(const void* doc, QList<LineInfo> lines, int firstLineNr, int linesToSkipDelta);
private:
	LatexParser* latexParser;
};

#endif // GRAMMARCHECK_H
