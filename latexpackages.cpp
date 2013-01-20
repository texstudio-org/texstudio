#include "latexpackages.h"
#include <QMutex>

LatexPackages * LatexPackages::m_Instance = 0;

LatexPackages::LatexPackages() :
	QObject(0), m_dataSource(None)
{
	loadStaticPackageList(":/utilities/packageList");
	queryPackageList();
}

LatexPackages *LatexPackages::instance() {
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new LatexPackages();
	mutex.unlock();
	return m_Instance;
}

LatexPackages::DataSource LatexPackages::dataSource() {
	return m_dataSource;
}

bool LatexPackages::packageExists(const QString& name) {
	return packages.keys().contains(name);
}

QString LatexPackages::shortDescription(const QString& name) {
	return packages[name].shortDescription;
}

bool LatexPackages::loadStaticPackageList(const QString &file) {
	if (file.isEmpty()) return false;
	packages.reserve(3000);

	QFile f(file);
	if (! f.open(QFile::ReadOnly)) return false;

	while (!f.atEnd()) {
		QString line = f.readLine().trimmed();
		if (line.startsWith('#')) continue;
		int sep = line.indexOf(':');
		if (sep<0) {
			packages.insert(line, LatexPackageInfo(line));
		} else {
			QString name = line.left(sep);
			packages.insert(name, LatexPackageInfo(name, line.mid(sep+1)));
		}
	}
	m_dataSource = Static;
	return true;
}

bool LatexPackages::queryPackageList() {
	QStringList args;
	args << "--help";
	QProcess *proc = new QProcess(this);
	//proc->setProperty("package", package);
	connect(proc, SIGNAL(readyReadStandardOutput()), SLOT(queryReadData()));
	connect(proc, SIGNAL(readyReadStandardError()), SLOT(queryReadError()));
	connect(proc, SIGNAL(finished(int)), SLOT(queryPackageListCompleted(int)));
	connect(proc, SIGNAL(error(QProcess::ProcessError)), SLOT(queryError(QProcess::ProcessError)));
	proc->start("C:/texlive/2012/bin/win32/tlmgr.bat", args);
	qDebug() << "baz";
	return true;
}

void LatexPackages::queryReadData() {
	QProcess *proc = qobject_cast<QProcess *>(sender());
	qDebug() << proc->readAllStandardOutput();
	m_queryData += proc->readAllStandardOutput() + '\n';
	qDebug() << "reading";
}

void LatexPackages::queryReadError() {
	QProcess *proc = qobject_cast<QProcess *>(sender());
	qDebug() << "error:" << proc->readAllStandardError();
}

void LatexPackages::queryPackageListCompleted(int exitCode) {
	qDebug() << "foo";
	qDebug() << "content" << m_queryData;
	Q_UNUSED(exitCode);
	QProcess *proc = qobject_cast<QProcess *>(sender());
	if (!proc) return;
	//QString package = proc->property("package").toString();
	QString info = proc->readAll();
	qDebug() << info << exitCode;
	proc->deleteLater();
}

void LatexPackages::queryError(QProcess::ProcessError error) {
	qDebug() << "error" << error;
}
