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


#ifndef LATEXHIGHLIGHTER_H
#define LATEXHIGHLIGHTER_H


#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>
#include <QColor>
#include <QTextBlockUserData>

class QTextDocument;

class LatexHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LatexHighlighter(QTextDocument *parent = 0);
    QColor ColorStandard, ColorComment, ColorMath, ColorCommand, ColorKeyword;
    QStringList KeyWords;
public slots:
void setColors(QColor colMath, QColor colCommand, QColor colKeyword);
protected:
    void highlightBlock(const QString &text);
};


#endif
