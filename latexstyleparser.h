#ifndef LATEXSTYLEPARSER_H
#define LATEXSTYLEPARSER_H
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

	QString makeArgString(int count, bool withOptional=false) const;
	QStringList parseLine(const QString &line, bool &inRequirePackage, QStringList &parsedPackages, const QString &fileName) const;
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
