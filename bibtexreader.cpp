#include "bibtexreader.h"

bibtexReader::bibtexReader(QObject *parent) :
    SafeThread(parent)
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
        if(line.startsWith('%'))
            continue;
        if(found==-1 && line.contains(bibId)){
            int p=line.indexOf('{');
            if(p<0)
                continue;
            QString id=line.mid(p+1).trimmed();
            if(id.endsWith(','))
                id.remove(id.length()-1,1);
            if(id!=bibId)
                continue;
            found=10;
            result=line;
            continue;
        }
        if(found==0 || (found>0 && (line.startsWith('@')||line.isEmpty())))
            break;
        if(found>=0){
            result+="\n"+line;
            found--;
        }
    } while (!line.isNull());
    if(!result.isEmpty())
        emit sectionFound(result);
}
