#ifndef TXSTABWIDGET_H
#define TXSTABWIDGET_H

#include "mostQtHeaders.h"

class TxsTabWidget : public QTabWidget
{
Q_OBJECT
public:
    explicit TxsTabWidget(QWidget *parent = 0);
    void moveTab(int from,int to);

signals:
    void tabMoved(int from,int to);
	void tabBarContextMenuRequested(QPoint point);

public slots:

};

#endif // TXSTABWIDGET_H
