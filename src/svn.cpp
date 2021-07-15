#include "svn.h"
#include "smallUsefulFunctions.h"
#include "buildmanager.h"

SVN::SVN(QObject *parent) : QObject(parent)
{
}

/*!
 * Return a filename suitable to pass to an svn command line call. This does:
 *   1. enquote the filename in double qoutes.
 *   2. add '@' at the end if the filename contains an @. This prevents the interpretation
 *      of the contained @ as revision marker. See https://stackoverflow.com/a/757510/2726279
 */
QString SVN::quote(QString filename) {
	if (filename.contains('@')) {
		filename += '@';
	}
	return quotePath(filename);
}
/*!
 * \brief generate string which contains command "svn action args"
 * \param action
 * \param args
 * \return
 */
QString SVN::makeCmd(QString action, QString args)
{
	return BuildManager::CMD_SVN + " " + action + " " + args;
}
/*!
 * \brief generate a string which contains the command for "svnadmin action args"
 * \param action
 * \param args
 * \return
 */
QString SVN::makeAdminCmd(QString action, QString args)
{
	return BuildManager::CMD_SVNADMIN + " " + action + " " + args;
}

/*!
 * \brief svn commit filenmae
 * \param filename
 * \param message commit message
 */
void SVN::commit(QString filename, QString message)
{
	runSvn("commit", "-m " + enquoteStr(message) + " " + quote(filename));
}
/*!
 * \brief svn lock filename
 * \param filename
 */
void SVN::lock(QString filename)
{
	runSvn("lock", quote(filename));
}
/*!
 * \brief get svn status filename
 * \param filename
 * \return
 */
SVN::Status SVN::status(QString filename)
{
	QString output = runSvn("status", quote(filename));
	if (output.isEmpty()) return SVN::CheckedIn;
	if (output.startsWith("?")) return SVN::Unmanaged;
	if (output.startsWith("M")) return SVN::Modified;
	if (output.startsWith("C")) return SVN::InConflict;
	if (output.startsWith("L")) return SVN::Locked;
	return SVN::Unknown;
}
/*!
 * \brief get svn log
 * \param filename
 * \return
 */
QStringList SVN::log(QString filename)
{
    QString output = runSvn("log", quote(filename));
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
    QStringList revisions = output.split("\n", Qt::SkipEmptyParts);
#else
	QStringList revisions = output.split("\n", QString::SkipEmptyParts);
#endif
	QMutableStringListIterator iter(revisions);
	bool keep = false;
	QString elem;
	while (iter.hasNext()) {
		elem = iter.next();
		if (!keep) iter.remove();
        keep = elem.contains(QRegularExpression("-{60,}"));
	}
	return revisions;
}
/*!
 * \brief create a svn repository with trunk/branches/tags in directory filename
 * \param filename
 */
void SVN::createRepository(QString filename)
{
	QString path = QFileInfo(filename).absolutePath();
	//setStatusMessageProcess(QString(" svn create repo "));
	runSvnAdmin("create", quotePath(path + "/repo"));
	runSvn("mkdir", "\"file:///" + path + "/repo/trunk\" -m\"txs auto generate\"");
	runSvn("mkdir", "\"file:///" + path + "/repo/branches\" -m\"txs auto generate\"");
	runSvn("mkdir", "\"file:///" + path + "/repo/tags\" -m\"txs auto generate\"");
	runSvn("checkout", "\"file:///" + path + "/repo/trunk\" \"" + path + "\"");
}
/*!
 * \brief run svn command
 * \param action
 * \param args
 * \return
 */
QString SVN::runSvn(QString action, QString args)
{
	QString output;
	emit statusMessage(QString(" svn %1 ").arg(action));
	emit runCommand(makeCmd(action, args), &output);
	return output;
}
/*!
 * \brief run svnadmin
 * \param action
 * \param args
 * \return
 */
QString SVN::runSvnAdmin(QString action, QString args)
{
	QString output;
	emit statusMessage(QString(" svn admin %1 ").arg(action));
	emit runCommand(makeAdminCmd(action, args), &output);
	return output;
}


