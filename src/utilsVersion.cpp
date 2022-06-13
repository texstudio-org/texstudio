#include "utilsVersion.h"
#include "mostQtHeaders.h"

int gitRevisionToInt(const char *)
{
    QString s = QString(TEXSTUDIO_GIT_REVISION).split('-').value(1,"0");
	if (s.endsWith('+'))
		s = s.left(s.length() - 1);
	return s.toInt();
}

QList<int> Version::parseVersionNumber(const QString &versionNumber)
{
	QList<int> result;
    QRegularExpression terminatingChars("[A-Za-z\\s-]");
	int len = versionNumber.indexOf(terminatingChars);
	QStringList parts = versionNumber.left(len).split('.');
	if (parts.isEmpty())
		return result;  // empty
	foreach (const QString &v, parts) {
		bool ok(true);
		result << v.toInt(&ok);
		if (!ok) {
			return QList<int>();
		}
	}
	for (int i=result.count(); i<=2; i++) {
		result << 0;  // 1.0 is extended to 1.0.0
	}
	return result;
}

bool Version::versionNumberIsValid(const QString &versionNumber)
{
	QList<int> parsedVersionNumber = parseVersionNumber(versionNumber);
    return parsedVersionNumber.length() == 3;
}


/*!
 * Return the revision number from a hg revision string, e.g. "1234:asassdasd" -> 1234.
 * Returns 0 if the input string is not a vailid hg revision string.
 */
int Version::parseGitRevisionNumber(const QString &revision)
{
    return revision.split('-')[1].toInt();
}

// compares two versions strings
// Meaning of result: v1 [result] v2, e.g. v1 Older than v2
Version::VersionCompareResult Version::compareStringVersion(const QString &v1, const QString &v2)
{
	return compareIntVersion(parseVersionNumber(v1), parseVersionNumber(v2));
}

Version::VersionCompareResult Version::compareIntVersion(const QList<int> &v1, const QList<int> &v2)
{
    if (v1.length() < 3 || v2.length() < 3)
		return Invalid;
    if (v1.length() > 4 || v2.length() > 4){
        return Invalid;
    }
	for (int i=0; i<v1.count(); i++) {
        if(i>=v2.count()) return Higher;
		if (v1.at(i) < v2.at(i)) return Lower;
		else if (v1.at(i) > v2.at(i)) return Higher;
	}
    if(v1.count()<v2.count()){
        return Lower;
    }
	return Same;
}

Version Version::current()
{
	Version v(TXSVERSION);
    QString s = QString(TEXSTUDIO_GIT_REVISION).split('-').value(1,"0");
	if (s.endsWith('+'))
		s = s.left(s.length() - 1);
	v.revision = s.toInt();
    if (QString(TEXSTUDIO_GIT_REVISION).contains("RC") || QString(TEXSTUDIO_GIT_REVISION).contains("rc")){
        v.type="rc";
    }
    if (QString(TEXSTUDIO_GIT_REVISION).contains("beta")){
        v.type = "beta";
    }
    if (QString(TEXSTUDIO_GIT_REVISION).contains("alpha")){
        v.type = "alpha";
    }
    if (v.type.isEmpty()){
		v.type = "stable";
	} else {
		v.type = "dev";
	}
#if defined(Q_OS_WIN)
	v.platform =  "win";
#elif defined(Q_OS_MAC)
	v.platform = "mac";
#elif defined(Q_OS_LINUX)
	v.platform = "linux";
#endif
	return v;
}

bool Version::operator >(const Version &other) const
{
	VersionCompareResult res = compareStringVersion(versionNumber, other.versionNumber);
    if(res!=Same)
        return (res == Higher);
    if(type==other.type){
        bool revisionLarger = (revision > 0 && other.revision > 0 && revision > other.revision);
        return revisionLarger;
    }
	QStringList levelList = {"dev", "alpha", "beta", "rc", "stable"};
    int lvl = levelList.indexOf(type);
    int lvl_other = levelList.indexOf(other.type);
    return lvl_other==0 && lvl==4 ? false : lvl>lvl_other; // special treatment a.b-dev > a.b stable but a.b-dev < a.b-beta/rc
}

bool Version::isEmpty() const
{
	return versionNumber.isEmpty() && revision == 0;
}

bool Version::isValid() const
{
	return versionNumberIsValid(versionNumber);
}

