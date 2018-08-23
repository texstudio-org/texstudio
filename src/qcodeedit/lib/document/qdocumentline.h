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

#ifndef _QDOCUMENT_LINE_H_
#define _QDOCUMENT_LINE_H_

#include "qce-config.h"

/*!
	\file qdocumentline.h
	\brief Definition of the QDocumentLine class
*/

#include "qformat.h"

class QPoint;
class QString;

class QDocument;
class QDocumentLineHandle;

struct QNFAMatchContext;

struct QParenthesis
{
	enum Role
	{
		Open		= 1,
		Close		= 2,
		Indent		= 4,
		Fold		= 8,
		Match		= 16
	};
	
	inline QParenthesis()
	 : id(0), role(0), offset(0), length(0)
	{}
	
	inline QParenthesis(int i, quint8 r, int pos, int len)
	 : id(i), role(r), offset(pos), length(len)
	{}
	
	int id;
	int role;
	int offset;
	int length;
};

Q_DECLARE_TYPEINFO(QParenthesis, Q_MOVABLE_TYPE);

class QCE_EXPORT QDocumentLine
{
	friend class QDocumentLineHandle;
	friend class QDocumentCursorHandle;
	
	public:
		enum LineCookies {
			STACK_ENVIRONMENT_COOKIE = 1,
			DIFF_LIST_COOCKIE = 2,
			UNCLOSED_ENVIRONMENT_COOKIE = 3,
            LEXER_COOKIE = 4,
            LEXER_REMAINDER_COOKIE = 5,
            LEXER_RAW_COOKIE = 6,
            LEXER_COMMANDSTACK_COOKIE = 7,
			PICTURE_COOKIE = 42,
			PICTURE_COOKIE_DRAWING_POS = 43,
			GRAMMAR_ERROR_COOKIE = 44
		};

		enum State
		{
			None				= 0,
			Hidden				= 1,
			CollapsedBlockStart	= 2,
			CollapsedBlockEnd	= 4,
			
			LayoutDirty			= 16,
			FormatsApplied		= 32,
			LayoutedByQTextLayout	= 64
		};
		
        Q_DECLARE_FLAGS(States, State)
		
		explicit QDocumentLine(QDocument *doc);
		QDocumentLine(const QDocumentLine& line);
        QDocumentLine(QDocumentLineHandle *h = nullptr);
		
		~QDocumentLine();
		
		bool isNull() const;
		bool isValid() const;
		
		inline bool operator == (const QDocumentLineHandle* h) const
		{
			return m_handle == h;
		}
		
		inline bool operator != (const QDocumentLineHandle* h) const
		{
			return m_handle != h;
		}
		
		bool operator == (const QDocumentLine& l) const;
		bool operator != (const QDocumentLine& l) const;
		
		bool operator < (const QDocumentLine& l) const;
		bool operator >= (const QDocumentLine& l) const;
		
		bool operator > (const QDocumentLine& l) const;
		bool operator <= (const QDocumentLine& l) const;
			
		QDocumentLine& operator = (const QDocumentLine& l);

		QString text() const;
		
		int length() const;
		int lineSpan() const;
		
		int firstChar() const;
		int lastChar() const;
		bool startsWith(const QString &txt);
		
		int indent() const;
		
		int nextNonSpaceChar(int pos) const;
		int previousNonSpaceChar(int pos) const;

		inline QString indentation() const
		{ int idx = firstChar(); return idx != -1 ? text().left(idx) : text(); }
		
		inline bool isHidden() const
		{ return hasFlag(Hidden); }
		
		bool hasFlag(State s) const;
		bool hasAnyFlag(int s) const;
		void setFlag(State s, bool y = true);

		QDocument* document() const;
		
		int xToCursor(int x) const;
		int cursorToX(int cpos) const;
		
		int wrappedLineForCursor(int cpos) const;
		
		int documentOffsetToCursor(int x, int y) const;
		void cursorToDocumentOffset(int cpos, int& x, int& y) const;
		
		QPoint cursorToDocumentOffset(int cpos) const;
		
		void addMark(int id);
		void removeMark(int id);
		void toggleMark(int id);
		
		QList<int> marks() const;
		bool hasMark(int id) const;
		
		bool hasOverlay(int fid) const;
		QList<QFormatRange> overlays() const;
		
		void clearOverlays();
		void clearOverlays(int formatToClear);
		void clearOverlays(QList<int> formatsToClear);
		void addOverlay(const QFormatRange& over);
		void removeOverlay(const QFormatRange& over);
		bool hasOverlay(int id);
		QList<QFormatRange> getOverlays(int preferredFormat = -1) const;
		QFormatRange getOverlayAt(int index, int preferredFormat = -1) const;
		QFormatRange getFirstOverlay(int start = 0, int end = -1, int preferredFormat = -1) const;
		QFormatRange getLastOverlay(int start = 0, int end = -1, int preferredFormat = -1) const;
		
		void setFormats(const QVector<int>& formats);
		QVector<int> compose();
		QVector<int> getFormats();
		int getFormatAt(int pos);
		
		const QVector<QParenthesis>& parentheses() const;
		void setParentheses(const QVector<QParenthesis>& parentheses);
		
		inline QDocumentLineHandle* handle() const
		{ return m_handle; }
		
		QNFAMatchContext* matchContext();

		QVariant getCookie(int type);
		void setCookie(int type,QVariant data);
		void removeCookie(int type);

		bool isRTLByLayout() const;
		bool isRTLByText() const;
		QTextLayout* getLayout() const;
		int leftCursorPosition(int oldPos) const;
		int rightCursorPosition(int oldPos) const;
private:
		QDocumentLineHandle *m_handle;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDocumentLine::States)

#endif
