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

#ifndef _QSEARCH_REPLACE_PANEL_H_
#define _QSEARCH_REPLACE_PANEL_H_

#include "mostQtHeaders.h"

#include "qpanel.h"

/*!
	\file qsearchreplacepanel.h
	\brief Definition of the QSearchReplacePanel class.
	
	\see QSearchReplacePanel
*/

//#include "ui_searchreplace.h"

class QDocumentCursor;
class QDocumentLine;
class QDocumentSearch;

class QCE_EXPORT QSearchReplacePanel : public QPanel //, private Ui::SearchReplace
{
	Q_OBJECT
	
	public:
		Q_PANEL(QSearchReplacePanel, "Search Replace Panel")
		
		QSearchReplacePanel(QWidget *p = 0);
		virtual ~QSearchReplacePanel();
		
		virtual QString type() const;
		bool isReplaceModeActive() const;
		QDocumentCursor getSearchScope() const;
		QDocumentSearch * search(){
			return m_search;
		}

	public slots:
		void display(int mode, bool replace);
		
		void findNext();
		void findReplace(bool backward, bool replace=false, bool replaceAll=false);
		void find(QString text, bool backward, bool highlight, bool regex, bool word, bool caseSensitive);
                void find(QString text, bool backward, bool highlight, bool regex, bool word, bool caseSensitive, bool fromCursor, bool selection);
		void setOptions(int searchOptions, bool cursor, bool selection);
		
	signals:
		void onClose();
	protected:
		virtual bool forward(QMouseEvent *e);
		virtual void editorChange(QEditor *e);
		
		virtual bool eventFilter(QObject *o, QEvent *e);
		
		virtual void hideEvent(QHideEvent *e);
		virtual void closeEvent(QCloseEvent *e);

                virtual void resizeEvent(QResizeEvent *e);

	private slots:
		void on_leFind_textEdited(const QString& text);
		void on_leReplace_textEdited(const QString& text);
		
		void on_cbReplace_toggled(bool on);
		
		void on_cbCase_toggled(bool on);
		void on_cbWords_toggled(bool on);
		void on_cbRegExp_toggled(bool on);
		void on_cbCursor_toggled(bool on);
		void on_cbHighlight_toggled(bool on);
		void on_cbSelection_toggled(bool on);
		void on_cbEscapeSeq_toggled(bool on);
		void on_cbPrompt_toggled(bool on);
		

		void on_bNext_clicked();
		void on_bPrevious_clicked();

		void on_bReplaceNext_clicked();
		void on_bReplacePrevious_clicked();
		void on_bReplaceAll_clicked();
		
		void cursorPositionChanged();

	private:
		void init();
		void on_leFind_returnPressed(bool backward);
		void on_leReplace_returnPressed(bool backward);
		QDocumentSearch *m_search;
		bool m_lastDirection;
		int minimum_width;

	protected:
		//protected to give unit tests access
		QGridLayout *gridLayout;
		QFrame *frame_2;
		QHBoxLayout *hboxLayout;
		QToolButton *bClose;
		QLabel *label;
		QLineEdit *leFind;
		QToolButton *bNext;
		QToolButton *bPrevious;
		QFrame *frame_6;
		QGridLayout *gridLayout1;
		QCheckBox *cbCase;
		QCheckBox *cbWords;
		QCheckBox *cbRegExp;
		QCheckBox *cbHighlight;
		QCheckBox *cbCursor;
		QCheckBox *cbSelection;
		QPushButton *bReplaceAll;
		QFrame *frame;
		QHBoxLayout *hboxLayout1;
		QCheckBox *cbPrompt;
		QCheckBox *cbReplaceAll;
		QCheckBox *cbEscapeSeq;
		QCheckBox *cbReplace;
		QLineEdit *leReplace;
		QToolButton *bReplaceNext;
		QToolButton *bReplacePrevious;

};

#endif // _QSEARCH_REPLACE_PANEL_H_
