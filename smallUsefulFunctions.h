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


enum NextWordFlags{
    NW_NOTHING=0,
    NW_TEXT=1,
    NW_COMMAND=2,
    NW_COMMENT=4
};
//searches the next word in the line line after the index index
//index returns the index of the first character after the word
//outWord the word (normalized, stripped latex special chars)
//wordStartIndex the starting index of the word
//return: true if there is really a word
bool nextWord(QString line,int &index,QString &outWord,int &wordStartIndex);    
//similar, but can also search commands/comments
int nextWord(QString line,int &index,QString &outWord,int &wordStartIndex, int flags);    
//removes special latex characters 
QString latexToPlainWord(QString word);    
//extracts the section name after \section is removed (brackets removal)
QString extractSectionName(QString word);
#endif
