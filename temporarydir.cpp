#include "temporarydir.h"

QStringList TemporaryDir::createdDirs = QStringList();
QDir TemporaryDir::m_sessionDir = QDir();
bool TemporaryDir::m_sessionDirIsSet = false;

/*!
	Creates an temporary directory. On success, exists() is true. The directory
	will live until TemporaryDir::removeCreatedDirs() is called.
 */
TemporaryDir::TemporaryDir() : QDir()
{
	int len = 6;
	int maxTries = 20;
	QDir d = QDir::temp();
	QString dirname;
	for (int i=0; i<maxTries; i++) {
		dirname = "texstudio_" + makeRandomWord(len);
		if (d.mkpath(dirname)) {
			d.cd(dirname);
			setPath(d.path());
			qDebug() << absolutePath();
			createdDirs.append(absolutePath());
			break;
		}
	}
}

TemporaryDir::~TemporaryDir()
{
}

QDir TemporaryDir::sessionDir()
{
	qDebug() << m_sessionDir.dirName();
	if (!m_sessionDirIsSet)  {
		// TODO: should be locked
		m_sessionDir = TemporaryDir();
		m_sessionDirIsSet = true;
	}
	return m_sessionDir;
}

QString TemporaryDir::makeRandomWord(int len)
{
	QString s;
	for (int i=0; i<len; i++) {
		char ch = char((qrand() & 0xffff) % (26 + 26));
		if (ch < 26)
			s.append(QChar(ch + 'A'));
		else 
			s.append(QChar(ch - 26 + 'a'));
	}
	return s;
}

/*!
	Removes all directories an their content, which were created using TemporaryDir()
	Fails silently.
 */
void TemporaryDir::removeCreatedDirs()
{
	qDebug() << createdDirs.length();
	QTime t;
	t.start();
	foreach (const QString &dir, createdDirs) {
		qDebug() << dir;
		QDir d(dir);
		if (d.exists()) {
#if QT_VERSION >= 0x050000
			bool ok = d.removeRecursively();
			qDebug () << ok << d.absolutePath();
#else
			// TODO: for some reason this only deletes the folder contents
			QString dirname = d.dirName();
			d.cdUp();
			bool ok = d.rmpath(dirname);  
			qDebug () << ok;
#endif
		}
	}
	qDebug() << "done" << t.elapsed();
}

