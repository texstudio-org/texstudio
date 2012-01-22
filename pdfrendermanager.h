#ifndef PDFRENDERMANAGER_H
#define PDFRENDERMANAGER_H

#include "mostQtHeaders.h"

#ifndef NO_POPPLER_PREVIEW

#include <QCache>
#include <QImage>

#include "pdfrenderengine.h"

class RecInfo{
public:
	QObject *obj;
	const char *slot;
	int x,y,w,h;
	int pageNr;
	qreal xres;
	bool cache;
	bool priority;
};

class CachePixmap: public QPixmap
{
public:
	CachePixmap(const QPixmap &pixmap);
	CachePixmap();
	void setRes(qreal res,int x,int y);
	qreal getRes(){
		return resolution;
	}
	QPoint getCoord(){
		return QPoint(x,y);
	}

private:
	qreal resolution;
	int x,y;
};

class PDFQueue : public QObject
{
public:
    explicit PDFQueue(QObject *parent=0);

    inline void ref() { m_ref.ref(); }
    void deref();
    int getRef(){ return m_ref; }

    QQueue<RenderCommand> mCommands;
    QSemaphore mCommandsAvailable;
    QMutex mQueueLock;
    bool stopped;

    QMutex mPriorityLock;

    int num_renderQueues;
    
    QList<PDFRenderEngine *>renderQueues;

	QByteArray documentData;
private:

#if QT_VERSION < 0x040400
    QBasicAtomic m_ref;
#else
    QAtomicInt m_ref;
#endif
};

class PDFRenderManager : public QObject
{
	Q_OBJECT
public:
	explicit PDFRenderManager(QObject *parent);
	~PDFRenderManager();
	QPixmap renderToImage(int pageNr,QObject *obj,const char *rec,double xres=72.0, double yres=72.0, int x=-1, int y=-1, int w=-1, int h=-1,bool cache=true,bool priority=false,Poppler::Page::Rotation rotate=Poppler::Page::Rotate0);
	Poppler::Document* loadDocument(const QString& fileName, int &errorType, bool foreceLoad=false);
	void setDocument(const QByteArray& data,Poppler::Document *docPointer);
	void stopRendering();
	void fillCache(int pg=-1);
	qreal getResLimit();

public slots:
	void addToCache(QImage img,int pageNr,int ticket);

private:
	friend class PDFRenderEngine;
	bool checkDuplicate(int &ticket,RecInfo &info);
	void enqueue(RenderCommand cmd,bool priority);

	Poppler::Document *document;
	int cachedNumPages;

	QCache<int,CachePixmap> renderedPages;
	QMultiMap<int,RecInfo> lstOfReceivers;
	int currentTicket;

	QMap<int,RecInfo> lstForThumbs;
	PDFQueue *queueAdministration;
};

#endif // PDFRENDERMANAGER_H

#endif
