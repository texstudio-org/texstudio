#include "smallUsefulFunctions.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
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
    searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new
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
