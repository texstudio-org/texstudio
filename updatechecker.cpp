#include "updatechecker.h"
#include "smallUsefulFunctions.h"
#include "configmanager.h"
#include <QNetworkReply>
#include <QNetworkProxyFactory>
#include <QMutex>

UpdateChecker * UpdateChecker::m_Instance = 0;

UpdateChecker::UpdateChecker() :
	QObject(0), silent(true)
{
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	networkManager = new QNetworkAccessManager();
}

UpdateChecker::~UpdateChecker()
{
	m_Instance = 0;
}

// compares two versions strings
// Meaning of result: v1 [result] v2, e.g. v1 Older than v2
UpdateChecker::VersionCompareResult UpdateChecker::versionCompare(const QString &v1, const QString &v2) {
	QStringList v1parts = v1.split(' ')[0].split('.');
	QStringList v2parts = v2.split(' ')[0].split('.');

	for (int i=v1parts.count(); i<v2parts.count(); i++) {
		v1parts.append("0");
	}
	for (int i=v2parts.count(); i<v1parts.count(); i++) {
		v2parts.append("0");
	}

	for (int i=0; i<v1parts.count(); i++) {
		bool ok;
		int n1 = v1parts.at(i).toInt(&ok);
		if (!ok) return Invalid;
		int n2 = v2parts.at(i).toInt(&ok);
		if (!ok) return Invalid;
		if (n1 < n2) return Lower;
		else if (n1 > n2) return Higher;
	}
	return Same;
}

QString UpdateChecker::lastCheckAsString() {
	QDateTime lastCheck = ConfigManager::getInstance()->getOption("Update/LastCheck").toDateTime();
	return lastCheck.isValid() ? lastCheck.toString("d.M.yyyy hh:mm") : tr("Never", "last update");
}

void UpdateChecker::autoCheck() {
	ConfigManagerInterface *cfg  = ConfigManager::getInstance();
	bool autoCheck = cfg->getOption("Update/AutoCheck").toBool();
	if (autoCheck) {
		QDateTime lastCheck = cfg->getOption("Update/LastCheck").toDateTime();
		int checkInterval = cfg->getOption("Update/AutoCheckInvervalDays").toInt();
		if (!lastCheck.isValid() || lastCheck.addDays(checkInterval) < QDateTime::currentDateTime()) {
			check();
		}
	}

}

void UpdateChecker::check(bool silent) {
	this->silent = silent;
	QNetworkRequest request = QNetworkRequest(QUrl("http://texstudio.sourceforge.net/update/txsUpdate.xml"));
	request.setRawHeader("User-Agent", "TeXstudio Update Checker");
	QNetworkReply *reply = networkManager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(onRequestCompleted()));
	if (!silent)
		connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError()));
}

void UpdateChecker::onRequestError() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (!reply) return;

	txsCritical(tr("Update check failed with error:\n") + reply->errorString());
}

void UpdateChecker::onRequestCompleted()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (!reply || reply->error() != QNetworkReply::NoError) return;

	QByteArray ba = reply->readAll();
	parseData(ba);
	checkForNewVersion();
}

void UpdateChecker::parseData(const QByteArray &data) {
	QDomDocument domDocument;
	if (domDocument.setContent(data)){
		QDomElement root = domDocument.documentElement();
		if (root.tagName() != "versions") {
			if (!silent) txsWarning(tr("Update check  ddddd failed (invalid update file format)."));
			return;
		}
		
		latestStableVersion = VersionInfo();
		latestDevVersion = VersionInfo();
		QDomNodeList nodes = root.elementsByTagName("version");
		for (int i=0; i<nodes.count(); i++) {
			QDomElement elem = nodes.at(i).toElement();
			VersionInfo v;
			v.platform = elem.attribute("platform");
			v.versionNumber = elem.attribute("number");
			v.type = elem.attribute("type");
			v.revision = elem.attribute("revision").toInt();
#if defined(Q_OS_WIN)
			if (v.platform != "win") continue;
#elif defined(Q_OS_MAC)
			if (v.platform != "mac") continue;
#else
			if (v.platform != "linux") continue;
#endif
			if (v.type == "stable") {
				latestStableVersion = v;
			} else if (v.type == "development") {
				latestDevVersion = v;
			}
		}
	}
}

void UpdateChecker::checkForNewVersion() {
	bool checkDevVersions = ConfigManager::getInstance()->getOption("Update/AutoCheckIncludeDevVersion").toBool();

	if (checkDevVersions) {
		VersionCompareResult res = versionCompare(latestDevVersion.versionNumber, latestStableVersion.versionNumber);
		if (res == Higher || (res == Same && latestDevVersion.revision > latestStableVersion.revision)) {
			res = versionCompare(latestDevVersion.versionNumber, TXSVERSION);
			if (res == Invalid) {
				if (!silent) txsWarning(tr("Update check for development version failed (invalid update file format)."));
				return;
			} else {
				QString s = QString(TEXSTUDIO_HG_REVISION).split(':').at(0);
				if (s.endsWith('+')) 
					s = s.left(s.length() -1);
				int revision = s.toInt();
				if (res == Higher || (res == Same && latestDevVersion.revision > revision)) {
					notify(QString(tr(
						"A new version of TeXstudio is available.<br>"
						"<table><tr><td>Current version:</td><td>%1 (%2)</td></tr>"
						"<tr><td>Latest stable version:</td><td>%3 (%4)</td></tr>"
						"<tr><td>Latest development version:</td><td>%5 (%6)</td></tr>"
						"</table><br><br>"
						"You can download it from the <a href='%7'>TeXstudio website</a>."
						)).arg(TXSVERSION).arg(revision)
						  .arg(latestStableVersion.versionNumber).arg(latestStableVersion.revision)
						  .arg(latestDevVersion.versionNumber).arg(latestDevVersion.revision)
						  .arg("http://texstudio.sourceforge.net")
					);
					return;
				}
			}
		}
	}
	
	VersionCompareResult res = versionCompare(latestStableVersion.versionNumber, TXSVERSION);
	if (res == Invalid) {
		if (!silent) txsWarning(tr("Update check failed (invalid update file format)."));
		return;
	}
	if (res == Higher) {
		notify(QString(tr(
			"A new version of TeXstudio is available.<br>"
			"<table><tr><td>Current version:</td><td>%1</td></tr>"
			"<tr><td>Latest stable version:</td><td>%2</td></tr>"
			"</table><br><br>"
			"You can download it from the <a href='%3'>TeXstudio website</a>."
			)).arg(TXSVERSION).arg(latestStableVersion.versionNumber).arg("http://texstudio.sourceforge.net")
		);
	} else {
		if (!silent) txsInformation(tr("TeXstudio is up-to-date."));
	}

	ConfigManager::getInstance()->setOption("Update/LastCheck", QDateTime::currentDateTime());
	emit checkCompleted();
}

void UpdateChecker::notify(QString message) {
	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("TeXstudio Update"));
	msgBox.setTextFormat(Qt::RichText);
	msgBox.setText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

UpdateChecker *UpdateChecker::instance() {
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new UpdateChecker();
	mutex.unlock();
	return m_Instance;
}


