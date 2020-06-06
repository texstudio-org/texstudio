#ifndef GIT_H
#define GIT_H

#include "mostQtHeaders.h"
/*!
 * \brief GIT class
 * This class provides easy access to the git command.
 */
class GIT : public QObject
{
	Q_OBJECT

public:
    enum Status {Unknown, Unmanaged, Modified, Locked, CheckedIn, InConflict, NoRepository};

    explicit GIT(QObject *parent = Q_NULLPTR);

	static QString quote(QString filename);
	static QString makeCmd(QString action, QString args);

	void commit(QString filename, QString message) const;
	Status status(QString filename) const;
	QStringList log(QString filename) const;
	void createRepository(QString filename) const;

    QString runGit(QString action, QString args) const;

signals:
	void runCommand(const QString &commandline, QString *output) const;
	void statusMessage(const QString &message) const;

};

#endif // GIT_H
