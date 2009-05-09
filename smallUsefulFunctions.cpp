#include "smallUsefulFunctions.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QMessageBox>

const QString CommonEOW="~!@#$%^&*()_+{}|:\"<>?,./;[]-= \t\n\r`+�";

QString getCommonEOW(){
    return CommonEOW;
}

QStringList findResourceFiles(QString dirName, QString filter){
    QStringList searchFiles;
    #if defined( Q_WS_X11 )
    searchFiles<<PREFIX"/share/texmakerx/"+dirName; //X_11
    #endif
    searchFiles<<QCoreApplication::applicationDirPath() + "/"+dirName; //windows new
   // searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new
    searchFiles<<":/"+dirName; //resource fall back

    foreach (QString fn, searchFiles) {
        QDir fic(fn);
        if (fic.exists() && fic.isReadable() )
        {
            return fic.entryList(QStringList(filter),QDir::Files,QDir::Name);
            break;
        }
    }
    return QStringList();
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
    searchFiles<<QCoreApplication::applicationDirPath() + "/utilities/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/completion/"+fileName; //windows new
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

	int nDirs = dirs.count();

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
			for (int j=0; j < basedirs.count(); ++j)
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


QString latexToPlainWord(QString word){
    word.replace(QString("\\-"),"",Qt::CaseInsensitive); //Trennung [separation] (german-babel-package also: \")
    word.replace(QString("\\/"),"",Qt::CaseInsensitive); //ligatur preventing (german-package also: "|)
    word.replace(QString("\"~"),"-",Qt::CaseInsensitive); //- ohne Trennung (without separation)
    //german-babel-package: "- (\- but also normal break),  "= ( like - but also normal break), "" (umbruch ohne bindestrich)
    return word;
}

QString extractSectionName(QString word){
    int i=0;
    int start=word.indexOf("{",i);
    i=start;
    int stop=word.indexOf("}",i);
    i=word.indexOf("{",i+1);
    while(i>0 && stop>0 && i<stop){
        stop=word.indexOf("}",stop+1);
        i=word.indexOf("{",i+1);
    }
    if (stop<0) stop=word.length();
    word=word.mid(start+1,stop-start-1);
    return word;
}

QString textToLatex(QString text){
    QList<QPair<QString,QString> > replaceList;
    replaceList.append(QPair<QString, QString> ("\\","\\verb+\\+"));
    replaceList.append(QPair<QString, QString> ("{","\\{"));
    replaceList.append(QPair<QString, QString> ("}","\\}"));
    replaceList.append(QPair<QString, QString> ("#","\\#"));
    replaceList.append(QPair<QString, QString> ("$","\\$"));
    replaceList.append(QPair<QString, QString> ("%","\\%"));
    replaceList.append(QPair<QString, QString> ("&","\\&"));
    replaceList.append(QPair<QString, QString> ("~","\\~{}"));
    replaceList.append(QPair<QString, QString> ("_","\\_"));
    replaceList.append(QPair<QString, QString> ("^","\\^"));

    for (QList<QPair<QString,QString> >::iterator it=replaceList.begin(); it!=replaceList.end();++it)
        text.replace(it->first,it->second);

    return text;
}

bool localAwareLessThan(const QString &s1, const QString &s2)
{
	return QString::localeAwareCompare(s1,s2)<0;
}

	
int nextToken(const QString &line,int &index)
{
	bool inWord=false;
	bool inCmd=false;
	//bool reparse=false;
    bool singleQuoteChar=false;
    int start=-1;
	int i=index;
    for (i=(i>0?i:0);i<line.size();i++){
        QChar cur = line.at(i);
        if (inCmd) {
            if (CommonEOW.indexOf(cur)>=0) break; 
        } else if (inWord) {
            if (cur=='\\') {
                if (i+1<line.size() && line.at(i+1)=='-')  {
                    i++;//ignore word separation marker
                    //reparse=true;
                } else break;
            } else if (cur=='\'') { 
                if (singleQuoteChar) break;	 //no word's with two '' => output
                else singleQuoteChar=true;   //but accept one
            } else if (CommonEOW.indexOf(cur)>=0) break;
        } else if (cur=='\\') {
            start=i;
            inCmd=true;
        } else if (cur=='{' || cur=='}' || cur=='%') {
			index=i+1;
			return i;
        } else if (cur=='\\') {
            start=i;
            inCmd=true;
        } else if (CommonEOW.indexOf(cur)<0 && cur!='\'') {
            start=i;
            inWord=true;
        }
    }
    index=i;
    return start;
}


NextWordFlag nextWord(const QString &line,int &index,QString &outWord,int &wordStartIndex, bool returnCommands){
        static const QStringList optionCommands = QStringList() << "\\ref" << "\\label"  << "\\includegraphics" << "\\usepackage" << "\\documentclass";
	static const QStringList environmentCommands = QStringList() << "\\begin" << "\\end" 
													<< "\\newenvironment" << "\\renewenvironment";

	QString lastCommand="";
	while ((wordStartIndex = nextToken(line, index))!=-1){
		outWord=line.mid(wordStartIndex,index-wordStartIndex);
		if (outWord.length()==0) return NW_NOTHING; //should never happen
		switch (outWord.at(0).toAscii()) {
			case '%': return NW_COMMENT; //return comment start
			case '\\': 
				if (returnCommands) return NW_COMMAND;
                                if(!optionCommands.contains(lastCommand)) lastCommand=outWord;
				break;
			case '{': break; //ignore
			case '}': lastCommand=""; break;//command doesn't matter anymore
			default:
				if (outWord.contains("\\")) 
					outWord=latexToPlainWord(outWord); //remove special chars
				if (optionCommands.contains(lastCommand)) 
					; //ignore command options
				else if (environmentCommands.contains(lastCommand)) 
					return NW_ENVIRONMENT;
				else return NW_TEXT;
		}
	}
	return NW_NOTHING;
}

bool nextTextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex){
	NextWordFlag flag;
	//flag can be nothing, text, comment, environment
	//text/comment returns false, text returns true, environment is ignored
	while ((flag=nextWord(line,index,outWord,wordStartIndex,false))==NW_ENVIRONMENT) 
		;
	return flag==NW_TEXT; 
}
