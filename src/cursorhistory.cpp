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
#include "cursorhistory.h"
#include "qdocumentcursor.h"


CursorHistory::CursorHistory(LatexDocuments *docs) :
    QObject(docs), m_backAction(nullptr), m_forwardAction(nullptr), m_maxLength(30), m_insertionEnabled(true)
{
	connect(docs, SIGNAL(aboutToDeleteDocument(LatexDocument *)), this, SLOT(aboutToDeleteDoc(LatexDocument *)));
	currentEntry = history.end();
}

/*!
  Inserts the cursor behind the current entry
*/
bool CursorHistory::insertPos(QDocumentCursor cur, bool deleteBehindCurrent)
{
	if (!m_insertionEnabled) return false;
	if (!cur.isValid()) return false;

	CursorPosition pos(cur);
	connectUnique(pos.doc(), SIGNAL(destroyed(QObject *)), this, SLOT(documentClosed(QObject *)));
	// TODO destroyed() may be duplicate to aboutToDeleteDocument() - needs more testing. anyway it does not harm
	connectUnique(pos.doc(), SIGNAL(lineDeleted(QDocumentLineHandle *)), this, SLOT(lineDeleted(QDocumentLineHandle *)));
	connectUnique(pos.doc(), SIGNAL(lineRemoved(QDocumentLineHandle *)), this, SLOT(lineDeleted(QDocumentLineHandle *)));

	if (deleteBehindCurrent && currentEntry != history.end()) {
		currentEntry++;
		currentEntry = history.erase(currentEntry, history.end());
	}
	if (currentEntry == history.end() && currentEntry != history.begin()) currentEntry--;

	// do not insert neighboring duplicates
	if (currentEntryValid() && (*currentEntry).equals(pos)) {
		updateNavActions();
		return false;
	}
	CursorPosList::iterator it = prevValidEntry(currentEntry);
	if (it != history.end() && (*it).isValid() && (*it).equals(pos)) {
		updateNavActions();
		return false;
	}

	if (history.count() >= m_maxLength) {
		if (currentEntry == history.begin()) {
			history.removeLast();
		} else {
			history.removeFirst();
		}
	}

	currentEntry++;
	history.insert(currentEntry, pos);
	updateNavActions();
	return true;
}

QDocumentCursor CursorHistory::currentPos()
{
	if (!currentEntryValid()) {
		validate();
	}
	if (!currentEntryValid()) {
		qDebug() << "invalid current position in CursorHistory";
		return QDocumentCursor();
	}
	return (*currentEntry).toCursor();
}

void CursorHistory::setInsertionEnabled(bool b)
{
	m_insertionEnabled = b;
}

/*!
 Register an action as backward action. This is only used to set the enabled state of the action depending on if back is possible.
 It does not actually connect the action to the back() slot because it is unspecified if other slots connected to the action are executed
 before or after back().
 Therefore the user has to call back() manually, or, if it is unabigous, connect the trigger signal of the action to the back() slot himself.
 */
void CursorHistory::setBackAction(QAction *back)
{
	m_backAction = back;
	updateNavActions();
}

/*!
 Register an action as forward action. This is only used to set the enabled state of the action depending on if forward is possible.
 It does not actually connect the action to the forward() slot because it is unspecified if other slots connected to the action are executed
 before or after forward().
 Therefore the user has to call forward() manually, or, if it is unabigous, connect the trigger signal of the action to the forward() slot himself.
 */
void CursorHistory::setForwardAction(QAction *forward)
{
	m_forwardAction = forward;
	updateNavActions();
}

void CursorHistory::clear()
{
	history.clear();
	currentEntry = history.end();
	updateNavActions();
}

QDocumentCursor CursorHistory::back(const QDocumentCursor &currentCursor)
{
	if (currentEntry == history.begin()) {
		updateNavActions();
		return QDocumentCursor();
	}

	// insert currentCursor to be able to go back
	if (currentCursor.isValid() && insertPos(currentCursor, false)) {
		currentEntry--;
	}

	CursorPosition pos(currentCursor);
	if (pos.isValid() && !pos.equals(*currentEntry)) {
		updateNavActions();
		return currentPos();
	}

	currentEntry = prevValidEntry(currentEntry);
	updateNavActions();
	return currentPos();
}

QDocumentCursor CursorHistory::forward(const QDocumentCursor &currentCursor)
{
	Q_UNUSED(currentCursor);
	CursorPosList::iterator next = nextValidEntry(currentEntry);
	if (currentEntry == history.end() || next == history.end()) {
		updateNavActions();
		return QDocumentCursor();
	}
	currentEntry = next;
	updateNavActions();
	return currentPos();
}

void CursorHistory::aboutToDeleteDoc(LatexDocument *doc)
{
	// remove all entries with document from list.
	for (CursorPosList::iterator it = history.begin(); it != history.end(); ) {
		if ( (*it).doc() == doc ) {
			if (currentEntry == it)
				currentEntry = nextValidEntry(currentEntry);
			removeEntry(it);
		} else ++it;
	}

	updateNavActions();
}

void CursorHistory::documentClosed(QObject *obj)
{
	LatexDocument *doc = qobject_cast<LatexDocument *>(obj);
	if (doc)
		aboutToDeleteDoc(doc);
}

void CursorHistory::lineDeleted(QDocumentLineHandle *dlh)
{
	for (CursorPosList::iterator it = history.begin(); it != history.end(); ++it) {
		if ( (*it).dlh() == dlh ) {
			if (currentEntry == it)
				currentEntry = nextValidEntry(currentEntry);
			removeEntry(it);
		}
	}
	updateNavActions();
}

void CursorHistory::updateNavActions()
{
	if (m_backAction) {
		m_backAction->setEnabled(currentEntry != history.begin());
	}
	if (m_forwardAction) {
		m_forwardAction->setEnabled(nextValidEntry(currentEntry) != history.end());
	}
}

void CursorHistory::removeEntry(CursorPosList::iterator &it)
{
	Q_ASSERT(it != history.end());
	if (currentEntry == it) {
		currentEntry = nextValidEntry(currentEntry);
	}
	Q_ASSERT(currentEntry != it);
	it = history.erase(it);
}

bool CursorHistory::currentEntryValid()
{
	if (currentEntry == history.end()) return false;

	return (*currentEntry).isValid();
}

/*!
  Removes all invalid entries from history
 */
void CursorHistory::validate()
{
	CursorPosList::iterator it = history.begin();
	while (it != history.end()) {
		if (!(*it).isValid()) {
			if (it == currentEntry) currentEntry++;
			qDebug() << "removed invalid cursorHistory entry" << (*it).doc()->getFileName();
			Q_ASSERT(currentEntry != it);
			it = history.erase(it);
		} else {
			++it;
		}
	}
}

CursorPosList::iterator CursorHistory::prevValidEntry(const CursorPosList::iterator &start)
{
	CursorPosList::iterator it = start;
	while (true) {
		if (it == history.begin()) return it;
		--it;
		if ((*it).isValid()) {
			return it;
		}
		bool moveCurrent = (currentEntry == it);
		it = history.erase(it);
		if (moveCurrent) currentEntry = it;
	}
	Q_ASSERT(0);
	return history.end(); // never reached
}

CursorPosList::iterator CursorHistory::nextValidEntry(const CursorPosList::iterator &start)
{
	CursorPosList::iterator it = start;
	if (it == history.end()) return it;
	++it;
	while (true) {
		if (it == history.end()) return it;
		if ((*it).isValid()) {
			return it;
		}
		bool moveCurrent = (currentEntry == it);
		it = history.erase(it);
		if (moveCurrent) currentEntry = it;
	}
	Q_ASSERT(0);
	return history.end(); // never reached
}

void CursorHistory::debugPrint()
{
	qDebug() << "*** Cursor History ***";
	CursorPosList::iterator it = history.begin();
	while (it != history.end()) {
		CursorPosition pos = *it;
		qDebug() << ((it == currentEntry) ? "*" : " ") << pos.doc()->getFileName() << pos.oldLineNumber() << "col:" << pos.columnNumber();
		it++;
	}
	qDebug() << ((it == currentEntry) ? "*" : " ") << "end";
}
