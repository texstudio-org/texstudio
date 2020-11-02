#include "sessionlist.h"
#include "configmanager.h"
#include "smallUsefulFunctions.h"


SessionList::SessionList(QMenu *menu, QObject *parent) : QObject(parent), m_menu(menu)
{
	m_config = dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
}

void SessionList::addFilenameToList(const QString &file)
{
	if (file.endsWith("lastSession.txss")) return;
	REQUIRE(m_config);
	QStringList files = m_config->getOption("Files/Recent Session Files").toStringList();
	int maxFiles = m_config->getOption("Files/Max Recent Sessions").toInt();
	bool changed = addMostRecent(file, files, maxFiles);
	if (changed) {
		m_config->setOption("Files/Recent Session Files", files);
		updateMostRecentMenu();
	}
}

/*
 * updates the most recent session entries in the menu
 */
void SessionList::updateMostRecentMenu()
{
	REQUIRE(m_config);
	QStringList files = m_config->getOption("Files/Recent Session Files").toStringList();
	REQUIRE(m_menu);
	QList<QAction *> actions = m_menu->actions();
	int i = 0;

	/* convention: session entries are actions with a data tag "session:<filename>" */
	foreach (const QString &file, files) {
		QAction *sessionAct;
		while (i < actions.count() && !actions[i]->data().toString().startsWith("session")) i++;
		if (i >= actions.count()) {
			sessionAct = m_menu->addAction("");
		} else {
			sessionAct = actions[i];
		}
        QString temp=QDir::toNativeSeparators(file);
        temp.replace("&","&&");
        sessionAct->setText(temp);
		sessionAct->setData("session:" + file);
		sessionAct->setVisible(true);
		connectUnique(sessionAct, SIGNAL(triggered()), this, SLOT(menuActionTriggered()));
		i++;
	}
	// disable remaining unused actions
	for (int ii=i+1; ii<actions.count(); ii++) {
		if (actions[ii]->data().toString().startsWith("session:"))
			actions[ii]->setVisible(false);
	}
}

void SessionList::menuActionTriggered()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
    QString filename = act->data().toString().remove(QRegularExpression("^session:"));
	emit loadSessionRequest(filename);
	addFilenameToList(filename);
}
