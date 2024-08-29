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
    static QRegularExpression rxLatexError("^\\s*! (.*)$");
    static QRegularExpression rxBadBox("^\\s*(Over|Under)(full \\\\[hv]box .*)$");
    static QRegularExpression rxWarning("^\\s*(((! )?(La|pdf|Lua)TeX)|Package) .*Warning.*:(.*)$");
    static QRegularExpression rxOnlyStars("^\\*+\\s*$");
    static QRegularExpression rxOnlyExclMarks("^!+\\s*$");
    static QRegularExpression rxExclDots("^!\\.+\\s*$");
    static QRegularExpression rxOnlyDots("^\\.+\\s*$");
    if (text.indexOf(rxLatexError)==0 || text == "! " || text.indexOf(rxOnlyExclMarks)==0 || text.indexOf(rxExclDots)==0) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_ERROR));
    } else if (text.indexOf(rxBadBox)==0) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_BADBOX));
    } else if (text.indexOf(rxWarning)==0 || text.startsWith("* ") || text.indexOf(rxOnlyStars)==0) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_WARNING));
    } else if (text.startsWith(". ") || text.indexOf(rxOnlyDots)==0) {
		setFormat(0, text.length(), LatexLogEntry::textColor(LT_INFO));
	} else if (text.indexOf(".tex", 0) != -1 && !text.startsWith("Error:")) {
		setFormat(0, text.length(), ColorFile);
	}
}
