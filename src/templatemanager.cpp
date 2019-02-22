#include "templatemanager.h"
#include "templatemanager_p.h"
#include "templateselector.h"
#include "mostQtHeaders.h"
#include "configmanager.h"

QString TemplateManager::configBaseDir;

TemplateManager::TemplateManager(QObject *parent) :
	QObject(parent)
{
}

QString TemplateManager::builtinTemplateDir()
{
#ifdef Q_OS_MAC
	QString fn = "/Applications/texstudio.app/Contents/Resources/";
	if (!QDir(fn).isReadable()) { // fallback if program is not installed
		fn = QCoreApplication::applicationDirPath();
		fn.chop(6);
		fn += "/Resources/";
	}
	if (!QDir(fn).isReadable()) { // fallback if program is not packaged as app (e.g. debug build )
		return QCoreApplication::applicationDirPath() + "/templates/";
	}
	return fn;
#endif
#ifdef Q_OS_WIN
	return QCoreApplication::applicationDirPath() + "/templates/";
#else
#if !defined(PREFIX)
#define PREFIX ""
#endif
#ifndef Q_OS_MAC
	QString fn = PREFIX"/share/texstudio/";
	if (!QDir(fn).isReadable()) { // fallback if program is not installed (e.g. debug build )
		fn = QCoreApplication::applicationDirPath() + "/templates/";
	}
	return fn;
#endif
#endif
}

bool TemplateManager::ensureUserTemplateDirExists()
{
	QDir d(userTemplateDir());
	if (!d.exists()) {
		if (!d.mkpath(userTemplateDir())) {
			qDebug() << "Creation of userTemplateDir failed:" << userTemplateDir();
			return false;
		}
	}
	return true;
}

// Originally user templates were stored whereever the user wanted and maintained in the option "User/Templates".
// This behavior has now been changed to always store user templates in [config]/templates/user/ The advantage is
// that we don't have to maintain the template list and it's not lost when resetting the configuration.
// This function allows to move existing templates to the the new location.
void TemplateManager::checkForOldUserTemplates()
{
	ConfigManagerInterface *cfg = ConfigManager::getInstance();
	if (!cfg) return;
	QStringList userTemplateList = cfg->getOption("User/Templates").toStringList();
	if (!userTemplateList.isEmpty()) {
		bool move = UtilsUi::txsConfirmWarning(tr("TeXstudio found user templates in deprecated locations.\n"
		                                 "From now on user templates are hosted at\n%1\n"
		                                 "Should TeXstudio move the existing user templates there?\n"
		                                 "If not, they will not be available via the Make Template dialog.").arg(userTemplateDir()));
		if (move) {
			foreach (const QString &fname, userTemplateList) {
				QFileInfo fi(fname);
				if (!fi.exists()) {
					userTemplateList.removeOne(fname);
					continue;
				}
				QString newName = userTemplateDir() + fi.fileName();
				if (!QFile::copy(fname, newName)) {
					UtilsUi::txsWarning(tr("Copying template from\n%1\nto\n%2\nfailed.").arg(fname).arg(newName));
				} else {
					if (!QFile::remove(fname)) {
						UtilsUi::txsInformation(tr("File\n%1\n could not be removed.").arg(fname));
					}
					userTemplateList.removeOne(fname);
				}
			}
		}
		if (!userTemplateList.isEmpty()) {
			if (UtilsUi::txsConfirmWarning(tr("There are still unmoved templates. Should TeXstudio stop monitoring them?"))) {
				userTemplateList.clear();
			}
		}
		cfg->setOption("User/Templates", userTemplateList);
	}
}


// Creates a new template resource from the information of the XML node.
// The parent is the template manager. You may reparent the resource later.
// returns 0 if there is no valid resource info in the node
AbstractTemplateResource *TemplateManager::createResourceFromXMLNode(const QDomElement &resElem)
{
	if (resElem.tagName() != "Resource") {
		qDebug() << "Not an XML Resource Node";
        return nullptr;
	}

	QString name, path, description;
	bool isEditable = false;
	QIcon icon;
	QDomElement elem = resElem.firstChildElement("Path");
	if (!elem.isNull())
		path = elem.text();
	elem = resElem.firstChildElement("Description");
	if (!elem.isNull())
		description = elem.text();
	elem = resElem.firstChildElement("Editable");
	if (!elem.isNull())
		isEditable = elem.text() == "1" || elem.text().toLower() == "true";
	elem = resElem.firstChildElement("Icon");
	QStringList iconNames;
	if (!elem.isNull())
		iconNames << elem.text();
	// locate the icon in the resource path
	QDir d(path);
	iconNames << "LatexTemplateResource.svg" << "LatexTemplateResource.svgz" << "LatexTemplateResource.png";
	foreach (const QString &name, iconNames) {
		if (d.exists(name)) {
			icon = QIcon(d.absoluteFilePath(name));
			break;
		}
	}

	elem = resElem.firstChildElement("Name");
	if (!elem.isNull())
		name = elem.text();
	if (name.isEmpty())
		name = tr("Unnamed Resource");
	else if (name == "%Builtin") {
		name = tr("Builtin");
		path = builtinTemplateDir();
		description = tr("Basic template files shipped with TeXstudio.");
		isEditable = false;
		icon = QIcon(":/images/appicon.png");
	} else if (name == "%User") {
		name = tr("User");
		path = userTemplateDir();
		description = tr("User created template files");
		isEditable = true;
		icon = QIcon(":/images-ng/user.svgz");
	}

	if (QFileInfo(path).isDir()) {
		LocalLatexTemplateResource *tplResource = new LocalLatexTemplateResource(path, name, this, icon);
		tplResource->setDescription(description);
		tplResource->setEditable(isEditable);
		return tplResource;
	}
    return nullptr;
}

QList<AbstractTemplateResource *> TemplateManager::resourcesFromXMLFile(const QString &filename)
{
	QList<AbstractTemplateResource *> list;

	QFile file(filename);
	if (!file.open(QFile::ReadOnly)) {
		qDebug() << "unable to open template resource file" << filename;
		return list;
	}

	QDomDocument domDoc;
	QString errorMsg;
	int errorLine;
	if (!domDoc.setContent(&file, &errorMsg, &errorLine)) {
		file.close();
		qDebug() << "invalid xml file format" << filename;
		qDebug() << "at line" << errorLine << ":" << errorMsg;
		return list;
	}

	QDomElement root = domDoc.documentElement();
	if (root.tagName() != "LatexTemplateResources") {
		qDebug() << "not a template resource configuration file" << filename;
		return list;
	}

	QDomElement elem = root.firstChildElement("Resource");
	while (!elem.isNull()) {
		AbstractTemplateResource *tplResource = createResourceFromXMLNode(elem);
		if (tplResource) {
			list.append(tplResource);
		}
		elem = elem.nextSiblingElement("Resource");
	}
	return list;
}

TemplateSelector *TemplateManager::createLatexTemplateDialog()
{
	TemplateSelector *dialog = new TemplateSelector(tr("Select LaTeX Template"));
	connect(dialog, SIGNAL(editTemplateRequest(TemplateHandle)), SLOT(editTemplate(TemplateHandle)));
	connect(dialog, SIGNAL(editTemplateInfoRequest(TemplateHandle)), SLOT(editTemplateInfo(TemplateHandle)));

	QFileInfo fi(QDir(configBaseDir), "template_resources.xml");
	if (!fi.exists()) {
		QFile::copy(":/utilities/template_resources.xml", fi.absoluteFilePath()); // set up default
	}

	QList<AbstractTemplateResource *> l = resourcesFromXMLFile(fi.absoluteFilePath());
	foreach (AbstractTemplateResource *res, l) {
		dialog->addResource(res);
	}
	return dialog;
}

bool TemplateManager::tableTemplateDialogExec()
{
	TemplateSelector dialog(tr("Select Table Template"));
	dialog.hideFolderSelection();
	connect(&dialog, SIGNAL(editTemplateRequest(TemplateHandle)), SLOT(editTemplate(TemplateHandle)));
	connect(&dialog, SIGNAL(editTemplateInfoRequest(TemplateHandle)), SLOT(editTemplateInfo(TemplateHandle)));
	LocalTableTemplateResource userTemplates(configBaseDir, tr("User"), this, QIcon(":/images-ng/user.svgz"));
	LocalTableTemplateResource builtinTemplates(builtinTemplateDir(), "Builtin", this, QIcon(":/images/appicon.png"));
	dialog.addResource(&userTemplates);
	dialog.addResource(&builtinTemplates);

	bool ok = dialog.exec();
	if (ok) {
		selectedFile = dialog.selectedTemplate().file();
	}
	return ok;
}

void TemplateManager::editTemplate(TemplateHandle th)
{
	emit editRequested(th.file());
}

void TemplateManager::editTemplateInfo(TemplateHandle th)
{
	QString fname = th.file();
	if (!fname.endsWith(".js")) {
		fname = replaceFileExtension(fname, "json");
	}
	emit editRequested(fname);
}
