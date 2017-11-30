#include "dblclickmenubar.h"

#include "QMouseEvent"

DblClickMenuBar::DblClickMenuBar(QWidget *parent) :
	QMenuBar(parent)
{
}

void DblClickMenuBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (!actionAt(event->pos())) {
		emit doubleClicked();
		return;
	}
	QMenuBar::mouseDoubleClickEvent(event);
}
