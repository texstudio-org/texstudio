#ifndef GRAMMARCHECK_H
#define GRAMMARCHECK_H

#include "mostQtHeaders.h"

#include "latexparser/latexparser.h"
//TODO: move this away
#include "grammarcheck_config.h"


struct LineInfo {
	const void *line;
	QString text;
};

enum GrammarErrorType { GET_UNKNOWN = 0, GET_WORD_REPETITION, GET_LONG_RANGE_WORD_REPETITION, GET_BAD_WORD, GET_BACKEND, GET_BACKEND_SPECIAL1, GET_BACKEND_SPECIAL2, GET_BACKEND_SPECIAL3, GET_BACKEND_SPECIAL4};

struct GrammarError {
	int offset;
	int length;
	GrammarErrorType error;
	QString message;
	QStringList corrections;
	GrammarError();
	GrammarError(int offset, int length, const GrammarErrorType &error, const QString &message);
	GrammarError(int offset, int length, const GrammarErrorType &error, const QString &message, const QStringList &corrections);
	GrammarError(int offset, int length, const GrammarError &other);
};

struct LineResult {
	const void *doc;
	const void *line;
	int lineNr;
	QList<GrammarError> errors;
};

Q_DECLARE_METATYPE(LineInfo)
Q_DECLARE_METATYPE(GrammarError)
Q_DECLARE_METATYPE(GrammarErrorType)
Q_DECLARE_METATYPE(QList<LineInfo>)
Q_DECLARE_METATYPE(QList<GrammarError>)

struct LanguageGrammarData {
	QSet<QString> stopWords;
	QSet<QString> badWords;
};

class GrammarCheckBackend;

struct CheckRequest;

typedef QHash<const void *, QPair<uint, int> > TicketHash;

class GrammarCheck : public QObject
{
	Q_OBJECT

public:
    explicit GrammarCheck(QObject *parent = nullptr);
	~GrammarCheck();
	enum LTStatus {LTS_Unknown, LTS_Working, LTS_Error};
	LTStatus languageToolStatus() { return ltstatus; }
	QString serverUrl();
    QString getLastErrorMessage();

signals:
	void checked(const void *doc, const void *line, int lineNr, QList<GrammarError> errors);
	void languageToolStatusChanged();
    void errorMessage(QString message);
public slots:
	void init(const LatexParser &lp, const GrammarCheckerConfig &config);
	void check(const QString &language, const void *doc, const QList<LineInfo> &lines, int firstLineNr);
	void shutdown();
private slots:
	void processLoop();
	void process(int reqId);
	void backendChecked(uint ticket, int subticket, const QList<GrammarError> &errors, bool directCall = false);
    void updateLTStatus();
private:
	QString languageFromHunspellToLanguageTool(QString language);
	QString languageFromLanguageToolToHunspell(QString language);
	LTStatus ltstatus;
	LatexParser *latexParser;
	GrammarCheckerConfig config;
	GrammarCheckBackend *backend;
	QMap<QString, LanguageGrammarData> languages;

	uint ticket;
	bool pendingProcessing;
	bool shuttingDown;
	TicketHash tickets;
	QList<CheckRequest> requests;
	QSet<QString> floatingEnvs;
	QHash<QString, QString> languageMapping;
};

struct CheckRequestBackend;

class GrammarCheckBackend : public QObject
{
	Q_OBJECT
public:
	GrammarCheckBackend(QObject *parent);
	virtual void init(const GrammarCheckerConfig &config) = 0;
	virtual bool isAvailable() = 0;
    virtual bool isWorking() = 0;
	virtual QString url() = 0;
    virtual void check(uint ticket, uint subticket, const QString &language, const QString &text) = 0;
	virtual void shutdown() = 0;
    virtual QString getLastErrorMessage() = 0;
signals:
	void checked(uint ticket, int subticket, const QList<GrammarError> &errors);
    void languageToolStatusChanged();
    void errorMessage(QString message);
};

class QNetworkAccessManager;
class QNetworkReply;


class GrammarCheckLanguageToolJSON: public GrammarCheckBackend
{
    Q_OBJECT

public:
    GrammarCheckLanguageToolJSON(QObject *parent = nullptr);
    ~GrammarCheckLanguageToolJSON();
    virtual void init(const GrammarCheckerConfig &config);
    virtual bool isAvailable();
    virtual bool isWorking();
    virtual QString url();
    virtual void check(uint ticket, uint subticket, const QString &language, const QString &text);
    virtual void shutdown();
    virtual QString getLastErrorMessage();
private slots:
    void finished(QNetworkReply *reply);
private:
    QNetworkAccessManager *nam;
    QUrl server;

    enum Availability {Terminated = -2, Broken = -1, Unknown = 0, WorkedAtLeastOnce = 1};
    Availability connectionAvailability;

    bool triedToStart;
    bool firstRequest;
    QPointer<QProcess> javaProcess;

    QString ltPath, javaPath, ltArguments;
    QSet<QString> ignoredRules;
    QList<QSet<QString> >  specialRules;
    uint startTime;
    void tryToStart();

    QList<CheckRequestBackend> delayedRequests;

    QSet<QString> languagesCodesFail;
    QString errorText; // last error message
};

#endif // GRAMMARCHECK_H
