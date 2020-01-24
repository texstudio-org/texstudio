#include "findindirs.h"
#include "utilsSystem.h"

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
FindInDirs::FindInDirs(bool mostRecent, bool checkReadable, const QString &resolveDir, const QString &dirs) :
	m_mostRecent(mostRecent),
	m_checkReadable(checkReadable),
	m_resolveDir(resolveDir)
{
	Q_ASSERT(QDir::isAbsolutePath(resolveDir));
	if (!dirs.isEmpty()) {
		loadDirs(dirs);
	}
}

/*!
 * \brief     Load additional search directories into the search object.
 * \param[in] dirs Search directories to load into the search object. Multiple
 * directories should be separated by the platform-specific directory
 * separator. Relative directory pathnames have resolveDir prepended
 * to them.
 */
void FindInDirs::loadDirs(const QString &dirs)
{
	loadDirs(splitPaths(dirs));
}

/*!
 * \brief Load additional search directories into the search object.
 * \param[in] dirs Search directories to load into the search object. Relative
 * directory pathnames have resolveDir prepended to them.
 */
void FindInDirs::loadDirs(const QStringList &dirs)
{
	foreach(const QString &oneDir, dirs) {
		m_absDirs.push_back(
			QDir::isAbsolutePath(oneDir) ?
			oneDir :
			m_resolveDir + QDir::separator() + oneDir
		);
	}
}

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
QString FindInDirs::findAbsolute(const QString &pathname) const
{
	QFileInfo pathInfo(pathname);
	QFileInfo mrInfo;
	if (findCheckFile(pathInfo)) {
		if (m_mostRecent) {
			mrInfo = pathInfo;
		} else {
			return pathInfo.absoluteFilePath();
		}
	}
	foreach (const QString &oneSearchDir, m_absDirs) {
		QFileInfo fi (QDir(oneSearchDir), pathInfo.fileName());
		if (findCheckFile(fi)) {
			if (m_mostRecent) {
				if (
					mrInfo.filePath().isEmpty() ||
					mrInfo.lastModified() < fi.lastModified()
				) {
					mrInfo = fi;
				}
			} else {
				return fi.absoluteFilePath();
			}
		}
	}
	if (m_mostRecent && (mrInfo.filePath().isEmpty() == false)) {
		return mrInfo.absoluteFilePath();
	} else {
		return "";
	}
}

bool FindInDirs::findCheckFile(const QFileInfo &fileInfo) const
{
	return(m_checkReadable ? fileInfo.isReadable() : fileInfo.exists());
}
