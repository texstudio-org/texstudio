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

// subgroups of utility functions:
#include "utilsUI.h"
#include "utilsSystem.h"
#include "utilsVersion.h"

//#inlcude "latexcompleter_config.h"

struct CommandArgument {
	bool isOptional;
	int number;
	QString value;
};
Q_DECLARE_METATYPE( CommandArgument )

//void txs_assert(const char *assertion, const char *file, int line);


class LatexCompleterConfig;


typedef QString (QObject::*StringToStringCallback)(const QString&) ;

QString getCommonEOW();


//removes special latex characters
QString latexToPlainWord(const QString& word);
QString latexToPlainWordwithReplacementList(const QString& word, QMap<QString, QString> &replacementList );
//closing bracket (opening and closing bracket considered correctly)
int findClosingBracket(const QString& word,int &start,QChar oc=QChar('{'),QChar cc=QChar('}'));
//opening bracket (opening and closing bracket considered correctly), start at "start"
int findOpeningBracket(const QString& word,int start,QChar oc=QChar('{'),QChar cc=QChar('}'));
//replaces character with corresponding LaTeX commands
QString textToLatex(const QString& text);
// replaces \texorpdfstring{tex}{pdfString} with pdfString
QString& parseTexOrPDFString(QString& s);

QStringList joinLinesExceptCommentsAndEmptyLines(const QStringList& lines);
QStringList splitLines(const QStringList& lines, int maxCharPerLine, const QRegExp& breakChars);

//compares two strings locale aware
bool localeAwareLessThan(const QString &s1, const QString &s2);

// true for characters that are valid in latex command names, e.g. \section*
inline bool isCommandChar(const QChar &c) { return c.isLetter() || c=='*'; }
// returns the position of the first non-whitespace at or after pos
int getCommand(const QString &line, QString &outCmd, int pos=0);
QList< CommandArgument > getCommandOptions(const QString &line, int pos=0, int *posBehind=0);
QString getParamItem(const QString &line, int pos, bool stopAtWhiteSpace=false);

QString trimLeft(const QString &s);
QString trimRight(const QString &s);

// find token (e.g. \label \input \section and return content (\section{content})
QString findToken(const QString &line,const QString &token);
QString findToken(const QString &line,const QString &token,int &start);
QString findToken(const QString &line,QRegExp &token);
// find token (e.g. \label \input \section and return content (\newcommand{name}[arg]), returns true if outName!=""
bool findTokenWithArg(const QString &line,const QString &token, QString &outName, QString &outArg);
bool findCommandWithArg(const QString &line, QString &cmd, QString &outName, QString &outArg, QString &remainder, int &argStart, QString &option);


// generate multiple times used regexpression
QRegExp generateRegExp(const QString &text,const bool isCase,const bool isWord, const bool isRegExp);

QStringList regExpFindAllMatches(const QString& searchIn, const QRegExp& regexp, int cap = 0);
QList<int> indicesOf(const QString& line, const QString& word, Qt::CaseSensitivity cs = Qt::CaseSensitive);
QList<int> indicesOf(const QString& line, const QRegExp& rx);

// add Environment to QNFA DOM
void addEnvironmentToDom(QDomDocument &doc,const QString& EnvironName,const QString& EnvironMode);
void addStructureCommandsToDom(QDomDocument &doc ,const QList<QStringList> &structureCommandLists);

QString intListToStr(const QList<int> &ints);
QList<int> strToIntList(const QString &s);

bool minimalJsonParse(const QString &text, QHash<QString, QString> &map);
// generates a string in the format "id"  : "val", where the colon is at least a position minIdWidth+2 (filling with spaces)
QString formatJsonStringParam(const QString &id, const QString &val, int minIdWidth = 0);
QString enquoteStr(const QString &s);
QString dequoteStr(const QString &s);

QString quotePath(const QString &s);

QTextCodec * guessEncodingBasic(const QByteArray& data, int * outSure);

enum {
	MIB_LATIN1 = 4,
	MIB_WINDOWS1252 = 2252,
	MIB_UTF8 = 106,
	MIB_UTF16BE = 1013,
	MIB_UTF16LE = 1014

};

QString getImageAsText(const QPixmap &AImage);
void showTooltipLimited(QPoint tt,QString topic,int width=0);
QString truncateLines(const QString & s, int maxLines);

bool addMostRecent(const QString & item, QStringList & mostRecentList, int maxLength);

class LatexParser{
	friend class SmallUsefulFunctionsTest;
public:
	LatexParser();
	void init();

    enum ContextType {Unknown, Command, Environment, Label, Reference, Citation, Citation_Ext, Option, Graphics,Package,Keyval,KeyvalValue};
	// realizes whether col is in a \command or in a parameter {}
	int findContext(QString &line, int &column) const;
	
	//position of the % starting a comment (takes care of multiple backslashes before comment character ..)
	static int commentStart(const QString& text);
	
	// remove comment from text, take care of multiple backslashes before comment character ...
	static QString cutComment(const QString& text);
	
	ContextType findContext(const QString &line, int column, QString &command, QString& value) const;
	static void resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts=0);
	static QString removeOptionBrackets(const QString &option);
	
    //QSet<QString> refCommands;
    //QSet<QString> labelCommands;
    //QSet<QString> citeCommands;
	QSet<QString> environmentCommands;
    //QSet<QString> definitionCommands;
	QSet<QString> optionCommands;
	QSet<QString> mathStartCommands;
	QSet<QString> mathStopCommands;
    //QSet<QString> tabularEnvirons;
    //QSet<QString> fileCommands;
    //QSet<QString> includeCommands;
    //QSet<QString> usepackageCommands;
	QSet<QString> customCommands;
    //QSet<QString> graphicsIncludeCommands;
	QStringList structureCommands;
	QList<QStringList> structureCommandLists;  // a list for each level. 0:\part,\mypart 1:\chapter,\mychapter 2:\section ... 5:paragraph
	int structureDepth() { return structureCommandLists.length(); }
	int structureCommandLevel(const QString &cmd) const;
	QMultiHash<QString,QString> packageAliases; // aliases for classes to packages e.g. article = latex-document, latex-mathsymbols, etc
	QMultiHash<QString,QString> environmentAliases; // aliases for environments, e.g. equation is math, supertabular is also tab etc.
	// commands used for syntax check (per doc basis)
	QHash<QString,QSet<QString> > possibleCommands;
	
	void append(const LatexParser& elem);
	void substract(const LatexParser& elem);
	void importCwlAliases();
	void clear();
	static QTextCodec* QTextCodecForLatexName(QString str);
	static QStringList latexNamesForTextCodec(const QTextCodec *codec);
	static void guessEncoding(const QByteArray& data, QTextCodec *&guess, int &sure);
	
	static LatexParser& getInstance();
private:
	static int lineStart(const QByteArray& data, int index);
	static int lineEnd(const QByteArray& data, int index);
	static QString getEncodingFromPackage(const QByteArray& data, int headerSize, const QString &packageName);
};

Q_DECLARE_METATYPE(LatexParser)

struct LatexReader{
	LatexReader();
	LatexReader(const QString& line);
	LatexReader(const LatexParser& lp, const QString& line);
    LatexReader(const LatexParser& lp, const QString& line, QMap<QString,QString> &replacementList);
	
	/** searches the next token in the line line after/at the index index
	//there are these possible kind of tokens % (which starts a comment), { or } (as parentheses), \.* (command) or .* (text)
	 \param index returns the index of the first character after the word
	 \param inOption Don't stop at eow characters
	 \param detectMath If true, returns $ $$ _ ^ & as commands
	 \returns start index of the token (or -1 if last)
	*/
	static int nextToken(const QString &line,int &index, bool inOption,bool detectMath);
	
	enum NextWordFlag {
		NW_NOTHING=0,
		NW_TEXT=1,
		NW_COMMAND=2,
		NW_COMMENT=3,
		NW_ENVIRONMENT=4, //environment name, e.g. in \begin or \newenvironment
		NW_REFERENCE=5,
		NW_LABEL=6,
		NW_CITATION=7,
        NW_PUNCTATION=8,
        NW_PACKAGE=9
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
	
	const QString& getLine() const;
	void setLine(const QString& line);
	QString line;
	
	int index;
	QString word;
	QString lastCommand;
	int wordStartIndex;

private:
	const LatexParser* lp;
    QMap<QString, QString> mReplacementList;
};


class LatexPackage{
public:
	LatexPackage();
	QString packageName;
	QStringList requiredPackages;
	QStringList completionWords;
	QHash<QString,QSet<QString> > possibleCommands;
	QSet<QString> optionCommands;
	QMultiHash<QString,QString> environmentAliases;
	void unite(LatexPackage &add);
};

LatexPackage loadCwlFile(const QString fileName,LatexCompleterConfig *config=0);

#endif
