/***************************************************************************
 *   copyright       : (C) 2007 by Pascal Brachet                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "spellerdialog.h"

#include "smallUsefulFunctions.h"

#include "qdocumentline.h"

SpellerDialog::SpellerDialog(QWidget *parent,SpellerUtility *utility)
		:QDialog(parent),m_speller(utility),editor(0),editorView(0) {
	ui.setupUi(this);
	setModal(true);

	m_speller=utility;

	connect(ui.pushButtonIgnoreList, SIGNAL(clicked()), this, SLOT(toggleIgnoreList()));
	connect(ui.pushButtonAddRemove, SIGNAL(clicked()), this, SLOT(addRemoveIgnoredWord()));
	connect(ui.pushButtonIgnore, SIGNAL(clicked()), this, SLOT(slotIgnore()));
	connect(ui.pushButtonAlwaysIgnore, SIGNAL(clicked()), this, SLOT(slotAlwaysIgnore()));
	connect(ui.pushButtonReplace, SIGNAL(clicked()), this, SLOT(slotReplace()));
	connect(ui.listWidget, SIGNAL(itemSelectionChanged()),this, SLOT(updateItem()));
	connect(ui.ignoreListView, SIGNAL(clicked(QModelIndex)),this, SLOT(ignoreListClicked(QModelIndex)));

	ui.listWidget->setEnabled(false);
	ui.lineEditNew->setEnabled(false);
	ui.pushButtonIgnore->setEnabled(false);
	ui.pushButtonAlwaysIgnore->setEnabled(false);
	ui.pushButtonReplace->setEnabled(false);
	ui.lineEditOriginal->setEnabled(false);
	resize(size().width(),height()-ui.ignoreListFrame->height());
	ui.ignoreListFrame->hide();
}

SpellerDialog::~SpellerDialog() {
	ui.lineEditOriginal->clear();
	ui.listWidget->clear();
	ui.lineEditNew->clear();

}

void SpellerDialog::setEditorView(LatexEditorView *edView) {
	editor=edView?edView->editor:0;
	editorView=edView;
}

void SpellerDialog::startSpelling() {
	if (!editor) return;
	ignoreListChanged=false;
	if (editor->cursor().hasSelection()) {
		ui.labelMessage->setText(tr("Check spelling selection..."));
		//endpos=c.selectionEnd();
		//c.setPosition(endpos,QTextCursor::MoveAnchor);
		//c.setPosition(startpos,QTextCursor::MoveAnchor);
		startLine=editor->cursor().selectionStart().lineNumber();
		startIndex=editor->cursor().selectionStart().columnNumber();
		endLine=editor->cursor().selectionEnd().lineNumber();
		endIndex=editor->cursor().selectionEnd().columnNumber();
	} else  {
		//	c.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor);
		ui.labelMessage->setText(tr("Check spelling from cursor..."));
		//endpos=c.position();
		//c.setPosition(startpos,QTextCursor::MoveAnchor);
		editor->getCursorPosition(startLine,startIndex);
		endLine=editor->document()->lines()-1;
		endIndex=editor->text(endLine).length();
		QString curLine=editor->document()->line(startLine).text();
		int nextIndex=0;
		int wordStartIndex=0;
		QString tempWord;
		//jump from word to word until an valid index is reached
		while (nextIndex<startIndex)
			if (!nextTextWord(curLine,nextIndex,tempWord,wordStartIndex)) break;
		startIndex=wordStartIndex;
	}
	curLine=startLine;
	curIndex=startIndex;
	curWord="";
	show();
	SpellingNextWord();
}
void SpellerDialog::closeEvent(QCloseEvent* ce) {
	if (editorView && ignoreListChanged) {
		ignoreListChanged=false;
		editorView->documentContentChanged(0,editor->document()->lines());
	}
	if (editor) editor->setCursorPosition(startLine,startIndex);
	ce->accept();
}

void SpellerDialog::accept() {
	if (editorView && ignoreListChanged) {
		ignoreListChanged=false;
		editorView->documentContentChanged(0,editor->document()->lines());
	}
	if (editor) editor->setCursorPosition(startLine,startIndex);
	QDialog::accept();
}

void SpellerDialog::updateItem() {
	int current=-1;
	QList<QListWidgetItem *> items;
	items = ui.listWidget->selectedItems();
	if (items.count() > 0) {
		ui.listWidget->setCurrentItem(items[0]);
		current=ui.listWidget->row(items[0]);
	}
	if (current>=0) {
		ui.lineEditNew->setText(ui.listWidget->currentItem()->text());
	}
}


void SpellerDialog::slotIgnore() {
	SpellingNextWord();
}

void SpellerDialog::slotAlwaysIgnore() {
	//todo: real time update of now allowed words
	m_speller->addToIgnoreList(ui.lineEditOriginal->text());
	ignoreListChanged=true;
	SpellingNextWord();
}

void SpellerDialog::slotReplace() {
	if (!editor) return;
	if (editor->cursor().hasSelection()) {
		QString selectedword=editor->cursor().selectedText();
		curWord=ui.lineEditNew->text();
		editor->cursor().removeSelectedText();
		editor->cursor().insertText(curWord);
	}
	SpellingNextWord();
}

void SpellerDialog::SpellingNextWord() {
	if (!editor || !m_speller) return;
	for (; curLine<=endLine; curLine++) {
		int wordStartIndex;
		while (nextTextWord(editor->text(curLine),curIndex,curWord,wordStartIndex)) {
			if (curLine==endLine && curIndex>endIndex)
				break; //not in checked range
			if (m_speller->check(curWord)) continue;
			QStringList suggWords=m_speller->suggest(curWord);

			QDocumentCursor wordSelection(editor->document(),curLine,wordStartIndex);
			wordSelection.movePosition(curIndex-wordStartIndex,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
			editor->setCursor(wordSelection);

			ui.listWidget->setEnabled(true);
			ui.lineEditNew->setEnabled(true);
			ui.pushButtonIgnore->setEnabled(true);
			ui.pushButtonAlwaysIgnore->setEnabled(true);
			ui.pushButtonReplace->setEnabled(true);
			ui.lineEditOriginal->setEnabled(true);
			ui.lineEditOriginal->setText(curWord);
			ui.listWidget->clear();
			ui.lineEditNew->clear();
			ui.labelMessage->setText("");
			if (!suggWords.isEmpty()) {
				ui.listWidget->addItems(suggWords);
				ui.lineEditNew->setText(suggWords.at(0));
			}
			return;
		}
		curIndex=0;
		curWord="";
	}

	//no word found
	ui.listWidget->setEnabled(false);
	ui.lineEditNew->setEnabled(false);
	ui.pushButtonIgnore->setEnabled(false);
	ui.pushButtonAlwaysIgnore->setEnabled(false);
	ui.pushButtonReplace->setEnabled(false);
	ui.lineEditOriginal->setEnabled(false);
	ui.lineEditOriginal->clear();
	ui.listWidget->clear();
	ui.lineEditNew->clear();
	ui.labelMessage->setText("<b>"+tr("No more misspelled words")+"</b>");
}

void SpellerDialog::toggleIgnoreList() {
	if (ui.ignoreListFrame->isVisible()) {
		ui.ignoreListFrame->hide();
		ui.pushButtonIgnoreList->setText(tr("Show Ignore List \\/"));
		resize(size().width(),height()-ui.ignoreListFrame->height());
	} else {
		resize(size().width(),height()+ui.ignoreListFrame->height());
		ui.pushButtonIgnoreList->setText(tr("Hide Ignore List /\\"));
		if (m_speller && !ui.ignoreListView->model())
			ui.ignoreListView->setModel(m_speller->ignoreListModel());
		ui.ignoreListFrame->show();
	}
}

void SpellerDialog::addRemoveIgnoredWord() {
	if (!m_speller) return;
	QString word=ui.lineEditIgnoredWord->text();
	if (m_speller->ignoreListModel()->stringList().contains(word)) m_speller->removeFromIgnoreList(word);
	else m_speller->addToIgnoreList(word);
}

void SpellerDialog::ignoreListClicked(const QModelIndex &mod) {
	// remove unused argument warning
	(void) mod;

	if (!ui.ignoreListView->model()) return;
	ui.lineEditIgnoredWord->setText(ui.ignoreListView->model()->data(ui.ignoreListView->currentIndex(),Qt::DisplayRole).toString());
}
