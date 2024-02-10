#include "latexrepository.h"
#include <QXmlStreamReader>
#include <QMutex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

LatexRepository *LatexRepository::m_Instance = nullptr;

LatexRepository::LatexRepository() :
    QObject(nullptr), m_dataSource(None)
{
    loadStaticPackageList(":/utilities/packageDatabase.json");
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
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return false;
    QJsonDocument Document = QJsonDocument::fromJson(f.readAll());
    const QJsonArray &array(Document.array());

    for(const QJsonValue &value : array){
        const QJsonObject &object(value.toObject());
        LatexPackageInfo package;
        package.id = object["id"].toString();
        package.name = object["name"].toString();
        package.caption = object["caption"].toString().replace("\'","\''");
        //Authors
        QJsonArray authorsArray = object["authors"].toArray();
        for(const QJsonValue &item : authorsArray){
            CTANAuthor author;
            const QJsonObject &authorObject(item.toObject());
            author.id = authorObject["key"].toString();
            author.name = authorObject["givenname"].toString();
            author.familyName = authorObject["familyname"].toString();
            package.authors.append(author);
        }
        //Copyright
        QJsonArray copyrightArray = object["copyright"].toArray();
        for(const QJsonValue &item : copyrightArray){
            CTANCopyright copyright;
            const QJsonObject &copyrightObject(item.toObject());
            copyright.ownerId = copyrightObject["owner"].toString();
            copyright.year = copyrightObject["year"].toString();
            package.copyrights.append(copyright);
        }
        //License
        QJsonArray licenseArray = object["license"].toArray();
        for(const QJsonValue &item : licenseArray){
            CTANLicense license;
            const QJsonObject &licenseObject(item.toObject());
            license.key = licenseObject["key"].toString();
            license.name = licenseObject["name"].toString();
            license.isFree = licenseObject["free"].toBool();
            package.licences.append(license);
        }

        //Version
        QJsonObject item = object["version"].toObject();
        CTANVersion version;
        version.number = item["number"].toString();
        QDate date = QDate::fromString(item["date"].toString(),"yyyy-MM-dd");
        version.date = date;
        package.version = version;
        //Description
        QJsonArray descriptionsArray = object["descriptions"].toArray();
        for(const QJsonValue &item : descriptionsArray){
            CTANDescription description;
            const QJsonObject &descriptionObject(item.toObject());
            QString language = descriptionObject["language"].toString();
            description.language = (language.isNull() || language.isEmpty()) ? "en" : language;
            description.text = descriptionObject["text"].toString().replace("\'","\''");
            package.descriptions.append(description);
        }
        //Documentation
        QJsonArray documetationsArray = object["documentation"].toArray();
        for(const QJsonValue &item : documetationsArray){
            CTANDocumentation documentation;
            const QJsonObject &documetationObject(item.toObject());
            documentation.language = documetationObject["language"].toString().replace("\'","\''");
            documentation.details = documetationObject["details"].toString().replace("\'","\''");
            documentation.href = documetationObject["href"].toString();
            package.documentations.append(documentation);
        }
        QJsonObject ctanObject = object["ctan"].toObject();
        package.ctanLink = ctanObject["path"].toString();
        package.miktex = object["miktex"].toString();
        package.texlive = object["texlive"].toString();

        QJsonArray topicsArray = object["topics"].toArray();
        for(const QJsonValue &item : topicsArray){
            CTANTopic topic;
            const QJsonObject &topicsObject(item.toObject());
            topic.key = topicsObject["key"].toString();
            topic.details = topicsObject["details"].toString();
            package.topics.append(topic);

        }
        packages.insert(package.id,package);
    }
    f.close();
    m_dataSource = Static;
	return true;
}

bool LatexRepository::packageExists(const QString &name)
{
    return packages.contains(name);
}

QString LatexRepository::shortDescription(const QString &name)
{
    return packages[name].caption;
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

QString LatexRepository::packageInfo(LatexPackageInfo package)
{
    QString Info = tr("### Package %1 Info").arg(package.id)+"\n";
    Info += tr("- Name : ")+package.name+"\n";
    Info += tr("- Caption : ")+package.caption+"\n";
    Info += tr("- Authors : \n")+package.authorsFullName()+"\n";
    QString delim = ( package.version.number.isEmpty() || !package.version.date.isValid() ? "" : ", " );
    Info += tr("- Version : ")+package.version.number+delim+package.version.date.toString()+"\n";
    Info += tr("- Documentation : \n")+package.showAllDocumentation()+"\n";
    Info += tr("- Copyright : \n")+package.showAllCopyrights()+"\n";
    Info += tr("- License : \n")+package.showAllLicenses()+"\n";
    Info += tr("- MikTex : ")+package.miktex+"\n";
    Info += tr("- TexLive : ")+package.texlive+"\n";
    Info += tr("- Topics : \n")+package.showAllTopics()+"\n";
    Info += tr("- Link : ")+package.ctanLink+"\n";
    return Info;
}

QHash<QString, LatexPackageInfo> LatexRepository::getPackageHash()
{
    return packages;
}
