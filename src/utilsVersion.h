#ifndef Header_UtilsVersion
#define Header_UtilsVersion

#define TEXSTUDIO "TeXstudio"


#define TXSVERSION "4.0.2"

#define TXSVERSION_NUMERIC 0x040002



//#define IS_DEVELOPMENT_VERSION (TXSVERSION_NUMERIC & 0x000001)
#define IS_DEVELOPMENT_VERSION 0 // odd numbers have not been used at all, git version gives a much clearer insight about the used version

extern const char *TEXSTUDIO_GIT_REVISION;

#ifdef QT_NO_DEBUG
#define COMPILED_DEBUG_OR_RELEASE "R"
#else
#define COMPILED_DEBUG_OR_RELEASE "D"
#endif

#include "mostQtHeaders.h"

int gitRevisionToInt(const char *);

class Version
{
public:
	enum VersionCompareResult {Invalid = -2, Lower = -1, Same = 0, Higher = 1};
	static VersionCompareResult compareStringVersion(const QString &v1, const QString &v2);
	static VersionCompareResult compareIntVersion(const QList<int> &v1, const QList<int> &v2);
	static QList<int> parseVersionNumber(const QString &versionNumber);
	static bool versionNumberIsValid(const QString &versionNumber);
    static int parseGitRevisionNumber(const QString &revision);

	Version() : revision(0) {}
	Version(QString number, int rev = 0) : versionNumber(number), revision(rev) {}
    Version(QString number, QString tp,int rev = 0) : versionNumber(number), type(tp), revision(rev) {}
	static Version current();

	QString platform;       // "win" or "mac" or "linux"
	QString versionNumber;  // "2.10.2"
	QString type;           // "stable", "release candidate" or "development"
    int revision;           // 5310, now changed to revision after tag as deliverd by "git describe"

	bool operator > (const Version &other) const;

	bool isEmpty() const;
	bool isValid() const;

};
#endif // UTILSVERSION_H
