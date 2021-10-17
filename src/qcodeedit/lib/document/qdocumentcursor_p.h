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

#ifndef Header_QDocument_Cursor_P
#define Header_QDocument_Cursor_P

#include "qce-config.h"

/*!
	\file qdocumentcursor_p.h
	\brief Definition of QDocumentCursorHandle
*/

#include "qdocumentcursor.h"

#include <QStack>

#include <QAtomicInt>

class QPoint;
class QPolygon;

class QDocument;
class QDocumentLine;
class QDocumentPrivate;
class QDocumentCommand;
class QDocumentCommandBlock;

class QCE_EXPORT QDocumentCursorHandle
{
	friend class QDocumentCursor;
	friend class QDocumentPrivate;
	friend class QDocumentCommand;

	public:
		enum Flags
		{
			Silent			= 1,
			ColumnMemory		= 2,
			MoveWithinWrapped	= 4,
			AutoErasable		= 0x100,
			AutoUpdated		= 0x200,
			AutoUpdateKeepBegin	= 0x400,
			AutoUpdateKeepEnd	= 0x800
		};

		QDocument* document() const;

		bool atEnd() const;
		bool atStart() const;

		bool atBlockEnd() const;
		bool atBlockStart() const;

		bool atLineEnd() const;
		bool atLineStart() const;

		bool hasSelection() const;
		bool isForwardSelection() const;

		bool isSilent() const;
		void setSilent(bool y);

		bool isAutoUpdated() const;
		void setAutoUpdated(bool y);

		bool isAutoErasable() const;
		void setAutoErasable(bool y);


		QDocumentLine line() const;
		QDocumentLine anchorLine() const;

		int lineNumber() const;
		int columnNumber() const;

		int anchorLineNumber() const;
		int anchorColumnNumber() const;

		int startLineNumber() const;
		int startColumnNumber() const;

		int endLineNumber() const;
		int endColumnNumber() const;

		int visualColumnNumber() const;

		void setLineNumber(int l, int m = QDocumentCursor::MoveAnchor);
		void setColumnNumber(int c, int m = QDocumentCursor::MoveAnchor);
		void setAnchorLineNumber(int l);
		void setAnchorColumnNumber(int c);

        QPointF documentPosition() const;
        QPointF anchorDocumentPosition() const;

		QPolygonF documentRegion() const;

		void shift(int offset);
		void setPosition(int pos, int m);
		bool movePosition(int offset, int op, const QDocumentCursor::MoveMode& m);

		void insertText(const QString& s, bool keepAnchor = false);

		QChar nextChar() const;
		QChar previousChar() const;

		void eraseLine();
		void deleteChar();
		void deletePreviousChar();

		QDocumentCursor selectionStart() const;
		QDocumentCursor selectionEnd() const;
		QDocumentCursor anchorCursor() const;

		bool eq(const QDocumentCursorHandle *h);
		bool lt(const QDocumentCursorHandle *h);
		bool gt(const QDocumentCursorHandle *h);

		QString selectedText() const;

		void clearSelection();
		void flipSelection();
		void removeSelectedText(bool keepAnchor = false);
		void replaceSelectedText(const QString& text);

		void select(QDocumentCursor::SelectionType t);
		void expandSelect(QDocumentCursor::SelectionType t);
		void setSelectionBoundary(const QDocumentCursor& c);
		void select(int line, int column, int lineTo = -1, int columnTo = -1);

		bool isWithinSelection(const QDocumentCursor& c) const;
		QDocumentCursor intersect(const QDocumentCursor& c) const;

		void beginBoundary(int& begline, int& begcol) const;
		void endBoundary(int& endline, int& endcol) const;
		void substractBoundaries(int lbeg, int cbeg, int lend, int cend);
		void boundaries(int& begline, int& begcol, int& endline, int& endcol) const;
		void intersectBoundaries(int& lbeg, int& cbeg, int& lend, int& cend) const;
		void intersectBoundaries(QDocumentCursorHandle *h, int& lbeg, int& cbeg, int& lend, int& cend) const;
		bool equalBoundaries(const QDocumentCursorHandle* c);
		bool equal(const QDocumentCursorHandle* c);


		void getMatchingPair(QDocumentCursor& from, QDocumentCursor& to, bool maximal) const;

		void beginEditBlock();
		void endEditBlock();

        void moveTo(int line, int column, const QDocumentCursor::MoveMode& m = QDocumentCursor::MoveAnchor);
		void moveTo(const QDocumentCursor &c, const QDocumentCursor::MoveMode& m );

		void copy(const QDocumentCursorHandle *c);

		void refreshColumnMemory();
		bool hasColumnMemory() const;
		void setColumnMemory(bool y);

		bool isRTL() const;

		virtual void execute(QDocumentCommand *c);

		inline void ref() { m_ref.ref(); }
		inline void deref() { if ( !m_ref.deref() ) delete this; }

		inline bool hasFlag(int f) const { return m_flags & f; }
		inline void setFlag(int f) { m_flags |= f; }
		inline void clearFlag(int f) { m_flags &= ~f; }
	protected:
		QDocumentCursorHandle(QDocument *d, int line = 0);
		QDocumentCursorHandle(QDocument *d, int line, int column, int lineTo = -1, int columnTo = -1);
		virtual ~QDocumentCursorHandle();

		QDocumentCursorHandle* clone(bool cloneAutoUpdatedFlag) const;

	private:
		int m_flags;
		QDocument *m_doc;

		QAtomicInt m_ref;

        int m_begOffset, m_endOffset, m_savedX, m_begLine, m_endLine; //beg: cursor position, end: anchor position
		QStack<QDocumentCommandBlock*> m_blocks;
};

Q_DECLARE_TYPEINFO(QDocumentCursorHandle*, Q_PRIMITIVE_TYPE);

#endif // !_QDOCUMENT_CURSOR_P_H_
