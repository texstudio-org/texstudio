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
struct CheckRequest;
typedef QHash<const void *, QPair<uint, int> > TicketHash;
class GrammarCheck : public QObject
{
    Q_OBJECT
public:
	explicit GrammarCheck(QObject *parent = 0);
	~GrammarCheck();
signals:
	void checked(const void* doc, const void* line, int lineNr, QList<GrammarError> errors);
public slots:
	void init(const LatexParser& lp, const GrammarCheckerConfig& config);
	void check(const QString& language, const void* doc, const QList<LineInfo>& lines, int firstLineNr, int linesToSkipDelta);
private slots:
	void process();
	void backendChecked(uint ticket, const QList<GrammarError>& errors, bool directCall = false);	
private:
	LatexParser* latexParser;
	GrammarCheckerConfig config;
	GrammarCheckBackend* backend;
	QMap<QString, LanguageGrammarData> languages;

	uint ticket;
	TicketHash tickets;
	QList<CheckRequest> requests;
};

class GrammarCheckBackend : public QObject{
	Q_OBJECT
public:
	GrammarCheckBackend(QObject* parent);
	virtual void init(const GrammarCheckerConfig& config) = 0;
	virtual bool isAvailable() = 0;
	virtual void check(uint ticket, const QString& language, const QString& text) = 0;
signals:
	void checked(uint ticket, const QList<GrammarError>& errors);	
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
	virtual void check(uint ticket, const QString& language, const QString& text);
private slots:
	void finished(QNetworkReply* reply);
private:
	QNetworkAccessManager *nam;
	QUrl server;
	
	int connectionAvailability; //-1: broken, 0: don't know, 1: worked at least once
	bool triedToStart;
	
	QString ltPath, javaPath;
	QSet<QString> ignoredRules;
	uint startTime;
	void tryToStart();
	
};

#endif // GRAMMARCHECK_H
