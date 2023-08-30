#include "latexrepository.h"
#include <QXmlStreamReader>
#include <QMutex>

LatexRepository *LatexRepository::m_Instance = nullptr;

LatexRepository::LatexRepository() :
    QObject(nullptr), m_dataSource(None)
{
    loadStaticPackageList(":/utilities/packageList.xml");
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
	if (! f.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }

	QXmlStreamReader xml;
	QIODevice *device = &f;
	xml.setDevice(device);

	if (!xml.readNextStartElement()) return false;
	while (xml.readNextStartElement()) {
		if (xml.name() == QString("package")) {
            QString key = xml.attributes().value(QString(""),QString("key")).toString();
            QString name = xml.attributes().value(QString(""),QString("name")).toString();
            QString caption = xml.attributes().value(QString(""),QString("caption")).toString();
			packages.insert(key, LatexPackageInfo(name, caption));
		}
		xml.skipCurrentElement();
	}
	m_dataSource = Static;
	return true;
}

bool LatexRepository::packageExists(const QString &name)
{
    return packages.contains(name);
}

QString LatexRepository::shortDescription(const QString &name)
{
    return packages[name].shortDescription;
}

TeXdocStatus LatexRepository::docStatus(const QString &name)
{
    return packages[name].docStatus;
}

void LatexRepository::updatePackageInfo(const QString &name, const TeXdocStatus &docStatus)
{
    packages[name].docStatus = docStatus;
}

/*!
 * \brief provide names of all known packages
 * \return
 */
QStringList LatexRepository::availablePackages()
{
    return packages.keys();
}
