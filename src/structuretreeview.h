#ifndef STRUCTURETREEVIEW_H
#define STRUCTURETREEVIEW_H

#include "mostQtHeaders.h"


struct StructureEntry;
class Editors;
class LatexDocuments;
class LatexDocument;
class ConfigManager;


class StructureTreeView : public QTreeView
{
	Q_OBJECT
public:
	// TODO: We've still got dependencies to Editors, LatexDocuments, ConfigManager
	// from the refactoring. Can we get rid of them?
	explicit StructureTreeView(Editors *edts, const LatexDocuments &docs, const ConfigManager &config, QWidget *parent = Q_NULLPTR);

signals:
	// all these request signals are used to delegate the actual action
	void requestCloseDocument(LatexDocument *document);
	void requestToggleMasterDocument(LatexDocument *document);
	void requestOpenAllRelatedDocuments(LatexDocument *document);
	void requestCloseAllRelatedDocuments(LatexDocument *document);
	void requestGotoLine(LatexDocument *document, int line, int col);
	void requestOpenExternalFile(const QString &filename);
	void insertText(const QString &text);
	void findLabelUsages(LatexDocument *doc, const QString &labelText);
	void createLabelForStructureEntry(const StructureEntry *entry);

protected slots:
	void showContextMenu(const QPoint &point);
	void expandSubitems();
	void collapseSubitems();
	void expandAllDocuments();
	void collapseAllDocuments();

	void closeDocument();
	void toggleMasterDocument();
	void openAllRelatedDocuments();
	void closeAllRelatedDocuments();
	void gotoLineFromAction();
	void openExternalFileFromAction();

	void moveDocumentToFront();
	void moveDocumentToEnd();
	void toggleSingleDocMode();
	void showInGraphicalShell_();

	void insertTextFromAction();
	void findLabelUsagesFromAction();
	void createLabelFromAction();

	// TODO: most logic of the following edit operations should probably be moved to LatexDocument or LatexEditorView
	void editSectionCopy();
	void editSectionCut();
	void editSectionPasteAfter();
	void editSectionPasteBefore();
	void editIndentSection();
	void editUnIndentSection();

	void copyFileName();
	void copyFilePath();

protected:
	LatexDocument *contextEntryToDoc();

private:
	StructureEntry *contextEntry;
	QModelIndex contextIndex;

	Editors *editors;
	const LatexDocuments &documents;
	const ConfigManager &configManager;

};


#endif // STRUCTURETREEVIEW_H
