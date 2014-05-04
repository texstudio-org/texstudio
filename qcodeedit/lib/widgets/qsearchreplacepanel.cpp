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

#include "qsearchreplacepanel.h"

/*!
	\file qsearchreplacepanel.cpp
	\brief Implementation of the QSearchReplacePanel class.

	\see QSearchReplacePanel
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"
#include "qdocumentsearch.h"
#include "qformatscheme.h"
#include "utilsSystem.h"

#include "configmanagerinterface.h"

#include "QCompleter"
/*!
	\ingroup widgets
	@{
*/

/*!
	\class QSearchReplacePanel
	\brief A panel that provide inline search/replace functionalities
*/

QCE_AUTO_REGISTER(QSearchReplacePanel)

bool cbHasFocus(const QComboBox* cb) {
	if (cb->hasFocus()) return true;
	if (cb->lineEdit() && cb->lineEdit()->hasFocus()) return true;
	//test for popupped combobox
	foreach (QObject* o, cb->children()) {
		QWidget* w = qobject_cast<QWidget*>(o);
		if (!w) continue;
		if (w->isVisible() && w->hasFocus()) return true;
		foreach (QObject* p, o->children()) {
			QWidget* x = qobject_cast<QWidget*>(p);
			if (!x) continue;
			if (x->isVisible() && x->hasFocus()) return true;
		}
	}
	return false;
}

QStringList findHistory, replaceHistory;

/*!
	\brief Constructor
*/
QSearchReplacePanel::QSearchReplacePanel(QWidget *p)
	: QPanel(p),m_search(0),m_lastDirection(false),useLineForSearch(false),searchOnlyInSelection(false)
{
	setObjectName("searchPanel");
	
	ConfigManagerInterface* conf = ConfigManagerInterface::getInstance();
	//setupUi(this);
	// do it completely programatic
	this->resize(801, 71);
	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setContentsMargins(-1, 4, -1, 4);
	gridLayout->setVerticalSpacing(2);

	QSize buttonSize(22,22);

	// find section
	bClose = new QToolButton(this);
	bClose->setObjectName(("bClose"));
	bClose->setMinimumSize(buttonSize);
	bClose->setMaximumSize(buttonSize);
    bClose->setIcon(getRealIconCached("fileclose"));
	gridLayout->addWidget(bClose, 0, 0, 1, 1);

	QLabel* lbFind = new QLabel(this);
	lbFind->setObjectName(("lbFind"));
	gridLayout->addWidget(lbFind, 0, 1, 1, 1);

	cFind = new QComboBox(this);
	cFind->setEditable(true);
	cFind->completer()->setCompletionMode(QCompleter::PopupCompletion);
	cFind->completer()->setCaseSensitivity(Qt::CaseSensitive);
	cFind->setObjectName(("cFind"));
	QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy4.setHorizontalStretch(2);
	cFind->setSizePolicy(sizePolicy4);
	cFind->setMinimumSize(QSize(120, 22));
	conf->registerOption("Search/Find History", &findHistory, QStringList()); 
	conf->linkOptionToObject(&findHistory, cFind, LinkOptions(LO_UPDATE_ALL | LO_DIRECT_OVERRIDE));
	gridLayout->addWidget(cFind, 0, 2, 1, 1);

	bNext = new QToolButton(this);
	bNext->setObjectName(("bNext"));
	bNext->setMinimumSize(buttonSize);
	bNext->setMaximumSize(buttonSize);
    bNext->setIcon(getRealIconCached("down"));
	gridLayout->addWidget(bNext, 0, 3, 1, 1);

	bPrevious = new QToolButton(this);
	bPrevious->setObjectName(("bPrevious"));
	bPrevious->setMinimumSize(buttonSize);
	bPrevious->setMaximumSize(buttonSize);
    bPrevious->setIcon(getRealIconCached("up"));
	gridLayout->addWidget(bPrevious, 0, 4, 1, 1);

	bCount = new QToolButton(this);
	bCount->setObjectName(("bCount"));
	bCount->setMinimumSize(buttonSize);
	bCount->setMaximumSize(buttonSize);
    bCount->setIcon(getRealIconCached("count"));
	gridLayout->addWidget(bCount, 0, 5, 1, 1);

	QFrame *frameFindOptions = new QFrame(this);
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy1.setHeightForWidth(frameFindOptions->sizePolicy().hasHeightForWidth());
	frameFindOptions->setSizePolicy(sizePolicy1);
	frameFindOptions->setFrameShape(QFrame::NoFrame);
	layoutFindOptions = new QGridLayout(frameFindOptions);
	layoutFindOptions->setContentsMargins(0, 0, 0, 0);
	layoutFindOptions->setVerticalSpacing(0);
    //cbCase = new QCheckBox();
    cbCase = new QToolButton(frameFindOptions);
    cbCase->setCheckable(true);
	cbCase->setObjectName(("cbCase"));
	cbCase->setToolTip(tr("Enables case sensitive search."));
    cbCase->setIcon(getRealIconCached("case"));
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, caseConfig, true, "Search/Case Sensitive", cbCase);
	layoutFindOptions->addWidget(cbCase, 0, 0, 1, 1);

    cbWords = new QToolButton(frameFindOptions);
    cbWords->setCheckable(true);
	cbWords->setToolTip(tr("Only searches for whole words."));
	cbWords->setObjectName(("cbWords"));
    cbWords->setIcon(getRealIconCached("word"));
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, wordConfig, false, "Search/Whole Words", cbWords);
	layoutFindOptions->addWidget(cbWords, 0, 1, 1, 1);

    cbRegExp = new QToolButton(frameFindOptions);
    cbRegExp->setCheckable(true);
	cbRegExp->setToolTip(tr("This interprets the search text as a regular expression.\nSome common regexps:\n r* will find any amount of r, r+ is equal to rr*, a? will matches a or nothing,\n () groups expressions together, [xyz] will find x,y, or z, . matches everything, \\. matches .\nYou can use \\1 to \\9 in the replace text to insert a submatch."));
	cbRegExp->setObjectName(("cbRegExp"));
    cbRegExp->setIcon(getRealIconCached("regex"));
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, regexConfig, false, "Search/Regular Expression", cbRegExp);
	layoutFindOptions->addWidget(cbRegExp, 0, 2, 1, 1);

    cbHighlight = new QToolButton(frameFindOptions);
    cbHighlight->setCheckable(true);
	cbHighlight->setObjectName(("cbHighlight"));
	cbHighlight->setToolTip(tr("Highlights search matches and replaced text."));
    cbHighlight->setIcon(getRealIconCached("highlight"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(lbFind->sizePolicy().hasHeightForWidth());	sizePolicy3.setHeightForWidth(cbHighlight->sizePolicy().hasHeightForWidth());
	cbHighlight->setSizePolicy(sizePolicy3);
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, highlightConfig, true, "Search/Highlight", cbHighlight);
	layoutFindOptions->addWidget(cbHighlight, 0, 3, 1, 1);

    cbCursor = new QToolButton(frameFindOptions);
    cbCursor->setCheckable(true);
	cbCursor->setToolTip(tr("Starts the search from the current cursor position."));
	cbCursor->setObjectName(("cbCursor"));
    cbCursor->setIcon(getRealIconCached("cursor"));
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, cursorConfig, true, "Search/Cursor", cbCursor);
	layoutFindOptions->addWidget(cbCursor, 0, 4, 1, 1);

    cbSelection = new QToolButton(frameFindOptions);
    cbSelection->setCheckable(true);
	cbSelection->setToolTip(tr("Only searches in the selected text."));
	cbSelection->setObjectName(("cbSelection"));
    cbSelection->setIcon(getRealIconCached("selection"));
    CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, selectionConfig, false, "Search/Selection", cbSelection);
	layoutFindOptions->addWidget(cbSelection, 0, 5, 1, 1);

	gridLayout->addWidget(frameFindOptions, 0, 6, 1, 1);

	// replace section
	cbReplace = new QCheckBox(this);
	cbReplace->setObjectName(("cbReplace"));
	cbReplace->setChecked(true);
	gridLayout->addWidget(cbReplace, 1, 0, 1, 1, Qt::AlignCenter);

	QLabel *lbReplace = new QLabel(this);
	lbReplace->setObjectName("lbReplace");
	gridLayout->addWidget(lbReplace, 1, 1, 1, 1);

	cReplace = new QComboBox(this);
	cReplace->setEditable(true);
	cReplace->completer()->setCompletionMode(QCompleter::PopupCompletion);
    cReplace->completer()->setCaseSensitivity(Qt::CaseSensitive);
	cReplace->setObjectName(("cReplace"));
	cReplace->setEnabled(true);
	QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Fixed);
	sizePolicy7.setHorizontalStretch(2);
	sizePolicy7.setVerticalStretch(0);
	sizePolicy7.setHeightForWidth(cReplace->sizePolicy().hasHeightForWidth());
	cReplace->setSizePolicy(sizePolicy7);
	cReplace->setMinimumSize(QSize(120, 22));
	cReplace->setMaximumSize(QSize(1200, 16777215));
	conf->registerOption("Search/Replace History", &replaceHistory, QStringList());
	conf->linkOptionToObject(&replaceHistory, cReplace, LinkOptions(LO_UPDATE_ALL | LO_DIRECT_OVERRIDE));
	gridLayout->addWidget(cReplace, 1, 2, 1, 1);

	bReplaceNext = new QToolButton(this);
	bReplaceNext->setObjectName(("bReplaceNext"));
	bReplaceNext->setMinimumSize(buttonSize);
	bReplaceNext->setMaximumSize(buttonSize);
    bReplaceNext->setIcon(getRealIconCached("replacedown"));
	gridLayout->addWidget(bReplaceNext, 1, 3, 1, 1);

	bReplacePrevious = new QToolButton(this);
	bReplacePrevious->setObjectName(("bReplacePrevious"));
	bReplacePrevious->setMinimumSize(buttonSize);
	bReplacePrevious->setMaximumSize(buttonSize);
    bReplacePrevious->setIcon(getRealIconCached("replaceup"));
	gridLayout->addWidget(bReplacePrevious, 1, 4, 1, 1);

	bReplaceAll = new QToolButton(this);
	bReplaceAll->setObjectName(("bReplaceAll"));
	bReplaceAll->setMinimumSize(buttonSize);
	bReplaceAll->setMaximumSize(buttonSize);
    bReplaceAll->setIcon(getRealIconCached("replaceall"));
	gridLayout->addWidget(bReplaceAll, 1, 5, 1, 1);

	QFrame* frameReplaceOptions = new QFrame(this);
	frameReplaceOptions->setObjectName(("frameReplaceOptions"));
	frameReplaceOptions->setFrameShape(QFrame::NoFrame);
	layoutReplaceOptions = new QGridLayout(frameReplaceOptions);
	layoutReplaceOptions->setContentsMargins(0, 0, 0, 0);
	layoutReplaceOptions->setVerticalSpacing(0);
	cbPrompt = new QCheckBox(frameReplaceOptions);
	cbPrompt->setToolTip(tr("Ask before any match is replaced."));
	cbPrompt->setObjectName(("cbPrompt"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, askConfig, false, "Search/Ask before Replace", cbPrompt);
	layoutReplaceOptions->addWidget(cbPrompt);

	cbEscapeSeq = new QCheckBox(frameReplaceOptions);
	cbEscapeSeq->setToolTip(tr("Enables the use of escape characters. These are:\n \\n = new line, \\r = carriage return, \\t = tab, \\\\ = \\"));
	cbEscapeSeq->setObjectName(("cbEscapeSeq"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, escapeConfig, false, "Search/Escape Sequence", cbEscapeSeq);
	layoutReplaceOptions->addWidget(cbEscapeSeq);

	gridLayout->addWidget(frameReplaceOptions, 1, 6, 1, 1);


	//retranslateUi(this);
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), cbReplace, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), lbReplace, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), cReplace, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplacePrevious, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceNext, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), frameReplaceOptions, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceAll, SLOT(setVisible(bool)));
	QObject::connect(bClose, SIGNAL(clicked()), this, SLOT(close()));

	// connect by name
	QMetaObject::connectSlotsByName(this);
	connect(cFind->lineEdit(),SIGNAL(textEdited(QString)),SLOT(cFind_textEdited(QString)));
	connect(cReplace->lineEdit(),SIGNAL(textEdited(QString)),SLOT(cReplace_textEdited(QString)));

	// set texts
    bClose->setToolTip(tr("Close search/replace panel"));
    cFind->setToolTip(tr("Text or pattern to search for"));
    bNext->setToolTip(tr("Find next"));
    bPrevious->setToolTip(tr("Find previous"));
    bCount->setToolTip(tr("Count occurences"));
    cReplace->setToolTip(tr("Replacement text"));
    bReplaceNext->setToolTip(tr("Replace and find next"));
    bReplacePrevious->setToolTip(tr("Replace and find previous"));
    bReplaceAll->setToolTip(tr("Replace all"));

    lbFind->setText(tr("Find:"));
	lbFind->setMinimumWidth(lbFind->sizeHint().width());
    cbCase->setText(tr("Case"));
	cbCase->setMinimumWidth(cbCase->sizeHint().width());
    cbWords->setText(tr("Words"));
	cbWords->setMinimumWidth(cbWords->sizeHint().width());
    cbRegExp->setText(tr("Regexp"));
	cbRegExp->setMinimumWidth(cbRegExp->sizeHint().width());
    cbHighlight->setText(tr("Highlight all"));
	cbHighlight->setMinimumWidth(cbHighlight->sizeHint().width());
    cbCursor->setText(tr("Cursor"));
	cbCursor->setMinimumWidth(cbCursor->sizeHint().width());
    cbSelection->setText(tr("Selection"));
	cbSelection->setMinimumWidth(cbSelection->sizeHint().width());
    lbReplace->setText(tr("Replace:"));
    cbPrompt->setText(tr("Prompt on replace"));
	cbPrompt->setMinimumWidth(cbPrompt->sizeHint().width());
    cbEscapeSeq->setText(tr("Escape sequences"));
	cbEscapeSeq->setMinimumWidth(cbEscapeSeq->sizeHint().width());

	minimum_width=bClose->sizeHint().width()
			+qMax(lbFind->sizeHint().width(), lbReplace->sizeHint().width())
			+cFind->minimumSize().width()
			+3*bNext->sizeHint().width()
			+gridLayout->contentsMargins().left()
			+gridLayout->contentsMargins().right()
			+6*gridLayout->horizontalSpacing();

	cFind->installEventFilter(this);
	cReplace->installEventFilter(this);
	Q_ASSERT(cFind->completer()->popup());
	cFind->completer()->popup()->installEventFilter(this);
	cReplace->completer()->popup()->installEventFilter(this);
	//cFind->lineEdit()->installEventFilter(this);
	//cReplace->lineEdit()->installEventFilter(this);
}

/*!
	\brief Empty destructor
*/
QSearchReplacePanel::~QSearchReplacePanel()
{
	if ( m_search )
		delete m_search;
	m_search=0;
}

/*!

*/
QString QSearchReplacePanel::type() const
{
	return "Search";
}

bool QSearchReplacePanel::isReplaceModeActive() const{
	return cbReplace->isChecked();
}

QDocumentCursor QSearchReplacePanel::getSearchScope() const{
	return m_search->scope();
}

void QSearchReplacePanel::setUseLineForSearch(bool b){
	useLineForSearch = b;
}

bool QSearchReplacePanel::getUseLineForSearch() const{
	return useLineForSearch;
}

void QSearchReplacePanel::setSearchOnlyInSelection(bool b){
	searchOnlyInSelection = b;
}

bool QSearchReplacePanel::getSearchOnlyInSelection() const{
	return searchOnlyInSelection;
}


/*!
	\brief
*/
void QSearchReplacePanel::editorChange(QEditor *e)
{
	if ( editor() )
	{
		disconnect(	editor(), SIGNAL( cursorPositionChanged() ),
					this	, SLOT  ( cursorPositionChanged() ) );
	}

	if ( e )
	{
		connect(e	, SIGNAL( cursorPositionChanged() ),
				this, SLOT  ( cursorPositionChanged() ) );
	}
}

bool QSearchReplacePanel::forward(QMouseEvent *e)
{
	Q_UNUSED(e)
	
	/*
		This panel does not need mouse events to be forwarded to the editor.
		Even more, it requires them not to be forwarded...
	*/
	return false;
}

/*!

*/
void QSearchReplacePanel::display(int mode, bool replace)
{
	//qDebug("display(%i)", replace);
        if (! m_search) init();

	bool visible = true;

	if ( mode < 0 )
		visible = (replace != cbReplace->isChecked()) || isHidden();
	else
		visible = mode;

	if ( visible )
	{
		//frameReplace->setVisible(replace);
		bool focusFindEdit = true;
		if (m_search){
			if(editor()->cursor().hasSelection()){
				if(editor()->cursor().anchorLineNumber()!=editor()->cursor().lineNumber() || !useLineForSearch ||cbSelection->isChecked()){
					if (searchOnlyInSelection){
						if(cbSelection->isChecked()) on_cbSelection_toggled(true);
						else cbSelection->setChecked(true);
					}
				} if ( (cbHasFocus(cFind) || cbHasFocus(cReplace)) && visible) {
					//don't copy selection to cFind, if the panel is in use
					if ( cbHasFocus(cFind) && replace )
						focusFindEdit = false; //switch to replace edit, if the cursor is in the find edit (sideeffect: ctrl+r toggles active edit)
				} else {
					// single line selection
					// copy content to cFind (doesn't trigger textEdited; don't call textEdited to prevent cursor jumping)
					cFind->setEditText(editor()->cursor().selectedText());
					m_search->setSearchText(cFind->currentText());
				}
			} else if (useLineForSearch && !replace && !((cbHasFocus(cFind) || cbHasFocus(cReplace)) && visible)) {
				// use word under cursor if no selection is present (qt creator behavior)
				QDocumentCursor m_cursor=editor()->cursor();
				m_cursor.select(QDocumentCursor::WordUnderCursor);
				if (!m_cursor.selectedText().isEmpty()) {
					cFind->setEditText(m_cursor.selectedText());
					m_search->setSearchText(cFind->currentText());
				}
			} else if ( cbHasFocus(cFind) && replace && visible)
				focusFindEdit = false;
			if (cbHighlight->isChecked() && !m_search->hasOption(QDocumentSearch::HighlightAll))
				m_search->setOption(QDocumentSearch::HighlightAll, true);
		}
		cbReplace->setChecked(replace);
		if (focusFindEdit) {
			cFind->setFocus();
			cFind->lineEdit()->selectAll();
		} else {
			cReplace->setFocus();
			cReplace->lineEdit()->selectAll();
		}
		//show();
	}else closeEvent(0);
		
	setVisible(visible);

	if ( !visible )
		editor()->setFocus();
}

void QSearchReplacePanel::closeSomething(bool closeTogether){
	/*qDebug() << "popup"<< QApplication::activePopupWidget();
	foreach (QObject* o, cFind->children()) {
		qDebug()<<"child"<<o;
		if (qobject_cast<QWidget*>(o)) qDebug() << "   "<<(qobject_cast<QWidget*>(o))->hasFocus()<<(qobject_cast<QWidget*>(o))->isVisible();
		foreach (QObject* p, o->children()) {
			qDebug()<<"child child  "<<p;
			if (qobject_cast<QWidget*>(p)) 
				qDebug() << "   "<<(qobject_cast<QWidget*>(p))->hasFocus()
				<<(qobject_cast<QWidget*>(p))->isVisible();
			foreach (QObject* q, p->children()) {
				qDebug()<<"child child child    "<<q;
				if (qobject_cast<QWidget*>(q)) qDebug() << "   "<<(qobject_cast<QWidget*>(q))->hasFocus()<<(qobject_cast<QWidget*>(q))->isVisible();
			}
		}
	}*/
	if (cFind->completer()->popup()->isVisible() && cFind->completer()->popup()->hasFocus())
		cFind->setFocus();
	else if (cReplace->completer()->popup()->isVisible() && cReplace->completer()->popup()->hasFocus())
		cReplace->setFocus();
	else if (isReplaceModeActive() & !closeTogether)
		display(1,false);
	else
		display(0,false);	
}

void QSearchReplacePanel::findNext(){
	findReplace(m_lastDirection);
}


void QSearchReplacePanel::updateSearchOptions(bool replace, bool replaceAll){
	if ( !m_search ) init();
	if ( cbCursor->isChecked() && !m_search->cursor().isValid() )
		m_search->setCursor(editor()->cursor());  //start from current cursor if no known cursor
	if ( !cbCursor->isChecked() && replaceAll )
		m_search->setCursor(QDocumentCursor());
	if ( m_search->searchText()!=cFind->currentText() )
		m_search->setSearchText(cFind->currentText());
	if ( replace && m_search->replaceText()!=cReplace->currentText() )
		m_search->setReplaceText(cReplace->currentText());
	m_search->setOption(QDocumentSearch::Replace,replace);
}

QStringList QSearchReplacePanel::getHistory(bool rfindHistory){
	return (rfindHistory?findHistory:replaceHistory);
}

void QSearchReplacePanel::setHistory(const QStringList& newHistory, bool sfindHistory){
	QStringList& history = (sfindHistory?findHistory:replaceHistory);
	history = newHistory;
	ConfigManagerInterface::getInstance()->updateAllLinkedObjects(&history);
}

void QSearchReplacePanel::rememberLastSearch(QStringList& history, const QString& str, bool incremental){
	if (history.isEmpty()) {
		history.append(str);
		ConfigManagerInterface::getInstance()->updateAllLinkedObjects(&history);
		return;
	}
	if (!incremental && !history.contains(str)) {
		history.append(str);
		ConfigManagerInterface::getInstance()->updateAllLinkedObjects(&history);
	}
}
	
void QSearchReplacePanel::findReplace(bool backward, bool replace, bool replaceAll, bool countOnly)
{
	Q_ASSERT(!(replace && countOnly));
	Q_ASSERT(!(replaceAll && !replace));

	if ( !m_search  && !isVisible() ) {
		display(1, false);
		return;
	}

	updateSearchOptions(replace,replaceAll);;
	m_lastDirection=backward;

	if (!countOnly)  m_search->next(backward, replaceAll, !cbPrompt->isChecked(), true);
	else {
		m_search->setOption(QDocumentSearch::Silent, true);
		QDocumentCursor startCur = m_search->cursor();
		int question = QMessageBox::Yes;
		if (startCur.isValid() && cbCursor->isChecked() &&
		    ((startCur.selectionStart() > m_search->scope().selectionStart() && startCur.selectionEnd() < m_search->scope().selectionEnd()) || !m_search->scope().isValid())) {
			m_search->setCursor(m_search->cursor().selectionEnd());
			int count = m_search->next(false, true, true, false);
			question = QMessageBox::information(this,tr("Count result"),tr("The search text occurs %1 times after the current cursor. Do you want to restart from the beginning of the scope?").arg(count),QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}
		if (question == QMessageBox::Yes) {
			m_search->setCursor(QDocumentCursor());
			int count = m_search->next(false, true, true, false);
			QMessageBox::information(this,tr("Count result"),tr("The search text occurs %1 times within the search scope.").arg(count),QMessageBox::Ok);
		}
		m_search->setCursor(startCur);
		m_search->setOption(QDocumentSearch::Silent, false);
	}
	rememberLastSearch(findHistory,cFind->currentText(),m_search->options() & QDocumentSearch::Silent);
	rememberLastSearch(replaceHistory,cReplace->currentText(),m_search->options() & QDocumentSearch::Silent);
	if (isVisible() && !cbHasFocus(cFind) && !cbHasFocus(cReplace) ) {
		if (replace) cReplace->setFocus();
		else cFind->setFocus();
	}
}

void QSearchReplacePanel::find(QString text, bool backward, bool highlight, bool regex, bool word, bool caseSensitive, bool fromCursor, bool selection){
    cbSelection->setChecked(selection);
    cbCursor->setChecked(fromCursor);
    find(text, backward, highlight, regex, word, caseSensitive);
}

void QSearchReplacePanel::selectAllMatches(){
	if (!editor()) return;
	updateSearchOptions(false,false);
	m_search->setOption(QDocumentSearch::Silent, true); //don't forget
	QDocumentCursor startCur = m_search->cursor();
	m_search->setCursor(QDocumentCursor());

	editor()->setCursor(QDocumentCursor());
	QDocumentCursor last = QDocumentCursor();
	int count = 0;
	while (m_search->next(false, false, false, false) && m_search->cursor().isValid()) {
		if (!count) editor()->setCursor(m_search->cursor());
		else if (last < m_search->cursor()) editor()->addCursorMirror(m_search->cursor());
		else break;
		last = m_search->cursor();
		count++;
	}

	m_search->setCursor(startCur);
	m_search->setOption(QDocumentSearch::Silent, false);

	if (count) editor()->setFocus();
	else if (!isVisible()) display(1,false);
}

void QSearchReplacePanel::find(QString text, bool backward, bool highlight, bool regex, bool word, bool caseSensitive){
	if (!isVisible()) display(1,false);
	if (m_search && m_search->searchText()!=text) {
		delete m_search;
		m_search=0;
	}
	//if (!m_search) editor()->setCursorPosition(0,0); ??
	if(!m_search) init();
	cFind->setEditText(text);
	cbHighlight->setChecked(highlight);
	cbRegExp->setChecked(regex);
	cbCase->setChecked(caseSensitive);
	cbWords->setChecked(word);
	findReplace(backward);
}
void QSearchReplacePanel::setOptions(int searchOptions, bool cursor, bool selection){
	cbRegExp->setChecked(searchOptions & QDocumentSearch::RegExp);
	cbCase->setChecked(searchOptions &QDocumentSearch::CaseSensitive);
	cbWords->setChecked(searchOptions &QDocumentSearch::WholeWords);
	cbHighlight->setChecked(searchOptions &QDocumentSearch::HighlightAll);
	cbReplace->setChecked(searchOptions & QDocumentSearch::Replace);
	cbPrompt->setChecked(searchOptions & QDocumentSearch::Prompt);
	cbEscapeSeq->setChecked(searchOptions & QDocumentSearch::EscapeSeq);
	cbCursor->setChecked(cursor);
	cbSelection->setChecked(selection);
}
/*!

*/
void QSearchReplacePanel::hideEvent(QHideEvent *)
{
}

void QSearchReplacePanel::closeEvent(QCloseEvent *)
{
	//beware: the CloseEvent could be 0
	
	if ( m_search )
	{
		if (isVisible() && editor() && m_search->lastReplacedPosition().isValid()) {
			editor()->setCursor(m_search->lastReplacedPosition(), false);
			editor()->ensureCursorVisible(QEditor::Navigation);
		}
		//m_search->highlightSelection(false);
		m_search->setOption(QDocumentSearch::HighlightAll, false);
		//reset search scope
		m_search->setScope(QDocumentCursor());
		if (!cbCursor->isChecked())
			m_search->setCursor(QDocumentCursor());
		emit onClose();
		//delete m_search;
		//m_search=0;
	}
}


void QSearchReplacePanel::resizeEvent(QResizeEvent *e){

	int w=e->size().width() - layoutFindOptions->contentsMargins().left() - layoutFindOptions->contentsMargins().right();
	w=w-minimum_width; // remaining space
	QList<QWidget*> listOfWidget;
	// search
	listOfWidget << cbCase << cbWords << cbRegExp << cbHighlight << cbCursor << cbSelection;
	int row=0;
	int col=0;
	int remaining_space=w;
	int spacing=layoutFindOptions->horizontalSpacing();
	foreach(QWidget *wdg,listOfWidget){
		remaining_space -= wdg->minimumWidth();
		if(remaining_space>0){
			layoutFindOptions->addWidget(wdg, row, col, 1, 1);
			remaining_space -= spacing;
			col++;
		}else{
			col=0;
			row++;
			layoutFindOptions->addWidget(wdg, row, col, 1, 1);
			col++;
			remaining_space=w-wdg->minimumWidth();
		}
	}
	// replace
	listOfWidget.clear();
	listOfWidget << cbPrompt << cbEscapeSeq;
	row=0;
	col=0;
	remaining_space=w;
	spacing=layoutReplaceOptions->horizontalSpacing();
	foreach(QWidget *wdg,listOfWidget){
		remaining_space -= wdg->minimumWidth();
		if(remaining_space>0){
			layoutReplaceOptions->addWidget(wdg, row, col, 1, 1);
			remaining_space -= spacing;
			col++;
		}else{
			col=0;
			row++;
			layoutReplaceOptions->addWidget(wdg, row, col, 1, 1);
			col++;
			remaining_space=w-wdg->minimumWidth();
		}
	}
	QPanel::resizeEvent(e);
}


bool QSearchReplacePanel::eventFilter(QObject *o, QEvent *e)
{
//	if (e->type() == QEvent::KeyPress)
//		qDebug() << QDateTime::currentDateTime() << "eventfilter:" << o << (o?o->objectName():"..") << " vs. " << cFind->completer()->popup();
	if ( o == cFind || o == cReplace )
	{
		int kc;
		switch ( e->type() )
		{
			/*
			case QEvent::FocusIn :
				cFind->grabKeyboard();
                                break;*/

		/*	case QEvent::FocusOut :
				e->setAccepted(true);
				return true;
				//cFind->releaseKeyboard();
				//break;
			*/

			case QEvent::KeyPress :

				kc = static_cast<QKeyEvent*>(e)->key();
				if ( ( (kc == Qt::Key_Enter) || (kc == Qt::Key_Return) ) )
				{
					//on_cFind_returnPressed();
					if (cbHasFocus(cReplace)) 
						on_cReplace_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
					else
						on_cFind_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
					return true;
				} else if ( kc == Qt::Key_Escape) {
					if ( cbReplace->isChecked() )
						display(0,false);
					else
						display(0,false);
					return true;
				} else if ( kc == Qt::Key_Tab || kc == Qt::Key_Backtab ) {
					if ( cbReplace->isChecked() )
					{
						if ( cbHasFocus(cFind) )
							cReplace->setFocus();
						else
							cFind->setFocus();
					}
					return true;
				}
				break;

			default:
				break;
		}
	} else if ( o == cFind->completer()->popup() || o == cReplace->completer()->popup() ) {
		int kc;
		switch ( e->type() )
		{
		case QEvent::KeyPress :

			kc = static_cast<QKeyEvent*>(e)->key();
			if ( (kc == Qt::Key_Enter) || (kc == Qt::Key_Return) )
			{
				//on_cFind_returnPressed();
				if (cbHasFocus(cReplace)) 
					on_cReplace_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
				else
					on_cFind_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
				return true;
			} else if ( kc == Qt::Key_Tab || kc == Qt::Key_Backtab ) {
				qobject_cast<QWidget*>(o)->hide();
				if ( cbReplace->isChecked() )
				{
					if ( cbHasFocus(cFind) )
						cReplace->setFocus();
					else
						cFind->setFocus();
				}
				return true;
			} else if ( static_cast<QKeyEvent*>(e)->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier)) {
				qobject_cast<QWidget*>(o)->hide(); //keep shortcuts working with active popup completer
			}
			break;
		default:;
		}
	}

	return QWidget::eventFilter(o, e);
}

void QSearchReplacePanel::cFind_textEdited(const QString& text)
{ 
	if (! m_search) init();
	
	m_search->setSearchText(text);
	
	if ( text.isEmpty() )
	{
		cFind->lineEdit()->setStyleSheet(QString());
		return;
	}

	QDocumentCursor cur = editor()->cursor();

	if (m_search->cursor().isValid()){
		cur = m_search->cursor();
		m_search->setCursor(m_search->cursor().selectionStart());
	}
	
	m_search->setOption(QDocumentSearch::Silent,true);
	
	findReplace(false);
	
	m_search->setOption(QDocumentSearch::Silent,false);	
	
	if ( m_search->cursor().isNull() )
		cFind->lineEdit()->setStyleSheet("QLineEdit { background: red; color : white; }");
	else if ((m_search->cursor().anchorLineNumber() < cur.anchorLineNumber()) || 
			(m_search->cursor().anchorLineNumber() == cur.anchorLineNumber() && m_search->cursor().anchorColumnNumber()<cur.anchorColumnNumber())) {
		cFind->lineEdit()->setStyleSheet("QLineEdit { background: yellow; color : black; }");
		editor()->setCursor(m_search->cursor());
	} else {
		cFind->lineEdit()->setStyleSheet(QString());
		editor()->setCursor(m_search->cursor());
	}
}

void QSearchReplacePanel::on_cFind_returnPressed(bool backward)
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(backward);

}
void QSearchReplacePanel::on_cReplace_returnPressed(bool backward){
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(backward,true);
}

void QSearchReplacePanel::cReplace_textEdited(const QString& text)
{
	if ( m_search )
		m_search->setReplaceText(text);

}

void QSearchReplacePanel::on_cbPrompt_toggled(bool on){
	if ( m_search )
		m_search->setOption(QDocumentSearch::Prompt, on);
	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbReplace_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::Replace, on);

	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbWords_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::WholeWords, on);
	if (on && cbRegExp->isChecked()) 
		cbRegExp->setChecked(false); //word and regexp is not possible
	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbRegExp_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::RegExp, on);
	if (on && cbWords->isChecked()) 
		cbWords->setChecked(false); //word and regexp is not possible
	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbCase_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::CaseSensitive, on);

	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbCursor_toggled(bool on)
{
	if ( m_search )
	{
		if ( on && !cbSelection->isChecked())
			m_search->setCursor(editor()->cursor());
		else
			m_search->setCursor(QDocumentCursor());
	}

	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbHighlight_toggled(bool on)
{
	if ( !m_search )
		init();

	if ( m_search )
	{
		m_search->setOption(QDocumentSearch::HighlightAll, on);
	}

	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_cbSelection_toggled(bool on)
{
	if ( m_search ) {
		m_search->setScope(on ? editor()->cursor() : QDocumentCursor());
		/*if ( m_search && cbHighlight->isChecked())
		{
			m_search->setOption(QDocumentSearch::HighlightAll, false);
			m_search->setOption(QDocumentSearch::HighlightAll, true);
		}*/
	}
	cFind->setFocus();
}

void QSearchReplacePanel::on_cbEscapeSeq_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::EscapeSeq, on);

	if ( cFind->isVisible() )
		cFind->setFocus();
}

void QSearchReplacePanel::on_bNext_clicked()
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(false);
}

void QSearchReplacePanel::on_bPrevious_clicked()
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(true);
}

void QSearchReplacePanel::on_bCount_clicked()
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(false, false, false, true);
}

void QSearchReplacePanel::on_bReplaceNext_clicked()
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(false,true);
}
void QSearchReplacePanel::on_bReplacePrevious_clicked()
{
	cFind->lineEdit()->setStyleSheet(QString());
	findReplace(true,true);
}

void QSearchReplacePanel::on_bReplaceAll_clicked()
{
	 cFind->lineEdit()->setStyleSheet(QString());
	 findReplace(false,true,true);
}

void QSearchReplacePanel::init()
{
	if ( m_search )
	{
		delete m_search;
		m_search = 0;
	}

	QDocumentSearch::Options opt;

	if ( cbRegExp->isChecked() )
		opt |= QDocumentSearch::RegExp;

	if ( cbCase->isChecked() )
		opt |= QDocumentSearch::CaseSensitive;

	if ( cbWords->isChecked() )
		opt |= QDocumentSearch::WholeWords;

	if ( cbHighlight->isChecked())
		opt |= QDocumentSearch::HighlightAll;

	if ( cbReplace->isChecked())
		opt |= QDocumentSearch::Replace;

	if ( cbPrompt->isChecked() )
        	opt |= QDocumentSearch::Prompt;

	if ( cbEscapeSeq->isChecked() )
        	opt |= QDocumentSearch::EscapeSeq;
	
	m_search = new QDocumentSearch(	editor(),
									cFind->currentText(),
									opt,
									cbReplace->isChecked()
										?
											cReplace->currentText()
										:
											QString()
									);


	if ( cbSelection->isChecked() && editor()->cursor().hasSelection()){
		m_search->setScope(editor()->cursor());
	} else if ( cbCursor->isChecked() )
		m_search->setCursor(editor()->cursor());



}

void QSearchReplacePanel::cursorPositionChanged()
{
	if ( m_search )
	{
		if ( editor()->cursor() == m_search->cursor() )
			return;

		if ( cbSelection->isChecked() && editor()->cursor().hasSelection() && isVisible()){
			m_search->setScope(editor()->cursor());
		} /*else {
			if ( cbCursor->isChecked() )
				m_search->setCursor(editor()->cursor());
		}*/
		if ( cbCursor->isChecked() )
				m_search->setCursor(editor()->cursor());
	}
}

/*! @} */
