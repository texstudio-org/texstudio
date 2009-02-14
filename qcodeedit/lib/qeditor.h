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

#include "qce-config.h"

/*!
	\file qeditor.h
	\brief Definition of the QEditor class
*/

#include <QHash>
#include <QPointer>
#include <QScrollBar>
#include <QBasicTimer>
#include <QAbstractScrollArea>
#include <QTextCodec>
 
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
			
			Persistent		= 0x040,
			Multiline		= 0x080,
			FoldedCursor	= 0x100,
			
			Internal				= 0x00000fff,
			
			LineWrap				= 0x00001000,
			
			CtrlNavigation			= 0x00010000,
			CursorJumpPastWrap		= 0x00020000,
			
			ReplaceTabs				= 0x00100000,
			RemoveTrailing			= 0x00200000,
			PreserveTrailingIndent	= 0x00400000,
			
			AutoCloseChars			= 0x01000000,
			AutoIndent				= 0x02000000,
			
			Accessible				= 0xfffff000
		};
		
		class InputBinding
		{
			public:
				virtual ~InputBinding() {}
				
				virtual QString id() const = 0;
				virtual QString name() const = 0;
				
				virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}
				
				virtual void postKeyPressEvent(QKeyEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool inputMethodEvent(QInputMethodEvent* event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}
				
				virtual void postInputMethodEvent(QInputMethodEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool mouseMoveEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}

				virtual void postMouseMoveEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool mousePressEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}
				
				virtual void postMousePressEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool mouseReleaseEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}
				
				virtual void postMouseReleaseEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
					return false;
				}
				
				virtual void postMouseDoubleClickEvent(QMouseEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)
				}
				
				virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor)
				{
					Q_UNUSED(event)
					Q_UNUSED(editor)

					return false;
				}
		};
		
		Q_DECLARE_FLAGS(State, EditFlag)
		
		struct PlaceHolder
		{
			class Affector
			{
				public:
					virtual ~Affector() {}
					virtual QString affect(const QString& base, int i) = 0;
			};
			
			PlaceHolder() : length(0), affector(0) {}
			PlaceHolder(const PlaceHolder& ph) : length(ph.length), affector(ph.affector)
			{
				cursor = ph.cursor;
				mirrors << ph.mirrors;
			}
			
			int length;
			Affector *affector;
			QDocumentCursor cursor;
			QList<QDocumentCursor> mirrors;
		};
		
		QEditor(QWidget *p = 0);
		QEditor(bool actions, QWidget *p = 0);
		QEditor(const QString& s, QWidget *p = 0);
		QEditor(const QString& s, bool actions, QWidget *p = 0);
		virtual ~QEditor();
		
		bool flag(EditFlag) const;
		
		bool canUndo() const;
		bool canRedo() const;
		
		QString text() const;
		QString text(int line) const;
		
		QTextCodec* codec() const;
		QDocument* document() const;
		InputBinding* inputBinding() const;
		
		bool isCursorVisible() const;
		QDocumentCursor cursor() const;
		
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
		
		bool isContentModified() const;
		#endif
		
		bool isInConflict() const;
		QTextCodec* getFileEncoding() const;
		void setFileEncoding(QTextCodec* codec);
		void setFileEncoding(char* name);
		void setFileEncoding(int mib);
		
		int wrapWidth() const;
		
		inline int horizontalOffset() const
		{ return horizontalScrollBar()->isVisible() ? horizontalScrollBar()->value() : 0; }
		inline int verticalOffset() const
		{ return verticalScrollBar()->isVisible() ? verticalScrollBar()->value() : 0; }
		
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
		
		static int defaultFlags();
		static void setDefaultFlags(int f);
		
		static QTextCodec* defaultCodec();
		static void setDefaultCodec(int mib, int update);
		static void setDefaultCodec(QTextCodec *c, int update);
		static void setDefaultCodec(const char *name, int update);
		static void setDefaultCodec(const QByteArray& name, int update);
		
		static QStringList inputBindings();
		static QString defaultInputBinding();
		static void addInputBinding(InputBinding *b);
		static void removeInputBinding(InputBinding *b);
		static void setDefaultInputBinding(InputBinding *b);
		static void setDefaultInputBinding(const QString& b);
	public slots:
		void undo();
		void redo();
		
		void cut();
		void copy();
		void paste();
		
		void selectAll();
        void selectNothing();
		
		void find();
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
		
		void load(const QString& file, QTextCodec* codec= QTextCodec::codecForLocale());
		
		void setText(const QString& s);
		
		void setCodec(int mib);
		void setCodec(QTextCodec *c);
		void setCodec(const char *name);
		void setCodec(const QByteArray& name);
		
		void setDocument(QDocument *d);
		void setInputBinding(InputBinding *b);
		
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
		
		int placeHolderCount() const;
		
		void nextPlaceHolder();
		void previousPlaceHolder();
		void setPlaceHolder(int i);
		
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
		
	public slots:
		void checkClipboard();
		void reconnectWatcher();
		void fileChanged(const QString& f);
		
		void setContentClean(bool y);
		
		void emitCursorPositionChanged();
		
		virtual void setContentModified(bool y);
		
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
		virtual bool isProcessingKeyEvent(QKeyEvent *e, int *offset = 0);
		virtual bool processCursor(QDocumentCursor& c, QKeyEvent *e, bool& b);
		
		virtual void startDrag();
		virtual QMimeData* createMimeDataFromSelection() const;
		virtual void insertFromMimeData(const QMimeData *d);
		
		virtual void scrollContentsBy(int dx, int dy);
		
		// got to make it public for bindings
	public:
		void setFlag(EditFlag f, bool b);
		
		void pageUp(QDocumentCursor::MoveMode moveMode);
		void pageDown(QDocumentCursor::MoveMode moveMode);
		
		void selectionChange(bool force = false);
		
		void repaintCursor();
		void ensureCursorVisible();
		void ensureVisible(int line);
		void ensureVisible(const QRect &rect);
		
		void insertText(QDocumentCursor& c, const QString& text);
		
		QDocumentLine lineAtPosition(const QPoint& p) const;
		QDocumentCursor cursorForPosition(const QPoint& p) const;
		
		void setClipboardSelection();
		void setCursorPosition(const QPoint& p);
		
		void setCursorPosition(int line, int index);
		void getCursorPosition(int &line, int &index);
		
		void clearCursorMirrors();
		void addCursorMirror(const QDocumentCursor& c);
		
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
		
		void init(bool actions = true);
		void updateBindingsMenu();
		
		#ifndef _QMDI_
		QString m_name, m_fileName;
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
		
		QDocument *m_doc;
		QTextCodec *m_codec;
		InputBinding *m_binding;
		
		QLanguageDefinition *m_definition;
		QPointer<QCodeCompletionEngine> m_completionEngine;
		
		QDocumentCursor m_cursor, m_doubleClick, m_dragAndDrop;
		
		QList<QDocumentCursor> m_mirrors;
		
		int m_curPlaceHolder, m_cphOffset;
		QList<PlaceHolder> m_placeHolders;
		
		int m_state;
		bool m_selection;
		QRect m_crect, m_margins;
		QPoint m_clickPoint, m_dragPoint;
		QBasicTimer m_blink, m_scroll, m_click, m_drag;
		
		static QReliableFileWatch* watcher();
		
		static int m_defaultFlags;
		static QTextCodec *m_defaultCodec;
		
		static QList<QEditor*> m_editors;
		static InputBinding *m_defaultBinding;
		static QHash<QString, InputBinding*> m_bindings;
		
		static int m_manageMenu;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QEditor::State);

#endif
