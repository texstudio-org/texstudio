#include "findindirs.h"
#include "utilsSystem.h"

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

void FindInDirs::loadDirs(const QString &dirs)
{
	loadDirs(splitPaths(dirs));
}

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
