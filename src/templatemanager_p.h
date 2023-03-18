#ifndef Header_Template_Manager_P
#define Header_Template_Manager_P

#include "mostQtHeaders.h"
#include "qjsondocument.h"
#include "templatemanager.h"

// Abstract base class for templates
class Template
{
public:
	virtual ~Template() { foreach (TemplateHandle *th, handles) { th->setTmpl(0); } }
	virtual QString name() const { return QString(); }
	virtual QString description() const { return QString(); }
	virtual QString author() const { return QString(); }
	virtual QString version() const { return QString(); }
	virtual QDate date() const { return QDate(); }
	virtual QString license() const { return QString(); }
	virtual QPixmap previewImage() const { return QPixmap(); }
	virtual QString file() const { return QString(); }
	virtual bool isEditable() const { return false; }
	virtual bool isMultifile() const { return file().endsWith(".zip"); }
	bool createInFolder(const QString &path);
	virtual QStringList filesToOpen() const { return QStringList(); }

	void ref(TemplateHandle *th) {
		handles.append(th);
		//qDebug() << handles.size() << ">" << th->file() << this;
	}
	void deref(TemplateHandle *th) {
		//qDebug() << handles.size() << "<" << th->file() << this;
		handles.removeOne(th); }

private:
	QList<TemplateHandle *> handles;
};


class LocalFileTemplate : public Template
{
public:
	friend class LocalFileTemplateResource;
	virtual QString name() const { return metaData["Name"]; }
	virtual QString description() const { return metaData["Description"]; }
	virtual QString author() const { return metaData["Author"]; }
	virtual QString version() const { return metaData["Version"]; }
	virtual QDate date() const;
	virtual QString license() const { return metaData["License"]; }
	virtual QPixmap previewImage() const { return QPixmap(imageFile()); }
	virtual QString file() const { return m_mainfile; }
	virtual bool isEditable() const { return m_editable; }
	virtual QStringList filesToOpen() const;

protected:
	LocalFileTemplate(QString mainfile);
	void init();
	virtual bool readMetaData() { return false; }
	virtual bool saveMetaData() { return false; }

	QHash<QString, QString> metaData;

private:
	QString imageFile() const;
	QString m_mainfile; // a single .tex file or a .zip for multiple files
	bool m_editable;
};

class OnlineFileTemplate : public Template
{
public:
    OnlineFileTemplate(QJsonDocument jsonDoc);
    virtual QString name() const { return m_dd["Name"].toString(); }
    virtual QString description() const { return m_dd["Description"].toString(); }
    virtual QString author() const { return m_dd["Author"].toString(); }
    virtual QString version() const { return m_dd["Version"].toString(); }
    virtual QString license() const { return m_dd["License"].toString(); }
    virtual QPixmap previewImage() const { return m_preview; }
    virtual QString file() const { return m_url; }
    virtual bool isEditable() const { return false; }
    virtual bool isMultifile() const { return file().endsWith(".zip"); }
    virtual QStringList filesToOpen() const;

    void setPreviewImage(QPixmap img) {m_preview=img;}
    void setURL(const QString& name) {m_url=name;}

protected:
    QJsonDocument m_jsonDoc;
    QJsonObject m_dd;
    QPixmap m_preview;
    QString m_url;
};


class LocalLatexTemplate : public LocalFileTemplate
{
public:
	friend class LocalLatexTemplateResource;
protected:
	virtual bool readMetaData();
	virtual bool saveMetaData();
private:
	LocalLatexTemplate(QString mainfile) : LocalFileTemplate(mainfile) { init(); }
};


class LocalTableTemplate : public LocalFileTemplate
{
public:
	friend class LocalTableTemplateResource;
protected:
	virtual bool readMetaData();
private:
	LocalTableTemplate(QString mainfile) : LocalFileTemplate(mainfile) { init(); }
};


class LocalFileTemplateResource : public QObject, public AbstractTemplateResource
{
	Q_OBJECT
	Q_INTERFACES(AbstractTemplateResource)
public:
	~LocalFileTemplateResource();
	virtual QList<TemplateHandle> getTemplates();
	virtual bool isAccessible();
	virtual QString name() { return m_name; }
	virtual QString description() { return m_description; }
	void setDescription(const QString &descr) { m_description = descr; }
	virtual QIcon icon() { return m_icon; }
	void setEditable(bool b);

protected:
	LocalFileTemplateResource(QString path, QStringList filters, QString name, QObject *parent = 0, QIcon icon=QIcon());
	virtual LocalFileTemplate* createTemplate(QString file) = 0;
	void update();

private:
	QString m_path;
	QStringList m_filters;
	QString m_name;
	QString m_description;
	QIcon m_icon;
	QList<LocalFileTemplate*> m_templates;
};

class LocalLatexTemplateResource : public LocalFileTemplateResource
{
	Q_OBJECT

public:
	LocalLatexTemplateResource(QString path, QString name, QObject *parent, QIcon icon = QIcon())
        : LocalFileTemplateResource(path, QStringList() << "*.tex" << "*.lytex" << "*.zip" << "*.ctx", name, parent, icon) { update(); }

protected:
	virtual LocalFileTemplate* createTemplate(QString file) { return new LocalLatexTemplate(file); }
};

class LocalTableTemplateResource : public LocalFileTemplateResource
{
	Q_OBJECT

public:
	LocalTableTemplateResource(QString path, QString name, QObject *parent, QIcon icon = QIcon())
		: LocalFileTemplateResource(path, QStringList() << "*.js", name, parent, icon) { update(); }

protected:
	virtual LocalFileTemplate* createTemplate(QString file) { return new LocalTableTemplate(file); }
};


#endif // TEMPLATEMANAGER_P_H
