#include "templatemanager.h"
#include "mostQtHeaders.h"
#include "configmanager.h"

QString TemplateManager::userTemplateDir;

TemplateManager::TemplateManager(QObject *parent) :
	QObject(parent)
{
}

bool TemplateManager::ensureUserTemplateDirExists() {
	QDir d(userTemplateDir);
	if (!d.exists()) {
		if (!d.mkpath(userTemplateDir)) {
			qDebug() << "Creation of userTemplateDir failed:" << userTemplateDir;
			return false;
		}
	}
	return true;
}

// Originally user templates were stored whereever the user wanted and maintained in the option "User/Templates".
// This behavior has now been changed to always store user templates in [config]/templates/user/ The advantage is
// that we don't have to maintain the template list and it's not lost when resetting the configuration.
// This function allows to move existing templates to the the new location.
void TemplateManager::checkForOldUserTemplates() {
	ConfigManagerInterface *cfg = ConfigManager::getInstance();
	if (!cfg) return;
	QStringList userTemplateList = cfg->getOption("User/Templates").toStringList();
	if (!userTemplateList.isEmpty()) {
		bool move = txsConfirmWarning(tr("TeXstudio found user templates in deprecated locations.\n"
							"From now on user templates are hosted at\n%1\n"
							"Should TeXstudio move the existing user templates there?"
										 "If not, they will not be available via the Make Template dialog.").arg(userTemplateDir));
		if (move) {
			foreach (const QString &fname, userTemplateList) {
				QFileInfo fi(fname);
				if (!fi.exists()) continue;
				QString newName = userTemplateDir + fi.fileName();
				if (!QFile::copy(fname, newName)) {
					txsWarning(tr("Copying template from\n%1\nto\n%2\nfailed.").arg(fname).arg(newName));
				} else {
					if (!QFile::remove(fname)) {
						txsInformation(tr("File\n%1\n could not be removed.").arg(fname));
					}
					userTemplateList.removeOne(fname);
				}
			}
		}
		if (!userTemplateList.isEmpty()) {
			if (txsConfirmWarning(tr("There are still unmoved templates. Should TeXstudio stop monitoring them?"))) {
				userTemplateList.clear();
			}
		}
		cfg->setOption("User/Templates", userTemplateList);
	}
}
