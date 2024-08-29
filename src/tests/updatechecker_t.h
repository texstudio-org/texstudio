#ifndef Header_UpdateChecker_T
#define Header_UpdateChecker_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "updatechecker.h"
#include "testutil.h"
#include <QtTest/QtTest>

class UpdateCheckerTest: public QObject{
	Q_OBJECT
public:
	UpdateCheckerTest(bool executeAllTests) : allTests(executeAllTests) {}
private slots:
	void getLatestVersion() {
		if (!allTests) {
			qDebug("skipped getLatestVersion test");
			return;
		}
		QSignalSpy spy(UpdateChecker::instance(), SIGNAL(checkCompleted()));
		UpdateChecker::instance()->check();
		// wait until check is completed
        QElapsedTimer time;
		time.start();
		while (spy.count() == 0 && time.elapsed() < 5000) {
			QTest::qWait(100);
		}
		if (spy.count() > 0) {
            QRegularExpression rxVersion("^(\\d+)(?:\\.(\\d+))+$");
            QVERIFY( UpdateChecker::instance()->latestVersion().indexOf(rxVersion) == 0 );
		} else {
            qWarning("Timeout while trying to retrieve latest version from server.");
		}
	}
private:
	bool allTests;
};

#endif
#endif // UPDATECHECKER_T_H
