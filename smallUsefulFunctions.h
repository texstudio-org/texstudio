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

#define REQUIRE(x)  Q_ASSERT((x)); if (!(x)) return;
#define REQUIRE_RET(x,e)  Q_ASSERT((x)); if (!(x)) return (e);

typedef QString (QObject::*StringToStringCallback)(const QString&) ;

QString getCommonEOW();

QStringList findResourceFiles(const QString& dirName, const QString& filter);
//returns the real name of a resource file
QString findResourceFile(const QString& fileName, bool allowOverride = false, QStringList additionalPreferredPaths = QStringList(), QStringList additionalFallbackPaths = QStringList());
//returns if the file is writable (QFileInfo.isWritable works in different ways on Windows and Linux)
bool isFileRealWritable(const QString& filename);
//returns if the file exists and is writable
bool isExistingFileRealWritable(const QString& filename);
//adds QDir::separator() if the path end not with it
QString ensureTrailingDirSeparator(const QString& dirPath);
		

//returns kde version 0,3,4
int x11desktop_env();


//searches the next token in the line line after/at the index index
//there are these possible kind of tokens % (which starts a comment), { or } (as parantheses), \.* (command) or .* (text)
//index returns the index of the first character after the word
//detectMath==true: return $ $$ _ as commands
//return: start index of the token (or -1 if last)
int nextToken(const QString &line,int &index,bool abbreviation=false,bool inOption=false,bool detectMath=false);


enum NextWordFlag {
	NW_NOTHING=0,
	NW_TEXT=1,
	NW_COMMAND=2,
	NW_COMMENT=3,
	NW_ENVIRONMENT=4, //environment name, e.g. in \begin or \newenvironment
	NW_REFERENCE=5,
	NW_LABEL=6,
	NW_CITATION=7
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
NextWordFlag nextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex, bool returnCommands,bool abbreviations=false,bool *inStructure=0);

//searches the next text words and ignores command options, environments or comments
//returns false if none is found
bool nextTextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex);

//removes special latex characters
QString latexToPlainWord(const QString& word);
//extracts the section name after \section is removed (brackets removal)
QString extractSectionName(const QString& word,bool precut=false);
//closing bracket (opening and closing bracket considered correctly)
int findClosingBracket(const QString& word,int &start);
//replaces character with corresponding LaTeX commands
QString textToLatex(const QString& text);

//compares two strings local aware
bool localAwareLessThan(const QString &s1, const QString &s2);

// find token (e.g. \label \input \section and return content (\section{content})
QString findToken(const QString &line,const QString &token);
QString findToken(const QString &line,const QString &token,int &start);
QString findToken(const QString &line,QRegExp &token);
// find token (e.g. \label \input \section and return content (\newcommand{name}[arg]), returns true if outName!=""
bool findTokenWithArg(const QString &line,const QString &token, QString &outName, QString &outArg);
bool findCommandWithArg(const QString &line,QString &cmd, QString &outName, QString &outArg, QString &remainder,int &optionStart);



// generate multiple times used regexpression
QRegExp generateRegExp(const QString &text,const bool isCase,const bool isWord, const bool isRegExp);

// add Environment to QNFA DOM
void addEnvironmentToDom(QDomDocument &doc,const QString EnvironName,const QString EnvironMode);

//setup toolbutton as substitute for const combobox
QToolButton* createComboToolButton(QWidget *parent,const QStringList& list,const int height,const QFontMetrics fm,const QObject * receiver, const char * member,QString defaultElem="",QToolButton *combo=0);
//find the tool button which contains a given action
QToolButton* comboToolButtonFromAction(QAction* action);


//check if the run-time qt version is higher than the given version (e.g. 4,3)
bool hasAtLeastQt(int major, int minor);

QString getRelativeBaseNameToPath(const QString & file,QString basepath);
QString getPathfromFilename(const QString &compFile);

enum {
	MIB_LATIN1 = 4,
	MIB_UTF8 = 106,
	MIB_UTF16BE = 1013,
	MIB_UTF16LE = 1014

};

class LatexParser{
public:
	LatexParser();

        enum ContextType {Unknown, Command, Environment, Label, Reference, Citation, Option};
	// realizes whether col is in a \command or in a parameter {}
	static int findContext(QString &line, int column);
	
	//position of the % starting a comment (takes care of multiple backslashes before comment character ..)
	static int commentStart(const QString& text);

	// remove comment from text, take care of multiple backslashes before comment character ...
	static QString cutComment(const QString& text);

	static ContextType findContext(const QString &line, int column, QString &command, QString& value);
	static void resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts=0);

	static QSet<QString> refCommands;
	static QSet<QString> labelCommands;
	static QSet<QString> citeCommands;
	static QSet<QString> environmentCommands;
	static QSet<QString> definitionCommands;
	static QSet<QString> optionCommands;
	static QSet<QString> mathStartCommands;
        static QSet<QString> mathStopCommands;
        static QSet<QString> tabularEnvirons;
        static QSet<QString> fileCommands;
	static QSet<QString> includeCommands;
	static QSet<QString> usepackageCommands;
	static QStringList structureCommands;
	// commands used for syntax check (per doc basis)
	QSet<QString> tabularCommands;
	QSet<QString> normalCommands;
	QSet<QString> mathCommands;
	QSet<QString> tabbingCommands;
	QSet<QString> userdefinedCommands;

	void append(LatexParser elem);
	void substract(LatexParser elem);
	void clear();
	static QTextCodec* QTextCodecForLatexName(QString str);
	static void guessEncoding(const QByteArray& data, QTextCodec *&guess, int &sure);
};

QStringList loadCwlFiles(const QStringList &newFiles,LatexParser *cmds);

#endif
