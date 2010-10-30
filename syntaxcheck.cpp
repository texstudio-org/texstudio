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

void SyntaxCheck::putLine(QString text,QDocumentLineHandle* dlh,Environment previous,bool clearOverlay){
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
		checkLine(line,newRanges,activeEnv);
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


void SyntaxCheck::checkLine(QString &line,Ranges &newRanges,QStack<Environment> &activeEnv){
	// do syntax check on that line
	QString word;
	int start=0;
	int wordstart;
	int status;
	bool inStructure=false;
	while ((status=nextWord(line,start,word,wordstart,true,true,&inStructure))){
		if(status==NW_COMMAND){
			bool end=false;
			if(word=="\\begin"||word=="\\end"){
				end= (word=="\\end");
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
			if((activeEnv.top()==ENV_normal||end)&&!LatexParser::normalCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)){ // extend for math coammnds
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedCommand;
				if(LatexParser::mathCommands.contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(LatexParser::tabularCommands.contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				newRanges.append(elem);
			}
			if(activeEnv.top()==ENV_matrix && (word=="&" || word=="\\\\")) continue;
			if((activeEnv.top()==ENV_math||activeEnv.top()==ENV_matrix)&&!LatexParser::mathCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)&&!end){ // extend for math coammnds
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
				newRanges.append(elem);
			}
		}

	}
}

QString SyntaxCheck::getErrorAt(QString &text,int pos,Environment previous){
	// do syntax check
	QString line=text;
	QStack<Environment> activeEnv;
	activeEnv.push(previous);
	line=LatexParser::cutComment(line);
	Ranges newRanges;
	checkLine(line,newRanges,activeEnv);
	// find Error at Position
	ErrorType result=ERR_none;
	foreach(Error elem,newRanges){
		if(elem.range.second<pos) continue;
		if(elem.range.first>pos) break;
		result=elem.type;
	}
	// now generate Error message

	QStringList messages;
	messages << tr("no error")<< tr("unrecognized command")<< tr("unrecognized math command")<< tr("unrecognized tabular command")<< tr("tabular command outside tabular env")<< tr("math command outside math env");
	return messages.value(int(result),tr("unknown"));
}
