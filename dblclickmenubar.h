#ifndef DBLCLICKMENUBAR_H
#define DBLCLICKMENUBAR_H

#include <QMenuBar>

class DblClickMenuBar : public QMenuBar
{
	Q_OBJECT
public:
	explicit DblClickMenuBar(QWidget *parent = 0);
	
signals:
	void doubleClicked(); // emitted when double clicking empty part of menu bar
public slots:

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
};

#endif // DBLCLICKMENUBAR_H
