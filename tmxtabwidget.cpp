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
    if (hasAtLeastQt(4,5)){
        const QTabBar* tb=tabBar();
        disconnect(tb,SIGNAL(tabMoved(int,int)),this,SIGNAL(tabMoved(int,int)));
        tabBar()->moveTab(from,to);
        connect(tb,SIGNAL(tabMoved(int,int)),this,SIGNAL(tabMoved(int,int)));
    }
}
