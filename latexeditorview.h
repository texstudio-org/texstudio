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

#ifndef LATEXEDITORVIEW_H
#define LATEXEDITORVIEW_H

#include <qwidget.h>
#include <qfont.h>
#include <qcolor.h>
#include "latexeditor.h"
#include "linenumberwidget.h"
#include "findwidget.h"

class LatexEditorView : public QWidget  {
   Q_OBJECT
public: 
	LatexEditorView(QWidget *parent, QFont & efont,bool line, QColor colMath, QColor colCommand, QColor colKeyword);
	~LatexEditorView();
  LatexEditor *editor;
  FindWidget *findwidget;
  void changeSettings(QFont & new_font,bool line);
private:
  LineNumberWidget* m_lineNumberWidget;
  void setLineNumberWidgetVisible( bool );
};

#endif
