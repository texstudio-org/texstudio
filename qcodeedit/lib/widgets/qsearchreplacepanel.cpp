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
 : QPanel(p),m_search(0),m_lastDirection(false),m_group(-1)
{
	setupUi(this);
	setDefaultVisibility(false);

	cbCase->setChecked(false);

	leFind->installEventFilter(this);
	leReplace->installEventFilter(this);
	
	cbReplaceAll->setVisible(false);
}

/*!
	\brief Empty destructor
*/
QSearchReplacePanel::~QSearchReplacePanel()
{
	if ( m_search )
		delete m_search;
	if(m_group>-1 && editor() && editor()->document()){
		editor()->document()->clearMatches(m_group);
		editor()->document()->flushMatches(m_group);
		m_group = -1;
	}
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
		cbReplace->setChecked(replace);
		//frameReplace->setVisible(replace);
		leFind->setFocus();

                if (m_search){
                    if(editor()->cursor().hasSelection()){
						if(editor()->cursor().anchorLineNumber()!=editor()->cursor().lineNumber() || !editor()->UseLineForSearch() ||cbSelection->isChecked()){
							if(cbSelection->isChecked()){
								highlightSelection(false);
								highlightSelection(true);
							} else cbSelection->setChecked(true);
                        }else{
                            // single line selection
                            // copy content to leFind
                            leFind->setText(editor()->cursor().selectedText());
                        }
                    }
                    if (cbHighlight->isChecked() && !m_search->hasOption(QDocumentSearch::HighlightAll))
                        m_search->setOption(QDocumentSearch::HighlightAll, true);
                }
                leFind->selectAll();
		//show();
	}else{
		if ( m_search )
		{
			m_search->setOption(QDocumentSearch::HighlightAll, false);
			//m_search->clearMatches();
		}
	}

	setVisible(visible);

	if ( !visible )
		editor()->setFocus();
}

void QSearchReplacePanel::findNext(){
	findReplace(m_lastDirection);
}

/*!

*/
void QSearchReplacePanel::findReplace(bool backward, bool replace, bool replaceAll)
{
	if ( !m_search )
	{
		if ( !isVisible() )
		{
			display(1, false);
			return;
		} else {
			init();
		}
	}
	m_lastDirection=backward;
	/*if (replaceAll)
		m_search->setCursor(QDocumentCursor());
	else */if (cbCursor->isChecked() && !m_search->cursor().isValid())
		m_search->setCursor(editor()->cursor());  //start from current cursor if no known cursor
	if (m_search->searchText()!=leFind->text())
		m_search->setSearchText(leFind->text());
	if (replace && m_search->replaceText()!=leReplace->text())
		m_search->setReplaceText(leReplace->text());
	m_search->setOption(QDocumentSearch::Replace,replace);
	m_search->next(backward, replaceAll, !cbPrompt->isChecked(), true);
	if (isVisible() && !leFind->hasFocus() && !leReplace->hasFocus() )
		if (replace) leReplace->setFocus();
		else leFind->setFocus();
}

void QSearchReplacePanel::find(QString text, bool backward, bool highlight, bool regex){
    if (!isVisible()) display(1,false);
    if (m_search && m_search->searchText()!=text) {
        delete m_search;
        m_search=0;
    }
    if (!m_search) editor()->setCursorPosition(0,0);
    leFind->setText(text);
    cbHighlight->setChecked(highlight);
    cbRegExp->setChecked(regex);
	cbCase->setChecked(false);
	cbSelection->setChecked(false);
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
	highlightSelection(false);
}

bool QSearchReplacePanel::eventFilter(QObject *o, QEvent *e)
{
	int kc;

	if ( o == leFind || o == leReplace )
	{
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
			m_search->setOrigin(editor()->cursor());
		else
			m_search->setOrigin(QDocumentCursor());
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
		m_search->setOrigin(QDocumentCursor());
		m_search->setScope(on ? editor()->cursor() : QDocumentCursor());
		highlightSelection(on);
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

void QSearchReplacePanel::on_bRefresh_clicked()
{
	init();
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
		m_search->setOrigin(QDocumentCursor());
		highlightSelection();
	} else if ( cbCursor->isChecked() )
		m_search->setCursor(editor()->cursor());



}

void QSearchReplacePanel::cursorPositionChanged()
{
	if ( m_search )
	{
		if ( editor()->cursor() == m_search->cursor() )
			return;

		if ( cbSelection->isChecked() && editor()->cursor().hasSelection()){
			m_search->setScope(editor()->cursor());
			m_search->setOrigin(QDocumentCursor());
		} else {
			if ( cbCursor->isChecked() )
				m_search->setOrigin(editor()->cursor());
		}
		if (editor()->cursor().hasSelection()) m_search->setCursor(editor()->cursor().selectionStart());
		else m_search->setCursor(editor()->cursor());
	}
}

void QSearchReplacePanel::highlightSelection(bool on)
{
	if(on){
		m_group = editor()->document()->getNextGroupId();
		QFormatScheme *f = editor()->document()->formatScheme() ? editor()->document()->formatScheme() : QDocument::formatFactory();
		int sid = f ? f->id("selection") : 0;
		QDocumentCursor c=m_search->scope();
		int begLine=qMin(c.anchorLineNumber(),c.lineNumber());
		int endLine=qMax(c.anchorLineNumber(),c.lineNumber());
		int begCol= c.anchorLineNumber()<=c.lineNumber() ? c.anchorColumnNumber() : c.columnNumber();
		int endCol= c.anchorLineNumber()<=c.lineNumber() ? c.columnNumber() : c.anchorColumnNumber();
		for(int i=begLine;i<=endLine;i++){
			int beg = i==begLine ? begCol : 0;
			int en = i==endLine ? endCol : editor()->document()->line(i).length();
			editor()->document()->addMatch(m_group,
										   i,
										   beg,
										   en-beg,
										   sid);
		}
		editor()->document()->flushMatches(m_group);
		editor()->selectNothing();
	}else{
		editor()->document()->clearMatches(m_group);
		editor()->document()->flushMatches(m_group);
		m_group = -1;
	}
}

/*! @} */
