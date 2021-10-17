#ifndef Header_Latex_StyleParser
#define Header_Latex_StyleParser
#include "mostQtHeaders.h"
#include "utilsSystem.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class LatexStyleParser : public SafeThread
{
	Q_OBJECT
#ifndef QT_NO_DEBUG
	friend class LatexStyleParserTest;
#endif

public:
	explicit LatexStyleParser(QObject *parent = 0, QString baseDirName = "", QString kpsecmd = "");
	void stop();
	void addFile(QString filename);
	void setAlias(QMultiHash<QString, QString> PackageAliases) { mPackageAliases = PackageAliases; }

protected:
	void run();

private:
	struct XpArg
	{
		bool optional;
		QChar delimLeft;
		QChar delimRight;
		QChar fixedChar;
	};
	typedef QList<XpArg> XpArgList;

	static QString makeArgString(int count, bool withOptional=false);
	QStringList parseLine(const QString &line, bool &inRequirePackage, QStringList &parsedPackages, const QString &fileName) const;
	static bool parseLineRequirePackage(QStringList &results, const QString &line, bool &inRequirePackage);
	static bool parseLineDef(QStringList &results, const QString &line);
	static bool parseLineLet(QStringList &results, const QString &line);
	static bool parseLineCommand(QStringList &results, const QString &line);
	static bool parseLineEnv(QStringList &results, const QString &line);
	bool parseLineInput(QStringList &results, const QString &line, QStringList &parsedPackages, const QString &fileName) const;
	static bool parseLineNewLength(QStringList &results, const QString &line);
	static bool parseLineNewCounter(QStringList &results, const QString &line);
	static bool parseLineDecMathSym(QStringList &results, const QString &line);
	static bool parseLineRequire(QStringList &results, const QString &line);
	static bool parseLineRequireStart(QStringList &results, const QString &line, bool &inRequirePackage);
	bool parseLineLoadClass(QStringList &results, const QString &line) const;
	static bool parseLineXparseCommand(QStringList &results, const QString &line);
	static bool parseLineXparseEnv(QStringList &results, const QString &line);
	static bool parseLineXparseArgs(XpArgList &xpArgs, const QString &line, int lineOffset);
	static bool parseLineGetGroup(QString &group, const QString &line, int groupStart);
	static bool parseLineXparseOneArg(XpArg &xpArg, const QString &argDef);
	static void parseLineXparseOutputCwl(QStringList &results, const QString &prefix, const XpArgList &xpArgs, int index);
	static void parseLineXparseOutputCwl(QStringList &results, const QString &prefix, XpArgList::const_iterator itPos, XpArgList::const_iterator itEnd, int argIndex);
	QStringList readPackage(QString fileName, QStringList &parsedPackages) const;
	QStringList readPackageTexDef(QString fn) const;
	QStringList readPackageTracing(QString fn) const;
	QString kpsewhich(QString name, QString dirName = "") const;

signals:
	void scanCompleted(QString package);

public slots:

private:
	QQueue<QString> mFiles;
	QSemaphore mFilesAvailable;
	QMutex mFilesLock;

	bool stopped;

	QString baseDir;
	QString kpseWhichCmd;
	QString texdefDir;

	bool texdefMode;

	QMultiHash<QString, QString> mPackageAliases;
};

#endif // LATEXSTYLEPARSER_H
