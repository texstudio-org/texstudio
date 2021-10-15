/***************************************************************************
 *   copyright       : (C) 2012 by Tim Hoffmann                            *
 *   http://texstudio.sourceforge.net/                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef Header_CursorHistory
#define Header_CursorHistory

#include "mostQtHeaders.h"
#include "latexdocument.h"
#include "cursorposition.h"

typedef std::list<CursorPosition> CursorPosList;

class CursorHistory : public QObject
{
	Q_OBJECT

public:
	explicit CursorHistory(LatexDocuments *docs);

    uint maxLength() { return m_maxLength; }

	bool insertPos(QDocumentCursor cur, bool deleteBehindCurrent = true);
	QDocumentCursor currentPos();

	void setInsertionEnabled(bool b);

	void setBackAction(QAction *back);
	void setForwardAction(QAction *forward);
	QAction *backAction() { return m_backAction; }
	QAction *forwardAction() { return m_forwardAction; }

	void clear();
    int count() { return history.size(); }

	void debugPrint();
signals:

public slots:
	QDocumentCursor back(const QDocumentCursor &currentCursor = QDocumentCursor());
	QDocumentCursor forward(const QDocumentCursor &currentCursor = QDocumentCursor());

private slots:
	void aboutToDeleteDoc(LatexDocument *doc);
	void documentClosed(QObject *obj);
    void lineDeleted(QDocumentLineHandle *dlh,int hint=-1);

private:
	void updateNavActions();
	void removeEntry(CursorPosList::iterator &it);
	bool currentEntryValid();
	void validate();

	CursorPosList::iterator prevValidEntry(const CursorPosList::iterator &start);
	CursorPosList::iterator nextValidEntry(const CursorPosList::iterator &start);

	CursorPosList::iterator currentEntry;
	CursorPosList history;
	QAction *m_backAction;
	QAction *m_forwardAction;
    uint m_maxLength;
	bool m_insertionEnabled;
};

#endif // CURSORHISTORY_H
