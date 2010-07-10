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
 : QPanel(p),m_search(0),m_lastDirection(false)
{
        //setupUi(this);
        // do it completely programatic
    this->resize(801, 71);
            QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
            sizePolicy.setHorizontalStretch(0);
            sizePolicy.setVerticalStretch(0);
            sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
            this->setSizePolicy(sizePolicy);
            gridLayout = new QGridLayout(this);
            gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
            gridLayout->setContentsMargins(-1, 4, -1, 4);
            frame_2 = new QFrame(this);
            frame_2->setObjectName(QString::fromUtf8("frame_2"));
            QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
            sizePolicy1.setHorizontalStretch(0);
            sizePolicy1.setVerticalStretch(0);
            sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
            frame_2->setSizePolicy(sizePolicy1);
            frame_2->setMinimumSize(QSize(0, 22));
            frame_2->setFrameShape(QFrame::NoFrame);
            frame_2->setFrameShadow(QFrame::Raised);
            frame_2->setLineWidth(0);
            hboxLayout = new QHBoxLayout(frame_2);
            hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
            hboxLayout->setContentsMargins(-1, 0, -1, 0);
            bClose = new QToolButton(frame_2);
            bClose->setObjectName(QString::fromUtf8("bClose"));
            QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
            sizePolicy2.setHorizontalStretch(0);
            sizePolicy2.setVerticalStretch(0);
            sizePolicy2.setHeightForWidth(bClose->sizePolicy().hasHeightForWidth());
            bClose->setSizePolicy(sizePolicy2);
            bClose->setMinimumSize(QSize(20, 20));
            bClose->setMaximumSize(QSize(20, 20));
            QIcon icon;
            icon.addFile(QString::fromUtf8(":/closeall.png"), QSize(), QIcon::Normal, QIcon::Off);
            bClose->setIcon(icon);

            hboxLayout->addWidget(bClose);

            bRefresh = new QToolButton(frame_2);
            bRefresh->setObjectName(QString::fromUtf8("bRefresh"));
            sizePolicy2.setHeightForWidth(bRefresh->sizePolicy().hasHeightForWidth());
            bRefresh->setSizePolicy(sizePolicy2);
            bRefresh->setMinimumSize(QSize(20, 20));
            bRefresh->setMaximumSize(QSize(20, 20));
            QIcon icon1;
            icon1.addFile(QString::fromUtf8(":/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
            bRefresh->setIcon(icon1);

            hboxLayout->addWidget(bRefresh);

            label = new QLabel(frame_2);
            label->setObjectName(QString::fromUtf8("label"));
            QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
            sizePolicy3.setHorizontalStretch(0);
            sizePolicy3.setVerticalStretch(0);
            sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
            label->setSizePolicy(sizePolicy3);
            label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

            hboxLayout->addWidget(label);


            gridLayout->addWidget(frame_2, 0, 0, 1, 1);

            leFind = new QLineEdit(this);
            leFind->setObjectName(QString::fromUtf8("leFind"));
            QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
            sizePolicy4.setHorizontalStretch(2);
            sizePolicy4.setVerticalStretch(0);
            sizePolicy4.setHeightForWidth(leFind->sizePolicy().hasHeightForWidth());
            leFind->setSizePolicy(sizePolicy4);
            leFind->setMinimumSize(QSize(120, 22));

            gridLayout->addWidget(leFind, 0, 1, 1, 1);

            bNext = new QToolButton(this);
            bNext->setObjectName(QString::fromUtf8("bNext"));
            sizePolicy2.setHeightForWidth(bNext->sizePolicy().hasHeightForWidth());
            bNext->setSizePolicy(sizePolicy2);
            bNext->setMinimumSize(QSize(20, 20));
            bNext->setMaximumSize(QSize(20, 20));
            QIcon icon2;
            icon2.addFile(QString::fromUtf8(":/down.png"), QSize(), QIcon::Normal, QIcon::Off);
            bNext->setIcon(icon2);

            gridLayout->addWidget(bNext, 0, 3, 1, 1);

            bPrevious = new QToolButton(this);
            bPrevious->setObjectName(QString::fromUtf8("bPrevious"));
            sizePolicy2.setHeightForWidth(bPrevious->sizePolicy().hasHeightForWidth());
            bPrevious->setSizePolicy(sizePolicy2);
            bPrevious->setMinimumSize(QSize(20, 20));
            bPrevious->setMaximumSize(QSize(20, 20));
            QIcon icon3;
            icon3.addFile(QString::fromUtf8(":/up.png"), QSize(), QIcon::Normal, QIcon::Off);
            bPrevious->setIcon(icon3);

            gridLayout->addWidget(bPrevious, 0, 4, 1, 1);

            frame_6 = new QFrame(this);
            frame_6->setObjectName(QString::fromUtf8("frame_6"));
            sizePolicy1.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
            frame_6->setSizePolicy(sizePolicy1);
            frame_6->setFrameShape(QFrame::NoFrame);
            frame_6->setFrameShadow(QFrame::Raised);
            gridLayout1 = new QGridLayout(frame_6);
            gridLayout1->setContentsMargins(0, 0, 0, 0);
            gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
            cbCase = new QCheckBox(frame_6);
            cbCase->setObjectName(QString::fromUtf8("cbCase"));
            QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Preferred);
            sizePolicy5.setHorizontalStretch(0);
            sizePolicy5.setVerticalStretch(0);
            sizePolicy5.setHeightForWidth(cbCase->sizePolicy().hasHeightForWidth());
            cbCase->setSizePolicy(sizePolicy5);
            cbCase->setChecked(true);

            gridLayout1->addWidget(cbCase, 0, 0, 1, 1);

            cbWords = new QCheckBox(frame_6);
            cbWords->setObjectName(QString::fromUtf8("cbWords"));
            sizePolicy5.setHeightForWidth(cbWords->sizePolicy().hasHeightForWidth());
            cbWords->setSizePolicy(sizePolicy5);

            gridLayout1->addWidget(cbWords, 0, 1, 1, 1);

            cbRegExp = new QCheckBox(frame_6);
            cbRegExp->setObjectName(QString::fromUtf8("cbRegExp"));
            sizePolicy5.setHeightForWidth(cbRegExp->sizePolicy().hasHeightForWidth());
            cbRegExp->setSizePolicy(sizePolicy5);

            gridLayout1->addWidget(cbRegExp, 0, 2, 1, 1);

            cbHighlight = new QCheckBox(frame_6);
            cbHighlight->setObjectName(QString::fromUtf8("cbHighlight"));
            sizePolicy3.setHeightForWidth(cbHighlight->sizePolicy().hasHeightForWidth());
            cbHighlight->setSizePolicy(sizePolicy3);

            gridLayout1->addWidget(cbHighlight, 0, 3, 1, 1);

            cbCursor = new QCheckBox(frame_6);
            cbCursor->setObjectName(QString::fromUtf8("cbCursor"));
            sizePolicy5.setHeightForWidth(cbCursor->sizePolicy().hasHeightForWidth());
            cbCursor->setSizePolicy(sizePolicy5);
            cbCursor->setChecked(true);

            gridLayout1->addWidget(cbCursor, 0, 4, 1, 1);

            cbSelection = new QCheckBox(frame_6);
            cbSelection->setObjectName(QString::fromUtf8("cbSelection"));
            sizePolicy5.setHeightForWidth(cbSelection->sizePolicy().hasHeightForWidth());
            cbSelection->setSizePolicy(sizePolicy5);

            gridLayout1->addWidget(cbSelection, 0, 5, 1, 1);


            gridLayout->addWidget(frame_6, 0, 5, 2, 2,Qt::AlignTop);

            bReplaceAll = new QPushButton(this);
            bReplaceAll->setObjectName(QString::fromUtf8("bReplaceAll"));
            QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Fixed);
            sizePolicy6.setHorizontalStretch(0);
            sizePolicy6.setVerticalStretch(0);
            sizePolicy6.setHeightForWidth(bReplaceAll->sizePolicy().hasHeightForWidth());
            bReplaceAll->setSizePolicy(sizePolicy6);

            gridLayout->addWidget(bReplaceAll, 2, 5, 1, 1);

            frame = new QFrame(this);
            frame->setObjectName(QString::fromUtf8("frame"));
            frame->setFrameShape(QFrame::NoFrame);
            frame->setFrameShadow(QFrame::Raised);
            hboxLayout1 = new QHBoxLayout(frame);
            hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
            hboxLayout1->setContentsMargins(-1, 0, -1, 0);
            cbPrompt = new QCheckBox(frame);
            cbPrompt->setObjectName(QString::fromUtf8("cbPrompt"));
            sizePolicy5.setHeightForWidth(cbPrompt->sizePolicy().hasHeightForWidth());
            cbPrompt->setSizePolicy(sizePolicy5);
            cbPrompt->setChecked(false);

            hboxLayout1->addWidget(cbPrompt);

            cbReplaceAll = new QCheckBox(frame);
            cbReplaceAll->setObjectName(QString::fromUtf8("cbReplaceAll"));
            sizePolicy5.setHeightForWidth(cbReplaceAll->sizePolicy().hasHeightForWidth());
            cbReplaceAll->setSizePolicy(sizePolicy5);

            hboxLayout1->addWidget(cbReplaceAll);

            cbEscapeSeq = new QCheckBox(frame);
            cbEscapeSeq->setObjectName(QString::fromUtf8("cbEscapeSeq"));
            sizePolicy5.setHeightForWidth(cbEscapeSeq->sizePolicy().hasHeightForWidth());
            cbEscapeSeq->setSizePolicy(sizePolicy5);

            hboxLayout1->addWidget(cbEscapeSeq);


            gridLayout->addWidget(frame, 2, 6, 1, 1);

            cbReplace = new QCheckBox(this);
            cbReplace->setObjectName(QString::fromUtf8("cbReplace"));
            sizePolicy5.setHeightForWidth(cbReplace->sizePolicy().hasHeightForWidth());
            cbReplace->setSizePolicy(sizePolicy5);
            cbReplace->setLayoutDirection(Qt::LeftToRight);
            cbReplace->setChecked(true);

            gridLayout->addWidget(cbReplace, 2, 0, 1, 1);

            leReplace = new QLineEdit(this);
            leReplace->setObjectName(QString::fromUtf8("leReplace"));
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
            bReplaceNext->setObjectName(QString::fromUtf8("bReplaceNext"));
            sizePolicy2.setHeightForWidth(bReplaceNext->sizePolicy().hasHeightForWidth());
            bReplaceNext->setSizePolicy(sizePolicy2);
            bReplaceNext->setMinimumSize(QSize(20, 20));
            bReplaceNext->setMaximumSize(QSize(20, 20));
            QIcon icon4;
            icon4.addFile(QString::fromUtf8(":/images/qcodeedit/replacedown.png"), QSize(), QIcon::Normal, QIcon::Off);
            bReplaceNext->setIcon(icon4);

            gridLayout->addWidget(bReplaceNext, 2, 3, 1, 1);

            bReplacePrevious = new QToolButton(this);
            bReplacePrevious->setObjectName(QString::fromUtf8("bReplacePrevious"));
            sizePolicy2.setHeightForWidth(bReplacePrevious->sizePolicy().hasHeightForWidth());
            bReplacePrevious->setSizePolicy(sizePolicy2);
            bReplacePrevious->setMinimumSize(QSize(20, 20));
            bReplacePrevious->setMaximumSize(QSize(20, 20));
            QIcon icon5;
            icon5.addFile(QString::fromUtf8(":/images/qcodeedit/replaceup.png"), QSize(), QIcon::Normal, QIcon::Off);
            bReplacePrevious->setIcon(icon5);

            gridLayout->addWidget(bReplacePrevious, 2, 4, 1, 1);


            //retranslateUi(this);
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), cbReplace, SLOT(setVisible(bool)));
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), leReplace, SLOT(setVisible(bool)));
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplacePrevious, SLOT(setVisible(bool)));
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceNext, SLOT(setVisible(bool)));
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), frame, SLOT(setVisible(bool)));
            QObject::connect(cbReplace, SIGNAL(toggled(bool)), bReplaceAll, SLOT(setVisible(bool)));
            QObject::connect(bClose, SIGNAL(clicked()), this, SLOT(close()));

            // coonect by name ????
            QMetaObject::connectSlotsByName(this);

            // set texts
            #ifndef QT_NO_TOOLTIP
                    bClose->setToolTip(QApplication::translate("SearchReplace", "Close search/replace panel", 0, QApplication::UnicodeUTF8));
                    bRefresh->setToolTip(QApplication::translate("SearchReplace", "Refresh search underlying context (as an attempt to correct search behavior)", 0, QApplication::UnicodeUTF8));
                    leFind->setToolTip(QApplication::translate("SearchReplace", "Text or pattern to search for", 0, QApplication::UnicodeUTF8));
                    bNext->setToolTip(QApplication::translate("SearchReplace", "Find next occurence", 0, QApplication::UnicodeUTF8));
                    bPrevious->setToolTip(QApplication::translate("SearchReplace", "Find previous occurence", 0, QApplication::UnicodeUTF8));
                    leReplace->setToolTip(QApplication::translate("SearchReplace", "Replacement text", 0, QApplication::UnicodeUTF8));
                    bReplaceNext->setToolTip(QApplication::translate("SearchReplace", "Find next occurence", 0, QApplication::UnicodeUTF8));
                    bReplacePrevious->setToolTip(QApplication::translate("SearchReplace", "Find previous occurence", 0, QApplication::UnicodeUTF8));
            #endif // QT_NO_TOOLTIP
                    bClose->setText(QString());
                    bRefresh->setText(QString());
                    label->setText(QApplication::translate("SearchReplace", " Find :", 0, QApplication::UnicodeUTF8));
                    label->setMinimumWidth(label->sizeHint().width());
                    bNext->setText(QString());
                    bPrevious->setText(QString());
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
                    bReplaceAll->setText(QApplication::translate("SearchReplace", "all", 0, QApplication::UnicodeUTF8));
                    cbPrompt->setText(QApplication::translate("SearchReplace", "Prompt on replace", 0, QApplication::UnicodeUTF8));
                    cbReplaceAll->setText(QApplication::translate("SearchReplace", "Replace all", 0, QApplication::UnicodeUTF8));
                    cbEscapeSeq->setText(QApplication::translate("SearchReplace", "Escape sequences", 0, QApplication::UnicodeUTF8));
                    cbReplace->setText(QApplication::translate("SearchReplace", "Replace :", 0, QApplication::UnicodeUTF8));
                    bReplaceNext->setText(QString());
                    bReplacePrevious->setText(QString());

                    minimum_width=frame_2->sizeHint().width()+leFind->sizeHint().width()+2*bNext->sizeHint().width()+5*hboxLayout->spacing();
            //

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

	if (cbCursor->isChecked() && !m_search->cursor().isValid())
		m_search->setCursor(editor()->cursor());  //start from current cursor if no known cursor
	if (m_search->searchText()!=leFind->text())
		m_search->setSearchText(leFind->text());
	if (replace && m_search->replaceText()!=leReplace->text())
		m_search->setReplaceText(leReplace->text());
	m_search->setOption(QDocumentSearch::Replace,replace);
	m_search->next(backward, replaceAll, !cbPrompt->isChecked(), true);
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

void QSearchReplacePanel::find(QString text, bool backward, bool highlight, bool regex, bool word, bool caseSensitive){
    if (!isVisible()) display(1,false);
    if (m_search && m_search->searchText()!=text) {
        delete m_search;
        m_search=0;
    }
	if (!m_search) editor()->setCursorPosition(0,0);
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
		m_search->setOrigin(QDocumentCursor());
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
		if ( m_search && cbHighlight->isChecked())
		{
			m_search->setOption(QDocumentSearch::HighlightAll, false);
			m_search->setOption(QDocumentSearch::HighlightAll, true);
		}
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
			m_search->setOrigin(QDocumentCursor());
		} else {
			if ( cbCursor->isChecked() )
				m_search->setOrigin(editor()->cursor());
		}
		m_search->setCursor(editor()->cursor());
	}
}

int QSearchReplacePanel::numberOfFindings(){
	if ( m_search )
	{
		m_search->setOption(QDocumentSearch::HighlightAll, true);
		return m_search->indexedMatchCount();
	} else return 0;
}

/*! @} */
