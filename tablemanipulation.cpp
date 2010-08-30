#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "smallUsefulFunctions.h"
#include "tablemanipulation.h"

QStringList LatexTables::tabularNames = QStringList() << "tabular";
QStringList LatexTables::tabularNamesWithOneOption = QStringList() << "tabular*" << "tabularx";

void LatexTables::addRow(QDocumentCursor &c,const int numberOfColumns ){
    QDocumentCursor cur(c);
    bool stopSearch=false;
    if(cur.columnNumber()>1){
	cur.movePosition(2,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
	QString res=cur.selectedText();
	if(res=="\\\\") stopSearch=true;
	cur.movePosition(2,QDocumentCursor::Right);
    }
    const QStringList tokens("\\\\");
    int result=0;
    if(!stopSearch) result=findNextToken(cur,tokens);
    if(result==0 || result==-2){
	cur.beginEditBlock();
	if(result>-2) cur.insertText("\n");
	QString str("& ");
	QString outStr(" ");
	for(int i=1;i<numberOfColumns;i++){
	    outStr+=str;
	}
	cur.insertText(outStr);
	cur.insertText("\\\\");
	if(!cur.atLineEnd()) cur.insertText("\n");
	cur.endEditBlock();
    }
}

void LatexTables::removeRow(QDocumentCursor &c){
    QDocumentCursor cur(c);
    const QStringList tokens("\\\\");
    int result=findNextToken(cur,tokens,false,true);
    if(result==0) cur.movePosition(2,QDocumentCursor::Right);
    if(result==-2) cur.movePosition(1,QDocumentCursor::EndOfLine);
    bool breakLoop=(findNextToken(cur,tokens,true)==-1);
    if(!breakLoop) {
	cur.beginEditBlock();
	cur.removeSelectedText();
	if(cur.line().text().isEmpty()) cur.deleteChar();
    }
    cur.endEditBlock();
}

void LatexTables::addColumn(QDocument *doc,const int lineNumber,const int afterColumn,QStringList *cutBuffer){
    QDocumentCursor cur(doc);
    cur.beginEditBlock();
    cur.moveTo(lineNumber,0);
    int result=findNextToken(cur,QStringList(),false,true); // move to \begin{...}
    if(result!=-2) {
	cur.endEditBlock();
	return; // begin not found
    }
    cur.movePosition(1,QDocumentCursor::Right);
    QString line;
    bool breakLoop=false;
    result=2;
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
	if(result==0){
	    cur.movePosition(2,QDocumentCursor::Left);
	    cur.insertText("& ");
	}
	const QStringList tokens("\\\\");
	breakLoop=(findNextToken(cur,tokens)==-1);
	if(cur.atLineEnd()) cur.movePosition(1,QDocumentCursor::Right);
	line=cur.line().text();
	if(line.contains("\\end")) breakLoop=true;
    }
    cur.endEditBlock();
}

void LatexTables::removeColumn(QDocument *doc,const int lineNumber,const int column,QStringList *cutBuffer){
    QDocumentCursor cur(doc);
    //preparations for search
    QStringList nTokens;
    nTokens << "\\\\" << "\\&" << "&";

    cur.moveTo(lineNumber,0);
    int result=findNextToken(cur,QStringList(),false,true); // move to \begin{...}
    cur.movePosition(1,QDocumentCursor::Right);
    if(result!=-2) {
	return; // begin not found
    }
    cur.beginEditBlock();
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


int LatexTables::findNextToken(QDocumentCursor &cur,QStringList tokens,bool keepAnchor,bool backwards){
    int pos=-1;
    int nextToken=-1;
    int offset=0;
    QDocumentCursor::MoveOperation mvNextLine= backwards ? QDocumentCursor::PreviousLine : QDocumentCursor::NextLine;
    QDocumentCursor::MoveOperation mvNextChar= backwards ? QDocumentCursor::Left : QDocumentCursor::Right;
    QDocumentCursor::MoveOperation mvStartOfLine= backwards ? QDocumentCursor::EndOfLine : QDocumentCursor::StartOfLine;
    QDocumentCursor::MoveFlag mvFlag= keepAnchor ? QDocumentCursor::KeepAnchor : QDocumentCursor::MoveAnchor;
    do{
	QString line=cur.line().text();
	if(backwards){
	    offset=line.length();
	}
	line=LatexParser::cutComment(line);
	if(backwards){
	    offset=offset-line.length();
	    QString help;
	    foreach(QChar elem,line){
		help.prepend(elem);
	    }
	    line=help;
	}

	if(line.contains("\\end")&&!backwards) {
	    nextToken=-2;
	    break;
	}
	if(line.contains("nigeb\\")&&backwards) {
	    nextToken=-2;
	    break;
	}

	pos=-1;
	for(int i=0;i<tokens.count();i++){
	    QString elem=tokens.at(i);
	    int colNumber= cur.columnNumber();
	    if(backwards) colNumber=line.length()+offset-colNumber ;
	    int zw=line.indexOf(elem,colNumber);
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
	    cur.movePosition(1,mvStartOfLine,mvFlag);
	}
    }while(pos<0);
    if(pos>-1) {
	cur.movePosition(1,mvStartOfLine,mvFlag);
	cur.movePosition(pos+tokens.at(nextToken).length()+offset,mvNextChar,mvFlag);
    }
    return nextToken;
}

int LatexTables::getColumn(QDocumentCursor &cur){
    QDocumentCursor c(cur);
    QStringList tokens("\\\\");
    int result=findNextToken(c,tokens,false,true);
    if(result==0) c.movePosition(2,QDocumentCursor::Right);

    tokens << "\\&" << "&";
    int col=0;

    do{
	result=findNextToken(c,tokens);
	if(c.lineNumber()>cur.lineNumber()|| (c.lineNumber()==cur.lineNumber() && c.columnNumber()>cur.columnNumber())) break;
	if(result==2) col++;
    }while(result>0);
    return col;
}

int LatexTables::getNumberOfColumns(QDocumentCursor &cur){
    QDocumentCursor c(cur);
    int result=findNextToken(c,QStringList(),false,true);
    if(result!=-2) return -1;
    QString line=c.line().text();
    int pos=line.indexOf("\\begin");
    if(pos>-1){
	QStringList values;
	LatexParser::resolveCommandOptions(line,pos,values);
	QString env=values.takeFirst();
	if(!env.startsWith("{")||!env.endsWith("}")) return -1;
	env=env.mid(1);
	env.chop(1);
	if(tabularNames.contains(env)){
	    while(!values.isEmpty()){
		QString opt=values.takeFirst();
		if(opt.startsWith("[")&&opt.endsWith("]")) continue;
		if(!opt.startsWith("{")||!opt.endsWith("}")) return -1;
		opt=opt.mid(1);
		opt.chop(1);
		//calculate number of columns ...
		int cols=0;
		//remove filler
		QRegExp rx("\\*\\{(.+)\\}\\{(.+)\\}");
		int pos=0;
		while ((pos = rx.indexIn(opt, pos)) != -1) {
		    QString m=rx.cap(1);
		    bool ok;
		    int mult=m.toInt(&ok);
		    if(!ok) break;
		    QString rep=rx.cap(2);
		    QString repl;
		    for(int i=0;i<mult;i++){
			repl+=rep;
		    }
		    opt.replace(pos,rx.matchedLength(),repl);
		}
		opt.replace(QRegExp("@\\{.+\\}"),"");
		opt.replace(QRegExp("p\\{.+\\}"),"p");
		opt.replace("|","");
		cols=opt.length();
		//return result
		return cols;
	    }
	    return -1;
	}else return -1; //maybe this needs to be changed
    }
    return -1;
}

bool LatexTables::inTableEnv(QDocumentCursor &cur){
    QDocumentCursor c(cur);
    int result=findNextToken(c,QStringList(),false,true);
    if(result!=-2) return false;
    if(c.lineNumber()==cur.lineNumber()) return false;
    QString line=c.line().text();
    int pos=line.indexOf("\\begin");
    if(pos>-1){
	QStringList values;
	LatexParser::resolveCommandOptions(line,pos,values);
	QString env=values.takeFirst();
	if(!env.startsWith("{")||!env.endsWith("}")) return -1;
	env=env.mid(1);
	env.chop(1);
	if(tabularNames.contains(env,Qt::CaseSensitive)||tabularNamesWithOneOption.contains(env,Qt::CaseSensitive)){
	    int result=findNextToken(c,QStringList());
	    if(result!=-2) return false;
	    if(c.lineNumber()>cur.lineNumber()) return true;
	}
    }
    return false;
}
