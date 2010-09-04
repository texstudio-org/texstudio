#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "smallUsefulFunctions.h"
#include "tablemanipulation.h"

QStringList LatexTables::tabularNames = QStringList() << "tabular" << "array" << "longtable" << "supertabular";
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
	//if last line before end, check whether the user was too lazy to put in a linebreak
	if(result==-2){
	    QDocumentCursor ch(cur);
	    int res=findNextToken(ch,tokens,true,true);
	    if(res==-2){
		cur.movePosition(1,QDocumentCursor::Left);
		cur.insertText("\\\\\n");
	    }else{
		ch.movePosition(2,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
		if(ch.selectedText().contains(QRegExp("^\\S+$"))){
		    cur.movePosition(1,QDocumentCursor::Left);
		    cur.insertText("\\\\\n");
		}
	    }
	}
	//
	//result=findNextToken(cur,tokens);
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
	// check if end of cursor is at line end
	QDocumentCursor c2(cur.document(),cur.anchorLineNumber(),cur.anchorColumnNumber());
	if(c2.atLineEnd()) {
	    c2.movePosition(1,QDocumentCursor::Right);
	    cur.moveTo(c2,QDocumentCursor::KeepAnchor);
	}
	// remove text
	cur.beginEditBlock();
	cur.removeSelectedText();
	if(cur.line().text().isEmpty()) cur.deleteChar(); // don't leave empty lines
	cur.endEditBlock();
    }
}

void LatexTables::addColumn(QDocument *doc,const int lineNumber,const int afterColumn,QStringList *cutBuffer){
    QDocumentCursor cur(doc);
    QStringList pasteBuffer;
    if(cutBuffer) pasteBuffer=*cutBuffer;
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
	    breakLoop=(result<0); // end of tabular reached (eof or \end)
	    if(result<1) break; //end of tabular line reached
	}
	if(result==-1) break;
	//if last line before end, check whether the user was too lazy to put in a linebreak
	if(result==-2){
	    QDocumentCursor ch(cur);
	    QStringList tokens("\\\\");
	    int res=findNextToken(ch,tokens,true,true);
	    if(res==0){
		ch.movePosition(2,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
		if(ch.selectedText().contains(QRegExp("^\\S+$")))
		    break;
	    }
	}
	// add element
	if(result==2){
	    if(pasteBuffer.isEmpty()) {
		cur.insertText(" &");
	    }else{
		cur.insertText(pasteBuffer.takeFirst()+"&");
	    }
	}
	if(result<=0){
	    int count= result==0 ? 2 : 1;
	    cur.movePosition(count,QDocumentCursor::Left);
	    if(pasteBuffer.isEmpty()) {
		cur.insertText("& ");
	    }else{
		cur.insertText("&"+pasteBuffer.takeFirst());
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
	int off=0;
	for(int col=0;col<column;col++){
	    if(off>0) off--;
	    cur.clearSelection();
	    QDocumentCursor oldCur(cur);
	    do{
		result=findNextToken(cur,nTokens,true);
	    }while(result==1);
	    QString selText=cur.selectedText();
	    if(selText.startsWith("\\multicolumn")){
		int add=getNumOfColsInMultiColumn(selText);
		if(off==0) off=add;
		if(off>1) cur=oldCur;
	    }
	    breakLoop=(result<0); // end of tabular reached (eof or \end)
	    if(result<1) break; //end of tabular line reached
	}
	cur.clearSelection();
	if(result==-1) break;
	// add element
	if(result>0 || off){
	    do{
		result=findNextToken(cur,nTokens,true);
	    }while(result==1);
	    QString selText=cur.selectedText();
	    int add=0;
	    if(selText.startsWith("\\multicolumn")){
		add=getNumOfColsInMultiColumn(selText);
	    }
	    if(add>1) {
		//multicolumn handling
		QStringList values;
		LatexParser::resolveCommandOptions(selText,0,values);
		values.takeFirst();
		values.prepend(QString("{%1}").arg(add-1));
		cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		if(result==0) cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		cur.insertText("\\multicolumn"+values.join(""));
	    }else{
		//normal handling
		if(result==2 && column>0) {
		    cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		}
		if(result==0) {
		    cur.movePosition(2,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		}
		if(cutBuffer){
		    QString zw=cur.selectedText();
		    if(column==0) zw.chop(1);
		    cutBuffer->append(zw);
		}
		cur.removeSelectedText();
		if(column>0) {
		    cur.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
		    cur.removeSelectedText();
		}
	    }
	    const QStringList tokens("\\\\");
	    breakLoop=(findNextToken(cur,tokens)==-1);
	}
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
	    if(!backwards&&cur.lineNumber()>=cur.document()->lineCount()-1) break;
	    if(backwards&&cur.lineNumber()==0) break;
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
    int result=findNextToken(c,tokens,true,true);
    if(result==0) c.movePosition(2,QDocumentCursor::Right);
    if(c.lineNumber()==cur.lineNumber() && c.selectedText().contains(QRegExp("^\\s*$"))){
	c.movePosition(1,QDocumentCursor::EndOfLine,QDocumentCursor::KeepAnchor);
	QString zw=c.selectedText();
	if(zw.contains(QRegExp("^\\s*$"))) return -1;
    }

    c.clearSelection();

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
	int numberOfOptions=-1;
	if(tabularNames.contains(env)) numberOfOptions=0;
	if(tabularNamesWithOneOption.contains(env)) numberOfOptions=1;
	if(numberOfOptions>=0){
	    while(!values.isEmpty()){
		QString opt=values.takeFirst();
		if(opt.startsWith("[")&&opt.endsWith("]")) continue;
		if(numberOfOptions>0) {
		    numberOfOptions--;
		    continue;
		}
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

int LatexTables::getNumOfColsInMultiColumn(const QString &str){
    //return the number of columsn in mulitcolumn command
    QStringList values;
    LatexParser::resolveCommandOptions(str,0,values);
    if(!values.isEmpty()){
	QString zw=values.takeFirst();
	if(zw.startsWith("{")&&zw.endsWith("}")){
	    zw.chop(1);
	    zw=zw.mid(1);
	    bool ok;
	    int col=zw.toInt(&ok);
	    if(ok) return col;
	}
    }
    return -1;
}
