#ifndef Header_SyntaxCheck
#define Header_SyntaxCheck

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexparser.h"
#include "qdocumentline_p.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class SpellerUtility;
/*!
 * \brief store information on open environments
 */
class Environment
{
public:
    Environment(): id(-1), excessCol(0), dlh(nullptr),endingColumn(-1) , ticket(0), level(0) {} ///< constructor

	QString name; ///< name of environment, partially an alias is used, e.g. math instead of '$'
    QString origName; ///< original name of environment if alias is used, otherwise empty
	int id; ///< mostly unused, contains the number of columns for tabular-environments
	int excessCol; ///< number of unused tabular-columns if columns are strechted over several text lines
	QDocumentLineHandle *dlh; ///< linehandle of starting line
    int startingColumn;
    int endingColumn;
	int ticket;
    int level; ///< command level (see tokens) in order to handle nested commands like \shortstack

	bool operator ==(const Environment &env) const
	{
        return (name == env.name) && (id == env.id) && (excessCol == env.excessCol) && (origName == env.origName) && (level == env.level);
	}
	bool operator !=(const Environment &env) const
	{
        return (name != env.name) || (id != env.id) || (excessCol != env.excessCol) || (origName != env.origName) || (level != env.level);
	}
};

typedef QStack<Environment> StackEnvironment;

Q_DECLARE_METATYPE(StackEnvironment)

class SyntaxCheck : public SafeThread
{
	Q_OBJECT

public:
    /*!
     * \brief type of error
     */
	enum ErrorType {
		ERR_none, ///< no error
		ERR_unrecognizedEnvironment, ///< environment unknown
		ERR_unrecognizedCommand, ///< command unknown
		ERR_unrecognizedMathCommand, ///< unknown command for math environment
		ERR_unrecognizedTabularCommand, ///< unknown command for tabular environment
		ERR_TabularCommandOutsideTab, ///< tabular command outside tabular (e.g. \hline)
		ERR_MathCommandOutsideMath, ///< math command outside of math env
		ERR_TabbingCommandOutside, ///< tabbing command outside of tabbing env
		ERR_tooManyCols, ///< tabular has more columns in line than in definition
		ERR_tooLittleCols, ///< tabular has fewer columns in line than in definition
		ERR_missingEndOfLine, ///< unused
		ERR_closingUnopendEnv, ///< end{env} without corrresponding begin{env}
		ERR_EnvNotClosed, ///< end{env} missing
		ERR_unrecognizedKey, ///< in key/value argument, an unknown key is used
		ERR_unrecognizedKeyValues, ///< in key/value argument, an unknown value is used for a key
		ERR_commandOutsideEnv, ///< command used outside of designated environment (similar math command outside math)
        ERR_spelling, ///< syntax error of text word (spell checker)
        ERR_highlight, ///< arbitraty format for highlighting (math,verbatim,picture)
		ERR_MAX  // always last
	};
    /*!
     * \brief info which is queued for syntaxchecking
     */
	struct SyntaxLine {
		StackEnvironment prevEnv; ///< environmentstack at start of line
		TokenStack stack; ///< tokenstack at start of line (open arguments)
		int ticket; ///< ticket number
		bool clearOverlay; ///< clear syntax overlay, sometimes not necessary as it was done somewhere else
		QDocumentLineHandle *dlh; ///< linehandle
        int hint; ///< hint on lineNumber for faster look-up
        bool initialRun;
	};

    /*!
     * \brief structure to describe an syntax error
     */
	struct Error {
		QPair<int, int> range; ///<  start,stop of error marker
		ErrorType type; ///< type of error
        int format; ///< arbitrary format to used instead of error marker
	};

	typedef QList<Error > Ranges;

    explicit SyntaxCheck(QObject *parent = nullptr);

    void putLine(QDocumentLineHandle *dlh, StackEnvironment previous, TokenStack stack, bool clearOverlay = false,int hint=-1);
	void stop();
	void setErrFormat(int errFormat);
    QString getErrorAt(QDocumentLineHandle *dlh, int pos, StackEnvironment previous, TokenStack stack);
#ifndef NO_TESTS
	void waitForQueueProcess(void);
#endif
	static int containsEnv(const LatexParser &parser, const QString &name, const StackEnvironment &envs, const int id = -1);
    static bool checkMathEnvActive(const LatexParser &parser, const StackEnvironment &envs);
	int topEnv(const QString &name, const StackEnvironment &envs, const int id = -1);
	bool checkCommand(const QString &cmd, const StackEnvironment &envs);
	static bool equalEnvStack(StackEnvironment env1, StackEnvironment env2);

	void setLtxCommands(const LatexParser &cmds);
    void setSpeller(SpellerUtility *su);
    void setReplacementList(QMap<QString, QString> replacementList);
    void setFormats(QMap<QString, int> formatList);
    void enableSyntaxCheck(const bool enable);

	void markUnclosedEnv(Environment env);

signals:
    void checkNextLine(QDocumentLineHandle *dlh, bool clearOverlay, int ticket, int hint); ///< enqueue next line for syntax checking as context has changed

protected:
	void run();
    void checkLine(const QString &line, Ranges &newRanges, StackEnvironment &activeEnv, QDocumentLineHandle *dlh, TokenList &tl, TokenStack stack, int ticket, int commentStart=-1);

private:
	QQueue<SyntaxLine> mLines;
	QSemaphore mLinesAvailable;
	QMutex mLinesLock;
	QAtomicInt mLinesEnqueuedCounter; //!< Total number of lines enqueued from beginning. Never decremented.
	bool stopped;
    bool mSyntaxChecking; //! show/hide syntax errors
    int syntaxErrorFormat;
	LatexParser *ltxCommands;

	LatexParser newLtxCommands;
	bool newLtxCommandsAvailable;
	QMutex mLtxCommandLock;
	bool stackContainsDefinition(const TokenStack &stack) const;

    SpellerUtility *speller,*newSpeller;

    QMap<QString,QString> newReplacementList,mReplacementList;
    QMap<QString,int> newFormatList,mFormatList;

};

#endif // SYNTAXCHECK_H
