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

#include "logeditor.h"
#include "configmanager.h"

LogEditor::LogEditor(QWidget *parent) : QTextEdit(parent)
{
//setToolTip(tr("Click to jump to the line"));
	highlighter = new LogHighlighter(document());
	ConfigManagerInterface *config = ConfigManager::getInstance();
	QVariant fontFamily = config->getOption("LogView/FontFamily");
	if (fontFamily.isValid()) setFontFamily(fontFamily.toString());
	bool ok;
	int fontSize = config->getOption("LogView/FontSize").toInt(&ok);
	if (ok && fontSize > 0) setFontPointSize(fontSize);

	UtilsUi::enableTouchScrolling(this);
}

LogEditor::~LogEditor()
{
}

void LogEditor::wheelEvent(QWheelEvent *event)
{
	ConfigManagerInterface *config = ConfigManager::getInstance();
	if (!config->getOption("Editor/Mouse Wheel Zoom").toBool()) {
		event->setModifiers(event->modifiers() & ~Qt::ControlModifier);
	}
	QTextEdit::wheelEvent(event);
}

void LogEditor::insertLine(const QString &l)
{
    /*if (l.endsWith("\n")) append(l);
    else append(l + "\n");*/
    append(l);
}

void LogEditor::setCursorPosition(int para, int index)
{
	QTextCursor cur = textCursor();
	int i = 0;
	QTextBlock p = document()->begin();
	while (p.isValid()) {
		if (para == i) break;
		i++;
		p = p.next();
	}
	int pos = p.position();
	cur.movePosition(QTextCursor::End);
	setTextCursor(cur);
	cur.setPosition(pos + index, QTextCursor::MoveAnchor);
	setTextCursor(cur);
	ensureCursorVisible();
}

void LogEditor::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
	emit clickOnLogLine(textCursor().blockNumber());
	/*QTextEdit::mousePressEvent(e);
	QString content=textCursor().block().text();
	int Start, End;
	bool ok;
	QString s;
	QString line="";
	//// l. ///
	s = content;
	Start=End=0;
	Start=s.indexOf(QRegExp("l.[0-9]"), End);
	if (Start!=-1) {
		Start=Start+2;
		s=s.mid(Start,s.length());
		End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
		if (End!=-1)
			line=s.mid(0,End);
		else
			line=s.mid(0,s.length());
	};
	//// line ///
	s = content;
	Start=End=0;
	Start=s.indexOf(QRegExp("line [0-9]"), End);
	if (Start!=-1) {
		Start=Start+5;
		s=s.mid(Start,s.length());
		End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
		if (End!=-1)
			line=s.mid(0,End);
		else
			line=s.mid(0,s.length());
	};
	//// lines ///
	s = content;
	Start=End=0;
	Start=s.indexOf(QRegExp("lines [0-9]"), End);
	if (Start!=-1) {
		Start=Start+6;
		s=s.mid(Start,s.length());
		End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
		if (End!=-1)
			line=s.mid(0,End);
		else
			line=s.mid(0,s.length());
	};
	int l=line.toInt(&ok,10)-1;
	if (ok) {
		emit clickonline(l);
	}
	*/
}

void LogEditor::paintEvent(QPaintEvent *event)
{
	QRect rect = cursorRect();
	rect.setX(0);
	rect.setWidth(viewport()->width());
	QPainter painter(viewport());
	QBrush brush = palette().base();
	brush.setColor(UtilsUi::mediumLightColor(brush.color(), 110));
	painter.fillRect(rect, brush);
	painter.end();
	QTextEdit::paintEvent(event);
}
