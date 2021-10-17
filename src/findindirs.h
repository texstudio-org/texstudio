#ifndef Header_FindInDirs
#define Header_FindInDirs

#include "mostQtHeaders.h"

/*!
 * \brief   Search for a given filename in a specified list of directories
 * \details This class implements search for a given filename in a list of directories.
 * It also supports optional search modifiers for the search criteria.
 * TODO: Merge other file search functions (e.g. findResourceFile) into this class.
*/
class FindInDirs
{
public:
	FindInDirs(bool mostRecent, bool checkReadable, const QString &resolveDir, const QString &dirs = "");
	void loadDirs(const QString &dirs);
	void loadDirs(const QStringList &dirs);
	QString findAbsolute(const QString &pathname) const;

private:
	bool findCheckFile(const QFileInfo &fileInfo) const;

	bool m_mostRecent;
	bool m_checkReadable;
	QString m_resolveDir;
	QStringList m_absDirs;
};

#endif // FINDINDIRS_H
