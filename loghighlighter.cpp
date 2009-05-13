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


#include <QtGui>

#include "loghighlighter.h"

LogHighlighter::LogHighlighter(QTextDocument *parent)
		: QSyntaxHighlighter(parent) {
	ColorStandard = QColor(0x00, 0x00, 0x00);
	ColorFile = QColor(0x00,0x80, 0x00);
	ColorError=QColor(0xFF, 0x00, 0x00);
	ColorWarning=QColor(0x00, 0x00, 0xCC);
}

void LogHighlighter::highlightBlock(const QString &text) {
	QRegExp rxLatexError("! (.*)");
	QRegExp rxBadBox("(Over|Under)(full \\\\[hv]box .*)");
	QRegExp rxWarning("(((! )?(La|pdf)TeX)|Package) .*Warning.*:(.*)");
	if (rxLatexError.indexIn(text)!=-1) {
		setFormat(0, text.length(),ColorError);
	} else if ((rxBadBox.indexIn(text)!=-1) || (rxWarning.indexIn(text)!=-1)) {
		setFormat(0, text.length(),ColorWarning);
	} else if (text.indexOf(".tex",0)!=-1 && !text.startsWith("Error:")) {
		setFormat(0, text.length(),ColorFile);
	}
}
