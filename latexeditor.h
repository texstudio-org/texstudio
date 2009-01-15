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

#ifndef LATEXEDITOR_H
#define LATEXEDITOR_H

#include <QWidget>
#include <QString>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QCompleter>

#include "latexhighlighter.h"
#include "parenmatcher.h"

//class QCompleter;
//class ParenMatcher;
//class QTextBlock;


typedef  int UserBookmarkList[3];

class LatexEditor : public QTextEdit  {
   Q_OBJECT
public:
LatexEditor(QWidget *parent,QFont & efont, QColor colMath, QColor colCommand, QColor colKeyword);
~LatexEditor();
static void clearMarkerFormat(const QTextBlock &block, int markerId);
void gotoLine( int line );
bool search( const QString &expr, bool cs, bool wo, bool forward, bool startAtCursor );
void replace( const QString &r);
void commentSelection();
void uncommentSelection();
void indentSelection();
void unindentSelection();
void changeFont(QFont & new_font);
QString getEncoding();
void setEncoding(QString enc);
int getCursorPosition(int parag, int index);
void setCursorPosition(int para, int index);
void removeOptAlt();
int numoflines();
int linefromblock(const QTextBlock& p);
UserBookmarkList UserBookmark;
void selectword(int line, int col, QString word);
LatexHighlighter *highlighter;
void setCompleter(QCompleter *completer);
QCompleter *completer() const;
private:
QString encoding;
QString textUnderCursor() const;
QCompleter *c;
ParenMatcher *matcher;
private slots:
void checkSpellingWord();
void checkSpellingDocument();
void insertCompletion(const QString &completion);
protected:
void paintEvent(QPaintEvent *event);
void contextMenuEvent(QContextMenuEvent *e);
void keyPressEvent ( QKeyEvent * e );
void focusInEvent(QFocusEvent *e);
signals:
void spellme();
};

#endif
