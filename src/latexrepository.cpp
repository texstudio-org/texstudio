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
    loadStaticPackageList(":/utilities/PackageDatabase.json");
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
        package.Id = object["id"].toString();
        package.Name = object["name"].toString();
        package.Caption = object["caption"].toString().replace("\'","\''");
        //Authors
        QJsonArray authorsArray = object["authors"].toArray();
        for(const QJsonValue &item : authorsArray){
            CTANAuthor author;
            const QJsonObject &authorObject(item.toObject());
            author.Id = authorObject["key"].toString();
            author.Name = authorObject["givenname"].toString();
            author.FamilyName = authorObject["familyname"].toString();
            package.Authors.append(author);
        }
        //Copyright
        QJsonArray copyrightArray = object["copyright"].toArray();
        for(const QJsonValue &item : copyrightArray){
            CTANCopyright copyright;
            const QJsonObject &copyrightObject(item.toObject());
            copyright.OwnerId = copyrightObject["owner"].toString();
            copyright.Year = copyrightObject["year"].toString();
            package.Copyright.append(copyright);
        }
        //License
        QJsonArray licenseArray = object["license"].toArray();
        for(const QJsonValue &item : licenseArray){
            CTANLicense license;
            const QJsonObject &licenseObject(item.toObject());
            license.Key = licenseObject["key"].toString();
            license.Name = licenseObject["name"].toString();
            license.IsFree = licenseObject["free"].toBool();
            package.Licences.append(license);
        }

        //Version
        QJsonObject item = object["version"].toObject();
        CTANVersion version;
        version.Number = item["number"].toString();
        QDate date = QDate::fromString(item["date"].toString(),"yyyy-MM-dd");
        version.Date = date;
        package.Version = version;
        //Description
        QJsonArray descriptionsArray = object["descriptions"].toArray();
        for(const QJsonValue &item : descriptionsArray){
            CTANDescription description;
            const QJsonObject &descriptionObject(item.toObject());
            QString language = descriptionObject["language"].toString();
            description.Language = (language.isNull() || language.isEmpty()) ? "English" : language;
            description.Text = descriptionObject["text"].toString().replace("\'","\''");
            package.Descriptions.append(description);
        }
        //Documentation
        QJsonArray documetationsArray = object["documentation"].toArray();
        for(const QJsonValue &item : documetationsArray){
            CTANDocumentation documentation;
            const QJsonObject &documetationObject(item.toObject());
            documentation.Language = documetationObject["language"].toString().replace("\'","\''");
            documentation.Details = documetationObject["details"].toString().replace("\'","\''");
            documentation.Href = documetationObject["href"].toString();
            package.Documentations.append(documentation);
        }
        QJsonObject ctanObject = object["ctan"].toObject();
        package.CtanLink = ctanObject["path"].toString();
        package.Miktex = object["miktex"].toString();
        package.Texlive = object["texlive"].toString();

        QJsonArray topicsArray = object["topics"].toArray();
        for(const QJsonValue &item : topicsArray){
            CTANTopic topic;
            const QJsonObject &topicsObject(item.toObject());
            topic.Key = topicsObject["key"].toString();
            topic.Details = topicsObject["details"].toString();
            package.Topics.append(topic);

        }
        packages.insert(package.Id,package);
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
    return packages[name].Caption;
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
    QString Info = tr("### Package %1 Info").arg(package.Id)+"\n";
    Info += tr("- Name : ")+package.Name+"\n";
    Info += tr("- Caption : ")+package.Caption+"\n";
    Info += tr("- Authors : \n")+package.AuthorsFullName()+"\n";
    Info += tr("- Version : ")+package.Version.Number+", "+package.Version.Date.toString()+"\n";
    Info += tr("- Documentation : \n")+package.ShowAllDocumentation()+"\n";
    Info += tr("- Copyright : \n")+package.ShowAllCopyrights()+"\n";
    Info += tr("- License : \n")+package.ShowAllLicenses()+"\n";
    Info += tr("- MikTex : ")+package.Miktex+"\n";
    Info += tr("- TexLive : ")+package.Texlive+"\n";
    Info += tr("- Topics : \n")+package.ShowAllTopics()+"\n";
    Info += tr("- Link : ")+package.CtanLink+"\n";
    return Info;
}

QHash<QString, LatexPackageInfo> LatexRepository::getPackageHash()
{
    return packages;
}
