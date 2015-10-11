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

#include "loghighlighter.h"
#include "latexoutputfilter.h"

LogHighlighter::LogHighlighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
	ColorFile = QColor(0x00, 0x80, 0x00);
}

void LogHighlighter::highlightBlock(const QString &text)
{
	static QRegExp rxLatexError("\\s*! (.*)");
	static QRegExp rxBadBox("\\s*(Over|Under)(full \\\\[hv]box .*)");
	static QRegExp rxWarning("\\s*(((! )?(La|pdf|Lua)TeX)|Package) .*Warning.*:(.*)");
	static QRegExp rxOnlyStars("\\*+\\s*");
	static QRegExp rxOnlyExclMarks("!+\\s*");
	static QRegExp rxExclDots("!\\.+\\s*");
	static QRegExp rxOnlyDots("\\.+\\s*");
	if (rxLatexError.exactMatch(text) || text == "! " || rxOnlyExclMarks.exactMatch(text) || rxExclDots.exactMatch(text)) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_ERROR));
	} else if (rxBadBox.exactMatch(text)) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_BADBOX));
	} else if (rxWarning.exactMatch(text) || text.startsWith("* ") || rxOnlyStars.exactMatch(text)) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_WARNING));
	} else if (text.startsWith(". ") || rxOnlyDots.exactMatch(text)) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_INFO));
	} else if (text.indexOf(".tex", 0) != -1 && !text.startsWith("Error:")) {
		setFormat(0, text.length(), ColorFile);
	}
}
