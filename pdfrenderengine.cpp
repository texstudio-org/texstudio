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
#include "pdfrendermanager.h"

RenderCommand::RenderCommand(int p,double xr,double yr,int x,int y,int w, int h) :
    pageNr(p),xres(xr),yres(yr),x(x),y(y),w(w),h(h),ticket(-1),priority(false)
{
}

PDFRenderEngine::PDFRenderEngine(QObject *parent,PDFQueue *mQueue) :
       QThread(parent), cachedNumPages(0)
{
	document=0;
	queue=mQueue;
	queue->ref();
}

PDFRenderEngine::~PDFRenderEngine(){
	wait();
	delete document;
}

void PDFRenderEngine::setDocument(Poppler::Document *doc){
	document = doc;
	cachedNumPages = document->numPages();
}


void PDFRenderEngine::run(){
	forever {
		bool priorityThread=queue->mPriorityLock.tryLock();
		RenderCommand command(-1);
		if(priorityThread){
		    forever{
			bool leave=false;
			{ QMutexLocker(&queue->mQueueLock);
			    if(queue->stopped)
				break;
			    if(!queue->mCommands.isEmpty()){
				command=queue->mCommands.head();
				if(command.priority){
				    leave=queue->mCommandsAvailable.tryAcquire();
				    if(leave)
					queue->mCommands.dequeue();
				}
				if(leave){
				    queue->mPriorityLock.unlock();
				    break;
				}
			    }
			}
			msleep(1);
		    }
		}else{
		    //wait for enqueued lines
		    queue->mCommandsAvailable.acquire();
		    if(queue->stopped) break;
		    // get Linedata
		    queue->mQueueLock.lock();
		    command=queue->mCommands.dequeue();
		    queue->mQueueLock.unlock();
		}
		if(queue->stopped)
		    break;

		// render Image
		if(document && command.pageNr >= 0 && command.pageNr < cachedNumPages){
		    Poppler::Page *page=document->page(command.pageNr);
		    if(page){
			QImage image=page->renderToImage(command.xres, command.yres,
							  command.x, command.y, command.w, command.h);
			delete page;
			if(!queue->stopped)
			    emit sendImage(image,command.pageNr,command.ticket);
		    }
		    //qDebug() << this << " Render page " << command.pageNr << " at " << command.ticket << priorityThread << "x/y" << command.x << command.y << " res "<<command.xres << ", " << command.w << command.h;
		}
	}
	queue->deref();
	deleteLater();
}

#endif
