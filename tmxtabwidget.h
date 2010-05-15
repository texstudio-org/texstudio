#ifndef TMXTABWIDGET_H
#define TMXTABWIDGET_H

#include <QTabWidget>
#include <QTabBar>

class TmxTabWidget : public QTabWidget
{
Q_OBJECT
public:
    explicit TmxTabWidget(QWidget *parent = 0);
    void moveTab(int from,int to);

signals:
    void tabMoved(int from,int to);

public slots:

};

#endif // TMXTABWIDGET_H
