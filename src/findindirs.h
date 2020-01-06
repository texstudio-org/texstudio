#ifndef FINDINDIRS_H
#define FINDINDIRS_H

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
	/*!
	 * \brief     Creates a search object with search modifiers.
	 * \param[in] mostRecent From all matching files return the most recent one.
	 * \param[in] checkReadable A matching file must be readable.
	 * \param[in] resolveDir An absolute directory path that is used to turn
	 * loaded search directories into absolute ones. For each loaded
	 * directory a check is made if it is absolute. Absolute directories
	 * are used unchanged while relative directories have resolveDir
	 * prepended to them.
	 * \param[in] dirs Optional search directories to load into the search object.
	 * Multiple directories should be separated by the platform-specific
	 * directory separator.
	 */
	FindInDirs(bool mostRecent, bool checkReadable, const QString &resolveDir, const QString &dirs = "");
	/*!
	 * \brief     Load additional search directories into the search object.
	 * \param[in] dirs Search directories to load into the search object. Multiple
	 * directories should be separated by the platform-specific directory
	 * separator. Relative directory pathnames have resolveDir prepended
	 * to them.
	 */
	void loadDirs(const QString &dirs);
	/*!
	 * \brief Load additional search directories into the search object.
	 * \param[in] dirs Search directories to load into the search object. Relative
	 * directory pathnames have resolveDir prepended to them.
	 */
	void loadDirs(const QStringList &dirs);
	/*!
	 * \brief Searches for a given filename.
	 * \details Searches for a given filename. First a direct check for the specified
	 * filename is made in the current directory. If the specified filename
	 * is absolute then the current directory is ignored. If the direct check
	 * did not find a matching file, then the loaded search directories are
	 * checked one by one for the specified filename (ignoring any directory
	 * component of the searched filename.
	 * \param[in] pathname Searched pathname. After the initial direct check, the
	 * search in the loaded directories ignores the directory component of pathname.
	 * \return Returns the absolute pathname of the found file. If no matching
	 * file is found then an empty string ("") is returned.
	 */
	QString findAbsolute(const QString &pathname) const;

private:
	bool findCheckFile(const QFileInfo &fileInfo) const;

	bool m_mostRecent;
	bool m_checkReadable;
	QString m_resolveDir;
	QStringList m_absDirs;
};

#endif // FINDINDIRS_H
