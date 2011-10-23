#include "diffoperations.h"
#include "latexdocument.h"

void diffDocs(LatexDocument *doc,LatexDocument *doc2){

    QString text=doc->text();
    QString text2=doc2->text();
    diff_match_patch dmp;
    QList<Diff> diffList= dmp.diff_main(text, text2,true);
    dmp.diff_cleanupSemantic(diffList);
    int lineNr=0;
    int col=0;

    for(int i=0;i<diffList.size();++i){
	const Diff elem=diffList.at(i);
	if(elem.operation==EQUAL){
	    lineNr+=elem.text.count("\n");
	    col=elem.text.length();
	    if(elem.text.lastIndexOf("\n")>=0)
		col-=elem.text.lastIndexOf("\n")+1;
	}
	if(elem.operation==DELETE){
	    QStringList splitList=elem.text.split("\n");
	    QStringList splitListInsert;
	    if(splitList.isEmpty())
		continue;
	    QString lineDelete=splitList.takeFirst();
	    int diff=lineDelete.length();
	    bool toBeReplaced=false;
	    if(i+1<diffList.size() && diffList[i+1].operation==INSERT){
		splitListInsert=diffList[i+1].text.split("\n");
	    }
	    if( splitListInsert.size()>0 && (splitList.size()>1 || splitListInsert.size()>1) ){
		toBeReplaced=true;
	    }
	    QVariant var=doc->line(lineNr).getCookie(2);
	    DiffList lineData;

	    bool lineModified;

	    if(var.isValid()){
		lineData=var.value<DiffList>();
		if(lineData.isEmpty())
		    lineModified=doc->isLineModified(doc->line(lineNr));
		else
		    lineModified=lineData.first().lineWasModified;
	    } else {
		lineModified=doc->isLineModified(doc->line(lineNr));
	    }

	    //doc->line(lineNr).addOverlay(QFormatRange(col,diff,fid));
	    DiffOp diffOperation;
	    diffOperation.start=col;
	    diffOperation.length=diff;
	    diffOperation.lineWasModified=lineModified;
	    if(toBeReplaced){
		diffOperation.type=DiffOp::Replace;
		diffOperation.text=splitListInsert.takeFirst();
		if(splitList.isEmpty())
		    diffOperation.text+="\n"+splitListInsert.join("\n");
	    } else {
		diffOperation.type=DiffOp::Delete;
	    }
	    lineData.append(diffOperation);
	    doc->line(lineNr).setCookie(2,QVariant::fromValue<DiffList>(lineData));
	    col+=diff;
	    int sz=splitList.size();
	    for(int j=0;j<sz;j++){
		col=0;
		QString ln=splitList.takeFirst();
		DiffOp diffOperation;
		diffOperation.start=col;
		diffOperation.length=ln.length();
		if(toBeReplaced){
		    diffOperation.type=DiffOp::Replace;
		    if(splitListInsert.isEmpty()){
			diffOperation.text="";
		    }else{
			diffOperation.text=splitListInsert.takeFirst();
			if(splitList.isEmpty() && !splitListInsert.isEmpty())
			    diffOperation.text+="\n"+splitListInsert.join("\n");
		    }
		} else {
		    diffOperation.type=DiffOp::Delete;
		}

		var=doc->line(lineNr+j+1).getCookie(2);
		DiffList lineData;

		if(var.isValid()){
		    lineData=var.value<DiffList>();
		    if(lineData.isEmpty())
			lineModified=doc->isLineModified(doc->line(lineNr+j+1));
		    else
			lineModified=lineData.first().lineWasModified;
		} else {
		    lineModified=doc->isLineModified(doc->line(lineNr+j+1));
		}
		diffOperation.lineWasModified=lineModified;

		lineData.append(diffOperation);
		doc->line(lineNr+j+1).setCookie(2,QVariant::fromValue<DiffList>(lineData));
		col=ln.length();
	    }
	    lineNr+=elem.text.count("\n");
	    if(toBeReplaced)
		i++;
	}
	if(elem.operation==INSERT){
	    QStringList splitList=elem.text.split("\n");
	    if(splitList.isEmpty())
		continue;
	    QDocumentCursor cur(doc);
	    if(lineNr+1>doc->lines()){
		cur.moveTo(lineNr-1,0);
		cur.movePosition(1,QDocumentCursor::EndOfLine);
		cur.insertText("\n");
	    }else{
		cur.moveTo(lineNr,col);
	    }
	    int diff=splitList.first().length();
	    cur.insertText(splitList.first());
	    int lnNr=cur.lineNumber();
	    if(splitList.size()>1)
		cur.insertText("\n");
	    QVariant var=doc->line(lnNr).getCookie(2);
	    DiffList lineData;
	    bool lineModified;

	    if(var.isValid()){
		lineData=var.value<DiffList>();
		if(lineData.isEmpty())
		    lineModified=doc->isLineModified(doc->line(lnNr));
		else
		    lineModified=lineData.first().lineWasModified;
	    } else {
		lineModified=doc->isLineModified(doc->line(lnNr));
	    }

	    DiffOp diffOperation;
	    diffOperation.start=col;
	    diffOperation.length=diff;
	    diffOperation.type=DiffOp::Insert;
	    diffOperation.text="";
	    diffOperation.lineWasModified=lineModified;
	    lineData.append(diffOperation);
	    doc->line(lnNr).setCookie(2,QVariant::fromValue<DiffList>(lineData));
	    //doc->line(lnNr).addOverlay(QFormatRange(col,diff,fid_Insert));
	    col+=diff;
	    splitList.removeFirst();
	    for(int i=0;i<splitList.size();i++){
		QString ln=splitList.at(i);
		cur.insertText(ln);
		lnNr=cur.lineNumber();
		if(i+1<splitList.size())
		    cur.insertText("\n");
		QVariant var=doc->line(lnNr).getCookie(2);
		DiffList lineData;

		if(var.isValid()){
		    lineData=var.value<DiffList>();
		    if(lineData.isEmpty())
			lineModified=doc->isLineModified(doc->line(lnNr));
		    else
			lineModified=lineData.first().lineWasModified;
		} else {
		    lineModified=doc->isLineModified(doc->line(lnNr));
		}
		DiffOp diffOperation;
		diffOperation.start=0;
		diffOperation.length=ln.length();
		diffOperation.type=DiffOp::Insert;
		diffOperation.text="";
		diffOperation.lineWasModified=lineModified;
		lineData.append(diffOperation);
		doc->line(lnNr).setCookie(2,QVariant::fromValue<DiffList>(lineData));
		//doc->line(lnNr).addOverlay(QFormatRange(0,ln.length(),fid_Insert));
		col=ln.length();
	    }
	    lineNr+=elem.text.count("\n");
	}
    }
}
