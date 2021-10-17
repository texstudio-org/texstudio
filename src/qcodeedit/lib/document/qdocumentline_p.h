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

#ifndef Header_QDocument_Line_P
#define Header_QDocument_Line_P

#include "qce-config.h"

/*!
	\file qdocumentline_p.h
	\brief Definition of QDocumentLineHandle
*/

#include "qnfa.h"

#include "qformat.h"

#include "qdocumentline.h"

#include <QPair>
#include <QList>
#include <QString>
#include <QVector>

#include <QTextLayout>

#include <QReadWriteLock>

#include <QAtomicInt>

class QPoint;

class QDocument;
class QDocumentLine;
class QDocumentBuffer;
class QDocumentPrivate;
struct RenderRange;

class QCE_EXPORT QDocumentLineHandle
{
	friend class QDocument;
	friend class QDocumentLine;
	friend class QDocumentBuffer;
	friend class QDocumentPrivate;

	public:
		QDocumentLineHandle(QDocument *d);
		QDocumentLineHandle(const QString& s, QDocument *d);

		int count() const;
		int length() const;

		int position() const;

		QString text() const;
//private:
//		int line() const;
public:
		int xToCursor(int x) const;
		int cursorToX(int i) const;
		qreal cursorToXNoLock(int i) const;

		int wrappedLineForCursor(int cpos) const;
		int wrappedLineForCursorNoLock(int cpos) const;

        int documentOffsetToCursor(qreal x, qreal y, bool disallowPositionBeyondLine = false) const;
		void cursorToDocumentOffset(int cpos, qreal &x, qreal &y) const;

		QPointF cursorToDocumentOffset(int cpos) const;

		int indent() const;

		int nextNonSpaceChar(uint pos) const;
		int previousNonSpaceChar(int pos) const;
		int nextNonSpaceCharNoLock(uint pos) const;
		int previousNonSpaceCharNoLock(int pos) const;

		bool hasFlag(int flag) const;
		void setFlag(int flag, bool y = true) const;

		QDocument* document() const;

		void updateWrap(int lineNr) const;
		void updateWrapAndNotifyDocument(int ownLineNumber) const;

		void setFormats(const QVector<int>& formats);

		void clearOverlays();
		void clearOverlays(int format);
		void clearOverlays(QList<int> formats);
		void addOverlay(const QFormatRange& over);
		void addOverlayNoLock(const QFormatRange& over);
		void removeOverlay(const QFormatRange& over);
		bool hasOverlay(int id);
		QList<QFormatRange> getOverlays(int preferredFormat) const;
		QFormatRange getOverlayAt(int index, int preferredFormat) const;
		QFormatRange getFirstOverlay(int start = 0, int end = -1, int preferredFormat = -1) const;
		QFormatRange getLastOverlay(int start = 0, int end = -1, int preferredFormat = -1) const;

		void shiftOverlays(int position, int offset);

        void draw(int lineNr,
                    QPainter *p,
                    qreal xOffset,
                    qreal vWidth,
                    const QVector<int>& selectionBoundaries,
                    const QPalette& pal,
                    bool fullSel,
                    qreal yStart=0,
                    qreal yEnd=-1) const;

		QString exportAsHtml(int fromOffset=0, int toOffset = -1, int maxLineWidth = -1, int maxWrap = 0) const;

		inline QString& textBuffer() { setFlag(QDocumentLine::LayoutDirty, true); return m_text; }

		inline void ref() { m_ref.ref(); }
		inline void deref() { if ( !m_ref.deref() ) delete this; }
		int getRef(){ return m_ref.fetchAndAddRelaxed(0); }

		QList<int> getBreaks();
		void clearFrontiers(){
		    m_frontiers.clear();
		}

		~QDocumentLineHandle();

		QVector<int> compose() const;
		QVector<int> getFormats() const;
		QVector<int> getCachedFormats() const;

		void lockForRead() const {
		    mLock.lockForRead();
		}
		void lockForWriteText() {
		    mLock.lockForWrite();
		    mTicket++;
		}
		void lockForWrite() {
		    mLock.lockForWrite();
		}
		void unlock() const {
		    mLock.unlock();
		}

		int getCurrentTicket(){
		    return mTicket;
		}

		QVariant getCookie(int type) const;
		QVariant getCookieLocked(int type) const;
		void setCookie(int type,QVariant data);
		bool hasCookie(int type) const;
		bool removeCookie(int type);

		bool isRTLByLayout() const;
		bool isRTLByText() const;
		void layout(int lineNr) const; //public for unittests
	private:
		void drawBorders(QPainter *p, qreal yStart, qreal yEnd) const;

		void applyOverlays() const;
		void splitAtFormatChanges(QList<RenderRange>* ranges, const QVector<int>* sel = nullptr, int from = 0, int until = -1) const;

        qreal getPictureCookieHeight() const;

		template <template<class T> class CONTAINER_TYPE>
		CONTAINER_TYPE<QTextLayout::FormatRange> decorations() const;

		QString m_text;
		QDocument *m_doc;

		QAtomicInt m_ref;

        mutable qreal m_indent;
		mutable quint16 m_state;
		mutable QTextLayout *m_layout;
		mutable QVector<int> m_cache;
        mutable QVector< QPair<int, qreal> > m_frontiers; //list of line wraps, <character, x in pixel (if it were unwrapped) >

		QNFAMatchContext m_context;

		QVector<int> m_formats;
		QVector<QParenthesis> m_parens;
		QList<QFormatRange> m_overlays;

		enum SelectionState {noSel,partialSel,fullSel};
		SelectionState lineHasSelection;
		QBitmap wv;
		mutable QReadWriteLock mLock;
		int mTicket; // increment on each write access to detect obsolete info in parallel thread
		QMap<int,QVariant> mCookies; // store additional info on lines. Helpful for to retrieve info on multiline commands
};

Q_DECLARE_TYPEINFO(QDocumentLineHandle*, Q_PRIMITIVE_TYPE);
Q_DECLARE_METATYPE(QDocumentLineHandle*)

#endif // !_QDOCUMENT_LINE_P_H_
