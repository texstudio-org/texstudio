#ifndef Header_Latex_Repository
#define Header_Latex_Repository

#include "mostQtHeaders.h"
enum TeXdocStatus { Undefined, Available, Unavailable };

struct CTANAuthor
{
    QString id;
    QString name;
    QString familyName;
    bool active;
};

struct CTANCopyright
{
    QString ownerId;
    QString year;
};

struct CTANVersion
{
    QString number;
    QDate date;
};

struct CTANDescription
{
    QString language;
    QString text;
};

struct CTANDocumentation
{
    QString language;
    QString details;
    QString href;
};

struct CTANLicense
{
    QString key;
    QString name;
    bool isFree;
};

struct CTANTopic
{
    QString key;
    QString details;
};

class LatexPackageInfo
{
public:
    LatexPackageInfo(const QString &name = QString(), const QString &shortDescr = QString(), bool inst = false, TeXdocStatus status = Undefined)
	{
        this->name = name;
        caption = shortDescr;
		installed = inst;
		docStatus = status;
	}

    QString id;
    QString name;
    QString caption;
    QList<CTANAuthor> authors;
    QList<CTANCopyright> copyrights;
    QList<CTANLicense> licences;
    CTANVersion version;
    QList<CTANDescription> descriptions;
    QList<CTANDocumentation> documentations;
    QString ctanLink;
    QList<CTANTopic> topics;
    QString miktex;
    QString texlive;
    QStringList also;
    bool installed;
    TeXdocStatus docStatus;

    QString authorsFullName(){
        QString text;
        for(CTANAuthor author : authors){
            text += "\t- "+author.name+" "+author.familyName+"\n";
        }
        return text;
    }

    QString showAllCopyrights(){
        QString text;
        for(CTANCopyright copyright : copyrights){
            if(!copyright.ownerId.isEmpty() || !copyright.year.isEmpty()){
                text += "\t- "+copyright.ownerId+", "+copyright.year+"\n";
            }
        }
        return text;
    }

    QString showAllLicenses(){
        QString text;
        QString isFree;
        for(CTANLicense license : licences){
            isFree = (license.isFree) ? QObject::tr(" (Free)") : QObject::tr(" (Not free)");
            text += "\t- "+license.key+", "+license.name+isFree+"\n";
        }
        return text;
    }

    QString showAllDocumentation(){
        QString text;
        for(CTANDocumentation doc : documentations){
            text += "\t- ["+doc.details+"](https://www.ctan.org/tex-archive"+doc.href.remove("ctan:")+")\n";
        }
        return text;
    }

    QString showAllTopics(){
        QString text;
        for(CTANTopic topic : topics){
            text += "\t- "+topic.key+" : "+topic.details+"\n";
        }
        return text;
    }
};
Q_DECLARE_METATYPE(LatexPackageInfo)

class LatexRepository : public QObject
{
	Q_OBJECT

public:
	static LatexRepository *instance();

	enum DataSource { None, Static, Texlive, Miktex };

	DataSource dataSource();
	bool packageExists(const QString &name);
	QString shortDescription(const QString &name);
	TeXdocStatus docStatus(const QString &name);
	void updatePackageInfo(const QString &name, const TeXdocStatus &docStatus);
    QStringList availablePackages();
    static QString packageInfo(LatexPackageInfo package);
    QHash<QString, LatexPackageInfo> getPackageHash();

private:
	LatexRepository();
	LatexRepository(const LatexRepository &);
	LatexRepository &operator=(const LatexRepository &);

	bool loadStaticPackageList(const QString &file);
    // QString AuthorsDBFile;

	static LatexRepository *m_Instance;

	QHash<QString, LatexPackageInfo> packages; // name, short description
	DataSource m_dataSource;
};

#endif // LATEXREPOSITORY_H
