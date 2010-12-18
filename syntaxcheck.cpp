#include "syntaxcheck.h"

SyntaxCheck::SyntaxCheck(QObject *parent) :
		QThread(parent)
{
	mLinesLock.lock();
	stopped=false;
	mLines.clear();
	mLinesLock.unlock();
}

void SyntaxCheck::setErrFormat(int errFormat){
	syntaxErrorFormat=errFormat;
}

void SyntaxCheck::putLine(QString text,QDocumentLineHandle* dlh,Environment previous,bool clearOverlay,int cols){
	Q_ASSERT(dlh);
	SyntaxLine newLine;
	dlh->ref(); // impede deletion of handle while in syntax check queue
	dlh->lockForRead();
	newLine.ticket=dlh->getCurrentTicket();
	dlh->unlock();
	newLine.text=text;
	newLine.dlh=dlh;
	newLine.prevEnv=previous;
	newLine.clearOverlay=clearOverlay;
	newLine.cols=cols;
	mLinesLock.lock();
	mLines.enqueue(newLine);
	mLinesLock.unlock();
	//avoid reading of any results before this execution is stopped
	//mResultLock.lock(); not possible under windows
	mLinesAvailable.release();
}

void SyntaxCheck::stop(){
	stopped=true;
	mLinesAvailable.release();
}

void SyntaxCheck::run(){
	forever {
		//wait for enqueued lines
		mLinesAvailable.acquire();
		if(stopped) break;
		// get Linedata
		mLinesLock.lock();
		SyntaxLine newLine=mLines.dequeue();
		mLinesLock.unlock();
		// do syntax check
		QString line=newLine.text;
		QStack<Environment> activeEnv;
		activeEnv.push(newLine.prevEnv);
		line=LatexParser::cutComment(line);
		Ranges newRanges;
		checkLine(line,newRanges,activeEnv,newLine.cols);
		// place results
		if(newLine.clearOverlay) newLine.dlh->clearOverlays(syntaxErrorFormat);
		if(newRanges.isEmpty()) continue;
		newLine.dlh->lockForWrite();
		if(newLine.ticket==newLine.dlh->getCurrentTicket()){ // discard results if text has been changed meanwhile
			Error elem;
			foreach(elem,newRanges){
				newLine.dlh->addOverlayNoLock(QFormatRange(elem.range.first,elem.range.second,syntaxErrorFormat));
			}
		}
		newLine.dlh->unlock();
		newLine.dlh->deref(); //if deleted, delete now
	}
}


void SyntaxCheck::checkLine(QString &line,Ranges &newRanges,QStack<Environment> &activeEnv,int cols){
	// do syntax check on that line
	QString word;
	int start=0;
	int wordstart;
	int status;
	bool inStructure=false;
	// do additional checks (not limited to commands)
	// check tabular compliance (columns)
	if(activeEnv.top()==ENV_tabular){
	    int end=line.indexOf("\\\\");
	    if(end>=0){
		int pos=-1;
		int count=0;
		QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
		rxMultiColumn.setMinimal(true);
		do{
		    int res=rxMultiColumn.indexIn(line,pos+1);
		    //pos=line.indexOf(QRegExp("[^\\\\]&"),pos+1);
		    pos=line.indexOf(QRegExp("([^\\\\]|^)&"),pos+1);
		    if(res>-1 && (res<pos || pos<0) ){
			// multicoulmn before &
			bool ok;
			int c=rxMultiColumn.cap(1).toInt(&ok);
			if(ok){
			    count+=c-1;
			}
			pos=res+rxMultiColumn.cap().length()-1;
		    }
		    count++;
		} while(pos>=0 && count<cols && pos<end);
		if(pos>end)
		    pos=-1;
		if(pos>=0){
		    Error elem;
		    elem.range=QPair<int,int>(pos+1,end-pos-1);
		    elem.type=ERR_tooManyCols;
		    newRanges.append(elem);
		}
		if(pos==-1 && count<cols){
		    Error elem;
		    elem.range=QPair<int,int>(end,2);
		    elem.type=ERR_tooLittleCols;
		    newRanges.append(elem);
		}
	    }else{
		/* deactivated as a little too irritating
		// missing newline
		Error elem;
		elem.range=QPair<int,int>(0,line.length());
		elem.type=ERR_missingEndOfLine;
		newRanges.append(elem);
		*/
	    }
	}
	// check command-words
	while ((status=nextWord(line,start,word,wordstart,true,true,&inStructure))){
		if(status==NW_COMMAND){
			bool ignoreEnv=false;
			if(word=="\\begin"||word=="\\end"){
				QStringList options;
				LatexParser::resolveCommandOptions(line,wordstart,options);
				if(options.size()>0){
					word+=options.first();
				}
			}
			if(LatexParser::refCommands.contains(word)||LatexParser::labelCommands.contains(word)||LatexParser::fileCommands.contains(word)){ //don't check syntax in reference, label or include
				QStringList options;
				LatexParser::resolveCommandOptions(line,wordstart,options);
				if(options.size()>0){
					QString first=options.takeFirst();
					if(!first.startsWith("[")){  //handling of includegraphics should be improved !!!
						start+=first.length();
					}else{
						if(!options.isEmpty()){
							QString second=options.first();
							if(second.startsWith("{")){
								second.fill(' ');
								line.replace(start+first.length(),second.length(),second);
							}
						}
					}
				}
			}
			if(LatexParser::mathStartCommands.contains(word)&&activeEnv.top()!=ENV_math){
				activeEnv.push(ENV_math);
				continue;
			}
			if(LatexParser::mathStopCommands.contains(word)&&activeEnv.top()==ENV_math){
				activeEnv.pop();
				if(activeEnv.isEmpty()) activeEnv.push(ENV_normal);
				continue;
			}
			if(ignoreEnv&&(LatexParser::normalCommands.contains(word) || LatexParser::tabularCommands.contains(word) || LatexParser::userdefinedCommands.contains(word) || LatexParser::mathCommands.contains(word)|| LatexParser::tabbingCommands.contains(word)) )
			    continue;
			if((activeEnv.top()==ENV_tabbing)&&!LatexParser::tabbingCommands.contains(word) &&!LatexParser::normalCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)){ // extend for math coammnds
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedCommand;
				if(LatexParser::mathCommands.contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(LatexParser::tabularCommands.contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				newRanges.append(elem);
			}
			if((activeEnv.top()==ENV_normal)&&!LatexParser::normalCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)){ // extend for math coammnds
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedCommand;
				if(LatexParser::mathCommands.contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(LatexParser::tabularCommands.contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				if(LatexParser::tabbingCommands.contains(word))
					elem.type=ERR_TabbingCommandOutside;
				newRanges.append(elem);
			}
			if(activeEnv.top()==ENV_matrix && (word=="&" || word=="\\\\")) continue;
			if((activeEnv.top()==ENV_math||activeEnv.top()==ENV_matrix)&&!LatexParser::mathCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)&&!ignoreEnv){ // extend for math coammnds
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedMathCommand;
				if(LatexParser::tabularCommands.contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				newRanges.append(elem);
			}
			if(activeEnv.top()==ENV_tabular&&!LatexParser::normalCommands.contains(word) && !LatexParser::tabularCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)){ // extend for math coammnds
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedTabularCommand;
				if(LatexParser::mathCommands.contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(LatexParser::tabbingCommands.contains(word))
					elem.type=ERR_TabbingCommandOutside;
				newRanges.append(elem);
			}
		}

	}


    }

QString SyntaxCheck::getErrorAt(QString &text,int pos,Environment previous,int cols){
	// do syntax check
	QString line=text;
	QStack<Environment> activeEnv;
	activeEnv.push(previous);
	line=LatexParser::cutComment(line);
	Ranges newRanges;
	checkLine(line,newRanges,activeEnv,cols);
	// find Error at Position
	ErrorType result=ERR_none;
	foreach(Error elem,newRanges){
		if(elem.range.second+elem.range.first<pos) continue;
		if(elem.range.first>pos) break;
		result=elem.type;
	}
	// now generate Error message

	QStringList messages;
	messages << tr("no error")<< tr("unrecognized command")<< tr("unrecognized math command")<< tr("unrecognized tabular command")<< tr("tabular command outside tabular env")<< tr("math command outside math env") << tr("tabbing command outside tabbing env") << tr("more cols in tabular than specified") << tr("cols in tabular missing")
		 << tr("\\\\ missing");
	return messages.value(int(result),tr("unknown"));
}
