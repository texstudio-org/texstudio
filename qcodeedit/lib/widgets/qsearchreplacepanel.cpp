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

#include "configmanagerinterface.h"

/*!
	\ingroup widgets
	@{
*/

/*!
	\class QSearchReplacePanel
	\brief A panel that provide inline search/replace functionalities
*/

QCE_AUTO_REGISTER(QSearchReplacePanel)

/*!
	\brief Constructor
*/
QSearchReplacePanel::QSearchReplacePanel(QWidget *p)
 : QPanel(p),m_search(0),m_lastDirection(false)
{
	ConfigManagerInterface* conf = ConfigManagerInterface::getInstance();
	//setupUi(this);
	// do it completely programatic
	this->resize(801, 71);
	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setContentsMargins(-1, 4, -1, 4);
	QFrame* frame_2 = new QFrame(this);
	frame_2->setObjectName(("frame_2"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	frame_2->setSizePolicy(sizePolicy1);
	frame_2->setMinimumSize(QSize(0, 22));
	frame_2->setFrameShape(QFrame::NoFrame);
	frame_2->setLineWidth(0);
	QHBoxLayout* hboxLayout = new QHBoxLayout(frame_2);
	hboxLayout->setObjectName(("hboxLayout"));
	hboxLayout->setContentsMargins(-1, 0, -1, 0);

	QSize buttonSize(22,22);

	bClose = new QToolButton(frame_2);
	bClose->setObjectName(("bClose"));
	bClose->setMinimumSize(buttonSize);
	bClose->setMaximumSize(buttonSize);
	bClose->setIcon(QIcon(":/closeall.png"));

	hboxLayout->addWidget(bClose);

	QLabel* label = new QLabel(frame_2);
	label->setObjectName(("label"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(sizePolicy3);
	label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

	hboxLayout->addWidget(label);


	gridLayout->addWidget(frame_2, 0, 0, 1, 1);

	leFind = new QLineEdit(this);
	leFind->setObjectName(("leFind"));
	QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy4.setHorizontalStretch(2);
	leFind->setSizePolicy(sizePolicy4);
	leFind->setMinimumSize(QSize(120, 22));

	gridLayout->addWidget(leFind, 0, 1, 1, 1);

	bNext = new QToolButton(this);
	bNext->setObjectName(("bNext"));
	bNext->setMinimumSize(buttonSize);
	bNext->setMaximumSize(buttonSize);
	bNext->setIcon(QIcon(":/down.png"));

	gridLayout->addWidget(bNext, 0, 3, 1, 1);

	bPrevious = new QToolButton(this);
	bPrevious->setObjectName(("bPrevious"));
	bPrevious->setMinimumSize(buttonSize);
	bPrevious->setMaximumSize(buttonSize);
	bPrevious->setIcon(QIcon(":/up.png"));

	gridLayout->addWidget(bPrevious, 0, 4, 1, 1);

	bCount = new QToolButton(this);
	bCount->setObjectName(("bCount"));
	bCount->setMinimumSize(buttonSize);
	bCount->setMaximumSize(buttonSize);
	bCount->setIcon(QIcon(":/images/qcodeedit/count.png"));

	gridLayout->addWidget(bCount, 0, 5, 1, 1);

	QFrame* frame_6 = new QFrame(this);
	sizePolicy1.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
	frame_6->setSizePolicy(sizePolicy1);
	frame_6->setFrameShape(QFrame::NoFrame);
	gridLayout1 = new QGridLayout(frame_6);
	gridLayout1->setContentsMargins(0, 0, 0, 0);
	cbCase = new QCheckBox(frame_6);
	cbCase->setObjectName(("cbCase"));
	cbCase->setToolTip(tr("Enables case sensitive search."));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, caseConfig, true, "Search/Case Sensitive", cbCase);

	gridLayout1->addWidget(cbCase, 0, 0, 1, 1);

	cbWords = new QCheckBox(frame_6);
	cbWords->setToolTip(tr("Only searches for whole words."));
	cbWords->setObjectName(("cbWords"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, wordConfig, false, "Search/Whole Words", cbWords);

	gridLayout1->addWidget(cbWords, 0, 1, 1, 1);

	cbRegExp = new QCheckBox(frame_6);
	cbRegExp->setToolTip(tr("This interprets the search text as a regular expression.\nSome common regexps:\n r* will find any amount of r, r+ is equal to rr*, a? will matches a or nothing,\n () groups expressions together, [xyz] will find x,y, or z, . matches everything, \\. matches .\nYou can use \\1 to \\9 in the replace text to insert a submatch."));
	cbRegExp->setObjectName(("cbRegExp"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, regexConfig, false, "Search/Regular Expression", cbRegExp);

	gridLayout1->addWidget(cbRegExp, 0, 2, 1, 1);

	cbHighlight = new QCheckBox(frame_6);
	cbHighlight->setObjectName(("cbHighlight"));
	cbHighlight->setToolTip(tr("Highlights search matches and replaced text."));
	sizePolicy3.setHeightForWidth(cbHighlight->sizePolicy().hasHeightForWidth());
	cbHighlight->setSizePolicy(sizePolicy3);
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, highlightConfig, true, "Search/Highlight", cbHighlight);

	gridLayout1->addWidget(cbHighlight, 0, 3, 1, 1);

	cbCursor = new QCheckBox(frame_6);
	cbCursor->setToolTip(tr("Starts the search from the current cursor position."));
	cbCursor->setObjectName(("cbCursor"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, cursorConfig, true, "Search/Cursor", cbCursor);

	gridLayout1->addWidget(cbCursor, 0, 4, 1, 1);

	cbSelection = new QCheckBox(frame_6);
	cbSelection->setToolTip(tr("Only searches in the selected text."));
	cbSelection->setObjectName(("cbSelection"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, selectionConfig, false, "Search/Selection", cbSelection);

	gridLayout1->addWidget(cbSelection, 0, 5, 1, 1);


	gridLayout->addWidget(frame_6, 0, 6, 2, 2,Qt::AlignTop);

	bReplaceAll = new QToolButton(this);
	bReplaceAll->setObjectName(("bReplaceAll"));
	bReplaceAll->setMinimumSize(buttonSize);
	bReplaceAll->setMaximumSize(buttonSize);
	bReplaceAll->setIcon(QIcon(":/images/qcodeedit/replaceall.png"));

	gridLayout->addWidget(bReplaceAll, 2, 5, 1, 1);

	QFrame* frame = new QFrame(this);
	frame->setObjectName(("frame"));
	frame->setFrameShape(QFrame::NoFrame);
	frame->setFrameShadow(QFrame::Raised);
	QHBoxLayout* hboxLayout1 = new QHBoxLayout(frame);
	hboxLayout1->setContentsMargins(-1, 0, -1, 0);
	cbPrompt = new QCheckBox(frame);
	cbPrompt->setToolTip(tr("Ask before any match is replaced."));
	cbPrompt->setObjectName(("cbPrompt"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, askConfig, false, "Search/Ask before Replace", cbPrompt);

	hboxLayout1->addWidget(cbPrompt);

	//cbReplaceAll = new QCheckBox(frame);
	//cbReplaceAll->setObjectName(("cbReplaceAll"));

	//hboxLayout1->addWidget(cbReplaceAll);

	cbEscapeSeq = new QCheckBox(frame);
	cbEscapeSeq->setToolTip(tr("Enables the use of escape characters. These are:\n \\n = new line, \\r = carriage return, \\t = tab, \\\\ = \\, \\0 = ascii 0 "));
	cbEscapeSeq->setObjectName(("cbEscapeSeq"));
	CONFIG_DECLARE_OPTION_WITH_OBJECT(conf, bool, escapeConfig, false, "Search/Escape Sequence", cbEscapeSeq);

	hboxLayout1->addWidget(cbEscapeSeq);


	gridLayout->addWidget(frame, 2, 6, 1, 1);

	cbReplace = new QCheckBox(this);
	cbReplace->setObjectName(("cbReplace"));
	cbReplace->setChecked(true);

	gridLayout->addWidget(cbReplace, 2, 0, 1, 1);

	leReplace = new QLineEdit(this);
	leReplace->setObjectName(("leReplace"));
	leReplace->setEnabled(true);
	QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Fixed);
	sizePolicy7.setHorizontalStretch(2);
	sizePolicy7.setVerticalStretch(0);
	sizePolicy7.setHeightForWidth(leReplace->sizePolicy().hasHeightForWidth());
	leReplace->setSizePolicy(sizePolicy7);
	leReplace->setMinimumSize(QSize(120, 22));
	leReplace->setMaximumSize(QSize(1200, 16777215));

	gridLayout->addWidget(leReplace, 2, 1, 1, 1);

	bReplaceNext = new QToolButton(this);
	bReplaceNext->setObjectName(("bReplaceNext"));
	bReplaceNext->setMinimumSize(buttonSize);
	bReplaceNext->setMaximumSize(buttonSize);
	bReplaceNext->setIcon(QIcon(":/images/qcodeedit/replacedown.png"));

	gridLayout->addWidget(bReplaceNext, 2, 3, 1, 1);

	bReplacePrevious = new QToolButton(this);
	bReplacePrevious->setObjectName(("bReplacePrevious"));
	bReplacePrevious->setMinimumSize(buttonSize);
	bReplacePrevious->setMaximumSize(buttonSize);
	bReplacePrevious->setIcon(QIcon(":/images/qcodeedit/replaceup.png"));

	gridLayout->addWidget(bReplacePrevious, 2, 4, 1, 1);


	//retranslateUi(this);
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), cbReplace, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), leReplace, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplacePrevious, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceNext, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), frame, SLOT(setVisible(bool)));
	QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceAll, SLOT(setVisible(bool)));
	QObject::connect(bClose, SIGNAL(clicked()), this, SLOT(close()));

	// connect by name
	QMetaObject::connectSlotsByName(this);

	// set texts
	bClose->setToolTip(QApplication::translate("SearchReplace", "Close search/replace panel", 0, QApplication::UnicodeUTF8));
	leFind->setToolTip(QApplication::translate("SearchReplace", "Text or pattern to search for", 0, QApplication::UnicodeUTF8));
	bNext->setToolTip(QApplication::translate("SearchReplace", "Find next occurence", 0, QApplication::UnicodeUTF8));
	bPrevious->setToolTip(QApplication::translate("SearchReplace", "Find previous occurence", 0, QApplication::UnicodeUTF8));
	leReplace->setToolTip(QApplication::translate("SearchReplace", "Replacement text", 0, QApplication::UnicodeUTF8));
	bReplaceNext->setToolTip(QApplication::translate("SearchReplace", "Find next occurence", 0, QApplication::UnicodeUTF8));
	bReplacePrevious->setToolTip(QApplication::translate("SearchReplace", "Find previous occurence", 0, QApplication::UnicodeUTF8));
	bReplaceAll->setToolTip(QApplication::translate("SearchReplace", "Replace all", 0, QApplication::UnicodeUTF8));
	bCount->setToolTip(QApplication::translate("SearchReplace", "Count occurences", 0, QApplication::UnicodeUTF8));

	label->setText(QApplication::translate("SearchReplace", " Find :", 0, QApplication::UnicodeUTF8));
	label->setMinimumWidth(label->sizeHint().width());
	cbCase->setText(QApplication::translate("SearchReplace", "Case", 0, QApplication::UnicodeUTF8));
	cbCase->setMinimumWidth(cbCase->sizeHint().width());
	cbWords->setText(QApplication::translate("SearchReplace", "Words", 0, QApplication::UnicodeUTF8));
	cbWords->setMinimumWidth(cbWords->sizeHint().width());
	cbRegExp->setText(QApplication::translate("SearchReplace", "Regexp", 0, QApplication::UnicodeUTF8));
	cbRegExp->setMinimumWidth(cbRegExp->sizeHint().width());
	cbHighlight->setText(QApplication::translate("SearchReplace", "Highlight all", 0, QApplication::UnicodeUTF8));
	cbHighlight->setMinimumWidth(cbHighlight->sizeHint().width());
	cbCursor->setText(QApplication::translate("SearchReplace", "Cursor", 0, QApplication::UnicodeUTF8));
	cbCursor->setMinimumWidth(cbCursor->sizeHint().width());
	cbSelection->setText(QApplication::translate("SearchReplace", "Selection", 0, QApplication::UnicodeUTF8));
	cbSelection->setMinimumWidth(cbSelection->sizeHint().width());
	//bReplaceAll->setText(QApplication::translate("SearchReplace", "all", 0, QApplication::UnicodeUTF8));
	cbPrompt->setText(QApplication::translate("SearchReplace", "Prompt on replace", 0, QApplication::UnicodeUTF8));
	cbEscapeSeq->setText(QApplication::translate("SearchReplace", "Escape sequences", 0, QApplication::UnicodeUTF8));
	cbReplace->setText(QApplication::translate("SearchReplace", "Replace :", 0, QApplication::UnicodeUTF8));
	//cbReplaceAll->setText(QApplication::translate("SearchReplace", "Replace all", 0, QApplication::UnicodeUTF8));

	minimum_width=frame_2->sizeHint().width()+leFind->sizeHint().width()+2*bNext->sizeHint().width()+5*hboxLayout->spacing();
	//

	leFind->installEventFilter(this);
	leReplace->installEventFilter(this);
	
	//cbReplaceAll->setVisible(false);

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
				if(editor()->cursor().anchorLineNumber()!=editor()->cursor().lineNumber() || !editor()->UseLineForSearch() ||cbSelection->isChecked()){
					if(cbSelection->isChecked()) on_cbSelection_toggled(true);
					else cbSelection->setChecked(true);
				} if ( (leFind->hasFocus() || leReplace->hasFocus()) && visible) {
					//don't copy selection to leFind, if the panel is in use
					if ( leFind->hasFocus() && replace )
						focusFindEdit = false; //switch to replace edit, if the cursor is in the find edit (sideeffect: ctrl+r toggles active edit)
				} else {
					// single line selection
					// copy content to leFind
					leFind->setText(editor()->cursor().selectedText());
				}
			}
			if (cbHighlight->isChecked() && !m_search->hasOption(QDocumentSearch::HighlightAll))
				m_search->setOption(QDocumentSearch::HighlightAll, true);
		}
		cbReplace->setChecked(replace);
		if (focusFindEdit) {
			leFind->setFocus();
			leFind->selectAll();
		} else {
			leReplace->setFocus();
			leReplace->selectAll();
		}
		//show();
	}else closeEvent(0);

	setVisible(visible);

	if ( !visible )
		editor()->setFocus();
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
	if ( m_search->searchText()!=leFind->text() )
		m_search->setSearchText(leFind->text());
	if ( replace && m_search->replaceText()!=leReplace->text() )
		m_search->setReplaceText(leReplace->text());
	m_search->setOption(QDocumentSearch::Replace,replace);
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
        if (isVisible() && !leFind->hasFocus() && !leReplace->hasFocus() ) {
		if (replace) leReplace->setFocus();
		else leFind->setFocus();
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
	leFind->setText(text);
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
	int w=e->size().width();
	w=w-minimum_width; // remaining space
	QList<QWidget*> listOfWidget;
	listOfWidget << cbCase << cbWords << cbRegExp << cbHighlight << cbCursor << cbSelection;
	int row=0;
	int col=0;
	int remaining_space=w;
	foreach(QWidget *wdg,listOfWidget){
		remaining_space=remaining_space-wdg->minimumWidth();
		if(remaining_space>0){
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
		}else{
			col=0;
			row++;
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
			remaining_space=w-wdg->minimumWidth();
		}
	}
	QPanel::resizeEvent(e);
}


bool QSearchReplacePanel::eventFilter(QObject *o, QEvent *e)
{

	if ( o == leFind || o == leReplace )
	{
		int kc;
		switch ( e->type() )
		{
			/*
			case QEvent::FocusIn :
				leFind->grabKeyboard();
				break;

			case QEvent::FocusOut :
				leFind->releaseKeyboard();
				break;
				*/

			case QEvent::KeyPress :

				kc = static_cast<QKeyEvent*>(e)->key();

				if ( (kc == Qt::Key_Enter) || (kc == Qt::Key_Return) )
				{
					//on_leFind_returnPressed();
					if (leReplace->hasFocus()) 
						on_leReplace_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
					else
						on_leFind_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
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
						if ( leFind->hasFocus() )
							leReplace->setFocus();
						else
							leFind->setFocus();
					}
					return true;
				}
				break;

			default:
				break;
		}
	}

	return QWidget::eventFilter(o, e);
}

void QSearchReplacePanel::on_leFind_textEdited(const QString& text)
{
	if (! m_search) init();
	
	m_search->setSearchText(text);
	
	if ( text.isEmpty() )
	{
		leFind->setStyleSheet(QString());
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
		leFind->setStyleSheet("QLineEdit { background: red; color : white; }");
	else if ((m_search->cursor().anchorLineNumber() < cur.anchorLineNumber()) || 
			(m_search->cursor().anchorLineNumber() == cur.anchorLineNumber() && m_search->cursor().anchorColumnNumber()<cur.anchorColumnNumber())) {
		leFind->setStyleSheet("QLineEdit { background: yellow; color : black; }");
		editor()->setCursor(m_search->cursor());
	} else {
		leFind->setStyleSheet(QString());
		editor()->setCursor(m_search->cursor());
	}
}

void QSearchReplacePanel::on_leFind_returnPressed(bool backward)
{
	leFind->setStyleSheet(QString());
	findReplace(backward);

}
void QSearchReplacePanel::on_leReplace_returnPressed(bool backward){
	leFind->setStyleSheet(QString());
	findReplace(backward,true);
}

void QSearchReplacePanel::on_leReplace_textEdited(const QString& text)
{
	if ( m_search )
		m_search->setReplaceText(text);

}

void QSearchReplacePanel::on_cbPrompt_toggled(bool on){
	if ( m_search )
		m_search->setOption(QDocumentSearch::Prompt, on);
	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_cbReplace_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::Replace, on);

	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_cbWords_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::WholeWords, on);
	if (on && cbRegExp->isChecked()) 
		cbRegExp->setChecked(false); //word and regexp is not possible
	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_cbRegExp_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::RegExp, on);
	if (on && cbWords->isChecked()) 
		cbWords->setChecked(false); //word and regexp is not possible
	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_cbCase_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::CaseSensitive, on);

	if ( leFind->isVisible() )
		leFind->setFocus();
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

	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_cbHighlight_toggled(bool on)
{
	if ( !m_search )
		init();

	if ( m_search )
	{
		m_search->setOption(QDocumentSearch::HighlightAll, on);
	}

	if ( leFind->isVisible() )
		leFind->setFocus();
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
	leFind->setFocus();
}

void QSearchReplacePanel::on_cbEscapeSeq_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::EscapeSeq, on);

	if ( leFind->isVisible() )
		leFind->setFocus();
}

void QSearchReplacePanel::on_bNext_clicked()
{
	leFind->setStyleSheet(QString());
	findReplace(false);
}

void QSearchReplacePanel::on_bPrevious_clicked()
{
	leFind->setStyleSheet(QString());
	findReplace(true);
}

void QSearchReplacePanel::on_bCount_clicked()
{
	leFind->setStyleSheet(QString());
	findReplace(false, false, false, true);
}

void QSearchReplacePanel::on_bReplaceNext_clicked()
{
	leFind->setStyleSheet(QString());
	findReplace(false,true);
}
void QSearchReplacePanel::on_bReplacePrevious_clicked()
{
	leFind->setStyleSheet(QString());
	findReplace(true,true);
}

void QSearchReplacePanel::on_bReplaceAll_clicked()
{
	 leFind->setStyleSheet(QString());
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
									leFind->text(),
									opt,
									cbReplace->isChecked()
										?
											leReplace->text()
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
