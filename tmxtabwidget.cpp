#include "tmxtabwidget.h"
#include "smallUsefulFunctions.h"

TmxTabWidget::TmxTabWidget(QWidget *parent) :
		QTabWidget(parent)
{
	if (hasAtLeastQt(4,5)){
		const QTabBar* tb=tabBar();
		connect(tb,SIGNAL(tabMoved(int,int)),this,SIGNAL(tabMoved(int,int)));
	}
}

void TmxTabWidget::moveTab(int from,int to){
	Q_UNUSED(to)
	QString text=tabText(from);
	QWidget *wdg=widget(from);
	removeTab(from);
	insertTab(0,wdg,text);
	setCurrentIndex(0);
}
