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

#ifndef Header_QDocument_Cursor
#define Header_QDocument_Cursor

#include "qce-config.h"

#include "modifiedQObject.h"
#include <QMetaType>
#include <QPoint>

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
		Q_ENUMS(MoveOperation)
		Q_ENUMS(MoveMode MoveFlag)
		Q_ENUMS(SelectionType)
	public:
		enum MoveFlag
		{
			MoveAnchor	= 0,
			KeepAnchor	= 1,
			ThroughWrap	= 2,
			ThroughFolding  = 4
		};
		
        Q_DECLARE_FLAGS(MoveMode, MoveFlag)
		
		enum MoveOperation
		{
			NoMove,
			Up,
			Down,
			Left,
			PreviousCharacter,
			Right,
			NextCharacter,
			Start,
			StartOfLine,
			StartOfBlock = StartOfLine,
			StartOfWord,
			StartOfWordOrCommand,
			StartOfParenthesis,
            StartOfLineText,
			PreviousBlock,
			PreviousLine = PreviousBlock,
			PreviousWord,
			WordLeft,
			WordRight,
			End,
			EndOfLine,
			EndOfBlock = EndOfLine,
			EndOfWord,
			EndOfWordOrCommand,
			NextWord,
			NextBlock,
			NextLine = NextBlock
		};
		
		enum SelectionType
		{
			WordUnderCursor,
			WordOrCommandUnderCursor,
			LineUnderCursor,
			ParenthesesInner,
			ParenthesesOuter
		};
		
        Q_INVOKABLE explicit QDocumentCursor(QDocument *doc);
        Q_INVOKABLE QDocumentCursor(const QDocumentCursor& cursor);
        QDocumentCursor(QDocumentCursor&& cursor);
		QDocumentCursor(const QDocumentCursor& cursor, const bool cloneAutoUpdateFlag);
        Q_INVOKABLE QDocumentCursor(QDocument *doc, int line, int column = 0, int lineTo = -1, int columnTo = -1);
		//QDocumentCursor(const QDocumentLine& line, int column = 0);
        QDocumentCursor(QDocumentCursorHandle* handle = nullptr);
		QDocumentCursor(const QDocumentCursor& from, const QDocumentCursor& to);

		~QDocumentCursor();
		
		QDocumentCursor clone(bool cloneAutoUpdatedFlag) const;
		
		QDocumentCursor& operator = (const QDocumentCursor& c);
        QDocumentCursor& operator = (QDocumentCursor&& c);
		
		bool operator == (const QDocumentCursor& c) const;
		bool operator != (const QDocumentCursor& c) const;
		
		bool operator < (const QDocumentCursor& c) const;
		bool operator > (const QDocumentCursor& c) const;
		
		bool operator <= (const QDocumentCursor& c) const;
		bool operator >= (const QDocumentCursor& c) const;
		
		Q_INVOKABLE bool beginBoundaryLarger (const QDocumentCursor& c) const;
		Q_INVOKABLE bool endBoundaryLarger (const QDocumentCursor& c) const;
		Q_INVOKABLE bool equalBoundaries(const QDocumentCursor& c) const;
		Q_INVOKABLE bool equal(const QDocumentCursor& c) const;
		
		void beginBoundary(int& begline, int& begcol) const;
		void endBoundary(int& endline, int& endcol) const;
		void boundaries(int& begline, int& begcol, int& endline, int& endcol) const;
		
		Q_INVOKABLE bool isNull() const;
		Q_INVOKABLE bool isValid() const;
		
		Q_INVOKABLE bool atEnd() const;
		Q_INVOKABLE bool atStart() const;
		
		Q_INVOKABLE bool atBlockEnd() const;
		Q_INVOKABLE bool atBlockStart() const;
		
		Q_INVOKABLE bool atLineEnd() const;
		Q_INVOKABLE bool atLineStart() const;
		
		Q_INVOKABLE bool hasSelection() const;
		Q_INVOKABLE bool isForwardSelection() const;
		
		Q_INVOKABLE bool isSilent() const;
		void setSilent(bool y);
		
		Q_INVOKABLE bool isAutoUpdated() const;
		void setAutoUpdated(bool y);

		Q_INVOKABLE bool isAutoErasable() const;
		void setAutoErasable(bool y);
		
		int position() const;
		
		Q_INVOKABLE int lineNumber() const;
		Q_INVOKABLE int columnNumber() const;
		
		Q_INVOKABLE int anchorLineNumber() const;
		Q_INVOKABLE int anchorColumnNumber() const;

		Q_INVOKABLE int startLineNumber() const;
		Q_INVOKABLE int startColumnNumber() const;

		Q_INVOKABLE int endLineNumber() const;
		Q_INVOKABLE int endColumnNumber() const;

		Q_INVOKABLE int visualColumnNumber() const;
		
		Q_INVOKABLE void setLineNumber(int c, MoveMode m = MoveAnchor);
		Q_INVOKABLE void setColumnNumber(int c, MoveMode m = MoveAnchor);
		Q_INVOKABLE void setAnchorLineNumber(int c) const;
		Q_INVOKABLE void setAnchorColumnNumber(int c) const;

		Q_INVOKABLE int wrappedLineOffset() const;
		Q_INVOKABLE int anchorWrappedLineOffset() const;
		
        Q_INVOKABLE QPointF documentPosition() const;
        Q_INVOKABLE QPointF anchorDocumentPosition() const;
		
		QPolygonF documentRegion() const;
		
		QDocumentLine line() const;
		QDocumentLine anchorLine() const;
		
		Q_INVOKABLE void shift(int offset);
		Q_INVOKABLE void setPosition(int pos, MoveMode m = MoveAnchor);
		Q_INVOKABLE bool movePosition(int offset, MoveOperation op = NextCharacter, MoveMode m = MoveAnchor);
		
		Q_INVOKABLE void moveTo(int line, int column, MoveMode m = MoveAnchor);
		void moveTo(const QDocumentCursor &c, MoveMode m = MoveAnchor);
		//void moveTo(const QDocumentLine &l, int column, MoveMode m = MoveAnchor);
		
		Q_INVOKABLE void eraseLine();
		Q_INVOKABLE void insertLine(bool keepAnchor = false);
		Q_INVOKABLE void insertText(const QString& s, bool keepAnchor = false);
		
		QDocumentCursor selectionStart() const;
		QDocumentCursor selectionEnd() const;
		QDocumentCursor anchorCursor() const;
		
		Q_INVOKABLE QString selectedText() const;
		
		Q_INVOKABLE void clearSelection();
		Q_INVOKABLE void flipSelection();
		Q_INVOKABLE void removeSelectedText();
		Q_INVOKABLE void replaceSelectedText(const QString& text);
		
		Q_INVOKABLE void select(SelectionType t);
		Q_INVOKABLE void expandSelect(SelectionType t);
		Q_INVOKABLE void setSelectionBoundary(const QDocumentCursor& c);
		Q_INVOKABLE void select(int line, int column, int lineTo = -1, int columnTo = -1);
		Q_INVOKABLE void selectColumns(int column, int columnTo = -1);
		
		Q_INVOKABLE bool isWithinSelection(const QDocumentCursor& c) const;
		Q_INVOKABLE QDocumentCursor intersect(const QDocumentCursor& c) const;
		void intersectBoundaries(int& lbeg, int& cbeg, int& lend, int& cend) const;

		void getMatchingPair(QDocumentCursor& from, QDocumentCursor& to, bool maximal = true) const;

		Q_INVOKABLE QChar nextChar() const;
		Q_INVOKABLE QChar previousChar() const;
		
		Q_INVOKABLE void deleteChar();
		Q_INVOKABLE void deletePreviousChar();
		
		Q_INVOKABLE void beginEditBlock();
		Q_INVOKABLE void endEditBlock();
		
		void refreshColumnMemory();
		bool hasColumnMemory() const;
		void setColumnMemory(bool y);
		
		QDocumentSelection selection() const;
		
		bool isRTL() const;

		QDocument* document() const;
		
		inline QDocumentCursorHandle* handle() const
		{ return m_handle; }
		
		static void sort(QDocumentCursor& from, QDocumentCursor& to);

	private:
		QDocumentCursorHandle *m_handle;
};

Q_DECLARE_METATYPE(QDocumentCursor)

#endif
