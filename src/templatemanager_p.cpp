#include "templatemanager_p.h"
#include "JlCompress.h"
#include "smallUsefulFunctions.h"

/*** TemplateHandle **********************************************************/

// *INDENT-OFF* (astyle-config)
TemplateHandle::TemplateHandle(const TemplateHandle &th) : m_tmpl(nullptr) { setTmpl(th.m_tmpl); }
TemplateHandle::TemplateHandle(Template *tmpl) : m_tmpl(nullptr) { setTmpl(tmpl); }
TemplateHandle::~TemplateHandle() { setTmpl(nullptr); }
bool TemplateHandle::isValid() const         { return (m_tmpl); }
TemplateHandle& TemplateHandle::operator = (const TemplateHandle& th) {
	setTmpl(th.m_tmpl);
	return *this;
}

QString TemplateHandle::name() const         { return (m_tmpl) ? m_tmpl->name() : QString(); }
QString TemplateHandle::description() const  { return (m_tmpl) ? m_tmpl->description() : QString(); }
QString TemplateHandle::author() const       { return (m_tmpl) ? m_tmpl->author() : QString(); }
QString TemplateHandle::version() const      { return (m_tmpl) ? m_tmpl->version() : QString(); }
QDate TemplateHandle::date() const           { return (m_tmpl) ? m_tmpl->date() : QDate(); }
QString TemplateHandle::license() const      { return (m_tmpl) ? m_tmpl->license() : QString(); }
QPixmap TemplateHandle::previewImage() const { return (m_tmpl) ? m_tmpl->previewImage() : QPixmap(); }
QString TemplateHandle::file() const         { return (m_tmpl) ? m_tmpl->file() : QString(); }
bool TemplateHandle::isEditable() const      { return (m_tmpl) ? m_tmpl->isEditable() : false; }

bool TemplateHandle::isMultifile() const     { return (m_tmpl) ? m_tmpl->isMultifile() : false; }

bool TemplateHandle::createInFolder(const QString &path) const { return (m_tmpl) ? m_tmpl->createInFolder(path) : false; }
QStringList TemplateHandle::filesToOpen() const { return (m_tmpl) ? m_tmpl->filesToOpen() : QStringList(); }
// *INDENT-ON* (astyle-config)


void TemplateHandle::setTmpl(Template *tmpl)
{
	if ( m_tmpl ) m_tmpl->deref(this);
	m_tmpl = tmpl;
	if ( m_tmpl ) m_tmpl->ref(this);
}

/*** Template ****************************************************************/

bool Template::createInFolder(const QString &path)
{
	QDir dir(path);
	if (!dir.exists()) {
		bool created = dir.mkpath(".");
		if (!created) return false;
	} else {
		QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
		if (!entries.isEmpty()) {
			bool ok = UtilsUi::txsConfirmWarning(QCoreApplication::translate("TemplateManager", "The target folder is not empty. It is recommended to instantiate "
			                            "in new folders. Otherwise existing files may be overwritten. "
			                            "Do you wish to use this folder anyway?"));
			if (!ok) return false;
		}
	}

	if (!isMultifile()) {
		QFileInfo fi(file());
		QFileInfo target(dir, fi.fileName());
		return QFile::copy(file(), target.absoluteFilePath());
	} else {
		bool success = !JlCompress::extractDir(file(), dir.absolutePath()).isEmpty();
		return success;
	}
	return false;
}

/*** LocalFileTemplate *******************************************************/

QDate LocalFileTemplate::date() const
{
	QDate d;
	d = QDate::fromString(metaData["Date"], Qt::ISODate);
	if (!d.isValid())
		d = QDate::fromString(metaData["Date"], Qt::SystemLocaleShortDate);
	return d;
}

QStringList LocalFileTemplate::filesToOpen() const
{
	QStringList files;
	foreach (const QString & f, metaData["FilesToOpen"].split(";")) {
		QString ft(f.trimmed());
		if (!ft.isEmpty())
			files << ft;
	}
	return files;
}

LocalFileTemplate::LocalFileTemplate(QString mainfile) : m_mainfile(mainfile), m_editable(false) {}

void LocalFileTemplate::init()
{
	if (!readMetaData()) {
		metaData.insert("Name", QFileInfo(file()).baseName());
	}
}

QString LocalFileTemplate::imageFile() const
{
	QString fname = replaceFileExtension(m_mainfile, "png");
	return (QFileInfo(fname).exists()) ? fname : QString();
}

/*** LocalLatexTemplate ******************************************************/

bool LocalLatexTemplate::readMetaData()
{
	QFile f(replaceFileExtension(file(), "json"));
	if (!f.exists()) {
		f.setFileName(replaceFileExtension(file(), "meta")); // in a very early version of meta data .meta was used instead of .json
		if (!f.exists())
			return false;
	}

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		UtilsUi::txsWarning(TemplateManager::tr("You do not have read permission to this file:") + QString("\n%1").arg(f.fileName()));
		return false;
	}
	QTextStream in(&f);
	in.setCodec("UTF-8");
	return minimalJsonParse(in.readAll(), metaData);
}

bool LocalLatexTemplate::saveMetaData()
{
	QFile f(file());
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream out(&f);
	out.setCodec("UTF-8");
	out << "{\n";
	bool first = true;
	foreach (const QString &key, metaData.keys()) {
		if (first) {
			first = false;
		} else {
			out << ",\n";
		}
		out << formatJsonStringParam(key, metaData[key], 13);
	}
	out << "\n}";
	return true;
}

/*** LocalTableTemplate ******************************************************/

bool LocalTableTemplate::readMetaData()
{
	QString jsonData;

	QFile f(file());
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		UtilsUi::txsWarning(TemplateManager::tr("You do not have read permission to this file:") + QString("\n%1").arg(f.fileName()));
		return false;
	}
	jsonData = f.readLine();
	int col = jsonData.indexOf(QRegExp("\\s*var\\s+metaData\\s+=\\s+\\{"));
	if (col < 0) return false;
	jsonData = jsonData.mid(col);
	QString all = f.readAll();
	jsonData.append(all); // works with minimalJsonParse because it stops after the first top level {}
	// should check when switching to a real JSON parser. However with this it is
	// easy to extract var metaData = {}

	return minimalJsonParse(jsonData, metaData);
}


/*** LocalFileTemplateResource **********************************************/

LocalFileTemplateResource::LocalFileTemplateResource(QString path, QStringList filters, QString name, QObject *parent, QIcon icon)
	: QObject(parent), AbstractTemplateResource(), m_path(path), m_filters(filters), m_name(name), m_icon(icon)
{ }

LocalFileTemplateResource::~LocalFileTemplateResource()
{
	foreach (LocalFileTemplate *lft, m_templates)
		delete lft;
}

QList<TemplateHandle> LocalFileTemplateResource::getTemplates()
{
	QList<TemplateHandle> l;
	foreach (LocalFileTemplate *tmpl, m_templates)
		l.append(TemplateHandle(tmpl));
	return l;
}

bool LocalFileTemplateResource::isAccessible()
{
	QDir dir(m_path);
	return dir.exists() && dir.isReadable();
}

void LocalFileTemplateResource::setEditable(bool b)
{
	foreach (LocalFileTemplate *tmpl, m_templates) {
		tmpl->m_editable = b;
	}
}

void LocalFileTemplateResource::update()
{
	foreach (LocalFileTemplate *lft, m_templates)
		delete lft;
	m_templates.clear();

	QDir dir(m_path);
	foreach (QString fname, dir.entryList(m_filters, QDir::Files | QDir::Readable, QDir::Name)) {
		LocalFileTemplate *lft = createTemplate(QFileInfo(dir, fname).absoluteFilePath());
		if (lft)
			m_templates.append(lft);
	}
}

