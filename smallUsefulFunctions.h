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
//returns if the file is writable
//(QFileInfo.isWritable works in different ways on Windows and Linux)
bool isFileRealWritable(QString filename); 
bool isExistingFileRealWritable(QString filename); 
QString findResourceFile(QString fileName);
#endif
