#ifndef Header_Latex_Repository
#define Header_Latex_Repository

#include "mostQtHeaders.h"
enum TeXdocStatus { Undefined, Available, Unavailable };

class LatexPackageInfo
{
public:
	LatexPackageInfo(const QString &name = QString(), const QString &shortDescr = QString(), bool inst = false, TeXdocStatus status = Undefined, const QString &message = QString(""))
	{
		this->name = name;
		shortDescription = shortDescr;
		installed = inst;
		docStatus = status;
		docMessage = message;
	}

	QString name;
	QString shortDescription;
	bool installed;
	TeXdocStatus docStatus;
	QString docMessage;
};
Q_DECLARE_METATYPE(LatexPackageInfo)

class LatexRepository : public QObject
{
	Q_OBJECT

public:
	static LatexRepository *instance();

	enum DataSource { None, Static, Texlive, Miktex };

	DataSource dataSource();
	bool packageExists(const QString &name);
	QString shortDescription(const QString &name);
	TeXdocStatus docStatus(const QString &name);
	QString docMessage(const QString &name);
	void updatePackageInfo(const QString &name, const TeXdocStatus &docStatus, const QString &docMessage);
	QStringList availablePackages();

private:
	LatexRepository();
	LatexRepository(const LatexRepository &);
	LatexRepository &operator=(const LatexRepository &);

	bool loadStaticPackageList(const QString &file);

	static LatexRepository *m_Instance;

	QHash<QString, LatexPackageInfo> packages; // name, short description
	DataSource m_dataSource;
};

#endif // LATEXREPOSITORY_H
