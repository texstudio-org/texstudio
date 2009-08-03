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

class QCE_EXPORT QDocumentCursor
{
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
		
		bool rightBoundaryLarger (const QDocumentCursor& c) const;
		bool leftBoundaryLarger (const QDocumentCursor& c) const;
		
		void leftBoundaries(int& begline, int& begcol) const;
		void rightBoundaries(int& endline, int& endcol) const;
		
		bool isNull() const;
		bool isValid() const;
		
		bool atEnd() const;
		bool atStart() const;
		
		bool atBlockEnd() const;
		bool atBlockStart() const;
		
		bool atLineEnd() const;
		bool atLineStart() const;
		
		bool hasSelection() const;
		
		bool isSilent() const;
		void setSilent(bool y);
		
		bool isAutoUpdated() const;
		void setAutoUpdated(bool y);
		
		int position() const;
		
		int lineNumber() const;
		int columnNumber() const;
		
		int anchorLineNumber() const;
		int anchorColumnNumber() const;
		
		int visualColumnNumber() const;
		
		void setLineNumber(int c, MoveMode m = MoveAnchor);
		void setColumnNumber(int c, MoveMode m = MoveAnchor);
		
		int wrappedLineOffset() const;
		int anchorWrappedLineOffset() const;
		
		QPoint documentPosition() const;
		QPoint anchorDocumentPosition() const;
		
		QPolygon documentRegion() const;
		
		QDocumentLine line() const;
		QDocumentLine anchorLine() const;
		
		void shift(int offset);
		void setPosition(int pos, MoveMode m = MoveAnchor);
		bool movePosition(int offset, MoveOperation op = NextCharacter, MoveMode m = MoveAnchor);
		
		void moveTo(int line, int column);
		void moveTo(const QDocumentCursor &c);
		void moveTo(const QDocumentLine &l, int column);
		
		void eraseLine();
		void insertLine();
		void insertText(const QString& s);
		
		QDocumentCursor selectionStart() const;
		QDocumentCursor selectionEnd() const;
		
		QString selectedText() const;
		
		void clearSelection();
		void removeSelectedText();
		void replaceSelectedText (const QString& newText); 
		
		void select(SelectionType t);
		void setSelectionBoundary(const QDocumentCursor& c);
		
		bool isWithinSelection(const QDocumentCursor& c) const;
		QDocumentCursor intersect(const QDocumentCursor& c) const;
		
		QChar nextChar() const;
		QChar previousChar() const;
		
		void deleteChar();
		void deletePreviousChar();
		
		void beginEditBlock();
		void endEditBlock();
		
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

#endif
