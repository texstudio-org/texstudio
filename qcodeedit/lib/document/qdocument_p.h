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

#ifndef _QDOCUMENT_P_H_
#define _QDOCUMENT_P_H_

#include "qce-config.h"

/*!
	\file qdocument_p.h
	\brief Definition of the private document API
*/

#include "qnfa.h"

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

#include <QPair>
#include <QHash>
#include <QFont>
#include <QStack>
#include <QQueue>
#if QT_VERSION < 0x040400
#include <QAtomic>
#else
#include <QAtomicInt>
#endif
#include <QUndoStack>
#include <QStringList>
#include <QTextLayout>
#include <QFontMetrics>
#include <QUndoCommand>

#include <QTextLayout>

template <typename T, int x>
class QVarLengthArray;

// TODO : create buffer class for (fragmented) doc data storage
// -> reduce memory usage for large files
// -> speed up loading by avoiding many reallocs
// -> speed up editing by huges mem moves

//typedef QVarLengthArray<int, 10> QSmallArray;
//typedef QVarLengthArray<quint8, 100> QMediumArray;

typedef QVector<int> QSmallArray;
typedef QVector<int> QMediumArray;

class QDocument;
class QDocumentPrivate;
class QDocumentCommand;
class QDocumentCommandBlock;

class QLanguageDefinition;

Q_DECLARE_TYPEINFO(QDocumentSelection, Q_PRIMITIVE_TYPE);

class QCE_EXPORT QDocumentLineHandle
{
	friend class QDocument;
	friend class QDocumentLine;
	friend class QDocumentPrivate;
	
	public:
		QDocumentLineHandle(QDocument *d);
		QDocumentLineHandle(const QString& s, QDocument *d);
		
		int count() const;
		int length() const;
		
		int position() const;
		
		QString text() const;
		
		int line() const;
		
		int xToCursor(int x) const;
		int cursorToX(int i) const;
		
		int wrappedLineForCursor(int cpos) const;
		
		int documentOffsetToCursor(int x, int y) const;
		void cursorToDocumentOffset(int cpos, int& x, int& y) const;
		
		QPoint cursorToDocumentOffset(int cpos) const;
		
		int nextNonSpaceChar(uint pos) const;
		int previousNonSpaceChar(int pos) const;
		
		bool hasFlag(QDocumentLine::State s) const;
		void setFlag(QDocumentLine::State s, bool y = true) const;
		
		QDocument* document() const;
		
		QDocumentLineHandle* next() const;
		QDocumentLineHandle* previous() const;
		
		void updateWrap() const;
		
		void setFormats(const QVector<int>& formats);
		
		void clearOverlays();
		void addOverlay(const QFormatRange& over);
		void removeOverlay(const QFormatRange& over);
		bool hasOverlay(int id);
		QFormatRange getOverlayAt(int index, int preferredFormat);
		QFormatRange getFirstOverlayBetween(int start, int end, int preferredFormat = -1);
		QFormatRange getLastOverlayBetween(int start, int end, int preferredFormat = -1);
		
		void shiftOverlays(int position, int offset);
		
		void draw(	QPainter *p,
					int xOffset,
					int vWidth,
					const QSmallArray& sel,
					const QSmallArray& cursors,
					const QPalette& pal,
					bool fullSel) const;
		
		inline QString& textBuffer() { setFlag(QDocumentLine::LayoutDirty, true); return m_text; }
		
		inline void ref() { m_ref.ref(); }
		inline void deref() { if ( m_ref ) m_ref.deref(); if ( !m_ref ) delete this; }
		
	protected:
		~QDocumentLineHandle();
		
	private:
		void layout() const;
		void applyOverlays() const;
		
		QMediumArray compose() const;
		QList<QTextLayout::FormatRange> decorations() const;
		
		QString m_text;
		QDocument *m_doc;
#if QT_VERSION < 0x040400
		QBasicAtomic m_ref;
#else
		QAtomicInt m_ref;
#endif
		mutable int m_indent;
		mutable quint16 m_state;
		mutable QTextLayout *m_layout;
		mutable QVector<int> m_cache;
		mutable QVector< QPair<int, int> > m_frontiers;
		
		QNFAMatchContext m_context;
		
		QVector<int> m_formats;
		QVector<QParenthesis> m_parens;
		QList<QFormatRange> m_overlays;
};

Q_DECLARE_TYPEINFO(QDocumentLineHandle*, Q_PRIMITIVE_TYPE);

class QCE_EXPORT QDocumentCursorHandle
{
	friend class QDocumentCursor;
	friend class QDocumentPrivate;
	friend class QDocumentCommand;
	
	public:
		enum Flags
		{
			Silent				= 1,
			ColumnMemory			= 2,
			MoveWithinWrapped	= 4
		};

		QDocument* document() const;
		
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
		
		QDocumentLine line() const;
		QDocumentLine anchorLine() const;
		
		int lineNumber() const;
		int columnNumber() const;
		
		int anchorLineNumber() const;
		int anchorColumnNumber() const;
		
		int visualColumnNumber() const;
		
		void setColumnNumber(int c, QDocumentCursor::MoveMode m =
									QDocumentCursor::MoveAnchor);
		
		QPoint documentPosition() const;
		QPoint anchorDocumentPosition() const;
		
		QPolygon documentRegion() const;
		
		int position() const;
		
		void shift(int offset);
		void setPosition(int pos, QDocumentCursor::MoveMode m);
		bool movePosition(int offset, QDocumentCursor::MoveOperation op, QDocumentCursor::MoveMode m);
		
		void insertText(const QString& s);
		
		void eraseLine();
		void deleteChar();
		void deletePreviousChar();
		QChar getPreviousChar();
		
		QDocumentCursor selectionStart() const;
		QDocumentCursor selectionEnd() const;
		
		bool eq(const QDocumentCursorHandle *h);
		bool lt(const QDocumentCursorHandle *h);
		bool gt(const QDocumentCursorHandle *h);
		
		QString selectedText() const;
		
		void clearSelection();
		void removeSelectedText();
		
		void select(QDocumentCursor::SelectionType t);
		void setSelectionBoundary(const QDocumentCursor& c);
		
		bool isWithinSelection(const QDocumentCursor& c) const;
		QDocumentCursor intersect(const QDocumentCursor& c) const;
		
		void substractBoundaries(int lbeg, int cbeg, int lend, int cend);
		void boundaries(int& begline, int& begcol, int& endline, int& endcol) const;
		void intersectBoundaries(int& lbeg, int& cbeg, int& lend, int& cend) const;
		void intersectBoundaries(QDocumentCursorHandle *h, int& lbeg, int& cbeg, int& lend, int& cend) const;
		
		void beginEditBlock();
		void endEditBlock();
		
		void moveTo(int line, int column);
		void moveTo(const QDocumentCursor &c);
		
		void copy(const QDocumentCursorHandle *c);
		
		void refreshColumnMemory();
		bool hasColumnMemory() const;
		void setColumnMemory(bool y);
		
		virtual void execute(QDocumentCommand *c);
		
		inline void ref() { m_ref.ref(); }
		inline void deref() { if ( m_ref ) m_ref.deref(); if ( !m_ref ) delete this; }
		
		inline bool hasFlag(int f) const { return m_flags & f; }
		inline void setFlag(int f) { m_flags |= f; }
		inline void clearFlag(int f) { m_flags &= ~f; }
		
	protected:
		QDocumentCursorHandle(QDocument *d, int line = 0);
		virtual ~QDocumentCursorHandle();
		
		QDocumentCursorHandle* clone() const;
		
	private:
		int m_flags;
		QDocument *m_doc;
#if QT_VERSION < 0x040400
		QBasicAtomic m_ref;
#else
		QAtomicInt m_ref;
#endif
		int m_begOffset, m_endOffset, m_max, m_begLine, m_endLine;
		QStack<QDocumentCommandBlock*> m_blocks;
};

Q_DECLARE_TYPEINFO(QDocumentCursorHandle*, Q_PRIMITIVE_TYPE);

class QCE_EXPORT QDocumentPrivate
{
	friend class QEditConfig;
	
	friend class QDocument;
	friend class QDocumentCommand;
	friend class QDocumentLineHandle;
	friend class QDocumentCursorHandle;
	
	public:
		QDocumentPrivate(QDocument *d);
		~QDocumentPrivate();
		
		void execute(QDocumentCommand *cmd);
		
		void draw(QPainter *p, QDocument::PaintContext& cxt);
		
		QDocumentLineHandle* lineForPosition(int& position) const;
		int position(const QDocumentLineHandle *l) const;
		
		QDocumentLineHandle* at(int line) const;
		int indexOf(const QDocumentLineHandle *l) const;
		
		QDocumentIterator index(const QDocumentLineHandle *l);
		QDocumentConstIterator index(const QDocumentLineHandle *l) const;
		
		QDocumentLineHandle* next(const QDocumentLineHandle *l) const;
		QDocumentLineHandle* previous(const QDocumentLineHandle *l) const;
		
		void adjustWidth(int l);
		//int checkWidth(QDocumentLineHandle *l, int w);
		//int checkWidth(QDocumentLineHandle *l, const QString& s);
		
		void setWidth();
		void setHeight();
		
		static void setFont(const QFont& f);
		
		void beginChangeBlock();
		void endChangeBlock();
		
		inline int maxMarksPerLine() const
		{ return m_maxMarksPerLine; }
		
		inline bool hasMarks() const
		{ return m_marks.count(); }
		
		QList<int> marks(QDocumentLineHandle *h) const;
		void hasMark(QDocumentLineHandle *h, int mid);
		
		void addMark(QDocumentLineHandle *h, int mid);
		void toggleMark(QDocumentLineHandle *h, int mid);
		void removeMark(QDocumentLineHandle *h, int mid);
		
		int findNextMark(int id, int from = 0, int until = -1);
		int findPreviousMark(int id, int from = -1, int until = 0);
		
		int getNextGroupId();
		void releaseGroupId(int groupId);
		void clearMatches(int gid);
		void flushMatches(int gid);
		void addMatch(int gid, int line, int pos, int len, int format);
		
		void emitFormatsChange (int line, int lines);
		void emitContentsChange(int line, int lines);
		
		int visualLine(int textLine) const;
		int textLine(int visualLine, int *wrap = 0) const;
		void hideEvent(int line, int count);
		void showEvent(int line, int count);
		
		void setWidth(int width);
		
		void emitFormatsChanged();
		void emitContentsChanged();
		
		void emitLineDeleted(QDocumentLineHandle *h);
		void emitMarkChanged(QDocumentLineHandle *l, int m, bool on);
		
		inline QDocumentIterator begin() { return m_lines.begin(); }
		inline QDocumentIterator end() { return m_lines.end(); }
		
		inline QDocumentConstIterator constBegin() const { return m_lines.constBegin(); }
		inline QDocumentConstIterator constEnd() const { return m_lines.constEnd(); }
		
	protected:
		void updateHidden(int line, int count);
		void updateWrapped(int line, int count);
		
		void insertLines(int after, const QList<QDocumentLineHandle*>& l);
		void removeLines(int after, int n);
		
		void emitWidthChanged();
		void emitHeightChanged();
		
		void updateFormatCache();
		void setFormatScheme(QFormatScheme *f);
		void tunePainter(QPainter *p, int fid);
		
	private:
		QDocument *m_doc;
		QUndoStack m_commands;
		QDocumentCursor *m_editCursor;
		
		bool m_suspend, m_deleting;
		QQueue<QPair<int, int> > m_notifications;
		
		QMap<int, int> m_hidden;
		QMap<int, int> m_wrapped;
		QVector< QPair<QDocumentLineHandle*, int> > m_largest;
		
		struct Match
		{
			int line;
			QFormatRange range;
			QDocumentLineHandle *h;
		};
		
		struct MatchList : QList<Match>
		{
			MatchList() : index(0) {}
			
			int index;
		};
		
		int m_lastGroupId;
		QList<int> m_freeGroupIds;
		QHash<int, MatchList> m_matches;
		
		bool m_constrained;
		int m_width, m_height;
		
		int m_tabStop;
		static int m_defaultTabStop;
		
		static QFont *m_font;
		static bool m_fixedPitch;
		static QFontMetrics *m_fontMetrics;
		static int m_leftMargin;
		static QDocument::WhiteSpaceMode m_showSpaces;
		static QDocument::LineEnding m_defaultLineEnding;
		static int m_lineHeight;
		static int m_lineSpacing;
		static int m_spaceWidth;
		static int m_ascent;
		static int m_descent;
		static int m_leading;
		static int m_wrapMargin;
		
		QFormatScheme *m_formatScheme;
		QLanguageDefinition *m_language;
		static QFormatScheme *m_defaultFormatScheme;
		
		QVector<QFont> m_fonts;
		
		static QList<QDocumentPrivate*> m_documents;
		
		int m_maxMarksPerLine;
		QHash<QDocumentLineHandle*, QList<int> > m_marks;
		QHash<QDocumentLineHandle*, QPair<int, int> > m_status;
		
		int _nix, _dos;
		QString m_lineEndingString;
		QDocument::LineEnding m_lineEnding;
		
		QVector<QDocumentLineHandle*> m_lines;
};

#endif
