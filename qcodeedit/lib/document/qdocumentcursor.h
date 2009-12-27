/****************************************************************************
**
** Copyright (C) 2006-2009 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
** 
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef _QDOCUMENT_CURSOR_H_
#define _QDOCUMENT_CURSOR_H_

#include "qce-config.h"

#include <QObject>
#include <QMetaType>

/*!
	\file qdocumentcursor.h
	\brief Definition of the QDocumentCursor class
*/

class QChar;
class QPoint;
class QString;
class QPolygon;

class QString;
class QChar;

class QDocument;
class QDocumentLine;
struct QDocumentSelection;
class QDocumentCursorHandle;

class QCE_EXPORT QDocumentCursor : public QObject
{
        Q_OBJECT
	public:
		enum MoveFlag
		{
			MoveAnchor	= 0,
			KeepAnchor	= 1,
			ThroughWrap	= 2
		};
		
		Q_DECLARE_FLAGS(MoveMode, MoveFlag);
		
		enum MoveOperation
		{
			NoMove,
			Up,
			Down,
			Left,
			PreviousCharacter = Left,
			Right,
			NextCharacter = Right,
			Start,
			StartOfLine,
			StartOfBlock = StartOfLine,
			StartOfWord,
			PreviousBlock,
			PreviousLine = PreviousBlock,
			PreviousWord,
			WordLeft,
			WordRight,
			End,
			EndOfLine,
			EndOfBlock = EndOfLine,
			EndOfWord,
			NextWord,
			NextBlock,
			NextLine = NextBlock
		};
		
		enum SelectionType
		{
			WordUnderCursor,
			LineUnderCursor
		};
		
                explicit QDocumentCursor(QDocument *doc);
		QDocumentCursor(const QDocumentCursor& cursor);
		QDocumentCursor(QDocument *doc, int line, int column = 0);
		//QDocumentCursor(const QDocumentLine& line, int column = 0);
		QDocumentCursor(QDocumentCursorHandle* handle = 0);
		
		~QDocumentCursor();
		
		QDocumentCursor clone() const;
		
		QDocumentCursor& operator = (const QDocumentCursor& c);
		
		bool operator == (const QDocumentCursor& c) const;
		bool operator != (const QDocumentCursor& c) const;
		
		bool operator < (const QDocumentCursor& c) const;
		bool operator > (const QDocumentCursor& c) const;
		
		bool operator <= (const QDocumentCursor& c) const;
		bool operator >= (const QDocumentCursor& c) const;
		
		bool beginBoundaryLarger (const QDocumentCursor& c) const;
		bool endBoundaryLarger (const QDocumentCursor& c) const;
		
		void beginBoundary(int& begline, int& begcol) const;
		void endBoundary(int& endline, int& endcol) const;
		void boundaries(int& begline, int& begcol, int& endline, int& endcol) const;
		
		bool isNull() const;
		bool isValid() const;
		
                Q_INVOKABLE bool atEnd() const;
                Q_INVOKABLE bool atStart() const;
		
                Q_INVOKABLE bool atBlockEnd() const;
                Q_INVOKABLE bool atBlockStart() const;
		
                Q_INVOKABLE bool atLineEnd() const;
                Q_INVOKABLE bool atLineStart() const;
		
                Q_INVOKABLE bool hasSelection() const;
		
		bool isSilent() const;
		void setSilent(bool y);
		
		bool isAutoUpdated() const;
		void setAutoUpdated(bool y);

		bool isAutoErasable() const;
		void setAutoErasable(bool y);
		
		int position() const;
		
                Q_INVOKABLE int lineNumber() const;
                Q_INVOKABLE int columnNumber() const;
		
                Q_INVOKABLE int anchorLineNumber() const;
                Q_INVOKABLE int anchorColumnNumber() const;
		
		int visualColumnNumber() const;
		
                Q_INVOKABLE void setLineNumber(int c, MoveMode m = MoveAnchor);
                Q_INVOKABLE void setColumnNumber(int c, MoveMode m = MoveAnchor);
		
		int wrappedLineOffset() const;
		int anchorWrappedLineOffset() const;
		
		QPoint documentPosition() const;
		QPoint anchorDocumentPosition() const;
		
		QPolygon documentRegion() const;
		
		QDocumentLine line() const;
		QDocumentLine anchorLine() const;
		
                Q_INVOKABLE void shift(int offset);
                Q_INVOKABLE void setPosition(int pos, MoveMode m = MoveAnchor);
                Q_INVOKABLE bool movePosition(int offset, MoveOperation op = NextCharacter, MoveMode m = MoveAnchor);
		
                Q_INVOKABLE void moveTo(int line, int column);
		void moveTo(const QDocumentCursor &c);
		void moveTo(const QDocumentLine &l, int column);
		
                Q_INVOKABLE void eraseLine();
                Q_INVOKABLE void insertLine(bool keepAnchor = false);
                Q_INVOKABLE void insertText(const QString& s, bool keepAnchor = false);
		
		QDocumentCursor selectionStart() const;
		QDocumentCursor selectionEnd() const;
		
                Q_INVOKABLE QString selectedText() const;
		
                Q_INVOKABLE void clearSelection();
                Q_INVOKABLE void removeSelectedText();
                Q_INVOKABLE void replaceSelectedText(const QString& text);
		
		void select(SelectionType t);
		void setSelectionBoundary(const QDocumentCursor& c);
		
		bool isWithinSelection(const QDocumentCursor& c) const;
		QDocumentCursor intersect(const QDocumentCursor& c) const;
		
		QChar nextChar() const;
		QChar previousChar() const;
		
                Q_INVOKABLE void deleteChar();
                Q_INVOKABLE void deletePreviousChar();
		
                Q_INVOKABLE void beginEditBlock();
                Q_INVOKABLE void endEditBlock();
		
		void refreshColumnMemory();
		bool hasColumnMemory() const;
		void setColumnMemory(bool y);
		
		QDocumentSelection selection() const;
		
		QDocument* document() const;
		
		inline QDocumentCursorHandle* handle() const
		{ return m_handle; }
		
	private:
		QDocumentCursorHandle *m_handle;
};

Q_DECLARE_METATYPE(QDocumentCursor)

#endif
