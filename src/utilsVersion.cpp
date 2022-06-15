#include "utilsVersion.h"
#include "mostQtHeaders.h"

QStringList levelList = {"alpha", "beta", "rc", "stable"};

int gitRevisionToInt(const char *)
{
// ex: 4.3.0beta1-24-g5c925a387
    QString s = QString(TEXSTUDIO_GIT_REVISION).split('-').value(1,"0");
	if (s.endsWith('+'))
		s = s.left(s.length() - 1);
	return s.toInt();
}

QList<int> Version::parseVersionNumber(const QString &versionNumber)
{
	QList<int> result;
	QStringList parts = versionNumber.split('.');
	if (parts.isEmpty())
		return result;  // empty
	QRegularExpression numberPart("^\\d+$");
	foreach (const QString &v, parts) {
		if (numberPart.match(v).hasMatch())
			result << v.toInt();
		else
			return QList<int>();
	}
	for (int i=result.count(); i < 3; i++) {
		result << 0;  // 1.0 is extended to 1.0.0
	}
	return result;
}

// accepts a or a.b or a.b.c where a, b, and c each a sequence of atleast 1 digits like 4711
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
	QRegExp rx("^((\\d+\\.)+(\\d+))([a-zA-Z]+)?(\\d*)?(-(\\d+)-)?");
	if (rx.indexIn(QString(TEXSTUDIO_GIT_REVISION)) == 0){
		QString type = rx.cap(4).toLower();
		int revision = rx.cap(5).toInt();
		QString cap7 = rx.cap(7);
		int commitsAfter;
		if (cap7 == "")
			commitsAfter = -1;
		else
			commitsAfter = cap7.toInt();
		Version v( TXSVERSION, type, revision, commitsAfter);
#if defined(Q_OS_WIN)
		v.platform =  "win";
#elif defined(Q_OS_MAC)
		v.platform = "mac";
#elif defined(Q_OS_LINUX)
		v.platform = "linux";
#endif
		return v;
	}
	Version v;
	return v;
}

QString Version::versionToString(const Version &v)
{
	QString s;
	if (v.isEmpty())
		return "";
	else {
		s = v.versionNumber;
		if (!(v.type == "stable") || v.revision > 0) {
			s += v.type + QString("%1").arg(v.revision);
		}
		if (v.commitsAfter > -1)
			s += QString("-%1").arg(v.commitsAfter);
	}
	return s;
}

bool Version::operator >(const Version &other) const
{
	VersionCompareResult res = compareStringVersion(versionNumber, other.versionNumber);
    if (res != Same)
        return (res == Higher);
    if (type == other.type){
        bool revisionLarger = (revision > other.revision || revision == other.revision && commitsAfter > other.commitsAfter);
        return revisionLarger;
    }
    int lvl = levelList.indexOf(type);
    int lvl_other = levelList.indexOf(other.type);
    return lvl > lvl_other;
}

bool Version::isEmpty() const
{
	return versionNumber.isEmpty() && type.isEmpty() && revision == 0 && commitsAfter == 0;
}

bool Version::isValid() const
{
	return versionNumberIsValid(versionNumber)
		&& levelList.indexOf(type.toLower()) > -1
		&& revision >= 0
		&& commitsAfter >= -1;
}
