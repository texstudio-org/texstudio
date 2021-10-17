#ifndef Header_SVN
#define Header_SVN

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

    void commit(QString filename, QString message);
    void lock(QString filename);
    Status status(QString filename);
    QStringList log(QString filename);
    void createRepository(QString filename);

    QString runSvn(QString action, QString args);
    QString runSvnAdmin(QString action, QString args);

signals:
    void runCommand(const QString &commandline, QString *output);
    void statusMessage(const QString &message);

};

#endif // SVN_H
