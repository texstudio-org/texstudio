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

#ifndef _QEDITOR_H_
#define _QEDITOR_H_

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
			
			Overwrite		= 0x001,
			CursorOn		= 0x002,
			ReadOnly		= 0x004,
			MousePressed	= 0x008,
			MaybeDrag		= 0x010,
			Selection		= 0x020,
			EnsureVisible	= 0x040,
			
			Internal				= 0x00000fff,
			
			LineWrap				= 0x00001000,
			
			CtrlNavigation			= 0x00010000,
			CursorJumpPastWrap		= 0x00020000,
			
			ReplaceTabs				= 0x00100000,
			RemoveTrailing			= 0x00200000,
			PreserveTrailingIndent	= 0x00400000,
			AdjustIndent			= 0x00800000,
			
			AutoCloseChars			= 0x01000000,
			AutoIndent				= 0x02000000,
			WeakIndent				= 0x04000000,
			
			Accessible				= 0xfffff000
		};
		
		Q_DECLARE_FLAGS(State, EditFlag)
		
		struct PlaceHolder
		{
			class Affector
			{
				public:
					virtual ~Affector() {}
					virtual void affect(const QStringList& base, int ph, const QKeyEvent *e, int mirror, QString& after) const = 0;
			};
			
			PlaceHolder() : length(0), autoRemove(true), affector(0) {}
			PlaceHolder(const PlaceHolder& ph) : length(ph.length), autoRemove(ph.autoRemove), affector(ph.affector)
			{
				cursor = ph.cursor;
				mirrors  << ph.mirrors;
			}
			PlaceHolder(int len, const QDocumentCursor &cur): length(len), autoRemove(true),  affector(0), cursor(cur) {}
			
			int length;
			bool autoRemove;
			Affector *affector;
			QDocumentCursor cursor;
			QList<QDocumentCursor> mirrors;
		};
		
		QEditor(QWidget *p = 0);
		QEditor(bool actions, QWidget *p = 0, QDocument *doc=0);
		QEditor(const QString& s, QWidget *p = 0);
		QEditor(const QString& s, bool actions, QWidget *p = 0);
		virtual ~QEditor();
		
		bool flag(EditFlag) const;
		
		bool canUndo() const;
		bool canRedo() const;
		
		Q_INVOKABLE QString text() const;
		Q_INVOKABLE QString text(int line) const;
		
		QDocument* document() const;
		
		QList<QEditorInputBindingInterface*> inputBindings() const;
		
		bool isCursorVisible() const;
		QDocumentCursor cursor() const;
		QDocumentCursorHandle* cursorHandle() const;
		
		int cursorMirrorCount() const;
		QDocumentCursor cursorMirror(int i) const;
		
		QLanguageDefinition* languageDefinition() const;
		QCodeCompletionEngine* completionEngine() const;
		
		QAction* action(const QString& s);
		
		virtual QRect cursorRect() const;
		virtual QRect selectionRect() const;
		virtual QRect lineRect(int line) const;
		virtual QRect lineRect(const QDocumentLine& l) const;
		virtual QRect cursorRect(const QDocumentCursor& c) const;
		
		#ifndef _QMDI_
		QString name() const;
		QString fileName() const;
		QFileInfo fileInfo() const;
		
		bool isContentModified() const;
		#endif
		
		bool isInConflict() const;
		QTextCodec* getFileCodec() const;
		void setFileCodec(QTextCodec* codec);
		void viewWithCodec(QTextCodec* codec);
		
		int wrapWidth() const;

		bool displayModifyTime();
		void setDisplayModifyTime(bool flag) {mDisplayModifyTime=flag;}
		inline int horizontalOffset() const
		{ return horizontalScrollBar()->isVisible() ? horizontalScrollBar()->value() : 0; }
		inline int verticalOffset() const
		{ return verticalScrollBar()->isVisible() ? verticalScrollBar()->value() * m_doc->getLineSpacing() : 0; }
		
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
	public slots:
		void undo();
		void redo();
		
		void cut();
		void copy();
		void paste();
		
		void selectAll();
		void selectNothing();
		
		void find();
		void find(QString text, bool highlight, bool regex, bool word=false, bool caseSensitive=false);
                void find(QString text, bool highlight, bool regex, bool word, bool caseSensitive, bool fromCursor, bool selection);
		void findNext();
		void replace();
		
		void gotoLine();
		
		void indentSelection();
		void unindentSelection();
		
		void commentSelection();
		void uncommentSelection();
		
		void setLineWrapping(bool on);
		
		virtual void save();
		void save(const QString& filename);
		
		virtual void print();
		
		virtual void retranslate();
		
		virtual void write(const QString& s);
		
		void addAction(QAction *a, const QString& menu, const QString& toolbar = QString());
		void removeAction(QAction *a, const QString& menu, const QString& toolbar = QString());
		
		void load(const QString& file, QTextCodec* codec/*= QTextCodec::codecForLocale()*/);
		
		void setText(const QString& s);
		
		void setDocument(QDocument *d);
		
		void addInputBinding(QEditorInputBindingInterface *b);
		void removeInputBinding(QEditorInputBindingInterface *b);
		void setInputBinding(QEditorInputBindingInterface *b);
		
		void setCursor(const QDocumentCursor& c);
		
		void setLanguageDefinition(QLanguageDefinition *d);
		
		void setCompletionEngine(QCodeCompletionEngine *e);
		
		void zoom(int n);
		
		void setPanelMargins(int l, int t, int r, int b);
		void getPanelMargins(int *l, int *t, int *r, int *b) const;
		
		void setTitle(const QString& title);
		
		void highlight();
		
		void clearPlaceHolders();
		void addPlaceHolder(const PlaceHolder& p, bool autoUpdate = true);
		void addPlaceHolderMirror(int placeHolderId, const QDocumentCursor& c);
		void removePlaceHolder(int id);
				
		int placeHolderCount() const;
		int currentPlaceHolder() const;
		const PlaceHolder& getPlaceHolder(int i) const;
		
		bool nextPlaceHolder();
		bool previousPlaceHolder();
		void setPlaceHolder(int i, bool selectCursors=true);
		
		virtual void setFileName(const QString& f);
		
	signals:
		void loaded(QEditor *e, const QString& s);
		void saved(QEditor *e, const QString& s);
		
		void contentModified(bool y);
		void titleChanged(const QString& title);
		
		void textEdited(QKeyEvent *e);
		void cursorPositionChanged();
		
		void copyAvailable(bool y);
		
		void undoAvailable(bool y);
		void redoAvailable(bool y);
		
		void markChanged(const QString& f, QDocumentLineHandle *l, int mark, bool on);

		void hovered(QPoint pos);

		void fileReloaded();
		void fileAutoReloading(QString fname);
		void updateCompleter();

		void cursorHovered();
		
	public slots:
		void checkClipboard();
		void reconnectWatcher();
		void fileChanged(const QString& f);
		
		void setContentClean(bool y);
		
		void emitCursorPositionChanged();
		void ensureCursorVisible();
		
		virtual void setContentModified(bool y);

		void updateCompleterNow();
		void completerNeedsUpdate();
		
	protected:
		virtual bool event(QEvent *e);
		
		virtual void paintEvent(QPaintEvent *e);
		virtual void timerEvent(QTimerEvent *e);
		
		virtual void keyPressEvent(QKeyEvent *e);
		
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
		
		virtual bool moveKeyEvent(QDocumentCursor& c, QKeyEvent *e, bool *leave);
		virtual bool isProcessingKeyEvent(QKeyEvent *e);
		virtual bool processCursor(QDocumentCursor& c, QKeyEvent *e, bool& b);
		
		virtual void startDrag();
		virtual QMimeData* createMimeDataFromSelection() const;
		
		virtual void scrollContentsBy(int dx, int dy);
	public:
		virtual void insertFromMimeData(const QMimeData *d);

		void setFlag(EditFlag f, bool b);
		
	public slots:
		void pageUp(QDocumentCursor::MoveMode moveMode);
		void pageDown(QDocumentCursor::MoveMode moveMode);
		
		void selectionChange(bool force = false);
		
		void repaintCursor();
		void ensureVisible(int line);
		void ensureVisible(const QRect &rect);
		
	protected:
		void preInsert(QDocumentCursor& c, const QString& text);

	public slots:
		void insertText(QDocumentCursor& c, const QString& text);
		void insertText(const QString& text);

	public:
		QDocumentLine lineAtPosition(const QPoint& p) const;
		QDocumentCursor cursorForPosition(const QPoint& p) const;
		
		void setClipboardSelection();
		void setCursorPosition(const QPoint& p);
		
		void setCursorPosition(int line, int index);
		void getCursorPosition(int &line, int &index);
		
		void clearCursorMirrors();
		void addCursorMirror(const QDocumentCursor& c);

		void setUseLineForSearch(bool b)
		{m_UseLineForSearch=b;}
		bool UseLineForSearch()
		{return m_UseLineForSearch;}

		void setUseTabforMoveToPlaceholder(bool b){
			m_UseTabforMoveToPlaceholder=b;
		}
		bool UseTabforMoveToPlaceholder(){
			return m_UseTabforMoveToPlaceholder;
		}

		QString cutBuffer;
		int cutLineNumber;
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
		
		#ifndef _QMDI_
		QString m_name, m_fileName;
		QFileInfo m_fileInfo; 
		#endif
		
		QMenu *pMenu;
		QHash<QString, QAction*> m_actions;
		
		QMenu *m_lineEndingsMenu;
		QActionGroup *m_lineEndingsActions;
		
		QMenu *m_bindingsMenu;
		QAction *aDefaultBinding;
		QActionGroup *m_bindingsActions;
		
		char m_saveState;
		quint16 m_checksum;
		
		bool mCompleterNeedsUpdate;

		QDocument *m_doc;
		QList<QEditorInputBindingInterface*> m_bindings;
		
		QLanguageDefinition *m_definition;
		QPointer<QCodeCompletionEngine> m_completionEngine;
		
		QDocumentCursor m_cursor, m_doubleClick, m_dragAndDrop;
		
		QList<QDocumentCursor> m_mirrors;
		
		int m_curPlaceHolder, m_lastPlaceHolder, m_cphOffset;
		bool m_placeHolderSynchronizing; 
		
		QList<PlaceHolder> m_placeHolders;
		
		int m_state;
		bool m_selection;
		QRect m_crect, m_margins;
		QPoint m_clickPoint, m_dragPoint;
		QBasicTimer m_blink, m_scroll, m_click, m_drag;

		bool mDisplayModifyTime;
		
		static QReliableFileWatch* watcher();
		
		static int m_defaultFlags;
		
		static QList<QEditor*> m_editors;
		static QEditorInputBindingInterface *m_defaultBinding;
		static QHash<QString, QEditorInputBindingInterface*> m_registeredBindings;
		
		static int m_manageMenu;

		bool m_UseLineForSearch;
		bool m_UseTabforMoveToPlaceholder;

                bool m_blockKey;

		int m_lastLine,m_lastColumn,m_hoverCount;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QEditor::State);

#endif
