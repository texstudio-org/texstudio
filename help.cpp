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
