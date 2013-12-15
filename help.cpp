#include "help.h"
#include "texdocdialog.h"
#include "smallUsefulFunctions.h"
#include <QMutex>


Help * Help::m_Instance = 0;

Help::Help() :
	QObject(0)
{
}

void Help::execTexdocDialog(const QStringList &packages, const QString &defaultPackage)
{
	TexdocDialog dialog;
	dialog.setPackageNames(packages);
	if (!defaultPackage.isEmpty()) {
		dialog.setPreferredPackage(defaultPackage);
	}
	if (dialog.exec()) {
		viewTexdoc(dialog.selectedPackage());
		QString package = dialog.selectedPackage();
	}
}

void Help::viewTexdoc(QString package)
{
	if (package.isEmpty()) {
		QAction *act = qobject_cast<QAction*>(sender());
		if (!act) return;
		package = act->data().toString();
	}
	if (!package.isEmpty()) {
		QProcess proc(this);
		connect(&proc, SIGNAL(readyReadStandardError()), this, SLOT(viewTexdocError()));
		proc.start("texdoc", QStringList() << "--view" << package);
		if (!proc.waitForFinished(2000)) {
			txsWarning(QString(tr("texdoc took too long to open the documentation for the package:")+"\n%1").arg(package));
			return;
		}
	}
}

int Help::texDocSystem=0;

bool Help::isMiktexTexdoc() {
    if (!texDocSystem) {
		QProcess proc;
		proc.start("texdoc --version");
		proc.waitForFinished(1000);
		QString answer = QString(proc.readAll());
        texDocSystem = answer.startsWith("MiKTeX") ? 1 : 2;
	}
	return (texDocSystem==1);
}

QString Help::packageDocFile(const QString &package) {
	QStringList args;
	if (Help::isMiktexTexdoc()) {
		args << "--list-only";
	} else {
		args << "--list" << "--machine";
	}
	args << package;
	QProcess proc;
	proc.start("texdoc", args);
	if (!proc.waitForFinished(2000)) {
		txsWarning(QString(tr("texdoc did not respond to query on package:")+"\n%1").arg(package));
		return QString();
	}
	QString output = proc.readAllStandardOutput();
	QStringList allFiles;
	if (Help::isMiktexTexdoc()) {
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

void Help::texdocAvailableRequest(const QString &package)
{
	if (package.isEmpty())
		return;

	QStringList args;
	if (isMiktexTexdoc()) {
		args << "--print-only" << package;
	} else {
	    args << "--list" << "--machine"; // --print-only does not exist in texlive 2012, actual is response is not used either ...
		// TODO: not the right option: don't open the viewer here
		// There seems to be no option yielding only the would be called command
		// Alternative: texdoc --list -M and parse the first line for the package name
	}
	QProcess *proc = new QProcess(this);
	proc->setProperty("package", package);
	connect(proc, SIGNAL(finished(int)), SLOT(texdocAvailableRequestFinished(int)));
	proc->start("texdoc", args);
}

void Help::texdocAvailableRequestFinished(int exitCode)
{
	Q_UNUSED(exitCode);
	QProcess *proc = qobject_cast<QProcess *>(sender());
	if (!proc) return;
	QString package = proc->property("package").toString();
	QString docCommand = proc->readAll();

	emit texdocAvailableReply(package, !docCommand.isEmpty());
	proc->deleteLater();
}


void Help::viewTexdocError() {
	QProcess *proc = qobject_cast<QProcess*>(sender());
	if (proc) {
		txsWarning(proc->readAllStandardError());
	}
}

Help *Help::instance()
{
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new Help();
	mutex.unlock();
	return m_Instance;
}


LatexReference::LatexReference(QObject *parent) : QObject(parent) {}

void LatexReference::setFile(QString filename) {
	m_filename = filename;

	QFile f(filename);
	if (!f.open(QFile::ReadOnly | QFile::Text)) return;
	QTime t;
	t.start();
	QTextStream stream(&f);
	stream.setCodec("UTF-8");
	m_htmltext = stream.readAll();
	makeIndex();
}

bool LatexReference::contains(const QString &command) {
	return m_anchors.contains(command);
}

/* tries to generate a text of suitable length for display as a tooltip */
QString LatexReference::getTextForTooltip(const QString &command) {
	QString sectionText = getSectionText(command);
	QString partialText;
	if (sectionText.count('\n') > 30) { // tooltip would be very large: try to get a reasonable smaller string
		if (command.startsWith("\\begin{")) {
			return truncateLines(sectionText, 30);
		} else {
			partialText = getPartialText(command);
			if (!partialText.isEmpty()) return partialText;
		}
	}
	return sectionText;
}

/* get all the text in the section describing the command
 * it starts with the first heading after the section anchor and ranges down to the next <hr>
 */
QString LatexReference::getSectionText(const QString &command) {
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
	return m_htmltext.mid(sAnchor.start_pos, sAnchor.end_pos-sAnchor.start_pos);
}

/* get only a partial description for the command
 * the serach looks for the following block types (sqare brackets mark the extrated text:
 *    [<dt>(anchor-in-here)</dt><dd></dd>]
 *    </div>[(anchor-in-here)]</a name=
 */
QString LatexReference::getPartialText(const QString &command) {
	static QRegExp startTag("<(dt|/div)>");
	QString endTag;
	int endOffset = 0;

	Anchor anchor(m_anchors[command]);
	if (anchor.name.isNull()) return QString();
	if (anchor.start_pos < 0) {
		anchor.start_pos = m_htmltext.indexOf(QString("<a name=\"%1\">").arg(anchor.name));
		anchor.start_pos = m_htmltext.lastIndexOf(startTag, anchor.start_pos);
		if (startTag.cap(1) == "dt") {
			endTag = "</dd>";
			endOffset = endTag.length();
		} else {
			anchor.start_pos += QString("</div>").length();
			endTag = "</p>";
		}
	}
	if (anchor.start_pos < 0) return QString();
	if (anchor.end_pos < 0) {
		anchor.end_pos = m_htmltext.indexOf(endTag, anchor.start_pos+1);
		if (anchor.end_pos >= 0) anchor.end_pos += endOffset;
		m_anchors.insert(command, anchor); // save positions for a faster lookup next time
	}
	return m_htmltext.mid(anchor.start_pos, anchor.end_pos-anchor.start_pos);
}

/* parses the index of the reference manual and extracts the anchor names for the commands */
void LatexReference::makeIndex() {
	QString startTag("<table class=\"index-fn\"");
	QString endTag("</table>");

	int start = m_htmltext.indexOf(startTag);
	if (start < 0) return;
	int end = m_htmltext.indexOf(endTag, start);
	int length = end < 0 ? -1 : end - start + endTag.length();
	QString indexText = m_htmltext.mid(start, length);

	QRegExp rx("<a href=\"#([^\"]+)\"><code>([^\\s<]+)[^\n]*<a href=\"#([^\"]+)\">([^<]+)</a>");
	int pos = 0;
	while (pos >= 0) {
		pos = indexText.indexOf(rx, pos);
		if (pos < 0) break;
		QString anchorName(rx.cap(1));
		QString word(rx.cap(2));
		QString sectionAnchorName(rx.cap(3));
		QString sectionTitle(rx.cap(4));
		if (word.startsWith('\\')) { // a command
			if (word == "\\begin" || word == "\\") {
				// don't add these words to the index because they give a mess in the tooltips
				pos += rx.matchedLength();
				continue;
			}
			m_anchors.insert(word, Anchor(anchorName));
			m_sectionAnchors.insert(word, Anchor(sectionAnchorName));
		} else if (anchorName.contains("environment")){ // an environment
			m_anchors.insert("\\begin{"+word, Anchor(anchorName));
			m_sectionAnchors.insert("\\begin{"+word, Anchor(sectionAnchorName));
		} else {
			// TODO: anything useful in the rest?
			//qDebug() << word << anchorName << sectionAnchorName << sectionTitle;
		}
		pos += rx.matchedLength();
	}
	//qDebug() << "Found entries in index:" << m_anchors.count();

}

