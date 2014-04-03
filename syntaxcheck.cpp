#include "syntaxcheck.h"
#include "latexdocument.h"
#include "tablemanipulation.h"

SyntaxCheck::SyntaxCheck(QObject *parent) :
       SafeThread(parent), syntaxErrorFormat(-1), ltxCommands(0), newLtxCommandsAvailable(false)
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

void SyntaxCheck::putLine(QDocumentLineHandle* dlh,StackEnvironment previous,bool clearOverlay){
	REQUIRE(dlh);
	SyntaxLine newLine;
	dlh->ref(); // impede deletion of handle while in syntax check queue
	dlh->lockForRead();
	newLine.ticket=dlh->getCurrentTicket();
	dlh->unlock();
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
	ltxCommands = new LatexParser();
	
	forever {
		//wait for enqueued lines
		mLinesAvailable.acquire();
		if(stopped) break;
		
		if (newLtxCommandsAvailable) {
			mLtxCommandLock.lock();
			if (newLtxCommandsAvailable) {
				newLtxCommandsAvailable = false;
				*ltxCommands = newLtxCommands;
			}
			mLtxCommandLock.unlock();
		}
		
		// get Linedata
		mLinesLock.lock();
		SyntaxLine newLine=mLines.dequeue();
		mLinesLock.unlock();
		// do syntax check
		newLine.dlh->lockForRead();
		QString line=newLine.dlh->text();
		newLine.dlh->removeCookie(3); //remove possible errors from unclosed envs
		newLine.dlh->unlock();
		QVector<int>fmts=newLine.dlh->getFormats();
		for(int i=0;i<line.length() && i < fmts.size();i++){
			if(fmts[i]==verbatimFormat){
				line[i]=QChar(' ');
			}
		}
		StackEnvironment activeEnv=newLine.prevEnv;
		line=ltxCommands->cutComment(line);
		Ranges newRanges;
		
		checkLine(line,newRanges,activeEnv,newLine.dlh,newLine.ticket);
		// place results
		if(newLine.clearOverlay) newLine.dlh->clearOverlays(syntaxErrorFormat);
		//if(newRanges.isEmpty()) continue;
		newLine.dlh->lockForWrite();
		if(newLine.ticket==newLine.dlh->getCurrentTicket()){ // discard results if text has been changed meanwhile
			foreach(const Error& elem,newRanges)
				newLine.dlh->addOverlayNoLock(QFormatRange(elem.range.first,elem.range.second,syntaxErrorFormat));
			
			// active envs
			QVariant oldEnvVar=newLine.dlh->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
			StackEnvironment oldEnv;
			if(oldEnvVar.isValid())
				oldEnv=oldEnvVar.value<StackEnvironment>();
			bool cookieChanged=!equalEnvStack(oldEnv,activeEnv);
			//if excessCols has changed the subsequent lines need to be rechecked.
			if(cookieChanged){
				QVariant env;
				env.setValue(activeEnv);
				newLine.dlh->setCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE,env);
				newLine.dlh->ref(); // avoid being deleted while in queue
				//qDebug() << newLine.dlh->text() << ":" << activeEnv.size();
				emit checkNextLine(newLine.dlh,true,newLine.ticket);
			}
		}
		newLine.dlh->unlock();
		
		newLine.dlh->deref(); //if deleted, delete now
	}
	
	delete ltxCommands;
	ltxCommands = 0;
}


void SyntaxCheck::checkLine(const QString &line,Ranges &newRanges,StackEnvironment &activeEnv, QDocumentLineHandle *dlh,int ticket){
	// do syntax check on that line
	int cols=containsEnv(*ltxCommands, "tabular",activeEnv);
	LatexReader lr(*ltxCommands, line);
	int status;
	// check command-words
	while ((status=lr.nextWord(true))){
		const QString &word = lr.word;
		const int &wordstart = lr.wordStartIndex;
		if(status==LatexReader::NW_COMMAND){
			if(word=="\\begin"||word=="\\end"){
				QStringList options;
                QList<int> starts;
                ltxCommands->resolveCommandOptions(line,wordstart,options,&starts);
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
						tp.excessCol=0;
						tp.dlh=dlh;
						tp.ticket=ticket;
						if(env=="tabular" || ltxCommands->environmentAliases.values(env).contains("tabular")){
							// tabular env opened
							// get cols !!!!
                            if(((env=="tabu")||(env=="longtabu"))&&options.size()==1){ // special treatment as the env is rather not latex standard
                                QString helper=line.mid(starts.first()+options.first().length());
                                helper=helper.trimmed();
                                if(helper.startsWith("to ")||helper.startsWith("spread ")){
                                    int i=helper.indexOf("{");
                                    if(i>-1){
                                        QStringList options_zw;
                                        ltxCommands->resolveCommandOptions(helper,i,options_zw);
                                        if(!options_zw.isEmpty()){
                                            options<<options_zw.first();
                                        }
                                    }
                                }
                            }
                            cols=LatexTables::getNumberOfColumns(options);
							tp.id=cols;
						}
						activeEnv.push(tp);
					}else{
						if(!activeEnv.isEmpty()){
							Environment tp=activeEnv.top();
							if(tp.name==env){
								activeEnv.pop();
								if(tp.name=="tabular" || ltxCommands->environmentAliases.values(tp.name).contains("tabular")){
									// correct length of col error if it exists
									if(!newRanges.isEmpty()){
										Error &elem=newRanges.last();
										if(elem.type==ERR_tooManyCols && elem.range.first+elem.range.second>wordstart){
											elem.range.second=wordstart-elem.range.first;
										}
									}
									// get new cols
									cols=containsEnv(*ltxCommands, "tabular",activeEnv);
								}
							}else{
								Error elem;
								elem.range=QPair<int,int>(wordstart,word.length());
								elem.type=ERR_closingUnopendEnv;
								newRanges.append(elem);
							}
						}else{
							Error elem;
							elem.range=QPair<int,int>(wordstart,word.length());
							elem.type=ERR_closingUnopendEnv;
							newRanges.append(elem);
						}
					}
					// add env-name for syntax checking to "word"
					lr.word+=options.first();
				}
			}
			if(ltxCommands->possibleCommands["%definition"].contains(word)){ // don't check in command definition
				QStringList options;
				QList<int> starts;
				ltxCommands->resolveCommandOptions(line,wordstart,options,&starts);
				for(int i=1;i<options.count()&&i<4;i++){
					QString option=options.at(i);
					if(option.startsWith("[")){
						continue;
					}
					lr.index=starts.at(i)+option.length();
					break;
				}
			}
            if(ltxCommands->possibleCommands["%ref"].contains(word)||ltxCommands->possibleCommands["%label"].contains(word)||ltxCommands->possibleCommands["%file"].contains(word)||ltxCommands->possibleCommands["%cite"].contains(word)||ltxCommands->possibleCommands["%bibitem"].contains(word)||ltxCommands->possibleCommands["%url"].contains(word)){ //don't check syntax in reference, label or include
				QStringList options;
				QList<int> starts;
				ltxCommands->resolveCommandOptions(line,wordstart,options,&starts);
				while(options.size()>0){
					QString first=options.takeFirst();
					int start=starts.takeFirst();
					lr.index=start+first.length();
					if(!first.startsWith("[")){  //handling of includegraphics should be improved !!!
						break;
					}
				}
			}
			if(ltxCommands->mathStartCommands.contains(word)&&(activeEnv.isEmpty()||activeEnv.top().name!="math")){
				Environment env;
				env.name="math";
				env.id=1; // to be changed
				env.dlh=dlh;
				env.ticket=ticket;
				activeEnv.push(env);
				continue;
			}
			if(ltxCommands->mathStopCommands.contains(word)&&!activeEnv.isEmpty()&&activeEnv.top().name=="math"){
				activeEnv.pop();
				continue;
			}
			if(ltxCommands->possibleCommands["user"].contains(word)||ltxCommands->customCommands.contains(word))
				continue;
			
			//tabular checking
			if(topEnv("tabular",activeEnv)!=0){
				if(word=="&"){
					activeEnv.top().excessCol++;
					if(activeEnv.top().excessCol>=activeEnv.top().id){
						Error elem;
						elem.range=QPair<int,int>(wordstart,word.length());
						elem.type=ERR_tooManyCols;
						newRanges.append(elem);
					}
					continue;
				}
                if((word=="\\\\")||(word=="\\tabularnewline")){
					if(activeEnv.top().excessCol<(activeEnv.top().id-1)){
						Error elem;
						elem.range=QPair<int,int>(wordstart,word.length());
						elem.type=ERR_tooLittleCols;
						newRanges.append(elem);
					}
					if(activeEnv.top().excessCol>=(activeEnv.top().id)){
						Error elem;
						elem.range=QPair<int,int>(wordstart,word.length());
						elem.type=ERR_tooManyCols;
						newRanges.append(elem);
					}
					activeEnv.top().excessCol=0;
					continue;
				}
				if(word=="\\multicolumn"){
					QRegExp rxMultiColumn("\\\\multicolumn\\{(\\d+)\\}\\{.+\\}\\{.+\\}");
					rxMultiColumn.setMinimal(true);
					int res=rxMultiColumn.indexIn(line,wordstart);
					if(res>-1){
						// multicoulmn before &
						bool ok;
						int c=rxMultiColumn.cap(1).toInt(&ok);
						if(ok){
							activeEnv.top().excessCol+=c-1;
						}
					}
					if(activeEnv.top().excessCol>=activeEnv.top().id){
						Error elem;
						elem.range=QPair<int,int>(wordstart,word.length());
						elem.type=ERR_tooManyCols;
						newRanges.append(elem);
					}
					continue;
				}
				
			}
			// ignore commands containing @
			if(word.contains('@'))
				continue;
			
			if(!checkCommand(word,activeEnv)){
				Error elem;
				elem.range=QPair<int,int>(wordstart,word.length());
				elem.type=ERR_unrecognizedCommand;
				
				if(ltxCommands->possibleCommands["math"].contains(word))
					elem.type=ERR_MathCommandOutsideMath;
				if(ltxCommands->possibleCommands["tabular"].contains(word))
					elem.type=ERR_TabularCommandOutsideTab;
				if(ltxCommands->possibleCommands["tabbing"].contains(word))
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
	line=ltxCommands->cutComment(line);
	Ranges newRanges;
	checkLine(line,newRanges,activeEnv,dlh,dlh->getCurrentTicket());
	// add Error for unclosed env
	QVariant var=dlh->getCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE);
	if(var.isValid()){
		activeEnv=var.value<StackEnvironment>();
		Q_ASSERT_X(activeEnv.size()==1,"SyntaxCheck","Cookie error");
		Environment env=activeEnv.top();
		QString cmd="\\begin{"+env.name+"}";
		int index=line.lastIndexOf(cmd);
		if(index>=0){
			Error elem;
			elem.range=QPair<int,int>(index,cmd.length());
			elem.type=ERR_EnvNotClosed;
			newRanges.append(elem);
		}
	}
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
	         << tr("\\\\ missing") << tr("closing environment which has not been opened") << tr("environment not closed");
	return messages.value(int(result),tr("unknown"));
}
void SyntaxCheck::setLtxCommands(const LatexParser& cmds){
	if (stopped) return;
	mLtxCommandLock.lock();
	newLtxCommandsAvailable = true;
	newLtxCommands = cmds;
	mLtxCommandLock.unlock();
}

void SyntaxCheck::waitForQueueProcess(){
	while(!crashed && mLinesAvailable.available()>0){
		wait(1);
	}
}

bool SyntaxCheck::queuedLines(){
	return mLinesAvailable.available()>0;
}

int SyntaxCheck::topEnv(const QString& name,const StackEnvironment& envs,const int id){
	if(envs.isEmpty())
		return 0;
	
	Environment env=envs.top();
	if(env.name==name){
		if(id<0 || env.id==id)
			return env.id;
	}
	if(id<0 && ltxCommands->environmentAliases.contains(env.name)){
		QStringList altEnvs=ltxCommands->environmentAliases.values(env.name);
		foreach(const QString& altEnv,altEnvs){
			if(altEnv==name)
				return env.id;
		}
	}
	return 0;
}

int SyntaxCheck::containsEnv(const LatexParser& parser, const QString& name,const StackEnvironment& envs,const int id){
	for (int i = envs.size()-1; i >-1; --i) {
		Environment env=envs.at(i);
		if(env.name==name){
			if(id<0 || env.id==id)
				return env.id;
		}
		if(id<0 && parser.environmentAliases.contains(env.name)){
			QStringList altEnvs=parser.environmentAliases.values(env.name);
			foreach(const QString& altEnv,altEnvs){
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
		if(ltxCommands->possibleCommands.contains(env.name) && ltxCommands->possibleCommands.value(env.name).contains(cmd))
			return true;
		if(ltxCommands->environmentAliases.contains(env.name)){
			QStringList altEnvs=ltxCommands->environmentAliases.values(env.name);
			foreach(const QString& altEnv,altEnvs){
				if(ltxCommands->possibleCommands.contains(altEnv) && ltxCommands->possibleCommands.value(altEnv).contains(cmd))
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

void SyntaxCheck::markUnclosedEnv(Environment env){
	QDocumentLineHandle *dlh=env.dlh;
	if(!dlh)
		return;
	dlh->lockForWrite();
	if(dlh->getCurrentTicket()==env.ticket){
		QString line=dlh->text();
		line=ltxCommands->cutComment(line);
		QString cmd="\\begin{"+env.name+"}";
		int index=line.lastIndexOf(cmd);
		if(index>=0){
			Error elem;
			elem.range=QPair<int,int>(index,cmd.length());
			elem.type=ERR_EnvNotClosed;
			dlh->addOverlayNoLock(QFormatRange(elem.range.first,elem.range.second,syntaxErrorFormat));
			QVariant var_env;
			StackEnvironment activeEnv;
			activeEnv.append(env);
			var_env.setValue(activeEnv);
			dlh->setCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE,var_env); //ERR_EnvNotClosed;
		}
	}
	dlh->unlock();
}
