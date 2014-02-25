#ifndef TXSTABWIDGET_H
#define TXSTABWIDGET_H

#include "mostQtHeaders.h"

class LatexEditorView;

class TxsTabWidget : public QTabWidget
{
Q_OBJECT
public:
	explicit TxsTabWidget(QWidget *parent = 0);
	void moveTab(int from,int to);

	QList<LatexEditorView *> editors() const;
	bool containsEditor(LatexEditorView *edView) const;

	LatexEditorView* currentEditorView() const;
	void setCurrentEditor(LatexEditorView *edView);

signals:
	void tabMoved(int from,int to);
	void tabBarContextMenuRequested(QPoint point);
	void editorAboutToChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void closeCurrentEditorRequest();
	void currentEditorChanged();

public slots:
	void closeTab(LatexEditorView *edView);

	void gotoNextDocument();
	void gotoPrevDocument();

	// low level public functions
	void insertEditor(LatexEditorView *edView, int pos=-1 /*append*/, bool asCurrent=true);
	void removeEditor(LatexEditorView *edView);

private slots:
	void currentTabAboutToChange(int from, int to);
	void closeTab(int i);
};

class ChangeAwareTabBar : public QTabBar
{
Q_OBJECT
public:

signals:
	void currentTabAboutToChange(int from, int to);

protected:
	virtual void mousePressEvent(QMouseEvent *event);
};

#endif // TXSTABWIDGET_H
