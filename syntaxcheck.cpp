#include "syntaxcheck.h"
#include "latexdocument.h"
#include "tablemanipulation.h"

SyntaxCheck::SyntaxCheck(QObject *parent) :
		QThread(parent), syntaxErrorFormat(-1)
{
	mLinesLock.lock();
	stopped=false;
	mLines.clear();
	mLinesLock.unlock();
	verbatimFormat=0;
	//mLtxCommandLock.unlock();
}

void SyntaxCheck::setErrFormat(int errFormat){
	syntaxErrorFormat=errFormat;
}

void SyntaxCheck::putLine(QDocumentLineHandle* dlh,StackEnvironment previous,bool clearOverlay,int excessCols){
	REQUIRE(dlh);
	SyntaxLine newLine;
	dlh->ref(); // impede deletion of handle while in syntax check queue
	dlh->lockForRead();
	newLine.ticket=dlh->getCurrentTicket();
	dlh->unlock();
	newLine.dlh=dlh;
	newLine.prevEnv=previous;
	newLine.clearOverlay=clearOverlay;
	newLine.excessCols = excessCols;
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
		newLine.dlh->lockForRead();
		QString line=newLine.dlh->text();
		newLine.dlh->unlock();
		QVector<int>fmts=newLine.dlh->getFormats();
		for(int i=0;i<line.length() && i < fmts.size();i++){
			if(fmts[i]==verbatimFormat){
				line[i]=QChar(' ');
			}
		}
		StackEnvironment activeEnv=newLine.prevEnv;
		line=LatexParser::cutComment(line);
		Ranges newRanges;

		int excessCols=newLine.excessCols;
		checkLine(line,newRanges,activeEnv,excessCols);
		// place results
		if(newLine.clearOverlay) newLine.dlh->clearOverlays(syntaxErrorFormat);
		//if(newRanges.isEmpty()) continue;
		newLine.dlh->lockForWrite();
		if(newLine.ticket==newLine.dlh->getCurrentTicket()){ // discard results if text has been changed meanwhile
			foreach(const Error& elem,newRanges)
				newLine.dlh->addOverlayNoLock(QFormatRange(elem.range.first,elem.range.second,syntaxErrorFormat));

			int oldCookie=newLine.dlh->getCookie(0).toInt();
			bool cookieChanged=(oldCookie!=excessCols);
			// active envs
			QVariant oldEnvVar=newLine.dlh->getCookie(1);
			StackEnvironment oldEnv;
			if(oldEnvVar.isValid())
				oldEnv=oldEnvVar.value<StackEnvironment>();
			if(!equalEnvStack(oldEnv,activeEnv))
				cookieChanged=true;
			//if excessCols has changed the subsequent lines need to be rechecked.
			if(cookieChanged){
				newLine.dlh->setCookie(0,excessCols);
				QVariant env;
				env.setValue(activeEnv);
				newLine.dlh->setCookie(1,env);
				newLine.dlh->ref(); // avoid being deleted while in queue
				//qDebug() << newLine.dlh->text() << ":" << activeEnv.size();
				emit checkNextLine(newLine.dlh,true,excessCols,newLine.ticket);
			}
		}
		newLine.dlh->unlock();

		newLine.dlh->deref(); //if deleted, delete now
	}
}


void SyntaxCheck::checkLine(QString &line,Ranges &newRanges,StackEnvironment &activeEnv,int &excessCols){
	// do syntax check on that line
	QMutexLocker locker(&mLtxCommandLock);
	QString word;
	int cols=containsEnv("tabular",activeEnv);
	int start=0;
	int wordstart;
	int status;
	bool inStructure=false;
	// do additional checks (not limited to commands)
	// check tabular compliance (columns)
	int count=0;
	if(containsEnv("tabular",activeEnv)){
		count=excessCols;
		int end=line.indexOf("\\\\");
		int pos=-1;
		int wrongPos=-1;
		int res=-1;
		int lastEnd=-1;
		while(end>=0){
			QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
			rxMultiColumn.setMinimal(true);
			bool mc_found=false;
			do{
				res=rxMultiColumn.indexIn(line,pos+1);
				do{
					wrongPos=line.indexOf("\\&",pos+1);
					pos=line.indexOf("&",pos+1);
				} while(wrongPos>-1 && wrongPos+1==pos);
				if(res>-1 && (res<pos || pos<0) ){
					// multicoulmn before &
					bool ok;
					int c=rxMultiColumn.cap(1).toInt(&ok);
					if(ok){
						count+=c-2;
					}
					mc_found=true;
					if(pos<0){
						count+=2;
						break;
					}
					pos=res+1;
				}else{
					mc_found=false;
				}
				count++;
			} while(pos>=0 && count<cols && pos<end);
			if((pos>=0 && pos<end &&!mc_found)||(count>cols)){
				if(mc_found)
					pos=res-1;
				Error elem;
				elem.range=QPair<int,int>(pos,end-pos);
				elem.type=ERR_tooManyCols;
				newRanges.append(elem);
			}
			if((pos==-1 || pos>end) && count<cols){
				Error elem;
				elem.range=QPair<int,int>(end,2);
				elem.type=ERR_tooLittleCols;
				newRanges.append(elem);
			}
			lastEnd=end;
			end=line.indexOf("\\\\",end+2);
			count=0;
			pos=lastEnd;
		}
		pos=lastEnd;
		// check for columns beyond last newline
		QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
		rxMultiColumn.setMinimal(true);
		bool mc_found=false;
		end=line.length();
		int lastPos=0;
		do{
			int res=rxMultiColumn.indexIn(line,pos+1);
			//pos=line.indexOf(QRegExp("[^\\\\]&"),pos+1);
			//pos=line.indexOf(QRegExp("([^\\\\]|^)&"),pos+1);
			do{
				wrongPos=line.indexOf("\\&",pos+1);
				pos=line.indexOf("&",pos+1);
			} while(wrongPos>-1 && wrongPos+1==pos);
			if(res>-1 && (res<pos || pos<0) ){
				// multicoulmn before &
				bool ok;
				int c=rxMultiColumn.cap(1).toInt(&ok);
				if(ok){
					count+=c-1;
				}
				pos=res+rxMultiColumn.cap().length()-1;
				mc_found=true;
			}else{
				mc_found=false;
			}
			count++;
			if(count>cols && (res>-1 || lastPos>-1)){
				if(mc_found)
					lastPos=res-1;
				Error elem;
				elem.range=QPair<int,int>(lastPos,end-lastPos);
				elem.type=ERR_tooManyCols;
				newRanges.append(elem);
			}
			lastPos=pos;
		} while(pos>=0);
		excessCols=count-1;
	}// tabular checking
	// check command-words
	while ((status=nextWord(line,start,word,wordstart,true,true,&inStructure))){
		if(status==NW_COMMAND){
			if(word=="\\begin"||word=="\\end"){
				QStringList options;
				LatexParser::resolveCommandOptions(line,wordstart,options);
				if(options.size()>0){
					// adapt env stack
					QString env=options.first();
					if(env.startsWith("{"))
						env=env.remove(0,1);
					if(env.endsWith("}"))
						env.chop(1);
					if(word=="\\begin"){
						Environment tp;
						tp.name=env;
						tp.id=1; //needs correction
						if(env=="tabular" || LatexParser::environmentAliases.values(env).contains("tabular")){
							// tabular env opened
							// get cols !!!!
							cols=LatexTables::getNumberOfColumns(options);
							tp.id=cols;
						}
						activeEnv.push(tp);
					}else{
						Environment tp=activeEnv.top();
						if(tp.name==env){
							activeEnv.pop();
							if(tp.name=="tabular" || LatexParser::environmentAliases.values(tp.name).contains("tabular")){
								// stop excesscols from being handed on
								excessCols=0;
								// correct length of col error if it exists
								if(!newRanges.isEmpty()){
								    Error &elem=newRanges.last();
								    if(elem.type==ERR_tooManyCols && elem.range.first+elem.range.second>wordstart){
									elem.range.second=wordstart-elem.range.first;
								    }
								}
								// get new cols
								cols=containsEnv("tabular",activeEnv);
							}
						}
					}
					// add env-name for syntax checking to "word"
					word+=options.first();
				}
			}
			if(LatexParser::definitionCommands.contains(word)){ // don't check in command definition
				QStringList options;
				QList<int> starts;
				LatexParser::resolveCommandOptions(line,wordstart,options,&starts);
				for(int i=1;i<options.count()&&i<4;i++){
					QString option=options.at(i);
					if(option.startsWith("[")){
						continue;
					}
					start=starts.at(i)+option.length();
					break;
				}
			}
			if(ltxCommands.refCommands.contains(word)||LatexParser::labelCommands.contains(word)||LatexParser::fileCommands.contains(word)||LatexParser::citeCommands.contains(word)){ //don't check syntax in reference, label or include
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
			if(LatexParser::mathStartCommands.contains(word)&&activeEnv.top().name!="math"){
				Environment env;
				env.name="math";
				env.id=1; // to be changed
				activeEnv.push(env);
				continue;
			}
			if(LatexParser::mathStopCommands.contains(word)&&activeEnv.top().name=="math"){
				activeEnv.pop();
				continue;
			}
			if(ltxCommands.possibleCommands["user"].contains(word)||LatexParser::customCommands.contains(word))
				continue;

			if(!checkCommand(word,activeEnv)){
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedCommand;

				if(ltxCommands.possibleCommands["math"].contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(ltxCommands.possibleCommands["tabular"].contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				if(ltxCommands.possibleCommands["tabbing"].contains(word))
					elem.type=ERR_TabbingCommandOutside;
				newRanges.append(elem);
			}
		}

	}


}

QString SyntaxCheck::getErrorAt(QDocumentLineHandle *dlh,int pos,StackEnvironment previous){
	// do syntax check
	QString line=dlh->text();
	QVector<int>fmts=dlh->getFormats();
	for(int i=0;i<line.length() && i < fmts.size();i++){
		if(fmts[i]==verbatimFormat){
			line[i]=QChar(' ');
		}
	}
	QStack<Environment> activeEnv=previous;
	line=LatexParser::cutComment(line);
	Ranges newRanges;
	int excessCols=0;
	dlh->lockForRead();
	QDocumentLineHandle *prev=dlh->previous();
	dlh->unlock();
	if(prev){
		prev->lockForRead();
		excessCols=prev->getCookie(0).toInt();
		prev->unlock();
	}
	checkLine(line,newRanges,activeEnv,excessCols);
	// find Error at Position
	ErrorType result=ERR_none;
	foreach(const Error& elem,newRanges){
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
void SyntaxCheck::setLtxCommands(LatexParser cmds){
	QMutexLocker locker(&mLtxCommandLock);
	ltxCommands=cmds;
}

void SyntaxCheck::waitForQueueProcess(){
	while(mLinesAvailable.available()>0){
		wait(1);
	}
}

bool SyntaxCheck::queuedLines(){
	return mLinesAvailable.available()>0;
}

int SyntaxCheck::containsEnv(const QString& name,const StackEnvironment& envs,const int id){
	for (int i = envs.size()-1; i >-1; --i) {
		Environment env=envs.at(i);
		if(env.name==name){
			if(id<0 || env.id==id)
				return env.id;
		}
		if(id<0 && LatexParser::environmentAliases.contains(env.name)){
			QStringList altEnvs=LatexParser::environmentAliases.values(env.name);
			foreach(QString altEnv,altEnvs){
				if(altEnv==name)
					return env.id;
			}
		}
	}
	return 0;
}

bool SyntaxCheck::checkCommand(const QString &cmd,const StackEnvironment &envs){
	for (int i = 0; i < envs.size(); ++i) {
		Environment env=envs.at(i);
		if(ltxCommands.possibleCommands.contains(env.name) && ltxCommands.possibleCommands.value(env.name).contains(cmd))
			return true;
		if(LatexParser::environmentAliases.contains(env.name)){
			QStringList altEnvs=LatexParser::environmentAliases.values(env.name);
			foreach(QString altEnv,altEnvs){
				if(ltxCommands.possibleCommands.contains(altEnv) && ltxCommands.possibleCommands.value(altEnv).contains(cmd))
					return true;
			}
		}
	}
	return false;
}

bool SyntaxCheck::equalEnvStack(StackEnvironment env1,StackEnvironment env2){
	if(env1.isEmpty() || env2.isEmpty())
		return env1.isEmpty() && env2.isEmpty();
	if(env1.size()!=env2.size())
		return false;
	for(int i=0;i<env1.size();i++){
		if(env1.value(i)!=env2.value(i))
			return false;
	}
	return true;
}
