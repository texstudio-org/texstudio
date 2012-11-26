#ifndef SESSION_H
#define SESSION_H

#include "mostQtHeaders.h"

struct FileInSession {
	QString fileName;
	int cursorLine;
	int cursorCol;
	int firstLine;
};

Q_DECLARE_METATYPE(FileInSession)

class ConfigManager;

class Session {
public:
	Session() {}
	Session(const Session &s);

	bool load(const QString &file);
	bool load(const ConfigManager &config); //
	bool save(const QString &file) const;

	const QList<FileInSession> files() const { return m_files; }
	void addFile(FileInSession f);

	void setMasterFile(const QString &file) { m_masterFile = file; }
	QString masterFile() const { return m_masterFile; }

	void setCurrentFile(const QString &file) { m_currentFile = file; }
	QString currentFile() const { return m_currentFile; }

	void setBookmarks(const QList<QVariant> &bookmarkList) { m_bookmarks = bookmarkList; }
	QList<QVariant> bookmarks() const { return m_bookmarks; }

private:
	QList<FileInSession> m_files;
	QString m_masterFile;
	QString m_currentFile;

	QList<QVariant> m_bookmarks;
};

#endif // SESSION_H
