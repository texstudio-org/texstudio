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

#include <QScrollBar>
#include <QPaintEvent>

static QString escapeCpp(const QString& s, bool rep)
{
	if ( !rep )
		return s;

	QString es;

	for ( int i = 0; i < s.count(); ++i )
	{
		if ( (s.at(i) == '\\') && ((i + 1) < s.count()) )
		{
			QChar c = s.at(++i);

			if ( c == '\\' )
				es += '\\';
			else if ( c == 't' )
				es += '\t';
			else if ( c == 'n' )
				es += '\n';
			else if ( c == 'r' )
				es += '\r';
			else if ( c == '0' )
				es += '\0';

		} else {
			es += s.at(i);
		}
	}

	//qDebug("\"%s\" => \"%s\"", qPrintable(s), qPrintable(es));

	return es;
}

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
 : QPanel(p), lastDirection(0), m_search(0)
{
	setupUi(this);
	setDefaultVisibility(false);

	cbCase->setChecked(false);

	leFind->installEventFilter(this);
	leReplace->installEventFilter(this);
}

/*!
	\brief Empty destructor
*/
QSearchReplacePanel::~QSearchReplacePanel()
{
	if ( m_search )
		delete m_search;
}

/*!

*/
QString QSearchReplacePanel::type() const
{
	return "Search";
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
		leFind->selectAll();
		//show();
	}

	setVisible(visible);

	if ( !visible )
		editor()->setFocus();
}

/*!

*/
void QSearchReplacePanel::find(int backward)
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

		if ( backward != -1 )
			lastDirection = backward;
	}

        bool replaceAll = false;

	if ( backward == -1 )
	{
		backward = lastDirection;
	} else {
		if ( lastDirection != backward && editor()->cursor().hasSelection() && !replaceAll )
			m_search->next(backward, false); //the first hit is already selected

		lastDirection = backward;
	}

	m_search->next(backward, replaceAll);

	if (isVisible() && !leFind->hasFocus() && !leReplace->hasFocus() )
		leFind->setFocus();
}

void QSearchReplacePanel::replace(bool replaceAll)
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
        bool res=m_search->cursor().hasSelection();
        if(res||replaceAll) m_search->next(0,replaceAll,true);
        if(!replaceAll) m_search->next(lastDirection);

        if (isVisible() && !leFind->hasFocus() && !leReplace->hasFocus() )
                leFind->setFocus();
}

void QSearchReplacePanel::find(QString text, bool backward, bool highlight, bool regex){
    if (!isVisible()) display(1,false);
    if (m_search && m_search->searchText()!=text) {
        delete m_search;
        m_search=0;
    }
    if (!m_search) editor()->setCursorPosition(0,0);
    lastDirection=backward?1:0;
    leFind->setText(text);
    cbHighlight->setChecked(highlight);
    cbRegExp->setChecked(regex);
    find (backward?1:0);
}

/*!

*/
void QSearchReplacePanel::hideEvent(QHideEvent *)
{
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
					on_leFind_returnPressed(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers());
					return true;
				} else if ( kc == Qt::Key_Escape) {
					if ( cbReplace->isChecked() )
						display(1,false);
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
	if ( cbReplace->isChecked() )
	{
		// do not perfrom incremental search when replacing

		if ( m_search )
			m_search->setSearchText(text);

		leFind->setStyleSheet(QString());
		return;
	}

	bool hadSearch = m_search;
	QDocumentCursor cur = editor()->cursor();

	if ( m_search )
	{
		cur = m_search->cursor();

		m_search->setSearchText(text);

		if ( cbCursor->isChecked() )
		{
			QDocumentCursor c = cur;
			c.setColumnNumber(qMin(c.anchorColumnNumber(), c.columnNumber()));

			m_search->setCursor(c);
		}
	} else {
		// TODO : make incremental search optional
		init();
	}

	if ( text.isEmpty() )
	{
		leFind->setStyleSheet(QString());
		return;
	}

	m_search->setOption(QDocumentSearch::Silent, true);

	find(0);

	m_search->setOption(QDocumentSearch::Silent, false);

	if ( m_search->cursor().isNull() )
	{
		leFind->setStyleSheet("QLineEdit { background: red; color : white; }");

		if ( hadSearch )
		{
			m_search->setCursor(cur);

			// figure out whether other matches are availables
			QDocumentSearch::Options opts = m_search->options();
			opts &= ~QDocumentSearch::HighlightAll;
			opts |= QDocumentSearch::Silent;

			QDocumentSearch temp(editor(), text, opts);
			temp.setOrigin(QDocumentCursor());
			temp.setScope(m_search->scope());
			temp.next(true);

			if ( temp.cursor().isValid() )
			{
				// other match found from doc start
				leFind->setStyleSheet("QLineEdit { background: yellow; color : black; }");
				m_search->setCursor(cur.document()->cursor(0,0));
				find(0);
			}
		}
	} else {
		leFind->setStyleSheet(QString());
		editor()->setCursor(m_search->cursor());
	}
}

void QSearchReplacePanel::on_leFind_returnPressed(bool backward)
{
	leFind->setStyleSheet(QString());

	if ( backward )
		find(1);
	else
		find(0);

}

void QSearchReplacePanel::on_leReplace_textEdited(const QString& text)
{
	if ( m_search )
		m_search->setReplaceText(text);

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

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbRegExp_clicked(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::RegExp, on);

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbCase_toggled(bool on)
{
	if ( m_search )
		m_search->setOption(QDocumentSearch::CaseSensitive, on);

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbCursor_clicked(bool on)
{
	if ( m_search )
	{
		m_search->setOrigin(on ? editor()->cursor() : QDocumentCursor());

		if ( cbHighlight->isChecked() )
			m_search->next(false);
	}

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbHighlight_clicked(bool on)
{
	if ( !m_search )
		init();

	if ( m_search )
	{
		m_search->setOption(QDocumentSearch::HighlightAll, on);

		if ( on && !m_search->indexedMatchCount() )
			m_search->next(false);
	}

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbSelection_toggled(bool on)
{
	if ( m_search )
		m_search->setScope(on ? editor()->cursor() : QDocumentCursor());

	leFind->setFocus();
}

void QSearchReplacePanel::on_cbEscapeSeq_toggled(bool on)
{
	// remove unused argument warning
	(void) on;

	if ( m_search )
		m_search->setReplaceText(escapeCpp(leReplace->text(), cbEscapeSeq->isChecked()));
}

void QSearchReplacePanel::on_bNext_clicked()
{
	if ( !m_search )
		init();

	leFind->setStyleSheet(QString());
	find(0);
}

void QSearchReplacePanel::on_bPrevious_clicked()
{
	if ( !m_search )
		init();

	leFind->setStyleSheet(QString());
	find(1);
}

void QSearchReplacePanel::on_bRefresh_clicked()
{
	init();
}

void QSearchReplacePanel::on_bReplace_clicked()
{
        if ( !m_search )
                init();

        leFind->setStyleSheet(QString());
        replace();
}

void QSearchReplacePanel::on_bReplaceAll_clicked()
{
        if ( !m_search )
                init();

        leFind->setStyleSheet(QString());
        replace(true);
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

	if ( cbHighlight->isChecked() && !cbReplace->isVisible() )
		opt |= QDocumentSearch::HighlightAll;

	if ( cbReplace->isChecked() && cbReplace->isVisible() )
		opt |= QDocumentSearch::Replace;

        opt |= QDocumentSearch::Prompt;

	m_search = new QDocumentSearch(	editor(),
									leFind->text(),
									opt,
									cbReplace->isChecked()
										?
											escapeCpp(leReplace->text(), cbEscapeSeq->isChecked())
										:
											QString()
									);


	if ( cbCursor->isChecked() )
		m_search->setCursor(editor()->cursor());

	if ( cbSelection->isChecked() )
		m_search->setScope(editor()->cursor());

}

void QSearchReplacePanel::cursorPositionChanged()
{
	if ( m_search )
	{
		if ( editor()->cursor() == m_search->cursor() || cbHighlight->isChecked() )
			return;

		if ( cbCursor->isChecked() )
			m_search->setOrigin(editor()->cursor());

		m_search->setCursor(editor()->cursor());
	}
}

/*! @} */
