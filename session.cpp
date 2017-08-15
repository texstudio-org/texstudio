#include "session.h"
#include "configmanager.h"
#include "smallUsefulFunctions.h"

QString Session::m_fileExtension = "txss";

Session::Session(const Session &s)
{
	m_files.append(s.m_files);
	m_masterFile = s.m_masterFile;
	m_currentFile = s.m_currentFile;

	m_bookmarks = s.m_bookmarks;
	m_pdfFile = s.m_pdfFile;
	m_pdfEmbedded = s.m_pdfEmbedded;
}

bool Session::load(const QString &file)
{
	if (!QFileInfo(file).isReadable()) return false;
	QSettings s(file, QSettings::IniFormat);
	if (!s.childGroups().contains("Session")) return false;
	m_files.clear();
	s.beginGroup("Session");
	QStringList groups = s.childGroups();
	QDir dir = QFileInfo(file).dir();
	for (int i = 0; i < 1000; i++) {
		if (!groups.contains(QString("File%1").arg(i)))
			break;
		s.beginGroup(QString("File%1").arg(i));
		FileInSession f;
		QString filename = s.value("FileName").toString();
		if (filename.isEmpty()) continue;
		f.fileName = QDir::cleanPath(dir.filePath(filename));
		f.editorGroup = s.value("EditorGroup", 0).toInt();
		f.cursorLine = s.value("Line", 0).toInt();
		f.cursorCol = s.value("Col", 0).toInt();
		f.firstLine = s.value("FirstLine", 0).toInt();
		f.foldedLines = strToIntList(s.value("FoldedLines").toString());
		m_files.append(f);
		s.endGroup();
	}
	m_masterFile = QDir::cleanPath(dir.filePath(s.value("MasterFile").toString()));
	m_currentFile = QDir::cleanPath(dir.filePath(s.value("CurrentFile").toString()));
	
	foreach (const QVariant &v, s.value("Bookmarks").value<QList<QVariant> >()) {
		Bookmark bm = Bookmark::fromStringList(v.toStringList());
		bm.filename = QDir::cleanPath(dir.filePath(bm.filename));
		m_bookmarks << bm;
	}
	s.endGroup();

	s.beginGroup("InternalPDFViewer");
	QString pdfFileName(s.value("File").toString());
	m_pdfFile = (pdfFileName.trimmed().isEmpty()) ? "" : QDir::cleanPath(dir.filePath(pdfFileName));
	m_pdfEmbedded = s.value("Embedded").toBool();
	s.endGroup();
	return true;
}

bool Session::save(const QString &file, bool relPaths) const
{
	if (!isFileRealWritable(file)) return false;
	QSettings s(file, QSettings::IniFormat);
	s.clear();
	s.beginGroup("Session");
	s.setValue("FileVersion", 1); // increment if format changes are applied later on. This might be used for version-dependent loading.
	QDir dir = QFileInfo(file).dir();
	for (int i = 0; i < m_files.count(); i++) {
		s.beginGroup(QString("File%1").arg(i));
		s.setValue("FileName", fmtPath(dir, m_files[i].fileName, relPaths));
		s.setValue("EditorGroup", m_files[i].editorGroup);
		s.setValue("Line", m_files[i].cursorLine);
		s.setValue("Col", m_files[i].cursorCol);
		s.setValue("FirstLine", m_files[i].firstLine);
		s.setValue("FoldedLines", intListToStr(m_files[i].foldedLines)); // saving as string is not very elegant, but at least human-readable (QList<int> would result in a byte stream - after adding it as a metatype)
		s.endGroup();
	}
	s.setValue("MasterFile", fmtPath(dir, m_masterFile, relPaths));
	s.setValue("CurrentFile", fmtPath(dir, m_currentFile, relPaths));
	
	QList<QVariant> bookmarkList;
	foreach (Bookmark bm, m_bookmarks) {
		if (relPaths) {
			bm.filename = fmtPath(dir, bm.filename, relPaths);
		}
		bookmarkList << bm.toStringList();
	}
	s.setValue("Bookmarks", bookmarkList);
	s.endGroup();

	s.beginGroup("InternalPDFViewer");
	s.setValue("File", fmtPath(dir, m_pdfFile, relPaths));
	s.setValue("Embedded", m_pdfEmbedded);
	s.endGroup();

	return true;
}

void Session::addFile(FileInSession f)
{
	m_files.append(f);
}

QString Session::fmtPath(const QDir &dir, const QString &file, bool relPath)
{
	if (!relPath)
		return file;
	else
		return dir.relativeFilePath(file);
}

