#include "git.h"
#include "smallUsefulFunctions.h"
#include "buildmanager.h"

GIT::GIT(QObject *parent) : QObject(parent)
{
}

/*!
 * Return a filename suitable to pass to an GIT command line call. This does:
 *   1. enquote the filename in double qoutes.
 *   2. add '@' at the end if the filename contains an @. This prevents the interpretation
 *      of the contained @ as revision marker. See https://stackoverflow.com/a/757510/2726279
 */
QString GIT::quote(QString filename) {
	if (filename.contains('@')) {
		filename += '@';
	}
	return quotePath(filename);
}
/*!
 * \brief generate string which contains command "GIT action args"
 * \param action
 * \param args
 * \return
 */
QString GIT::makeCmd(QString action, QString args)
{
    return BuildManager::CMD_GIT + " " + action + " " + args;
}

/*!
 * \brief GIT commit filename
 * \param filename
 * \param message commit message
 */
void GIT::commit(QString filename, QString message)
{
    runGit("add", quote(filename));
    runGit("commit", "-m " + enquoteStr(message) + " " + quote(filename));
}

/*!
 * \brief Stage a list of files in the given repository in a single git call.
 * \param path repository root directory
 * \param files list of relative file paths to stage
 * \return git output (may contain error/fatal on failure)
 */
QString GIT::stageFiles(const QString &path, const QStringList &files)
{
    if (files.isEmpty()) return QString();
    QStringList quotedFiles;
    quotedFiles.reserve(files.size());
    for (const QString &file : files)
        quotedFiles << quote(file);
    return runGit("add", quote(path), quotedFiles.join(' '));
}

/*!
 * \brief Commit all currently staged changes in the repository.
 * \param path repository root directory
 * \param message commit message
 * \return git output (may contain error/fatal on failure)
 */
QString GIT::commitStaged(const QString &path, const QString &message)
{
    return runGit("commit", quote(path), "-m " + enquoteStr(message));
}
/*!
 * \brief GIT push
 * \param filename
 */
void GIT::push(QString filename)
{
    runGit("push", quote(filename),"");
}

/*!
 * \brief get GIT status filename
 * \param filename
 * \return
 */
GIT::Status GIT::status(QString filename)
{
    QString output = runGit("status -s", quote(filename));
    output=output.trimmed(); // git delivers a leading space sometimes (?)
    if (output.isEmpty()) return GIT::CheckedIn;
    if (output.startsWith("?")) return GIT::Unmanaged;
    if (output.startsWith("fatal")) return GIT::NoRepository;
    if (output.startsWith("M")) return GIT::Modified;
    if (output.startsWith("C")) return GIT::InConflict;
    if (output.startsWith("L")) return GIT::Locked;
    return GIT::Unknown;
}
/*!
 * \brief get GIT log
 * \param filename
 * \return
 */
QStringList GIT::log(QString filename)
{
    const QString path = QFileInfo(filename).absolutePath();
    QString fn = QFileInfo(filename).fileName();
    QString output = runGit("log --pretty='%h %s@@@'", quote(path),quote(fn));
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
    QStringList revisions = output.split("@@@", Qt::SkipEmptyParts);
#else
    QStringList revisions = output.split("@@@", QString::SkipEmptyParts);
#endif
    // circumvent strange behaviour of git adding \n  now and then ...
    for(QString& elem:revisions){
        elem=elem.simplified();
    }
    if(!revisions.isEmpty() && revisions.last().isEmpty()){
        revisions.takeLast();
    }
    return revisions;
}
/*!
 * \brief create a GIT repository
 * \param filename
 */
void GIT::createRepository(QString filename)
{
    const QString path = QFileInfo(filename).absolutePath();
    //setStatusMessageProcess(QString(" GIT create repo "));
    runGit("init", quote(path));
}
/*!
 * \brief run GIT command
 * \param action
 * \param args
 * \return
 */
QString GIT::runGit(QString action, QString args)
{
	QString output;
    emit statusMessage(QString(" GIT %1 ").arg(action));
    emit runCommand(makeCmd(action, args), &output);
	return output;
}

/*!
 * \brief GIT pull
 * \param path repository path
 */
void GIT::pull(QString path)
{
    runGit("pull", quote(path), "");
}

/*!
 * \brief GIT fetch
 * \param path repository path
 */
void GIT::fetch(QString path)
{
    runGit("fetch", quote(path), "");
}

/*!
 * \brief get list of changed files in repository
 * \param path repository root path
 * \return list of FileEntry with status code and file path
 */
QList<GIT::FileEntry> GIT::getChangedFiles(QString path)
{
    QList<FileEntry> result;
    const QString output = runGit("status --porcelain", quote(path), "");
    const QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        if (line.length() < 4) continue;
        FileEntry entry;
        entry.statusCode = line.left(2);
        entry.filePath = line.mid(3).trimmed();
        // strip surrounding quotes that git sometimes adds
        if (entry.filePath.startsWith('"') && entry.filePath.endsWith('"')) {
            entry.filePath = entry.filePath.mid(1, entry.filePath.length() - 2);
        }
        result.append(entry);
    }
    return result;
}

/*!
 * \brief get current branch name
 * \param path repository path
 * \return branch name, or empty string if not a repository
 */
QString GIT::getCurrentBranch(QString path)
{
    const QString output = runGit("rev-parse --abbrev-ref HEAD", quote(path), "");
    return output.trimmed();
}

/*!
 * \brief get the repository-wide commit history with graph data
 * \param path repository root directory
 * \param maxEntries maximum number of log entries to return
 * \return list of GraphEntry structs (hash, parents, refs, subject)
 *
 * Uses \c %x01 (ASCII 0x01) as a field separator to avoid conflicts with
 * characters that can legitimately appear in ref names or commit subjects.
 */
QList<GIT::GraphEntry> GIT::getRepoLogGraph(const QString &path, int maxEntries)
{
    // Format: fullhash SOH parents SOH refs SOH subject
    // %P gives space-separated full parent hashes; %D gives comma-separated ref names.
    const QString fmt = "--format=%H%x01%P%x01%D%x01%s";
    const QString output = runGit(
        QString("log %1 -n %2").arg(fmt).arg(maxEntries),
        quote(path), "");

    QList<GraphEntry> result;
    const QChar sep(0x01);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const QStringList lines = output.split('\n', Qt::SkipEmptyParts);
#else
    const QStringList lines = output.split('\n', QString::SkipEmptyParts);
#endif
    for (const QString &line : lines) {
        const QStringList parts = line.split(sep);
        if (parts.size() < 4) continue;
        GraphEntry entry;
        entry.hash = parts[0].trimmed();
        if (!parts[1].trimmed().isEmpty())
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
            entry.parents = parts[1].trimmed().split(' ', Qt::SkipEmptyParts);
#else
            entry.parents = parts[1].trimmed().split(' ', QString::SkipEmptyParts);
#endif
        if (!parts[2].trimmed().isEmpty()) {
            for (const QString &r : parts[2].split(','))  {
                const QString trimmed = r.trimmed();
                if (!trimmed.isEmpty()) entry.refs << trimmed;
            }
        }
        // Subject is everything after the third separator (may contain the sep char itself)
        entry.subject = QStringList(parts.mid(3)).join(sep).trimmed();
        result << entry;
    }
    return result;
}

/*!
 * \brief get commit statistics (changed files + diff summary) for a single commit
 * \param path repository root directory
 * \param hash full or short commit hash
 * \return human-readable text with commit header and per-file change statistics
 */
QString GIT::getCommitStat(const QString &path, const QString &hash)
{
    // --no-patch: show header + stat lines only (no diff hunks)
    // --format=...: short hash, author, date.
    // %x20 (hex-encoded space) is used inside the format to avoid literal spaces
    // that would be split as argument boundaries by the build manager command runner.
    const QString action =
        "show --no-patch --stat "
        "--format=commit%x20%h%nAuthor:%x20%an%nDate:%x20%ad "
        "--date=short";
    return runGit(action, quote(path), hash);
}


/*!
 * \brief get the repository-wide commit history (most recent first)
 * \param path repository root directory
 * \param maxEntries maximum number of log entries to return
 * \return list of log lines in "short-hash subject" format
 */
QStringList GIT::getRepoLog(const QString &path, int maxEntries)
{
    const QString output = runGit(
        QString("log --oneline -n %1").arg(maxEntries),
        quote(path), "");
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
    return output.split('\n', Qt::SkipEmptyParts);
#else
    return output.split('\n', QString::SkipEmptyParts);
#endif
}
/*!
 * \brief run GIT command
 * \param action
 * \param path
 * \param args
 * \return
 * This variant is specifically useful for git log as it can't handle absolute file paths
 */
QString GIT::runGit(QString action,QString path, QString args)
{
    QString output;
    emit statusMessage(QString(" GIT %1 ").arg(action));
    emit runCommand(makeCmd("-C "+path+" "+action, args), &output);
    return output;
}



