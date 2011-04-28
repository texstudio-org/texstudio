/***************************************************************************
 *   copyright       : (C) 2011 by Jan Sundermeyer                         *
 *   http://texmakerx.sf.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pdfrendermanager.h"

PDFRenderManager::PDFRenderManager(QObject *parent) :
    QObject(parent)
{
    num_renderQueues=2;
    if(QThread::idealThreadCount()>2)
	num_renderQueues=QThread::idealThreadCount();
    for(int i=0;i<num_renderQueues;i++){
	PDFRenderEngine *renderQueue=new PDFRenderEngine(this);
	connect(renderQueue,SIGNAL(sendImage(QImage,int,int)),this,SLOT(addToCache(QImage,int,int)));
	renderQueues.append(renderQueue);
    }
    document=0;
    currentTicket=0;
    stopped=false;
}

PDFRenderManager::~PDFRenderManager(){
    stopRendering();
    document=0;
}

void PDFRenderManager::stopRendering(){
    stopped=true;
    mCommandsAvailable.release(num_renderQueues);
    for(int i=0;i<num_renderQueues;i++){
	renderQueues[i]->wait();
    }
    document=0;
}

void PDFRenderManager::setDocument(QString fileName){
    renderedPages.clear();
    for(int i=0;i<num_renderQueues;i++){
	document=Poppler::Document::load(fileName);
	document->setRenderBackend(Poppler::Document::SplashBackend);
	document->setRenderHint(Poppler::Document::Antialiasing);
	document->setRenderHint(Poppler::Document::TextAntialiasing);
	renderQueues[i]->setDocument(document);
	if(!renderQueues[i]->isRunning())
	    renderQueues[i]->start();
    }
    fillCache();
}

QPixmap PDFRenderManager::renderToImage(int pageNr,QObject *obj,const char *rec,double xres, double yres, int x, int y, int w, int h,bool cache,bool priority){
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
    currentTicket++;
    bool enqueueCmd=!checkDuplicate(currentTicket,info);
    lstOfReceivers.insert(currentTicket,info);
    // return best guess/cached at once, refine later
    Poppler::Page *page=document->page(pageNr);
    QPixmap img;
    qreal scale=10;
    if(renderedPages.contains(pageNr)){ // try cache first
	img=*renderedPages[pageNr];
    }
    if(img.isNull()) // not cached, thumbnail present ?
	img=QPixmap::fromImage(page->thumbnail());
    if(!img.isNull()){ // if a image was found, scale it apropriately
	QSize sz=page->pageSize();
	scale=sz.width()*xres/(72.0*img.width());
	int sx=qRound(img.width()*scale);
	int sy=qRound(img.height()*scale);
	if(scale>1.01 || scale<0.99)
	    img=img.scaled(QSize(sx,sy),Qt::KeepAspectRatio,Qt::FastTransformation);
	if(x>-1 && y>-1 && w>-1 && h>-1){
	    img=img.copy(x,y,w,h);
	}
    }
    if(img.isNull()){
	// generate deafult empty, to be rendered image
	if(w<0 || h<0){
	    QSize sz=page->pageSize();
	    w=sz.width();
	    h=sz.height();
	}
	img=QPixmap(w,h);
	img.fill(QApplication::palette().color(QPalette::Light).rgb());
	// paint something (rendering ... or similar)
    }
    if(enqueueCmd){
	if(scale>1.1){ // don't render again if it is smaller or about right
	    RenderCommand cmd(pageNr,xres,yres);
	    cmd.ticket=currentTicket;
	    enqueue(cmd,priority);
	}else{
	    lstOfReceivers.remove(currentTicket);
	}
    }
    delete page;
    return img;
}

void PDFRenderManager::addToCache(QImage img,int pageNr,int ticket){
    if(lstOfReceivers.contains(ticket)){
	QList<RecInfo> infos=lstOfReceivers.values(ticket);
	lstOfReceivers.remove(ticket);
	foreach(RecInfo info,infos){
	    if(info.cache){
		QPixmap *image=new QPixmap(QPixmap::fromImage(img));
		renderedPages.insert(pageNr,image);
	    }
	    if(info.obj){
		if(info.x>-1 && info.y>-1 && info.w>-1 && info.h>-1)
		    img=img.copy(info.x,info.y,info.w,info.h);
		QMetaObject::invokeMethod(info.obj,info.slot,Q_ARG(QPixmap,QPixmap::fromImage(img)),Q_ARG(int,pageNr));
	    }
	}
    }
}

void PDFRenderManager::fillCache(){
    for(int i=0;i<document->numPages();i++){
	renderToImage(i,0,"");
    }
}

bool PDFRenderManager::checkDuplicate(int &ticket,RecInfo &info){
    //check if a similar picture is not already in the renderqueue
    QMultiMap<int,RecInfo>::const_iterator i=lstOfReceivers.constBegin();
    for(i;i!=lstOfReceivers.constEnd();i++){
	if(i.value().pageNr!=info.pageNr)
	    continue;
	if(i.value().x<0 && i.value().y<0 && i.value().w<0 && i.value().h<0
	    && info.x<0 && info.y<0 && info.w<0 && info.h<0){
	    if(i.value().xres*1.01>=info.xres){
		ticket=i.key();
		return true;
	    }
	}
    }
    return false;
}

void PDFRenderManager::enqueue(RenderCommand cmd,bool priority){
    mQueueLock.lock();
    if(priority){
	mCommands.prepend(cmd);
    }else{
	mCommands.enqueue(cmd);
    }
    mQueueLock.unlock();
    mCommandsAvailable.release();
}
