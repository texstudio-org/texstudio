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

#ifndef _QDOCUMENT_H_
#define _QDOCUMENT_H_

#include "qce-config.h"

/*!
	\file qdocument.h
	\brief Definition of the QDocument class
	
	\defgroup document Document related classes 
*/

#include <QList>
#include <QMap>
#include <QVector>
#include <QLinkedList>

#include <QObject>
#include <QPalette>
#include <QMetaType>

class QFont;
class QRect;
class QPrinter;
class QDateTime;
class QFormatScheme;
class QLanguageDefinition;

struct QCE_EXPORT QDocumentSelection
{
	int start, end;
	int startLine, endLine;
};

class QDocumentLine;
class QDocumentCursor;
class QDocumentPrivate;
class QDocumentCommand;
class QDocumentLineHandle;
class QDocumentCursorHandle;

typedef QVector<QDocumentLineHandle*>::iterator QDocumentIterator;
typedef QVector<QDocumentLineHandle*>::const_iterator QDocumentConstIterator;

typedef QMap<QChar,int> WCache;

Q_DECLARE_METATYPE(QDocumentIterator)
Q_DECLARE_METATYPE(QDocumentConstIterator)

class QCE_EXPORT QDocument : public QObject
{
	friend class QMatcher;
	friend class QDocumentPrivate;
	friend class QDocumentCommand;
	
	Q_OBJECT
	
	public:
		struct PaintContext
		{
			int width;
			int height;
			int xoffset;
			int yoffset;
			QPalette palette;
			bool blinkingCursor;
			bool fillCursorRect;
			QList<QDocumentCursorHandle*> extra;
			QList<QDocumentCursorHandle*> cursors;
			QList<QDocumentSelection> selections;
		};
		
		enum LineEnding
		{
			Conservative,
			Local,
			Unix,
			Windows,
			Mac
		};
		
		enum TextProcessing
		{
			RemoveTrailingWS		= 1,
			PreserveIndent			= 2,
			RestoreTrailingIndent	= 4
		};
		
		enum WhiteSpaceFlag
		{
			ShowNone		= 0x00,
			ShowTrailing	= 0x01,
			ShowLeading		= 0x02,
			ShowTabs		= 0x04
		};
		
		Q_DECLARE_FLAGS(WhiteSpaceMode, WhiteSpaceFlag)
		
		explicit QDocument(QObject *p = 0);
		virtual ~QDocument();
		
		QString text(int mode) const;
		QString text(bool removeTrailing = false, bool preserveIndent = true) const;
		QStringList textLines() const;
		void setText(const QString& s);
		
		void load(const QString& file, QTextCodec* codec);
		void startChunkLoading();
		void stopChunkLoading();
		void addChunk(const QString& txt);
		
		LineEnding lineEnding() const;
		LineEnding originalLineEnding() const;
		QString lineEndingString() const;
		void setLineEnding(LineEnding le);
		
		QTextCodec* codec() const;
		void setCodec(QTextCodec* codec);

		QDateTime lastModified() const;
		void setLastModified(const QDateTime& d);
		
		bool canUndo() const;
		bool canRedo() const;
		
		int width() const;
		int height() const;
		int widthConstraint() const;
		
		int lines() const;
		int lineCount() const;
		int visualLines() const;
		int visualLineCount() const;
		
		int visualLineNumber(int textLineNumber) const;
		int textLineNumber(int visualLineNumber) const;
		
		int y(int line) const;
		int lineNumber(int ypos, int *wrap = 0) const;
		int y(const QDocumentLine& l) const;
		
		QRect lineRect(int line) const;
		QRect lineRect(const QDocumentLine& l) const;
		
		QDocumentCursor* editCursor() const;
		void setEditCursor(QDocumentCursor *c);
				
		QLanguageDefinition* languageDefinition() const;
		void setLanguageDefinition(QLanguageDefinition *l);
		
		int maxMarksPerLine() const;
		int findNextMark(int id, int from = 0, int until = -1) const;
		int findPreviousMark(int id, int from = -1, int until = 0) const;
		void removeMarks(int id);
		
		QDocumentLine lineAt(const QPoint& p) const;
		void cursorForDocumentPosition(const QPoint& p, int& line, int& column) const;
		QDocumentCursor cursorAt(const QPoint& p) const;
		
		QDocumentLine line(int line) const;
		QDocumentLine line(QDocumentConstIterator iterator) const;
		
		QDocumentCursor cursor(int line, int column = 0, int lineTo=-1, int columnTo=-1) const;
		
		QDocumentLine findLine(int& position) const;
		int findLineContaining(const QString &searchText,  const int& startLine=0, const Qt::CaseSensitivity cs = Qt::CaseSensitive, const bool backward=false) const;
		int findLineRegExp(const QString &searchText,  const int& startLine, const Qt::CaseSensitivity cs, const bool wholeWord, const bool useRegExp) const;
		
		bool isLineModified(const QDocumentLine& l) const;
		bool hasLineEverBeenModified(const QDocumentLine& l) const;
		
		virtual void draw(QPainter *p, PaintContext& cxt);
		
		void execute(QDocumentCommand *cmd);
		
		inline QDocumentPrivate* impl() { return m_impl; }
		
		QDocumentConstIterator begin() const;
		QDocumentConstIterator end() const;
		
		QDocumentConstIterator iterator(int ln) const;
		QDocumentConstIterator iterator(const QDocumentLine& l) const;
		
		void beginMacro();
		void endMacro();
		bool hasMacros();
		
		QFormatScheme* formatScheme() const;
		void setFormatScheme(QFormatScheme *f);
		
		int getNextGroupId();
		void releaseGroupId(int groupId);
		void clearMatches(int groupId);
		//void clearMatchesFromToWhenFlushing(int groupId, int firstMatch, int lastMatch);
		void flushMatches(int groupId);
		void addMatch(int groupId, int line, int pos, int len, int format);
		
		static QFont font();
		static void setFont(const QFont& f);
		static const QFontMetrics fontMetrics();
		
		static LineEnding defaultLineEnding();
		static void setDefaultLineEnding(LineEnding le);

		static QTextCodec* defaultCodec();
		static void setDefaultCodec(QTextCodec* codec);
		
		static int tabStop();
		static void setTabStop(int n);
		
		static WhiteSpaceMode showSpaces();
		static void setShowSpaces(WhiteSpaceMode y);
		
		static QFormatScheme* defaultFormatScheme();
		static void setDefaultFormatScheme(QFormatScheme *f);
		
		static QFormatScheme* formatFactory();
		static void setFormatFactory(QFormatScheme *f);
		
		static int screenLength(const QChar *d, int l, int tabStop);
		static QString screenable(const QChar *d, int l, int tabStop);
		
		inline void markViewDirty() { formatsChanged(); }
		
		bool isClean() const;
		
		void expand(int line);
		void collapse(int line);
		void expandParents(int l);
		void foldBlockAt(bool unFold, int line);
		bool linesPartiallyFolded(int fromInc, int toInc);
		void correctFolding(int fromInc, int toInc);

	public slots:
		void clear();
		
		void undo();
		void redo();

		void clearUndo();
		
		void setClean();
		
		void highlight();
		
		void print(QPrinter *p);
		
		void clearWidthConstraint();
		void setWidthConstraint(int width);
		void markFormatCacheDirty();
		
	signals:
		void cleanChanged(bool m);
		
		void undoAvailable(bool y);
		void redoAvailable(bool y);
		
		void formatsChanged();
		void contentsChanged();
		
		void formatsChange (int line, int lines);
		void contentsChange(int line, int lines);
		
		void widthChanged(int width);
		void heightChanged(int height);
		void sizeChanged(const QSize& s);
		
		void lineCountChanged(int n);
		void visualLineCountChanged(int n);
		
		void lineDeleted(QDocumentLineHandle *h);
		void lineRemoved(QDocumentLineHandle *h);
		void markChanged(QDocumentLineHandle *l, int m, bool on);
		
		void lineEndingChanged(int lineEnding);
		
	private:
		QString m_leftOver;
		QDocumentPrivate *m_impl;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDocument::WhiteSpaceMode)

#endif

