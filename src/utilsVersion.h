#ifndef Header_UtilsVersion
#define Header_UtilsVersion

#define TEXSTUDIO "TeXstudio"

#define TXSVERSION "4.5.3"

extern const char *TEXSTUDIO_GIT_REVISION;

#ifdef QT_NO_DEBUG
#define COMPILED_DEBUG_OR_RELEASE "R"
#else
#define COMPILED_DEBUG_OR_RELEASE "D"
#endif

#include "mostQtHeaders.h"

class Version
{
public:
	enum VersionCompareResult {Invalid = -2, Lower = -1, Same = 0, Higher = 1};
	static VersionCompareResult compareStringVersion(const QString &v1, const QString &v2);
	static VersionCompareResult compareIntVersion(const QList<int> &v1, const QList<int> &v2);
	static QStringList parseGitData(const QString &data);
	static QStringList stringVersion2Parts(const QString &str);
	static QList<int> parseVersionNumber(const QString &versionNumber);
    static int parseVersionNumberToInt(const QString &versionNumber);
	static bool versionNumberIsValid(const QString &versionNumber);
	static QString versionToString(const Version &v);
	Version() : revision(0), commitsAfter(0) {}
	Version(QString number, int rev = 0) : versionNumber(number), type(QString("stable")), revision(rev), commitsAfter(0) {}
    Version(QString number, QString tp, int rev = 0, int count = 0) : versionNumber(number), type(tp), revision(rev), commitsAfter(count) {}
    static Version current();

	QString platform;       // "win" or "mac" or "linux"
	QString versionNumber;  // "2.10.2"
	QString type;           // "stable", "rc", "beta", "alpha"
    int revision;           // 5310, now changed to revision after tag as delivered by "git describe"
	int commitsAfter;       // commitsAfter == 24 for dev version 4.3.0beta1-24-g5c925a387, -nn- is missing iff commitsAfter == 0

	bool operator > (const Version &other) const;

	bool isEmpty() const;
	bool isValid() const;

};
#endif // UTILSVERSION_H
