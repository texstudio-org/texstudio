#ifndef EDITORS_H
#define EDITORS_H

#include "mostQtHeaders.h"

class TxsTabWidget;
class LatexEditorView;

class Editors : public QWidget
{
	Q_OBJECT
public:
	explicit Editors(QWidget *parent = 0);
	void addTabWidget(TxsTabWidget *w);
	void addEditor(LatexEditorView *edView, bool asCurrent = true);
	void insertEditor(LatexEditorView *edView, int index, bool asCurrent = true);
	enum Position {AbsoluteFront, AbsoluteEnd, GroupFront, GroupEnd};
	void moveEditor(LatexEditorView *edView, Position pos);
public slots:
	void removeEditor(LatexEditorView *edView);
protected:
	void insertEditor(LatexEditorView *edView, TxsTabWidget *tabWidget=0 /*current*/, int pos=-1 /*append*/, bool asCurrent = true);
	void removeEditor(LatexEditorView *edView, TxsTabWidget *tabWidget);
public:
	void closeEditor(LatexEditorView *edView);
	bool containsEditor(LatexEditorView *edView) const;

	TxsTabWidget * currentTabWidget() const;

	QString currentTabText() const;

	void updateDocumentStatus();

	LatexEditorView * currentEditor() const;
	void setCurrentEditor(LatexEditorView *edView);

	QList<LatexEditorView *> editors();

signals:
	void currentEditorChanged();
	void editorAboutToChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void closeCurrentEditorRequest();
	void listOfEditorsChanged();
	void editorsReordered();

public slots:
	void setCurrentEditorFromAction();
	void setCurrentEditorFromSender();
	void activateNextEditor();
	void activatePreviousEditor();

protected slots:
	void setCurrentGroup(int index);
	void activateTabWidgetFromSender();
	void onTabWidgetEditorChanged();
	void tabBarContextMenu(const QPoint &point);
	void onEditorChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void moveToOtherTabGroup();
	void moveToTabGroup(LatexEditorView *edView, TxsTabWidget *target, int targetIndex);
	void changeSplitOrientation();

protected:
	int tabGroupIndexFromEditor(LatexEditorView *edView) const;
	TxsTabWidget *tabWidgetFromEditor(LatexEditorView *edView) const;

private:
	QSplitter *splitter;
	QList<TxsTabWidget *> tabGroups;
	int currentGroupIndex;
};

#endif // EDITORS_H
