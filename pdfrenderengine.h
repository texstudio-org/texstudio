#ifndef PDFRENDERENGINE_H
#define PDFRENDERENGINE_H

#ifndef NO_POPPLER_PREVIEW

#include "poppler-qt4.h"

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class RenderCommand {
public:
    explicit RenderCommand(int p,double xr=72.0,double yr=72.0,int x=-1,int y=-1,int w=-1,int h=-1);
    int pageNr;
    double xres;
    double yres;
    int x;
    int y;
    int w;
    int h;
};

class PDFRenderEngine : public QThread
{
    Q_OBJECT
public:
    explicit PDFRenderEngine(QObject *parent = 0);
    ~PDFRenderEngine();

    void enqueue(RenderCommand cmd);
    void stop();
    void setDocument(Poppler::Document *doc){
	document=doc;
    }

signals:
    void sendImage(QImage image,int page);

public slots:

protected:
    void run();

private:
    Poppler::Document	*document;
    QQueue<RenderCommand> mCommands;
    QSemaphore mCommandsAvailable;
    QMutex mQueueLock;
    bool stopped;

};

#endif // PDFRENDERENGINE_H

#endif
