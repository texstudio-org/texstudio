#include "latexpackages.h"
#include <QMutex>

LatexPackages * LatexPackages::m_Instance = 0;

LatexPackages::LatexPackages() :
	QObject(0), m_dataSource(None)
{
	loadStaticPackageList(":/utilities/packageList");
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

bool LatexPackages::packageExists(const QString& name) {
	return packages.keys().contains(name);
}

QString LatexPackages::shortDescription(const QString& name) {
	return packages[name].shortDescription;
}
