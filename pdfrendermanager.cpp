/***************************************************************************
 *   copyright       : (C) 2011 by Jan Sundermeyer                         *
 *   http://texstudio.sf.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef NO_POPPLER_PREVIEW

#include "pdfrendermanager.h"
#include "smallUsefulFunctions.h"
#include <QtCore/qmath.h>

const int kMaxPageZoom=1000000;
const qreal kMaxDpiForFullPage= isRetinaMac() ? 1000.0 : 500.0;

PDFQueue::PDFQueue(QObject *parent): QObject(parent){
#if QT_VERSION < 0x040400
    m_ref.init(1);
#else
    m_ref=1;
#endif
}

void PDFQueue::deref() {
    if ( !m_ref.deref() )
    {
	delete this;
    }
}

CachePixmap::CachePixmap(const QPixmap &pixmap) :
		QPixmap(pixmap), resolution(0), x(0), y(0)
{
}
CachePixmap::CachePixmap() :
		QPixmap(), resolution(0), x(0), y(0)
{
}

void CachePixmap::setRes(qreal res, int x, int y){
	this->x=x;
	this->y=y;
	this->resolution=res;
}

PDFRenderManager::PDFRenderManager(QObject *parent,int limitQueues) :
       QObject(parent), cachedNumPages(0)
{
	queueAdministration=new PDFQueue();
    if(limitQueues>0){
        queueAdministration->num_renderQueues=limitQueues;
    }else{
        queueAdministration->num_renderQueues=2;
        if(QThread::idealThreadCount()>2)
            queueAdministration->num_renderQueues=QThread::idealThreadCount();
    }
	for(int i=0;i<queueAdministration->num_renderQueues;i++){
		PDFRenderEngine *renderQueue=new PDFRenderEngine(0,queueAdministration);
		connect(renderQueue,SIGNAL(sendImage(QImage,int,int)),this,SLOT(addToCache(QImage,int,int)));
		queueAdministration->renderQueues.append(renderQueue);
	}
	currentTicket=0;
	queueAdministration->stopped=false;
	renderedPages.setMaxCost(512); // will be overwritten by config
    mFillCacheMode=true;
}

PDFRenderManager::~PDFRenderManager(){
	stopRendering();
	queueAdministration->deref();
}

void PDFRenderManager::stopRendering(){
	lstOfReceivers.clear();
	queueAdministration->stopped=true;
	queueAdministration->mCommandsAvailable.release(queueAdministration->num_renderQueues);
	document.clear();
	cachedNumPages = 0;
}

void PDFRenderManager::setCacheSize(int megabyte) {
	renderedPages.setMaxCost(megabyte);
}

QSharedPointer<Poppler::Document> PDFRenderManager::loadDocument(const QString &fileName, Error &error, bool foreceLoad){
	renderedPages.clear();
	QFile f(fileName);
	if (!f.open(QFile::ReadOnly)) {
		error = FileOpenFailed;
		return QSharedPointer<Poppler::Document>();
	}
	
	queueAdministration->documentData = f.readAll();
	if (!queueAdministration->documentData.mid(qMax(0, queueAdministration->documentData.size() - 1024)).trimmed().endsWith("%%EOF") &&
	    !foreceLoad) {
		error = FileIncomplete;
		return QSharedPointer<Poppler::Document>();
	}

	Poppler::Document *docPtr;
	docPtr = Poppler::Document::loadFromData(queueAdministration->documentData);
	if (!docPtr) {
		error = PopplerError;
		return QSharedPointer<Poppler::Document>();
	}
	
	if (docPtr->isLocked()) {
		delete docPtr;
		docPtr = 0;
		error = FileLocked;
		return QSharedPointer<Poppler::Document>();
	}

	cachedNumPages = docPtr->numPages();

	docPtr->setRenderBackend(Poppler::Document::SplashBackend);
	docPtr->setRenderHint(Poppler::Document::Antialiasing);
	docPtr->setRenderHint(Poppler::Document::TextAntialiasing);


	for(int i=0;i<queueAdministration->num_renderQueues;i++){
		// poppler is not thread-safe, so each render engine needs a separate Poppler::Document
		Poppler::Document *doc=Poppler::Document::loadFromData(queueAdministration->documentData);
		QSharedPointer<Poppler::Document> spDoc(doc);
		queueAdministration->renderQueues[i]->setDocument(spDoc);
		if (!doc) {
			Q_ASSERT(false);
			error = FileIncomplete;
			return QSharedPointer<Poppler::Document>();
		}
		doc->setRenderBackend(Poppler::Document::SplashBackend);
		doc->setRenderHint(Poppler::Document::Antialiasing);
		doc->setRenderHint(Poppler::Document::TextAntialiasing);
		if(!queueAdministration->renderQueues[i]->isRunning())
			queueAdministration->renderQueues[i]->start();
	}
	mFillCacheMode=true;

	error = NoError;
	document = QSharedPointer<Poppler::Document>(docPtr);
	return document;
}

QPixmap PDFRenderManager::renderToImage(int pageNr,QObject *obj,const char *rec,double xres, double yres, int x, int y, int w, int h,bool cache,bool priority,Poppler::Page::Rotation rotate){
	if (document.isNull()) return QPixmap();
	if (pageNr < 0 || pageNr >= cachedNumPages) return QPixmap();
	RecInfo info;
	info.obj=obj;
	info.slot=rec;
	info.x=x;
	info.y=y;
	info.w=w;
	info.h=h;
	info.pageNr=pageNr;
	info.cache=cache;
	info.xres=xres;
	info.priority=priority;
	currentTicket++;
	int mCurrentTicket=currentTicket;
	bool enqueueCmd=!checkDuplicate(mCurrentTicket,info);
	if(!enqueueCmd) // already queued fillcache
	    return QPixmap();
	if(!priority && renderedPages.contains(pageNr))
	    enqueueCmd=false;
	// return best guess/cached at once, refine later
	Poppler::Page *page=document->page(pageNr);
	if(!page)
	    return QPixmap();
	CachePixmap img;
	qreal scale=10;
	bool partialImage=false;
	if(renderedPages.contains(pageNr+kMaxPageZoom) && xres>kMaxDpiForFullPage){ // try cache first
		CachePixmap *cachedPix=renderedPages[pageNr+kMaxPageZoom];
		if(cachedPix->getCoord()==QPoint(x,y) && cachedPix->getRes()<1.01*xres && cachedPix->getRes()>0.99*xres && cachedPix->width()==w && cachedPix->height()==h){
			img=*cachedPix;
			partialImage=true;
			enqueueCmd=false;
		}
	}
	if(img.isNull() && renderedPages.contains(pageNr)){ // try cache first
		img=*renderedPages[pageNr];
	}
	//if(img.isNull()) // not cached, thumbnail present ? (fix crash?)
	//	img=QPixmap::fromImage(page->thumbnail());
	if(!img.isNull() && !partialImage){ // if a image was found, scale it apropriately
		QSize sz=page->pageSize();
		scale=sz.width()*xres/(72.0*img.width());
		if(scale<0)
			scale=1.0;
		int sx=qRound(img.width()*scale);
		int sy=qRound(img.height()*scale);
		if(scale>1.01 || scale<0.99){
			img=img.scaled(QSize(sx,sy),Qt::KeepAspectRatio,Qt::FastTransformation);
			if(cache){
			    if(xres>kMaxDpiForFullPage)
				pageNr=pageNr+kMaxPageZoom;
			    CachePixmap *image=new CachePixmap(img);
			    image->setRes(xres,x,y);
			    int cost=qRound(xres*xres/10000.0);
			    if(cost<1)
				cost=1;
			    renderedPages.insert(pageNr,image,cost);
			}
		}
		if(!cache && x>-1 && y>-1 && w>-1 && h>-1){
		    img=img.copy(x,y,w,h);
		}
	}
	if(xres<0){
        if(mFillCacheMode){
        scale=1.0; //don't render thumbnails
        enqueueCmd=false;
        if(img.isNull())
            lstForThumbs.insert(pageNr,info);
        }else{
            info.xres=20;
            xres=20.0;
            yres=20.0;
        }
    }
	if(img.isNull()){
		// generate deafult empty, to be rendered image
		if(w<0 || h<0){
			QSize sz;
			sz=page->pageSize();
			w=sz.width();
			h=sz.height();
		}
		img=QPixmap(w,h);
		img.fill(QApplication::palette().color(QPalette::Light).rgb());
		// paint something (rendering ... or similar)
	}
	if(enqueueCmd){
		if(scale>1.01 || scale<0.99){ // always rerender, only not if it is already equivalent
			QMutableMapIterator<int,RecInfo> i(lstOfReceivers);
			while (i.hasNext()){
				i.next();
				if(mCurrentTicket!=i.key()){
					RecInfo elem=i.value();
					if(elem.pageNr==info.pageNr
					   && elem.obj==info.obj
					   && elem.slot==info.slot
					   ){
						qreal rel=elem.xres/info.xres;
						if(rel>1.01 || rel<0.99 || elem.x!=info.x || elem.y!=info.y || elem.w!=info.w || elem.h!=info.h){
							i.remove();
						}else{
							info.pageNr=-1;
							break;
						}
					}
				}
			}
			if(info.pageNr>=0){
				RenderCommand cmd(pageNr,xres,yres);
				if(xres>kMaxDpiForFullPage){
					cmd.x=x;
					cmd.y=y;
					cmd.w=w;
					cmd.h=h;
				}
				cmd.rotate=rotate;
				cmd.ticket=mCurrentTicket;
				cmd.priority=priority;
				lstOfReceivers.insert(mCurrentTicket,info);
				enqueue(cmd,priority);
			}
		}
	}//else{
	//	lstOfReceivers.insert(mCurrentTicket,info);
	//}
	delete page;
	return img;
}

void PDFRenderManager::addToCache(QImage img,int pageNr,int ticket){
	//qDebug() << ticket << " rec at "<<QThread::currentThreadId();
	if(lstOfReceivers.contains(ticket)){
		QList<RecInfo> infos=lstOfReceivers.values(ticket);
		lstOfReceivers.remove(ticket);
		foreach(RecInfo info,infos){
			if(info.cache){
				if(info.xres>kMaxDpiForFullPage)
					pageNr=pageNr+kMaxPageZoom;
				CachePixmap *image=new CachePixmap(QPixmap::fromImage(img));
				image->setRes(info.xres,info.x,info.y);
				int sizeInMB=qCeil(image->width()*image->height()*image->depth()/8388608.0);
				renderedPages.insert(pageNr,image,sizeInMB);
			}
			if(info.obj){
				if(info.x>-1 && info.y>-1 && info.w>-1 && info.h>-1 && !(info.xres>kMaxDpiForFullPage))
					img=img.copy(info.x,info.y,info.w,info.h);

#if (QT_VERSION < 0x050000)
				// workaround for TXS bug 3557369: http://sourceforge.net/tracker/?func=detail&aid=3557369&group_id=250595&atid=1126426
				// based on QTBUG-26451: https://bugreports.qt-project.org/browse/QTBUG-26451
				// preventing QPixmap::fromImage(img) to crash in low memory situations
				QImage *testImage = new QImage( img.size(), QImage::Format_RGB32 );
				if ( testImage->isNull() ) {
					qDebug() << "PDF render manager: Not enough memory to allocate image. Reducing cache filling. Current cost:" << renderedPages.totalCost() << "of" << renderedPages.maxCost();
					reduceCacheFilling(0.5);
				}
				delete testImage;
#endif
				QMetaObject::invokeMethod(info.obj,info.slot,Q_ARG(QPixmap,QPixmap::fromImage(img)),Q_ARG(int,pageNr));
			}
		}
		if(lstForThumbs.contains(pageNr)){
			RecInfo info=lstForThumbs.take(pageNr);
			QMetaObject::invokeMethod(info.obj,info.slot,Q_ARG(QPixmap,QPixmap::fromImage(img)),Q_ARG(int,pageNr));
		}
	}
}

qreal PDFRenderManager::getResLimit(){
	return kMaxDpiForFullPage;
}

void PDFRenderManager::fillCache(int pg){
	if (document.isNull()) return;
	QSet<int> renderedPage;
	foreach(RecInfo elem,lstOfReceivers){
		if(elem.cache)
			renderedPage.insert(elem.pageNr);
	}
	foreach(int elem,renderedPages.keys()){
		renderedPage.insert(elem);
	}
	int i=pg-1;
	int j=pg;
	if(j<0)
		j=-1;
	const int MAX_CACHE_OFFSET = 20; // disables filling of overview dock ...
	int max=qMin(cachedNumPages, pg+MAX_CACHE_OFFSET);
	int min=qMax(0, pg-MAX_CACHE_OFFSET);
	while(i>=min || j<max){
		j++;
		if(i >= min && i < max && !renderedPage.contains(i)) // don't rerender page
			renderToImage(i,0,"");
		if(j >= min && j < max &&!renderedPage.contains(j)) // don't rerender page
			renderToImage(j,0,"");
		i--;
	}
    mFillCacheMode=false;
}

bool PDFRenderManager::checkDuplicate(int &,RecInfo &info){
	//check if a similar picture is not already in the renderqueue
	QMultiMap<int,RecInfo>::const_iterator i=lstOfReceivers.constBegin();
	for(;i!=lstOfReceivers.constEnd();++i){
		if(i.value().pageNr!=info.pageNr)
			continue;
		if(i.value().x<0 && i.value().y<0 && i.value().w<0 && i.value().h<0
		   && info.x<0 && info.y<0 && info.w<0 && info.h<0){
			if(info.priority){
				//qDebug()<<"duplicate";
				return true;
			}
		}
	}
	return false;
}

void PDFRenderManager::enqueue(RenderCommand cmd,bool priority){
	queueAdministration->mQueueLock.lock();
	if(priority){
		queueAdministration->mCommands.prepend(cmd);
	}else{
		queueAdministration->mCommands.enqueue(cmd);
	}
	queueAdministration->mQueueLock.unlock();
	queueAdministration->mCommandsAvailable.release();
}

void PDFRenderManager::reduceCacheFilling(double fraction) {
	int targetCost = renderedPages.totalCost() * fraction;

	foreach (int key, renderedPages.keys()) {
		if (renderedPages.totalCost() < targetCost)
			break;
		renderedPages.remove(key);
	}
}

#endif
