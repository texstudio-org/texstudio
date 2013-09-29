#include "kpathseaParser.h"

KpathSeaParser::KpathSeaParser(QObject *parent,QString kpsecmd) :
    SafeThread(parent)
{
    kpseWhichCmd=kpsecmd;
}



void KpathSeaParser::run(){
    QString fullName=kpsewhich(); // find lcoations of ls-R (file database of tex)
    QStringList results;
    if(fullName.isEmpty()){
	// try specical treatment for miktex as it does not use ls-R
	QString result=mpm("--version");
	if(result.isEmpty())
	    return;
	result=mpm("--list");
	QStringList lstOfPackages=result.split("\n");
	QStringList::iterator it;
	foreach(QString pck,lstOfPackages){
	    if(pck.startsWith("i")){
		pck=pck.simplified();
		QStringList zw=pck.split(" ");
		if(zw.count()==4){
		    pck=zw.at(3);
		    result=mpm("--print-package-info "+pck);
		    qDebug()<<pck;
		    QStringList lines=result.split("\n");
		    bool pckFound=false;
		    for(int i=0;i<lines.count();i++){
			if(lines.at(i).startsWith("run-time files:")){
			    pckFound=true;
			    continue;
			}
			if(pckFound){
			    QString fn=lines.at(i).simplified();
			    fn=QFileInfo(fn).fileName();
			    if(fn.endsWith(".sty")||fn.endsWith(".sty")){
				fn.chop(4);
				it=qLowerBound(results.begin(),results.end(),fn);
				if(it==results.end() || *it!=fn)
				    results.insert(it,fn);
			    }
			    if(fn.endsWith(":"))
				break;
			}
		    }
		}
	    }
	}
    }else{
	QStringList lstOfFiles=fullName.split(":");
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
	return result.trimmed();
    }
    return "";
}

QString KpathSeaParser::mpm(QString arg){
    if(!kpseWhichCmd.isEmpty()){
	QString mpmCmd=kpseWhichCmd.replace("kpsewhich","mpm");
	QProcess myProc(0);
	QStringList arguments=arg.split(" ");
	myProc.start(mpmCmd,arguments);
	myProc.waitForFinished();
	QString result;
	if(myProc.exitCode()==0){
	    result=myProc.readAllStandardOutput();
	}
	return result.trimmed();
    }
    return "";
}
