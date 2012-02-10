#ifndef GRAMMARCHECK_H
#define GRAMMARCHECK_H

#include "mostQtHeaders.h"

#include <QObject>
#include <QVariant>

#include "smallUsefulFunctions.h"

#include "grammarcheck_config.h"

struct LineInfo{
	const void* line;
	int lineNr;
	QString text;
};

enum GrammarErrorType { GET_UNKNOWN, GET_WORD_REPETITION, GET_BACKEND};

struct GrammarError{
	int offset;
	int length;
	GrammarErrorType error;
	QString message;
	QStringList corrections;
	GrammarError();
	GrammarError(int offset, int length, const GrammarErrorType& error, const QString& message);
	GrammarError(int offset, int length, const GrammarErrorType& error, const QString& message, const QStringList& corrections);
	GrammarError(int offset, int length, const GrammarError& other);
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

struct LanguageGrammarData{
	QSet<QString> stopWords;
};

class GrammarCheckBackend;
class GrammarCheck : public QObject
{
    Q_OBJECT
public:
	explicit GrammarCheck(QObject *parent = 0);
	~GrammarCheck();
signals:
	void checked(const void* doc, const void* line, int lineNr, QList<GrammarError> errors);
public slots:
	void init(LatexParser lp, GrammarCheckerConfig config);
	void check(const QString& language, const void* doc, QList<LineInfo> lines, int firstLineNr, int linesToSkipDelta);
private:
	LatexParser* latexParser;
	GrammarCheckerConfig config;
	GrammarCheckBackend* backend;
	uint ticket;
	QHash<const void *, uint> tickets;
	QMap<QString, LanguageGrammarData> languages;
};

class GrammarCheckBackend : public QObject{
	Q_OBJECT
public:
	GrammarCheckBackend(QObject* parent);
	virtual void init(const GrammarCheckerConfig& config) = 0;
	virtual bool isAvailable() = 0;
	virtual QList<GrammarError> check(const QString& language, const QString& text) = 0;
};

class QNetworkAccessManager;
class QNetworkReply;
class GrammarCheckLanguageToolSOAP: public GrammarCheckBackend{
	Q_OBJECT
public:
	GrammarCheckLanguageToolSOAP(QObject* parent = 0);
	~GrammarCheckLanguageToolSOAP();
	virtual void init(const GrammarCheckerConfig& config);
	virtual bool isAvailable();
	virtual QList<GrammarError> check(const QString& language, const QString& text);
public slots:
	void finished(QNetworkReply* reply);
private:
	QMap<int, int> replied;
	QMap<int, QByteArray> reply;
	int ticket;
	QNetworkAccessManager *nam;
	QUrl server;
	
	int connectionAvailability; //-1: broken, 0: don't know, 1: worked at least once
};

#endif // GRAMMARCHECK_H
