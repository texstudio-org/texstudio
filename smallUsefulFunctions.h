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
class QDocumentLineHandle;
class QDocument;


class LatexCompleterConfig;
/*!
 * \brief repesent syntax information on text element
 * The objective for this class is to translate a text(-line) into a series of tokens which can be interpreted much faster and easier subsequently
 * The translation process is divided into 2 passes.
 *
 * Pass 1 simply determines word limits and symbols
 * e.g.\n
 * \\label{abc} def\n
 * is translated to
 \verbatim
 [command 0 6] [openBrace 7 1] [word 8 3] [closeBrace 12 1] [word 14 3]
 \endverbatim
 *
 * no context is used
 *
 * Pass 2 interprets the data in order to assign arguments to commands and to assign a purpose for the arguments if they are defined in the cwl
 * It uses the tokens from the first pass to speed-up processing\n
 * e.g. (from previous example, level is represented by the line, type/subtype is given)\n
 \verbatim
 level=0 [command/none 0 6] [braces/label 7 5]                  [word/none 14 3]
 level=1                                       [label/none 8 3]
 \endverbatim
 The level is encoded via the level-property. The list is actually still linear.
 */
class Tokens
{
public:
	Tokens(): start(-1), length(-1), level(-1), dlh(0), type(none), subtype(none), argLevel(0) {}
	int start;
	int length;
	int level;
    QString optionalCommandName;
	QDocumentLineHandle *dlh;

	enum TokenType {none = 0, word, command, braces, bracket,
	                squareBracket, openBrace, openBracket, openSquare, closeBrace,
	                closeBracket, closeSquareBracket, math, comment, commandUnknown, label, bibItem, file, imagefile, bibfile,
	                keyValArg, keyVal_key, keyVal_val, list, text, env, beginEnv, def, labelRef, package, width, placement, colDef, title, url, documentclass, beamertheme, packageoption,
	                color, verbatimStart, verbatimStop, verbatim, symbol, punctuation, number, generalArg, defArgNumber, optionalArgDefinition, definition, defWidth, labelRefList, specialArg, newTheorem,newBibItem,_end = 255
	               };
	static QString tokenTypeName(TokenType t);

	TokenType type;
	/// subtype is used to determine the type of argument
	TokenType subtype;
	int argLevel; ///< number of argument (>0) or option (<0, =-numberOfOption)
	static QSet<TokenType> tkArg();
	static QSet<TokenType> tkOption();
	static QSet<TokenType> tkBraces();
	static QSet<TokenType> tkOpen();
	static QSet<TokenType> tkClose();
	static QSet<TokenType> tkCommalist();
	static QSet<TokenType> tkSingleArg();
	static TokenType opposite(TokenType type);
	static TokenType closed(TokenType type);
	bool operator==(const Tokens &v) const;
	QString getText();
};
QDebug operator<<(QDebug dbg, Tokens::TokenType tk);
QDebug operator<<(QDebug dbg, Tokens tk);

typedef QList<Tokens> TokenList;
typedef QStack<Tokens> TokenStack;

Q_DECLARE_METATYPE(TokenList);
Q_DECLARE_METATYPE(TokenStack);
void qDebugTokenList(TokenList tl);

/*!
 * \brief define available arguments for a command
 */
class CommandDescription
{
public:
	CommandDescription();
	int optionalArgs; ///< number of optional arguments
	int bracketArgs; ///< number of () arguments
	int args; ///< number of mandatory arguments (in braces)
	int level;
	QList<Tokens::TokenType> argTypes; ///< define argument type as token
	QList<Tokens::TokenType> optTypes; ///< define argument type as token
	QList<Tokens::TokenType> bracketTypes; ///< define argument type as token
    QString optionalCommandName; ///< stores optionally command name. It is used for processing command description during lexing
	QString toDebugString() const; ///< debug function to get easier information on command description
    bool operator==(const CommandDescription &v) const; ///< compare two command descriptions
};

typedef QStack<CommandDescription> CommandStack;

Q_DECLARE_METATYPE(CommandStack);

typedef QHash<QString, CommandDescription> CommandDescriptionHash;

typedef QString (QObject::*StringToStringCallback)(const QString &) ;

QString getCommonEOW();


/// removes special latex characters
QString latexToPlainWord(const QString &word);
QString latexToPlainWordwithReplacementList(const QString &word, QMap<QString, QString> &replacementList );
/// closing bracket (opening and closing bracket considered correctly)
int findClosingBracket(const QString &word, int &start, QChar oc = QChar('{'), QChar cc = QChar('}'));
/// opening bracket (opening and closing bracket considered correctly), start at "start"
int findOpeningBracket(const QString &word, int start, QChar oc = QChar('{'), QChar cc = QChar('}'));
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
int findCommandWithArgsFromTL(const TokenList &tl, Tokens &cmd, TokenList &args, int offset, bool parseComment = false);


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

QTextCodec *guessEncodingBasic(const QByteArray &data, int *outSure);

enum {
	MIB_LATIN1 = 4,
	MIB_WINDOWS1252 = 2252,
	MIB_UTF8 = 106,
	MIB_UTF16BE = 1013,
	MIB_UTF16LE = 1014

};
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
 * \brief class for storing latex syntax informtion and latex parsing
 *
 * The latex parsing is less important since the token based system, but the storage of syntax information is still used.
 */
class LatexParser
{
	friend class SmallUsefulFunctionsTest;
public:
	LatexParser(); ///< constructor
	~LatexParser();
	void init(); ///< set default values

	static const int MAX_STRUCTURE_LEVEL;
	
	enum ContextType {Unknown, Command, Environment, Label, Reference, Citation, Citation_Ext, Option, Graphics, Package, Keyval, KeyvalValue, OptionEx, ArgEx};
	// could do with some generalization as well, optionEx/argEx -> special treatment with specialOptionCommands

	/// realizes whether col is in a \command or in a parameter {}
	int findContext(QString &line, int &column) const;

	///position of the % starting a comment (takes care of multiple backslashes before comment character ..)
	static int commentStart(const QString &text);

	/// remove comment from text, take care of multiple backslashes before comment character ...
	static QString cutComment(const QString &text);

	ContextType findContext(const QString &line, int column, QString &command, QString &value) const;
	static bool resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts = 0);
	static QString removeOptionBrackets(const QString &option);

	QSet<QString> environmentCommands; ///< used by LatexReader only, obsolete
	QSet<QString> optionCommands; ///< used by LatexReader only, obsolete
	QStringList mathStartCommands; ///< commands to start math-mode like '$'
	QStringList mathStopCommands; ///< commands to stop math-mode like '$'
	QSet<QString> customCommands; ///< commands defined in config dialog as custom commands
	int structureDepth()
	{
		return MAX_STRUCTURE_LEVEL;
	}
	int structureCommandLevel(const QString &cmd) const;
	QMultiHash<QString, QString> packageAliases; ///< aliases for classes to packages e.g. article = latex-document, latex-mathsymbols, etc
	QMultiHash<QString, QString> environmentAliases; ///< aliases for environments, e.g. equation is math, supertabular is also tab etc.
	/// commands used for syntax check (per doc basis)
	QHash<QString, QSet<QString> > possibleCommands;
	QHash<QString, QSet<QPair<QString, int> > > specialTreatmentCommands; ///< special commands, obsolete
	QHash<QString, QString> specialDefCommands; ///< define special elements, e.g. define color etc
	QMap<int, QString> mapSpecialArgs;

	CommandDescriptionHash commandDefs; ///< command definitions

	void append(const LatexParser &elem); ///< append values
	void substract(const LatexParser &elem); ///< remove values
	void importCwlAliases(); ///< import package aliases from disc
	void clear(); ///< set to default values
	static QTextCodec *QTextCodecForLatexName(QString str); ///< get textcodec from codec name
	static QStringList latexNamesForTextCodec(const QTextCodec *codec); ///< get codec name used in latex from text codec
	static void guessEncoding(const QByteArray &data, QTextCodec *&guess, int &sure); ///< guess text codec for file

	static LatexParser &getInstance();
private:
	static int lineStart(const QByteArray &data, int index);
	static int lineEnd(const QByteArray &data, int index);
	static QString getEncodingFromPackage(const QByteArray &data, int headerSize, const QString &packageName); ///< get encoding from usepackage definition in file
};

Q_DECLARE_METATYPE(LatexParser)
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
QString getArg(const TokenList &tl,Tokens::TokenType type);
QString findRestArg(QDocumentLineHandle *dlh, Tokens::TokenType type, int count = 10);
CommandDescription extractCommandDef(QString line, QString definition);
CommandDescription extractCommandDefKeyVal(QString line, QString &key);
Tokens getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first = false);
int getTokenAtCol(TokenList &tl, int pos, bool first = false);
TokenList getArgContent(Tokens &tk);
TokenList getArgContent(TokenList &tl, int pos, int level, int runAwayPrevention = 10);
TokenStack getContext(QDocumentLineHandle *dlh, int pos);
QString getCommandFromToken(Tokens tk); ///< get command name from Token \a tk which is an argument
Tokens getCommandTokenFromToken(TokenList tl, Tokens tk);
TokenList simpleLexLatexLine(QDocumentLineHandle *dlh); ///< first pass lexing of text line
bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const LatexParser &lp); ///< second pass lexing of text line, uses tokens from first pass
int getCompleterContext(QDocumentLineHandle *dlh, int column);
#endif
