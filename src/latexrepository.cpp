#include "latexrepository.h"
#include <QMutex>

LatexRepository *LatexRepository::m_Instance = nullptr;

LatexRepository::LatexRepository() :
    QObject(nullptr), m_dataSource(None)
{
	loadStaticPackageList(":/utilities/packageList");
}

LatexRepository *LatexRepository::instance()
{
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new LatexRepository();
	mutex.unlock();
	return m_Instance;
}

LatexRepository::DataSource LatexRepository::dataSource()
{
	return m_dataSource;
}

bool LatexRepository::loadStaticPackageList(const QString &file)
{
	if (file.isEmpty()) return false;
	packages.reserve(3000);

	QFile f(file);
	if (! f.open(QFile::ReadOnly)) return false;

	while (!f.atEnd()) {
		QString line = f.readLine().trimmed();
		if (line.startsWith('#')) continue;
		int sep = line.indexOf(':');
		if (sep < 0) {
			packages.insert(line, LatexPackageInfo(line));
		} else {
			QString name = line.left(sep);
			packages.insert(name, LatexPackageInfo(name, line.mid(sep + 1)));
		}
	}
	m_dataSource = Static;
	return true;
}

bool LatexRepository::packageExists(const QString &name)
{
	return packages.keys().contains(name);
}

QString LatexRepository::shortDescription(const QString &name)
{
	return packages[name].shortDescription;
}
