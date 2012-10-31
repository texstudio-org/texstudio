#include "templatemanager_p.h"
#include "smallUsefulFunctions.h"

/*** TemplateHandle **********************************************************/

TemplateHandle::TemplateHandle(const TemplateHandle &th) : m_tmpl(0) { setTmpl(th.m_tmpl); }
TemplateHandle::TemplateHandle(Template *tmpl) : m_tmpl(0) { setTmpl(tmpl); }
TemplateHandle::~TemplateHandle() { setTmpl(0); }
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

void TemplateHandle::setTmpl(Template *tmpl) {
	if ( m_tmpl ) m_tmpl->deref(this);
	m_tmpl = tmpl;
	if ( m_tmpl ) m_tmpl->ref(this);
}


/*** LocalFileTemplate *******************************************************/

QDate LocalFileTemplate::date() const {
	QDate d;
	d = QDate::fromString(metaData["Date"], Qt::ISODate);
	if (!d.isValid())
		d = QDate::fromString(metaData["Date"], Qt::SystemLocaleShortDate);
	return d;
}

LocalFileTemplate::LocalFileTemplate(QString mainfile) : m_mainfile(mainfile), m_editable(false) {}

void LocalFileTemplate::init() {
	if (!readMetaData()) {
		metaData.insert("Name", QFileInfo(file()).baseName());
	}
}

QString LocalFileTemplate::imageFile() const {
	QString fname = replaceFileExtension(m_mainfile, "png");
	return (QFileInfo(fname).exists()) ? fname : QString();
}

/*** LocalLatexTemplate ******************************************************/

bool LocalLatexTemplate::readMetaData() {
	QFile f(replaceFileExtension(file(), "json"));
	if (!f.exists()) {
		f.setFileName(replaceFileExtension(file(), "meta")); // in a very early version of meta data .meta was used instead of .json
		if (!f.exists())
			return false;
	}

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		txsWarning(TemplateManager::tr("You do not have read permission to this file:")+QString("\n%1").arg(f.fileName()));
		return false;
	}
	return minimalJsonParse(f.readAll(), metaData);
}

bool LocalLatexTemplate::saveMetaData() {
	QFile f(file());
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream out(&f);
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

bool LocalTableTemplate::readMetaData() {
	QString jsonData;

	QFile f(file());
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		txsWarning(TemplateManager::tr("You do not have read permission to this file:")+QString("\n%1").arg(f.fileName()));
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


/*** LocalFileTemplateRessource **********************************************/

LocalFileTemplateRessource::LocalFileTemplateRessource(QString path, QStringList filters, QString name, QObject *parent, QIcon icon)
	: QObject(parent), AbstractTemplateRessource(), m_path(path), m_filters(filters), m_name(name), m_icon(icon)
{ }

LocalFileTemplateRessource::~LocalFileTemplateRessource() {
	foreach (LocalFileTemplate *lft, m_templates)
		delete lft;
}

QList<TemplateHandle> LocalFileTemplateRessource::getTemplates() {
	QList<TemplateHandle> l;
	foreach (LocalFileTemplate *tmpl, m_templates)
		l.append(TemplateHandle(tmpl));
	return l;
}

bool LocalFileTemplateRessource::isAccessible() {
	QDir dir(m_path);
	return dir.exists() && dir.isReadable();
}

void LocalFileTemplateRessource::setEditable(bool b) {
	foreach (LocalFileTemplate *tmpl, m_templates) {
		tmpl->m_editable = b;
	}
}

void LocalFileTemplateRessource::update() {
	foreach (LocalFileTemplate *lft, m_templates)
		delete lft;
	m_templates.clear();

	QDir dir(m_path);
	foreach (QString fname, dir.entryList(m_filters, QDir::Files | QDir::Readable, QDir::Name)) {
		LocalFileTemplate * lft = createTemplate(QFileInfo(dir, fname).absoluteFilePath());
		if (lft)
			m_templates.append(lft);
	}
}


