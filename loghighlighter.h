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


#ifndef LOGHIGHLIGHTER_H
#define LOGHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>
#include <QColor>

class QTextDocument;

class LogHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LogHighlighter(QTextDocument *parent = 0);
    QColor ColorStandard, ColorFile, ColorError, ColorWarning;

protected:
    void highlightBlock(const QString &text);
};


#endif
