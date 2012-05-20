#include "txstabwidget.h"
#include "smallUsefulFunctions.h"

TxsTabWidget::TxsTabWidget(QWidget *parent) :
		QTabWidget(parent)
{
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
