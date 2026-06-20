#ifndef Header_Git
#define Header_Git

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

    struct FileEntry {
        QString statusCode; ///< two-character git status code (e.g. " M", "M ", "??", "A ")
        QString filePath;   ///< path relative to repository root
    };

    explicit GIT(QObject *parent = Q_NULLPTR);

	static QString quote(QString filename);
	static QString makeCmd(QString action, QString args);

    void commit(QString filename, QString message);
    void stageFiles(const QString &path, const QStringList &files);
    void commitStaged(const QString &path, const QString &message);
    void push(QString filename);
    void pull(QString path);
    void fetch(QString path);
    Status status(QString filename);
    QStringList log(QString filename);
    QStringList getRepoLog(const QString &path, int maxEntries = 100);
    void createRepository(QString filename);
    QList<FileEntry> getChangedFiles(QString path);
    QString getCurrentBranch(QString path);

    QString runGit(QString action, QString args);
    QString runGit(QString action, QString path,QString args);

signals:
    void runCommand(const QString &commandline, QString *output);
    void statusMessage(const QString &message);

};

#endif // GIT_H
