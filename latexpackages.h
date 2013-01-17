#ifndef LATEXPACKAGES_H
#define LATEXPACKAGES_H

#include "mostQtHeaders.h"

class LatexPackages : public QObject
{
	Q_OBJECT
public:
	static LatexPackages *instance();

	bool packageExists(const QString& name);
	QString shortDescription(const QString& name);

private:
	LatexPackages();
	LatexPackages(const LatexPackages &);
	LatexPackages& operator=(const LatexPackages &);

	bool loadPackageList(const QString& file);

	static LatexPackages * m_Instance;

	QHash<QString, QString> packages; // name, short description
};

#endif // LATEXPACKAGES_H
