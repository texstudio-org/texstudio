#include "latexrepository.h"
#include <QXmlStreamReader>
#include <QMutex>

LatexRepository *LatexRepository::m_Instance = nullptr;

LatexRepository::LatexRepository() :
    QObject(nullptr), m_dataSource(None)
{
	loadStaticPackageList("packages.xml");
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
        QMessageBox::warning(nullptr, tr("Reading Package Data"),
                             tr("Cannot read file %1").arg(QDir::toNativeSeparators(file)));
        return false;
    }

	QXmlStreamReader xml;
	QIODevice *device = &f;
	xml.setDevice(device);

	if (!xml.readNextStartElement()) return false;
	while (xml.readNextStartElement()) {
		if (xml.name() == QString("package")) {
			QString key = QString("%1").arg(xml.attributes().value(QString(""),QString("key")));
			QString name = QString("%1").arg(xml.attributes().value(QString(""),QString("name")));
			QString caption = QString("%1").arg(xml.attributes().value(QString(""),QString("caption")));
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
