#ifndef KPATHSEAPARSER_H
#define KPATHSEAPARSER_H
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"

class PackageListReader : public SafeThread
{
	Q_OBJECT
public:
	explicit PackageListReader(QObject *parent=0) : SafeThread(parent) {}

protected:
	void run();
	virtual QStringList parseOutput(const QString &output);
	QString cmd;
	QStringList arguments;

signals:
	void scanCompleted(QStringList packages);
};


class KpathSeaParser : public PackageListReader
{
	Q_OBJECT
public:
	explicit KpathSeaParser(QObject *parent = 0,QString kpsecmd="");
protected:
	QStringList parseOutput(const QString &output);
};


class MiktexPackageListReader : public PackageListReader
{
	Q_OBJECT
public:
	explicit MiktexPackageListReader(QObject *parent = 0);
protected:
	QStringList parseOutput(const QString &output);
};




#endif // LATEXSTYLEPARSER_H
