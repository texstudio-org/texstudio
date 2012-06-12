#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include "mostQtHeaders.h"
#include <QNetworkAccessManager>

class UpdateChecker : public QObject
{
	Q_OBJECT
public:
	static UpdateChecker *instance();

	enum VersionCompareResult {Invalid=-2, Lower=-1, Same=0, Higher=1};
	static VersionCompareResult versionCompare(const QString& v1, const QString& v2);

	static QString lastCheckAsString();

	void autoCheck();
	void check(bool silent = true);
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
	static QRegExp rxVersion;

	QNetworkAccessManager *networkManager;
	bool silent; // do not show error or up-to-date messages

	void parseData(const QByteArray &data);
};

#endif // UPDATECHECKER_H
