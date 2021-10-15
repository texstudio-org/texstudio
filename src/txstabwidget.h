#ifndef Header_TxStab_Widget
#define Header_TxStab_Widget

#include "mostQtHeaders.h"

class LatexEditorView;

class TxsTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit TxsTabWidget(QWidget *parent = 0);
	void moveTab(int from, int to);

	QList<LatexEditorView *> editors() const;
	bool containsEditor(LatexEditorView *edView) const;

	LatexEditorView *currentEditor() const;
	void setCurrentEditor(LatexEditorView *edView);
	LatexEditorView *editorAt(QPoint p);
	void setActive(bool active);

	bool isEmpty() const;
	bool currentEditorViewIsFirst() const;
	bool currentEditorViewIsLast() const;

signals:
	void tabMoved(int from, int to);
	void tabBarContextMenuRequested(QPoint point);
	void editorAboutToChangeByTabClick(LatexEditorView *from, LatexEditorView *to);
	void closeEditorRequested(LatexEditorView *edView);
	void currentEditorChanged();
	void activationRequested();

public slots:
	void gotoNextDocument();
	void gotoPrevDocument();
	void gotoFirstDocument();
	void gotoLastDocument();

	// low level public functions
	void insertEditor(LatexEditorView *edView, int pos = -1 /*append*/, bool asCurrent = true);
	void removeEditor(LatexEditorView *edView);

protected:
	LatexEditorView *editorAt(int index);
	void connectEditor(LatexEditorView *edView);
	void disconnectEditor(LatexEditorView *edView);
	void updateTab(int index);
protected slots:
	void updateTabFromSender();

private slots:
	void currentTabAboutToChange(int from, int to);
	void onTabCloseRequest(int i);

private:
	bool m_active;
};
Q_DECLARE_METATYPE(TxsTabWidget *)


class ChangeAwareTabBar : public QTabBar
{
	Q_OBJECT
public:

signals:
	void currentTabAboutToChange(int from, int to);
	void tabLeftClicked();
	void middleMouseButtonPressed(int tabNr);

protected:
	virtual void mousePressEvent(QMouseEvent *event);
};

#endif // TXSTABWIDGET_H
