/***************************************************************************
 *   copyright       : (C) 2008 by Benito van der Zander                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SMALLUSEFULFUNCTIONS_H
#define SMALLUSEFULFUNCTIONS_H

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

#include "codesnippet.h"
#include "latexparser/latextokens.h"
#include "latexparser/commanddescription.h"
class LatexParser;

//#inlcude "latexcompleter_config.h"

// evaluates to j if i < 0
//              i if j < 0
//              qMin(i, j) if i, j >= 0
// Usage example:
// find the first occuence of either A or B in a string
// pos = indexMin(s.indexOf('A'), s.indexOf('B'))
// pos is negative if s does not contain neither A nor B
#define indexMin(i, j) ((i < 0) ? qMax(i, j) : (j < 0) ? qMax(i, j) : qMin(i, j))


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
QStringList splitLines(const QStringList &lines, int maxCharPerLine, const QRegExp &breakChars);

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
int findCommandWithArgs(const QString &line, QString &cmd, QStringList &args, QList<int> *argStarts = 0, int offset = 0, bool parseComment = false);
int findCommandWithArgsFromTL(const TokenList &tl, Token &cmd, TokenList &args, int offset, bool parseComment = false);


/// generate multiple times used regexpression
QRegExp generateRegExp(const QString &text, const bool isCase, const bool isWord, const bool isRegExp);

QStringList regExpFindAllMatches(const QString &searchIn, const QRegExp &regexp, int cap = 0);
QList<int> indicesOf(const QString &line, const QString &word, Qt::CaseSensitivity cs = Qt::CaseSensitive);
QList<int> indicesOf(const QString &line, const QRegExp &rx);

/// add Environment to QNFA DOM
void addEnvironmentToDom(QDomDocument &doc, const QString &EnvironName, const QString &EnvironMode, bool completeParentheses=true);
void addStructureCommandsToDom(QDomDocument &doc , const QHash<QString, QSet<QString> > &possibleCommands);

QString intListToStr(const QList<int> &ints);
QList<int> strToIntList(const QString &s);

bool minimalJsonParse(const QString &text, QHash<QString, QString> &map);
/// generates a string in the format "id"  : "val", where the colon is at least a position minIdWidth+2 (filling with spaces)
QString formatJsonStringParam(const QString &id, const QString &val, int minIdWidth = 0);
QString enquoteStr(const QString &s);
QString dequoteStr(const QString &s);

QString quotePath(const QString &s);
QString removeQuote(const QString &s);
QString removePathDelim(const QString &s);
QString removeAccents(const QString &s);
QString makeLatexLabel(const QString &s);

uint joinUnicodeSurrogate(const QChar &highSurrogate, const QChar &lowSurrogate);

/*! encode image as text for html
 * This is used to generate images for tooltips.
 */
QString getImageAsText(const QPixmap &AImage, const int w = -1);
void showTooltipLimited(QPoint pos, QString text, int relatedWidgetWidth = 0);
QString truncateLines(const QString &s, int maxLines);

bool addMostRecent(const QString &item, QStringList &mostRecentList, int maxLength);

/*!
 * \brief The ArgumentList class holds lists of LaTeX command arguments
 *
 * An argument is enclosed either in curly or square brackets (mandatory/optional argument).
 */
class ArgumentList : public QStringList
{
public:
	inline ArgumentList() {}
	enum ArgType {Optional, Mandatory};
	QString argContent(int index) const;
	QString argContent(int index, ArgType type) const;
	ArgType argType(int index) const;
	int count(ArgType type) const;
};

/*!
 * \brief class for parsing latex code
 *
 * \warning obsolete with lexer based token system
 * \note this functionality is still used in none-core methods
 */
struct LatexReader {
	LatexReader();
	LatexReader(const QString &line);
	LatexReader(const LatexParser &lp, const QString &line);
	LatexReader(const LatexParser &lp, const QString &line, QMap<QString, QString> &replacementList);

	/*! searches the next token in the line line after/at the index index
	 there are these possible kind of tokens % (which starts a comment), { or } (as parentheses), \.* (command) or .* (text)
	 \param index returns the index of the first character after the word
	 \param inOption Don't stop at eow characters
	 \param detectMath If true, returns $ $$ _ ^ & as commands
	 \returns start index of the token (or -1 if last)
	*/
	static int nextToken(const QString &line, int &index, bool inOption, bool detectMath);

	enum NextWordFlag {
		NW_NOTHING = 0,
		NW_TEXT = 1,
		NW_COMMAND = 2,
		NW_COMMENT = 3,
		NW_ENVIRONMENT = 4, ///< environment name, e.g. in \begin or \newenvironment
		NW_REFERENCE = 5,
		NW_LABEL = 6,
		NW_CITATION = 7,
		NW_PUNCTATION = 8,
		NW_PACKAGE = 9
	};

	//Returns the next word (giving meaning to the nextToken tokens)
	//line: line to be examined
	//index: start index as input and returns the first character after the found word
	//outWord: found word (length can differ from index - wordStartIndex for text words)
	//wordStartIndex: start of the word
	//returnCommands: if this is true it returns \commands (NW_COMMAND), "normal" "text"  NW_TEXT and % (NW_COMMENT)  [or NW_NOTHING at the end]
	//                "    "  is false it only returns normal text (NW_TEXT, without things like filenames after \include), environment names
	//                          (NW_ENVIRONMENT, they are treated as text in the other mode) and % (NW_COMMENT)       [or NW_NOTHING at the end]
	//returns the type of outWord
	NextWordFlag nextWord(bool returnCommands);

	//searches the next text words and ignores command options, environments or comments
	//returns false if none is found
	bool nextTextWord();

	const QString &getLine() const; ///< get current line of latexParser
	void setLine(const QString &line); ///< set line for latexParser
	QString line; ///< current line used in latexParser

	int index; ///< current used column position
	QString word; ///< currently handled word
	QString lastCommand; ///< currently active command
	int wordStartIndex; ///< index of \a word

private:
	const LatexParser *lp;
	QMap<QString, QString> mReplacementList;
};


typedef QPair<QString, int> QPairQStringInt;
/*!
 * \brief store necessary information for latex package
 *
 * Stores commands for completion and syntax check.
 */
class LatexPackage
{
public:
	LatexPackage();

	// Temporary solution: keys of LatexDocuments::cachedPackages have become complex. Use these functions to manage them.
	// This is a first step for refactoring the existing code. No functionality is changed.
	// In the long run, the information should be stored and accessed via the LatexPackage objects, which are referenced by the keys.
	static QString makeKey(const QString &cwlFilename, const QString &options);  // TODO not yet used: where are the keys actually created?
	static QString keyToCwlFilename(const QString &key);
	static QString keyToPackageName(const QString &key);
	static QStringList keyToOptions(const QString &key);

	bool notFound;  // Workaround: explicit flag better than using a magic value in package name. TODO: Do we need not found packages?
	QString packageName; ///< name of package
	QStringList requiredPackages; ///< necessary sub-packages
	CodeSnippetList completionWords; ///< list of completion words
	QHash<QString, QSet<QString> > possibleCommands; ///< possible commands, info for syntax checking
	QHash<QString, QString> specialDefCommands; ///< define special elements, e.g. define color etc
	QSet<QString> optionCommands; ///< commands which contain arguments, obsolete
	QHash<QString, QSet< QPairQStringInt > > specialTreatmentCommands; ///< special commands, obsolete
	QMultiHash<QString, QString> environmentAliases; ///< environment aliases, especially environments which signify math environments concerning syntax check
	CommandDescriptionHash commandDescriptions; ///< command definitions
	void unite(LatexPackage &add, bool forCompletion = false); ///< merge with LatexPackage \a add
};

LatexPackage loadCwlFile(const QString fileName, LatexCompleterConfig *config = 0, QStringList conditions = QStringList());

class QDocumentLineHandle;

QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type);
QString getArg(const TokenList &tl,Token::TokenType type);
QString findRestArg(QDocumentLineHandle *dlh, Token::TokenType type, int count = 10);
CommandDescription extractCommandDef(QString line, QString definition);
CommandDescription extractCommandDefKeyVal(QString line, QString &key);
Token getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first = false);
int getTokenAtCol(TokenList &tl, int pos, bool first = false);
TokenList getArgContent(Token &tk);
TokenList getArgContent(TokenList &tl, int pos, int level, int runAwayPrevention = 10);
TokenStack getContext(QDocumentLineHandle *dlh, int pos);
QString getCommandFromToken(Token tk); ///< get command name from Token \a tk which is an argument
Token getCommandTokenFromToken(TokenList tl, Token tk);
TokenList simpleLexLatexLine(QDocumentLineHandle *dlh); ///< first pass lexing of text line
bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const LatexParser &lp); ///< second pass lexing of text line, uses tokens from first pass
int getCompleterContext(QDocumentLineHandle *dlh, int column);
#endif
