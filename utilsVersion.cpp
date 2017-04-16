#include "utilsVersion.h"
#include "mostQtHeaders.h"

int hgRevisionToInt(const char *)
{
	QString s = QString(TEXSTUDIO_HG_REVISION).split(':').at(0);
	if (s.endsWith('+'))
		s = s.left(s.length() - 1);
	return s.toInt();
}

QList<int> Version::parseVersionNumber(const QString &versionNumber)
{
	QList<int> result;
	QRegExp terminatingChars("[\\s-]");
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
	return (parseVersionNumber(versionNumber).length() == 3);
}

// compares two versions strings
// Meaning of result: v1 [result] v2, e.g. v1 Older than v2
Version::VersionCompareResult Version::compareStringVersion(const QString &v1, const QString &v2)
{
	return compareIntVersion(parseVersionNumber(v1), parseVersionNumber(v2));
}

Version::VersionCompareResult Version::compareIntVersion(const QList<int> &v1, const QList<int> &v2)
{
	if (v1.length() != 3 || v2.length() != 3)
		return Invalid;
	for (int i=0; i<v1.count(); i++) {
		if (v1.at(i) < v2.at(i)) return Lower;
		else if (v1.at(i) > v2.at(i)) return Higher;
	}
	return Same;
}

Version Version::current()
{
	Version v(TXSVERSION);
	QString s = QString(TEXSTUDIO_HG_REVISION).split(':').at(0);
	if (s.endsWith('+'))
		s = s.left(s.length() - 1);
	v.revision = s.toInt();
#if defined(Q_OS_WIN)
	v.platform =  "win";
#elif defined(Q_OS_MAC)
	v.platform = "mac";
#elif defined(Q_OS_LINUX)
	v.platform = "linux";
#endif
	// v.type  // TODO currently not stored
	return v;
}

bool Version::operator >(const Version &other) const
{
	VersionCompareResult res = compareStringVersion(versionNumber, other.versionNumber);
	bool revisionLarger = (revision > 0 && other.revision > 0 && revision > other.revision);
	return (res == Higher || (res == Same && revisionLarger));
}

bool Version::isEmpty() const
{
	return versionNumber.isEmpty() && revision == 0;
}

bool Version::isValid() const
{
	return versionNumberIsValid(versionNumber);
}

