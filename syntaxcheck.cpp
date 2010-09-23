#include "syntaxcheck.h"

SyntaxCheck::SyntaxCheck(QObject *parent) :
    QThread(parent)
{
    mResultLock.lock();
    mLinesLock.lock();
    mLines.clear();
    mResults.clear();
    mLinesLock.unlock();
    mResultLock.unlock();
}

void SyntaxCheck::putLine(QString line){
    mLinesLock.lock();
    mLines.enqueue(line);
    mLinesLock.unlock();
    //avoid reading of any results before this execution is stopped
    mResultLock.lock();
    mLinesAvailable.release();
}

bool SyntaxCheck::isEmpty(){
    mResultLock.lock();
    bool res=mResults.isEmpty();
    mResultLock.lock();
    return res;
}

QList<QPair<int,int> > SyntaxCheck::getResult(){
    mResultLock.lock();
    Ranges *rng;
    QList<QPair<int,int> > result;
    if(!mResults.isEmpty()){
	rng=mResults.dequeue();
	result=*rng;
	delete rng;
    }
    mResultLock.unlock();
    return result;
}

void SyntaxCheck::run(){
    forever {
	     //wait for enqueued lines
	     mLinesAvailable.acquire();

	     // copy line
	     mLinesLock.lock();
	     QString line=mLines.dequeue();
	     mLinesLock.unlock();
             line=LatexParser::cutComment(line);
	     Ranges* newRanges=new Ranges;
	     // do syntax check on that lien
             QString word;
             int start=0;
             int wordstart;
             int status;
             bool inStructure=false;
             while ((status=nextWord(line,start,word,wordstart,true,true,&inStructure))){
                 if(status==NW_COMMAND){
                     if(!LatexParser::normalCommands.contains(word) && !LatexParser::userdefinedCommands.contains(word)){ // extend for math coammnds
                         QPair<int,int> elem(wordstart,word.length());
                         newRanges->append(elem);
                     }
                 }

	     }
	     // place results
	     mResults.enqueue(newRanges);
	     mResultLock.unlock();
	 }
}
