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

#ifndef Header_QEditor
#define Header_QEditor

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qeditor.h
	\brief Definition of the QEditor class
*/
 
#include "qdocument.h"
#include "qdocumentcursor.h"

#ifdef _QMDI_
	#include "qmdiclient.h"
#endif

class QMenu;
class QAction;
class QMimeData;
class QTextCodec;
class QActionGroup;

class QPropertyAnimation;

class QReliableFileWatch;

class QDocumentLineHandle;

class QLanguageDefinition;
class QCodeCompletionEngine;

class QEditorInputBindingInterface;

class QCE_EXPORT QEditor : public QAbstractScrollArea
#ifdef _QMDI_
, public qmdiClient
#endif
{
	friend class QEditConfig;
	friend class QEditorFactory;

	Q_OBJECT
	
	public:
		enum CodecUpdatePolicy
		{
			NoUpdate		= 0,
			UpdateOld		= 1,
			UpdateDefault	= 2,
			UpdateCustom	= 4,
			
			UpdateAll		= 7
		};
		
		enum EditFlag
		{
			None			= 0,
			
			Overwrite		= 0x01,
			CursorOn		= 0x02,
			ReadOnly		= 0x04,
			MousePressed	= 0x08,
			MaybeDrag		= 0x10,
			Selection		= 0x20,
			EnsureVisible	= 0x40,

			Internal		= 0x000000ff,
			
			LineWrap			= 0x00000100,
			HardLineWrap		= 0x00000200,
			LineWidthConstraint	= 0x00000400,

			AllowDragAndDrop	= 0x00000800,

			CtrlNavigation		= 0x00001000,
			CursorJumpPastWrap	= 0x00002000,

			SmoothScrolling     = 0x00004000,
			MouseWheelZoom      = 0x00008000,
			VerticalOverScroll  = 0x04000000,

			ReplaceIndentTabs		= 0x00010000,
			ReplaceTextTabs			= 0x00020000,
			RemoveTrailing			= 0x00040000,
			PreserveTrailingIndent	= 0x00080000,
			AdjustIndent			= 0x00100000,
			
			AutoCloseChars		= 0x00200000,
			AutoIndent			= 0x00400000,
			WeakIndent			= 0x00800000,
			AutoInsertLRM		= 0x01000000,
			BidiVisualColumnMode= 0x02000000,

			ShowPlaceholders	= 0x10000000,
			OverwriteOpeningBracketFollowedByPlaceholder = 0x20000000,
			OverwriteClosingBracketFollowingPlaceholder = 0x40000000,

			Accessible		= 0xffffff00
		};
		Q_DECLARE_FLAGS(State, EditFlag)

		enum EditOperation{
			NoOperation = 0,
			Invalid = -1,

			EnumForCursorStart = 0x1000,

			CursorUp,
			CursorDown,
			CursorLeft,
			CursorRight,
			CursorWordLeft,
			CursorWordRight,
			CursorStartOfLine,
            CursorStartOfLineText,
			CursorEndOfLine,
			CursorStartOfDocument,
			CursorEndOfDocument,

			CursorPageUp,
			CursorPageDown,

			EnumForSelectionStart = 0x2000,

			SelectCursorUp,
			SelectCursorDown,
			SelectCursorLeft,
			SelectCursorRight,
			SelectCursorWordLeft,
			SelectCursorWordRight,
			SelectCursorStartOfLine,
            SelectCursorStartOfLineText,
			SelectCursorEndOfLine,
			SelectCursorStartOfDocument,
			SelectCursorEndOfDocument,

			SelectPageUp,
			SelectPageDown,

			EnumForCursorEnd = 0x3000,

			DeleteLeft,
			DeleteRight,
			DeleteLeftWord,
			DeleteRightWord,
			NewLine,

			ChangeOverwrite = 0x4000,
			Undo,
			Redo,
			Copy,
			Paste,
			Cut,
			Print,
			SelectAll,
			Find,
			FindNext,
			FindPrevious,
			Replace,

			CreateMirrorUp = 0x5000,
			CreateMirrorDown,
			NextPlaceHolder,
			PreviousPlaceHolder,
			NextPlaceHolderOrWord,
			PreviousPlaceHolderOrWord,
			TabOrIndentSelection,
			InsertTab,
			IndentSelection,
			UnindentSelection,
			NextPlaceHolderOrChar,
			PreviousPlaceHolderOrChar
		};

		enum MoveFlagsEnum {
			NoFlags = 0x0000,
			Animated = 0x0001,
			KeepSurrounding = 0x0002,
			ExpandFold = 0x0004,
			AllowScrollToTop = 0x0008,

			// semantic abbreviations
			Navigation = Animated | KeepSurrounding | ExpandFold,
			NavigationToHeader = Animated | KeepSurrounding | ExpandFold | AllowScrollToTop,

			KeepDistanceFromViewTop = 0x1000
		};
		Q_DECLARE_FLAGS(MoveFlags, MoveFlagsEnum)

		/*
		struct PlaceHolder
		{
			class Affector
			{
				public:
					virtual ~Affector() {}
					virtual void affect(const QStringList& base, int ph, const QKeyEvent *e, int mirror, QString& after) const = 0;
			};
			
			PlaceHolder() : length(0), autoRemove(true), autoOverride(false), affector(0) {}
			PlaceHolder(const PlaceHolder& ph) : length(ph.length), autoRemove(ph.autoRemove), autoOverride(ph.autoOverride), affector(ph.affector)
			{
				cursor = ph.cursor;
				mirrors  << ph.mirrors;
			}
			PlaceHolder(int len, const QDocumentCursor &cur): length(len), autoRemove(true), autoOverride(false), affector(0), cursor(cur) {}
			
			int length;
			bool autoRemove, autoOverride;
			Affector *affector;
			QDocumentCursor cursor;
			QList<QDocumentCursor> mirrors;
		};
		*/
        QEditor(QWidget *p = nullptr);
        QEditor(bool actions, QWidget *p = nullptr, QDocument *doc=nullptr);
        QEditor(const QString& s, QWidget *p = nullptr);
        QEditor(const QString& s, bool actions, QWidget *p = nullptr);
		virtual ~QEditor();
		
		bool flag(EditFlag) const;
		
		Q_INVOKABLE bool canUndo() const;
		Q_INVOKABLE bool canRedo() const;
		
		Q_INVOKABLE QString text() const;
		Q_INVOKABLE QString text(int line) const;
		
		Q_INVOKABLE QDocument* document() const;
		
		QList<QEditorInputBindingInterface*> inputBindings() const;
		
		Q_INVOKABLE bool isCursorVisible() const;
		QDocumentCursor cursor() const;
		Q_PROPERTY(QDocumentCursor cursor READ cursor WRITE setCursor DESIGNABLE false STORED false);
		QDocumentCursorHandle* cursorHandle() const;
		
		Q_INVOKABLE int cursorMirrorCount() const;
		Q_INVOKABLE QDocumentCursor cursorMirror(int i) const;
		
		Q_INVOKABLE QList<QDocumentCursor> cursors() const;

		QLanguageDefinition* languageDefinition() const;
		QCodeCompletionEngine* completionEngine() const;
		
		QAction* action(const QString& s);
		
        virtual QRectF cursorRect() const;
        virtual QRectF selectionRect() const;
        virtual QRectF lineRect(int line) const;
        virtual QRectF cursorRect(const QDocumentCursor& c) const;
        virtual QRectF cursorMircoFocusRect() const;

		
		virtual int getFirstVisibleLine();
		virtual int getLastVisibleLine();

		Q_INVOKABLE virtual void scrollToFirstLine(int l);

		void setCursorSurroundingLines(int s);
			
		Q_INVOKABLE QString name() const;
		Q_INVOKABLE QString fileName() const;
		Q_INVOKABLE QFileInfo fileInfo() const;

		Q_INVOKABLE bool isReadOnly() const;
		Q_INVOKABLE void setReadOnly(bool b);

		Q_INVOKABLE bool isContentModified() const;
		
		Q_INVOKABLE bool isInConflict() const;
		Q_INVOKABLE QTextCodec* getFileCodec() const;
		Q_INVOKABLE void setFileCodec(QTextCodec* codec);
		void viewWithCodec(QTextCodec* codec);
		
		int wrapWidth() const;

		bool displayModifyTime() const;
		void setDisplayModifyTime(bool flag) {mDisplayModifyTime=flag;}

		bool ignoreExternalChanges() const {return mIgnoreExternalChanges;}
		void setIgnoreExternalChanges(bool flag) {mIgnoreExternalChanges=flag;}

		bool silentReloadOnExternalChanges() const {return mSilentReloadOnExternalChanges;}
		void setSilentReloadOnExternalChanges(bool flag) {mSilentReloadOnExternalChanges=flag;}
		void setUseQSaveFile(bool flag) {m_useQSaveFile=flag;}

        inline qreal horizontalOffset() const
        {
#if defined Q_OS_MAC
            return horizontalScrollBar()->value();
#else
            return horizontalScrollBar()->isVisible() ? horizontalScrollBar()->value() : 0;
#endif
        }
        inline qreal verticalOffset() const
        {
#if defined Q_OS_MAC
            return verticalScrollBar()->value() * m_doc->getLineSpacing();  // does this work always ?
#else
            return verticalScrollBar()->isVisible() ? 1. * verticalScrollBar()->value() * m_doc->getLineSpacing() : 0;
#endif
        }
		
		inline QPoint mapToContents(const QPoint &point) const
		{
			return QPoint(	point.x() + horizontalOffset(),
							point.y() + verticalOffset() );
		}
		
		inline QPoint mapFromContents(const QPoint &point) const
		{
			return QPoint(	point.x() - horizontalOffset(),
							point.y() - verticalOffset() );
		}
		
		inline QPoint mapFromFrame(const QPoint &point) const
		{
			return QPoint(	point.x() + m_margins.left(),
							point.y() + m_margins.top() );
		}

		inline QPoint mapToFrame(const QPoint &point) const
		{
			return QPoint(	point.x() - m_margins.left(),
							point.y() - m_margins.top() );
		}

		virtual bool protectedCursor(const QDocumentCursor& c) const;

		static int defaultFlags();
		static void setDefaultFlags(int f);
				
		static QEditorInputBindingInterface* registeredInputBinding(const QString& n);
		static QString defaultInputBindingId();
		static QStringList registeredInputBindingIds();
		static void registerInputBinding(QEditorInputBindingInterface *b);
		static void unregisterInputBinding(QEditorInputBindingInterface *b);
		static void setDefaultInputBinding(QEditorInputBindingInterface *b);
		static void setDefaultInputBinding(const QString& b);
		static inline const QList<QEditor*>& editors() { return m_editors; }		

		static QString translateEditOperation(const EditOperation& op);
        static void setEditOperations(const QHash<QString, int>& newOptions, bool mergeWithDefault=false);
        static QHash<QString, int> getEditOperations(bool excludeDefault=false);
		static QSet<int> getAvailableOperations();
		static void registerEditOperation(const EditOperation& op);
		static void addEditOperation(const EditOperation& op, const Qt::KeyboardModifiers& modifiers, const Qt::Key& key);
		static void addEditOperation(const EditOperation& op, const QKeySequence::StandardKey& key);
		EditOperation getEditOperation(const Qt::KeyboardModifiers& modifiers, const Qt::Key& key);

		void disableAccentHack(bool disable){
		    m_disableAccentHack=disable;
		}

        void addMark(int pos,QColor color,QString type="");
        void addMarkDelayed(int pos, QColor color, QString type);
        void addMark(QDocumentLineHandle *dlh, QColor color, QString type="");
        void addMarkRange(int start,int end,QColor color,QString type="");
        void removeMark(int pos, QString type="");
        void removeMark(QDocumentLineHandle *dlh,QString type="");
        void removeMark(QString type);
        void removeAllMarks();
        void paintMarks();

	public slots:
		void undo();
		void redo();
		
		void cut();
		void copy();
		void paste();
		
		void selectAll();
		void selectNothing();
		void selectExpand(QDocumentCursor::SelectionType selectionType);
		void selectExpandToNextWord();
		void selectExpandToNextLine();
		void selectAllOccurences();
		void selectNextOccurence();
		void selectPrevOccurence();
		void selectNextOccurenceKeepMirror();
		void selectPrevOccurenceKeepMirror();
		void selectOccurence(bool backward, bool keepMirrors, bool all);

		void relayPanelCommand(const QString& panel, const QString& command, const QList<QVariant>& args = QList<QVariant>());

		void find();
		void find(QString text, bool highlight, bool regex, bool word=false, bool caseSensitive=false);
		void find(QString text, bool highlight, bool regex, bool word, bool caseSensitive, bool fromCursor, bool selection);
		void findInSameDir();
		void findNext();
		void findPrev();
		void findCount();
		void selectAllMatches();
		void replacePanel();
		void replaceNext();
		void replacePrev();
		void replaceAll();

		void gotoLine();
		
	protected:
		void insertTab(QDocumentCursor &cur);
    public slots:
		void tabOrIndentSelection();
		void insertTab();
		void indentSelection();
		void unindentSelection();
		
		void commentSelection();
		void uncommentSelection();
		void toggleCommentSelection();
		
		void setLineWrapping(bool on);
		void setHardLineWrapping(bool on);
		void setSoftLimitedLineWrapping(bool on);
		void setWrapAfterNumChars(int numChars);
protected:
        void setWrapLineWidth(qreal l);
		bool writeToFile(const QString &filename, const QByteArray &data);
public:		
		virtual void save();
		void save(const QString& filename);
		bool saveCopy(const QString& filename);
		void saveEmergencyBackup(const QString& filename);

        bool preEditSet;
        int preEditLineNumber,preEditColumnNumber,preEditLength,m_preEditFormat;
public slots:
		
		virtual void print();
		
		virtual void retranslate();
		
		virtual void write(const QString& s);
		
		void addAction(QAction *a, const QString& menu, const QString& toolbar = QString());
		void removeAction(QAction *a, const QString& menu, const QString& toolbar = QString());
		
		void load(const QString& file, QTextCodec* codec/* = QTextCodec::codecForLocale()*/);
		void reload();
		
		void setText(const QString& s, bool allowUndo = true);
		
		void setDocument(QDocument *d);
		
		void addInputBinding(QEditorInputBindingInterface *b);
		void removeInputBinding(QEditorInputBindingInterface *b);
		void setInputBinding(QEditorInputBindingInterface *b);
		
		void setCursor(const QDocumentCursor& c, bool moveView = true);
		
		void setLanguageDefinition(QLanguageDefinition *d);
		
		void setCompletionEngine(QCodeCompletionEngine *e);
		
		void zoomIn();
		void zoomOut();
		void resetZoom();
		void zoom(int n);
		
        void setPanelMargins(qreal l, qreal t, qreal r, qreal b);
        void getPanelMargins(qreal *l, qreal *t, qreal *r, qreal *b) const;
		
		void setTitle(const QString& title);
		
		void highlight();
		
		void clearPlaceHolders();
		void addPlaceHolder(const PlaceHolder& p, bool autoUpdate = true);
		void addPlaceHolderMirror(int placeHolderId, const QDocumentCursor& c);
		void removePlaceHolder(int id);
		void replacePlaceHolders(const QList<PlaceHolder>& newPlaceholders);
				
		int placeHolderCount() const;
		int currentPlaceHolder() const;
		const PlaceHolder& getPlaceHolder(int i) const;
		QList<PlaceHolder> getPlaceHolders();
		bool isAutoOverrideText(const QString& s) const;
		void resizeAutoOverridenPlaceholder(const QDocumentCursor& start, int length);

		bool nextPlaceHolder();
		bool previousPlaceHolder();
		void setPlaceHolder(int i, bool selectCursors=true);
		
		virtual void setFileName(const QString& f);
		
	signals:
		void loaded(QEditor *e, const QString& s);
		void saved(QEditor *e, const QString& s);
		
		void contentModified(bool y);
		void readOnlyChanged(bool y);
		void titleChanged(const QString& title);
		void focusReceived();
		
		void textEdited(QKeyEvent *e);
		void cursorPositionChanged();
		
		void copyAvailable(bool y);
		
		void undoAvailable(bool y);
		void redoAvailable(bool y);
		
		void markChanged(const QString& f, QDocumentLineHandle *l, int mark, bool on);

		void hovered(QPoint pos);

		void fileReloaded();
		void fileInConflict();
		void fileInConflictShowDiff();
		void fileAutoReloading(QString fname);
		void needUpdatedCompleter();
        void requestClose();

		void cursorHovered();

		void emitWordDoubleClicked();
		
		void visibleLinesChanged();
		
		void slowOperationStarted();
		void slowOperationEnded();
	public slots:
		void checkClipboard();
		void reconnectWatcher();
		void fileChanged(const QString& f);
		
		void setContentClean(bool y);
		
		void emitCursorPositionChanged();
		void ensureCursorVisible(const QDocumentCursor& cursor, MoveFlags mflags = NoFlags);
		void ensureCursorVisible(MoveFlags mflags = NoFlags);
		
		virtual void setContentModified(bool y);

		void emitNeedUpdatedCompleter();
		
	protected:
		void setVerticalScrollBarMaximum();
		virtual bool event(QEvent *e);
		
		virtual void paintEvent(QPaintEvent *e);
		virtual void timerEvent(QTimerEvent *e);
		
		virtual void keyPressEvent(QKeyEvent *e);
		virtual void keyReleaseEvent(QKeyEvent *);
	public:
		virtual void inputMethodEvent(QInputMethodEvent* e);
		
		virtual void mouseMoveEvent(QMouseEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		virtual void mouseDoubleClickEvent(QMouseEvent *e);
		
		virtual void dragEnterEvent(QDragEnterEvent *e);
		virtual void dragLeaveEvent(QDragLeaveEvent *e);
		virtual void dragMoveEvent(QDragMoveEvent *e);
		virtual void dropEvent(QDropEvent *e);
		
		virtual void changeEvent(QEvent *e);
		virtual void showEvent(QShowEvent *);
		virtual void wheelEvent(QWheelEvent *e);
		virtual void resizeEvent(QResizeEvent *e);
		virtual void focusInEvent(QFocusEvent *e);
		virtual void focusOutEvent(QFocusEvent *e);
		
		virtual void contextMenuEvent(QContextMenuEvent *e);
		
		virtual void closeEvent(QCloseEvent *e);
		
		virtual bool focusNextPrevChild(bool next);
		
		virtual void cursorMoveOperation(QDocumentCursor &cursor, EditOperation op);
		virtual void processEditOperation(QDocumentCursor& c, const QKeyEvent* e, EditOperation op);
		
		void selectCursorMirrorBlock(const QDocumentCursor& cursor, bool horizontalSelect);

		virtual void startDrag();
		virtual QMimeData* createMimeDataFromSelection() const;
		
		virtual void scrollContentsBy(int dx, int dy);

		virtual QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
	public:
		virtual void insertFromMimeData(const QMimeData *d);

		void setFlag(EditFlag f, bool b);
		void setDoubleClickSelectionType(QDocumentCursor::SelectionType type) {m_doubleClickSelectionType = type;}
		void setTripleClickSelectionType(QDocumentCursor::SelectionType type) {m_tripleClickSelectionType = type;}

	public slots:
		void pageUp(QDocumentCursor::MoveMode moveMode);
		void pageDown(QDocumentCursor::MoveMode moveMode);

		void repaintCursor();
		void ensureVisible(int line);
        void ensureVisible(const QRectF &rect);
		
	protected:
		void preInsertUnindent(QDocumentCursor& c, const QString& text, int additionalUnindent);

	public slots:
		void insertText(QDocumentCursor& c, const QString& text);
		void insertText(const QString& text);

	public:
		QDocumentLine lineAtPosition(const QPoint& p) const;
        QDocumentCursor cursorForPosition(const QPoint& p, bool disallowPositionBeyondLine = false) const;
		
		void setClipboardSelection();
		void setCursorPosition(const QPoint& p, bool moveView = true);
		
		void setCursorPosition(int line, int index, bool moveView = true);
		void getCursorPosition(int &line, int &index);
		bool getPositionBelowCursor(QPointF &offset, int width, int height, bool &above);
		bool getPositionBelowCursor(QPointF &offset, int width=0, int height=0);

		Q_INVOKABLE void clearCursorMirrors();
		Q_INVOKABLE void addCursorMirror(const QDocumentCursor& c);
		Q_INVOKABLE void cursorMirrorsRemoveSelectedText();

		void setCursorBold(bool bold);

		QString cutBuffer;

	protected slots:
		void documentWidthChanged(int newWidth);
		void documentHeightChanged(int newWidth);
		
		void repaintContent(int i, int n);
		void updateContent (int i, int n);
		
		void markChanged(QDocumentLineHandle *l, int mark, bool on);
		
		void bindingSelected(QAction *a);
		
		void lineEndingSelected(QAction *a);
		void lineEndingChanged(int lineEnding);
		
	protected:
		enum SaveState
		{
			Undefined,
			Saving,
			Saved,
			Conflict
		};
		
		void init(bool actions = true,QDocument *doc=0);
		void updateBindingsMenu();
			
		QMenu *pMenu;
		QHash<QString, QAction*> m_actions;
		
		QMenu *m_lineEndingsMenu;
		QActionGroup *m_lineEndingsActions;
		
		QMenu *m_bindingsMenu;
		QAction *aDefaultBinding;
		QActionGroup *m_bindingsActions;
		
		char m_saveState;
		quint16 m_checksum;

		QDocument *m_doc;
		QList<QEditorInputBindingInterface*> m_bindings;
		
		QLanguageDefinition *m_definition;
		QPointer<QCodeCompletionEngine> m_completionEngine;
		
		QDocumentCursor m_cursor, m_multiClickCursor, m_dragAndDrop;
		QDocumentCursor::SelectionType m_doubleClickSelectionType;
		QDocumentCursor::SelectionType m_tripleClickSelectionType;
		int m_cursorLinesFromViewTop;
		int m_cursorMirrorBlockAnchor;
		
		QList<QDocumentCursor> m_mirrors;
		
		bool atPlaceholder();
        bool isMirrored();
        int m_curPlaceHolder, m_cphOffset;
		bool m_placeHolderSynchronizing; 
		
		QList<PlaceHolder> m_placeHolders;
		
		int m_state;
		bool m_selection;
        QRectF m_crect, m_margins;
		QPoint m_clickPoint, m_dragPoint;
		QBasicTimer m_blink, m_click, m_drag, m_autoScroll;

		bool mDisplayModifyTime;
		bool mIgnoreExternalChanges;
		bool mSilentReloadOnExternalChanges;
		bool m_useQSaveFile;
		
		static QReliableFileWatch* watcher();
		
		static int m_defaultFlags;
		
		static QList<QEditor*> m_editors;
		static QEditorInputBindingInterface *m_defaultBinding;
		static QHash<QString, QEditorInputBindingInterface*> m_registeredBindings;
		
		static bool m_defaultKeysSet;
        static QHash<QString, int> m_registeredKeys;
		static QSet<int> m_registeredOperations;
        static QHash<QString, int> m_registeredDefaultKeys;

		static int m_manageMenu;

		bool m_UseTabforMoveToPlaceholder;

		bool m_blockKey,m_disableAccentHack;

		int m_lastLine,m_lastColumn,m_hoverCount;

		int m_cursorSurroundingLines;
		
        int m_LineWidth;
		int m_wrapAfterNumChars;

		QPropertyAnimation *m_scrollAnimation;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QEditor::State)
Q_DECLARE_OPERATORS_FOR_FLAGS(QEditor::MoveFlags)

inline bool QEditor::atPlaceholder() {
	return m_curPlaceHolder >= 0 && m_curPlaceHolder<m_placeHolders.count();
}

const int LRM = 0x200E;

#endif
