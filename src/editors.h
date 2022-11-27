#ifndef Header_Editors
#define Header_Editors

#include "mostQtHeaders.h"

class TxsTabWidget;
class LatexEditorView;
class EditorChangeProxy;

class Editors : public QWidget
{
	Q_OBJECT
public:
    explicit Editors(QWidget *parent = nullptr);
	void addTabWidget(TxsTabWidget *w);
	void addEditor(LatexEditorView *edView, bool asCurrent = true);
	void insertEditor(LatexEditorView *edView, int index, bool asCurrent = true);
	enum Position {AbsoluteFront, AbsoluteEnd, GroupFront, GroupEnd};
	void moveEditor(LatexEditorView *edView, Position pos);
public slots:
	void requestCloseEditor(LatexEditorView *edView);
	void removeEditor(LatexEditorView *edView);
protected:
    void insertEditor(LatexEditorView *edView, TxsTabWidget *tabWidget=nullptr /*current*/, int pos=-1 /*append*/, bool asCurrent = true);
	void removeEditor(LatexEditorView *edView, TxsTabWidget *tabWidget);
public:
	bool containsEditor(LatexEditorView *edView) const;

	TxsTabWidget * currentTabWidget() const;

	LatexEditorView * currentEditor() const;
	void setCurrentEditor(LatexEditorView *edView, bool setFocus = true);

	QList<LatexEditorView *> editors();
	int tabGroupIndexFromEditor(LatexEditorView *edView) const;
	void moveToTabGroup(LatexEditorView *edView, int groupIndex, int targetIndex);
    void moveAllToGroupZeroifEmpty();
    bool getSplitVertical();

signals:
	void currentEditorChanged();
	void editorAboutToChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void closeCurrentEditorRequested();
	void listOfEditorsChanged();
	void editorsReordered();

public slots:
	void setCurrentEditorFromAction();
	void setCurrentEditorFromSender();
	void closeEditorFromAction();
	void closeOtherEditorsFromAction();
	void toggleReadOnlyFromAction();
	bool activateNextEditor();
	bool activatePreviousEditor();
    void changeSplitOrientation();

protected slots:
	void setCurrentGroup(int index);
	bool activateTabWidgetFromSender();
	void tabBarContextMenu(const QPoint &point);
	void onEditorChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void moveToOtherTabGroup();
	void moveAllToOtherTabGroup();
	void moveAllOthersToOtherTabGroup();
	void moveToTabGroup(LatexEditorView *edView, TxsTabWidget *target, int targetIndex);

protected:
	TxsTabWidget *tabWidgetFromEditor(LatexEditorView *edView) const;

private:
	QSplitter *splitter;
	QList<TxsTabWidget *> tabGroups;
	int currentGroupIndex;

	EditorChangeProxy *changes;
};



class EditorChangeProxy : public QObject
{
	Q_OBJECT
public:
	EditorChangeProxy(Editors *e);

	bool block();
	void release();
signals:
	void currentEditorChanged();
	void listOfEditorsChanged();
public slots:
	void currentEditorChange();
	void listOfEditorsChange();
private:
	Editors *editors;
	LatexEditorView *currentEditorAtBlock;
	QList<LatexEditorView *> listOfEditorsAtBlock;
	bool blocked;
};

#endif // EDITORS_H
