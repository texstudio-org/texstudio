#include "help.h"
#include "texdocdialog.h"
#include "smallUsefulFunctions.h"
#include "utilsSystem.h"
#include "configmanager.h"
#include <QProcessEnvironment>
#include <QMutex>

Help::Help(QObject *parent): QObject(parent),texDocSystem(0)
{

}

/*!
 * \brief execute a dialog to let the user choose a package to show its documentation
 * \param packages
 * \param defaultPackage
 */
void Help::execTexdocDialog(const QStringList &packages, const QString &defaultPackage)
{
    TexdocDialog dialog(nullptr,this);
	dialog.setPackageNames(packages);
	if (!defaultPackage.isEmpty()) {
		dialog.setPreferredPackage(defaultPackage);
	}
	if (dialog.exec()) {
		viewTexdoc(dialog.selectedPackage());
	}
}
/*!
 * \brief run texdoc --view package
 * \param package
 */
void Help::viewTexdoc(QString package)
{
	if (package.isEmpty()) {
		QAction *act = qobject_cast<QAction *>(sender());
		if (!act) return;
		package = act->data().toString();
	}
	if (!package.isEmpty()) {
        QString answer=runTexdoc("--view "+package);
	}
}

/*!
 * \brief check if system runs miktex
 * Tries to run texdoc --veriosn and analyzes result.
 * Miktex starts with MikTeX ...
 * \return
 */
bool Help::isMiktexTexdoc()
{
    if (!texDocSystem) {
        QString answer=runTexdoc("--version");
		texDocSystem = answer.startsWith("MiKTeX") ? 1 : 2;
	}
	return (texDocSystem == 1);
}

bool Help::isTexdocExpectedToFinish()
{
	if (!isMiktexTexdoc()) return true;
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    foreach (const QString &var, env.keys()) {
		if (var.startsWith("MIKTEX_VIEW_")) {
			// miktex texdoc will run as long as the viewer is opened when the MIKTEX_VIEW_* variables are set
			// http://docs.miktex.org/manual/mthelp.html
			return false;
		}
	}
	return true;
}

/*!
 * \brief search for documentation files for a given package
 * It uses texdoc to access that information.
 * \param package
 * \param silent
 * \return
 */
QString Help::packageDocFile(const QString &package, bool silent)
{
    QString cmd = BuildManager::CMD_TEXDOC;
	if (cmd.isEmpty()) {
		if (!silent) UtilsUi::txsWarning(tr("texdoc not found."));
		return QString();
	}
	QStringList args;
    if (isMiktexTexdoc()) {
		args << "--list-only";
	} else {
		args << "--list" << "--machine";
	}
	args << package;


    QString output =runTexdoc(args.join(" "));

	QStringList allFiles;
    if (isMiktexTexdoc()) {
		allFiles = output.split("\r\n");
	} else {
		foreach (const QString &line, output.split("\n")) {
			QStringList cols = line.simplified().split(" ");
			if (cols.count() > 2)
				allFiles << cols.at(2);
		}
	}
	foreach (const QString &file, allFiles) {
		if (file.endsWith(".pdf") || file.endsWith(".dvi"))
			return file;
	}
	return QString();
}
/*!
 * \brief search for documentation files for a given package asynchrnously
 * It uses texdoc to access that information.
 * The results are processed in texdocAvailableRequestFinished
 * \param package
 * \param silent
 * \return
 */
void Help::texdocAvailableRequest(const QString &package)
{
	if (package.isEmpty())
		return;
    if (BuildManager::CMD_TEXDOC.isEmpty()) {
		emit texdocAvailableReply(package, false, tr("texdoc not found."));
		return;
	}

	QStringList args;
	if (isMiktexTexdoc()) {
		args << "--print-only" << package;
	} else {
        args << "--list" << "--machine" << package; // --print-only does not exist in texlive 2012, actual is response is not used either ...
		// TODO: not the right option: don't open the viewer here
		// There seems to be no option yielding only the would be called command
		// Alternative: texdoc --list -M and parse the first line for the package name
	}
    runTexdocAsync(args.join(" "),SLOT(texdocAvailableRequestFinished(int,QProcess::ExitStatus)));

}
void Help::texdocAvailableRequestFinished(int,QProcess::ExitStatus status){

    if(status!=QProcess::NormalExit) return; // texdoc --list failed

    ProcessX *proc=qobject_cast<ProcessX *>(sender());
    QString *buffer=proc->getStdoutBuffer();
    QString cmdLine=proc->getCommandLine();
    int i=cmdLine.lastIndexOf(" ");
    QString package;
    if(i>-1){
        package=cmdLine.mid(i+1);
    }


    if(buffer==nullptr) return; // sanity check

    if(!isMiktexTexdoc() && !buffer->isEmpty()){
        // analyze texdoc --list result in more detail, as it gives results even for partially matched names
        QStringList lines=buffer->split("\n");
        QString line=lines.first();
        QStringList cols=line.split("\t");
        if(cols.count()>4){
            if(cols.value(1).startsWith("-")){
                buffer->clear(); // only partial, no real match
            }
        }
    }

    emit texdocAvailableReply(package, !buffer->isEmpty(), QString());

    delete buffer;
}

/*!
 * \brief run texdoc command
 * \param args
 * \return
 */
QString Help::runTexdoc(QString args)
{
    QString output;
    emit statusMessage(QString(" texdoc "));
    emit runCommand(BuildManager::CMD_TEXDOC+" "+args, &output);
    return output;
}
/*!
 * \brief run texdoc command asynchronously
 * \param args
 * \param finishedCMD SLOT for return path
 * \return
 */
bool Help::runTexdocAsync(QString args,const char * finishedCMD)
{
    emit statusMessage(QString(" texdoc (async)"));
    emit runCommandAsync(BuildManager::CMD_TEXDOC+" "+args, finishedCMD);
    return true;
}




LatexReference::LatexReference(QObject *parent) : QObject(parent) {}

void LatexReference::setFile(QString filename)
{
	m_filename = filename;
	if (filename.isEmpty()) return;

	QFile f(filename);
	if (!f.open(QFile::ReadOnly | QFile::Text)) return;
	QTextStream stream(&f);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    stream.setCodec("UTF-8");
#endif
	m_htmltext = stream.readAll();
	makeIndex();
}

bool LatexReference::contains(const QString &command)
{
	return m_anchors.contains(command);
}

/// tries to generate a text of suitable length for display as a tooltip
QString LatexReference::getTextForTooltip(const QString &command)
{
	QString sectionText = getSectionText(command);
	QString partialText;
    if (sectionText.count('\n') > 30) { // tooltip would be very large: try to get a reasonable smaller string
        if (command.startsWith("\\begin{")) {
			return truncateLines(sectionText, 30);
		} else {
			partialText = getPartialText(command);
            int nr=partialText.count('\n');
            if(nr<10)
                return truncateLines(sectionText, 30);
            if (!partialText.isEmpty()) return partialText;
        }
	}
	return sectionText;
}

/*! get all the text in the section describing the command
 * it starts with the first heading after the section anchor and ranges down to the next <hr>
 */
QString LatexReference::getSectionText(const QString &command)
{
	Anchor sAnchor(m_sectionAnchors[command]);
	if (sAnchor.name.isNull()) return QString();
	if (sAnchor.start_pos < 0) {
		sAnchor.start_pos = m_htmltext.indexOf(QString("<a name=\"%1\">").arg(sAnchor.name));
		sAnchor.start_pos = m_htmltext.indexOf("<h", sAnchor.start_pos); // skip header div by going to next headline
	}
	if (sAnchor.start_pos < 0) return QString();
	if (sAnchor.end_pos < 0) {
		QString endTag("<hr>");
		sAnchor.end_pos = m_htmltext.indexOf(endTag, sAnchor.start_pos);
		m_sectionAnchors.insert(command, sAnchor); // save positions for a faster lookup next time
	}
	return m_htmltext.mid(sAnchor.start_pos, sAnchor.end_pos - sAnchor.start_pos);
}

/*! get only a partial description for the command
 *  the serach looks for the following block types (sqare brackets mark the extrated text:
 *    [<dt>(anchor-in-here)</dt><dd></dd>]
 *    </div>[(anchor-in-here)]</a name=
 */
QString LatexReference::getPartialText(const QString &command)
{
    static QRegularExpression startTag("<(dt|/div)>");
	QString endTag;
	int endOffset = 0;

	Anchor anchor(m_anchors[command]);
	if (anchor.name.isNull()) return QString();
	if (anchor.start_pos < 0) {
		anchor.start_pos = m_htmltext.indexOf(QString("<a name=\"%1\">").arg(anchor.name));
        QRegularExpressionMatch match;
        anchor.start_pos = m_htmltext.lastIndexOf(startTag, anchor.start_pos,&match);
        if (match.captured(1) == "dt") {
			endTag = "</dd>";
			endOffset = endTag.length();
		} else {
			anchor.start_pos += QString("</div>").length();
			endTag = "</p>";
		}
	}
	if (anchor.start_pos < 0) return QString();
	if (anchor.end_pos < 0) {
		anchor.end_pos = m_htmltext.indexOf(endTag, anchor.start_pos + 1);
		if (anchor.end_pos >= 0) anchor.end_pos += endOffset;
		int hrEnd = m_htmltext.indexOf("<hr>", anchor.start_pos + 1);
		if (hrEnd >= 0 && hrEnd < anchor.end_pos) // don't go further than the next <hr>
			anchor.end_pos = hrEnd;
		m_anchors.insert(command, anchor); // save positions for a faster lookup next time
	}
	return m_htmltext.mid(anchor.start_pos, anchor.end_pos - anchor.start_pos);
}

/* parses the index of the reference manual and extracts the anchor names for the commands */
void LatexReference::makeIndex()
{
	QString startTag("<table class=\"index-cp\"");
	QString endTag("</table>");

	int start = m_htmltext.indexOf(startTag);
	if (start < 0) return;
	int end = m_htmltext.indexOf(endTag, start);
	int length = end < 0 ? -1 : end - start + endTag.length();
	QString indexText = m_htmltext.mid(start, length);

    QRegularExpression rx("<a href=\"#([^\"]+)\"><code>([^\\s<]+)[^\n]*<a href=\"#([^\"]+)\">([^<]+)</a>");
	int pos = 0;
	while (pos >= 0) {
        QRegularExpressionMatch match;
        pos = indexText.indexOf(rx, pos,&match);
		if (pos < 0) break;
        QString anchorName(match.captured(1));
        QString word(match.captured(2));
        QString sectionAnchorName(match.captured(3));
        //QString sectionTitle(match.captured(4));
		if (word.startsWith('\\')) { // a command
			if (word == "\\begin" || word == "\\") {
				// don't add these words to the index because they give a mess in the tooltips
                pos += match.capturedLength();
				continue;
			}
			m_anchors.insert(word, Anchor(anchorName));
			m_sectionAnchors.insert(word, Anchor(sectionAnchorName));
		} else if (anchorName.contains("environment")) { // an environment
			m_anchors.insert("\\begin{" + word, Anchor(anchorName));
			m_sectionAnchors.insert("\\begin{" + word, Anchor(sectionAnchorName));
		} else {
			// TODO: anything useful in the rest?
			//qDebug() << word << anchorName << sectionAnchorName << sectionTitle;
		}
        pos += match.capturedLength();
	}
	//qDebug() << "Found entries in index:" << m_anchors.count();
}

