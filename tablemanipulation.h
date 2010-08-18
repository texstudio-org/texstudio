#ifndef TABLEMANIPULATION_H
#define TABLEMANIPULATION_H

#include "qdocument.h"

void addRow(const QDocument *doc,const int afterLine,const int numberOfColumns );
void addColumn(const QDocument *doc,const int afterColumn,QStringList &cutBuffer);
void removeColmun(const QDocument *doc,const int column,QStringList &cutBuffer);

#endif // TABLEMANIPULATION_H
