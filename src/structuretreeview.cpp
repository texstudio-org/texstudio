#include "structuretreeview.h"
#include "latexstructure.h"
#include "latexdocument.h"
#include "configmanager.h"
#include "utilsUI.h"
#include "utilsSystem.h"
#include "editors.h"
#include "latexeditorview.h"



StructureTreeView::StructureTreeView(Editors *edts, const LatexDocuments &docs, const ConfigManager &config, QWidget *parent) :
	QTreeView(parent),
	editors(edts),
	documents(docs),
	configManager(config)
{
	header()->hide();
	setObjectName("StructureTree");
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
	UtilsUi::enableTouchScrolling(this);

	if (configManager.indentationInStructure > 0)
		setIndentation(configManager.indentationInStructure);
}

void StructureTreeView::showContextMenu(const QPoint &point)
{
	//StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	contextIndex = indexAt(point);
	contextEntry = LatexDocumentsModel::indexToStructureEntry(contextIndex);
	if (!contextEntry) return;
	if (contextEntry->type == StructureEntry::SE_DOCUMENT_ROOT) {
		QMenu menu;
		if (contextEntry->document != documents.masterDocument) {
			menu.addAction(tr("Close document"), this, SLOT(closeDocument()));
			menu.addAction(tr("Set as explicit root document"), this, SLOT(toggleMasterDocument()));
			menu.addAction(tr("Open all related documents"), this, SLOT(openAllRelatedDocuments()));
			menu.addAction(tr("Close all related documents"), this, SLOT(closeAllRelatedDocuments()));
		} else
			menu.addAction(tr("Remove explicit root document role"), this, SLOT(toggleMasterDocument()));
		if (documents.model->getSingleDocMode()) {
			menu.addAction(tr("Show all open documents in this tree"), this, SLOT(toggleSingleDocMode()));
		} else {
			menu.addAction(tr("Show only current document in this tree"), this, SLOT(toggleSingleDocMode()));
		}
		menu.addSeparator();
		menu.addAction(tr("Move document to &front"), this, SLOT(moveDocumentToFront()));
		menu.addAction(tr("Move document to &end"), this, SLOT(moveDocumentToEnd()));
		menu.addSeparator();
		menu.addAction(tr("Expand Subitems"), this, SLOT(expandSubitems()));
		menu.addAction(tr("Collapse Subitems"), this, SLOT(collapseSubitems()));
		menu.addAction(tr("Expand all documents"), this, SLOT(expandAllDocuments()));
		menu.addAction(tr("Collapse all documents"), this, SLOT(collapseAllDocuments()));
		menu.addSeparator();
		menu.addAction(msgGraphicalShellAction(), this, SLOT(showInGraphicalShell_()));
		menu.exec(mapToGlobal(point));
		return;
	}
	if (!contextEntry->parent) return;
	if (contextEntry->type == StructureEntry::SE_LABEL) {
		QMenu menu;
		menu.addAction(tr("Insert"), this, SLOT(insertTextFromAction()))->setData(contextEntry->title);
		menu.addAction(tr("Insert as %1").arg("\\ref{...}"), this, SLOT(insertTextFromAction()))->setData(QString("\\ref{%1}").arg(contextEntry->title));
		menu.addAction(tr("Insert as %1").arg("\\pageref{...}"), this, SLOT(insertTextFromAction()))->setData(QString("\\pageref{%1}").arg(contextEntry->title));
		menu.addSeparator();
		QAction *act = menu.addAction(tr("Find Usages"), this, SLOT(findLabelUsagesFromAction()));
		act->setData(contextEntry->title);
		act->setProperty("doc", QVariant::fromValue<LatexDocument *>(contextEntry->document));
		menu.exec(mapToGlobal(point));
		return;
	}
	if (contextEntry->type == StructureEntry::SE_SECTION) {
		QMenu menu(this);

		StructureEntry *labelEntry = LatexDocumentsModel::labelForStructureEntry(contextEntry);
		if (labelEntry) {
			menu.addAction(tr("Insert Label"), this, SLOT(insertTextFromAction()))->setData(labelEntry->title);
			foreach (QString refCmd, configManager.referenceCommandsInContextMenu.split(",")) {
				refCmd = refCmd.trimmed();
				if (!refCmd.startsWith('\\')) continue;
				menu.addAction(QString(tr("Insert %1 to Label", "autoreplaced, e.g.: Insert \\ref to Label").arg(refCmd)), this, SLOT(insertTextFromAction()))->setData(QString("%1{%2}").arg(refCmd).arg(labelEntry->title));
			}
			menu.addSeparator();
		} else {
			menu.addAction(tr("Create Label"), this, SLOT(createLabelFromAction()))->setData(QVariant::fromValue(contextEntry));
			menu.addSeparator();
		}

		menu.addAction(tr("Copy"), this, SLOT(editSectionCopy()));
		menu.addAction(tr("Cut"), this, SLOT(editSectionCut()));
		menu.addAction(tr("Paste Before"), this, SLOT(editSectionPasteBefore()));
		menu.addAction(tr("Paste After"), this, SLOT(editSectionPasteAfter()));
		menu.addSeparator();
		menu.addAction(tr("Indent Section"), this, SLOT(editIndentSection()));
		menu.addAction(tr("Unindent Section"), this, SLOT(editUnIndentSection()));
		if (!contextEntry->children.isEmpty()) {
			menu.addSeparator();
			menu.addAction(tr("Expand Subitems"), this, SLOT(expandSubitems()));
			menu.addAction(tr("Collapse Subitems"), this, SLOT(collapseSubitems()));
		}
		menu.exec(mapToGlobal(point));
		return;
	}
	if (contextEntry->type == StructureEntry::SE_MAGICCOMMENT) {
		QMenu menu;
		menu.addAction(tr("Go to Definition"), this, SLOT(gotoLineFromAction()))->setData(QVariant::fromValue(contextEntry));
		menu.exec(mapToGlobal(point));
		return;
	}
	if (contextEntry->type == StructureEntry::SE_INCLUDE) {
		QMenu menu;
		menu.addAction(tr("Open Document"), this, SLOT(openExternalFileFromAction()))->setData(QVariant::fromValue(contextEntry));
		menu.addAction(tr("Go to Definition"), this, SLOT(gotoLineFromAction()))->setData(QVariant::fromValue(contextEntry));
		menu.exec(mapToGlobal(point));
		return;
	}
}

void StructureTreeView::expandSubitems()
{
	if (!contextEntry)
		return;
	UtilsUi::setSubtreeExpanded(this, contextIndex, true);
    contextEntry = nullptr;
}

void StructureTreeView::collapseSubitems()
{
	if (!contextEntry)
		return;
	UtilsUi::setSubtreeExpanded(this, contextIndex, false);
    contextEntry = nullptr;
}

void StructureTreeView::expandAllDocuments()
{
	UtilsUi::setSubtreeExpanded(this, rootIndex(), true);
}

void StructureTreeView::collapseAllDocuments()
{
	UtilsUi::setSubtreeExpanded(this, rootIndex(), false);
}

LatexDocument *StructureTreeView::contextEntryToDoc()
{
	if (!contextEntry) return Q_NULLPTR;
	LatexDocument *doc = contextEntry->document;
	contextEntry = Q_NULLPTR;
	return doc;
}

void StructureTreeView::closeDocument()
{
	LatexDocument *document = contextEntryToDoc();
	if (!document) return;
	emit requestCloseDocument(document);
}

void StructureTreeView::toggleMasterDocument()
{
	LatexDocument *document = contextEntryToDoc();
	if (!document) return;
	emit requestToggleMasterDocument(document);
}

void StructureTreeView::openAllRelatedDocuments()
{
	LatexDocument *document = contextEntryToDoc();
	if (!document) return;
	emit requestOpenAllRelatedDocuments(document);
}

void StructureTreeView::closeAllRelatedDocuments()
{
	LatexDocument *document = contextEntryToDoc();
	if (!document) return;
	emit requestCloseAllRelatedDocuments(document);
}

void StructureTreeView::gotoLineFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	StructureEntry *entry = qvariant_cast<StructureEntry *>(action->data());

	if (!entry || !entry->document) return;
	LatexDocument *doc = entry->document;
	QDocumentLineHandle *dlh = entry->getLineHandle();
	int lineNr = -1;
	if ((lineNr = doc->indexOf(dlh)) >= 0) {
		emit requestGotoLine(entry->document, lineNr, 0);
	}
}

void StructureTreeView::openExternalFileFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	StructureEntry *entry = qvariant_cast<StructureEntry *>(action->data());
	emit requestOpenExternalFile(entry->title);
}

void StructureTreeView::moveDocumentToFront()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
	if (!entry || entry->type != StructureEntry::SE_DOCUMENT_ROOT) return;
	editors->moveEditor(entry->document->getEditorView(), Editors::AbsoluteFront);
}

void StructureTreeView::moveDocumentToEnd()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
	if (!entry || entry->type != StructureEntry::SE_DOCUMENT_ROOT) return;
	editors->moveEditor(entry->document->getEditorView(), Editors::AbsoluteEnd);
}

void StructureTreeView::toggleSingleDocMode()
{
	bool mode = documents.model->getSingleDocMode();
	documents.model->setSingleDocMode(!mode);
}

void StructureTreeView::showInGraphicalShell_()
{
	LatexDocument *document = contextEntryToDoc();
	if (!document) return;
	showInGraphicalShell(this, document->getFileName());
}

void StructureTreeView::insertTextFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	emit insertText(action->data().toString());
}

void StructureTreeView::findLabelUsagesFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;

	QString labelText = action->data().toString();
	LatexDocument *doc = action->property("doc").value<LatexDocument *>();

	emit findLabelUsages(doc, labelText);
}

void StructureTreeView::createLabelFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	StructureEntry *entry = qvariant_cast<StructureEntry *>(action->data());
	emit createLabelForStructureEntry(entry);
}

/*!
 * context menu action: Select the selected section and copy it to the clipboard.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editSectionCopy()
{
	// called by action
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if(!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if(!edView) return;
	editors->setCurrentEditor(edView);
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	edView->editor->setCursorPosition(sel.startLine, 0);
	QDocumentCursor cur = edView->editor->cursor();
	//m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	cur.setSilent(true);
	cur.movePosition(sel.endLine - sel.startLine - 1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	cur.movePosition(0, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	edView->editor->setCursor(cur);
	edView->editor->copy();
}

/*!
 * context menu action: Cut the selected section to the clipboard.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editSectionCut()
{
	// called by action
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if (!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
	editors->setCurrentEditor(edView);
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	edView->editor->setCursorPosition(sel.startLine, 0);
	QDocumentCursor cur = edView->editor->cursor();
	//m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	cur.setSilent(true);
	cur.movePosition(sel.endLine - sel.startLine - 1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	cur.movePosition(0, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	edView->editor->setCursor(cur);
	edView->editor->cut();
}

/*!
 * context menu action: Paste the clipboard contents before the selected section.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editSectionPasteBefore()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if (!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
	editors->setCurrentEditor(edView);

	int line = entry->getRealLineNumber();
	edView->editor->setCursorPosition(line, 0);
	edView->editor->insertText("\n");
	edView->editor->setCursorPosition(line, 0);
	edView->paste();
}

/*!
 * context menu action: Paste the clipboard contents after the selected section.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editSectionPasteAfter()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if (!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
	editors->setCurrentEditor(edView);
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	int line = sel.endLine;
	if (line >= edView->editor->document()->lines()) {
		edView->editor->setCursorPosition(line - 1, 0);
		QDocumentCursor c = edView->editor->cursor();
		c.movePosition(1, QDocumentCursor::End, QDocumentCursor::MoveAnchor);
		edView->editor->setCursor(c);
		edView->editor->insertText("\n");
	} else {
		edView->editor->setCursorPosition(line, 0);
		edView->editor->insertText("\n");
		edView->editor->setCursorPosition(line, 0);
	}
	edView->paste();
}

/*!
 * context menu action: Indent the selected section.
 * This replaces the sections and all its sub-sections with a lower heading, e.g.
 *     \section -> \subsection
 *     \chapter -> \section
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editIndentSection()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if (!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
	editors->setCurrentEditor(edView);
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	QStringList sectionOrder;
	sectionOrder << "\\subparagraph" << "\\paragraph" << "\\subsubsection" << "\\subsection" << "\\section" << "\\chapter";

	// replace sections
	QString line;
	QDocumentCursor cursor = edView->editor->cursor();
	for (int l = sel.startLine; l < sel.endLine; l++) {
		edView->editor->setCursorPosition(l, 0);
		cursor = edView->editor->cursor();
		line = edView->editor->cursor().line().text();
		QString m_old = "";
		foreach (const QString &elem, sectionOrder) {
			if (m_old != "") line.replace(elem, m_old);
			m_old = elem;
		}

		cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		edView->editor->setCursor(cursor);
		edView->editor->insertText(line);
	}
}

/*!
 * context menu action: Unindent the selected section.
 * This replaces the sections and all its sub-sections with a higher heading, e.g.
 *     \subsection -> \section
 *     \section -> \chapter
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void StructureTreeView::editUnIndentSection()
{
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(currentIndex());
    if (!entry) return;
	LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
	editors->setCurrentEditor(edView);
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	QStringList sectionOrder;
	sectionOrder << "\\chapter" << "\\section" << "\\subsection" << "\\subsubsection" << "\\paragraph" << "\\subparagraph" ;

	// replace sections
	QString line;
	QDocumentCursor cursor = edView->editor->cursor();
	for (int l = sel.startLine; l < sel.endLine; l++) {
		edView->editor->setCursorPosition(l, 0);
		cursor = edView->editor->cursor();
		line = edView->editor->cursor().line().text();
		QString m_old = "";
		foreach (const QString &elem, sectionOrder) {
			if (m_old != "") line.replace(elem, m_old);
			m_old = elem;
		}

		cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		edView->editor->setCursor(cursor);
		edView->editor->insertText(line);
	}
}
