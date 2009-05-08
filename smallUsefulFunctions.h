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
#include <QString>

QString getCommonEOW(); 

//returns the real name of a resource file (allowing the user to override resource files with local files)
QString findResourceFile(QString fileName);
//returns if the file is writable (QFileInfo.isWritable works in different ways on Windows and Linux)
bool isFileRealWritable(QString filename); 
//returns if the file exists and is writable 
bool isExistingFileRealWritable(QString filename);  
//get relative path for a given file
QString getRelativePath(const QString basepath, const QString & file);


//searches the next token in the line line after/at the index index
//there are three possible kind of tokens % (which starts a comment), { or } (as parantheses), \.* (command) or .* (text)
//index returns the index of the first character after the word
//return: start index of the token (or -1 if last)
int nextToken(const QString &line,int &index);    


enum NextWordFlag{
    NW_NOTHING=0,
    NW_TEXT=1,
    NW_COMMAND=2,
    NW_COMMENT=3,
	NW_ENVIRONMENT=4
};
NextWordFlag nextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex, bool returnCommands);

//searches the next text words and ignores command options, environments or comments
//returns false if none is found 
bool nextTextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex);

//removes special latex characters 
QString latexToPlainWord(QString word);    
//extracts the section name after \section is removed (brackets removal)
QString extractSectionName(QString word);
//replaces character with corresponding LaTeX commands
QString textToLatex(QString text);

//compares two strings local aware
bool localAwareLessThan(const QString &s1, const QString &s2);

#endif
