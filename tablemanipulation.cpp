#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "smallUsefulFunctions.h"
#include "tablemanipulation.h"

void addRow(QDocument *doc,const int afterLine,const int numberOfColumns ){
    QDocumentCursor cur(doc);
    cur.moveTo(afterLine,0);
    cur.movePosition(1,QDocumentCursor::EndOfLine);
    cur.insertText("\n");
    QString str("& ");
    QString outStr(" ");
    for(int i=1;i<numberOfColumns;i++){
	outStr+=str;
    }
    cur.insertText(outStr);
    cur.insertText("\\\\");
}

void removeRow(QDocument *doc,const int afterLine ){
    QDocumentCursor cur(doc);
    cur.beginEditBlock();
    cur.moveTo(afterLine,0);
    const QStringList tokens("\\\\");
    bool breakLoop=(findNextToken(cur,tokens,true)==-1);
    if(!breakLoop) {
	cur.removeSelectedText();
	if(cur.line().text().isEmpty()) cur.deleteChar();
    }
    cur.endEditBlock();
}

void addColumn(QDocument *doc,const int lineNumber,const int afterColumn,QStringList *cutBuffer){
    QDocumentCursor cur(doc);
    cur.beginEditBlock();
    cur.moveTo(lineNumber,0);
    QString line;
    bool breakLoop=false;
    int result=2;
    while(!breakLoop){
	for(int col=0;col<afterColumn;col++){
	    QStringList nTokens;
	    nTokens << "\\\\" << "\\&" << "&";
	    do{
		result=findNextToken(cur,nTokens);
	    }while(result==1);
	    if(result<1) breakLoop=true;
	}
	if(result<0) break;
	// add element
	if(result==2){
	    cur.insertText(" &");
	}
	const QStringList tokens("\\\\");
	breakLoop=(findNextToken(cur,tokens)==-1);
	if(cur.atLineEnd()) cur.movePosition(1,QDocumentCursor::Right);
	line=cur.line().text();
	if(line.contains("\\end")) breakLoop=true;
    }
    cur.endEditBlock();
}

void removeColumn(QDocument *doc,const int lineNumber,const int column,QStringList *cutBuffer){
    QDocumentCursor cur(doc);
    //preparations for search
    QStringList nTokens;
    nTokens << "\\\\" << "\\&" << "&";

    cur.beginEditBlock();
    cur.moveTo(lineNumber,0);
    QString line;
    bool breakLoop=false;
    while(!breakLoop){
	int result=2;
	for(int col=0;col<column;col++){
	    do{
		result=findNextToken(cur,nTokens);
	    }while(result==1);
	    if(result<1) breakLoop=true;
	}
	if(result==-1) break;
	// add element
	if(result>-1){
	    do{
		result=findNextToken(cur,nTokens,true);
	    }while(result==1);

	    if(result==2 && column>0) {
		cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
	    }
	    if(result==0) {
		cur.movePosition(2,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
	    }
	    cur.removeSelectedText();
	    if(column>0) {
		cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		cur.removeSelectedText();
	    }
	}
	const QStringList tokens("\\\\");
	breakLoop=(findNextToken(cur,tokens)==-1);
	if(cur.atLineEnd()) cur.movePosition(1,QDocumentCursor::Right);
	line=cur.line().text();
	if(line.contains("\\end")) breakLoop=true;
    }
    cur.endEditBlock();
}


int findNextToken(QDocumentCursor &cur,QStringList tokens,bool keepAnchor,bool backwards){
    int pos=-1;
    int nextToken=-1;
    QDocumentCursor::MoveOperation mvNextLine= backwards ? QDocumentCursor::PreviousLine : QDocumentCursor::NextLine;
    QDocumentCursor::MoveOperation mvNextChar= backwards ? QDocumentCursor::Left : QDocumentCursor::Right;
    QDocumentCursor::MoveOperation mvStartOfLine= backwards ? QDocumentCursor::EndOfLine : QDocumentCursor::StartOfLine;
    QDocumentCursor::MoveFlag mvFlag= keepAnchor ? QDocumentCursor::KeepAnchor : QDocumentCursor::MoveAnchor;
    do{
	QString line=cur.line().text();
	line=LatexParser::cutComment(line);
	if(line.contains("\\end")&&!backwards) {
	    nextToken=-2;
	    break;
	}
	if(line.contains("\\begin")&&backwards) {
	    nextToken=-2;
	    break;
	}

	pos=-1;
	for(int i=0;i<tokens.count();i++){
	    QString elem=tokens.at(i);
	    int zw=line.indexOf(elem,cur.columnNumber());
	    if(zw>-1) {
		if(pos>zw || pos==-1){
		    pos=zw;
		    nextToken=i;
		}
	    }
	}
	if(pos<0){
	    if(cur.lineNumber()>=cur.document()->lineCount()-1) break;
	    cur.movePosition(1,mvNextLine,mvFlag);
	    cur.movePosition(1,QDocumentCursor::StartOfLine,mvFlag);
	}
    }while(pos<0);
    if(pos>-1) {
	cur.movePosition(1,mvStartOfLine,mvFlag);
	cur.movePosition(pos+tokens.at(nextToken).length(),mvNextChar,mvFlag);
    }
    return nextToken;
}

int getColumn(QDocumentCursor &cur){
    QDocumentCursor c(cur);
    QStringList tokens("\\\\");
    bool breakLoop=(findNextToken(c,tokens,false,true)==-1);

    tokens << "\\&" << "&";
    int result;
    int col=0;

    do{
	result=findNextToken(c,tokens);
	if(c.lineNumber()>cur.lineNumber()|| (c.lineNumber()==cur.lineNumber() && c.columnNumber()>cur.columnNumber())) break;
	if(result==2) col++;
    }while(result>0);
    return col;
}
