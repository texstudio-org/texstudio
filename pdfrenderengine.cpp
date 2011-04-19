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

#ifndef NO_POPPLER_PREVIEW

#include "pdfrenderengine.h"

RenderCommand::RenderCommand(int p,double xr,double yr,int x,int y,int w, int h) :
    pageNr(p),xres(xr),yres(yr),x(x),y(y),w(w),h(h)
{
}

PDFRenderEngine::PDFRenderEngine(QObject *parent) :
    QThread(parent)
{
    document=0;
    mCommands.clear();
    stopped=false;
}

PDFRenderEngine::~PDFRenderEngine(){
    delete document;
}

void PDFRenderEngine::stop(){
	stopped=true;
	mCommandsAvailable.release();
}

void PDFRenderEngine::enqueue(RenderCommand cmd){
    mQueueLock.lock();
    mCommands.enqueue(cmd);
    mQueueLock.unlock();
    mCommandsAvailable.release();
}

void PDFRenderEngine::run(){
    forever {
	//wait for enqueued lines
	mCommandsAvailable.acquire();
	if(stopped) break;
	// get Linedata
	mQueueLock.lock();
	RenderCommand command=mCommands.dequeue();
	mQueueLock.unlock();
	// render Image
	if(document){
	    Poppler::Page *page=document->page(command.pageNr);
	    QImage	image=page->renderToImage(command.xres, command.yres,
					  command.x, command.y, command.w, command.h);
	    delete page;
	    emit sendImage(image,command.pageNr);
	}
    }
}

#endif
