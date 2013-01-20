#ifndef LATEXPACKAGES_H
#define LATEXPACKAGES_H

#include "mostQtHeaders.h"

class LatexPackageInfo {
public:
	LatexPackageInfo(const QString &name=QString(), const QString &shortDescr=QString(), bool inst=false) {
		this->name = name;
		shortDescription = shortDescr;
		installed = inst;
	}

	QString name;
	QString shortDescription;
	bool installed;
};
Q_DECLARE_METATYPE(LatexPackageInfo);

class LatexPackages : public QObject
{
	Q_OBJECT
public:
	static LatexPackages *instance();

	enum DataSource { None, Static, Texlive, Miktex };

	DataSource dataSource();
	bool packageExists(const QString& name);
	QString shortDescription(const QString& name);

private:
	LatexPackages();
	LatexPackages(const LatexPackages &);
	LatexPackages& operator=(const LatexPackages &);
	static LatexPackages * m_Instance;

private slots:
	bool loadStaticPackageList(const QString& file);
	bool queryPackageList();
	void queryReadData();
	void queryReadError();
	void queryPackageListCompleted(int exitCode);
	void queryError(QProcess::ProcessError error);

private:
	QHash<QString, LatexPackageInfo> packages; // name, short description
	DataSource m_dataSource;
	QString m_queryData;
};

#endif // LATEXPACKAGES_H
