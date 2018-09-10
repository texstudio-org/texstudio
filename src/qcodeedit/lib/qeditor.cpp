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

#include "qeditor.h"

/*!
	\file qeditor.cpp
	\brief Implementation of the QEditor class
*/

#include "qeditorinputbindinginterface.h"

#include "qdocument.h"
#include "qdocument_p.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"
#include "qformatscheme.h"

#include "qlanguagedefinition.h"
#include "qcodecompletionengine.h"

#include "qcodeedit.h"
#include "qpanellayout.h"
#include "qgotolinedialog.h"
#include "qlinemarksinfocenter.h"

#include "qreliablefilewatch.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexparser.h"
#include <QDrag>

#include "libqmarkedscrollbar/src/markedscrollbar.h"

#if QT_VERSION >= 0x040600
#include <QPropertyAnimation>
#endif

#if QT_VERSION >= 0x050100
#include <QSaveFile>
#endif

#ifdef Q_OS_MAC
#include <QSysInfo>
#endif

#include <QPrinter>
#include <QPrintDialog>
//#define Q_GL_EDITOR

#ifdef _QMDI_
#include "qmdiserver.h"
#endif

#ifdef _EDYUK_
#include "edyukapplication.h"
#include "qshortcutmanager.h"

#define Q_SHORTCUT(a, s, c) EDYUK_SHORTCUT(a, tr(c), tr(s))
#else
#define Q_SHORTCUT(a, s, c) a->setShortcut( QKeySequence( tr(s, c) ) )
#endif

#ifdef Q_GL_EDITOR
#include <QGLWidget>
#endif

#define QCE_ACTION(name, action) { QAction *_a_ = m_actions.value(name); if ( _a_ ) _a_ action; }
#define QCE_TR_ACTION(name, label) { QAction *_a_ = m_actions.value(name); if ( _a_ ) _a_->setText(label); }
#define QCE_ENABLE_ACTION(name, yes) { QAction *_a_ = m_actions.value(name); if ( _a_ ) _a_->setEnabled(yes); }

/*!
	\ingroup editor
	@{

	\class QEditor
	\brief A text editing widget

	QEditor is the central widget in QCE. It allows user to view and edit a
	document.

	QEditor has an API similar to that of QTextEdit and it behaves in a very
	similar way.

	Notable differences are :
	<ul>
	<li>QEditor can be given an InputBinding which can change the way it
	handle user inputs which enables such things as implementing emacs-like
	or Vi-like editing (almost) effortlessly.</li>
	<li>QEditor has actions instead of hard coded shortcuts and expose them
	so that, among other things, they can be easily added to menus/toolbars
	and their shortcuts can be changed</li>
	<li>QEditor brings the notion of cursor mirrors. Column selection and
	column editing are just special use case of cursor mirrors.</li>
	<li>QEditor brings the notion of placeholders, snippets-editing is just
	as special use case of placeholders.</li>
	<li>QEditor allows easy encodings management</li>
	</ul>

	QEditor can gain features when it is managed by a QCodeEdit class which
	is responsible for panels management.
*/


/*!
	\enum QEditor::CodecUpdatePolicy
	\brief Specify the actions to take when changing the default codec

*/


/*!
	\enum QEditor::EditFlag
	\brief Flag holding information about the state of an editor

	Some of these are public and can be modified freely and some
	others are only meant to be used internally though they can
	still be read.

*/

/*!
	\struct QEditor::PlaceHolder
	\brief A small structure holding placeholder data

	Placeholders are basically lists of cursors. When several palceholders coexist, it is
	possible to navigate among them using the key assigned to that function by the current
	input binding (CTRL+arrows by default).

	Each placeholder consist of a primary cursor and a list of mirrors (modeling the internals
	of QEditor and allowing extended snippet replacements easily).
	
	Additionaly a placeholder can have an Affector which allows the text of the mirrors to be
	modified in any imaginable way
*/

/*!
	\class QEditor::PlaceHolder::Affector
	\brief A small class allowing "placeholder scripting"
	
	The purpose of this class is to affect/process/reformat (whichever word you understand/like
	most) the content of placeholder mirrors.
	
	The main placeholder instance (primary cursor) will always contain the text typed by the user,
	only mirrors can be affected.
	
	To allow a large panel of processing to be done the affector is passed the following data :
	<ul>
		<li>A stringlist containing placeholder contents (primary cursor of all placeholders present in the editor)
		<li>The index of the current placeholder among these
		<li>The key event leading to a modification of the current placeholder
		<li>The index of the current mirror
		<li>A reference to the text of that placeholder mirror. This text has already been modified according
		to the key event. The original text can be retrieved from the first argument (stringlist). This text
		can be modified in any way you see fit or left as it is.
	</ul>
*/

////////////////////////////////////////////////////////////////////////
//	Bindings handling
////////////////////////////////////////////////////////////////////////

QList<QEditor*> QEditor::m_editors;
QEditorInputBindingInterface* QEditor::m_defaultBinding = nullptr;
QHash<QString, QEditorInputBindingInterface*> QEditor::m_registeredBindings;
bool QEditor::m_defaultKeysSet = false;
QHash<QString, int> QEditor::m_registeredKeys;
QSet<int> QEditor::m_registeredOperations;
QHash<QString, int> QEditor::m_registeredDefaultKeys;


/*!
	\return A list of available input bindings
*/
QStringList QEditor::registeredInputBindingIds()
{
	return m_registeredBindings.keys();
}

/*!
	\return the name of the default input binding

	\note The "Default" name (or its translation, obtained via QEditor::tr())
	is used to indicate that no default input binding has been set.
*/
QString QEditor::defaultInputBindingId()
{
	return m_defaultBinding ? m_defaultBinding->name() : tr("Default");
}

/*!
	\brief Add an input binding to make it available for all editors
*/
void QEditor::registerInputBinding(QEditorInputBindingInterface *b)
{
	m_registeredBindings[b->id()] = b;

	foreach ( QEditor *e, m_editors )
		e->updateBindingsMenu();

}

/*!
	\brief Remove an input binding from the pool of publicly available ones
*/
void QEditor::unregisterInputBinding(QEditorInputBindingInterface *b)
{
	m_registeredBindings.remove(b->id());

	foreach ( QEditor *e, m_editors )
		e->updateBindingsMenu();

}

/*!
	\brief Set the default input binding

	\note This does not change the current input binding of existing editors
*/
void QEditor::setDefaultInputBinding(QEditorInputBindingInterface *b)
{
	m_defaultBinding = b;
}

/*!
	\brief Set the default input binding

	\note If no binding of the given name is available the default (null)
	binding will be set back as default binding.

	\note This does not change the current input binding of existing editors
*/
void QEditor::setDefaultInputBinding(const QString& b)
{
	m_defaultBinding = m_registeredBindings.value(b);
}
////////////////////////////////////////////////////////////////////////

/*!
	\return A pointer to the global "reliable" file monitor used by QEditor to avoid file conflicts

	The point of using a custom file watcher is to work around a bug (limitation) of QFileSystemWatcher
	which sometimes emit multiple signals for a single file save. It also enables to use a single
	object shared by all QEditor instances and reduce memory footprint.
*/
QReliableFileWatch* QEditor::watcher()
{
	static QPointer<QReliableFileWatch> _qce_shared;

	if ( !_qce_shared )
		_qce_shared = new QReliableFileWatch;

	return _qce_shared;
}

////////////////////////////////////////////////////////////////////////

int QEditor::m_defaultFlags = QEditor::MouseWheelZoom | QEditor::AutoIndent | QEditor::AdjustIndent | QEditor::AutoCloseChars | QEditor::ShowPlaceholders;

/*!
	\return The default flags set to every QEditor upon construction
	\note the default flags are a configuration-oriented feature which only expose "user" flags
*/
int QEditor::defaultFlags()
{
	return m_defaultFlags;
}

/*!
	\brief Set the default editor flags

	Setting editor flags result in them being applied to ALL existing editors
	and editors to be created later on.

	These can of course be modified on a per-editor basis later on.
*/
void QEditor::setDefaultFlags(int flags)
{
	m_defaultFlags = flags & Accessible;

	foreach ( QEditor *e, m_editors )
	{
		bool ontoWrap = (m_defaultFlags & LineWrap) && !(e->m_state & LineWrap);
		bool outOfWrap = !(m_defaultFlags & LineWrap) && (e->m_state & LineWrap);

		e->m_state &= Internal;
		e->m_state |= m_defaultFlags;

		if ( ontoWrap )
		{
			e->document()->setWidthConstraint(e->wrapWidth());
		} else if ( outOfWrap ) {
			e->document()->clearWidthConstraint();
		}

		QAction *a = e->m_actions.value("wrap");

		if ( a && (a->isChecked() != (bool)(e->m_state & LineWrap)) )
			a->setChecked(e->m_state & LineWrap);

	}
}

/*!
	\brief ctor

	\note Creates builtin menus/actions
*/
QEditor::QEditor(QWidget *p)
 : QAbstractScrollArea(p),
    pMenu(nullptr), m_lineEndingsMenu(nullptr), m_lineEndingsActions(nullptr),
    m_bindingsMenu(nullptr), aDefaultBinding(nullptr), m_bindingsActions(nullptr),
    m_doc(nullptr), m_definition(nullptr),
	m_doubleClickSelectionType(QDocumentCursor::WordOrCommandUnderCursor), m_tripleClickSelectionType(QDocumentCursor::LineUnderCursor),
	m_curPlaceHolder(-1), m_placeHolderSynchronizing(false), m_state(defaultFlags()),
    mDisplayModifyTime(true), m_blockKey(false), m_disableAccentHack(false), m_LineWidth(0), m_wrapAfterNumChars(0), m_scrollAnimation(nullptr)
{
	m_editors << this;

	m_saveState = Undefined;
	
	init();
}

/*!
	\brief ctor
	\param actions Whether builtin actions and menus should be created
*/
QEditor::QEditor(bool actions, QWidget *p,QDocument *doc)
 : QAbstractScrollArea(p),
    pMenu(nullptr), m_lineEndingsMenu(nullptr), m_lineEndingsActions(nullptr),
    m_bindingsMenu(nullptr), aDefaultBinding(nullptr), m_bindingsActions(nullptr),
    m_doc(nullptr), m_definition(nullptr),
	m_doubleClickSelectionType(QDocumentCursor::WordOrCommandUnderCursor), m_tripleClickSelectionType(QDocumentCursor::ParenthesesOuter),
	m_curPlaceHolder(-1), m_placeHolderSynchronizing(false), m_state(defaultFlags()),
    mDisplayModifyTime(true), m_blockKey(false), m_disableAccentHack(false), m_LineWidth(0), m_wrapAfterNumChars(0), m_scrollAnimation(nullptr)
{
	m_editors << this;

	m_saveState = Undefined;

	init(actions,doc);
}


/*!
	\brief ctor
	\param s file to load

	\note Creates builtin menus/actions
*/
QEditor::QEditor(const QString& s, QWidget *p)
 : QAbstractScrollArea(p),
    pMenu(nullptr), m_lineEndingsMenu(nullptr), m_lineEndingsActions(nullptr),
    m_bindingsMenu(nullptr), aDefaultBinding(nullptr), m_bindingsActions(nullptr),
    m_doc(nullptr), m_definition(nullptr), m_curPlaceHolder(-1), m_placeHolderSynchronizing(false), m_state(defaultFlags()),
        mDisplayModifyTime(true),m_blockKey(false),m_disableAccentHack(false),m_LineWidth(0),m_scrollAnimation(nullptr)
{
	m_editors << this;

	m_saveState = Undefined;

	init();

	setText(s, false);
}

/*!
	\brief ctor
	\param s file to load
	\param actions Whether builtin actions and menus should be created
	\note Creates builtin menus/action
*/
QEditor::QEditor(const QString& s, bool actions, QWidget *p)
 : QAbstractScrollArea(p),
    pMenu(nullptr), m_lineEndingsMenu(nullptr), m_lineEndingsActions(nullptr),
    m_bindingsMenu(nullptr), aDefaultBinding(nullptr), m_bindingsActions(nullptr),
    m_doc(nullptr), m_definition(nullptr), m_curPlaceHolder(-1), m_placeHolderSynchronizing(false), m_state(defaultFlags()),
    mDisplayModifyTime(true), m_useQSaveFile(true), m_blockKey(false), m_disableAccentHack(false), m_LineWidth(0), m_scrollAnimation(nullptr)
{
	m_editors << this;

	m_saveState = Undefined;

	init(actions);
	
	setText(s, false);
}

/*!
	\brief dtor
*/
QEditor::~QEditor()
{
	m_editors.removeAll(this);

	if ( m_completionEngine )
		delete m_completionEngine;

	/* view class should not delete corresponding data
	if ( m_doc )
		delete m_doc;
	*/

	if ( m_editors.isEmpty() )
	{
		delete watcher();
	} else {
		watcher()->removeWatch(this);
	}
}

/*!
	\internal
*/
void QEditor::init(bool actions,QDocument *doc)
{
	#ifdef Q_GL_EDITOR
	setViewport(new QGLWidget);
	#endif

	viewport()->setCursor(Qt::IBeamCursor);
	viewport()->setBackgroundRole(QPalette::Base);
	//viewport()->setAttribute(Qt::WA_OpaquePaintEvent, true);
	viewport()->setAttribute(Qt::WA_KeyCompression, true);
	viewport()->setAttribute(Qt::WA_InputMethodEnabled, true);
	viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);


    MarkedScrollBar *scrlBar=new MarkedScrollBar();
    scrlBar->enableClipping(false);
    scrlBar->setDocument(doc);
    setVerticalScrollBar(scrlBar);
    //addMark(5,Qt::red);

	verticalScrollBar()->setSingleStep(1);
	horizontalScrollBar()->setSingleStep(20);

	setAcceptDrops(true);
	//setDragEnabled(true);
	setFrameStyle(QFrame::NoFrame);
	setFrameShadow(QFrame::Plain);
	setFocusPolicy(Qt::WheelFocus);
	setAttribute(Qt::WA_KeyCompression, true);
	setAttribute(Qt::WA_InputMethodEnabled, true);

	connect(this							,
			SIGNAL( markChanged(QString, QDocumentLineHandle*, int, bool) ),
			QLineMarksInfoCenter::instance(),
			SLOT  ( markChanged(QString, QDocumentLineHandle*, int, bool) ) );

	if(doc){
		// externally created document
		m_doc=doc;
	}else{
		m_doc = new QDocument(this);
	}

	connect(m_doc	, SIGNAL( formatsChange (int, int) ),
			this	, SLOT  ( repaintContent(int, int) ) );

	connect(m_doc	, SIGNAL( contentsChange(int, int) ),
			this	, SLOT  ( updateContent (int, int) ) );

	connect(m_doc		, SIGNAL( formatsChanged() ),
			viewport()	, SLOT  ( update() ) );

	connect(m_doc	, SIGNAL( widthChanged(int) ),
			this	, SLOT  ( documentWidthChanged(int) ) );

	connect(m_doc	, SIGNAL( heightChanged(int) ),
			this	, SLOT  ( documentHeightChanged(int) ) );

	connect(m_doc	, SIGNAL( cleanChanged(bool) ),
			this	, SLOT  ( setContentClean(bool) ) );

	connect(m_doc	, SIGNAL( undoAvailable(bool) ),
			this	, SIGNAL( undoAvailable(bool) ) );

	connect(m_doc	, SIGNAL( redoAvailable(bool) ),
			this	, SIGNAL( redoAvailable(bool) ) );

	connect(m_doc	, SIGNAL( markChanged(QDocumentLineHandle*, int, bool) ),
			this	, SLOT  ( markChanged(QDocumentLineHandle*, int, bool) ) );

	connect(m_doc	, SIGNAL( lineEndingChanged(int) ),
			this	, SLOT  ( lineEndingChanged(int) ) );

	connect(m_doc, SIGNAL(slowOperationStarted()), SIGNAL(slowOperationStarted()));
	connect(m_doc, SIGNAL(slowOperationEnded()), SIGNAL(slowOperationEnded()));

	m_cursorLinesFromViewTop=0;
	m_lastColumn=-2;
	m_lastLine=-2;
	m_hoverCount=-2;
    preEditSet=false;
    m_preEditFormat=0;

	if ( m_defaultBinding )
	{
		m_bindings << m_defaultBinding;
	}

	if ( actions )
	{
		pMenu = new QMenu;

		QAction *a, *sep;

		a = new QAction(QIcon(":/undo.png"), tr("&Undo"), this);
		a->setObjectName("undo");
		Q_SHORTCUT(a, "Ctrl+Z", "Edit");
		a->setEnabled(false);
		connect(this , SIGNAL( undoAvailable(bool) ),
				a	, SLOT  ( setEnabled(bool) ) );
		connect(a	, SIGNAL( triggered() ),
				this , SLOT  ( undo() ) );

		addAction(a, "&Edit", "Edit");

		a = new QAction(QIcon(":/redo.png"), tr("&Redo"), this);
		a->setObjectName("redo");
		Q_SHORTCUT(a, "Ctrl+Y", "Edit");
		a->setEnabled(false);
		connect(this , SIGNAL( redoAvailable(bool) ),
				a	, SLOT  ( setEnabled(bool) ) );
		connect(a	, SIGNAL( triggered() ),
				this , SLOT  ( redo() ) );

		addAction(a, "&Edit", "Edit");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Edit", "Edit");

		a = new QAction(QIcon(":/cut.png"), tr("Cu&t"), this);
		a->setObjectName("cut");
		Q_SHORTCUT(a, "Ctrl+X", "Edit");
		a->setEnabled(false);
		connect(this, SIGNAL( copyAvailable(bool) ),
				a	, SLOT  ( setEnabled(bool) ) );
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( cut() ) );

		addAction(a, "&Edit", "Edit");

		a = new QAction(QIcon(":/copy.png"), tr("&Copy"), this);
		a->setObjectName("copy");
		Q_SHORTCUT(a, "Ctrl+C", "Edit");
		a->setEnabled(false);
		connect(this , SIGNAL( copyAvailable(bool) ),
				a	, SLOT  ( setEnabled(bool) ) );
		connect(a	, SIGNAL( triggered() ),
				this , SLOT  ( copy() ) );

		addAction(a, "&Edit", "Edit");

		a = new QAction(QIcon(":/paste.png"), tr("&Paste"), this);
		a->setObjectName("paste");
		//aPaste->setEnabled(QApplication::clipboard()->text().count());
		Q_SHORTCUT(a, "Ctrl+V", "Edit");
		connect(QApplication::clipboard()	, SIGNAL( dataChanged() ),
				this						, SLOT  ( checkClipboard() ) );

		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( paste() ) );

		addAction(a, "&Edit", "Edit");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Edit", "Edit");

		a = new QAction(QIcon(":/indent.png"), tr("&Indent"), this);
		a->setObjectName("indent");
		Q_SHORTCUT(a, "Ctrl+I", "Edit");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( indentSelection() ) );

		addAction(a, "&Edit", "Edit");

		a = new QAction(QIcon(":/unindent.png"), tr("&Unindent"), this);
		a->setObjectName("unindent");
		Q_SHORTCUT(a, "Ctrl+Shift+I", "Edit");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( unindentSelection() ) );

		addAction(a, "&Edit", "Edit");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Edit", "");

		a = new QAction(tr("Toggle &Comment"), this);
		a->setObjectName("togglecomment");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( toggleCommentSelection() ) );

		a = new QAction(QIcon(":/comment.png"), tr("Co&mment"), this);
		a->setObjectName("comment");
		Q_SHORTCUT(a, "Ctrl+D", "Edit");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( commentSelection() ) );

		addAction(a, "&Edit", "Edit");

		a = new QAction(QIcon(":/uncomment.png"), tr("Unc&omment"), this);
		a->setObjectName("uncomment");
		Q_SHORTCUT(a, "Ctrl+Shift+D", "Edit");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( uncommentSelection() ) );

		addAction(a, "&Edit", "Edit");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Edit", "");

		a = new QAction(tr("&Select all"), this);
		a->setObjectName("selectAll");
		Q_SHORTCUT(a, "Ctrl+A", "Edit");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( selectAll() ) );

		addAction(a, "&Edit", "Edit");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, QString());

		a = new QAction(QIcon(":/find.png"), tr("&Find"), this);
		a->setObjectName("find");
		Q_SHORTCUT(a, "Ctrl+F", "Search");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( find() ) );

		addAction(a, "&Search", "Search");

		a = new QAction(QIcon(":/next.png"), tr("Fin&d next"), pMenu);
		a->setObjectName("findNext");
		Q_SHORTCUT(a, "F3", "Search");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( findNext() ) );

		addAction(a, "&Search", "Search");

		a = new QAction(QIcon(":/replace.png"), tr("&Replace"), this);
		a->setObjectName("replace");
		Q_SHORTCUT(a, "Ctrl+R", "Search");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( replacePanel() ));

		addAction(a, "&Search", "Search");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Search", "Search");

		a = new QAction(QIcon(":/goto.png"), tr("&Goto line..."), this);
		a->setObjectName("goto");
		Q_SHORTCUT(a, "Ctrl+G", "Search");
		connect(a	, SIGNAL( triggered() ),
				this, SLOT  ( gotoLine() ) );

		addAction(a, "&Search", "Search");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, "&Edit", "");

		a = new QAction(tr("Dynamic line wrapping"), this);
		a->setObjectName("wrap");
		a->setCheckable(true);
		a->setChecked(flag(LineWrap));

		addAction(a, "&Edit", "");

		Q_SHORTCUT(a, "F10", "Edit");
		connect(a	, SIGNAL( toggled(bool) ),
				this, SLOT  ( setLineWrapping(bool) ) );


		m_bindingsMenu = new QMenu(tr("Input binding"), this);
		m_bindingsActions = new QActionGroup(m_bindingsMenu);
		//m_bindingsActions->setExclusive(true);

		connect(m_bindingsActions	, SIGNAL( triggered(QAction*) ),
				this				, SLOT  ( bindingSelected(QAction*) ) );

		aDefaultBinding = new QAction(tr("Default"), m_bindingsMenu);
		aDefaultBinding->setCheckable(true);
		aDefaultBinding->setData("default");

		m_bindingsMenu->addAction(aDefaultBinding);
		m_bindingsMenu->addSeparator();
		m_bindingsActions->addAction(aDefaultBinding);
        m_registeredBindings["default"] = nullptr;

		updateBindingsMenu();

		m_bindingsMenu->menuAction()->setObjectName("bindings");
		addAction(m_bindingsMenu->menuAction(), "&Edit", "");

		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, QString());

		m_lineEndingsMenu = new QMenu(tr("Line endings"), this);
		m_lineEndingsActions = new QActionGroup(m_lineEndingsMenu);
		m_lineEndingsActions->setExclusive(true);

		connect(m_lineEndingsActions, SIGNAL( triggered(QAction*) ),
				this				, SLOT  ( lineEndingSelected(QAction*) ) );

		m_lineEndingsActions->addAction(tr("Conservative"))->setData("conservative");
		m_lineEndingsActions->addAction(tr("Local"))->setData("local");
		m_lineEndingsActions->addAction(tr("Unix/Linux"))->setData("unix");
		m_lineEndingsActions->addAction(tr("Dos/Windows"))->setData("dos");
		m_lineEndingsActions->addAction(tr("Old Mac"))->setData("mac");
		
		QList<QAction*> lle = m_lineEndingsActions->actions();

		foreach ( QAction *a, lle )
		{
			a->setCheckable(true);
			m_lineEndingsMenu->addAction(a);
		}

		lle.at(0)->setChecked(true);

		m_lineEndingsMenu->menuAction()->setObjectName("lineEndings");
		addAction(m_lineEndingsMenu->menuAction(), "&Edit", "");

		/*
		sep = new QAction(this);
		sep->setSeparator(true);
		addAction(sep, QString());
		*/
	}

	if (!m_defaultKeysSet) getEditOperations();

	setWindowTitle("[*]"); //remove warning of setWindowModified

	setCursor(QDocumentCursor());
}

/*!
	\return wether the flag \a f is set
*/
bool QEditor::flag(EditFlag f) const
{
	return m_state & f;
}

/*!
	\brief Sets the flag \a f
*/
void QEditor::setFlag(EditFlag f, bool b)
{
	if ( b )
	{
		m_state |= f;
	} else {
		m_state &= ~f;
	}

	if ( f == LineWrap || f == HardLineWrap || f==LineWidthConstraint)
	{
		m_doc->impl()->setHardLineWrap(flag(HardLineWrap));
		m_doc->impl()->setLineWidthConstraint(flag(LineWidthConstraint));


		if ( isVisible() ) {
		    if ( flag(HardLineWrap) || flag(LineWidthConstraint) )
				m_doc->setWidthConstraint( m_LineWidth > 0 ? m_LineWidth : wrapWidth() );
			else if ( flag(LineWrap) )
				m_doc->setWidthConstraint( wrapWidth() );
			else
				m_doc->clearWidthConstraint();
		}

		m_cursor.refreshColumnMemory();

		QAction *a = m_actions.value("wrap");

		if ( a && !a->isChecked() )
			a->setChecked(flag(LineWrap));

		// TODO : only update cpos if cursor used to be visible?
		ensureCursorVisible();
	}

}

/*!
	\return whether it is possible to call undo()
*/
bool QEditor::canUndo() const
{
	return m_doc ? m_doc->canUndo() : false;
}

/*!
	\return whether it is possible to call redo()
*/
bool QEditor::canRedo() const
{
	return m_doc ? m_doc->canRedo() : false;
}

/*!
	\brief Set line wrapping
	\param on line wrap on/off

	\note the function also enables "cursor movement within wrapped lines"
	which can be disabled manually using setFlag(QEditor::CursorJumpPastWrap, false);
*/
void QEditor::setLineWrapping(bool on)
{
	setFlag(LineWrap, on);
	setFlag(CursorJumpPastWrap, on);
}

void QEditor::setHardLineWrapping(bool on)
{
	setFlag(HardLineWrap, on);
}
void QEditor::setSoftLimitedLineWrapping(bool on)
{
	setFlag(HardLineWrap, false);
	setFlag(LineWidthConstraint, on);
}

void QEditor::setWrapLineWidth(int l){
    m_LineWidth=l;
    if(flag(HardLineWrap)||flag(LineWidthConstraint))
	m_doc->setWidthConstraint(m_LineWidth);
}

void QEditor::setWrapAfterNumChars(int numChars){
	if (numChars <= 0) {
		m_wrapAfterNumChars = 0;
		setWrapLineWidth(0);
	}
	m_wrapAfterNumChars = qMax(numChars, 20);
	int w=QFontMetrics(QDocument::font()).averageCharWidth()*(m_wrapAfterNumChars+0.5) + 5; // +5 fixed width on left side, 0.5: 1/2 a char margin on right side
	setWrapLineWidth(w);
}

/*!
	\return The whole text being edited
*/
QString QEditor::text() const
{
	return m_doc ? m_doc->text() : QString();
}

/*!
	\return The text at a given line
	\param line text line to extract, using C++ array conventions (start at zero)
*/
QString QEditor::text(int line) const
{
	return m_doc ? m_doc->line(line).text() : QString();
}

/*!
	\brief Set the text of the underlying document and update display
*/
void QEditor::setText(const QString& s, bool allowUndo)
{
	clearPlaceHolders();

	if ( m_doc )
		m_doc->setText(s, allowUndo);

	if (!allowUndo || !m_cursor.isValid()) setCursor(QDocumentCursor(m_doc));
	else setCursor(m_cursor);

	documentWidthChanged(m_doc->width());
	documentHeightChanged(m_doc->height());
	viewport()->update();
}

/*!
	\brief Save the underlying document to a file

	\see fileName()
*/
void QEditor::save()
{
	if ( !m_doc )
		return;

	if ( fileName().isEmpty() )
	{
		QString fn = QFileDialog::getSaveFileName();

		if ( fn.isEmpty() )
			return;

		setFileName(fn);
	} else if ( isInConflict() ) {
		QMessageBox msg (QMessageBox::Warning,
		             tr("Conflict!"),
		             tr(
		               "%1\nhas been modified by another application.\n"
		               "Press \"Save\" to overwrite the file on disk\n"
		               "Press \"Reset\" to reload the file from disk.\n"
		               "Press \"Diff\" to show differences in the editor.\n"
		               "Press \"Ignore\" to ignore this warning.\n"
		               ).arg(fileName()),
		             QMessageBox::NoButton,
		             this);
		msg.addButton(QMessageBox::Save);
		msg.addButton(QMessageBox::Reset);
		msg.addButton(QMessageBox::Ignore);
		QAbstractButton * diffBtn = msg.addButton(tr("Diff"), QMessageBox::ActionRole);
		msg.setDefaultButton(msg.addButton(QMessageBox::Cancel));
		if (msg.exec() == QMessageBox::NoButton) {
			if ( msg.clickedButton() == diffBtn ) {
				m_saveState = Undefined;
				emit fileInConflictShowDiff();
			}
			return;
		}
		QAbstractButton * button = msg.clickedButton();
		int ret = msg.standardButton(button);

		if ( ret == QMessageBox::Save )
		{
			m_saveState = Undefined;
		} else if ( ret == QMessageBox::Reset ) {
			load(fileName(),document()->codec());
			m_saveState = Undefined;
			return;
		} else if ( ret == QMessageBox::Ignore ) {
			m_saveState = Undefined;
			return;
		} else if ( button == diffBtn ){
			m_saveState = Undefined;
			emit fileInConflictShowDiff(); //guess this branch is unused
			return;
		} else {
			return;
		}
	}

	m_saveState = Saving;

	//QTextStream s(&f);
	//s << text();
	// insert hard line breaks on modified lines (if desired)

	//remove all watches (on old and new file name (setfilename above could have create one!) )
	Q_ASSERT(watcher());
	watcher()->removeWatch(QString(), this);

	if (!saveCopy(fileName())) {
		m_saveState = Undefined;
		reconnectWatcher();

		return;
	}

	m_doc->setClean();

	emit saved(this, fileName());
	m_saveState = Saved;
	
	QTimer::singleShot(100, this, SLOT( reconnectWatcher() ));
	
	update();
}


bool QEditor::saveCopy(const QString& filename){
	Q_ASSERT(m_doc);

	emit slowOperationStarted();

	// insert hard line breaks on modified lines (if desired)
	if(flag(HardLineWrap)){
		QList<QDocumentLineHandle*> handles = m_doc->impl()->getStatus().keys();
		m_doc->applyHardLineWrap(handles);
	}
	
	QString txt = m_doc->text(flag(RemoveTrailing), flag(PreserveTrailingIndent));
	QByteArray data =  m_doc->codec() ? m_doc->codec()->fromUnicode(txt) : txt.toLocal8Bit();

#if QT_VERSION >= 0x050100
	if (m_useQSaveFile) {
		QSaveFile file(filename);
		if (file.open(QIODevice::WriteOnly)) {
			file.write(data);
			bool success = file.commit();
			if (!success) {
				QMessageBox::warning(this, tr("Saving failed"),
									 tr("%1\nCould not be written. Error (%2): %3.\n"
										"If the file already existed on disk, it was not modified by this operation.")
										.arg(QDir::toNativeSeparators(filename))
										.arg(file.error())
										.arg(file.errorString()),
									 QMessageBox::Ok);
			}
			return success;
		}
		QMessageBox::warning(this, tr("Saving failed"), tr("Could not get write permissions on file\n%1.\n\nPerhaps it is read-only or opened in another program?").arg(QDir::toNativeSeparators(filename)), QMessageBox::Ok);
		return false;
	} else {
		return writeToFile(filename, data);
	}
#else
	return writeToFile(filename, data);
#endif
}

/*!
 * Securely writes data to a file. If this is not successfull, the original file stays intact.
 * This procedure is only necessary for Qt < 5.1.0. More recent versions of Qt provide a standard
 * way for this using QSaveFile.
 *
 * This is our safe saving strategy:
 * 1. Prepare: If the file exists, create a copy backupFilename so that it's content is not lost in case of error.
 * 2. Save: Write the file.
 * 3. Cleanup: In case of error, rename the backupFilename back to the original filename.
 *
 * \return true if the data were written to the file successfully.
 */
bool QEditor::writeToFile(const QString &filename, const QByteArray &data) {
	bool sucessfullySaved = false;

	// check available disk space
	quint64 freeBytes;
	while (1) {
		if (!getDiskFreeSpace(QFileInfo(filename).canonicalPath(), freeBytes)) break;
		if (static_cast<quint64>(data.size()) < freeBytes) break;

		QMessageBox::StandardButton bt;
		bt = QMessageBox::critical(this, tr("Saving failed"),
				tr("There seems to be not enough space to save the file at\n%1\n\n"
				   "File size: %2 kB\n"
				   "Free space: %3 kB\n\n"
				   "You should clean up some space and retry. Alternatively you can\n"
				   "cancel the save operation and save to another location instead.\n"
				   "When ignoring this warning TeXstudio will try save to the specified\n"
				   "location. However if there is really not enough space, this will\n"
				   "result in data loss.\n"
				   ).arg(filename).arg(data.size()/1024).arg(freeBytes/1024L),QMessageBox::Retry|QMessageBox::Ignore|QMessageBox::Cancel, QMessageBox::Retry);
		if (bt == QMessageBox::Cancel) { emit slowOperationEnded(); return false; }
		else if (bt == QMessageBox::Ignore) break;
	}

	// 1. Prepare
	QString backupFilename;
	if (QFileInfo(filename).exists()) {
		int MAX_TRIES = 100;
		for (int i=0; i<MAX_TRIES; i++) {
			QString fn = filename + QString("~txs%1").arg(i);
			if (QFile::copy(filename, fn)) {
				backupFilename = fn;
				break;
			}
		}
		if (backupFilename.isNull()) {
			QMessageBox::warning(this, tr("Warning"),
								 tr("Creating a backup of the file failed. You can still continue saving. "
								    "However, if the save action fails, you may loose the data in the original file. "
								    "Do you wish to continue?"),
								 QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
		}
	}

	// 2. Save
	QFile f(filename);
	if ( !f.open(QFile::WriteOnly) ) {
		QMessageBox::warning(this, tr("Saving failed"), tr("Could not get write permissions on file\n%1.\n\nPerhaps it is read-only or opened in another program?").arg(QDir::toNativeSeparators(filename)), QMessageBox::Ok);

		// 3. Cleanup
		QFile::remove(backupFilename);  // original was not modified
		sucessfullySaved = false;
	} else {
		int bytesWritten = f.write(data);
		sucessfullySaved = (bytesWritten == data.size());

		// 3. Cleanup
		if (sucessfullySaved) {
			QFile::remove(backupFilename);
		} else {
			QString message = tr("Writing the document to file\n%1\nfailed.").arg(filename);
			if (!backupFilename.isNull()) {
				QFile::remove(filename);
				bool ok = QFile::rename(backupFilename, filename);  // revert
				if (!ok) {
					message += "\n" + tr("The original file on disk was destroyed during the save operation.\n"
					                     "You'll find a copy at\n%1").arg(backupFilename);
				}
			}
			QMessageBox::critical(this, tr("Saving failed"), message, QMessageBox::Ok);
		}

		f.close(); //explicite close for watcher (??? is this necessary anymore?)
	}

	emit slowOperationEnded();

	return sucessfullySaved;
}


/*!
	\brief Save the content of the editor to a file

	\note This method renames the editor, stop monitoring the old
	file and monitor the new one
*/
void QEditor::save(const QString& fn)
{
	if ( fileName().count() ) {
		watcher()->removeWatch(fileName(), this);
	}

	if ( !saveCopy(fn) ) {
		m_saveState = Undefined;
		reconnectWatcher();

		return;
	}

	m_doc->setClean();

	setFileName(fn);
	emit saved(this, fn);
	m_saveState = Saved;
	
	QTimer::singleShot(100, this, SLOT( reconnectWatcher() ));
}


/*! 
  Saves the text to filename without error checking and unmodified (e.g. without performing hard line break) 
  */
void QEditor::saveEmergencyBackup(const QString& filename){
	Q_ASSERT(m_doc);

	emit slowOperationStarted();

	bool sucessfullySaved = QFile::exists(filename);
	do {
		QString txt = m_doc->textLines().join(m_doc->lineEndingString()); 
		QByteArray data = txt.toUtf8();

		quint64 freeBytes;
		if (getDiskFreeSpace(QFileInfo(filename).canonicalPath(), freeBytes) && (static_cast<quint64>(data.size()) < freeBytes)) 
			break;

		QFile f(filename);

		if ( !f.open(QFile::WriteOnly) ) 
			break;

		sucessfullySaved = f.write(data) == data.size();
		f.flush();
	} while (0);

	if (!sucessfullySaved)
		QFile::remove(filename);
	
	emit slowOperationEnded();
}

/*!
	\internal
*/
void QEditor::checkClipboard()
{
	// LOOKS LIKE THIS FUNCTION NEVER GETS CALLED DESPITE THE CONNECTION...

	//const QMimeData *d = QApplication::clipboard()->mimeData();

	//qDebug("checking clipboard : %s", d);

	//QCE_ENABLE_ACTION("paste", d && d->hasText())
}

/*!
	\internal
*/
void QEditor::reconnectWatcher()
{
	watcher()->removeWatch(this);
	watcher()->addWatch(fileName(), this);
}

/*!
	\internal
*/
void QEditor::fileChanged(const QString& file)
{
	if ( (file != fileName()) || (m_saveState == Saving) || mIgnoreExternalChanges )
		return;
	
	/*
	if ( m_saveState == Saved )
	{
		qApp->processEvents();
		
		m_saveState = Undefined;
		return;
	}
	*/

	if ( !QFileInfo(file).exists())
	{
		watcher()->removeWatch(QString(), this); //no duplicated questions

		if(isHidden() && mSilentReloadOnExternalChanges){ // if hidden, just close the editor
			emit requestClose();
			return;
		}

		int ret = QMessageBox::warning(this, tr("File deleted"), tr("The file %1 has been deleted on disk.\n"
		                                                            "Should I save the document as it is to restore the file?\n").arg(fileName()), QMessageBox::Save | QMessageBox::Ignore);
		if (ret == QMessageBox::Save) {
			if ( QFileInfo(file).exists() ) {
				QMessageBox::warning(this, tr("File deleted"), tr("Well, this is strange: The file %1 is not deleted anymore.\n"
				                                                  "Probably someone else restored it and therefore I'm not going to override the (possible modified) version on the disk.").arg(fileName()), QMessageBox::Ok);
				m_saveState = Conflict;
				reconnectWatcher();
				return;
			} else {
				m_saveState = Undefined;
				save(); //save will reconnect the watcher
				return;
			}
		}

		if ( QFileInfo(file).exists() )
			reconnectWatcher();

	} else if ( !isContentModified() )
	{
		// silently reload file if the editor contains no modification?
		// -> result in undo/redo history loss, still ask confirmation ?
		bool autoReload = true;

		if ( (canUndo() || canRedo()) && !mSilentReloadOnExternalChanges )
		{
			watcher()->removeWatch(QString(), this); //no duplicated questions
			
			int ret = QMessageBox::warning(this,
			                               tr("File changed"),
			                               tr(
			                                 "%1\nhas been modified by another application.\n\n"
			                                 "Undo/Redo stack would be discarded by the auto-reload.\n"
			                                 "Do you wish to keep up to date by reloading the file?\n\n"
			                                 "(Note: You can permanently enable silent reloading in the options.)"
			                                 ).arg(fileName()),
			                               QMessageBox::Yes
			                               |
			                               QMessageBox::No
			                               );

			if ( ret == QMessageBox::No )
				autoReload = false;
			reconnectWatcher();
		}

		if ( autoReload ){
			reload();
			return;
		}
	}

	// TODO : check for actual modification (using a checksum?)
	// TODO : conflict reversible (checksum again?)
	
	//qDebug("conflict!");
	m_saveState = Conflict;
	emit fileInConflict();
}

/*!
	\return Whether a file conflict has been detected

	File conflicts happen when the loaded file is modified
	on disk by another application if the text has been
	modified in QCE
*/
bool QEditor::isInConflict() const
{
	return m_saveState == Conflict;
}

void QEditor::emitNeedUpdatedCompleter(){
	emit needUpdatedCompleter();
}

QTextCodec* QEditor::getFileCodec() const
{
 //   if (m_codec==0) QMessageBox::information(0,"abc","def",0);
    return m_doc?m_doc->codec():QDocument::defaultCodec();
}

void QEditor::setFileCodec(QTextCodec* codec){
    if (!m_doc || !codec || codec==m_doc->codec()) return;
    m_doc->setCodec(codec); //standard encoding in memory, file encoding set when saving
   // setContentModified(true);
}
void QEditor::viewWithCodec(QTextCodec* codec){
    if (!m_doc || !codec) return;
    QByteArray dat= m_doc->codec()->fromUnicode(document()->text());
    m_doc->setCodec(codec); //standard encoding in memory, file encoding set when saving
    document()->setText(m_doc->codec()->toUnicode(dat), false);
}

/*!
	\brief Print the content of the editor
*/
void QEditor::print()
{
	if ( !m_doc )
		return;

	QPrinter printer;

	// TODO : create a custom print dialog, page range sucks, lines range would be better
	QPrintDialog dialog(&printer, this);
	dialog.setWindowTitle(tr("Print Source Code"));
	dialog.setEnabledOptions(QPrintDialog::PrintToFile | QPrintDialog::PrintPageRange);

	if ( dialog.exec() == QDialog::Accepted )
	{
		m_doc->print(&printer);
	}
}

void QEditor::relayPanelCommand(const QString& panel, const QString& command, const QList<QVariant>& args){
	QCodeEdit *m = QCodeEdit::manager(this);
	if (!m) {
		qDebug("Unmanaged QEditor");
		return;
	}
	if (panel == "Search") m->sendPanelCommand("Goto", "hide");
	m->sendPanelCommand(panel, qPrintable(command), args);
}


/*!
	\brief Show the search/replace panel, if any
*/
void QEditor::find()
{
	relayPanelCommand("Search", "display", QList<QVariant>() << 1 << false);
}

void QEditor::find(QString text, bool highlight, bool regex, bool word, bool caseSensitive){
	relayPanelCommand("Search", "find", QList<QVariant>() << text << false << highlight << regex << word << caseSensitive);
}

void QEditor::find(QString text, bool highlight, bool regex, bool word, bool caseSensitive, bool fromCursor, bool selection){
	relayPanelCommand("Search", "find", QList<QVariant>() << text << false << highlight << regex << word << caseSensitive << fromCursor << selection);
}

void QEditor::findInSameDir()
{
	relayPanelCommand("Search", "findNext");
}
void QEditor::findNext()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << false);
}
void QEditor::findPrev()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << true);
}
void QEditor::findCount()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << false << false << false << true);
}
void QEditor::selectAllMatches(){
	relayPanelCommand("Search", "selectAllMatches");
}

/*!
	\brief Show the search/replace panel, if any
*/
void QEditor::replacePanel()
{
	relayPanelCommand("Search", "display", QList<QVariant>() << 1 << true);
}
void QEditor::replaceNext()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << false << true);
}
void QEditor::replacePrev()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << true << true);
}
void QEditor::replaceAll()
{
	relayPanelCommand("Search", "findReplace", QList<QVariant>() << false << true << true);
}

/*!
	\brief Show a panel or dialog to go to a specific line
*/
void QEditor::gotoLine()
{
	QCodeEdit *m = QCodeEdit::manager(this);
	
	if ( m && m->hasPanel("Goto") )
	{
		// makes sense hiding this one if present...
		m->sendPanelCommand("Search", "hide");
		
		m->sendPanelCommand("Goto", "show");
	} else {
		QGotoLineDialog dlg(this);
		
		dlg.exec(this);
	}
}

/*!
	\brief Run time translation entry point for compat with Edyuk
*/
void QEditor::retranslate()
{
	QCE_TR_ACTION("undo", tr("&Undo"))
	QCE_TR_ACTION("redo", tr("&Redo"))

	QCE_TR_ACTION("cut", tr("Cu&t"))
	QCE_TR_ACTION("copy", tr("&Copy"))
	QCE_TR_ACTION("paste", tr("&Paste"))

	QCE_TR_ACTION("indent", tr("&Indent"))
	QCE_TR_ACTION("unindent", tr("&Unindent"))
	QCE_TR_ACTION("comment", tr("Co&mment"))
	QCE_TR_ACTION("uncomment", tr("Unc&omment"))

	QCE_TR_ACTION("selectAll", tr("&Select all"))

	QCE_TR_ACTION("find", tr("&Find"))
	QCE_TR_ACTION("findNext", tr("Fin&d next"))
	QCE_TR_ACTION("replace", tr("&Replace"))

	QCE_TR_ACTION("goto", tr("&Goto line..."))

	if ( m_completionEngine )
		m_completionEngine->retranslate();

	if ( m_bindingsMenu )
		m_bindingsMenu->setTitle(tr("Input binding"));

	if ( aDefaultBinding )
		aDefaultBinding->setText(tr("Default"));

	#ifdef _QMDI_
	menus.setTranslation("&Edit", tr("&Edit"));
	menus.setTranslation("&Search", tr("&Search"));

	toolbars.setTranslation("Edit", tr("Edit"));
	toolbars.setTranslation("Search", tr("Search"));
	#endif
}

/*!
	\return the action associated with a given name, if the QEditor has been created with actions on
*/
QAction* QEditor::action(const QString& s)
{
	QHash<QString, QAction*>::const_iterator it = m_actions.constFind(s);

    return it != m_actions.constEnd() ? *it : nullptr;
}

/*!
	\brief Add an action to the editor
	\param a action to add
	\param menu if not empty (and if QCE is built with qmdilib support) the action will be added to that menu
	\param toolbar similar to \a menu but acts on toolbars

	\see removeAction()
*/
void QEditor::addAction(QAction *a, const QString& menu, const QString& toolbar)
{
	if ( !a )
		return;

	QWidget::addAction(a);

	m_actions[a->objectName()] = a;

	if ( pMenu && menu.count() )
	{
		pMenu->addAction(a);

		#ifdef _QMDI_
		menus[menu]->addAction(a);
		#endif
	}

	if ( toolbar.count() )
	{
		#ifdef _QMDI_
		toolbars[toolbar]->addAction(a);
		#endif
	}
}

/*!
	\brief remove an action form the editor
	\param a action to add
	\param menu if not empty (and if QCE is built with qmdilib support) the action will be added to that menu
	\param toolbar similar to \a menu but acts on toolbars

	\see addAction()
*/
void QEditor::removeAction(QAction *a, const QString& menu, const QString& toolbar)
{
	if ( !a )
		return;

	QWidget::removeAction(a);

	//m_actions.remove(a->objectName());

	if ( pMenu )
		pMenu->removeAction(a);

	#ifdef _QMDI_
	if ( menu.count() )
	{
		menus[menu]->removeAction(a);
	}

	if ( toolbar.count() )
	{
		toolbars[toolbar]->removeAction(a);
	}
	#else
	Q_UNUSED(menu)
	Q_UNUSED(toolbar)
	#endif
}

/*!
	\brief load a text file
	\param file file to load

	If the file cannot be loaded, previous content is cleared.
*/

void QEditor::load(const QString& file, QTextCodec* codec)
{
	clearPlaceHolders();

	m_doc->load(file,codec);

	setCursor(QDocumentCursor(m_doc));

	documentWidthChanged(m_doc->width());
	documentHeightChanged(m_doc->height());
	viewport()->update();

	//m_codec=codec;
	
	//qDebug("checksum = %i", m_lastFileState.checksum);

	if ( m_lineEndingsActions )
	{
		// TODO : update Conservative to report original line endings
		static const QRegExp rx(" \\[\\w+\\]");
		QAction *a = m_lineEndingsActions->actions().at(0);

		if ( a )
		{
			QDocument::LineEnding le = m_doc->originalLineEnding();

			QString txt = a->text();
			txt.remove(rx);
			txt += " [";

			if ( le == QDocument::Windows )
				txt += tr("Windows");
			else
				txt += tr("Unix");

			txt += ']';

			a->setText(txt);
		}
	}

	setFileName(file);
	
	emit loaded(this, file);

	reconnectWatcher();
}

void QEditor::reload(){
	emit fileAutoReloading(fileName());
	// save cursor information
	int lineNum = cursor().lineNumber();
	int col = cursor().columnNumber();
	int anchorLineOffset = cursor().anchorLineNumber() - lineNum;
	int anchorCol = cursor().anchorColumnNumber();
	QString lineText = cursor().line().text();

	load(fileName(),m_doc->codec());
	m_saveState = Undefined;

	// restore cursor position based on lineText
	int newLineNum = m_doc->findNearLine(lineText, lineNum);
	QDocumentCursor cur(m_doc, newLineNum+anchorLineOffset, anchorCol, newLineNum, col);
	if (newLineNum>=0 && cur.isValid()) {
		setCursor(cur);
	} else {
		// fall back to staying on the same line number
		cur = QDocumentCursor(m_doc, lineNum);
		if (cur.isValid()) {
			setCursor(cur);
		} else {
			// fall back 2: the new document contains fewer lines than the previous cursor position. -> end ist closest to previous position
			setCursor(QDocumentCursor(m_doc, m_doc->lineCount()-1));
		}
	}

	emit fileReloaded();
	return;
}

/*!
	\return a pointer to the underlying QDocument object
*/
QDocument* QEditor::document() const
{
	return m_doc;
}

/*!
	\internal
*/
void QEditor::setDocument(QDocument *d)
{
	Q_UNUSED(d)

	qWarning("QEditor::setDocument() is not working yet...");
}

/*!
	\brief Force a full re-highlighting of the document
*/
void QEditor::highlight()
{
	m_doc->highlight();
	//updateContent(0, m_doc->lines());
}

/*!
	\return the current InputBinding
*/
QList<QEditorInputBindingInterface*> QEditor::inputBindings() const
{
	return m_bindings;
}

/*!
	\brief Add an input binding
*/
void QEditor::addInputBinding(QEditorInputBindingInterface *b)
{
	if ( b )
		m_bindings << b;

	if ( !aDefaultBinding || !m_bindingsActions )
		return;

	QString id = b ? b->id() : QString();
	aDefaultBinding->setChecked(!b);

	if ( !b )
		return;

	QList<QAction*> actions = m_bindingsActions->actions();

	foreach ( QAction *a, actions )
	{
		if ( a->data().toString() != id )
		a->setChecked(true);
	}
}

/*!
	\brief Remove an input binding
*/
void QEditor::removeInputBinding(QEditorInputBindingInterface *b)
{
	int n = m_bindings.removeAll(b);
	
	if ( !aDefaultBinding || !m_bindingsActions || !n )
		return;
	
	QString id = b ? b->id() : QString();
	aDefaultBinding->setChecked(!b);
	
	if ( !b )
		return;
	
	QList<QAction*> actions = m_bindingsActions->actions();
	
	foreach ( QAction *a, actions )
	{
		if ( a->data().toString() != id )
			a->setChecked(false);
	}
}

/*!
	\brief Set the current input binding
*/
void QEditor::setInputBinding(QEditorInputBindingInterface *b)
{
	m_bindings.clear();
	
	if ( b )
		m_bindings << b;
	
	if ( !aDefaultBinding || !m_bindingsActions )
		return;
	
	QString id = b ? b->id() : QString();
	aDefaultBinding->setChecked(!b);
	
	if ( !b )
		return;
	
	QList<QAction*> actions = m_bindingsActions->actions();
	
	foreach ( QAction *a, actions )
	{
		if ( a )
			a->setChecked(a->data().toString() != id);
	}
}

/*!
	\internal
*/
void QEditor::updateBindingsMenu()
{
	if ( !aDefaultBinding || !m_bindingsMenu || !m_bindingsActions )
		return;

	QStringList bindings = registeredInputBindingIds();
	QList<QAction*> actions = m_bindingsActions->actions();

	aDefaultBinding->setChecked(m_bindings.contains(m_defaultBinding));

	foreach ( QAction *a, actions )
	{
		int idx = bindings.indexOf(a->data().toString());

		if ( idx == -1 )
		{
			m_bindingsMenu->removeAction(a);
			m_bindingsActions->removeAction(a);
			delete a;
		} else {
			bindings.removeAt(idx);

			foreach ( QEditorInputBindingInterface *b, m_bindings )
				if ( a->data().toString() == b->id() )
				a->setChecked(true);

		}
	}

	bindings.removeAll("default");

	foreach ( QString s, bindings )
	{
		QEditorInputBindingInterface *b = m_registeredBindings.value(s);

		if ( !b )
			continue;

		QAction *a = new QAction(b->name(), m_bindingsMenu);
		a->setData(b->id());
		a->setCheckable(true);

		m_bindingsActions->addAction(a);
		m_bindingsMenu->addAction(a);
	}
}

/*!
	\internal
*/
void QEditor::bindingSelected(QAction *a)
{
	//a = m_bindingsActions->checkedAction();

	if ( !a )
		return;
	
	QEditorInputBindingInterface *b = m_registeredBindings.value(a->data().toString());
	
	if ( a->isChecked() )
		addInputBinding(b);
	else
		removeInputBinding(b);
	
	//qDebug("setting binding to %s [0x%x]", qPrintable(a->data().toString()), m_binding);

	updateMicroFocus();
}

/*!
	\internal
*/
void QEditor::lineEndingSelected(QAction *a)
{
	a = m_lineEndingsActions->checkedAction();

	if ( !a )
		return;

	QString le = a->data().toString();

	if ( le == "conservative" )
		m_doc->setLineEnding(QDocument::Conservative);
	else if ( le == "local" )
		m_doc->setLineEnding(QDocument::Local);
	else if ( le == "unix" )
		m_doc->setLineEnding(QDocument::Unix);
	else if ( le == "dos" )
		m_doc->setLineEnding(QDocument::Windows);


	updateMicroFocus();
}

/*!
	\internal
*/
void QEditor::lineEndingChanged(int lineEnding)
{
	if ( !m_lineEndingsActions )
		return;

	QAction *a = m_lineEndingsActions->checkedAction(),
			*n = m_lineEndingsActions->actions().at(lineEnding);

	if ( a != n )
		n->setChecked(true);

}

/*!
	\return the current cursor
*/
QDocumentCursor QEditor::cursor() const
{
	QDocumentCursor copy(m_cursor, false);
	return copy;
}

/*!
	\return the current cursor handle
*/
QDocumentCursorHandle* QEditor::cursorHandle() const
{
	return m_cursor.handle();
}

/*!
	\brief Set the document cursor
	\param moveView: If disabled, no check is made that the new new cursor position position is visible.
		   In this case you take over responsibility to call ensureCursorVisible later on

*/
void QEditor::setCursor(const QDocumentCursor& c, bool moveView)
{
	repaintCursor();

	m_cursor = c.isValid() ? c : QDocumentCursor(m_doc);
	m_cursor.setColumnMemory(true);
	m_cursor.setAutoUpdated(true);
	m_cursor.setAutoErasable(false);
	clearCursorMirrors();

	if (m_cursor.columnNumber() > m_cursor.line().length())
		m_cursor.setColumnNumber(m_cursor.line().length());

	if ( m_curPlaceHolder >=0 && m_curPlaceHolder < m_placeHolders.count() )
	{
		const PlaceHolder& ph = m_placeHolders[m_curPlaceHolder];
		
		if ( !ph.cursor.isWithinSelection(m_cursor) )
		{
			setPlaceHolder(-1);
			viewport()->update();
		}
	}
	
	emitCursorPositionChanged();

	setFlag(CursorOn, true);
	repaintCursor();
	if (moveView) {
		ensureCursorVisible();
	}

	updateMicroFocus();
}

/*!
	\brief Set the cursor
	\param line document line to move the cursor to (start at zero)
	\param index column index of the new cursor (start at zero)
	\param moveView: If disabled, no check is made that the new cursor position is visible.
		   In this case you take over responsibility to call ensureCursorVisible later on

*/
void QEditor::setCursorPosition(int line, int index, bool moveView)
{
	setCursor(QDocumentCursor(m_doc, line, index), moveView);
}

/*!
	\brief Write the current cursor position to to integers
*/
void QEditor::getCursorPosition(int &line, int &index)
{
	line = m_cursor.lineNumber();
	index = m_cursor.columnNumber();
}

/*!
	\brief Return the position below the cursor
*/
bool QEditor::getPositionBelowCursor(QPoint& offset, int width, int height){
	bool above;
	return getPositionBelowCursor(offset, width, height, above);
}

/*!
 * \brief Calculate an optimal position for a widget of width and height that should be displayed close to the cursor
 * \param outOffset: output Position in Editor coordinates
 * \param outAbove: indicates whether it's better to place the widget above the cursor than below
 * \return false if there is no valid cursor, true otherwise
 */
bool QEditor::getPositionBelowCursor(QPoint& outOffset, int width, int height, bool& outAbove){
	QDocumentCursor c(m_cursor, false);
	QDocumentLine line = c.line();
	if (!c.line().isValid()) return false;
	if (c.columnNumber() < 0 || c.columnNumber() > line.length()) return false;

	outOffset = line.cursorToDocumentOffset(c.columnNumber()-1);
	outOffset.setY(outOffset.y() + document()->y(c.lineNumber()) + document()->getLineSpacing());
	outOffset = mapFromContents(outOffset);
	int left;
	int temp;
	getPanelMargins(&left, &temp, &temp, &temp);
	outOffset.setX(outOffset.x() + left);
	if (outOffset.y() + height > this->height()) {
		outOffset.setY(outOffset.y() - document()->getLineSpacing() - height);
		outAbove = true;
	} else {
		outAbove = false;
	}
	if (outOffset.x() + width > this->width()) {
		// box will extend beyond editor width
		// move to left but not further than the left border of the editor widget
		outOffset.setX(qMax(0, this->width() - width));
	}
	return true;
}

/*!
	\return the number of cursor mirrors currently used
*/
int QEditor::cursorMirrorCount() const
{
	return m_mirrors.count();
}

/*!
	\return the cursor mirror at index \a i

	Index has no extra meaning : you cannot deduce anything about
	the cursor mirror it corresponds to from it. For instance, the
	cursor mirror at index 0 is neither the first mirror added nor
	the one at smallest document position (well : it *might* be but
	that would be a coincidence...)
*/
QDocumentCursor QEditor::cursorMirror(int i) const
{
	return i >= 0 && i < m_mirrors.count() ? m_mirrors.at(i) : QDocumentCursor();
}

/*!
	\return the current cursor and all mirrors

	Not slow, but also not the fastest. Best to avoid in loops
*/
QList<QDocumentCursor> QEditor::cursors() const{
	QList<QDocumentCursor> res;
	if (m_cursor.isValid()) res << m_cursor;
	res << m_mirrors;
	return res;
}

/*!
	\brief Clear all placeholders
*/
void QEditor::clearPlaceHolders()
{
	bool updateView = m_curPlaceHolder >= 0 && m_curPlaceHolder < m_placeHolders.count();
	
	m_curPlaceHolder = -1;

	for ( int i = 0; i < m_placeHolders.count(); ++i )
	{
		PlaceHolder& ph = m_placeHolders[i];

		ph.cursor.setAutoUpdated(false);

		for ( int j = 0; j < ph.mirrors.count(); ++j )
		{
			ph.mirrors[j].setAutoUpdated(false);
		}

		ph.mirrors.clear();
	}

	m_placeHolders.clear();
	
	if ( updateView )
		viewport()->update();
	
}

/*!
	\brief Add a placeholder
	\param p placeholder data
	\param autoUpdate whether to force auto updating of all cursors used by the placeholder

	Auto update is on by default and it is recommended not to disable it unless you know what you are doing.
*/
void QEditor::addPlaceHolder(const PlaceHolder& p, bool autoUpdate)
{
	m_placeHolders << p;

	PlaceHolder& ph = m_placeHolders.last();

	ph.cursor.setAutoUpdated(autoUpdate);
	ph.cursor.setAutoErasable(p.autoRemove);
	ph.cursor.movePosition(ph.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);

	for ( int i = 0; i < ph.mirrors.count(); ++i )
	{
		int mirrorLen = ph.length;
		if (ph.affector)
            mirrorLen = ph.affector->affect(nullptr, ph.cursor.selectedText(), m_placeHolders.size()-1, i).length();


		ph.mirrors[i].setAutoUpdated(autoUpdate);
		ph.mirrors[i].setAutoErasable(p.autoRemove);
		ph.mirrors[i].movePosition(mirrorLen, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
	}
}
/*!
  Adds a mirror to the given placeholder
  */
void QEditor::addPlaceHolderMirror(int placeHolderId, const QDocumentCursor& c){
	if (placeHolderId<0 || placeHolderId>=m_placeHolders.count())
		return;
	PlaceHolder& ph = m_placeHolders[placeHolderId];
	ph.mirrors << c;
	ph.mirrors.last().setAutoUpdated(true);
	ph.mirrors.last().setAutoErasable(true);
    int mirrorLen = ph.affector ? ph.affector->affect(nullptr, ph.cursor.selectedText(), placeHolderId, ph.mirrors.size()-1).length() : ph.length;
	ph.mirrors.last().movePosition(mirrorLen, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
}

/*!
	\brief Remove a placeholder
	\param i placeholder index
	
	\note if the current placeholder is removed there will be NO automatic switching to a remaining one.
*/
void QEditor::removePlaceHolder(int id)
{
	if ( id == m_curPlaceHolder){
		clearCursorMirrors();
		m_curPlaceHolder = -1;
	}

	if ( id<0 || id>=m_placeHolders.count() ) 
		return;
	
	PlaceHolder& ph = m_placeHolders[id];
	
	for ( int i = 0; i < ph.mirrors.count(); ++i ){
		ph.mirrors[i].setAutoUpdated(false);
		ph.mirrors[i].line().setFlag(QDocumentLine::LayoutDirty,true);
	    }
	ph.mirrors.clear();
	ph.cursor.setAutoUpdated(false);
	m_placeHolders.removeAt(id);
	
	if ( id < m_curPlaceHolder )
		--m_curPlaceHolder;
	if ( id < m_lastPlaceHolder )
		--m_lastPlaceHolder;
	else if ( id == m_lastPlaceHolder )
		m_lastPlaceHolder=-1;
	
	viewport()->update();
}

/*!
	\brief Replaces all placeholders with new ones.

	\note New placeholders will not be initialized
*/
void QEditor::replacePlaceHolders(const QList<PlaceHolder>& newPlaceholders){
	clearPlaceHolders();//is this needed?
	m_placeHolders = newPlaceholders;
	if ( m_curPlaceHolder >= m_placeHolders.size() )
		m_curPlaceHolder = m_placeHolders.size() - 1;
	m_lastPlaceHolder = -1;
	viewport()->update();
}

/*!
	\return the number of placeholders currently set
*/
int QEditor::placeHolderCount() const
{
	return m_placeHolders.count();
}
/*!
	\return the id of the current placeholder
*/
int QEditor::currentPlaceHolder() const
{
	return m_curPlaceHolder;
}
const PlaceHolder& QEditor::getPlaceHolder(int i) const{
	return m_placeHolders.at(i);
}
QList<PlaceHolder> QEditor::getPlaceHolders(){
	return m_placeHolders;
}

/*! Checks if there exists a placeholder that will be auto overridden by inserting string s
*/
bool QEditor::isAutoOverrideText(const QString& s) const{
	const QDocumentCursor& c= m_cursor;
	if (c.hasSelection() || (flag(Overwrite) && !c.atLineEnd()))
		return false;
	for ( int i = m_placeHolders.size()-1; i >= 0 ; i-- )
		if ( m_placeHolders[i].autoOverride && m_placeHolders[i].cursor.lineNumber() == c.lineNumber() &&
		     m_placeHolders[i].cursor.anchorColumnNumber() == c.anchorColumnNumber() &&
		     m_placeHolders[i].cursor.selectedText().startsWith(s) ) {
		return true;
	}
	return false;
}

/*! Creates a temporary auto overridden placeholder at position start with length length, and
    merges it with a directly following placeholder (equivalent to extending the following placeholder
    by length characters to the left)
*/
void QEditor::resizeAutoOverridenPlaceholder(const QDocumentCursor& start, int length){
	for (int i=0;i<m_placeHolders.size();i++) {
		PlaceHolder& ph = m_placeHolders[i];
		if (ph.autoOverride &&
		    ph.cursor.lineNumber() == start.lineNumber() &&
		    ph.cursor.anchorColumnNumber() == start.columnNumber() + length) {
			ph.cursor.setAnchorColumnNumber(start.columnNumber());
		}
	}
}
/*!
	\brief Set the current placeholder to use

	This function change the cursor and the cursor mirrors.
*/
void QEditor::setPlaceHolder(int i, bool selectCursors)
{
	if (i == m_curPlaceHolder && i == -1) 
		return;
	
	if (m_curPlaceHolder >= 0 && m_curPlaceHolder < m_placeHolders.size() && m_placeHolders[m_curPlaceHolder].autoRemoveIfLeft) {
		if (i > m_curPlaceHolder) i--;
		int toRemove = m_curPlaceHolder;
		m_curPlaceHolder = -1; //prevent endless recursion, if cursor mirrors exist
		removePlaceHolder(toRemove);
	}
	
	m_curPlaceHolder = -1; 
	clearCursorMirrors();
	if ( i < 0 || i >= m_placeHolders.count() ){
		viewport()->update();
		return;
	}

	if (m_placeHolderSynchronizing) return;
	m_placeHolderSynchronizing=true; //prevent recursive calls (from updateContent)	TODO: move the synchronizing there

	QDocumentCursor cc = m_placeHolders[i].cursor;
	selectCursors|=!cc.isWithinSelection(m_cursor);// && cc.hasSelection() && cc.selectionStart()!=cc.selectionEnd();
	
	//qDebug("set placeholder: %i, select cursors: %i", i, (int)selectCursors);

	if (selectCursors)
		setCursor(cc);
	else if (m_cursor.hasColumnMemory()) 
		m_cursor.setColumnMemory(false);

	i = -1;
	for (int j=0;j<m_placeHolders.size();j++)
		if (cc.equal(m_placeHolders[j].cursor)) {
			i = j;
			break;
		}
	if (i == -1) return;
	
	PlaceHolder& ph = m_placeHolders[i]; //using reference to change the placeholder
	QString base = cc.selectedText();
	for ( int j=0; j< ph.mirrors.size(); j++)
	{
		QDocumentCursor &mc = ph.mirrors[j];
        QString mirrored = ph.affector ? ph.affector->affect(nullptr, base, i, j) : base;
		if (mc.selectedText()!=mirrored){
			//qDebug() << "resync placeholder mirror for " << m_curPlaceHolder << " mirror "<<j << " was: " << mc.selectedText() << " should be " << cc.selectedText() << " from " << cc.anchorLineNumber() << ":" << cc.anchorColumnNumber() << "->" << cc.lineNumber() << ":"<<cc.columnNumber()<<"\n";
			//if mirror synchronization is broken => resyncronize
			mc.replaceSelectedText(mirrored);
		}
	}

	m_placeHolderSynchronizing=false;
		
	/*
		ditch cursor mirrors in favor of QDocumentCursor::replaceSelectedText()
		
			* workaround mirror limitations re movement (no way to ensure proper
			synchronization when moving up/down)
			
			* make it relatively easy to implement affectors
	*/
	
	m_curPlaceHolder = i;
	
	viewport()->update();
}

/*!
	\brief Move to next placeholder

	\see setPlaceHolder
	\return is there actually a next placeholder
*/
bool QEditor::nextPlaceHolder()
{
	if ( m_placeHolders.isEmpty() )
		return false;

	/*++m_curPlaceHolder;

	if ( m_curPlaceHolder >= m_placeHolders.count() )
		m_curPlaceHolder = 0;
	*/
	int np=-1;
	for (int i=0; i< m_placeHolders.count();i++){
		if (m_placeHolders[i].cursor.beginBoundaryLarger(m_cursor) && 
			(np==-1 || m_placeHolders[i].cursor<=m_placeHolders[np].cursor) &&
			!m_placeHolders[i].autoOverride)
				np=i;
	}

	setPlaceHolder(np);
	return np!=-1;
}

/*!
	\brief Move to previous placeholder

	\see setPlaceHolder
	\return is there actually a previous placeholder
*/
bool QEditor::previousPlaceHolder()
{
	if ( m_placeHolders.isEmpty() )
		return false;

	/*if ( m_curPlaceHolder <= 0 )
		m_curPlaceHolder = m_placeHolders.count();

	--m_curPlaceHolder;*/
	int np=-1;
	for (int i=0; i< m_placeHolders.count();i++){
		if (m_cursor.endBoundaryLarger(m_placeHolders[i].cursor) && 
			(np==-1 || m_placeHolders[i].cursor>=m_placeHolders[np].cursor) &&
			!m_placeHolders[i].autoOverride)
				np=i;
	}	

	setPlaceHolder(np);
	return np!=-1;
}

/*!
	\return the code completion engine set to this editor, if any
*/
QCodeCompletionEngine* QEditor::completionEngine() const
{
	return m_completionEngine;
}

/*!
	\brief Set a code completion engine to the editor

	\warning Most completion engines can only be attached
	to a single editor due to issues in the widget used to
	dispaly matches so you got to clone them and, as a consequence
	QEditor will take ownership of the completion engines
	and delete them.
*/
void QEditor::setCompletionEngine(QCodeCompletionEngine *e)
{
	if ( m_completionEngine )
	{
        m_completionEngine->setEditor(nullptr);
		m_completionEngine->deleteLater();
	}

	m_completionEngine = e;

	if ( m_completionEngine )
	{
		m_completionEngine->setEditor(this);
	}
}

/*!
	\return the language definition set to this editor, if any
*/
QLanguageDefinition* QEditor::languageDefinition() const
{
	return m_definition;
}

/*!
	\brief Set a language definition to the editor
*/
void QEditor::setLanguageDefinition(QLanguageDefinition *d)
{
	m_definition = d;

	if ( m_doc )
		m_doc->setLanguageDefinition(d);

	if ( m_definition )
	{
		bool cuc = d->singleLineComment().count();

		QCE_ENABLE_ACTION("comment", cuc)
		QCE_ENABLE_ACTION("uncomment", cuc)
	} else {
		QCE_ENABLE_ACTION("comment", false)
		QCE_ENABLE_ACTION("uncomment", false)
	}
}

/*!
	\return the line at a given viewport position
*/
QDocumentLine QEditor::lineAtPosition(const QPoint& p) const
{
	return m_doc ? m_doc->lineAt(p) : QDocumentLine();
}

/*!
	\return The cursor object nearest to the given viewport position
*/
QDocumentCursor QEditor::cursorForPosition(const QPoint& p) const
{
	//qDebug("cursor for : (%i, %i)", p.x(), p.y());

	return m_doc ? m_doc->cursorAt(p) : QDocumentCursor();
}

/*!
	\brief Set the cursor to that nearest to a given viewport position
	\param moveView: If disabled, no check is made that the cursor is visible.
		   In this case you take over responsibility to call ensureCursorVisible later on
*/
void QEditor::setCursorPosition(const QPoint& p, bool moveView)
{
	//qDebug("cursor for : (%i, %i)", p.x(), p.y());

	QDocumentCursor c = cursorForPosition(p);

	if ( c.isValid() )
	{
		setCursor(c, moveView);
	}
}

/*!
	\brief Emitted whenever the position of the cursor changes
*/
void QEditor::emitCursorPositionChanged()
{
	m_cursorLinesFromViewTop = m_cursor.documentPosition().y() / m_doc->getLineSpacing() - verticalScrollBar()->value();
	emit cursorPositionChanged();
	emit copyAvailable(m_cursor.hasSelection());

	if ( m_definition )
		m_definition->match(m_cursor);

	if ( m_doc->impl()->hasMarks() )
		QLineMarksInfoCenter::instance()->cursorMoved(this);

}

/*!
	\brief Undo the last editing operation, if any on the stack
*/
void QEditor::undo()
{
	if ( m_doc )
	{
		if ( m_definition )
			m_definition->clearMatches(m_doc);

		m_doc->setProposedPosition(QDocumentCursor());

		m_doc->undo();

		QDocumentCursor c=m_doc->getProposedPosition();
        if(c.isValid() && !m_mirrors.size())
            setCursor(c);


		ensureCursorVisible();
		setFlag(CursorOn, true);
		emitCursorPositionChanged();
		repaintCursor();
	}
}

/*!
	\brief Redo the last undone editing operation, if any on the stack
*/
void QEditor::redo()
{
	if ( m_doc )
	{
		if ( m_definition )
			m_definition->clearMatches(m_doc);

		m_doc->redo();

		ensureCursorVisible();
		setFlag(CursorOn, true);
		emitCursorPositionChanged();
		repaintCursor();
	}
}

/*!
	\brief Cut the selected text, if any
*/
void QEditor::cut()
{
	copy();

    bool macroing = isMirrored();

	if ( macroing )
		m_doc->beginMacro();

	m_cursor.removeSelectedText();

	if ( atPlaceholder() ) // need new evaluation, because remove operation might have changed things
	{
		PlaceHolder& ph = m_placeHolders[m_curPlaceHolder];
		QString baseText = ph.cursor.selectedText();

		QKeyEvent ev(QEvent::KeyPress, Qt::Key_Paste, Qt::NoModifier); // just a dummy to be able to pass something reasonable to affect() - currently unused
		for ( int phm = 0; phm < ph.mirrors.count(); ++phm )
		{
			QString s = ph.affector ?  ph.affector->affect(&ev, baseText, m_curPlaceHolder, phm) : baseText;
			ph.mirrors[phm].replaceSelectedText(s);
		}
	}

	cursorMirrorsRemoveSelectedText();

	if ( macroing )
		m_doc->endMacro();

	clearCursorMirrors();

	ensureCursorVisible();
	setFlag(CursorOn, true);
	emitCursorPositionChanged();
	repaintCursor();
}

/*!
	\brief Copy the selected text, if any

	\note Column selection may be created but the can only be copied properly in a QCE editor
*/
void QEditor::copy()
{
	if ( !m_cursor.hasSelection() )
		return;

	QMimeData *d = createMimeDataFromSelection();
	QApplication::clipboard()->setMimeData(d);
	//QApplication::clipboard()->setText(m_cursor.selectedText());
}

/*!
	\brief Paste text from the clipboard to the current cursor position

	\note May paste column selections from other QCE editors
*/
void QEditor::paste()
{
	const QMimeData *d = QApplication::clipboard()->mimeData();

	if ( d )
		insertFromMimeData(d);
}

static bool unindent(const QDocumentCursor& cur)
{
	QDocumentLine beg(cur.line());
	int r = 0, n = 0, t = QDocument::tabStop();
	QString txt = beg.text().left(beg.firstChar());

	while ( txt.count() && (n < t) )
	{
		if ( txt.at(txt.length() - 1) == '\t' )
			n += t - (n % t);
		else
			++n;

		++r;
		txt.chop(1);
	}

	if ( !r )
		return false;

	QDocumentCursor c(cur);
	c.setSilent(true);
	c.movePosition(1, QDocumentCursor::StartOfBlock, QDocumentCursor::MoveAnchor);
	c.movePosition(r, QDocumentCursor::Right, QDocumentCursor::KeepAnchor);
	c.removeSelectedText();

	return true;
}

static void insertAtLineStart(const QDocumentCursor& cur, const QString& txt)
{
	QDocumentCursor c(cur);
	c.setSilent(true);
	c.setColumnNumber(0);
	c.insertText(txt);
}

static void removeFromStart(const QDocumentCursor& cur, const QString& txt)
{
	QDocumentLine l = cur.line();
	int pos = l.firstChar();

	if ( l.text().mid(pos, txt.length()) != txt )
		return;

	QDocumentCursor c(cur.document(), cur.lineNumber(), pos);
	c.setSilent(true);
	c.movePosition(txt.length(),
					QDocumentCursor::NextCharacter,
					QDocumentCursor::KeepAnchor);
	c.removeSelectedText();
}

/*!
 * \brief inserts a tab at given cursor position. Depending on the context and the
 * flags ReplaceIndentTabs and ReplaceTextTabs, this inserts spaces up to the next
 * tab stop, otherwise '\t' is inserted.
 */
void QEditor::insertTab(QDocumentCursor &cur)
{
	bool replaceTabs = flag(ReplaceIndentTabs);
	if (flag(ReplaceIndentTabs) != flag(ReplaceTextTabs)) {
		// need to check if cursor is in indent or in text
		QDocumentCursor cur(m_cursor);
		while (!cur.atLineStart()) {
			if (!cur.previousChar().isSpace()) {
				replaceTabs = flag(ReplaceTextTabs);
				break;
			}
			cur.movePosition(1, QDocumentCursor::PreviousCharacter);
		}
	}

	if (replaceTabs) {
		int tabStop = m_doc->tabStop();
		int spaceCount = tabStop - cur.columnNumber() % tabStop;
		cur.insertText(QString(spaceCount, ' '));
	} else {
		insertText(cur, "\t");
	}
}

void QEditor::tabOrIndentSelection()
{
	if (m_cursor.hasSelection()) {
		indentSelection();
	} else {
		insertTab();
	}
}

void QEditor::insertTab()
{
	bool macroing = m_mirrors.count();
	if (macroing) m_doc->beginMacro();

	insertTab(m_cursor);
	for ( int i = 0; i < m_mirrors.count(); ++i ) {
		insertTab(m_mirrors[i]);
	}

	if (macroing) m_doc->endMacro();
}

/*!
	\brief Indent the selection
*/
void QEditor::indentSelection()
{
	// TODO : respect tab stops in case of screwed up indent (correct it?)

	QString txt = flag(ReplaceIndentTabs) ? QString(m_doc->tabStop(), ' ') : QString("\t");
	
	if ( m_mirrors.count() )
	{
		m_doc->beginMacro();

		if ( !protectedCursor(m_cursor) )
			insertAtLineStart(m_cursor, txt);

		foreach ( const QDocumentCursor& m, m_mirrors )
			if ( !protectedCursor(m) )
				insertAtLineStart(m, txt);

		m_doc->endMacro();

	} else if ( !protectedCursor(m_cursor) ) {
		if ( !m_cursor.hasSelection() )

			insertAtLineStart(m_cursor, txt);
		else {
			QDocumentSelection s = m_cursor.selection();
			if ( s.end == 0 && s.startLine < s.endLine )
				s.endLine--; //only change last line if there is selected text
			QDocumentCursor c(m_doc, s.startLine);
			c.setSilent(true);
			c.beginEditBlock();

			while ( c.isValid() && (c.lineNumber() <= s.endLine) )
			{
				c.insertText(txt);
				c.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::ThroughFolding);

				if ( c.atEnd() )
					break;
			}

			c.endEditBlock();
		}
	}
}

/*!
	\brief Unindent the selection
*/
void QEditor::unindentSelection()
{
	if ( m_mirrors.count() )
	{
		m_doc->beginMacro();

		if ( !protectedCursor(m_cursor) )
			unindent(m_cursor);

		foreach ( const QDocumentCursor& m, m_mirrors ){
			if ( !protectedCursor(m) )
				unindent(m);
		}

		m_doc->endMacro();

	} else if ( !protectedCursor(m_cursor) ) {
		if ( !m_cursor.hasSelection())
			unindent(m_cursor);
		else {
			QDocumentSelection s = m_cursor.selection();
			if ( s.end == 0 && s.startLine < s.endLine )
				s.endLine--; //only change last line if there is selected text

			m_doc->beginMacro();

			for ( int i = s.startLine; i <= s.endLine; ++i )
			{
				unindent(QDocumentCursor(m_doc, i));
			}

			m_doc->endMacro();
		}
	}
}

/*!
	\brief Comment the selection (or the current line) using single line comments supported by the language
*/
void QEditor::commentSelection()
{
	if ( !m_definition )
		return;

	QString txt = m_definition->singleLineComment();

	if ( txt.isEmpty() )
		return;

	if ( m_mirrors.count() )
	{
		m_doc->beginMacro();

		m_definition->clearMatches(m_doc);  // Matches are not handled inside comments. We have to remove them. Otherwise they will stay forever in the comment line.

		if ( !protectedCursor(m_cursor) )
		insertAtLineStart(m_cursor, txt);

		foreach ( const QDocumentCursor& m, m_mirrors )
			if ( !protectedCursor(m) )
				insertAtLineStart(m, txt);

		m_doc->endMacro();

	} else if ( !protectedCursor(m_cursor) ) {
		m_definition->clearMatches(m_doc);  // Matches are not handled inside comments. We have to remove them. Otherwise they will stay forever in the comment line.
		if ( !m_cursor.hasSelection() )
			insertAtLineStart(m_cursor, txt);
		else {
			QDocumentSelection s = m_cursor.selection();
			if ( s.end == 0 && s.startLine < s.endLine )
				s.endLine--; //only change last line if there is selected text
			QDocumentCursor c(m_doc, s.startLine);
			c.setSilent(true);
			c.beginEditBlock();

			while ( c.isValid() && (c.lineNumber() <= s.endLine) )
			{
				c.insertText(txt);
				c.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::ThroughFolding);

				if ( c.atEnd() )
					break;
			}

			c.endEditBlock();
		}
	}
}

/*!
	\brief Uncomment the selection (or current line), provided it has been commented with single line comments
*/
void QEditor::uncommentSelection()
{
	if ( !m_definition )
		return;

	QString txt = m_definition->singleLineComment();

	if ( txt.isEmpty() )
		return;

	if ( m_mirrors.count() )
	{
		m_doc->beginMacro();

		if ( !protectedCursor(m_cursor) )
			removeFromStart(m_cursor, txt);

		foreach ( const QDocumentCursor& m, m_mirrors ){
			if ( !protectedCursor(m) )
				removeFromStart(m, txt);
		}

		m_doc->endMacro();

	} else if ( !protectedCursor(m_cursor) ){
		if ( !m_cursor.hasSelection() )
			removeFromStart(m_cursor, txt);
		else {
			QDocumentSelection s = m_cursor.selection();
			if ( s.end == 0 && s.startLine < s.endLine )
				s.endLine--; //only change last line if there is selected text
			if (s.startLine<0) s.startLine=0;
			if (s.endLine>m_doc->lines()-1) s.endLine=m_doc->lines()-1;

			m_doc->beginMacro();

			for ( int i = s.startLine; i <= s.endLine; ++i )
			{
				removeFromStart(QDocumentCursor(m_doc, i), txt);
			}

			m_doc->endMacro();
		}
	}
}

/*!
	\brief Toggle comments
	If all lines touched by a cursor or selection are commented remove the comment mark.
	Otherwise insert the comment mark
*/
void QEditor::toggleCommentSelection()
{
	if ( !m_definition )
		return;

	QString commentMark = m_definition->singleLineComment();
	bool allCommented = true;

	foreach (const QDocumentCursor &cursor, cursors()) {
		if (cursor.hasSelection()) {
			QDocumentCursor cur = cursor.selectionStart();
			for (int i = 0; i < cursor.endLineNumber() - cursor.startLineNumber() + 1; i++) {
				if (!cur.line().startsWith(commentMark)) {
					allCommented = false;
					break;
				}
				cur.movePosition(1, QDocumentCursor::NextLine);
			}
		} else {
			if (!cursor.line().startsWith(commentMark)) {
				allCommented = false;
			}
		}
		if (!allCommented) break;
	}

	if (allCommented) {
		uncommentSelection();
	} else {
		commentSelection();
	}
}

/*!
	\brief Select the whole text
*/
void QEditor::selectAll()
{
	clearCursorMirrors();

	m_cursor.movePosition(1, QDocumentCursor::Start);
	m_cursor.movePosition(1, QDocumentCursor::End, QDocumentCursor::KeepAnchor);

	emitCursorPositionChanged();

	viewport()->update();
}

void QEditor::selectNothing(){
    QDocumentCursor cur=cursor();
    cur.clearSelection();
	setCursor(cur);
}

/*!
 * \brief searches for the next occurence of the text in the last selection and
 * selects this additionally. If there is no selection, the word or command under
 * the cursor is selected.
 */
void QEditor::selectExpandToNextWord()
{
	if (!m_cursor.hasSelection()) {
		m_cursor.select(QDocumentCursor::WordOrCommandUnderCursor);
	} else {
		QDocumentCursor &lastCursor = m_cursor;
		foreach (const QDocumentCursor &cm, m_mirrors) {
			if (cm > lastCursor) lastCursor = cm;
		}
		QString selectedText = lastCursor.selectedText();
		QDocumentCursor searchCursor(lastCursor.document(), lastCursor.endLineNumber(), lastCursor.endColumnNumber());
		while (!searchCursor.atEnd()) {
			int col = searchCursor.line().text().indexOf(selectedText, searchCursor.columnNumber());
			if (col < 0) {
				searchCursor.movePosition(1, QDocumentCursor::EndOfLine);  // ensure searchCursor.atEnd() if no further matches are found
				searchCursor.movePosition(1, QDocumentCursor::NextLine);
			} else {
				QDocumentCursor c(m_cursor);
				m_cursor.setLineNumber(searchCursor.lineNumber());
				m_cursor.setColumnNumber(col);
				m_cursor.movePosition(selectedText.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
				// need to add the cursor mirror after changing m_cursor (if c == m_cursor, addCursorMirror does nothing)
				addCursorMirror(c);
				break;
			}
		}
	}

	emitCursorPositionChanged();
	viewport()->update();
}

/*!
 * \brief Expands the selection to include the full line.
 * If the selection does already span full lines, the next line will be added.
 * If there is no selection, the current line will be selected.
 */
void QEditor::selectExpandToNextLine()
{
	if (!m_cursor.hasSelection()) {
		m_cursor.movePosition(1, QDocumentCursor::StartOfLine);
		m_cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
		return;
	}
	if (!m_cursor.isForwardSelection()) {
		m_cursor.flipSelection();
	}
	m_cursor.setAnchorColumnNumber(0);
	m_cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);

	emitCursorPositionChanged();
	viewport()->update();
}

/*!
 * \brief Select all occurences of the current selection or the word/command under cursor
 * Note: if the selection is a word, matches are limited to complete words.
 */
void QEditor::selectAllOccurences()
{
	if (!m_cursor.hasSelection()) {
		m_cursor.select(QDocumentCursor::WordOrCommandUnderCursor);
	}
	if (!m_cursor.hasSelection()) {
		return;
	}
	QString text = m_cursor.selectedText();
	bool isWord = true;
	foreach (const QChar &c, text) {
		if (!c.isLetterOrNumber()) {
			isWord = false;
			break;
		}
	}
	QDocumentCursor cStart(m_cursor.document(), m_cursor.startLineNumber(), m_cursor.startColumnNumber());
	QDocumentCursor cEnd(m_cursor.document(), m_cursor.endLineNumber(), m_cursor.endColumnNumber());
	bool atBoundaries = (cStart.atLineStart() || !cStart.previousChar().isLetterOrNumber())
	                 && (cEnd.atLineEnd() || !cEnd.nextChar().isLetterOrNumber());

	// TODO: this is a quick solution: using the search panel to select all matches
	//       1. initialize the search with the required parameters
	//       2. select all matches
	//       3. close the search panel which was opened as a side effect of 1.
	// It would be better to be able to perform the search and select without interfering
	// with the search panel UI.
	find(text, false, false, isWord && atBoundaries, true);
	selectAllMatches();
	relayPanelCommand("Search", "closeElement", QList<QVariant>() << true);

	emitCursorPositionChanged();
	viewport()->update();
}

/*!
	\internal
*/
bool QEditor::event(QEvent *e)
{
	// preparations for tooltips

	if (e->type() == QEvent::ToolTip) {
		QHelpEvent *helpEvent = static_cast<QHelpEvent *>(e);
		emit hovered(helpEvent->pos()-QPoint(m_margins.left(),m_margins.top()));
		return true;
	}

	// qcodedit ...
	bool r = QAbstractScrollArea::event(e);

	if ( (e->type() == QEvent::Resize || e->type() == QEvent::Show) && m_doc )
		verticalScrollBar()->setMaximum(qMax(0, 1 + (m_doc->height() - viewport()->height()) / m_doc->getLineSpacing()));

    if ( e->type() == QEvent::Resize && flag(LineWrap)  && m_doc)
	{
		//qDebug("resize adjust (1) : wrapping to %i", viewport()->width());
		m_doc->setWidthConstraint(wrapWidth());
		ensureCursorVisible(KeepDistanceFromViewTop);
	}

	return r;
}

/*!
	\internal
*/
void QEditor::paintEvent(QPaintEvent *e)
{
	if ( !m_doc )
		return;

	QPainter p(viewport());
	const int yOffset = verticalOffset();
	const int xOffset = horizontalOffset();

	#ifdef Q_GL_EDITOR
	//QRect r(e->rect());
	QRect r(0, 0, viewport()->width(), viewport()->height());
	#else
	QRect r(e->rect());
	#endif

	//qDebug() << r;

	//p.setClipping(false);
	p.translate(-xOffset, -yOffset);

	QDocument::PaintContext ctx;
	ctx.xoffset = xOffset;
	ctx.yoffset = r.y() + yOffset;
	ctx.width = viewport()->width();
	ctx.height = qMin(r.height(), viewport()->height());
	ctx.palette = palette();
	if (m_cursor.isValid())
		ctx.cursors << m_cursor.handle();
	ctx.fillCursorRect = true;
	ctx.blinkingCursor = flag(CursorOn);

	if ( m_cursor.hasSelection() )
	{
		//qDebug("atempting to draw selected text");
		QDocumentSelection s = m_cursor.selection();

		ctx.selections << s;
	}

	// cursor mirrors :D
	foreach ( const QDocumentCursor& m, m_mirrors )
	{
		if ( ctx.blinkingCursor )
			ctx.extra << m.handle();

		if ( m.hasSelection() )
		{
			QDocumentSelection s = m.selection();

			ctx.selections << s;
		}
	}
	
	for (int i=0;i<ctx.selections.size();i++) {
		if (ctx.selections[i].start < 0) ctx.selections[i].start = 0;
		if (ctx.selections[i].end < 0) ctx.selections[i].end = 0;
	}

	if ( m_dragAndDrop.isValid() )
	{
		ctx.extra << m_dragAndDrop.handle();
	}
	if (flag(ShowPlaceholders)) {
		// put placeholder info into paint context
		ctx.placeHolders=m_placeHolders;
		ctx.curPlaceHolder=m_curPlaceHolder;
		ctx.lastPlaceHolder=m_lastPlaceHolder;
	}
        //qDebug("elapsed %d ms",tm.elapsed());

	// fill all the background, including areas on which the document does not draw
	// (e.g. left/right margins and the bottom of the viewport if it is larger than the document)
	QBrush bg = palette().base();
	if ( m_doc->getBackground().isValid() )
		bg.setColor(m_doc->getBackground());
	int width = qMax(viewport()->width(), m_doc->width());
	int height = qMax(viewport()->height(), m_doc->height() + m_doc->getLineSpacing());
	// the actual visible height may be up to one line larger than the doc height,
	// because the doc lines is are aligned to the top of the viewport. The viewport
	// then shows n.x lines and when scolled to the very bottom, the .x < 1 line
	// exceeds the document height.
	p.fillRect(0, 0, width, height, bg);

	p.save();
	m_doc->draw(&p, ctx);
	p.restore();
        //qDebug("drawn %d ms",tm.elapsed());

	//TODO: Customizable appearance
	//TODO: documentRegion is too large, isn't correctly redrawn (especially with a non fixed width font)


	/*
	debug code for cursor direction: 
	p.setPen(QColor(0,128,0));
	for (int i=0; i < m_placeHolders.count(); i++) {
		p.drawConvexPolygon(m_placeHolders[i].cursor.selectionStart().documentRegion());
		foreach (const QDocumentCursor& m, m_placeHolders[i].mirrors )
			p.drawConvexPolygon(m.selectionStart().documentRegion());
	}*/
	
}

/*!
	\internal
*/
void QEditor::timerEvent(QTimerEvent *e)
{
	int id = e->timerId();

	if ( id == m_blink.timerId() )
	{
		bool on = !flag(CursorOn);

		if ( m_cursor.hasSelection() )
			on &= style()->styleHint(QStyle::SH_BlinkCursorWhenTextSelected,
                                    nullptr,
									this) != 0;

		setFlag(CursorOn, on);

		repaintCursor();

		if(m_cursor.lineNumber()==m_lastLine && m_cursor.columnNumber()==m_lastColumn){
		    m_hoverCount++;
		    if(m_hoverCount==2) emit cursorHovered();
		}else{
		    m_lastLine=m_cursor.lineNumber();
		    m_lastColumn=m_cursor.columnNumber();
		    m_hoverCount=0;
		}

	} else if ( id == m_drag.timerId() ) {
		m_drag.stop();
		//startDrag();
	} else if ( id == m_click.timerId() ) {
		m_click.stop();
	}
}

static int max(const QList<QDocumentCursor>& l)
{
	int ln = 0;

	foreach ( const QDocumentCursor& c, l )
		if ( c.lineNumber() > ln )
			ln = c.lineNumber();

	return ln;
}

static int min(const QList<QDocumentCursor>& l)
{
	// beware the sign bit...
	int ln = 0x7fffffff;

	foreach ( const QDocumentCursor& c, l )
		if ( (c.lineNumber() < ln) || (ln < 0) )
			ln = c.lineNumber();

	return ln;
}

bool QEditor::protectedCursor(const QDocumentCursor& c) const
{
        Q_UNUSED(c);
	/*if ( c.hasSelection() )
	{
		int line = qMin(c.lineNumber(), c.anchorLineNumber()), end = qMax(c.lineNumber(), c.anchorLineNumber());
		return document()->linesPartiallyFolded(line,end);
	} else {
		return m_doc->line(c.lineNumber()).hasAnyFlag(QDocumentLine::Hidden | QDocumentLine::CollapsedBlockStart | QDocumentLine::CollapsedBlockEnd);
	}*/
	
	/*if (!isProtected) return false;
	if (!c.hasSelection()) return c.line().hasFlag(QDocumentLine::Hidden);
	return c.line().hasFlag(QDocumentLine::Hidden) || c.anchorLine().hasFlag(QDocumentLine::Hidden);*/
	return false;
}

/*!
	\internal
*/
void QEditor::keyPressEvent(QKeyEvent *e)
{
        //tm.start();
     //qDebug()<<"pressed"<<QTime::currentTime().toString("HH:mm:ss:zzz");
	// reset hover counter
	m_hoverCount=-1;

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->keyPressEvent(e, this) )
			return;

	EditOperation op = getEditOperation(e->modifiers(), (Qt::Key)e->key());
	bool handled = op != NoOperation;
	if (op >= EnumForCursorStart && op <= EnumForCursorEnd ){
		e->accept();

		if (m_mirrors.count()) {
			int maxSelect = 0;
			for (int i = -1; i < m_mirrors.count(); i++) {
				QDocumentCursor &cur = (i==-1) ? m_cursor : m_mirrors[i];
				// TODO can it happen with mirrors that the selection is across different lines?
				int len = cur.hasSelection() ? cur.selection().end-cur.selection().start : 0;
				if (len > maxSelect) maxSelect = len;
			}

			bool leftLine = false;
			for ( int i = -1; !leftLine && (i < m_mirrors.count()); ++i ) {
				QDocumentCursor &cur = (i==-1) ? m_cursor : m_mirrors[i];
				int curLine = cur.lineNumber();
				// handle unequal line lenghts
				if ((op == SelectCursorRight || op == SelectCursorWordRight) && cur.atLineEnd()) continue;
				if (op == SelectCursorLeft) {
					// TODO can it happen with mirrors that the selection is across different lines?
					int len = cur.hasSelection() ? cur.selection().end-cur.selection().start : 0;
					if (len < maxSelect) continue;
				}
				cursorMoveOperation(cur, op);
				leftLine = cur.lineNumber() != curLine;
			}

			if ( leftLine || (m_curPlaceHolder >= 0 && m_curPlaceHolder < m_placeHolders.size() && m_placeHolders[m_curPlaceHolder].autoRemoveIfLeft && !m_placeHolders[m_curPlaceHolder].cursor.isWithinSelection(m_cursor)))
				setPlaceHolder(-1);
			if (leftLine) {
				clearCursorMirrors();
				viewport()->update();
			} else {
				repaintCursor();
			}
		} else {
			// normal single cursor movement
			cursorMoveOperation(m_cursor, op);

			//setFlag(CursorOn, true);
			//ensureCursorVisible();

			if ( m_curPlaceHolder >= 0 && m_curPlaceHolder < m_placeHolders.size() && m_placeHolders[m_curPlaceHolder].autoRemoveIfLeft && !m_placeHolders[m_curPlaceHolder].cursor.isWithinSelection(m_cursor))
				setPlaceHolder(-1);
				/*if ( m_curPlaceHolder >= 0 && m_curPlaceHolder < m_placeHolders.count() )
				{
					// allow mirror movement out of line while in placeholder
					PlaceHolder& ph = m_placeHolders[m_curPlaceHolder];
					if ( ph.cursor.isWithinSelection(cursor) )
						return true;
					for ( int i = 0; i < ph.mirrors.count(); ++i )
						if ( ph.mirrors.at(i).isWithinSelection(cursor) )
							return true;
					if ( prev == cursor.lineNumber() && m_mirrors.empty()) {
						//mark placeholder as leaved
						m_curPlaceHolder = -1;
						return false;
					}
				}*/
			repaintCursor();
		}
	} else switch (op) {
	case Invalid:
		QApplication::beep();
		break;
	case CreateMirrorUp: case CreateMirrorDown:{
		int ln = - 1;
		QDocumentLine l;

		if (op == CreateMirrorUp )
		{
			ln = m_cursor.lineNumber();

			if ( m_mirrors.count() )
				ln = qMin(ln, min(m_mirrors));

			//qDebug("first %i", ln);

			l = m_doc->line(--ln);
		} else if ( op == CreateMirrorDown ) {
			ln = m_cursor.lineNumber();

			if ( m_mirrors.count() )
				ln = qMax(ln, max(m_mirrors));

			l = m_doc->line(++ln);
		}

		if ( l.isValid() )
		{
			addCursorMirror(QDocumentCursor(m_doc, ln, m_cursor.anchorColumnNumber()));
			repaintCursor();
			emitCursorPositionChanged();

			break;
		}
		break;
	}

	case ChangeOverwrite:
		setFlag(Overwrite, !flag(Overwrite));
		if(m_doc)
		    m_doc->setOverwriteMode(flag(Overwrite));

		// hack to make sure status panel gets updated...
		// TODO : emit signals on flag change?
		emitCursorPositionChanged();
		break;


	case NextPlaceHolder: nextPlaceHolder(); break;
	case PreviousPlaceHolder: previousPlaceHolder(); break;

	case TabOrIndentSelection: tabOrIndentSelection(); break;
	case InsertTab: insertTab(); break;
	case IndentSelection: indentSelection(); break;
	case UnindentSelection: unindentSelection(); break;

	case Undo: undo(); break;
	case Redo: redo(); break;
	case Copy: copy(); break;
	case Paste: paste(); break;
	case Cut: cut(); break;
	case Print: print();break;
	case SelectAll: selectAll(); break;
	case Find: find(); break;
	case FindNext: findNext(); break;
	case FindPrevious: findPrev(); break;
	case Replace: replacePanel(); break;

	case NoOperation:
	case DeleteLeft:
	case DeleteRight:
	case NewLine:
	default: {
		bool bOk = true;

		if (op == NoOperation) {
			QString text = e->text();

#if QT_VERSION >= 0x050000
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            if(e->modifiers()&(Qt::MetaModifier|Qt::ControlModifier))
                break;
#endif
#endif
            if ( text.isEmpty())
				break;
            QChar c=text.at(0);
            if(!c.isPrint() && !(c.category()==QChar::Other_Format))
                break;
            if(c==QChar('\t'))
                break;
		}

		bool prot = protectedCursor(m_cursor);

		foreach ( const QDocumentCursor& c, m_mirrors )
			prot |= protectedCursor(c);


		if ( prot ) break;

		handled = true;

		// clear matches to avoid offsetting and subsequent remanence of matches
		if ( m_definition )
			m_definition->clearMatches(m_doc);

		bool macroing = isMirrored() || m_mirrors.count() > 0;

		if ( macroing )
			m_doc->beginMacro();

		//TODO: blocked key
		if(!m_blockKey)
			processEditOperation(m_cursor, e, op);
		else
			m_blockKey=false;

		if ( atPlaceholder() ) // need new evaluation, because edit operation might have changed things
		{
			PlaceHolder& ph = m_placeHolders[m_curPlaceHolder];

			QString baseText = ph.cursor.selectedText();

			for ( int phm = 0; phm < ph.mirrors.count(); ++phm )
			{
				QString s = ph.affector ?  ph.affector->affect(e, baseText, m_curPlaceHolder, phm) : baseText;

				ph.mirrors[phm].replaceSelectedText(s);
			}
		}

		if ( m_mirrors.isEmpty() )
		{
			// this signal is NOT emitted when cursor mirrors are used ON PURPOSE
			// as it is the "standard" entry point for code completion, which cannot
			// work properly with cursor mirrors (art least not always and not simply)
			if ( handled )
				emit textEdited(e);

		} else {

			for ( int i = 0; bOk && (i < m_mirrors.count()); ++i )
				processEditOperation(m_mirrors[i], e, op);

		}

		if ( macroing )
			m_doc->endMacro();

	}

	}



	if ( !handled)
	{
		QAbstractScrollArea::keyPressEvent(e);

		foreach ( QEditorInputBindingInterface *b, m_bindings )
			b->postKeyPressEvent(e, this);
		return;
	}

	e->accept();
	emitCursorPositionChanged();
	setFlag(CursorOn, true);
	ensureCursorVisible();
#ifdef  Q_OS_MAC
	//repaintCursor(); // squeeze for a little speed
	if (QApplication::cursorFlashTime() > 0) {
		m_blink.start(QApplication::cursorFlashTime() / 2, this);
	}
#else
	repaintCursor();
#endif

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postKeyPressEvent(e, this);	
}

/*!
	\internal
*/
void QEditor::keyReleaseEvent(QKeyEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->keyReleaseEvent(e, this) )
			return;

	// currently the editor is doing nothing on KeyRelease

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postKeyReleaseEvent(e, this);
}

/*!
	\internal
*/
void QEditor::inputMethodEvent(QInputMethodEvent* e)
{
    foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->inputMethodEvent(e, this) )
			return;

	/*
	if ( m_doc->readOnly() )
	{
		e->ignore();
		return;
	}
	*/
//#ifdef Q_OS_MAC
    QString preEdit=e->preeditString();
    if( !preEdit.isEmpty()){
        int i=-1;
        m_cursor.beginEditBlock();
        if(preEditSet){
            i=preEditColumnNumber;
            m_cursor.movePosition(preEditLength,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
        }else{
            i=qMin(m_cursor.columnNumber(), m_cursor.anchorColumnNumber());
        }
        m_cursor.insertText(preEdit);
        m_cursor.line().addOverlay(QFormatRange(i,preEdit.length(),m_preEditFormat));
        m_cursor.endEditBlock();
        preEditSet=true;
        preEditColumnNumber=i;
        preEditLength=preEdit.length();
        preEditLineNumber=m_cursor.lineNumber();
        updateMicroFocus();
    }
//#endif

	if ( e->commitString().count() ) {
		m_cursor.beginEditBlock();
        if(preEditSet){
            preEditSet=false;
            if(m_cursor.lineNumber()==preEditLineNumber &&
               m_cursor.columnNumber()==preEditColumnNumber+preEditLength
            ){
                m_cursor.movePosition(preEditLength,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
                m_cursor.removeSelectedText();
            }
        }else{
#ifdef Q_OS_MAC
            // work-around for bug 1723
            // needs to handle chinese punctuation here, so filter only special, non-printable chars
            // see bug 1770

            if(e->commitString().count()==1){
                ushort code=e->commitString().at(0).unicode();
                if(code<32)
                    return;
            }
#endif
        }

		m_cursor.insertText(e->commitString());
#if (QT_VERSION < 0x040700) && (defined(Q_OS_MAC))
		if(!m_disableAccentHack)
			m_blockKey=true;
#endif

		m_cursor.endEditBlock();
	}

    if( preEdit.isEmpty() && e->commitString().isEmpty() && preEditSet) {
        m_cursor.beginEditBlock();
        m_cursor.movePosition(preEditLength, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);
        m_cursor.removeSelectedText();
        m_cursor.endEditBlock();
        preEditSet = false;
        preEditLength = 0;
    }

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postInputMethodEvent(e, this);

    e->accept();
}

/*!
	\internal
*/
void QEditor::mouseMoveEvent(QMouseEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->mouseMoveEvent(e, this) )
			return;

	forever
	{
		if ( !(e->buttons() & Qt::LeftButton) )
			break;

		if ( !( flag(MousePressed) || m_multiClickCursor.hasSelection() ) )
			break;

		if ( flag(MaybeDrag) )
		{
			m_drag.stop();

			if (	(e->globalPos() - m_dragPoint).manhattanLength() >
					QApplication::startDragDistance()
				)
				startDrag();

			//emit clearAutoCloseStack();
			break;
		}

		repaintCursor();

		const QPoint mousePos = mapToContents(e->pos());

		QDocumentCursor newCursor = cursorForPosition(mousePos);

		if ( newCursor.isNull() )
			break;

		if ( e->modifiers() & Qt::ControlModifier )
		{
			selectCursorMirrorBlock(newCursor, e->modifiers() & Qt::ShiftModifier);
		} else {
			if (m_multiClickCursor.isValid()) {
				m_cursor.select(m_multiClickCursor.lineNumber(), m_multiClickCursor.columnNumber(),
				                newCursor.lineNumber(), newCursor.columnNumber()
				                );
				m_cursor.expandSelect(m_multiClickCursor.property("isTripleClick").toBool() ? QDocumentCursor::LineUnderCursor : m_doubleClickSelectionType);
			} else {
				m_cursor.setSelectionBoundary(newCursor);
			}
		}

		ensureCursorVisible();
		//emit clearAutoCloseStack();
		emitCursorPositionChanged();

		repaintCursor();
		break;
	}

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postMouseMoveEvent(e, this);
	
}

/*!
	\internal
*/
void QEditor::mousePressEvent(QMouseEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->mousePressEvent(e, this) )
			return;

	forever
	{
		if ( !(e->buttons() & Qt::LeftButton) )
			break;

		QPoint p = mapToContents(e->pos());

		setFlag(MousePressed, true);
		setFlag(MaybeDrag, false);

		repaintCursor();

		if ( m_click.isActive() &&
			(( e->globalPos() - m_clickPoint).manhattanLength() <
				QApplication::startDragDistance() ))
		{
			m_multiClickCursor = m_cursor;
			m_multiClickCursor.clearSelection();  // just store the click position
			m_multiClickCursor.setProperty("isTripleClick", true);
			m_cursor.select(m_tripleClickSelectionType);
			m_click.stop();
		} else {
			QDocumentCursor cursor = cursorForPosition(p);

			if (!cursor.isValid() && !cursor.line().isValid() && cursor.lineNumber() > 0) {
				// clicked beyond end of doc: lineNumber is last line + 1
				// move cursor to end of doc.
				cursor.setLineNumber(cursor.lineNumber() - 1);
				cursor.movePosition(1, QDocumentCursor::EndOfLine);
			}

			if ( cursor.isNull() )
				break;

			if ( e->modifiers() == Qt::ShiftModifier )
			{
				clearCursorMirrors();
				m_cursor.setSelectionBoundary(cursor);
			} else if ( e->modifiers() & Qt::ControlModifier && ((e->modifiers() & Qt::ShiftModifier) || (e->modifiers() & Qt::AltModifier)) ) {
				//m_mirrors << cursor;
				if ( e->modifiers() & Qt::ShiftModifier )
				{
					selectCursorMirrorBlock(cursor, true);
				} else if ( (e->modifiers() & Qt::AltModifier) )
				{
					//remove existing mirrors if one is at the same position
					if ( m_cursor.isWithinSelection(cursor) || m_cursor.equal(cursor) )
					{
						if ( m_mirrors.size() )
						{
							m_cursor = m_mirrors.takeFirst();
							if (m_cursorMirrorBlockAnchor >= 0)
								m_cursorMirrorBlockAnchor--;
						} else
							setCursor(cursor);
						break;
					} else {
						bool removedExisting = false;
						for ( int i = 0; i < m_mirrors.size(); i++ )
							if ( m_mirrors[i].isWithinSelection(cursor) || m_mirrors[i].equal(cursor) )
							{
								m_mirrors.removeAt(i);
								removedExisting = true;
								if (m_cursorMirrorBlockAnchor >= i)
									m_cursorMirrorBlockAnchor--;
								break;
							}
						if ( removedExisting ) break;
					}
					m_cursorMirrorBlockAnchor = m_mirrors.size();
					addCursorMirror(cursor);
				}
			} else {

				const QDocumentCursor& cur = m_cursor;

				if ( m_cursor.hasSelection() )
				{
					bool inSel = cur.isWithinSelection(cursor);

					if ( !inSel )
					{
						foreach ( const QDocumentCursor& m, m_mirrors )
						{
							inSel = m.isWithinSelection(cursor);

							if ( inSel )
								break;
						}
					}

					if ( inSel && flag(AllowDragAndDrop) )
					{
						setFlag(MaybeDrag, true);

						m_dragPoint = e->globalPos();
						m_drag.start(QApplication::startDragTime(), this);

						break;
					}
				}

				m_multiClickCursor = QDocumentCursor();
				cutBuffer.clear();
				setCursor(cursor);
				break;
			}
		}

		ensureCursorVisible();
		//emit clearAutoCloseStack();
		cutBuffer.clear();
		emitCursorPositionChanged();
		repaintCursor();
		break;
	}

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postMousePressEvent(e, this);
	
}

/*!
	\internal
*/
void QEditor::mouseReleaseEvent(QMouseEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->mouseReleaseEvent(e, this) )
			return;

	repaintCursor();

	if ( flag(MaybeDrag) )
	{
		setFlag(MousePressed, false);
		setCursorPosition(mapToContents(e->pos()));

			m_cursor.clearSelection();
	}

	if ( flag(MousePressed) )
	{
		setFlag(MousePressed, false);

		setClipboardSelection();
	} else if (	e->button() == Qt::MidButton
				&& QApplication::clipboard()->supportsSelection()) {
		setCursorPosition(mapToContents(e->pos()));
		//setCursorPosition(viewport()->mapFromGlobal(e->globalPos()));

		const QMimeData *md = QApplication::clipboard()
								->mimeData(QClipboard::Selection);

		if ( md )
			insertFromMimeData(md);
	}

	repaintCursor();

	if ( m_drag.isActive() )
		m_drag.stop();

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postMouseReleaseEvent(e, this);
	
}

/*!
	\internal
*/
void QEditor::mouseDoubleClickEvent(QMouseEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->mouseDoubleClickEvent(e, this) )
			return;

	forever
	{
		if ( e->button() != Qt::LeftButton )
		{
			e->ignore();
			break;
		}

		setFlag(MousePressed, true);
		setFlag(MaybeDrag, false);

		repaintCursor();
		clearCursorMirrors();
		setCursorPosition(mapToContents(e->pos()));

		m_multiClickCursor = m_cursor;
		m_multiClickCursor.clearSelection();  // just store the click position
		m_multiClickCursor.setProperty("isTripleClick", false);

		if ( m_cursor.isValid() )
		{
			m_cursor.select(m_doubleClickSelectionType);

			setClipboardSelection();
			//emit clearAutoCloseStack();
			emitCursorPositionChanged();
			emitWordDoubleClicked();

			repaintCursor();
		} else {
			//qDebug("invalid cursor");
		}

		m_clickPoint = e->globalPos();
		m_click.start(qApp->doubleClickInterval(), this);
		break;
	}

	foreach ( QEditorInputBindingInterface *b, m_bindings )
		b->postMouseDoubleClickEvent(e, this);
	
}

/*!
	\internal
*/
void QEditor::dragEnterEvent(QDragEnterEvent *e)
{
	if (
			e
		&&
			e->mimeData()
		&&
			(
				e->mimeData()->hasFormat("text/plain")
			||
				e->mimeData()->hasFormat("text/html")
			)
		&&
			!e->mimeData()->hasFormat("text/uri-list")
		)
		e->acceptProposedAction();
	else
		return;

	m_dragAndDrop = QDocumentCursor();
}

/*!
	\internal
*/
void QEditor::dragLeaveEvent(QDragLeaveEvent *)
{
	const QRect crect = cursorRect(m_dragAndDrop);
	m_dragAndDrop = QDocumentCursor();

	if ( crect.isValid() )
		viewport()->update(crect);

}

/*!
	\internal
*/
void QEditor::dragMoveEvent(QDragMoveEvent *e)
{
	if (
			e
		&&
			e->mimeData()
		&&
			(
				e->mimeData()->hasFormat("text/plain")
			||
				e->mimeData()->hasFormat("text/html")
			)
		&&
			!e->mimeData()->hasFormat("text/uri-list")
		)
		e->acceptProposedAction();
	else
		return;

	QDocumentCursor c = cursorForPosition(mapToContents(e->pos()));

	if ( c.isValid() )
	{
		QRect crect = cursorRect(m_dragAndDrop);

		if ( crect.isValid() )
			viewport()->update(crect);

		m_dragAndDrop = c;

		// workaround for dragging
		// TODO 1: Exchange the use of KeepSurrounding for a check
		//         int lineSpacing = this->document()->getLineSpacing();
		//         if (e->pos().y() < lineSpacing || e->pos().y() > (height() - 2*lineSpacing))
		// TODO 2: The event is only fired when the mouse is moved, but scrolling should continue
		//         while dragging if the mouse is close to the border and not moved further
		//         (maybe even at different speeds depending on the distance to the border
		int backup = m_cursorSurroundingLines;
		m_cursorSurroundingLines = 1;  // restricting to 1 & KeepSurrounding is almost like scrolling
		ensureCursorVisible(m_dragAndDrop, KeepSurrounding);
		m_cursorSurroundingLines = backup;

		crect = cursorRect(m_dragAndDrop);
		viewport()->update(crect);
	}

	//e->acceptProposedAction();
}

/*!
	\internal
*/
void QEditor::dropEvent(QDropEvent *e)
{
	m_dragAndDrop = QDocumentCursor();

	QDocumentCursor c(cursorForPosition(mapToContents(e->pos())));

    if ( (e->source() == this) && (m_cursor.isWithinSelection(c)) ){
        e->setDropAction(Qt::CopyAction);
        e->accept();
		return;
    }

	if (
			e
		&&
			e->mimeData()
		&&
			(
				e->mimeData()->hasFormat("text/plain")
			||
				e->mimeData()->hasFormat("text/html")
			)
		&&
			!e->mimeData()->hasFormat("text/uri-list")
		)
	{
		e->acceptProposedAction();
	} else {
		return;
	}

	//repaintSelection();

	//m_doc->beginMacro();
	//m_cursor.beginEditBlock();
	QDocumentCursor insertCursor = cursorForPosition(mapToContents(e->pos()));
	
	if (
			(e->dropAction() == Qt::MoveAction)
		&&
			(
				(e->source() == this)
			||
				(e->source() == viewport())
			)
		)
	{
		insertCursor.setAutoUpdated(true);
		m_doc->beginMacro();
		
		m_cursor.removeSelectedText();
		cursorMirrorsRemoveSelectedText();

		clearCursorMirrors();
		m_cursor=insertCursor;//.moveTo(cursorForPosition(mapToContents(e->pos())));
		insertFromMimeData(e->mimeData());

		m_doc->endMacro();
		insertCursor.setAutoUpdated(false);
	} else {
		//qDebug("action : %i", e->dropAction());
		m_cursor.clearSelection();
		clearCursorMirrors();
		m_cursor=insertCursor;//.moveTo(cursorForPosition(mapToContents(e->pos())));
		insertFromMimeData(e->mimeData());
	}

	//m_cursor.endEditBlock();

	//m_doc->endMacro();
}

/*!
	\internal
*/
void QEditor::changeEvent(QEvent *e)
{
	QAbstractScrollArea::changeEvent(e);

	if (
			e->type() == QEvent::ApplicationFontChange
		||
			e->type() == QEvent::FontChange
		)
	{
		if ( !m_doc )
			return;

        m_doc->setBaseFont(font());
		//setTabStop(iTab);

	}
}

/*!
	\internal
*/
void QEditor::showEvent(QShowEvent *e)
{
	QCodeEdit *ce = QCodeEdit::manager(this);

	if ( ce )
		ce->panelLayout()->update();

	QAbstractScrollArea::showEvent(e);
	
	if ( flag(HardLineWrap)||flag(LineWidthConstraint) )
		m_doc->setWidthConstraint( m_LineWidth > 0 ? m_LineWidth : wrapWidth() );
	else if ( flag(LineWrap) )
		m_doc->setWidthConstraint( wrapWidth() );
	else
		m_doc->clearWidthConstraint();

	if ( flag(EnsureVisible) )
		ensureCursorVisible();
	
}

/*!
	\internal
	\brief Zoom in/out upon ctrl+wheel
*/
void QEditor::wheelEvent(QWheelEvent *e)
{
	if ( e->modifiers() & Qt::ControlModifier && flag(MouseWheelZoom))
	{
		const int delta = e->delta();

		if ( delta > 0 )
			zoom(1);
		else if ( delta < 0 )
			zoom(-1);

		//viewport()->update();

		return;
	}

	QAbstractScrollArea::wheelEvent(e);
	updateMicroFocus();
	//viewport()->update();
}

/*!
	\internal
*/
void QEditor::resizeEvent(QResizeEvent *)
{
	const QSize viewportSize = viewport()->size();

	if ( flag(HardLineWrap)||flag(LineWidthConstraint) ){
	    horizontalScrollBar()->setMaximum(qMax(0, m_LineWidth - viewportSize.width()));
	    horizontalScrollBar()->setPageStep(viewportSize.width());
	} else if ( flag(LineWrap) )
	{
	    //qDebug("resize t (2) : wrapping to %i", viewport()->width());

	    m_doc->setWidthConstraint(wrapWidth());
	} else {
	    horizontalScrollBar()->setMaximum(qMax(0, m_doc->width() - viewportSize.width()));
	    horizontalScrollBar()->setPageStep(viewportSize.width());
	}

	const int ls = m_doc->getLineSpacing();
	verticalScrollBar()->setMaximum(qMax(0, 1 + (m_doc->height() - viewportSize.height()) / ls));
	verticalScrollBar()->setPageStep(viewportSize.height() / ls);

	emit visibleLinesChanged();
	//qDebug("page step : %i", viewportSize.height() / ls);

	//if ( isCursorVisible() && flag(LineWrap) )
	//	ensureCursorVisible();
}

/*!
	\internal
*/
void QEditor::focusInEvent(QFocusEvent *e)
{
	setFlag(CursorOn, true);
	if (QApplication::cursorFlashTime() > 0) {
		m_blink.start(QApplication::cursorFlashTime() / 2, this);
	}
	//ensureCursorVisible();
	emit focusReceived();

	QAbstractScrollArea::focusInEvent(e);
}

/*!
	\internal
*/
void QEditor::focusOutEvent(QFocusEvent *e)
{
	setFlag(CursorOn, false);
	m_blink.stop();

	QAbstractScrollArea::focusOutEvent(e);
}

/*!
	\brief Context menu event

	All the (managed) actions added to the editor are showed in it by default.
*/
void QEditor::contextMenuEvent(QContextMenuEvent *e)
{
	foreach ( QEditorInputBindingInterface *b, m_bindings )
		if ( b->contextMenuEvent(e, this) )
			return;

	if ( !pMenu )
	{
		e->ignore();
		return;
	}

	e->accept();

	pMenu->exec(e->globalPos());
}

/*!
	\brief Close event

	When build with qmdilib support (e.g in Edyuk) this check for
	modifications and a dialog pops up to offer various options
	(like saving, discarding or canceling)
*/
void QEditor::closeEvent(QCloseEvent *e)
{
	#ifdef _QMDI_
	bool bOK = true;

	if ( isContentModified() )
		bOK = server()->maybeSave(this);

	if ( bOK )
	{
		e->accept();
		notifyDeletion();
	} else {
		e->ignore();
	}
	#else
	QAbstractScrollArea::closeEvent(e);
	#endif
}

#ifndef _QMDI_
/*!
	\return Whether the document has been modified.
*/
bool QEditor::isContentModified() const
{
	return m_doc ? !m_doc->isClean() : false;
}
#endif

/*!
	\brief Notify that the content is clean (modifications undone or document saved)

	\note Don't mess with this. The document knows better.
*/
void QEditor::setContentClean(bool y)
{
	setContentModified(!y);
}

/*!
	\brief Notify that the content has been modified

	\note Don't mess with this. The document knows better.
*/
void QEditor::setContentModified(bool y)
{
	#ifdef _QMDI_
	qmdiClient::setContentModified(y);
	#endif

	setWindowModified(y);
	emit contentModified(y);
}

/*!
	\brief Changes the file name

	This method does not affect files on disk (no save/load/move occurs)
*/
void QEditor::setFileName(const QString& f)
{
	REQUIRE(m_doc);
	
	QString prev = fileName();

	if ( f == prev )
		return;

	watcher()->removeWatch(QString(), this);

	m_doc->setFileName_DONOTCALLTHIS(f);

	if ( fileName().count() )
		watcher()->addWatch(fileName(), this);

	setTitle(name().count() ? name() : "untitled");
}

/*!
	\brief Set the title of the widget

	Take care of adding a "[*]" prefix so that document changes are visible
	on title bars.
*/
void QEditor::setTitle(const QString& title)
{
	QString s(title);

	if ( !s.contains("[*]") )
		s.prepend("[*]");

	setWindowTitle(s);
	emit titleChanged(title);
}

/*!
	\return The name of the file being edited (without its path)
*/
QString QEditor::name() const
{
	REQUIRE_RET(m_doc,"");
	return m_doc->getName();
}

/*!
	\return The full filename of the file being edited
*/
QString QEditor::fileName() const
{
	REQUIRE_RET(m_doc,"");
	return m_doc->getFileName();
}
QFileInfo QEditor::fileInfo() const{
	REQUIRE_RET(m_doc,QFileInfo());
	return m_doc->getFileInfo();
}

bool QEditor::isReadOnly() const
{
	REQUIRE_RET(m_doc, true);
	return m_doc->isReadOnly();
}

void QEditor::setReadOnly(bool b)
{
	REQUIRE(m_doc);
	m_doc->setReadOnly(b);
	emit readOnlyChanged(b);
}


/*!
	\brief Prevent tab key press to be considered as widget navigation
*/
bool QEditor::focusNextPrevChild(bool)
{
	// make sure we catch tabs :)

	return false;
}

void QEditor::registerEditOperation(const EditOperation& op){
	m_registeredOperations << op;
}

void QEditor::addEditOperation(const EditOperation& op, const Qt::KeyboardModifiers& modifiers, const Qt::Key& key){
    QKeySequence qkey=QKeySequence(((int)modifiers & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier | Qt::MetaModifier)) | (int)key);
    m_registeredKeys.insert(qkey.toString(), op);
	m_registeredOperations << op;
}

void QEditor::addEditOperation(const EditOperation& op, const QKeySequence::StandardKey& key){
	QList<QKeySequence> sc = QKeySequence::keyBindings(key);
	foreach (const QKeySequence& seq, sc){
		if (!seq.count()) continue;
		addEditOperation(op, (Qt::KeyboardModifiers)(seq[0] & Qt::KeyboardModifierMask), (Qt::Key)(seq[0] & ~Qt::KeyboardModifierMask));
	}
}

QEditor::EditOperation QEditor::getEditOperation(const Qt::KeyboardModifiers& modifiers, const Qt::Key& key){
    QKeySequence qkey=QKeySequence(((int)modifiers & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier | Qt::MetaModifier)) | (int)key);
    EditOperation op = (EditOperation) m_registeredKeys.value(qkey.toString() , NoOperation);
	static const int MAX_JUMP_TO_PLACEHOLDER = 5;
	switch (op){
	case IndentSelection: case UnindentSelection:
        //if (!m_cursor.hasSelection()) op = NoOperation; // works also if the cursor has no selection !
		break;
	case NextPlaceHolder: case PreviousPlaceHolder:
		if (m_placeHolders.isEmpty()) op = NoOperation;
		break;
	case NextPlaceHolderOrWord:
		op = CursorWordRight;
		foreach (const PlaceHolder& ph, m_placeHolders)
			if (ph.cursor.selectionStart() > m_cursor.selectionEnd() && !ph.autoOverride &&
			    ph.cursor.selectionStart().lineNumber() - m_cursor.selectionEnd().lineNumber() <= MAX_JUMP_TO_PLACEHOLDER  ){
				op = NextPlaceHolder;
				break;
			}
		break;
	case PreviousPlaceHolderOrWord:
		op = CursorWordLeft;
		foreach (const PlaceHolder& ph, m_placeHolders)
			if (ph.cursor.selectionEnd() < m_cursor.selectionStart() && !ph.autoOverride &&
			    m_cursor.selectionStart().lineNumber() - ph.cursor.selectionEnd().lineNumber() <= MAX_JUMP_TO_PLACEHOLDER ){
				op = PreviousPlaceHolder;
				break;
			}
		break;
	case NextPlaceHolderOrChar:
		op = CursorRight;
		foreach (const PlaceHolder& ph, m_placeHolders)
			if (ph.cursor.selectionStart() > m_cursor.selectionEnd() && !ph.autoOverride &&
				ph.cursor.selectionStart().lineNumber() - m_cursor.selectionEnd().lineNumber() <= MAX_JUMP_TO_PLACEHOLDER  ){
				op = NextPlaceHolder;
				break;
			}
		break;
	case PreviousPlaceHolderOrChar:
		op = CursorLeft;
		foreach (const PlaceHolder& ph, m_placeHolders)
			if (ph.cursor.selectionEnd() < m_cursor.selectionStart() && !ph.autoOverride &&
				m_cursor.selectionStart().lineNumber() - ph.cursor.selectionEnd().lineNumber() <= MAX_JUMP_TO_PLACEHOLDER ){
				op = PreviousPlaceHolder;
				break;
			}
		break;
	default:;
	}
	return op;
}

void QEditor::setEditOperations(const QHash<QString, int> &newOptions, bool mergeWithDefault){
	if (!mergeWithDefault) {
		m_registeredKeys = newOptions;
		return;
	}
	m_registeredKeys = m_registeredDefaultKeys;
    QHash<QString, int>::const_iterator i = newOptions.begin();
	while (i != newOptions.constEnd()) {
		m_registeredKeys.insert(i.key(),i.value());
		++i;
	}
}

QSet<int> QEditor::getAvailableOperations(){
	return m_registeredOperations;
}

QHash<QString, int> QEditor::getEditOperations(bool excludeDefault){
	if (!m_defaultKeysSet) { //todo: thread safe lock
		m_defaultKeysSet = true;

    addEditOperation(CursorUp, QKeySequence::MoveToPreviousLine);
    addEditOperation(CursorDown, QKeySequence::MoveToNextLine);
    addEditOperation(SelectCursorUp, QKeySequence::SelectPreviousLine);
    addEditOperation(SelectCursorDown, QKeySequence::SelectNextLine);

    addEditOperation(CursorLeft, QKeySequence::MoveToPreviousChar);
    addEditOperation(CursorRight, QKeySequence::MoveToNextChar);
    addEditOperation(SelectCursorLeft, QKeySequence::SelectPreviousChar);
    addEditOperation(SelectCursorRight, QKeySequence::SelectNextChar);

    addEditOperation(CursorStartOfLine, QKeySequence::MoveToStartOfLine);
    addEditOperation(CursorEndOfLine, QKeySequence::MoveToEndOfLine);
    addEditOperation(SelectCursorStartOfLine, QKeySequence::SelectStartOfLine);
    addEditOperation(SelectCursorEndOfLine, QKeySequence::SelectEndOfLine);

    addEditOperation(CursorStartOfDocument, QKeySequence::MoveToStartOfDocument);
    addEditOperation(CursorEndOfDocument, QKeySequence::MoveToEndOfDocument);
    addEditOperation(SelectCursorStartOfDocument, QKeySequence::SelectStartOfDocument);
    addEditOperation(SelectCursorEndOfDocument, QKeySequence::SelectEndOfDocument);

    #ifndef Q_OS_MAC  // Use the default Windows bindings.
		addEditOperation(CursorWordLeft, Qt::ControlModifier, Qt::Key_Left);
		addEditOperation(CursorWordRight, Qt::ControlModifier, Qt::Key_Right);
		addEditOperation(SelectCursorWordLeft, Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_Left);
		addEditOperation(SelectCursorWordRight, Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_Right);

		addEditOperation(CursorStartOfDocument, Qt::ControlModifier, Qt::Key_Home);
		addEditOperation(CursorEndOfDocument, Qt::ControlModifier, Qt::Key_End);
		addEditOperation(SelectCursorStartOfDocument, Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_Home);
		addEditOperation(SelectCursorEndOfDocument, Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_End);
	#else
	/*
		Except for pageup and pagedown, Mac OS X has very different behavior, we
		don't do it all, but here's the breakdown:

		Shift still works as an anchor, but only one of the other keys can be dow
		Ctrl (Command), Alt (Option), or Meta (Control).

		Command/Control + Left/Right -- Move to left or right of the line
						+ Up/Down -- Move to top bottom of the file.
						(Control doesn't move the cursor)

		Option	+ Left/Right -- Move one word Left/right.
				+ Up/Down  -- Begin/End of Paragraph.

		Home/End Top/Bottom of file. (usually don't move the cursor, but will select)

		There can be only one modifier (+ shift), but we also need to make sure
		that we have a "move key" pressed before we reject it.
	*/
        /* whyever fill the list with "invalid" commands ?????
		QList<Qt::KeyboardModifiers> modifierPairs;
		modifierPairs <<  (Qt::ControlModifier | Qt::AltModifier) << (Qt::ControlModifier | Qt::MetaModifier) << (Qt::AltModifier | Qt::MetaModifier);
		QList<Qt::Key> movementKeys;
		movementKeys << Qt::Key_Up << Qt::Key_Down << Qt::Key_Left << Qt::Key_Right;
		foreach (Qt::KeyboardModifiers mod, modifierPairs)
		    foreach (Qt::Key key, movementKeys)
			addEditOperation(Invalid, mod , key);
		modifierPairs <<  Qt::ControlModifier << Qt::AltModifier << Qt::MetaModifier;
		modifierPairs <<  (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier);
		movementKeys = QList<Qt::Key>() << Qt::Key_Home << Qt::Key_End;
		foreach (Qt::KeyboardModifiers mod, modifierPairs)
		    foreach (Qt::Key key, movementKeys)
			addEditOperation(Invalid, mod , key);
       */

		addEditOperation(CursorStartOfLine, Qt::AltModifier, Qt::Key_Up);
		addEditOperation(CursorEndOfLine, Qt::AltModifier, Qt::Key_Down);
		addEditOperation(SelectCursorStartOfLine, Qt::ShiftModifier | Qt::AltModifier, Qt::Key_Up);
		addEditOperation(SelectCursorEndOfLine, Qt::ShiftModifier | Qt::AltModifier, Qt::Key_Down);

		addEditOperation(CursorStartOfLine, Qt::ControlModifier, Qt::Key_Left);
		addEditOperation(CursorEndOfLine, Qt::ControlModifier, Qt::Key_Right);
		addEditOperation(SelectCursorStartOfLine, Qt::ShiftModifier | Qt::ControlModifier, Qt::Key_Left);
		addEditOperation(SelectCursorEndOfLine, Qt::ShiftModifier | Qt::ControlModifier, Qt::Key_Right);

		addEditOperation(CursorStartOfLine, Qt::MetaModifier, Qt::Key_Left);
		addEditOperation(CursorEndOfLine, Qt::MetaModifier, Qt::Key_Right);
		addEditOperation(SelectCursorStartOfLine, Qt::ShiftModifier | Qt::MetaModifier, Qt::Key_Left);
		addEditOperation(SelectCursorEndOfLine, Qt::ShiftModifier | Qt::MetaModifier, Qt::Key_Right);

		addEditOperation(CursorWordLeft, Qt::AltModifier, Qt::Key_Left);
		addEditOperation(CursorWordRight, Qt::AltModifier, Qt::Key_Right);
		addEditOperation(SelectCursorWordLeft, Qt::ShiftModifier | Qt::AltModifier, Qt::Key_Left);
		addEditOperation(SelectCursorWordRight, Qt::ShiftModifier | Qt::AltModifier, Qt::Key_Right);
	#endif

		addEditOperation(CursorPageUp, Qt::NoModifier, Qt::Key_PageUp);
		addEditOperation(SelectPageUp, Qt::ShiftModifier, Qt::Key_PageUp);
		addEditOperation(CursorPageDown, Qt::NoModifier, Qt::Key_PageDown);
		addEditOperation(SelectPageDown, Qt::ShiftModifier, Qt::Key_PageDown);

		addEditOperation(DeleteLeft, Qt::NoModifier, Qt::Key_Backspace);
        addEditOperation(DeleteRight, QKeySequence::Delete);
    #ifdef Q_OS_MAC
        addEditOperation(DeleteRight, Qt::ShiftModifier, Qt::Key_Backspace);
    #else
        addEditOperation(DeleteLeft, Qt::ShiftModifier, Qt::Key_Backspace);
    #endif

    #ifdef Q_OS_MAC
		addEditOperation(DeleteLeftWord, Qt::AltModifier, Qt::Key_Backspace);
		addEditOperation(DeleteRightWord, Qt::AltModifier, Qt::Key_Delete);
	#else
		addEditOperation(DeleteLeftWord, Qt::ControlModifier, Qt::Key_Backspace);
		addEditOperation(DeleteRightWord, Qt::ControlModifier, Qt::Key_Delete);
	#endif

		addEditOperation(NewLine, Qt::NoModifier, Qt::Key_Enter);
		addEditOperation(NewLine, Qt::NoModifier, Qt::Key_Return);

		addEditOperation(ChangeOverwrite, Qt::NoModifier, Qt::Key_Insert);

		addEditOperation(CreateMirrorUp, Qt::AltModifier | Qt::ControlModifier, Qt::Key_Up);
		addEditOperation(CreateMirrorDown, Qt::AltModifier | Qt::ControlModifier, Qt::Key_Down);

		registerEditOperation(NextPlaceHolder);
		registerEditOperation(PreviousPlaceHolder);
	#ifdef Q_OS_MAC
		registerEditOperation(NextPlaceHolderOrWord);
		registerEditOperation(PreviousPlaceHolderOrWord);
	#else
		addEditOperation(NextPlaceHolderOrWord, Qt::ControlModifier, Qt::Key_Right);
		addEditOperation(PreviousPlaceHolderOrWord, Qt::ControlModifier, Qt::Key_Left);
	#endif
		registerEditOperation(NextPlaceHolderOrChar);
		registerEditOperation(PreviousPlaceHolderOrChar);

		addEditOperation(TabOrIndentSelection, Qt::NoModifier, Qt::Key_Tab);
		addEditOperation(UnindentSelection, Qt::ShiftModifier, Qt::Key_Backtab);

		addEditOperation(Undo, QKeySequence::Undo);
		addEditOperation(Redo, QKeySequence::Redo);
		addEditOperation(Copy, QKeySequence::Copy);
		addEditOperation(Paste, QKeySequence::Paste);
		addEditOperation(Cut, QKeySequence::Cut);
		addEditOperation(Print, QKeySequence::Print);
		addEditOperation(SelectAll, QKeySequence::SelectAll);
		addEditOperation(Find, QKeySequence::Find);
		addEditOperation(FindNext, QKeySequence::FindNext);
		addEditOperation(FindPrevious, QKeySequence::FindPrevious);
		addEditOperation(Replace, QKeySequence::Replace);

		m_registeredDefaultKeys = m_registeredKeys;
	}
	if (!excludeDefault) return m_registeredKeys;
	else {
        QHash<QString, int> result = m_registeredKeys;
        foreach(QString key,m_registeredDefaultKeys.keys()){
                if(result.contains(key)){
                    if(result.value(key)==m_registeredDefaultKeys.value(key)){
                        result.remove(key);
                    }
                }else{
                    // add for removal
                    result.insert("#"+key,m_registeredDefaultKeys.value(key));
                }
        }
        return result;
	}
}

QString QEditor::translateEditOperation(const EditOperation& op){
	switch (op){
	case NoOperation: return tr("None");
	case Invalid: return tr("Invalid");

	case EnumForCursorStart: return tr("Internal");

	case CursorUp: return tr("Move cursor up");
	case CursorDown: return tr("Move cursor down");
	case CursorLeft: return tr("Move cursor left (1 character)");
	case CursorRight: return tr("Move cursor right (1 character)");
	case CursorWordLeft: return tr("Move cursor left (1 word)");
	case CursorWordRight: return tr("Move cursor right (1 word)");
	case CursorStartOfLine: return tr("Move cursor to line start");
	case CursorEndOfLine: return tr("Move cursor to line end");
	case CursorStartOfDocument: return tr("Move cursor to document start");
	case CursorEndOfDocument: return tr("Move cursor to document end");

	case CursorPageUp: return tr("Move cursor one page up");
	case CursorPageDown: return tr("Move cursor one page down");

	case EnumForSelectionStart: return tr("Internal");

	case SelectCursorUp: return tr("Select up");
	case SelectCursorDown: return tr("Select down");
	case SelectCursorLeft: return tr("Select left (1 character)");
	case SelectCursorRight: return tr("Select right (1 character)");
	case SelectCursorWordLeft: return tr("Select left (1 word)");
	case SelectCursorWordRight: return tr("Select right (1 word)");
	case SelectCursorStartOfLine: return tr("Select to line start");
	case SelectCursorEndOfLine: return tr("Select to line end");
	case SelectCursorStartOfDocument: return tr("Select to document start");
	case SelectCursorEndOfDocument: return tr("Select to document end");

	case SelectPageUp: return tr("Select page up");
	case SelectPageDown: return tr("Select page down");

	case EnumForCursorEnd: return tr("Internal");

	case DeleteLeft: return tr("Delete left character");
	case DeleteRight: return tr("Delete right character");
	case DeleteLeftWord: return tr("Delete left word");
	case DeleteRightWord: return tr("Delete right word");
	case NewLine: return tr("New line");

	case ChangeOverwrite: return tr("Change overwrite mode");
	case Undo: return tr("Undo");
	case Redo: return tr("Redo");
	case Copy: return tr("Copy");
	case Paste: return tr("Paste");
	case Cut: return tr("Cut");
	case Print: return tr("Print");
	case SelectAll: return tr("Select all");
	case Find: return tr("Find");
	case FindNext: return tr("Find next");
	case FindPrevious: return tr("Find previous");
	case Replace: return tr("Replace");

	case CreateMirrorUp: return tr("Create cursor mirror up");
	case CreateMirrorDown: return tr("Create cursor mirror down");
	case NextPlaceHolder: return tr("Next placeholder");
	case PreviousPlaceHolder: return tr("Previous placeholder");
	case NextPlaceHolderOrWord: return tr("Next placeholder or one word right");
	case PreviousPlaceHolderOrWord: return tr("Previous placeholder or one word left");
	case NextPlaceHolderOrChar: return tr("Next placeholder or character");
	case PreviousPlaceHolderOrChar: return tr("Previous placeholder or character");
	case TabOrIndentSelection: return tr("Tab or Indent selection");
	case InsertTab: return tr("Insert tab");
	case IndentSelection: return tr("Indent selection");
	case UnindentSelection: return tr("Unindent selection");

	}
	return tr("Unknown");
}

/*!
	\brief Start a drag and drop operation using the current selection
*/
void QEditor::startDrag()
{
	setFlag(MousePressed, false);
	QMimeData *data = createMimeDataFromSelection();

	QDrag *drag = new QDrag(this);
	drag->setMimeData(data);

	Qt::DropActions actions = Qt::CopyAction | Qt::MoveAction;
	Qt::DropAction action = drag->exec(actions, Qt::MoveAction);

	if ( (action == Qt::MoveAction) && (drag->target() != this))
	{
		m_cursor.removeSelectedText();
		cursorMirrorsRemoveSelectedText();
	}
}

/*!
	\brief Handle cursor movements upon key event
*/

void QEditor::cursorMoveOperation(QDocumentCursor &cursor, EditOperation eop){
	QDocumentCursor::MoveMode mode = eop >= EnumForSelectionStart ? QDocumentCursor::KeepAnchor : QDocumentCursor::MoveAnchor;
	if ( flag(LineWrap) && flag(CursorJumpPastWrap) )
		mode |= QDocumentCursor::ThroughWrap;
	QDocumentCursor::MoveOperation op = QDocumentCursor::NoMove;
	switch (eop){
	case CursorUp: case SelectCursorUp:
		op = QDocumentCursor::Up;
		cutBuffer.clear();
		break;
	case CursorDown: case SelectCursorDown:
		op = QDocumentCursor::Down;
		cutBuffer.clear();
		break;
	case CursorLeft: case SelectCursorLeft:
		if (flag(BidiVisualColumnMode)) op = QDocumentCursor::Left;
		else op = QDocumentCursor::PreviousCharacter;
		cutBuffer.clear();
		break;
	case CursorRight: case SelectCursorRight:
		if (flag(BidiVisualColumnMode)) op = QDocumentCursor::Right;
		else op = QDocumentCursor::NextCharacter;
		cutBuffer.clear();
		break;
	case CursorWordLeft: case SelectCursorWordLeft:
		if (flag(BidiVisualColumnMode)) op = QDocumentCursor::WordLeft;
		else op = QDocumentCursor::PreviousWord;
		break;
	case CursorWordRight: case SelectCursorWordRight:
		if (flag(BidiVisualColumnMode)) op = QDocumentCursor::WordRight;
		else op = QDocumentCursor::NextWord;
		break;
	case CursorStartOfLine: case SelectCursorStartOfLine:
		op = QDocumentCursor::StartOfLine;
		break;
	case CursorEndOfLine: case SelectCursorEndOfLine:
		op = QDocumentCursor::EndOfLine;
		break;
	case CursorStartOfDocument: case SelectCursorStartOfDocument:
		cutBuffer.clear();
		op = QDocumentCursor::Start;
		break;
	case CursorEndOfDocument: case SelectCursorEndOfDocument:
		cutBuffer.clear();
		op = QDocumentCursor::End;
		break;

	case CursorPageUp: case SelectPageUp:
		cutBuffer.clear();
		pageUp(mode);
		return;
	case CursorPageDown: case SelectPageDown:
		cutBuffer.clear();
		pageDown(mode);
		return;
	default:
		return;
	}

	cursor.movePosition(1, op, mode);
}



/*!
	\brief Go up by one page

	\note This method clears all cursor mirrors and suspend placeholder edition.
*/
void QEditor::pageUp(QDocumentCursor::MoveMode moveMode)
{
	setPlaceHolder(-1);
	clearCursorMirrors();

	if ( m_cursor.atStart() )
		return;

	int n = viewport()->height() / QDocument::getLineSpacing();

	repaintCursor();
	m_cursor.movePosition(n, QDocumentCursor::Up, moveMode);

	ensureCursorVisible();
	emitCursorPositionChanged();
	//updateMicroFocus();
}

/*!
	\brief Go down by one page

	\note This method clears all cursor mirrors.
*/
void QEditor::pageDown(QDocumentCursor::MoveMode moveMode)
{
	clearCursorMirrors();
	setPlaceHolder(-1);

	if ( m_cursor.atEnd() )
		return;

	int n = viewport()->height() / document()->getLineSpacing();

	repaintCursor();
	m_cursor.movePosition(n, QDocumentCursor::Down, moveMode);

	ensureCursorVisible();
	emitCursorPositionChanged();
}

/*!
	\internal
	\brief Process a key event for a given cursor

	This method only take care of editing operations, not movements.
*/
void QEditor::processEditOperation(QDocumentCursor& c, const QKeyEvent* e, EditOperation op)
{
	bool hasSelection = c.hasSelection();

	if ( hasSelection ) {
	    cutBuffer=c.selectedText();
	    c.removeSelectedText();
	}

	switch ( op )
	{
	case DeleteLeft :
		if(!hasSelection) c.deletePreviousChar();
		cutBuffer.clear();
		break;
	case DeleteRight :
		if(!hasSelection) c.deleteChar();
		cutBuffer.clear();
		break;

	case DeleteLeftWord :
		c.movePosition(1,QDocumentCursor::PreviousWord,QDocumentCursor::KeepAnchor);
		c.removeSelectedText();
		cutBuffer.clear();
		break;

	case DeleteRightWord :
		c.movePosition(1,QDocumentCursor::NextWord,QDocumentCursor::KeepAnchor);
		c.removeSelectedText();
		cutBuffer.clear();
		break;

	case NewLine:
		insertText(c, "\n");
		cutBuffer.clear();
		break;

	default :
	{
		QString text = e->text();

		if ( flag(ReplaceIndentTabs) )
		{
			text.replace("\t", QString(m_doc->tabStop(), ' '));
		}

		insertText(c, text);

		break;
	}
	}
}

void QEditor::selectCursorMirrorBlock(const QDocumentCursor &cursor, bool horizontalSelect)
{
	QDocumentCursorHandle *blockAnchor;
	if ( m_cursorMirrorBlockAnchor >= 0 && m_cursorMirrorBlockAnchor < m_mirrors.size() ) {
		blockAnchor = m_mirrors[m_cursorMirrorBlockAnchor].handle();
		while ( m_mirrors.size() > m_cursorMirrorBlockAnchor + 1) //remove all after m_cursorMirrorBlockAnchor
			m_mirrors.removeLast();
	} else {
		clearCursorMirrors();
		blockAnchor = m_cursor.handle();
	}
	if (!blockAnchor) return;
	// get column number for column selection
	int org = blockAnchor->anchorColumnNumber();
	int dst = cursor.columnNumber();
	// TODO : fix and adapt to line wrapping...

	int min = qMin(blockAnchor->lineNumber(), cursor.lineNumber());
	int max = qMax(blockAnchor->lineNumber(), cursor.lineNumber());

	if ( min != max )
	{
		for ( int l = min; l <= max; ++l )
		{
			if ( l != blockAnchor->lineNumber() )
				addCursorMirror(QDocumentCursor(m_doc, l, org));

		}

		if ( horizontalSelect )
		{
			blockAnchor->setColumnNumber(dst, QDocumentCursor::KeepAnchor);

			for ( int i = qMax(0, m_cursorMirrorBlockAnchor); i < m_mirrors.count(); ++i )
				m_mirrors[i].setColumnNumber(dst, QDocumentCursor::KeepAnchor);
		}
	} else {
		blockAnchor->setSelectionBoundary(cursor);
	}
}

void QEditor::preInsertUnindent(QDocumentCursor& c, const QString& s, int additionalUnindent)
{
	if ( !flag(AutoIndent) || flag(WeakIndent) ) return;
	if ( m_curPlaceHolder != -1 ) return;
	if ( !c.columnNumber() ) return;
	
	int firstNS = 0;
	QString txt = c.line().text();

	while ( (firstNS < txt.length()) && txt.at(firstNS).isSpace() )
		++firstNS;

	if ( !firstNS || firstNS < c.columnNumber() )
		return;

	if ( m_definition && m_definition->unindent(c, s) ) additionalUnindent++;
	
	if ( additionalUnindent <= 0 ) return;
	
	
	const int off = c.columnNumber() - firstNS;

	if ( off > 0 )
		c.movePosition(off, QDocumentCursor::PreviousCharacter);

	//TODO: fix unindent with tab/space mix by using c.previousChar() instead of txt.at(firstNS - 1) or calculate firstNS -= off.
	//      (example: "___|->", _ means space, -> tab, | cursor, write } )
	
	/*
		It might be possible to improve that part to have a more natural/smarter unindenting
		by trying to guess the scheme used by the user...
	*/
	for (;additionalUnindent > 0 && firstNS > 0; additionalUnindent--) {
		if ( txt.at(firstNS - 1) == '\t' )
		{
			c.movePosition(1, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);
			firstNS--;
		} else {
			const int ts = m_doc->tabStop();
			
			if (txt.contains(' ') && txt.contains('\t') && c.previousChar()=='\t') {
				--firstNS;
				c.movePosition(1, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);
			} else
				do
				{
					--firstNS;
					c.movePosition(1, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);
				} while ( QDocument::screenColumn(txt.constData(), firstNS, ts) % ts );
		}
	}		
	c.removeSelectedText();

	if ( off > 0 )
		c.movePosition(off, QDocumentCursor::NextCharacter);
}

/*!
	\brief Insert some text at a given cursor position
	
	This function is provided to keep indenting/outdenting working when editing
*/
void QEditor::insertText(QDocumentCursor& c, const QString& text)
{
    if ( protectedCursor(c) || text.isEmpty())
        return;

    QStringList lines = text.split('\n', QString::KeepEmptyParts);

    bool hasSelection = c.hasSelection();
    if (hasSelection && c.selectedText() == text) {
        if (!c.isForwardSelection())
            c.flipSelection();
        c.clearSelection();
        return;  // replacing a selection with itself -> nothing to do. (It's more safe to directly stop here, because the below indentation correction does not get all cases right).
    }

    bool beginNewMacro = !m_doc->hasMacros() && (hasSelection || flag(Overwrite) || lines.size()>1);
    if (beginNewMacro)
        m_doc->beginMacro();

    bool autoOverridePlaceHolder = false;
    if ( !hasSelection && flag(Overwrite) && !c.atLineEnd() )
        c.deleteChar();
    else {
        if ( hasSelection ){
            cutBuffer=c.selectedText();
            c.removeSelectedText();
        }

        //see isAutoOverrideText()
        for ( int i = m_placeHolders.size()-1; i >= 0 ; i-- )
            if ( m_placeHolders[i].autoOverride && m_placeHolders[i].cursor.lineNumber() == c.lineNumber() &&
                 m_placeHolders[i].cursor.anchorColumnNumber() == c.anchorColumnNumber() &&
                 (m_placeHolders[i].cursor.selectedText().startsWith(text)))
            {
                autoOverridePlaceHolder = true;
                if (m_placeHolders[i].cursor.selectedText() == text) removePlaceHolder(i);
            }
        if (autoOverridePlaceHolder) {
            for (int i=0; i<text.length(); i++)
                c.deleteChar();
        }
        QChar text0 = text.at(0);
        if (text0 == c.nextChar()) {
            // special functions for overwriting existing text
            if (flag(OverwriteClosingBracketFollowingPlaceholder) && (text0=='}' || text0==']')) {
                // remove placeholder when typing closing bracket at the end of a placeholder
                // e.g. \textbf{[ph]|} and typing '}'
                for ( int i = m_placeHolders.size()-1; i >= 0 ; i-- )
                    if (m_placeHolders[i].cursor.lineNumber() == c.lineNumber() &&
                            m_placeHolders[i].cursor.columnNumber() == c.columnNumber()
                            )
                    {
                        QChar openBracket = (text0=='}') ? '{' : '[';
                        if (findOpeningBracket(c.line().text(), c.columnNumber()-1, openBracket, text0) < m_placeHolders[i].cursor.anchorColumnNumber()) {
                            removePlaceHolder(i);
                            c.deleteChar();
                        }
                    }
            } else if (flag(OverwriteOpeningBracketFollowedByPlaceholder) && (text0=='{' || text0=='[')) {
                // skip over opening bracket if followed by a placeholder
                for ( int i = m_placeHolders.size()-1; i >= 0 ; i-- )
                    if (m_placeHolders[i].cursor.anchorLineNumber() == c.lineNumber() &&
                            m_placeHolders[i].cursor.anchorColumnNumber() == c.columnNumber() + 1
                            )  // anchor == start of placeholder
                    {
                        setPlaceHolder(i);
                        if (text.length() == 1) {
                            return; // don't insert the bracket because we've just jumped over it
                        } else {
                            QString remainder(text);
                            remainder.remove(0,1);
                            insertText(c, remainder);
                            return;
                        }
                    }
            }
        }
    }

    //prepare for auto bracket insertion
    QString writtenBracket;
    QString autoBracket;
    bool autoComplete = false;
    if (flag(AutoCloseChars) && !autoOverridePlaceHolder
            && (m_curPlaceHolder<0 || m_curPlaceHolder>=m_placeHolders.size() || m_placeHolders[m_curPlaceHolder].mirrors.isEmpty())
            && languageDefinition() && languageDefinition()->possibleEndingOfOpeningParenthesis(text)){
        autoComplete = true;
        foreach (const QString& s, languageDefinition()->openingParenthesis())
            if (s == text){
                writtenBracket = s;
                autoBracket = languageDefinition()->getClosingParenthesis(s);
                break;
            }
        if (autoBracket == writtenBracket)
            autoComplete = false; //don't things like "" or $$ (assuming only single letter self closing brackets exists)

        // no idea what the following code is supposed to do, it is probably erroneous
        // e.g {abc} abc |   , insert "{" at | will give a false match to the previous closing brace
        // check what would be the matching element if we inserted it
        if(autoComplete){
            c.insertText(text);
            // check if we are handling a multi-chrachter parenthesis, e.g. \[
            QString newAutoBracket;
            const QString& lineText = c.line().text().mid(0, c.columnNumber());
            foreach (const QString& s, languageDefinition()->openingParenthesis()){
                if (s.length() >= text.length() &&  //don't complete bracket of pasted text or codesnippets
                        lineText.endsWith(s)){
                    newAutoBracket = languageDefinition()->getClosingParenthesis(s);
                    writtenBracket = s;
                    break;
                }
            }
            if (newAutoBracket != autoBracket) {
                autoBracket=newAutoBracket;
            }

            QDocumentCursor prevc(c);
            QList<QList<QDocumentCursor> > matches = languageDefinition()->getMatches(prevc);
            bool found=false;
            for (int i=0; i < matches.size(); i++) {
                if (matches[i][0].anchorColumnNumber() == c.anchorColumnNumber()-writtenBracket.size()) {
                    if(matches[i][1].selectedText()==autoBracket){
                        prevc=matches[i][1];
                        found=true;
                        break;
                    }
                } else if (matches[i][1].anchorColumnNumber()==c.anchorColumnNumber()-writtenBracket.size()) {
                    if(matches[i][0].selectedText()==autoBracket){
                        prevc=matches[i][0];
                        found=true;
                        break;
                    }
                }
            }
            for(int k=0;k<text.size();k++){
                c.deletePreviousChar();
            }
            if(found){
                // check whether the found element has a matching element without our insertion
                prevc.flipSelection();
                matches = languageDefinition()->getMatches(prevc);
                if(matches.isEmpty()){
                    // no opening element without our insertion, so our insertion should *not* be autoclosed
                    autoComplete=false;
                }
            }
        }
    }

    //insert
    if ( (lines.count() == 1) || !flag(AdjustIndent)  || !flag(AutoIndent)) //|| flag(WeakIndent) || !flag(AdjustIndent)  || !flag(AutoIndent))
    {
        preInsertUnindent(c, lines.first(), 0);

        if ( flag(ReplaceIndentTabs) )
        {
            // TODO : replace tabs by spaces properly
        }

        c.insertText(text);
    } else {
        bool originallyAtLineStart = c.atLineStart();
        preInsertUnindent(c, lines.first(), 0);

        QDocumentCursor cc(c,false);
        if(!flag(WeakIndent)){
            // remove all prepending spaces as it is done later
            QString newText=lines.first().trimmed();

            for(int i=1;i<lines.count();i++){
                newText.append('\n');
                newText.append(lines.at(i).trimmed());
            }
            c.insertText(newText,true);
        }

        // FIXME ? work on strings to make sure command grouping does not interfere with cursor state...
        int firstChar = cc.line().firstChar();
        if (firstChar == -1) firstChar = cc.line().length(); //line contains only spaces
        QString constIndent = cc.line().text().left(qMax(0, qMin(firstChar, cc.columnNumber())));
        if ( flag(ReplaceIndentTabs) )
            constIndent.replace("\t", QString(m_doc->tabStop(), ' '));
        QString indent;
        int indentCount = 0;
        int delayedDeltaIndentCount=0; // this indent change is applied on the next line (e.g. unindentation is inhibited by prior characters like xy})

        QString newText=lines.takeFirst();
        cc.movePosition(1,QDocumentCursor::EndOfLine);
        QDocumentLine dl=cc.line();
        foreach (QParenthesis p, dl.parentheses()) {
            if ( !(p.role & QParenthesis::Indent) )
                continue;

            if ( p.role & QParenthesis::Open )
            {
                ++indentCount;
            }
            if ( p.role & QParenthesis::Close )
            {
                --indentCount;
            }
        }

        for (int i=0; i<lines.length(); i++)
        {
            QString l = lines[i];
            indentCount+=delayedDeltaIndentCount;
            delayedDeltaIndentCount=0;

            if(!flag(WeakIndent)){
                int n = 0;

                while ( n < l.count() && l.at(n).isSpace() )
                    ++n;

                l.remove(0, n);

                if ( m_definition )
                {
                    // TODO: FIXME ? work on strings to make sure command grouping does not interfere with cursor state...
                    //             (then the indentCount can be removed and the function should return the unindented indent,
                    //              but still needs to check for an unindent caused by a } at the beginning of the line)

                    //int deltaIndentCount=0;
                    //m_definition->indent(cc, &deltaIndentCount);



                    cc.movePosition(1,QDocumentCursor::Down);
                    cc.movePosition(1,QDocumentCursor::EndOfLine);

                    dl=cc.line();
                    QString dummyText=dl.text();
                    foreach (QParenthesis p, dl.parentheses()) {
                        if ( !(p.role & QParenthesis::Indent) )
                            continue;

                        if ( p.role & QParenthesis::Open )
                        {
                            ++delayedDeltaIndentCount;
                        }
                        if ( p.role & QParenthesis::Close )
                        {
                            if(delayedDeltaIndentCount){
                                --delayedDeltaIndentCount;
                            }else{
                                if(dummyText.left(p.offset).trimmed().isEmpty()){
                                    --indentCount;
                                    dummyText.replace(p.offset,p.length,QString(p.length,QChar(' ')));
                                }else{
                                    --delayedDeltaIndentCount;
                                }
                            }
                        }
                    }

                    if (indentCount >= 0){
                        indent=QString(indentCount,'\t');
                    }else{
                        //remove indent from constIndent
                        indent.clear();
                        if(!constIndent.isEmpty()){
                            int p=constIndent.indexOf('\t');
                            if(p>-1){
                                // remove one tab
                                constIndent.remove(p,1);
                            }else{
                                // remove tabStop spaces
                                constIndent.remove(0,m_doc->tabStop());
                            }
                        }
                    }

                    if ( flag(ReplaceIndentTabs) )
                        indent.replace("\t", QString(m_doc->tabStop(), ' '));
                }
            }
            //c.insertLine();
            newText.append("\n");
            if (i<lines.length()-1 || !l.isEmpty() || !originallyAtLineStart)
                // always indent line except last line if it is empty and the cursor was at line start
                // in that case, the original indentation is still present from the first line
                // example:
                // >....a
                // >|...c (and insert '....b\n'
            {
                //c.insertText(indent);
                //if(i>0 || flag(WeakIndent))
                newText.append(constIndent);  // indent is taken from previous line
                newText.append(indent);
            }

            //preInsertUnindent(c, l, additionalUnindent);

            //c.insertText(l);
            newText.append(l);
        }
        c.insertText(newText); // avoid inserting many single lines as it slows down txs considerably (contentschanged,patchStructure etc)
    }

    //bracket auto insertion
    if (autoComplete) {
	if (!cutBuffer.isEmpty()) {
	    c.insertText(cutBuffer+autoBracket);
	    c.movePosition(cutBuffer.length()+autoBracket.length(), QDocumentCursor::PreviousCharacter, QDocumentCursor::MoveAnchor);
	    c.movePosition(cutBuffer.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
	}

	if (flag(QEditor::AutoInsertLRM) && c.isRTL() && autoBracket == "}")
	    autoBracket = "}" + QString(QChar(LRM));

	QDocumentCursor copiedCursor = c.selectionEnd();
	PlaceHolder ph(autoBracket.length(),copiedCursor);
	ph.autoOverride = true;
	ph.cursor.handle()->setFlag(QDocumentCursorHandle::AutoUpdateKeepBegin);
	ph.cursor.handle()->setFlag(QDocumentCursorHandle::AutoUpdateKeepEnd);

	if (!cutBuffer.isEmpty()) {
	    addPlaceHolder(ph);
	    cutBuffer.clear();
	} else {
	    copiedCursor.insertText(autoBracket);
	    addPlaceHolder(ph);
	    c.movePosition(autoBracket.length(), QDocumentCursor::PreviousCharacter, QDocumentCursor::MoveAnchor);
	}
    }


    if (beginNewMacro)
        m_doc->endMacro();
}

void QEditor::insertText(const QString& text){
	insertText(m_cursor, text);
}

/*!
	\brief Write some text at the current cursor position
	
	This function is provided to make editing operations easier
	from the outside and to keep them compatible with cursor
	mirrors.
*/
void QEditor::write(const QString& s)
{
	document()->clearLanguageMatches();
	
	if (!m_mirrors.empty())
		m_doc->beginMacro();
	
	insertText(m_cursor, s);
	
	for ( int i = 0; i < m_mirrors.count(); ++i )
		insertText(m_mirrors[i], s);
	
	if (!m_mirrors.empty())
		m_doc->endMacro();
	
	emitCursorPositionChanged();
	setFlag(CursorOn, true);
	ensureCursorVisible();
	repaintCursor();
}

void QEditor::zoomIn()
{
	zoom(1);
}

void QEditor::zoomOut()
{
	zoom(-1);
}

void QEditor::resetZoom()
{
	zoom(0);
}

/*!
	\brief Zoom
	\param n relative zoom factor

	Zooming is achieved by changing the point size of the font as follows:

	fontPointSize += \a n
	
	n == 0 is used to reset the zoom
*/
void QEditor::zoom(int n)
{
	if ( !m_doc )
		return;
	
	if ( n == 0 )
		m_doc->setFontSizeModifier(0);
	else
		m_doc->setFontSizeModifier(m_doc->fontSizeModifier() + n);

	if (m_wrapAfterNumChars)
		setWrapAfterNumChars(m_wrapAfterNumChars); // updates the width for the new font
}

/*!
	\brief Obtain the value of panel margins
	\param l left margin
	\param t top margin
	\param r right margin
	\param b bottom margin
*/
void QEditor::getPanelMargins(int *l, int *t, int *r, int *b) const
{
	m_margins.getCoords(l, t, r, b);
}

/*!
	\brief Change the viewport margins to make room for panels
	\param l left margin
	\param t top margin
	\param r right margin
	\param b bottom margin
*/
void QEditor::setPanelMargins(int l, int t, int r, int b)
{
	m_margins.setCoords(l, t, r, b);

	setViewportMargins(l, t, r, b);

	if ( flag(LineWrap) )
	{
		//qDebug("panel adjust : wrapping to %i", viewport()->width());
		m_doc->setWidthConstraint(wrapWidth());
	}
}


/*!
	\brief Request repaint (using QWidget::update()) for the region occupied by the cursor
*/
void QEditor::repaintCursor()
{
	if ( m_mirrors.count() ){
		viewport()->update();
		return;
	}
	if (m_cursor.isNull())
		return;
	//check whether Format/Layout needs update
	bool updateAll=false;
	for(int i=getFirstVisibleLine();i<=getLastVisibleLine();i++){
	    if(m_doc->line(i).hasFlag(QDocumentLine::LayoutDirty)||!m_doc->line(i).hasFlag(QDocumentLine::FormatsApplied))
		updateAll=true;
	}
	if(updateAll){
	    viewport()->update();
	    return;
	}

	QRect r = cursorRect();

	if ( m_crect != r )
	{
		viewport()->update(m_crect.translated(horizontalOffset(), 0));
		m_crect = r;
		viewport()->update(m_crect.translated(horizontalOffset(), 0));
	} else {
		viewport()->update(m_crect.translated(horizontalOffset(), 0));
	}
}

/*!
	\return whether the cursor is currently visible
*/
bool QEditor::isCursorVisible() const
{
	QPoint pos = m_cursor.documentPosition();

	const QRect cursor(pos.x(), pos.y(), 1, document()->getLineSpacing());
	const QRect display(horizontalOffset(), verticalOffset(), viewport()->width(), viewport()->height());

	//qDebug() << pos << " belongs to " << display << " ?";

	return display.contains(pos); //cursor);
}

/*!
	\brief Ensure that the current cursor is visible
*/
void QEditor::ensureCursorVisible(const QDocumentCursor& cursor, MoveFlags mflags){
	QPoint pos = cursor.documentPosition();

	if (mflags & KeepDistanceFromViewTop && cursor == m_cursor) {
		int linesFromDocStart = pos.y() / m_doc->getLineSpacing();
		verticalScrollBar()->setValue(linesFromDocStart - m_cursorLinesFromViewTop);
	}

	int surrounding = (mflags&KeepSurrounding) ? m_cursorSurroundingLines : 0;

	const int ls = document()->getLineSpacing();

	int surroundingHeight = ls * surrounding;

	int ypos = pos.y(),
		yval = verticalScrollBar()->value() * ls, //verticalOffset(),
		ylen = viewport()->height(),
		yend = ypos + ls;
	int ytarget = -1;

     if ( ypos - surroundingHeight < yval ) {// cursor above
        ytarget = ypos / ls;
     } else if ( yend + surroundingHeight > (yval + ylen ) ) {// cursor below
          if (ypos > (yval + ylen) && (mflags & AllowScrollToTop)) { // cursor off screen: maximal move (cursor at topmost pos + surrounding - like in cursor above)
            ytarget = ypos / ls;
          } else { // cursor still on screen: minimal move (cursor at bottommost pos - surrounding)
            ytarget = 1 + (yend - ylen) / ls + surrounding + surrounding;
          }
     }

    if(ytarget>=0){
        ytarget-=surrounding;
        if(ytarget<0)
            ytarget=0;
#if QT_VERSION >= 0x040600
		int absDeltaY = qAbs(ytarget - verticalScrollBar()->value());
		if (flag(QEditor::SmoothScrolling) && mflags&Animated) {
			if (!m_scrollAnimation) {
				m_scrollAnimation = new QPropertyAnimation(this);
			}
			if (m_scrollAnimation->state() == QAbstractAnimation::Running) {
				m_scrollAnimation->stop();
			}
			m_scrollAnimation->setStartValue(verticalScrollBar()->value());
			m_scrollAnimation->setEndValue(ytarget);
			m_scrollAnimation->setTargetObject(verticalScrollBar());
			m_scrollAnimation->setPropertyName("value");
			m_scrollAnimation->setDuration(absDeltaY > 20 ? 300 : (absDeltaY * 300) / 20);
			if (absDeltaY > 40)
				m_scrollAnimation->setEasingCurve(QEasingCurve::InOutQuart);
			else if (absDeltaY > 20)
				m_scrollAnimation->setEasingCurve(QEasingCurve::InOutQuad);
			else
				m_scrollAnimation->setEasingCurve(QEasingCurve::Linear);
			m_scrollAnimation->start();
		} else {
			verticalScrollBar()->setValue(ytarget);
		}
#else
		verticalScrollBar()->setValue(ytarget);
#endif
    }

	int xval = horizontalOffset(),
		xlen = viewport()->width(),
		xpos = pos.x();

	if ( xpos < xval )
	{
		//qDebug("scroll leftward");
		horizontalScrollBar()->setValue(qMax(0, xpos - 4));
	} else if ( xpos > (xval + xlen - 4) ) {
		//qDebug("scroll rightward : %i", xpos - xlen + 4);
		horizontalScrollBar()
			->setValue(qMax(horizontalScrollBar()->value(), xpos - xlen + 4));
	}

	if ((mflags&ExpandFold) && m_cursor.line().isHidden())
		document()->expandParents(m_cursor.lineNumber());
}

/*!
	\brief Ensure that the current cursor is visible
*/
void QEditor::ensureCursorVisible(MoveFlags mflags)
{
	if ( !isVisible() )
	{
		setFlag(EnsureVisible, true);
		return;
	}	
	
	ensureCursorVisible(m_cursor, mflags);
	
	setFlag(EnsureVisible, false);
}


/*!
	\brief ensure that a given line is visible by updating scrollbars if needed
*/
void QEditor::ensureVisible(int line)
{
	if ( !m_doc )
		return;

	const int ls = document()->getLineSpacing();
	int ypos = m_doc->y(line),
		yval = verticalScrollBar()->value() * ls, //verticalOffset(),
		ylen = viewport()->height(),
		yend = ypos + ls;

	if ( ypos < yval )
		verticalScrollBar()->setValue(ypos / ls);
	else if ( yend > (yval + ylen) )
		verticalScrollBar()->setValue(1 + (yend - ylen) / ls);

}

/*!
	\brief Ensure that a given rect is visible by updating scrollbars if needed
*/
void QEditor::ensureVisible(const QRect &rect)
{
	if ( !m_doc )
		return;

	const int ls = document()->getLineSpacing();
	int ypos = rect.y(),
		yval = verticalOffset(),
		ylen = viewport()->height(),
		yend = ypos + rect.height();

	if ( ypos < yval )
		verticalScrollBar()->setValue(ypos / ls);
	else if ( yend > (yval + ylen) )
		verticalScrollBar()->setValue(1 + (yend - ylen) / ls);

	//verticalScrollBar()->setValue(rect.y());
}

/*!
	\return the rectangle occupied by the current cursor

	This will either return a cursorRect for the current cursor or
	the selectionRect() if the cursor has a selection.

	The cursor position, which would be the top left corner of the actual
	rectangle occupied by the cursor can be obtained using QDocumentCursor::documentPosition()

	The behavior of this method may surprise newcomers but it is actually quite sensible
	as this rectangle is mainly used to specify the update rect of the widget and the whole
	line needs to be updated to properly update the line background whenever the cursor move
	from a line to another.
*/
QRect QEditor::cursorRect() const
{
	return m_cursor.hasSelection() ? selectionRect() : cursorRect(m_cursor);
}

int QEditor::getFirstVisibleLine(){
	if (!document()) return 0;
	return document()->lineNumber(verticalOffset());
}

int QEditor::getLastVisibleLine(){
	if (!document()) return 0;
	return qMin(document()->lines()-1, document()->lineNumber(verticalOffset() + viewport()->height()) + 1);
}

void QEditor::scrollToFirstLine(int l){

	const int ls = document()->getLineSpacing();
	int ypos = m_doc->y(l-1);
	int yval = verticalOffset();
	int ylen = viewport()->height();
	int yend = ypos + ylen;

	if ( ypos < yval )
	    verticalScrollBar()->setValue(ypos / ls);
	else if ( yend > (yval + ylen) )
	    verticalScrollBar()->setValue(1 + (yend - ylen) / ls);

}

void QEditor::setCursorSurroundingLines(int s){
	m_cursorSurroundingLines = s;
}

/*!
	\return the rectangle occupied by the selection in viewport coordinates

	If the current cursor does not have a selection, its cursorRect() is returned.

	The returned rectangle will always be bigger than the actual selection has
	it is actually the union of all the rectangles occupied by all lines the selection
	spans over.
*/
QRect QEditor::selectionRect() const
{
	if ( !m_cursor.hasSelection() )
		return cursorRect(m_cursor);

	QDocumentSelection s = m_cursor.selection();

	if ( s.startLine == s.endLine )
		return cursorRect(m_cursor);

	int y = m_doc->y(s.startLine);
	QRect r = m_doc->lineRect(s.endLine);
	int height = r.y() + r.height() - y;

	r = QRect(0, y, viewport()->width(), height);
	r.translate(-horizontalOffset(), -verticalOffset());
	return r;
}

/*!
	\return the rectangle occupied by the given line, in viewport coordinates

	The width of the returned rectangle will always be the viewport width.
*/
QRect QEditor::lineRect(int line) const
{
	if ( !m_doc )
		return QRect();

	QRect r = m_doc->lineRect(line);
	r.setWidth(viewport()->width());
	r.translate(-horizontalOffset(), -verticalOffset());

	return r;
}

/*!
	\return The line rect of the given cursor
*/
QRect QEditor::cursorRect(const QDocumentCursor& c) const
{
	return lineRect(c.lineNumber());
}

/*!
	\return the area covered by the cursor (in widget coordinates)
*/
QRect QEditor::cursorMircoFocusRect() const
{
	QDocumentCursor c(m_cursor, false);
	QDocumentLine line=c.line();
	if (!c.isValid()) return QRect();
	if (c.columnNumber()<0 || c.columnNumber()>line.length()) return QRect();

	int left;
	int top;
	int temp;
	getPanelMargins(&left,&top,&temp,&temp);

	top += lineRect(m_cursor.lineNumber()).top();
	QPoint p = line.cursorToDocumentOffset(c.columnNumber());
	left += p.x();
	top += p.y();

	int width = 1; // TODO adapt for bold cursor and overwrite cursor
	int height = document()->getLineSpacing();
	return QRect(left, top, width, height);
}

/*!
	\brief creates a valid QMimeData object depending on the selection
*/
QMimeData* QEditor::createMimeDataFromSelection() const
{
	QMimeData *d = new QMimeData;

	if ( !m_cursor.hasSelection() )
	{
		qWarning("Generated empty MIME data");
		return d;
	}

	if ( m_mirrors.isEmpty() )
	{
		d->setText(m_cursor.selectedText());
	} else {
		// Multiple cursors. Use QMap to have the texts are ordered by line number.
		// Ordering by m_mirrors, would be selection order, which may be unexpected.
		// Also, selection order would require special handling of m_cursor insert
		// position depending on selection order (see bug 2315).
		// So line number order seems the more clear way to handle this.
		QMap<int, QString> texts;
		texts.insert(m_cursor.lineNumber(), m_cursor.selectedText());

		foreach ( const QDocumentCursor& m, m_mirrors )
		{
			texts.insert(m.lineNumber(), m.selectedText());
		}

		QString serialized = QStringList(texts.values()).join("\n");
		d->setText(serialized);
		d->setData("text/column-selection", serialized.toLocal8Bit());
	}

	//qDebug("generated selection from : \"%s\"", qPrintable(d->text()));

	return d;
}

/*!
	\brief Inserts the content of a QMimeData object at the cursor position

	\note Only plain text is supported... \see QMimeData::hasText()
*/
void QEditor::insertFromMimeData(const QMimeData *d)
{
	if ( d && m_cursor.isValid() && !isReadOnly() )
	{

		if ( d->hasFormat("text/column-selection") )
		{
			QStringList columns = QString::fromLocal8Bit(
										d->data("text/column-selection")
									).split('\n');

			m_doc->beginMacro();

			if ( m_cursor.hasSelection() )
				m_cursor.removeSelectedText();
			cursorMirrorsRemoveSelectedText();
			clearCursorMirrors();

			int col = m_cursor.columnNumber();
			//m_cursor.insertText(columns.takeFirst());
			insertText(m_cursor, columns.takeFirst());
			QDocumentCursor c = m_cursor;

			while ( columns.count() )
			{
				// check for end of doc and add line if needed...
				c.setColumnNumber(c.line().length());

				if ( c.atEnd() )
					c.insertText("\n");
				else
					c.movePosition(1, QDocumentCursor::NextCharacter);

				// align
				c.setColumnNumber(qMin(col, c.line().length()));

				// copy content of clipboard
				//c.insertText(columns.takeFirst());
				insertText(c, columns.takeFirst());
				addCursorMirror(c);
			}

			m_doc->endMacro();

		} else {
			QString txt;

			if ( d->hasFormat("text/plain") )
				txt = d->text();
			else if ( d->hasFormat("text/html") )
				txt = d->html();

			if (txt.isEmpty())
				return;

			bool slow = txt.size() > 5*1024;
			if (slow) emit slowOperationStarted();
			
			bool macroing = isMirrored() || m_mirrors.size();

			if ( macroing )
				m_doc->beginMacro();

			//if ( s )
			//{
			//	m_cursor.removeSelectedText();
			//}

			if ( !macroing && m_doc->lineCount() == 1 && m_doc->line(0).length() == 0)
				setText(txt, true);
			else {
				insertText(m_cursor, txt);
	
				if ( atPlaceholder() ) // need new evaluation, because insert operation might have changed things
				{
					PlaceHolder& ph = m_placeHolders[m_curPlaceHolder];
					QString baseText = ph.cursor.selectedText();
	
					QKeyEvent ev(QEvent::KeyPress, Qt::Key_Paste, Qt::NoModifier); // just a dummy to be able to pass something reasonable to affect() - currently unused
					for ( int phm = 0; phm < ph.mirrors.count(); ++phm )
					{
						QString s = ph.affector ?  ph.affector->affect(&ev, baseText, m_curPlaceHolder, phm) : baseText;
						ph.mirrors[phm].replaceSelectedText(s);
					}
				}
	
				for ( int i = 0; i < m_mirrors.count(); ++i )
				{
					insertText(m_mirrors[i], txt);
				}
			}

			if ( macroing )
				m_doc->endMacro();
			
			if (slow) emit slowOperationEnded();
		}

		ensureCursorVisible(KeepSurrounding);
		setFlag(CursorOn, true);

		emitCursorPositionChanged();
	}
}

/*!
	\brief Removes all cursor mirrors
*/
void QEditor::clearCursorMirrors()
{
	if ( m_mirrors.isEmpty() )
		return;
	
	setPlaceHolder(-1);
	repaintCursor();

	for ( int i = 0; i < m_mirrors.count(); ++i )
	{
		m_mirrors[i].setAutoUpdated(false);
	}

	m_mirrors.clear();
	m_cursorMirrorBlockAnchor = -1;
	
	viewport()->update();
}

/*!
	\brief Add a cursor mirror
*/
void QEditor::addCursorMirror(const QDocumentCursor& c)
{
	if ( c.isNull() || (c == m_cursor) || m_mirrors.contains(c) )
		return;

	m_mirrors << c;

	// necessary for smooth mirroring
	m_mirrors.last().setSilent(true);
	m_mirrors.last().setAutoUpdated(true);
	m_mirrors.last().setAutoErasable(false);
}

void QEditor::cursorMirrorsRemoveSelectedText()
{
	for ( int i = 0; i < m_mirrors.count(); ++i )
	{
		m_mirrors[i].removeSelectedText();
	}
}

void QEditor::setCursorBold(bool bold)
{
	if (m_doc)
		m_doc->impl()->setCursorBold(bold);
}

/*!
	\internal
	\brief Copy the selection to the clipboard
*/
void QEditor::setClipboardSelection()
{
	QClipboard *clipboard = QApplication::clipboard();

	if ( !clipboard->supportsSelection() || !m_cursor.hasSelection() )
		return;

	QMimeData *data = createMimeDataFromSelection();

	clipboard->setMimeData(data, QClipboard::Selection);
}

/*!
	\internal
	\brief Scroll contents

	Refer to QAbstractScrollArea doc for more info.
*/
void QEditor::scrollContentsBy(int dx, int dy)
{
	#ifdef Q_GL_EDITOR
	viewport()->update();
	#else
	const int ls = document()->getLineSpacing();
	viewport()->scroll(dx, dy * ls);
	#endif

	if (dy != 0)
		emit visibleLinesChanged();
}

QVariant QEditor::inputMethodQuery(Qt::InputMethodQuery property) const {
	switch(property) {
	case Qt::ImMicroFocus:
		return cursorMircoFocusRect();
	case Qt::ImFont:
		// TODO find out correct value: qtextcontol uses the following
		//return QVariant(d->cursor.charFormat().font());
		return QVariant();
	case Qt::ImCursorPosition:
		// TODO find out correct value: qtextcontol uses the following
		//return QVariant(d->cursor.position() - block.position());
		return QVariant();
	case Qt::ImSurroundingText:
		return QVariant(cursor().line().text());
	case Qt::ImCurrentSelection:
		return QVariant(cursor().selectedText());
	case Qt::ImMaximumTextLength:
		return QVariant(); // No limit.
	case Qt::ImAnchorPosition:
		// TODO find out correct value: qtextcontol uses the following
		//return QVariant(qBound(0, d->cursor.anchor() - block.position(), block.length()));
		return QVariant();
	default:
		return QVariant();
	}
}

/*!
	\internal
	\brief Workaround inconsistent width determination of viewport width
	accross platfroms when scrollbars are visible...
*/
int QEditor::wrapWidth() const
{
    #ifdef Q_OS_WIN32
	//if ( verticalScrollBar()->isVisible() )
	//	return viewport()->width() - verticalScrollBar()->width();
	#endif
	return (flag(HardLineWrap)||flag(LineWidthConstraint))&&m_LineWidth>0 ? m_LineWidth : viewport()->width();
}

/*!
	\internal
	\brief Slot called whenever document width changes

	Horizontal scrollbar is updated here.

	\note ensureCursorVisible() is NOT called.
*/
void QEditor::documentWidthChanged(int newWidth)
{
	if ( flag(LineWrap)&&!flag(HardLineWrap)&&!flag(LineWidthConstraint) )
	{
		horizontalScrollBar()->setMaximum(0);
		return;
	}

	int nv = qMax(0, newWidth - wrapWidth());

	if ( flag(HardLineWrap)||flag(LineWidthConstraint) ){
	    const QSize viewportSize = viewport()->size();
	    nv=(qMax(0, m_LineWidth - viewportSize.width()));
	}

	horizontalScrollBar()->setMaximum(nv);

	//ensureCursorVisible();
}

/*!
	\internal
	\brief Slot called whenever document height changes

	Vertical scrollbar is updated here (maximum is changed
	and value is modified if needed to ensure that the cursor is visible)
*/
void QEditor::documentHeightChanged(int newHeight)
{

	if ( flag(LineWrap) )
	{
		m_doc->setWidthConstraint(wrapWidth());
	}
	const int ls = document()->getLineSpacing();
	verticalScrollBar()->setMaximum(qMax(0, 1 + (newHeight - viewport()->height()) / ls));
	//ensureCursorVisible();
}

/*!
	\internal
	\brief Request paint event upon modification
	\param i first modified line
	\param n number of modified lines
*/
void QEditor::repaintContent(int i, int n)
{
	if ( !m_doc )
		return;

	#ifdef Q_GL_EDITOR
	viewport()->update();
	#else
	if ( n <= 0 )
	{
		viewport()->update();
	}

	QRect frect = m_doc->lineRect(i);

	const int yoff = verticalOffset() + viewport()->height();

	if ( frect.y() > yoff )
		return;

	if ( n == 1 )
	{
		frect.translate(0, -verticalOffset());
		//qDebug() << frect;
		viewport()->update(frect);
		return;
	}

	QRect lrect = m_doc->lineRect(i + n - 1);

	if ( (n > 0) && (lrect.y() + lrect.height()) < verticalOffset() )
		return;

	//qDebug("repainting %i lines starting from %ith one", n, i);

	//rect.setWidth(viewport()->width());
	//rect.setHeight(qMin(viewport()->height(), rect.height() * n));

	const int paintOffset = frect.y() - verticalOffset();
	const int paintHeight = lrect.y() + lrect.height() - frect.y();
	const int maxPaintHeight = viewport()->height() - paintOffset;

	QRect rect = QRect(
				frect.x(),
				paintOffset,
				viewport()->width(),
					(n <= 0)
				?
					maxPaintHeight
				:
					qMin(maxPaintHeight, paintHeight)
			);

	//qDebug() << rect;

	viewport()->update(rect);
	#endif
}

/*!
	\internal
	\brief Update function called upon editing action
	\param i First modified line
	\param n Number of modified lines

	If more than one line has been modified this function
	causes a repaint from the first visible line to the end
	of the viewport due to the way QAbstractScrollArea
	handles scrolling.

	\note This function used to update formatting but
	the highlighting has been moved to QDocument recently
*/
void QEditor::updateContent (int i, int n)
{
	if ( !m_doc )
		return;

	//qDebug("updating %i, %i", i, n);

	if (m_placeHolders.count()>0 && 
		!m_placeHolderSynchronizing) { //no recursion, if updateContent is called due to changes made by setPlaceHolder
		//look which placeholder has been modified
		if (m_mirrors.count()==0){
			for (int i=0;i<m_placeHolders.count();i++){
				if (m_placeHolders[i].autoOverride) continue;
				bool found=false;
				if (m_placeHolders[i].cursor.isWithinSelection(m_cursor))
					found=true;
				else foreach (const QDocumentCursor &c, m_placeHolders[i].mirrors) 
					if (c.isWithinSelection(m_cursor)) {
						found=true;
						break;
					}
				if (found) {
					if (m_curPlaceHolder!=i) 
						setPlaceHolder(i,false);
					break;
				}
			}
		}
		//remove placeholders
		//if another has been modified
		if (m_curPlaceHolder!=m_lastPlaceHolder && 
			m_lastPlaceHolder>=0 &&  m_lastPlaceHolder < m_placeHolders.count())
			if (m_placeHolders[m_lastPlaceHolder].autoRemove){
				removePlaceHolder(m_lastPlaceHolder);
				m_lastPlaceHolder=m_curPlaceHolder;
			}
		//if someone pressed enter
		if (m_curPlaceHolder>=0 && m_curPlaceHolder < m_placeHolders.count()) 
			if (m_placeHolders[m_curPlaceHolder].autoRemove && m_placeHolders[m_curPlaceHolder].cursor.lineNumber() != m_placeHolders[m_curPlaceHolder].cursor.anchorLineNumber())
				removePlaceHolder(m_curPlaceHolder);
		//empty ones (which are not currently used)
		for (int i=m_placeHolders.count()-1;i>=0;i--) {
			const PlaceHolder& ph = m_placeHolders.at(i);
			if (i != m_curPlaceHolder && i!=m_lastPlaceHolder && ph.autoRemove &&
				ph.cursor.lineNumber()==ph.cursor.anchorLineNumber() &&
				ph.cursor.columnNumber()==ph.cursor.anchorColumnNumber())
					removePlaceHolder(i);					
		}
		//invalid used ones
		if (m_lastPlaceHolder>=0 &&  m_lastPlaceHolder < m_placeHolders.count() &&
			m_placeHolders[m_lastPlaceHolder].cursor.lineNumber()==-1) {
			removePlaceHolder(m_lastPlaceHolder);
		}
		if (m_curPlaceHolder>=0 &&  m_curPlaceHolder < m_placeHolders.count() &&
			m_placeHolders[m_curPlaceHolder].cursor.lineNumber()==-1) {
			removePlaceHolder(m_curPlaceHolder);
		}
				
		 
		
		//stupid mirrors, resyncronize them if necessary 
		if (m_mirrors.count()>0 && m_curPlaceHolder>=0 && m_curPlaceHolder < m_placeHolders.count()){
			const PlaceHolder &ph = m_placeHolders[m_curPlaceHolder];
			foreach (const QDocumentCursor &mc, ph.mirrors)
				if (mc.selectedText()!=ph.cursor.selectedText()){
					setPlaceHolder(m_curPlaceHolder,false);
					break;
				}
		}
	}
	m_lastPlaceHolder=m_curPlaceHolder;
			
	repaintContent(i, n>1 ? -1 : n);
}

/*!
	\internal
*/
void QEditor::markChanged(QDocumentLineHandle *l, int mark, bool on)
{
	emit markChanged(fileName(), l, mark, on);
}

bool QEditor::displayModifyTime() const
{
    return mDisplayModifyTime;
}

bool QEditor::isMirrored(){
    bool macroing=atPlaceholder();
    if(macroing){
        if(m_placeHolders[m_curPlaceHolder].mirrors.count()<1)
            macroing=false;
    }
    return macroing;
}

void QEditor::addMark(int pos, QColor color, QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->addMark(pos,color,type);
    scrlBar->repaint();
}
void QEditor::addMarkDelayed(int pos, QColor color, QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->addMark(pos,color,type);
    //scrlBar->repaint();
}
void QEditor::paintMarks(){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->repaint();
}

void QEditor::addMark(QDocumentLineHandle *dlh, QColor color, QString type){
    if(dlh==nullptr)
        return;
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->addMark(dlh,color,type);
    scrlBar->repaint();
}

void QEditor::removeMark(int pos,QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->removeMark(pos,type);
    scrlBar->repaint();
}

void QEditor::removeMark(QDocumentLineHandle *dlh,QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->removeMark(dlh,type);
    scrlBar->repaint();
}

void QEditor::removeMark(QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->removeMark(type);
    scrlBar->repaint();
}

void QEditor::removeAllMarks(){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->removeAllMarks();
    scrlBar->removeAllShades();
}

void QEditor::addMarkRange(int start, int end, QColor color, QString type){
    MarkedScrollBar *scrlBar=qobject_cast<MarkedScrollBar*>(verticalScrollBar());
    scrlBar->addShade(start,end,color,type);
}

/*! @} */
