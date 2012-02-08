#ifndef GRAMMARCHECK_H
#define GRAMMARCHECK_H

#include <QObject>
#include <QVariant>
class LatexParser;

struct LineInfo{
	const void* doc;
	const void* line;
	QString text;
};

enum GrammarErrorType { GET_UNKNOWN, GET_WORD_REPETITION };

struct GrammarError{
	int offset;
	int length;
	GrammarErrorType error;
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

class GrammarCheck : public QObject
{
    Q_OBJECT
public:
	explicit GrammarCheck(QObject *parent = 0);
	~GrammarCheck();
signals:
	void checked(const void* doc, const void* line, int lineNr, QList<GrammarError> errors);
public slots:
	void init();
	void check(QList<LineInfo> lines, int firstLineNr, int linesToSkipDelta);
private:
	LatexParser* latexParser;
};

#endif // GRAMMARCHECK_H
