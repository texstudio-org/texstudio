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

#ifndef Header_QDocument
#define Header_QDocument

#include "modifiedQObject.h"

#include "qce-config.h"

/*!
	\file qdocument.h
	\brief Definition of the QDocument class

	\defgroup document Document related classes
*/

#include <QList>
#include <QMap>
#include <QVector>
#include <QFileInfo>
#include <QObject>
#include <QPalette>
#include <QMetaType>
#include <QFont>
#include <QTextCodec>

#include "qdocumentcursor.h"

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
//class QDocumentCursor;
class QDocumentPrivate;
class QDocumentCommand;
class QDocumentLineHandle;
class QDocumentCursorHandle;

typedef QVector<QDocumentLineHandle*>::iterator QDocumentIterator;
typedef QVector<QDocumentLineHandle*>::const_iterator QDocumentConstIterator;

template<typename T> class FastCache{
public:
	FastCache();
	T* insert(const int c, const T& width);
	bool contains(const int c) const;
	T value(const int c) const;
	bool valueIfThere(const int c, const T*& value) const;
	inline T* insert(const QChar& c, const T& width);
	inline bool contains(const QChar& c) const;
	inline T value(const QChar& c) const;
	inline bool valueIfThere(const QChar& c, const T*& value) const;
private:
	T fastMap[512];
	QMap<int, T> slowMap;
};

template<typename T> class CacheCache {
public:
	FastCache<T> * getCache(int format);
	void clear();
private:
	QMap<int, FastCache<T>* > caches;
};

Q_DECLARE_METATYPE(QDocumentIterator)
Q_DECLARE_METATYPE(QDocumentConstIterator)

typedef void (*GuessEncodingCallback) (const QByteArray& data, QTextCodec *&guess, int &sure);
class QKeyEvent;
struct PlaceHolder
{
	class Affector
	{
	public:
		virtual ~Affector() {}
		virtual QString affect(const QKeyEvent *e, const QString& base, int ph, int mirror) const = 0;
	};

	PlaceHolder() :
           length(0), autoRemove(true), autoOverride(false), autoRemoveIfLeft(false), affector(nullptr) {}
	PlaceHolder(const PlaceHolder& ph) :
	       length(ph.length), autoRemove(ph.autoRemove), autoOverride(ph.autoOverride), autoRemoveIfLeft(ph.autoRemoveIfLeft), affector(ph.affector), cursor(ph.cursor), mirrors(ph.mirrors){}
	PlaceHolder(int len, const QDocumentCursor &cur):
           length(len), autoRemove(true), autoOverride(false), autoRemoveIfLeft(false), affector(nullptr), cursor(cur) {}
	PlaceHolder& operator= (const PlaceHolder& ph) = default; // Silence -Wdeprecated-copy
    PlaceHolder& operator= (PlaceHolder&& ph) = default; // Silence -Wdeprecated-copy

	int length;
	bool autoRemove, autoOverride, autoRemoveIfLeft;
	Affector *affector;
	QDocumentCursor cursor;
	QList<QDocumentCursor> mirrors;
};

class QCE_EXPORT QDocument : public QObject
{
	friend class QMatcher;
	friend class QDocumentPrivate;
	friend class QDocumentCommand;
	friend class QDocumentCommandChangeCodec;

	Q_OBJECT

	public:
		struct PaintContext
		{
            qreal width;
            qreal height;
            qreal xoffset;  // draw content from position x+xoffset at position x (used for horizontal scrolling).
            qreal yoffset;
			QPalette palette;
			bool blinkingCursor;
			bool fillCursorRect;
			QList<QDocumentCursorHandle*> extra;
			QList<QDocumentCursorHandle*> cursors;
			QList<QDocumentSelection> selections;
            int curPlaceHolder;
			QList<PlaceHolder> placeHolders;
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

		enum WorkAroundFlag
		{
			DisableFixedPitchMode	= 0x01,
			DisableWidthCache		= 0x02,
			DisableLineCache            = 0x04,
			ForceQTextLayout            = 0x08,
            ForceSingleCharacterDrawing = 0x10,
            QImageCache = 0x20
		};

		Q_DECLARE_FLAGS(WorkAroundMode, WorkAroundFlag)

        explicit QDocument(QObject *p = nullptr);
		virtual ~QDocument();

		Q_INVOKABLE QString text(int mode) const;
		Q_INVOKABLE QString text(bool removeTrailing = false, bool preserveIndent = true) const;
		Q_INVOKABLE QStringList textLines() const;
		Q_INVOKABLE void setText(const QString& s, bool allowUndo);

		void load(const QString& file, QTextCodec* codec);
		void startChunkLoading();
		void stopChunkLoading();
		void addChunk(const QString& txt);

		QString getFileName() const;
		QFileInfo getFileInfo() const;
		QString getName() const;
		void setFileName_DONOTCALLTHIS(const QString& fileName);

		LineEnding lineEnding() const;
		LineEnding originalLineEnding() const;
		Q_INVOKABLE QString lineEndingString() const;
		void setLineEnding(LineEnding le);
        void setLineEndingDirect(LineEnding le,bool dontSendEmit=false);

		QTextCodec* codec() const;
		void setCodec(QTextCodec* codec);
		void setCodecDirect(QTextCodec* codec);

		bool isReadOnly() const;
		void setReadOnly(bool b);

		QDateTime lastModified() const;
		void setLastModified(const QDateTime& d);

		Q_INVOKABLE bool canUndo() const;
		Q_INVOKABLE bool canRedo() const;

        qreal width() const;
        qreal height() const;
        qreal widthConstraint() const;

		int lines() const;
		Q_INVOKABLE int lineCount() const;
		int visualLines() const;
		Q_INVOKABLE int visualLineCount() const;

		int visualLineNumber(int textLineNumber) const;
		int textLineNumber(int visualLineNumber) const;

        qreal y(int line) const;
        int lineNumber(qreal ypos, int *wrap = nullptr) const;

        QRectF lineRect(int line) const;

		QDocumentCursor* editCursor() const;
		void setEditCursor(QDocumentCursor *c);

		QLanguageDefinition* languageDefinition() const;
		void setLanguageDefinition(QLanguageDefinition *l);

		int maxMarksPerLine() const;
		int findNextMark(int id, int from = 0, int until = -1) const;
		int findPreviousMark(int id, int from = -1, int until = 0) const;
		void removeMarks(int id);
        QList<int> marks(QDocumentLineHandle *dlh) const;
        void removeMark(QDocumentLineHandle *dlh, int mid);

        QDocumentLine lineAt(const QPointF& p) const;
        void cursorForDocumentPosition(const QPointF& p, int& line, int& column, bool disallowPositionBeyondLine = false) const;
        QDocumentCursor cursorAt(const QPointF& p, bool disallowPositionBeyondLine = false) const;

		QDocumentLine line(int line) const;
		QDocumentLine line(QDocumentConstIterator iterator) const;

		Q_INVOKABLE QDocumentCursor cursor(int line, int column = 0, int lineTo=-1, int columnTo=-1) const;

		QDocumentLine findLine(int& position) const;
		int findLineContaining(const QString &searchText,  const int& startLine=0, const Qt::CaseSensitivity cs = Qt::CaseSensitive, const bool backward=false) const;
		int findLineRegExp(const QString &searchText,  const int& startLine, const Qt::CaseSensitivity cs, const bool wholeWord, const bool useRegExp) const;
		int findNearLine(const QString &lineText, int startLine) const;

		bool isLineModified(const QDocumentLine& l) const;
		bool hasLineEverBeenModified(const QDocumentLine& l) const;

		virtual void draw(QPainter *p, PaintContext& cxt);

		virtual QString exportAsHtml(const QDocumentCursor &range, bool includeHeader=true, bool simplifyCSS = false, int maxLineWidth = -1, int maxWrap = 0) const;

		void execute(QDocumentCommand *cmd);

		inline QDocumentPrivate* impl() { return m_impl; }

		QDocumentConstIterator begin() const;
		QDocumentConstIterator end() const;

		QDocumentConstIterator iterator(int ln) const;
		QDocumentConstIterator iterator(const QDocumentLine& l) const;

		Q_INVOKABLE void beginMacro();
		Q_INVOKABLE void endMacro();
		Q_INVOKABLE bool hasMacros();

		//Defer contentChange-signals until the last call of endDelayedUpdateBlock() and then emit all of them.
		//ATTENTION: This only works if the commands don't change the document line count or all changes occur top-to-bottom.
		Q_INVOKABLE void beginDelayedUpdateBlock();
		Q_INVOKABLE void endDelayedUpdateBlock();

		QFormatScheme* formatScheme() const;
		void setFormatScheme(QFormatScheme *f);
		QColor getBackground() const;
		QColor getForeground() const;

		int getNextGroupId();
		void releaseGroupId(int groupId);
		void clearMatches(int groupId);
		//void clearMatchesFromToWhenFlushing(int groupId, int firstMatch, int lastMatch);
		void flushMatches(int groupId);
		void addMatch(int groupId, int line, int pos, int len, int format);

		void clearLanguageMatches();

		static QFont font();
        static QFont baseFont();
        static int fontSizeModifier();
        static void setBaseFont(const QFont& f, bool forceUpdate = false);
        static void setFontSizeModifier(int m, bool forceUpdate = false);
		//static const QFontMetrics fontMetrics() const;
        static qreal getLineSpacing();
		static void setLineSpacingFactor(double scale);
        void setCenterDocumentInEditor(bool center);

		static LineEnding defaultLineEnding();
		static void setDefaultLineEnding(LineEnding le);

		static QTextCodec* defaultCodec();
		static void setDefaultCodec(QTextCodec* codec);
		static void addGuessEncodingCallback(const GuessEncodingCallback& callback);
		static void removeGuessEncodingCallback(const GuessEncodingCallback& callback);

		static int tabStop();
		static void setTabStop(int n);

		static WhiteSpaceMode showSpaces();
		static void setShowSpaces(WhiteSpaceMode y);

		static QFormatScheme* defaultFormatScheme();
		static void setDefaultFormatScheme(QFormatScheme *f);
		static void formatScheme(QFormatScheme *f);
		static void formatSchemeDeleted(QFormatScheme *f);

		int getFormatId(const QString& id);

		static int screenColumn(const QChar *d, int l, int tabStop, int column = 0);
		static QString screenable(const QChar *d, int l, int tabStop, int column = 0);

        inline void markViewDirty() { emit formatsChanged(); }

		bool isClean() const;

		Q_INVOKABLE void expand(int line);
		Q_INVOKABLE void collapse(int line);
		Q_INVOKABLE void expandParents(int l);
		Q_INVOKABLE void foldBlockAt(bool unFold, int line);
		bool linesPartiallyFolded(int fromInc, int toInc);
		void correctFolding(int fromInc, int toInc, bool forceCorrection = false);
		QList<int> foldedLines();
		void foldLines(QList<int> &lines);

		void adjustWidth(int line);

		static void setWorkAround(WorkAroundFlag workAround, bool newValue);
		static bool hasWorkAround(WorkAroundFlag workAround);

		bool getFixedPitch() const;

		bool forceLineWrapCalculation() const;
		void setForceLineWrapCalculation(bool v);
		void setOverwriteMode(bool overwrite);

		void applyHardLineWrap(const QList<QDocumentLineHandle*>& handles);
        bool linesMerged(QDocumentLineHandle* dlh,int bo,QDocumentLineHandle* fromLineHandle);
        void linesUnMerged(QDocumentLineHandle *dlh,QDocumentLineHandle *fromLineHandle);
        int bookMarkId(int bookmarkNumber);

        QDocumentCursor getProposedPosition(){
            return m_proposedPostion;
        }
        void setProposedPosition(QDocumentCursor c){
            m_proposedPostion=c;
        }

        QString debugUndoStack(int limit = 10000) const;

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
		void fontChanged(QFont);

		void formatsChange (int line, int lines);
		void contentsChange(int line, int lines);

		void widthChanged(int width);
		void heightChanged(int height);
		void sizeChanged(const QSize& s);

		void lineCountChanged(int n);
		void visualLineCountChanged(int n);

        void lineDeleted(QDocumentLineHandle *h,int hint=-1);
        void lineRemoved(QDocumentLineHandle *h);
        void linesRemoved(QDocumentLineHandle *h,int hint,int count);
		void markChanged(QDocumentLineHandle *l, int m, bool on);

		void lineEndingChanged(int lineEnding);

		void slowOperationStarted();
		void slowOperationEnded();

        void bookmarkRemoved(QDocumentLineHandle *dlh);
        void bookmarkAdded(QDocumentLineHandle *dlh,int nr);
	public:
		int indexOf(const QDocumentLineHandle* h, int hint = -1) const;
		int indexOf(const QDocumentLine& l, int hint = -1) const;
	private:
		QString m_leftOver;
		QDocumentPrivate *m_impl;
        QDocumentCursor m_proposedPostion;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDocument::WhiteSpaceMode)

#endif

