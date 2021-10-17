/***************************************************************************
 *   copyright       : (C) 2008 by Benito van der Zander                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_SmallUsefulFunctions
#define Header_SmallUsefulFunctions

#include "mostQtHeaders.h"
#include "qglobal.h"

/*! \file smallUsefulFunctions.h
 * Defines helper functions for various purposes
 * - helper functions for latex parsing
 * - helper functions for character substitution
 * - helper functions for setting-up commandlist to interpret commands
 */

// subgroups of utility functions:
#include "utilsUI.h"
#include "utilsSystem.h"
#include "utilsVersion.h"


// evaluates to j if i < 0
//              i if j < 0
//              qMin(i, j) if i, j >= 0
// Usage example:
// find the first occuence of either A or B in a string
// pos = indexMin(s.indexOf('A'), s.indexOf('B'))
// pos is negative if s does not contain neither A nor B

constexpr const int & indexMin(const int & a,const int & b){
    return (a < 0 || b < 0) ? qMax(a,b) : qMin(a,b);
}


struct CommandArgument {
	bool isOptional;
	int number;
	QString value;
};
Q_DECLARE_METATYPE( CommandArgument )

//void txs_assert(const char *assertion, const char *file, int line);


class LatexCompleterConfig;

typedef QString (QObject::*StringToStringCallback)(const QString &) ;


/// removes special latex characters
QString latexToPlainWord(const QString &word);
QString latexToPlainWordwithReplacementList(const QString &word, QMap<QString, QString> &replacementList );
/// replaces character with corresponding LaTeX commands
QString textToLatex(const QString &text);
QString latexToText(QString s);

QStringList joinLinesExceptCommentsAndEmptyLines(const QStringList &lines);
QStringList splitLines(const QStringList &lines, int maxCharPerLine, const QRegularExpression &breakChars);

/// compares two strings locale aware
bool localeAwareLessThan(const QString &s1, const QString &s2);

/// true for characters that are valid in latex command names, e.g. \section*
inline bool isCommandChar(const QChar &c)
{
	return c.isLetter() || c == '*';
}
/// returns the position of the first non-whitespace at or after pos
int getCommand(const QString &line, QString &outCmd, int pos = 0);
QList< CommandArgument > getCommandOptions(const QString &line, int pos = 0, int *posBehind = 0);
QString getParamItem(const QString &line, int pos, bool stopAtWhiteSpace = false);

QString trimLeft(const QString &s);
QString trimRight(const QString &s);

/// find token (e.g. \label \input \section and return content (\section{content})
QString findToken(const QString &line, const QString &token);
QString findToken(const QString &line, const QString &token, int &start);
QString findToken(const QString &line, QRegExp &token);
/// find token (e.g. \label \input \section and return content (\newcommand{name}[arg]), returns true if outName!=""
bool findTokenWithArg(const QString &line, const QString &token, QString &outName, QString &outArg);


/// generate multiple times used regexpression
QRegExp generateRegExp(const QString &text, const bool isCase, const bool isWord, const bool isRegExp);

QStringList regExpFindAllMatches(const QString &searchIn, const QRegExp &regexp, int cap = 0);
QList<int> indicesOf(const QString &line, const QString &word, Qt::CaseSensitivity cs = Qt::CaseSensitive);
QList<int> indicesOf(const QString &line, const QRegularExpression &rx);

/// add Environment to QNFA DOM
void addEnvironmentToDom(QDomDocument &doc, const QString &EnvironName, const QString &EnvironMode, bool completeParentheses=true);
void addStructureCommandsToDom(QDomDocument &doc , const QHash<QString, QSet<QString> > &possibleCommands);

QString intListToStr(const QList<int> &ints);
QList<int> strToIntList(const QString &s);

QString enquoteStr(const QString &s);
QString dequoteStr(const QString &s);

QString quotePath(const QString &s);
QString removeQuote(const QString &s);
QString removePathDelim(const QString &s);
QString removeAccents(const QString &s);
QString makeLatexLabel(const QString &s);

QStringList tokenizeCommandLine(const QString &commandLine);
QStringList extractOutputRedirection(const QStringList &commandArgs, QString &stdOut, QString &stdErr);

uint joinUnicodeSurrogate(const QChar &highSurrogate, const QChar &lowSurrogate);

/*! encode image as text for html
 * This is used to generate images for tooltips.
 */
QString getImageAsText(const QPixmap &AImage, const int w = -1);
void showTooltipLimited(QPoint pos, QString text, int relatedWidgetWidth = 0);
QString truncateLines(const QString &s, int maxLines);

bool addMostRecent(const QString &item, QStringList &mostRecentList, int maxLength);

#endif
