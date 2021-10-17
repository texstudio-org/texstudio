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


#ifndef Header_LogHighlighter
#define Header_LogHighlighter

#include "mostQtHeaders.h"

class QTextDocument;

class LogHighlighter : public QSyntaxHighlighter {
	Q_OBJECT

public:
	LogHighlighter(QTextDocument *parent = 0);
	QColor ColorFile;

protected:
	void highlightBlock(const QString &text);
};


#endif
