/***************************************************************************
 *   copyright       : (C) 2007 by Pascal Brachet                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_Speller_Dialog
#define Header_Speller_Dialog

#include "mostQtHeaders.h"

#include "latexeditorview.h"
#include "spellerutility.h"
//#include "latexparser/latexreader.h"

#include "ui_spellerdialog.h"

#include "qeditor.h"

#include <QStyledItemDelegate>

class SpellerDialog : public QDialog
{
	Q_OBJECT

public:
	SpellerDialog(QWidget *parent = 0, SpellerUtility *utility = 0);
	~SpellerDialog();
	Ui::SpellerDialog ui;
	void setEditorView(LatexEditorView *edView);
	void startSpelling();

private :
	QStatusBar *m_statusBar;
	SpellerUtility *m_speller;
	QEditor *editor;
	LatexEditorView *editorView;
    TokenList tl;
    int tokenListIndex;
	int startLine, startIndex, curLine, endLine, endIndex;
	bool ignoreListChanged;
    QMap<QString, QString> mReplacementList;

protected:
	void closeEvent(QCloseEvent *);

private slots:
	void accept();
	void slotIgnore();
    void slotIgnoreAll();
	void slotAlwaysIgnore();
	void slotReplace();
	void updateItem();
	void SpellingNextWord();
	void toggleIgnoreList(bool forceHide = false);
	void addIgnoredWord();
	void removeIgnoredWord();
	void finishEditIgnoreList();
};


class ValidatedLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	explicit ValidatedLineEdit(QWidget *parent = 0);
};


class IgnoreListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit IgnoreListViewDelegate(QObject *parent = 0);
	void setModelData(QWidget *editor,
	                  QAbstractItemModel *model,
	                  const QModelIndex &index) const;
};


#endif
