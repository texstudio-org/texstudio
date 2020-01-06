#ifndef FINDINDIRS_H
#define FINDINDIRS_H

#include "mostQtHeaders.h"

//TODO: merge findResourceFile into this class
class FindInDirs
{
public:
	FindInDirs(bool mostRecent, const QString &resolveDir, const QString &dirs = "");
	void loadDirs(const QString &dirs);
	void loadDirs(const QStringList &dirs);
	void loadOneDir(const QString &dir);
	QString findAbsolute(const QString &pathname);

private:
	bool m_mostRecent;
	QString m_resolveDir;
	QStringList m_absDirs;
};

#endif // FINDINDIRS_H
