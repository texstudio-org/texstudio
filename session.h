#ifndef SESSION_H
#define SESSION_H

#include "mostQtHeaders.h"

struct FileInSession {
	QString fileName;
	int cursorLine;
	int cursorCol;
	int firstLine;
	QList<int> foldedLines;
};

Q_DECLARE_METATYPE(FileInSession)

class ConfigManager;

class Session {
public:
	Session(): m_pdfEmbedded(false) {}
	Session(const Session &s);

	bool load(const QString &file);
	bool load(const ConfigManager &config); //
	bool save(const QString &file, bool relPaths=true) const;

	const QList<FileInSession> files() const { return m_files; }
	void addFile(FileInSession f);

	void setMasterFile(const QString &file) { m_masterFile = file; }
	QString masterFile() const { return m_masterFile; }

	void setCurrentFile(const QString &file) { m_currentFile = file; }
	QString currentFile() const { return m_currentFile; }

	void setBookmarks(const QList<QVariant> &bookmarkList) { m_bookmarks = bookmarkList; }
	QList<QVariant> bookmarks() const { return m_bookmarks; }

	static QString fileExtension() { return m_fileExtension; }

	void setPDFFile(const QString &pdf) { m_pdfFile = pdf; }
	QString PDFFile() const { return m_pdfFile; }

	void setPDFEmbedded(bool b) { m_pdfEmbedded = b; }
	bool PDFEmbedded() const { return m_pdfEmbedded; }

	static QString fmtPath(const QDir &dir, const QString &file, bool relPath=true);

private:
	static QString m_fileExtension;

	QList<FileInSession> m_files;
	QString m_masterFile;
	QString m_currentFile;

	QList<QVariant> m_bookmarks;

	QString m_pdfFile;
	bool m_pdfEmbedded;
};

#endif // SESSION_H
