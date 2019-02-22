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
#include "utilsUI.h"

#include "qdocumentline.h"

#include <QItemEditorCreatorBase>
#include <QStyledItemDelegate>

static const QRegExpValidator wordValidator(QRegExp("[^<].*"), nullptr);

SpellerDialog::SpellerDialog(QWidget *parent, SpellerUtility *utility)
    : QDialog(parent), m_statusBar(nullptr), m_speller(utility), editor(nullptr), editorView(nullptr)
{
	ui.setupUi(this);
	setModal(true);
	UtilsUi::resizeInFontHeight(this, 31, 26);

	m_statusBar = new QStatusBar();
	delete ui.dummyStatusBar;
	layout()->addWidget(m_statusBar);
	// workaround for wrong status bar text color (black) in modern style
	// TODO: change the style and remove this extra label
	QLabel *messageArea = new QLabel(m_statusBar);
	connect(m_statusBar, SIGNAL(messageChanged(QString)), messageArea, SLOT(setText(QString)));
	m_statusBar->addPermanentWidget(messageArea, 1);

	connect(ui.pushButtonIgnoreList, SIGNAL(clicked()), this, SLOT(toggleIgnoreList()));
	connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(addIgnoredWord()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeIgnoredWord()));
	connect(ui.pushButtonIgnore, SIGNAL(clicked()), this, SLOT(slotIgnore()));
	connect(ui.pushButtonAlwaysIgnore, SIGNAL(clicked()), this, SLOT(slotAlwaysIgnore()));
	connect(ui.pushButtonReplace, SIGNAL(clicked()), this, SLOT(slotReplace()));
	connect(ui.listSuggestions, SIGNAL(itemSelectionChanged()), this, SLOT(updateItem()));

	ui.listSuggestions->setEnabled(false);
	ui.lineEditNew->setEnabled(false);
	ui.pushButtonIgnore->setEnabled(false);
	ui.pushButtonAlwaysIgnore->setEnabled(false);
	ui.pushButtonReplace->setEnabled(false);
	ui.lineEditOriginal->setEnabled(false);

	ui.ignoreListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	IgnoreListViewDelegate *itemDelegate = new IgnoreListViewDelegate(ui.ignoreListView);
	ui.ignoreListView->setItemDelegate(itemDelegate);
	connect(itemDelegate, SIGNAL(closeEditor(QWidget *)), this, SLOT(finishEditIgnoreList()));

	toggleIgnoreList(true);  // start with hidden ignore list
}

SpellerDialog::~SpellerDialog()
{
	ui.lineEditOriginal->clear();
	ui.listSuggestions->clear();
	ui.lineEditNew->clear();

}

void SpellerDialog::setEditorView(LatexEditorView *edView)
{
    editor = edView ? edView->editor : nullptr;
	editorView = edView;
}

void SpellerDialog::startSpelling()
{
	if (!editor) return;
	ignoreListChanged = false;
	if (editor->cursor().hasSelection()) {

		m_statusBar->showMessage(tr("Check spelling selection..."));
		//endpos=c.selectionEnd();
		//c.setPosition(endpos,QTextCursor::MoveAnchor);
		//c.setPosition(startpos,QTextCursor::MoveAnchor);
		startLine = editor->cursor().selectionStart().lineNumber();
		startIndex = editor->cursor().selectionStart().columnNumber();
		endLine = editor->cursor().selectionEnd().lineNumber();
		endIndex = editor->cursor().selectionEnd().columnNumber();
	} else  {
		//	c.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor);
		m_statusBar->showMessage(tr("Check spelling from cursor..."));
		//endpos=c.position();
		//c.setPosition(startpos,QTextCursor::MoveAnchor);
		editor->getCursorPosition(startLine, startIndex);
		endLine = editor->document()->lines() - 1;
		endIndex = editor->text(endLine).length();
		latexReader.setLine(editor->document()->line(startLine).text());
		//jump from word to word until an valid index is reached
		while (latexReader.index < startIndex)
			if (!latexReader.nextTextWord()) break;
		startIndex = latexReader.wordStartIndex;
	}
	curLine = startLine;
	latexReader.index = startIndex;
	latexReader.word = "";
	show();
	SpellingNextWord();
}

void SpellerDialog::closeEvent(QCloseEvent *ce)
{
	if (editorView && ignoreListChanged) {
		ignoreListChanged = false;
		editorView->documentContentChanged(0, editor->document()->lines());
	}
	if (editor) editor->setCursorPosition(startLine, startIndex);
	ce->accept();
}

void SpellerDialog::accept()
{
	if (editorView && ignoreListChanged) {
		ignoreListChanged = false;
		editorView->documentContentChanged(0, editor->document()->lines());
	}
	if (editor) editor->setCursorPosition(startLine, startIndex);
	QDialog::accept();
}

void SpellerDialog::updateItem()
{
	int current = -1;
	QList<QListWidgetItem *> items;
	items = ui.listSuggestions->selectedItems();
	if (items.count() > 0) {
		ui.listSuggestions->setCurrentItem(items[0]);
		current = ui.listSuggestions->row(items[0]);
	}
	if (current >= 0) {
		ui.lineEditNew->setText(ui.listSuggestions->currentItem()->text());
	}
}

void SpellerDialog::slotIgnore()
{
	SpellingNextWord();
}

void SpellerDialog::slotAlwaysIgnore()
{
	//todo: real time update of now allowed words
	m_speller->addToIgnoreList(ui.lineEditOriginal->text());
	ignoreListChanged = true;
	SpellingNextWord();
}

void SpellerDialog::slotReplace()
{
	if (!editor) return;
	if (editor->cursor().hasSelection()) {
		QString selectedword = editor->cursor().selectedText();
		latexReader.index += ui.lineEditNew->text().size() - latexReader.word.size();
		latexReader.word = ui.lineEditNew->text();
		editor->insertText(latexReader.word);
	}
	SpellingNextWord();
}

void SpellerDialog::SpellingNextWord()
{
	if (!editor || !m_speller) return;
	for (; curLine <= endLine; curLine++) {
		latexReader.line = editor->text(curLine);
		LatexReader::NextWordFlag nwf;
		while ((nwf = latexReader.nextWord(false)) != LatexReader::NW_NOTHING) {
			if (curLine == endLine && latexReader.index > endIndex)
				break; //not in checked range
			if (nwf != LatexReader::NW_TEXT)
				continue;
			if (m_speller->check(latexReader.word)) continue;
			QStringList suggWords = m_speller->suggest(latexReader.word);

			QDocumentCursor wordSelection(editor->document(), curLine, latexReader.wordStartIndex);
			wordSelection.movePosition(latexReader.index - latexReader.wordStartIndex, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
			editor->setCursor(wordSelection);

			ui.listSuggestions->setEnabled(true);
			ui.lineEditNew->setEnabled(true);
			ui.pushButtonIgnore->setEnabled(true);
			ui.pushButtonAlwaysIgnore->setEnabled(true);
			ui.pushButtonReplace->setEnabled(true);
			ui.lineEditOriginal->setEnabled(true);
			ui.lineEditOriginal->setText(latexReader.word);
			ui.listSuggestions->clear();
			ui.lineEditNew->clear();
			m_statusBar->clearMessage();
			if (!suggWords.isEmpty()) {
				ui.listSuggestions->addItems(suggWords);
				ui.lineEditNew->setText(suggWords.at(0));
			}
			return;
		}
		latexReader.index = 0;
		latexReader.word = "";
	}

	//no word found
	ui.listSuggestions->setEnabled(false);
	ui.lineEditNew->setEnabled(false);
	ui.pushButtonIgnore->setEnabled(false);
	ui.pushButtonAlwaysIgnore->setEnabled(false);
	ui.pushButtonReplace->setEnabled(false);
	ui.lineEditOriginal->setEnabled(false);
	ui.lineEditOriginal->clear();
	ui.listSuggestions->clear();
	ui.lineEditNew->clear();
	m_statusBar->showMessage("<b>" + tr("No more misspelled words") + "</b>");
}

void SpellerDialog::toggleIgnoreList(bool forceHide)
{
	QList<QWidget *> hideableWidgets = QList<QWidget *>() << ui.ignoreListView << ui.labelIgnoredWords << ui.pushButtonAdd << ui.pushButtonRemove << ui.labelAsHideableSpacer;

	if (ui.ignoreListView->isVisible() || forceHide) {
		foreach (QWidget * w, hideableWidgets) w->hide();
		ui.pushButtonIgnoreList->setText(tr("Show User Words"));
		ui.pushButtonIgnoreList->setIcon(getRealIcon("down-arrow-circle-silver"));
		resize(width(), height() - (ui.ignoreListView->height() + ui.gridLayout->verticalSpacing()));
	} else {
		resize(width(), height() + (ui.listSuggestions->height() + ui.gridLayout->verticalSpacing()));
		ui.pushButtonIgnoreList->setText(tr("Hide User Words"));
		ui.pushButtonIgnoreList->setIcon(getRealIcon("up-arrow-circle-silver"));
		if (m_speller && !ui.ignoreListView->model())
			ui.ignoreListView->setModel(m_speller->ignoreListModel());
		foreach (QWidget * w, hideableWidgets) w->show();
	}
}

void SpellerDialog::addIgnoredWord()
{
	if (!m_speller) return;
	finishEditIgnoreList(); // needed for possible cleanup if an editor is open, harmless otherwise

	QStringListModel *m = m_speller->ignoreListModel();
	m->insertRow(0);
	m->setData(m->index(0), QVariant(tr("<new>", "Placeholder for new added word in ignore list")));

	ui.ignoreListView->selectionModel()->setCurrentIndex(m->index(0), QItemSelectionModel::Select);
	ui.ignoreListView->edit(m->index(0));
}

void SpellerDialog::removeIgnoredWord()
{
	if (!m_speller) return;
	if (!ui.ignoreListView->model()) return;
	QString selectedWord = ui.ignoreListView->model()->data(ui.ignoreListView->currentIndex(), Qt::DisplayRole).toString();
	m_speller->removeFromIgnoreList(selectedWord);
}

void SpellerDialog::finishEditIgnoreList()
{
	QString word = ui.ignoreListView->model()->data(ui.ignoreListView->currentIndex(), Qt::DisplayRole).toString();
	int dummy;
	if (wordValidator.validate(word, dummy) == QValidator::Acceptable) {
		m_speller->addToIgnoreList(word);
	} else {
		ui.ignoreListView->model()->removeRow(ui.ignoreListView->currentIndex().row());
	}
}

ValidatedLineEdit::ValidatedLineEdit(QWidget *parent) : QLineEdit(parent)
{
	setValidator(&wordValidator);
}

IgnoreListViewDelegate::IgnoreListViewDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
	QItemEditorCreatorBase *creator = new QStandardItemEditorCreator<ValidatedLineEdit>();
	QItemEditorFactory *factory = new QItemEditorFactory();
	factory->registerEditor(QVariant::String, creator);
	setItemEditorFactory(factory);
}

void IgnoreListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QByteArray n = editor->metaObject()->userProperty().name();
	if (!n.isEmpty()) {
		QString word = editor->property(n).toString();
		int pos;
		if (wordValidator.validate(word, pos) == QValidator::Acceptable) {
			model->setData(index, editor->property(n), Qt::EditRole);
		}
	}
}
