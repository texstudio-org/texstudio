#include "smallUsefulFunctions.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

QString getCommonEOW(){
    return "~!@#$%^&*()_+{}|:\"<>?,./;[]-= \n\r`+´";
} 

QString findResourceFile(QString fileName){
    QStringList searchFiles;
    #if defined( Q_WS_X11 )
    searchFiles<<PREFIX"/share/texmakerx/"+fileName; //X_11
    #endif
    searchFiles<<QCoreApplication::applicationDirPath() + "/../Resources/"+fileName; //macx
    searchFiles<<QCoreApplication::applicationDirPath() + "/"+fileName; //windows old 
    searchFiles<<QCoreApplication::applicationDirPath() + "/dictionaries/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/translation/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/help/"+fileName; //windows new
   // searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new
    searchFiles<<":/"+fileName; //resource fall back
    
    foreach (QString fn, searchFiles) {
        QFileInfo fic(fn);
        if (fic.exists() && fic.isReadable() ) 
        {
            return fn;
            break;
        }
    }
    return "";
}

bool isFileRealWritable(QString filename){
    #ifdef Q_WS_WIN
        //thanks to Vistas virtual folders trying to open an unaccessable file can create it somewhere else
        return QFileInfo(filename).isWritable();
    #endif
    QFile fi(filename);
    bool result=false;
    if (fi.exists()) result=fi.open(QIODevice::ReadWrite);
    else {
        result=fi.open(QIODevice::WriteOnly);
        fi.remove();
    }
    return result;
}

bool isExistingFileRealWritable(QString filename){
    return QFileInfo(filename).exists() && isFileRealWritable(filename);
}

QString getRelativePath(const QString basepath, const QString & file)
{

	QFileInfo fi(file);
	QString filename = fi.fileName();
	QString path = fi.path();
	QStringList basedirs = basepath.split("/");
	QStringList dirs = path.split("/");
	//QStringList basedirs = QStringList::split("/", basepath, false);
	//QStringList dirs = QStringList::split("/", path, false);

	uint nDirs = dirs.count();

	while ( dirs.count() > 0 && basedirs.count() > 0 &&  dirs[0] == basedirs[0] )
	{
		dirs.pop_front();
		basedirs.pop_front();
	}

	if (nDirs != dirs.count() )
	{
		path = dirs.join("/");

		if (basedirs.count() > 0)
		{
			for (uint j=0; j < basedirs.count(); ++j)
			{
				path = "../" + path;
			}
		}

		if ( path.length()>0 && path.right(1) != "/" ) path = path + "/";
	}
	else
	{
		path = fi.path();
	}

    if (!path.endsWith("/") && !path.endsWith("\\")) path+="/"; //necessary if basepath isn't given

	return path;
}



bool nextWord(QString line,int &index,QString &outWord,int &wordStartIndex){
    return nextWord(line,index,outWord,wordStartIndex,NW_TEXT)!=NW_NOTHING;
}

int nextWord(QString line,int &index,QString &outWord,int &wordStartIndex, int flags){
    //todo: latex akzents
    int result=NW_NOTHING;
    bool inWord=false;
    bool inCmd=false;
    bool reparse=false;
    bool singleQuoteChar=false;
    QString eow="~!@#$%^&*()_+{}|:\"<>?,./;[]-= \n\r\t`+´"; //cann't need a ' 
    int start=0;
    int i=index;
    for (i=(i>0?i:0);i<line.size();i++){
        QChar cur = line.at(i);
        if (inCmd) {
            if (cur=='%') {
                if (i-start>1) {
                    if (NW_COMMAND & flags) break; //output command
                    if (!(NW_COMMENT & flags)) return NW_NOTHING;
                    inCmd=false;
                    result|=NW_COMMENT;  //comment, no more words
                }
            } else if (eow.indexOf(cur)>=0) {
                if (NW_COMMAND & flags) break; //output command
                else inCmd=false;
            }
        } else if (inWord) {
            if (cur=='\\') {
                if (i+1<line.size() && line.at(i+1)=='-')  {
                    i++;//ignore word separation marker
                    reparse=true;
                } else {
                    inWord=false;
                    inCmd=true;
                }
            } else if (cur=='\'') { //
                if (singleQuoteChar) inWord=false; //no word's with two ''
                else singleQuoteChar=true;         //but accept one                
            } else if (cur=='%'){
                if (NW_TEXT & flags) break; //output command
                if (!(NW_COMMENT & flags)) return NW_NOTHING;
                inWord=false;
                result|=NW_COMMENT;  //comment, no more words
            } else if (eow.indexOf(cur)>=0) inWord=false;
            
            if (!inWord/* && i-start>2*/ && (NW_TEXT & flags)) {
                inWord=true;
                break; //output
            }
            //if (inCmd) start=i; //only necessary if flags&text==0, but then it won't be called
        } else if (cur=='\\') {
            start=i;
            inCmd=true;
        } else if (eow.indexOf(cur)<0 && cur!='\'') {
            start=i;    
            inWord=true;
        } else if (cur=='%') 
            if (NW_COMMENT & flags) result|=NW_COMMENT;  
            else return NW_NOTHING; 
    }
    if (inWord && (NW_TEXT & flags)) {
        wordStartIndex=start;
        index=i;
        outWord=line.mid(start,i-start);
        if (outWord.at(outWord.length()-1)==QChar('\'')) {
            outWord=outWord.left(outWord.length()-1);
            index--;
        }
        if (reparse) outWord=latexToPlainWord(outWord);
        if (outWord.isEmpty()) return NW_NOTHING;
        if (outWord.at(outWord.length()-1)==QChar('\'')) outWord=outWord.left(outWord.length()-1);
        return NW_TEXT|result;
    }
    if (inCmd && (NW_COMMAND & flags)) {
        wordStartIndex=start;
        index=i;
        outWord=line.mid(start,i-start);
        return NW_COMMAND|result;
    }
    return NW_NOTHING;
}

QString latexToPlainWord(QString word){
    word.replace(QString("\\-"),"",Qt::CaseInsensitive); //Trennung [separation] (german-babel-package also: \")
    word.replace(QString("\\/"),"",Qt::CaseInsensitive); //ligatur preventing (german-package also: "|)
    word.replace(QString("\"~"),"-",Qt::CaseInsensitive); //- ohne Trennung (without separation)
    //german-babel-package: "- (\- but also normal break),  "= ( like - but also normal break), "" (umbruch ohne bindestrich)
    return word;
}
