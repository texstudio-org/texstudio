#include "bibtexreader.h"

bibtexReader::bibtexReader(QObject *parent) :
    QThread(parent)
{
}

void bibtexReader::searchSection(QString file, QString bibId){
    QFile f(file);
    if (!f.open(QFile::ReadOnly)) return; //ups...
    QTextStream stream(&f);
    QString line;
    QString result;
    int found=-1;
    do {
        line = stream.readLine();
        if(line.contains(bibId)){
            found=6;
        }
        if(found>=0){
            if(!result.isEmpty())
                result+="\n";
            result+=line;
            found--;
        }
        if(found==0)
            break;
    } while (!line.isNull());
    if(!result.isEmpty())
        emit sectionFound(bibId,result);
}
