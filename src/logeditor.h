/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_LogEditor
#define Header_LogEditor

#include "mostQtHeaders.h"

#include "loghighlighter.h"

class LogEditor : public QTextEdit
{
	Q_OBJECT

public:
	LogEditor(QWidget *parent);
	~LogEditor();

	void wheelEvent(QWheelEvent *event);

public slots:
	void insertLine(const QString &l);
	void setCursorPosition(int parag, int index);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *event);

signals:
	void clickOnLogLine(int l); //0 based

private:
	LogHighlighter *highlighter;
};

#endif
