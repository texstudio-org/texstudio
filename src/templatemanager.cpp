#include "templatemanager.h"
#include "templatemanager_p.h"
#include "templateselector.h"
#include "mostQtHeaders.h"
#include "configmanager.h"
#include <QLibraryInfo>

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
    QStringList paths;

#if QT_VERSION_MAJOR>=6
    paths << QLibraryInfo::path(QLibraryInfo::PrefixPath)+"/share/texstudio/";
#else
    paths << PREFIX"/share/texstudio/";
#endif
    paths << "/usr/share/texstudio/"<< "/usr/local/share/texstudio/";
    paths<<QCoreApplication::applicationDirPath() + "/templates/";
    QString fn;
    for(const QString &pathName:paths){
        if (QDir(pathName).isReadable()) {
            fn=pathName;
            break;
        }
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
                    UtilsUi::txsWarning(tr("Copying template from\n%1\nto\n%2\nfailed.").arg(fname,newName));
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

TemplateSelector *TemplateManager::createLatexTemplateDialog()
{
	TemplateSelector *dialog = new TemplateSelector(tr("Select LaTeX Template"));
    dialog->setCachingDir(configBaseDir+"cachedTemplates");
	connect(dialog, SIGNAL(editTemplateRequest(TemplateHandle)), SLOT(editTemplate(TemplateHandle)));
	connect(dialog, SIGNAL(editTemplateInfoRequest(TemplateHandle)), SLOT(editTemplateInfo(TemplateHandle)));

    LocalLatexTemplateResource *builtinTemplates= new LocalLatexTemplateResource(builtinTemplateDir(), tr("Builtin"), this, QIcon(":/images/appicon.png"));
    LocalLatexTemplateResource *userTemplates= new LocalLatexTemplateResource(userTemplateDir(), tr("User"), this, getRealIcon("user"));
    QString description = tr("Basic template files shipped with TeXstudio.");
    builtinTemplates->setDescription(description);
    description = tr("User created template files");
    userTemplates->setDescription(description);
    userTemplates->setEditable(true);
    dialog->addResource(builtinTemplates);
    dialog->addResource(userTemplates);
    // add online category
    dialog->addOnlineRepository();

	return dialog;
}

bool TemplateManager::tableTemplateDialogExec()
{
	TemplateSelector dialog(tr("Select Table Template"));
	dialog.hideFolderSelection();
	connect(&dialog, SIGNAL(editTemplateRequest(TemplateHandle)), SLOT(editTemplate(TemplateHandle)));
	connect(&dialog, SIGNAL(editTemplateInfoRequest(TemplateHandle)), SLOT(editTemplateInfo(TemplateHandle)));
	LocalTableTemplateResource userTemplates(configBaseDir, tr("User"), this, getRealIcon("user"));
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
