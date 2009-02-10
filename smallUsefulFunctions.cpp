#include "smallUsefulFunctions.h"
#include <QFile>
#include <QFileInfo>
bool isFileRealWritable(QString filename){
    #ifdef Q_WS_WIN
        //thanks to Vistas virtual folders trying to open an unaccessable file can create it somewhere else
        return QFileInfo(filename).isWritable();
    #endif
    QFile fi(filename);
    bool result=false;
    if (fi.exists()) result=fi.open(QIODevice::ReadWrite);
    else {
        result=fi.open(QIODevice::ReadWrite);
        fi.remove();
    }
    return result;
}

bool isExistingFileRealWritable(QString filename){
    return QFileInfo(filename).exists() && isFileRealWritable(filename);
}
