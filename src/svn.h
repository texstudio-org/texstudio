#ifndef SVN_H
#define SVN_H

#include "mostQtHeaders.h"
/*!
 * \brief SVN class
 * This class provides easy access to the svn command.
 */
class SVN : public QObject
{
	Q_OBJECT

public:
	enum Status {Unknown, Unmanaged, Modified, Locked, CheckedIn, InConflict};

	explicit SVN(QObject *parent = Q_NULLPTR);

	static QString quote(QString filename);
	static QString makeCmd(QString action, QString args);
	static QString makeAdminCmd(QString action, QString args);

	void commit(QString filename, QString message) const;
	void lock(QString filename) const;
	Status status(QString filename) const;
	QStringList log(QString filename) const;
	void createRepository(QString filename) const;

	QString runSvn(QString action, QString args) const;
	QString runSvnAdmin(QString action, QString args) const;

signals:
	void runCommand(const QString &commandline, QString *output) const;
	void statusMessage(const QString &message) const;

};

#endif // SVN_H
