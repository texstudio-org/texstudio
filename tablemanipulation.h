#ifndef TABLEMANIPULATION_H
#define TABLEMANIPULATION_H

#include "qdocument.h"

void addRow(QDocument *doc,const int afterLine,const int numberOfColumns );
void addColumn(QDocument *doc,const int lineNumber,const int afterColumn,QStringList *cutBuffer=0);
void removeColumn(QDocument *doc,const int lineNumber,const int column,QStringList *cutBuffer=0);
void removeRow(QDocument *doc,const int afterLine );
int findNextToken(QDocumentCursor &cur,QStringList tokens,bool keepAnchor=false,bool backwards=false);
int getColumn(QDocumentCursor &cur);

#endif // TABLEMANIPULATION_H
