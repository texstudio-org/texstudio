/***************************************************************************
 *   copyright       : (C) 2007 by Pascal Brachet                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SPELLERDIALOG_H
#define SPELLERDIALOG_H

#include "latexeditorview.h"
#include "spellerutility.h"

#include "ui_spellerdialog.h"

#include "qeditor.h"

class SpellerDialog : public QDialog  {
	Q_OBJECT
public:
	SpellerDialog(QWidget *parent=0, SpellerUtility *utility=0);
	~SpellerDialog();
	Ui::SpellerDialog ui;
	void setEditorView(LatexEditorView *edView);
	void startSpelling();
private :
	SpellerUtility *m_speller;
	QEditor *editor;
	LatexEditorView *editorView;
	int startLine,startIndex,curLine,curIndex, endLine,endIndex;
	QString curWord;
	bool ignoreListChanged;
protected:
	void closeEvent(QCloseEvent*);
private slots:
	void accept();
	void slotIgnore();
	void slotAlwaysIgnore();
	void slotReplace();
	void updateItem();
	void SpellingNextWord();
	void toggleIgnoreList();
	void addRemoveIgnoredWord();
	void ignoreListClicked(const QModelIndex &mod);
};


#endif
