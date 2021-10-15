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

#ifndef Header_QDocument_P
#define Header_QDocument_P

#include "qce-config.h"

/*!
	\file qdocument_p.h
	\brief Definition of the private document API
*/

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

#include <QHash>
#include <QFont>
#include <QStack>
#include <QQueue>
#include <QDateTime>
#include <QUndoStack>
#include <QStringList>
#include <QFontMetricsF>
#include <QUndoCommand>
#include <QCache>

class QDocument;
class QDocumentBuffer;
class QDocumentPrivate;
class QDocumentCommand;
class QDocumentCommandBlock;

class QLanguageDefinition;

Q_DECLARE_TYPEINFO(QDocumentSelection, Q_PRIMITIVE_TYPE);

#include "qdocumentline_p.h"

#include "qdocumentcursor_p.h"

class QCE_EXPORT QDocumentPrivate
{
	friend class QEditConfig;
	
	friend class QDocument;
	friend class QDocumentCommand;
	friend class QDocumentLineHandle;
	friend class QDocumentCursorHandle;
	
	public:
		struct DrawTextLineContext {
			/*! additional information passed to drawTextLine()
			 * This has been created as part of extract method drawTextLine.
			 * Part of the arguments are constants passed to drawTextLine,
			 * others may be modified during drawTextLine.
			 * The number of required variables can probably be reduced during
			 * further refactoring.
			 */
			int docLineNr;
			int editLineNr;
			int firstLine; /* constant */
            qreal pos;  /* vertical position */
            qreal visiblePos;
			bool inSelection;
			QBrush base; /* constant */
			QBrush alternate; /* constant */
		};

		QDocumentPrivate(QDocument *d);
		~QDocumentPrivate();
		
		void execute(QDocumentCommand *cmd);
		
		void draw(QPainter *p, QDocument::PaintContext& cxt);
		void drawTextLine(QPainter *p, QDocument::PaintContext &cxt, DrawTextLineContext &lcxt);
		void drawPlaceholders(QPainter *p, QDocument::PaintContext &cxt);
		void drawCursors(QPainter *p, const QDocument::PaintContext &cxt);

		QString exportAsHtml(const QDocumentCursor& range, bool includeHeader, bool simplifyCSS, int maxLineWidth, int maxWrap) const;

		QDocumentLineHandle* lineForPosition(int& position) const;
		int position(const QDocumentLineHandle *l) const;
		
		QDocumentLineHandle* at(int line) const;
		int indexOf(const QDocumentLineHandle *l, int hint = -1) const;
		
		QDocumentIterator index(const QDocumentLineHandle *l);
		QDocumentConstIterator index(const QDocumentLineHandle *l) const;
		
		QDocumentLineHandle* next(const QDocumentLineHandle *l) const;
		QDocumentLineHandle* previous(const QDocumentLineHandle *l) const;
		
		void adjustWidth(int l);
		//int checkWidth(QDocumentLineHandle *l, int w);
		//int checkWidth(QDocumentLineHandle *l, const QString& s);
		
		void setWidth();
		void setHeight();
		
        static void setBaseFont(const QFont& f, bool forceUpdate = false);
        static void setFontSizeModifier(int m, bool forceUpdate = false);
protected:
        static void setFont(const QFont& f, bool forceUpdate = false);
		static void updateStaticCaches(const QPaintDevice *pd);
		void updateInstanceCaches(const QPaintDevice *pd, QDocument::PaintContext &cxt);

public:
		void beginChangeBlock();
		void endChangeBlock();
		bool hasChangeBlocks();
		
		void beginDelayedUpdateBlock();
		void endDelayedUpdateBlock();
		
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
		void removeMarks(int id);
		
		
		int getNextGroupId();
		void releaseGroupId(int groupId);
		void clearMatches(int gid);
		//void clearMatchesFromToWhenFlushing(int groupId, int firstMatch, int lastMatch);
		void flushMatches(int gid);
		void addMatch(int gid, int line, int pos, int len, int format);
		
		void emitFormatsChange (int line, int lines);
		void emitContentsChange(int line, int lines);
		
		int visualLine(int textLine) const;
		int textLine(int visualLine, int *wrap = 0) const;
		void hideEvent(int line, int count);
		void showEvent(int line, int count);
		
		void setWidth(int width);
		void setHardLineWrap(bool wrap);
		void setLineWidthConstraint(bool wrap);
        void setCenterDocumentInEditor(bool center);
		void setCursorBold(bool bold);
		
		void emitFormatsChanged();
		void emitContentsChanged();
		
		void emitLineDeleted(QDocumentLineHandle *h);
		void emitMarkChanged(QDocumentLineHandle *l, int m, bool on);
		
		inline QDocumentIterator begin() { return m_lines.begin(); }
		inline QDocumentIterator end() { return m_lines.end(); }
		
		inline QDocumentConstIterator constBegin() const { return m_lines.constBegin(); }
		inline QDocumentConstIterator constEnd() const { return m_lines.constEnd(); }

		void markFormatCacheDirty();

		void addAutoUpdatedCursor(QDocumentCursorHandle* c);
		void removeAutoUpdatedCursor(QDocumentCursorHandle* c);
		void discardAutoUpdatedCursors(bool documentDeleted=false);

		static void setWorkAround(QDocument::WorkAroundFlag workAround, bool newValue);
		static bool hasWorkAround(QDocument::WorkAroundFlag workAround);


		static bool getFixedPitch();

		void setForceLineWrapCalculation(bool v);

		bool hardLineWrap() const{
			return m_hardLineWrap;
		}
		bool lineWidthConstraint() const{
			return m_lineWidthConstraint;
		}
		void removeWrap(int i);

		int width() const{
			return m_width;
		}

		int leftMarginAndPadding() const {
			return m_leftMargin + m_leftPadding;
		}

		QHash<QDocumentLineHandle*, QPair<int, int> > getStatus(){
		    return m_status;
		}

		void setOverwriteMode(bool overwrite){
		    m_overwrite=overwrite;
		}

		QList<int> testGetHiddenLines();
	protected:
		void updateHidden(int line, int count);
		void updateWrapped(int line, int count);
		
		void insertLines(int after, const QList<QDocumentLineHandle*>& l);
		void removeLines(int after, int n);
		
		void emitWidthChanged();
		void emitHeightChanged();
		void emitFontChanged();
		
		static void updateFormatCache(const QPaintDevice *pd);
		void setFormatScheme(QFormatScheme *f);
		void tunePainter(QPainter *p, int fid);

        qreal textWidthSingleLetterFallback(int fid, const QString& text);
        qreal textWidth(int fid, const QString& text);
        qreal getRenderRangeWidth(int &columnDelta, int curColumn, const RenderRange& r, const int newFont, const QString& text);
        void drawText(QPainter& p, int fid, const QColor& baseColor, bool selected, qreal &xpos, qreal baseline, const QString& text);
		
	private:
		QDocument *m_doc;
		QUndoStack m_commands;
		QDocumentCursor *m_editCursor;
		bool m_drawCursorBold;
		
		bool m_deleting;
		QStack<QDocumentCommandBlock*> m_macros;
		QList<QPair<int, int> > m_delayedUpdates;
		int m_delayedUpdateBlocks;
		
		QMap<int, int> m_hidden;
		QMap<int, int> m_wrapped; //map of wrapped lines, (line number => line breaks in logical line)
		QVector< QPair<QDocumentLineHandle*, int> > m_largest;
		
		struct Match
		{
			int line;
			QFormatRange range;
			QDocumentLineHandle *h;
		};
		
		struct MatchList : QList<Match>
		{
			MatchList() : removeLength(0), removeStart(0) {}
			
			int removeLength;
			int removeStart;
		};
		
		int m_lastGroupId;
		QList<int> m_freeGroupIds;
		QHash<int, MatchList> m_matches;
		
		bool m_constrained;
		bool m_hardLineWrap,m_lineWidthConstraint;
        qreal m_leftMargin;
        qreal m_width, m_height;
		
		int m_tabStop;
		static int m_defaultTabStop;

		static double m_lineSpacingFactor;
        bool m_centerDocumentInEditor;

        static QFont *m_baseFont;  // original font associated with the document
        static QFont *m_font;      // current font, pointSize = m_baseFont.pointSize + m_fontSizeModifier
        static int m_fontSizeModifier;
		static bool m_fixedPitch;
		static QDocument::WorkAroundMode m_workArounds;
        static qreal m_leftPadding;  // width between left edge of the document and start of the text
		static QDocument::WhiteSpaceMode m_showSpaces;
		static QDocument::LineEnding m_defaultLineEnding;
		static QTextCodec* m_defaultCodec;

		// caches
		static int m_staticCachesLogicalDpiY;
        static qreal m_lineHeight;
        static qreal m_lineSpacing;
        static qreal m_spaceWidth;
        static qreal m_ascent;
        static qreal m_descent;
        static qreal m_leading;
				
		static QVector<QFont> m_fonts;
        static QList<QFontMetricsF> m_fontMetrics;
        static CacheCache<qreal> m_fmtWidthCache;
		static CacheCache<QPixmap> m_fmtCharacterCache[2];

		static QFormatScheme *m_formatScheme;
		QLanguageDefinition *m_language;
		static QFormatScheme *m_defaultFormatScheme;

		static QList<QDocumentPrivate*> m_documents;
		
		int m_maxMarksPerLine;
		QHash<QDocumentLineHandle*, QList<int> > m_marks;
		QHash<QDocumentLineHandle*, QPair<int, int> > m_status;
		
		int _nix, _dos, _mac;
		QString m_lineEndingString;
		QDocument::LineEnding m_lineEnding;
		QTextCodec *m_codec;

		bool m_readOnly;
		QDateTime m_lastModified;
		QString m_fileName, m_name;
		QFileInfo m_fileInfo; 

		QVector<QDocumentLineHandle*> m_lines;

        QCache<QDocumentLineHandle*,QImage> m_LineCacheAlternative;
        QCache<QDocumentLineHandle*,QPixmap> m_LineCache;
        qreal m_lineCacheXOffset, m_lineCacheWidth;
		int m_instanceCachesLogicalDpiY;

		QList<QDocumentCursorHandle*> m_autoUpdatedCursorList;
		QHash<QDocumentCursorHandle*, int> m_autoUpdatedCursorIndex;

		bool m_forceLineWrapCalculation;

		bool m_overwrite;
};

#endif
