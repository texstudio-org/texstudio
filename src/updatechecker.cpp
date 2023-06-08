#include "updatechecker.h"
#include "smallUsefulFunctions.h"
#include "utilsVersion.h"
#include "configmanager.h"
#include <QNetworkProxyFactory>
#include <QMutex>

UpdateChecker *UpdateChecker::m_Instance = nullptr;
int comboBoxUpdateLevel;

UpdateChecker::UpdateChecker() :
    QObject(nullptr), silent(true)
{
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	//networkManager = new QNetworkAccessManager();
    // activate networkManager only when directly needed as it causes network delays on mac (Bug 1717/1738)
    networkManager=nullptr;
}

UpdateChecker::~UpdateChecker()
{
    m_Instance = nullptr;
}

QString UpdateChecker::lastCheckAsString()
{
	QDateTime lastCheck = ConfigManager::getInstance()->getOption("Update/LastCheck").toDateTime();
	return lastCheck.isValid() ? QLocale().toString(lastCheck, QLocale::ShortFormat) : tr("Never", "last update");
}

void UpdateChecker::autoCheck()
{
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

void UpdateChecker::check(bool silent, int currentComboBoxUpdateLevel)
{
	// catch value if possible, s. comment at start of checkForNewVersion
	comboBoxUpdateLevel = currentComboBoxUpdateLevel;

	this->silent = silent;
    networkManager = new QNetworkAccessManager();
    QNetworkRequest request = QNetworkRequest(QUrl("https://api.github.com/repos/texstudio-org/texstudio/git/refs/tags"));
	request.setRawHeader("User-Agent", "TeXstudio Update Checker");
	QNetworkReply *reply = networkManager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(onRequestCompleted()));
	if (!silent)
#if QT_VERSION_MAJOR<6
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError(QNetworkReply::NetworkError)));
#else
        connect(reply, &QNetworkReply::errorOccurred,this, &UpdateChecker::onRequestError);
#endif
}

void UpdateChecker::onRequestError(QNetworkReply::NetworkError )
{
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (!reply) return;

	UtilsUi::txsCritical(tr("Update check failed with error:\n") + reply->errorString());

    networkManager->deleteLater();
    networkManager=nullptr;
}

void UpdateChecker::onRequestCompleted()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	if (!reply || reply->error() != QNetworkReply::NoError) return;

	QByteArray ba = reply->readAll();

	parseData(ba);
	if (comboBoxUpdateLevel > -2)  // if not About dialog
		checkForNewVersion();

    networkManager->deleteLater();
    networkManager=nullptr;
}

void UpdateChecker::parseData(const QByteArray &data)
{
    // parsing of github api result (tags)
    QString result=QString(data);
	QStringList items = Version::parseGitData(result);
    QStringList tags;
    foreach(const QString& item, items){
		int pos = item.indexOf("\"ref\":\"refs/tags/");	// "\"ref\":\"refs/tags/" has length 17
        if(pos>=0){
            QString zw = item.mid(pos+17, item.indexOf("\"", pos+17) - (pos+17));
//			qDebug() << zw;
            tags<<zw;
        }
    }
    bool rcFound = false;
    bool devFound = false;
    for(int j=tags.length()-1;j>=0;j--){
        QString tag=tags.value(j);
        QStringList parts = Version::stringVersion2Parts(tag);
//		qDebug() << parts[0] << parts[1] << parts[2] << parts[3];
		if (!parts.isEmpty()) {
            QString ver = parts[0];
            QString type = parts[1];
            int revision = parts[2].toInt();
            if (!rcFound && type.toLower() == "rc"){
                rcFound = true;
                Version v( ver, type, revision);
                latestReleaseCandidateVersion = v;
            }
            if (!devFound && ( type.toLower() == "beta" || type.toLower() == "alpha" )){
                devFound = true;
                Version v( ver, type, revision);
                latestDevVersion = v;
            }
            if (type.isEmpty() || type.toLower() == "stable"){
                Version v( ver, "stable", revision);
                latestStableVersion = v;
                if (latestStableVersion.isValid())
                    emit dataParsed(latestStableVersion.versionNumber);
                if (!latestDevVersion.isValid())
                    latestDevVersion = v;
                if (!latestReleaseCandidateVersion.isValid())
                    latestReleaseCandidateVersion = v;
                break; // all other versions are older, so abort after first release
            }
        }
    }
}

void UpdateChecker::checkForNewVersion()
{
	// updateLevel values from comboBoxUpdateLevel indices:
	// 0: stable, 1: release candidate, 2: development (alpha, beta)
	// Config dialog (check button) passes correct current index from dialog, so user can check with different settings without closing dialog
	// Auto check uses -1, since we do not have the current gui value. in this case we can stay with config value.
	// About dialog uses -2, so we can suppress Update dialog. But in this case this function isn't called.
	int updateLevel;
	if (comboBoxUpdateLevel > -1)
		updateLevel = comboBoxUpdateLevel;
	else // comboBoxUpdateLevel = -1
		updateLevel = ConfigManager::getInstance()->getOption("Update/UpdateLevel").toInt();

	bool checkReleaseCandidate = updateLevel >= 1;
	bool checkDevVersions = updateLevel >= 2;
	Version currentVersion = Version::current();
	QString downloadAddress = "https://texstudio.org";
	QString downloadAddressGit = "https://github.com/texstudio-org/texstudio/releases";

	if (!currentVersion.isValid() && !latestReleaseCandidateVersion.isValid() && !latestDevVersion.isValid()) {
		if (!silent) UtilsUi::txsWarning(tr("Update check failed (invalid update file format)."));
		return;
	}
	while (true) {  // single control loop, used be able to break the control flow when some new version is detected
		if (checkReleaseCandidate && !latestReleaseCandidateVersion.isEmpty()) {
			if (!latestReleaseCandidateVersion.isValid()) {
				if (!silent) UtilsUi::txsWarning(tr("Update check for release candidate failed (invalid update file format)."));
			}
			if (latestReleaseCandidateVersion > currentVersion && latestReleaseCandidateVersion > latestStableVersion) {
                notify(QString(tr("A new release candidate of TeXstudio is available.")+"<br><table><tr><td>"+
                                tr("Current version:")+"</td><td>%1</td></tr>"+
                                "<tr><td>"+tr("Latest stable version:")+"</td><td>%2</td></tr>"+
                               "<tr><td>"+tr("Release candidate:")+"</td><td>%3</td></tr></table><br><br>"+
                                tr("You can download it from the %1 TeXstudio website").arg(QString("<a href='%1'>").arg(downloadAddressGit))+"</a>."
                        )
						.arg(Version::versionToString(currentVersion),
							Version::versionToString(latestStableVersion),
                            Version::versionToString(latestReleaseCandidateVersion))
				);
				break;
			}
		}
		if (checkDevVersions && !latestDevVersion.isEmpty()) {
			if (!latestDevVersion.isValid()) {
				if (!silent) UtilsUi::txsWarning(tr("Update check for development version failed (invalid update file format)."));
			}
			if (latestDevVersion > currentVersion && (latestStableVersion.isEmpty() || latestDevVersion > latestStableVersion)) {
                notify(QString(tr("A new development version of TeXstudio is available.")+"<br><table><tr><td>"+
                                tr("Current version:")+"    </td><td>%1</td></tr>"+
                                "<tr><td>"+tr("Latest stable version:")+"</td><td>%2</td></tr>"+
                                "<tr><td>"+tr("Latest development version:")+"</td><td>%3</td></tr></table><br><br>"+
                                tr("You can download it from the %1 TeXstudio website").arg(QString("<a href='%1'>").arg(downloadAddressGit))+"</a>."
                        )
						.arg(Version::versionToString(currentVersion),
							Version::versionToString(latestStableVersion),
                            Version::versionToString(latestDevVersion))
				);
				break;
			}
		}
		if (!latestStableVersion.isEmpty()) {
			if (!latestStableVersion.isValid()) {
				if (!silent) UtilsUi::txsWarning(tr("Update check for stable version failed (invalid update file format)."));
			}
			if (latestStableVersion > currentVersion) {
                notify(QString(tr("A new stable version of TeXstudio is available.")+"<br><table><tr><td>"+
                                tr("Current version:")+"</td><td>%1</td></tr>"+
                                "<tr><td>"+tr("Latest stable version:")+"</td><td>%2</td></tr></table><br><br>"+
                                tr("You can download it from the %1 TeXstudio website").arg(QString("<a href='%1'>").arg(downloadAddressGit))+"</a>."
                        )
						.arg(Version::versionToString(currentVersion),
                            Version::versionToString(latestStableVersion))
				);
			} else {
				if (!silent) {
					UtilsUi::txsInformation(tr("Your TeXstudio version %1 is up-to-date.").arg(Version::versionToString(currentVersion)));
				}
			}
			break;
		} else {
            if (!silent) UtilsUi::txsInformation(tr("Failure to find current TeXstudio versions."));
		}
		break;
	}

	ConfigManager::getInstance()->setOption("Update/LastCheck", QDateTime::currentDateTime());
	emit checkCompleted();
}

void UpdateChecker::notify(QString message)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("TeXstudio Update"));
	msgBox.setTextFormat(Qt::RichText);
	msgBox.setText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
	msgBox.exec();
}

UpdateChecker *UpdateChecker::instance()
{
	static QMutex mutex;
	mutex.lock();
	if (!m_Instance)
		m_Instance = new UpdateChecker();
	mutex.unlock();
	return m_Instance;
}
