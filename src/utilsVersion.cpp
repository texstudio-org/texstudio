#include "utilsVersion.h"
#include "mostQtHeaders.h"

QStringList levelList = {"alpha", "beta", "rc", "stable"};

/* parse string from git into data items. It has the following form:
 * [{...},{...},...,{...}]
 * where each {...} represents one data item of one txs version. Ex. for ...:
 * "ref":"refs/tags/1.8.1","node_id":"MDM6UmVmMTEyMzcwNzY1OnJlZnMvdGFncy8xLjguMQ==","url":"https://api.github.com/repos/texstudio-org/texstudio/git/refs/tags/1.8.1","object":{"sha":"ef685c7e85c6045c35e6c25580030ad6f548f5f0","type":"commit","url":"https://api.github.com/repos/texstudio-org/texstudio/git/commits/ef685c7e85c6045c35e6c25580030ad6f548f5f0"}
 * we assume that none of the literal strings contains braces (i.e. "{" and "}")
 */  
QStringList Version::parseGitData(const QString &data) {
	QStringList items;
	QString item;
	int level = 0;
	int start = -1;
	for(int idx=0; idx< data.length(); ++idx) {
		QString chr = data.at(idx);
		if (chr=="{") {
			level += 1;
			if (level==1)
				start = idx;
		}
		if (chr=="}") {
			level -= 1;
			if (level==0) {
				item = data.mid(start+1, idx-start-1); // without { and }
				items << item;
			}
		}
	}
	return items;
}

QStringList Version::stringVersion2Parts(const QString &str) {
	QRegExp rx("^((\\d+)(\\.\\d+)*)([a-zA-Z]+)?(\\d*)?(-(\\d+)-)?($|[^.])");	// version tag, ex: 4.3.0beta1, git revison, ex: 4.3.0beta1-24-g5c925a387

	if (rx.indexIn(str) == 0) {
		QString ver = rx.cap(1);
		QString type = rx.cap(4);
		QString revision = rx.cap(5);
		QString commitAfter = rx.cap(7);
		return QStringList({ver, type, revision, commitAfter});
	}
	return QStringList({});
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
/*!
 * \brief return current version
 * Version in utilsVersion.h takes precedence over git as git tag are not necessarily present or correct
 * If version is identical, take commitsafter/revision from git
 * \return
 */
Version Version::current()
{
    Version v;
    QStringList vp_base = stringVersion2Parts(TXSVERSION);
    if (!vp_base.isEmpty()) {
        v.versionNumber = vp_base[0];
        v.type = vp_base[1];
        if (v.type == "") v.type = "stable";
        v.revision = vp_base[2].toInt();
        v.commitsAfter = vp_base[3].toInt();
#if defined(Q_OS_WIN)
        v.platform =  "win";
#elif defined(Q_OS_MAC)
        v.platform = "mac";
#elif defined(Q_OS_LINUX)
        v.platform = "linux";
#endif
    }
    QStringList vp = stringVersion2Parts(TEXSTUDIO_GIT_REVISION);
	if (!vp.isEmpty()) {
        if(!v.versionNumber.isEmpty()){
            if(!vp[1].isEmpty()) v.type = vp[1];
            v.revision = vp[2].toInt();
            v.commitsAfter = vp[3].toInt();
        }
	}

	return v;
}

QString Version::versionToString(const Version &v)
{
	QString s;
	if (v.isEmpty())
		return "";
	else {
		s = v.versionNumber;
		if (!(v.type.toLower() == "stable") || v.revision > 0) {
			s += v.type + QString("%1").arg(v.revision);
		}
		if (v.commitsAfter > 0)
			s += QString("-%1").arg(v.commitsAfter);
	}
	return s;
}

bool Version::operator >(const Version &other) const
{
	VersionCompareResult res = compareStringVersion(versionNumber, other.versionNumber);
    if (res != Same)
        return (res == Higher);
    if (type.toLower() == other.type.toLower()){
        bool revisionLarger = (revision > other.revision) || (revision == other.revision && commitsAfter > other.commitsAfter);
        return revisionLarger;
    }
    int lvl = levelList.indexOf(type.toLower());
    int lvl_other = levelList.indexOf(other.type.toLower());
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
		&& commitsAfter >= 0;
}
