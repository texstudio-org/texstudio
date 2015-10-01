#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include "mostQtHeaders.h"
#include <QNetworkAccessManager>

struct VersionInfo {
	VersionInfo() : revision(0) {}
	QString platform; // "win" or "mac" or "linux"
	QString versionNumber;  // "2.10.2"
	QString type;     // "stable" or "dev"
	int revision;     // 5310
};

class UpdateChecker : public QObject
{
	Q_OBJECT
public:
	~UpdateChecker();
	
	static UpdateChecker *instance();

	enum VersionCompareResult {Invalid=-2, Lower=-1, Same=0, Higher=1};
	static VersionCompareResult versionCompare(const QString& v1, const QString& v2);

	static QString lastCheckAsString();
	QString latestVersion() {return latestStableVersion.versionNumber;} // returns the version number retrieved in last check(), empty if no check has been performed so far

	void autoCheck();
	void check(bool m_silent = true);
signals:
	void checkCompleted();
public slots:
	
private slots:
	void onRequestError();
	void onRequestCompleted();
private:
	UpdateChecker();
	UpdateChecker(const UpdateChecker &);
	UpdateChecker& operator=(const UpdateChecker &);

	static UpdateChecker *m_Instance;

	QNetworkAccessManager *networkManager;
	bool silent; // do not show error or up-to-date messages
	
	VersionInfo latestStableVersion;
	VersionInfo latestDevVersion;

	void parseData(const QByteArray &data);
	void checkForNewVersion();
	void notify(QString message);
};

#endif // UPDATECHECKER_H
