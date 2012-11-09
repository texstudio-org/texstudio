#include "txstabwidget.h"
#include "latexeditorview.h"
#include "smallUsefulFunctions.h"

TxsTabWidget::TxsTabWidget(QWidget *parent) :
		QTabWidget(parent)
{
	setFocusPolicy(Qt::ClickFocus);
	setContextMenuPolicy(Qt::PreventContextMenu);

	QTabBar *tb = new QTabBar();
	tb->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(tb, SIGNAL(customContextMenuRequested(QPoint)), this, SIGNAL(tabBarContextMenuRequested(QPoint)));
	setTabBar(tb);

	if (hasAtLeastQt(4,5)){
		setDocumentMode(true);
		const QTabBar* tb=tabBar();
		connect(tb,SIGNAL(tabMoved(int,int)),this,SIGNAL(tabMoved(int,int)));
	}
}

void TxsTabWidget::moveTab(int from,int to){
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

LatexEditorView *TxsTabWidget::currentEditorView() const {
	return qobject_cast<LatexEditorView *>(currentWidget());
}

void TxsTabWidget::setCurrentEditor(LatexEditorView *edView) {
	if (currentWidget() == edView)
		return;

	REQUIRE(indexOf(edView)>=0);
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


