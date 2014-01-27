#include "txstabwidget.h"
#include "latexeditorview.h"
#include "smallUsefulFunctions.h"

TxsTabWidget::TxsTabWidget(QWidget *parent) :
	QTabWidget(parent)
{
	setFocusPolicy(Qt::ClickFocus);
	setContextMenuPolicy(Qt::PreventContextMenu);

	ChangeAwareTabBar *tb = new ChangeAwareTabBar();
	tb->setContextMenuPolicy(Qt::CustomContextMenu);
	tb->setUsesScrollButtons(true);
	connect(tb, SIGNAL(customContextMenuRequested(QPoint)), this, SIGNAL(tabBarContextMenuRequested(QPoint)));
	connect(tb, SIGNAL(currentTabAboutToChange(int,int)), this, SLOT(currentTabAboutToChange(int,int)));
	setTabBar(tb);

	if (hasAtLeastQt(4,5)){
		setDocumentMode(true);
		const QTabBar* tb=tabBar();
		connect(tb,SIGNAL(tabMoved(int,int)),this,SIGNAL(tabMoved(int,int)));
	}
}

void TxsTabWidget::moveTab(int from,int to) {
	int cur = currentIndex();
	QString text=tabText(from);
	QWidget *wdg=widget(from);
	removeTab(from);
	insertTab(to,wdg,text);
	if (cur == from) setCurrentIndex(to);
	else if (from < to && cur >= from && cur < to) 
		setCurrentIndex(cur-1);
	else if (to > from && cur >= from && cur < to) 
		setCurrentIndex(cur+1);
}

QList<LatexEditorView *> TxsTabWidget::editors() const {
	QList<LatexEditorView *> list;
	for (int i=0; i<count(); i++) {
		LatexEditorView *edView = qobject_cast<LatexEditorView *>(widget(i));
		Q_ASSERT(edView); // there should only be editors as tabs
		list.append(edView);
	}
	return list;
}

bool TxsTabWidget::containsEditor(LatexEditorView *edView) const{
	if (!edView) return false;
	return (indexOf(edView)>=0);
}

LatexEditorView *TxsTabWidget::currentEditorView() const {
	return qobject_cast<LatexEditorView *>(currentWidget());
}

void TxsTabWidget::setCurrentEditor(LatexEditorView *edView) {
	if (currentWidget() == edView)
		return;

	if (indexOf(edView)<0) {
		// catch calls in which editor is not a member tab.
		// TODO: such calls are deprecated as bad practice. We should avoid them in the long run. For the moment the fallback to do nothing is ok.
		qDebug() << "Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget";
#ifndef QT_NO_DEBUG
		txsWarning("Warning (deprecated call): TxsTabWidget::setCurrentEditor: editor not member of TxsTabWidget");
#endif
		return;
	}
	setCurrentWidget(edView);
}

void TxsTabWidget::gotoNextDocument() {
	if (count() <= 1) return;
	int cPage = currentIndex() + 1;
	if (cPage >= count()) setCurrentIndex(0);
	else setCurrentIndex(cPage);
}

void TxsTabWidget::gotoPrevDocument() {
	if (count() <= 1) return;
	int cPage = currentIndex() - 1;
	if (cPage < 0) setCurrentIndex(count() - 1);
	else setCurrentIndex(cPage);
}

void TxsTabWidget::currentTabAboutToChange(int from, int to) {
	LatexEditorView *edFrom = qobject_cast<LatexEditorView *>(widget(from));
	LatexEditorView *edTo = qobject_cast<LatexEditorView *>(widget(to));
	REQUIRE(edFrom);
	REQUIRE(edTo);
	emit editorAboutToChangeByTabClick(edFrom, edTo);
}

void TxsTabWidget::removeEditor(LatexEditorView *edView) {
	int i = indexOf(edView);
	if(i >= 0)
		removeTab(i);
}

void TxsTabWidget::insertEditor(LatexEditorView *edView, int pos, bool asCurrent) {
	Q_ASSERT(edView);
	insertTab(pos, edView, "?bug?");
	if (asCurrent) setCurrentEditor(edView);
}



void ChangeAwareTabBar::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		int toIndex = tabAt(event->pos());
		if (toIndex >= 0) {
			emit currentTabAboutToChange(currentIndex(), toIndex);
		}
	}
	QTabBar::mousePressEvent(event);
}
