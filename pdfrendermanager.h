#ifndef PDFRENDERMANAGER_H
#define PDFRENDERMANAGER_H

#include "mostQtHeaders.h"

 #include <QCache>

#include "pdfrenderengine.h"

class RecInfo{
public:
    explicit RecInfo(): obj(0),slot(""),x(-1),y(-1),w(-1),h(-1),cache(true){}
    QObject *obj;
    const char *slot;
    int x,y,w,h;
    bool cache;
};

class PDFRenderManager : public QObject
{
    Q_OBJECT
public:
    explicit PDFRenderManager(QObject *parent);
    ~PDFRenderManager();
    QImage renderToImage(int pageNr,QObject *obj,const char *rec,double xres=72.0, double yres=72.0, int x=-1, int y=-1, int w=-1, int h=-1,bool cache=true);
    void setDocument(QString fileName);

public slots:
    void addToCache(QImage img,int pageNr,int ticket);

private:


    Poppler::Document *document;

    PDFRenderEngine *renderQueue;
    QCache<int,QImage> renderedPages;
    QMap<int,RecInfo> lstOfReceivers;
    int currentTicket;
};

#endif // PDFRENDERMANAGER_H
