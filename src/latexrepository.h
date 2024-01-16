#ifndef Header_Latex_Repository
#define Header_Latex_Repository

#include "mostQtHeaders.h"
enum TeXdocStatus { Undefined, Available, Unavailable };

struct CTANAuthor
{
    QString Id;
    QString Name;
    QString FamilyName;
    bool Active;
};

struct CTANCopyright
{
    QString OwnerId;
    QString Year;
};

struct CTANVersion
{
    QString Number;
    QDate Date;
};

struct CTANDescription
{
    QString Language;
    QString Text;
};

struct CTANDocumentation
{
    QString Language;
    QString Details;
    QString Href;
};

struct CTANLicense
{
    QString Key;
    QString Name;
    bool IsFree;
};

struct CTANTopic
{
    QString Key;
    QString Details;
};

class LatexPackageInfo
{
public:
    LatexPackageInfo(const QString &name = QString(), const QString &shortDescr = QString(), bool inst = false, TeXdocStatus status = Undefined)
	{
        this->Name = name;
        Caption = shortDescr;
		installed = inst;
		docStatus = status;
	}

    QString Id;
    QString Name;
    QString Caption;
    QList<CTANAuthor> Authors;
    QList<CTANCopyright> Copyright;
    QList<CTANLicense> Licences;
    CTANVersion Version;
    QList<CTANDescription> Descriptions;
    QList<CTANDocumentation> Documentations;
    QString CtanLink;
    QList<CTANTopic> Topics;
    QString Miktex;
    QString Texlive;
    QStringList Also;
    bool installed;
    TeXdocStatus docStatus;

    QString AuthorsFullName(){
        QString text;
        for(CTANAuthor author : Authors){
            text += "\t- "+author.Name+" "+author.FamilyName+"\n";
        }
        return text;
    }

    QString ShowAllCopyrights(){
        QString text;
        for(CTANCopyright copyright : Copyright){
            if(!copyright.OwnerId.isEmpty() || !copyright.Year.isEmpty()){
                text += "\t- "+copyright.OwnerId+", "+copyright.Year+"\n";
            }
        }
        return text;
    }

    QString ShowAllLicenses(){
        QString text;
        QString isFree;
        for(CTANLicense license : Licences){
            isFree = (license.IsFree) ? QObject::tr(" (Free)") : QObject::tr(" (Not free)");
            text += "\t- "+license.Key+", "+license.Name+isFree+"\n";
        }
        return text;
    }

    QString ShowAllDocumentation(){
        QString text;
        for(CTANDocumentation doc : Documentations){
            text += "\t- ["+doc.Details+"](https://www.ctan.org/tex-archive"+doc.Href.remove("ctan:")+")\n";
        }
        return text;
    }

    QString ShowAllTopics(){
        QString text;
        for(CTANTopic topic : Topics){
            text += "\t- "+topic.Key+" : "+topic.Details+"\n";
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
    QString AuthorsDBFile;

	static LatexRepository *m_Instance;

	QHash<QString, LatexPackageInfo> packages; // name, short description
	DataSource m_dataSource;
};

#endif // LATEXREPOSITORY_H
