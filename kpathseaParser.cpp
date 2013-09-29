#include "kpathseaParser.h"

KpathSeaParser::KpathSeaParser(QObject *parent,QString kpsecmd) :
    SafeThread(parent)
{
    kpseWhichCmd=kpsecmd;
}



void KpathSeaParser::run(){
    QString fullName=kpsewhich(); // find lcoations of ls-R (file database of tex)
	if(fullName.isEmpty())
        return;
    QStringList lstOfFiles=fullName.split(":");
    QStringList results;
    QStringList::iterator it;
    foreach(QString fn,lstOfFiles){
        fn=fn.trimmed()+"/ls-R";
        QFile data(fn);
        QString line;
        if(data.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&data);
            while(!stream.atEnd()) {
                line = stream.readLine();
                if(line.endsWith(".sty")||line.endsWith(".cls")){
                    line.chop(4);
                    it=qLowerBound(results.begin(),results.end(),line);
                    if(it==results.end() || *it!=line)
                        results.insert(it,line);
                }
            }
        }
    }
    emit scanCompleted(results);
}



QString KpathSeaParser::kpsewhich(){
    if(!kpseWhichCmd.isEmpty()){
        QProcess myProc(0);
        QStringList arguments;
        arguments << "-show-path" << "ls-R";
        myProc.start(kpseWhichCmd,arguments);
        myProc.waitForFinished();
        QString result;
        if(myProc.exitCode()==0){
            result=myProc.readAllStandardOutput();
        }
        return result;
    }
    return "";
}

