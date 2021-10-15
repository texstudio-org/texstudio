#ifndef Header_UtilsVersion_T
#define Header_UtilsVersion_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "utilsVersion.h"
#include "testutil.h"
#include <QtTest/QtTest>

class VersionTest: public QObject{
	Q_OBJECT
public:
	VersionTest(bool executeAllTests) : allTests(executeAllTests) {}
private slots:
	void compareStringVersion_data() {
		QTest::addColumn<QString>("ver1");
		QTest::addColumn<QString>("ver2");
		QTest::addColumn<int>("expectedResult");

		QTest::newRow("equal") << "2.3" << "2.3" << (int) Version::Same;
		QTest::newRow("equal2") << "2.3.1" << "2.3.1" << (int) Version::Same;
		QTest::newRow("equal3") << "2" << "2.0" << (int) Version::Same;
		QTest::newRow("equal4") << "2.3" << "2.3.0" << (int) Version::Same;
		QTest::newRow("minor1") << "2.4" << "2.3" << (int) Version::Higher;
		QTest::newRow("minor2") << "2.3" << "2.4" << (int) Version::Lower;
		QTest::newRow("major1") << "3" << "2.4" << (int) Version::Higher;
		QTest::newRow("major2") << "3.0" << "2.4" << (int) Version::Higher;
		QTest::newRow("major3") << "3.1" << "2.4" << (int) Version::Higher;
		QTest::newRow("major4") << "3.1" << "2.4" << (int) Version::Higher;
		QTest::newRow("major4") << "3.0" << "2.4.2" << (int) Version::Higher;
		QTest::newRow("revision1") << "2.4.1" << "2.4" << (int) Version::Higher;
		QTest::newRow("revision2") << "2.4.2" << "2.4.1" << (int) Version::Higher;
		QTest::newRow("revision3") << "2.4" << "2.4.1" << (int) Version::Lower;
		QTest::newRow("revision4") << "2.4.1" << "2.4.2" << (int) Version::Lower;
		QTest::newRow("invalid") << "2.4b" << "2.4" << (int) Version::Invalid;
		QTest::newRow("twodigit") << "2.10.0" << "2.9.4" << (int) Version::Higher;
		QTest::newRow("additionalText") << "2.10.0 Release Candidate" << "2.10.0" << (int) Version::Same;
        QTest::newRow("additionalText2") << "2.10.0-RC" << "2.10.0" << (int) Version::Same;
	}

	void compareStringVersion() {
		QFETCH(QString, ver1);
		QFETCH(QString, ver2);
		QFETCH(int, expectedResult);

		int result = Version::compareStringVersion(ver1, ver2);
		QEQUAL(result, expectedResult);
	}

	void isValid_data() {
		QTest::addColumn<QString>("version");
		QTest::addColumn<bool>("valid");

		QTest::newRow("valid1") << "2.3" << true;
		QTest::newRow("valid2") << "2.3.1" << true;
		QTest::newRow("valid3") << "3.0.0 (Development)" << true;
		QTest::newRow("valid4") << "3.0.0-RC" << true;
		QTest::newRow("valid5") << "3.0.0b" << false;
		QTest::newRow("valid6") << "" << false;
	}

	void isValid() {
		QFETCH(QString, version);
		QFETCH(bool, valid);
		QEQUAL(Version(version).isValid(), valid);
	}
	
	void operatorLarger_data() {
		QTest::addColumn<QString>("ver1");
		QTest::addColumn<int>("rev1");
		QTest::addColumn<QString>("ver2");
		QTest::addColumn<int>("rev2");
		QTest::addColumn<bool>("expectedResult");

		QTest::newRow("larger1") << "2.3" << 100 << "2.3" << 100 << false;
		QTest::newRow("larger2") << "2.3" << 100 << "2.3" << 200 << false;
		QTest::newRow("larger3") << "2.3" << 200 << "2.3" << 100 << true;
		QTest::newRow("larger4") << "2.4" << 100 << "2.3" << 100 << true;
		QTest::newRow("larger5") << "2.4" << 100 << "2.3" << 200 << true;
		QTest::newRow("larger6") << "2.4" << 200 << "2.3" << 100 << true;
		QTest::newRow("larger7") << "2.2" << 100 << "2.3" << 100 << false;
		QTest::newRow("larger8") << "2.2" << 100 << "2.3" << 200 << false;
		QTest::newRow("larger9") << "2.2" << 200 << "2.3" << 100 << false;
	}

	void operatorLarger() {
		QFETCH(QString, ver1);
		QFETCH(int, rev1);
		QFETCH(QString, ver2);
		QFETCH(int, rev2);
		QFETCH(bool, expectedResult);

		QEQUAL(Version(ver1, rev1) > Version(ver2, rev2), expectedResult);
	}

    void operatorLarger2_data() {
        QTest::addColumn<QString>("ver1");
        QTest::addColumn<QString>("tp1");
        QTest::addColumn<int>("rev1");
        QTest::addColumn<QString>("ver2");
        QTest::addColumn<QString>("tp2");
        QTest::addColumn<int>("rev2");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("larger1") << "2.3.1" << "stable" << 100 << "2.3" << "stable" << 100 << true;
        QTest::newRow("larger2") << "2.3.2" << "stable" << 100 << "2.3.1" << "stable" << 100 << true;
        QTest::newRow("larger3") << "2.4.1" << "stable" << 100 << "2.3.4" << "stable" << 100 << true;
        QTest::newRow("larger4") << "2.4.1" << "stable" << 100 << "2.4.1" << "beta" << 100 << true;
        QTest::newRow("larger5") << "2.4.1" << "stable" << 100 << "2.4.1" << "release candidate" << 100 << true;
        QTest::newRow("larger6") << "2.4.1" << "stable" << 100 << "2.4.1" << "development" << 100 << false;
        QTest::newRow("larger7") << "2.4.1" << "beta" << 2 << "2.4.1" << "beta" << 1 << true;
        QTest::newRow("larger8") << "2.4.1" << "release candidate" << 1 << "2.4.1" << "beta" << 5 << true;
        QTest::newRow("larger9") << "2.4.1" << "release candidate" << 1 << "2.4.1" << "development" << 5 << true;
        QTest::newRow("larger10") << "2.4.1" << "beta" << 1 << "2.4.1" << "development" << 5 << true;

    }

    void operatorLarger2() {
        QFETCH(QString, ver1);
        QFETCH(QString, tp1);
        QFETCH(int, rev1);
        QFETCH(QString, ver2);
        QFETCH(QString, tp2);
        QFETCH(int, rev2);
        QFETCH(bool, expectedResult);

        QEQUAL(Version(ver1, tp1, rev1) > Version(ver2, tp2, rev2), expectedResult);
    }

private:
	bool allTests;
};

#endif // QT_NO_DEBUG
#endif // UTILSVERSION_T_H
