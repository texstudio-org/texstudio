/**************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#ifndef SYMBOLVIEWCLASSES_H
#define SYMBOLVIEWCLASSES_H

#include <QtCore/QObject>
#include <QtCore/QString>

struct Preamble{
   QString className;
   QString classArguments;
   QString additional;
};

struct Package{
   QString name;
   QString arguments;
};

struct Command{
   QString latexCommand;
   QString unicodeCommand;
   QString ImageCommand;
   QString comment;
   QString name;
   bool mathMode;
   bool forcePNG;
   bool iconMode;
   QList<Package> packages;
   QList<Package> unicodePackages;
   int referenceCount;
   QString path;
};

struct Version{
   QString major;
   QString minor;
};

#endif //SYMBOLVIEWCLASSES_H
