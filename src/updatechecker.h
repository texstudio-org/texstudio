#ifndef Header_UpdateChecker
#define Header_UpdateChecker

#include "mostQtHeaders.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "utilsVersion.h"
#include <QLocale>

class UpdateChecker : public QObject
{
	Q_OBJECT

public:
	~UpdateChecker();

	static UpdateChecker *instance();

	static QString lastCheckAsString();
	QString latestVersion() { return latestStableVersion.versionNumber; }  // returns the version number retrieved in last check(), empty if no check has been performed so far
	void autoCheck();
	void check(bool m_silent = true, int currentComboBoxUpdateLevel = -1);

signals:
	void dataParsed(QString versionNumber);
	void checkCompleted();

public slots:

private slots:
    void onRequestError(QNetworkReply::NetworkError code);
	void onRequestCompleted();

private:
	UpdateChecker();
	UpdateChecker(const UpdateChecker &);
	UpdateChecker &operator=(const UpdateChecker &);

	static UpdateChecker *m_Instance;

	QNetworkAccessManager *networkManager;
	bool silent; // do not show error or up-to-date messages

	Version latestStableVersion;
	Version latestReleaseCandidateVersion;
	Version latestDevVersion;

	void parseData(const QByteArray &data);
	void checkForNewVersion();
	void notify(QString message);
};

#endif // UPDATECHECKER_H
