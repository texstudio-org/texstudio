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
	void parseGitData_data() {
		QTest::addColumn<QString>("gitData");
		QTest::addColumn<QStringList>("list");
		QTest::addColumn<bool>("valid");

		// s. issue #2244
		QTest::newRow("parseGitData")
			<< QString( "[{\"ref\":\"refs/tags/3.1.2\",\"object\":{...}},")
					+ "{\"ref\":\"refs/tags/4.0.0alpha1\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha2\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha3\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha4\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha5\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha6\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha7\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0alpha8\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0beta1\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0beta2\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0beta3\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0rc1\",\"object\":{...}},"
					+ "{\"ref\":\"refs/tags/4.0.0rc2\",\"object\":{...}}]"
			<< QStringList({
					"\"ref\":\"refs/tags/3.1.2\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha1\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha2\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha3\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha4\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha5\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha6\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha7\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0alpha8\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0beta1\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0beta2\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0beta3\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0rc1\",\"object\":{...}",
					"\"ref\":\"refs/tags/4.0.0rc2\",\"object\":{...}"
			})
			<< true;
	}

	void parseGitData() {
		QFETCH(QString, gitData);
		QFETCH(QStringList, list);
		QFETCH(bool, valid);
		QEQUAL(Version::parseGitData(gitData) == list, valid);
	}

	void parseVersionNumber_data() {
		QTest::addColumn<QString>("version");
		QTest::addColumn<QList<int>>("vList");
		QTest::addColumn<bool>("valid");

		QTest::newRow("parseVersionNumber1") << "2.3" << QList<int>({2,3,0}) << true;
		QTest::newRow("parseVersionNumber2") << "" << QList<int>() << true;
		QTest::newRow("parseVersionNumber3") << "12.3.11" << QList<int>({12,3,11}) << true;
		QTest::newRow("parseVersionNumber4") << "4" << QList<int>({4,0,0}) << true;
		QTest::newRow("parseVersionNumber5") << "-4.0.0" << QList<int>() << true;
		QTest::newRow("parseVersionNumber6") << "4.5.6dev" << QList<int>() << true;
		QTest::newRow("parseVersionNumber7") << "4..6" << QList<int>() << true;
		QTest::newRow("parseVersionNumber8") << "4.5." << QList<int>() << true;
		QTest::newRow("parseVersionNumber9") << "2.3.1.8" << QList<int>({2,3,1,8}) << true;
	}

	void parseVersionNumber() {
		QFETCH(QString, version);
		QFETCH(QList<int>, vList);
		QFETCH(bool, valid);
		QEQUAL(Version::parseVersionNumber(version) == vList, valid);
	}

    void parseVersionNumberToInt_data() {
        QTest::addColumn<QString>("version");
        QTest::addColumn<int>("result");

        QTest::newRow("parseVersionNumber1") << "2.3" << 0x00020300;
        QTest::newRow("parseVersionNumber2") << "" << 0;
        QTest::newRow("parseVersionNumber3") << "12.3.11" << 0x000C030B;
        QTest::newRow("parseVersionNumber4") << "4" << 0x00040000;
        QTest::newRow("parseVersionNumber5") << "-4.0.0" << 0;
        QTest::newRow("parseVersionNumber6") << "4.5.6dev" << 0;
        QTest::newRow("parseVersionNumber7") << "4..6" << 0;
        QTest::newRow("parseVersionNumber8") << "4.5." << 0;
        QTest::newRow("parseVersionNumber9") << "2.3.1.8" << 0;
    }

    void parseVersionNumberToInt() {
        QFETCH(QString, version);
        QFETCH(int, result);
        QEQUAL(Version::parseVersionNumberToInt(version),result);
    }

	void stringVersion2Parts_data() {
		QTest::addColumn<QString>("version");
		QTest::addColumn<QStringList>("parts");
		QTest::addColumn<bool>("valid");

		QTest::newRow("versionParts1") << "4" << QStringList({"4","","",""}) << true;
		QTest::newRow("versionParts2") << "4.3.0beta1" << QStringList({"4.3.0","beta","1",""}) << true;
		QTest::newRow("versionParts3") << "4.3.0" << QStringList({"4.3.0","","",""}) << true;
		QTest::newRow("versionParts4") << "4.3.0beta1-24-g5c925a387" << QStringList({"4.3.0","beta","1","24"}) << true;
		QTest::newRow("versionParts5") << "4.3.0.beta1" << QStringList({}) << true;
		QTest::newRow("versionParts6") << "4.3.0.beta1-24-g5c925a387" << QStringList({}) << true;
	}

	void stringVersion2Parts() {
		QFETCH(QString, version);
		QFETCH(QStringList, parts);
		QFETCH(bool, valid);
		QEQUAL(Version::stringVersion2Parts(version) == parts, valid);
	}

	void versionToString_data() {
		QTest::addColumn<QString>("version");
		QTest::addColumn<QString>("type");
		QTest::addColumn<int>("rev");
		QTest::addColumn<int>("commits");
		QTest::addColumn<QString>("vString");
		QTest::addColumn<bool>("valid");

		QTest::newRow("versionToString1") << "2.3" << "stable" << 0 << 0 << "2.3" << true;
		QTest::newRow("versionToString2") << "2.3.1" << "stable" << 1 << 0 << "2.3.1stable1" << true;
		QTest::newRow("versionToString3") << "3.0.0" << "rc" << 1 << 0 << "3.0.0rc1" << true;
		QTest::newRow("versionToString4") << "3.0.0" << "beta" << 2 << 0 << "3.0.0beta2" << true;
		QTest::newRow("versionToString5") << "3.0.1" << "alpha" << 0 << 0 << "3.0.1alpha0" << true;
		QTest::newRow("versionToString6") << "3.0.1" << "alpha" << 1 << 33 << "3.0.1alpha1-33" << true;
		QTest::newRow("versionToString7") << "3.0.1" << "alpha" << 1 << 0 << "3.0.1alpha1" << true;
	}

	void versionToString() {
		QFETCH(QString, version);
		QFETCH(QString, type);
		QFETCH(int, rev);
		QFETCH(int, commits);
		QFETCH(QString, vString);
		QFETCH(bool, valid);
		QEQUAL(Version::versionToString(Version(version,type,rev,commits)) == vString, valid);
	}

	void compareStringVersion_data() {
		QTest::addColumn<QString>("ver1");
		QTest::addColumn<QString>("ver2");
		QTest::addColumn<int>("expectedResult");

		QTest::newRow("equal0") << "2" << "2.0.0" << (int) Version::Same;
		QTest::newRow("equal1") << "2.3" << "2.3" << (int) Version::Same;
		QTest::newRow("equal2") << "2.3.1" << "2.3.1" << (int) Version::Same;
		QTest::newRow("equal3") << "2" << "2.0" << (int) Version::Same;
		QTest::newRow("equal4") << "2.3" << "2.3.0" << (int) Version::Same;
		QTest::newRow("minor1") << "2.4" << "2.3" << (int) Version::Higher;
		QTest::newRow("minor2") << "2.3" << "2.4" << (int) Version::Lower;
		QTest::newRow("major1") << "3" << "2.4" << (int) Version::Higher;
		QTest::newRow("major2") << "3.0" << "2.4" << (int) Version::Higher;
		QTest::newRow("major3") << "3.1" << "2.4" << (int) Version::Higher;
		QTest::newRow("major4") << "3.2" << "2.4" << (int) Version::Higher;
		QTest::newRow("major4") << "3.0" << "2.4.2" << (int) Version::Higher;
		QTest::newRow("revision1") << "2.4.1" << "2.4" << (int) Version::Higher;
		QTest::newRow("revision2") << "2.4.2" << "2.4.1" << (int) Version::Higher;
		QTest::newRow("revision3") << "2.4" << "2.4.1" << (int) Version::Lower;
		QTest::newRow("revision4") << "2.4.1" << "2.4.2" << (int) Version::Lower;
		QTest::newRow("invalid") << "2.4b" << "2.4" << (int) Version::Invalid;
		QTest::newRow("twodigit") << "2.10.0" << "2.9.4" << (int) Version::Higher;
		QTest::newRow("additionalText") << "2.10.0 Release Candidate" << "2.10.0" << (int) Version::Invalid;
        QTest::newRow("additionalText2") << "2.10.0-RC" << "2.10.0" << (int) Version::Invalid;
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
		QTest::newRow("valid3") << "3.0.0 (Development)" << false;
		QTest::newRow("valid4") << "3.0.0-RC" << false;
		QTest::newRow("valid5") << "3.0.0b" << false;
		QTest::newRow("valid6") << "" << false;
		QTest::newRow("valid7") << "-3.0.0" << false;
	}

	void isValid() {
		QFETCH(QString, version);
		QFETCH(bool, valid);
		QEQUAL(Version(version).isValid(), valid);
	}

	void isValid2_data() {
		QTest::addColumn<QString>("version");
		QTest::addColumn<QString>("type");
		QTest::addColumn<int>("rev");
		QTest::addColumn<int>("commits");
		QTest::addColumn<bool>("valid");

		QTest::newRow("valid2.1") << "2.3" << "stable" << 0 << 0 << true;
		QTest::newRow("valid2.2") << "2.3.1" << "Stable" << 1 << 0 << true;
		QTest::newRow("valid2.3") << "3.0.0" << "development" << 1 << 1 << false;
		QTest::newRow("valid2.4") << "3.0.0" << "RC" << 1 << 0 << true;
		QTest::newRow("valid2.5") << "3.0.0" << "beta" << 2 << 0 << true;
		QTest::newRow("valid2.6") << "3.0.1" << "alpha" << 0 << 0 << true;
		QTest::newRow("valid2.7") << "3.0.1" << "alpha" << -1 << 0 << false;
		QTest::newRow("valid2.8") << "3.0.1" << "alpha" << 1 << -2 << false;
		QTest::newRow("valid2.9") << "2.3.1" << "" << 1 << 0 << false;
	}

	void isValid2() {
		QFETCH(QString, version);
		QFETCH(QString, type);
		QFETCH(int, rev);
		QFETCH(int, commits);
		QFETCH(bool, valid);
		QEQUAL(Version(version,type,rev,commits).isValid(), valid);
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
        QTest::addColumn<int>("commits1");
        QTest::addColumn<QString>("ver2");
        QTest::addColumn<QString>("tp2");
        QTest::addColumn<int>("rev2");
        QTest::addColumn<int>("commits2");
        QTest::addColumn<bool>("expectedResult");

        QTest::newRow("larger1")  << "2.3.1" << "stable" <<   0 <<  0   << "2.3.0" << "stable" <<   0 <<  0 << true;
        QTest::newRow("larger2")  << "2.3.2" << "stable" << 100 <<  0   << "2.3.1" << "stable" << 100 <<  0 << true;
        QTest::newRow("larger3")  << "2.4.1" << "stable" << 100 <<  0   << "2.3.4" << "stable" << 100 <<  0 << true;
        QTest::newRow("larger4")  << "2.4.1" << "stable" << 100 <<  0   << "2.4.1" << "beta"   << 100 <<  0 << true;
        QTest::newRow("larger5")  << "2.4.1" << "stable" << 100 <<  0   << "2.4.1" << "rc"     << 100 <<  0 << true;
        QTest::newRow("larger6")  << "2.4.1" << "stable" << 100 <<  0   << "2.4.1" << "stable" << 100 <<  0 << false;
        QTest::newRow("larger7")  << "2.4.1" << "beta"   <<   2 <<  0   << "2.4.1" << "beta"   <<   1 <<  0 << true;
        QTest::newRow("larger8")  << "2.4.1" << "rc"     <<   1 <<  0   << "2.4.1" << "beta"   <<   5 <<  0 << true;
        QTest::newRow("larger9")  << "2.4.1" << "rc"     <<   1 <<  5   << "2.4.1" << "rc"     <<   1 <<  0 << true;
        QTest::newRow("larger10") << "2.4.1" << "beta"   <<   1 <<  0   << "2.4.1" << "beta"   <<   1 << 17 << false;

    }

    void operatorLarger2() {
        QFETCH(QString, ver1);
        QFETCH(QString, tp1);
        QFETCH(int, rev1);
        QFETCH(int, commits1);
        QFETCH(QString, ver2);
        QFETCH(QString, tp2);
        QFETCH(int, rev2);
        QFETCH(int, commits2);
        QFETCH(bool, expectedResult);

        QEQUAL(Version(ver1, tp1, rev1, commits1) > Version(ver2, tp2, rev2, commits2), expectedResult);
    }

private:
	bool allTests;
};

#endif // QT_NO_DEBUG
#endif // UTILSVERSION_T_H
