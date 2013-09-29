#ifndef UPDATECHECKER_T_H
#define UPDATECHECKER_T_H
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
	void versionCompare_data() {
		QTest::addColumn<QString>("ver1");
		QTest::addColumn<QString>("ver2");
		QTest::addColumn<int>("expectedResult");

		QTest::newRow("equal") << "2.3" << "2.3" << (int) UpdateChecker::Same;
		QTest::newRow("equal2") << "2.3.1" << "2.3.1" << (int) UpdateChecker::Same;
		QTest::newRow("equal3") << "2" << "2.0" << (int) UpdateChecker::Same;
		QTest::newRow("equal4") << "2.3" << "2.3.0" << (int) UpdateChecker::Same;
		QTest::newRow("minor1") << "2.4" << "2.3" << (int) UpdateChecker::Higher;
		QTest::newRow("minor2") << "2.3" << "2.4" << (int) UpdateChecker::Lower;
		QTest::newRow("major1") << "3" << "2.4" << (int) UpdateChecker::Higher;
		QTest::newRow("major2") << "3.0" << "2.4" << (int) UpdateChecker::Higher;
		QTest::newRow("major3") << "3.1" << "2.4" << (int) UpdateChecker::Higher;
		QTest::newRow("major4") << "3.1" << "2.4" << (int) UpdateChecker::Higher;
		QTest::newRow("major4") << "3.0" << "2.4.2" << (int) UpdateChecker::Higher;
		QTest::newRow("revision1") << "2.4.1" << "2.4" << (int) UpdateChecker::Higher;
		QTest::newRow("revision2") << "2.4.2" << "2.4.1" << (int) UpdateChecker::Higher;
		QTest::newRow("revision3") << "2.4" << "2.4.1" << (int) UpdateChecker::Lower;
		QTest::newRow("revision4") << "2.4.1" << "2.4.2" << (int) UpdateChecker::Lower;
		QTest::newRow("invalid") << "2.4b" << "2.4" << (int) UpdateChecker::Invalid;
	}

	void versionCompare() {
		QFETCH(QString, ver1);
		QFETCH(QString, ver2);
		QFETCH(int, expectedResult);

		int result = UpdateChecker::versionCompare(ver1, ver2);
		QEQUAL(result, expectedResult);
	}

	void getLatestVersion() {
		if (!allTests) {
			qDebug("skipped getLatestVersion test");
			return;
		}
		QSignalSpy spy(UpdateChecker::instance(), SIGNAL(checkCompleted()));
		UpdateChecker::instance()->check();
		// wait until check is completed
		QTime time;
		time.start();
		while (spy.count() == 0 && time.elapsed() < 5000) {
			QTest::qWait(100);
		}
		if (spy.count() > 0) {
			QRegExp rxVersion("(\\d+)(?:\\.(\\d+))+");
			QVERIFY( rxVersion.exactMatch(UpdateChecker::instance()->latestVersion()) );
		} else {
			QWARN("Timeout while trying to retrieve latest version from server.");
		}
	}
private:
	bool allTests;
};

#endif
#endif // UPDATECHECKER_T_H
