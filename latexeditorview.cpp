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

#include "latexeditorview.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextBlock>

LatexEditorView::LatexEditorView(QWidget *parent,QFont & efont,bool line, QColor colMath, QColor colCommand, QColor colKeyword) : QWidget(parent)
{
QVBoxLayout* mainlay = new QVBoxLayout( this );
mainlay->setSpacing(0);
mainlay->setMargin(0);

QFrame *frame=new QFrame(this);
frame->setLineWidth(1);
frame->setFrameShape(QFrame::StyledPanel);
frame->setFrameShadow(QFrame::Sunken);
mainlay->addWidget(frame);

editor=new LatexEditor(frame,efont,colMath,colCommand,colKeyword);
m_lineNumberWidget = new LineNumberWidget( editor, frame);
m_lineNumberWidget->setFont(efont);
QFontMetrics fm( efont );
m_lineNumberWidget->setFixedWidth( fm.width( "00000" ) + 14 );
QHBoxLayout* lay = new QHBoxLayout( frame );
lay->setSpacing(0);
lay->setMargin(0);
lay->addWidget( m_lineNumberWidget );
lay->addWidget( editor );
setFocusProxy( editor );
setLineNumberWidgetVisible(line);

findwidget=new FindWidget(this);
mainlay->addWidget(findwidget);
findwidget->SetEditor(editor);
findwidget->hide();
}

LatexEditorView::~LatexEditorView()
{
}

void LatexEditorView::setLineNumberWidgetVisible( bool b )
{
    if( b ){
	m_lineNumberWidget->show();
    } else {
	m_lineNumberWidget->hide();
    }
}

void LatexEditorView::changeSettings(QFont & new_font,bool line)
{
  editor->changeFont(new_font);
  m_lineNumberWidget->setFont(new_font);
  QFontMetrics fm( new_font );
  m_lineNumberWidget->setFixedWidth( fm.width( "00000" ) + 14 );
  setLineNumberWidgetVisible(line);
}

