#ifndef FINDINDIRS_H
#define FINDINDIRS_H

#include "mostQtHeaders.h"

//TODO: merge findResourceFile into this class
class FindInDirs
{
public:
	FindInDirs(bool mostRecent, bool checkReadable, const QString &resolveDir, const QString &dirs = "");
	void loadDirs(const QString &dirs);
	void loadDirs(const QStringList &dirs);
	QString findAbsolute(const QString &pathname);

private:
	bool findCheckFile(const QFileInfo &fileInfo) const;

	bool m_mostRecent;
	bool m_checkReadable;
	QString m_resolveDir;
	QStringList m_absDirs;
};

#endif // FINDINDIRS_H
