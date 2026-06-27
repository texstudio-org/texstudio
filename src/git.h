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

    struct GraphEntry {
        QString hash;        ///< full commit hash
        QStringList parents; ///< parent hashes (full), empty for root commits
        QStringList refs;    ///< decoration strings, e.g. "HEAD -> main", "origin/main", "tag: v1.0"
        QString subject;     ///< first line of the commit message
    };

    explicit GIT(QObject *parent = Q_NULLPTR);

	static QString quote(QString filename);
	static QString makeCmd(QString action, QString args);

    void commit(QString filename, QString message);
    QString stageFiles(const QString &path, const QStringList &files);
    QString commitStaged(const QString &path, const QString &message);
    void push(QString filename,QString optionalArgs="");
    void pull(QString path);
    void fetch(QString path);
    Status status(QString filename);
    QStringList log(QString filename);
    QStringList getRepoLog(const QString &path, int maxEntries = 100);
    QList<GraphEntry> getRepoLogGraph(const QString &path, int maxEntries = 200, const QString &fileFilter = QString());
    QString getCommitStat(const QString &path, const QString &hash);
    QString getCommitFileNames(const QString &path, const QString &hash);
    void createRepository(QString filename);
    QList<FileEntry> getChangedFiles(QString path);
    QString getCurrentBranch(QString path);
    void unstageFiles(QString repoRoot, QStringList files);
    void checkoutFile(QString repoRoot, QString relPath,QString rev="HEAD");
    void checkout(QString repoRoot, QString arg);
    QStringList getBranches(QString repoRoot);

    QString runGit(QString action, QString args);
    QString runGit(QString action, QString path,QString args);

signals:
    void runCommand(const QString &commandline, QString *output);
    void statusMessage(const QString &message);

};

#endif // GIT_H
