#include "qdocumentcursor.h"

void addRow(QDocument *doc,const int afterLine,const int numberOfColumns ){
    QDocumentCursor cur(doc);
    cur.moveTo(afterLine,0);
    cur.movePosition(1,QDocumentCursor::EndOfLine);
    cur.insertText("\n");
    QString str(" &");
    for(int i=1;i<numberOfColumns;i++){
	str+=str;
    }
    if(numberOfColumns>1) cur.insertText(str);
    cur.insertText("\\\\");
}
