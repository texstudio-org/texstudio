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

#include "pdfrenderengine.h"
#include "pdfrendermanager.h"

RenderCommand::RenderCommand(int p, double xr, double yr, int x, int y, int w, int h) :
	pageNr(p), xres(xr), yres(yr), x(x), y(y), w(w), h(h), rotate(Poppler::Page::Rotate0), ticket(-1), priority(false)
{
}

PDFRenderEngine::PDFRenderEngine(QObject *parent, PDFQueue *mQueue) :
	SafeThread(parent), cachedNumPages(0)
{
	queue = mQueue;
	queue->ref();
}

PDFRenderEngine::~PDFRenderEngine()
{
	wait();
	queue->deref();
}

void PDFRenderEngine::setDocument(const QSharedPointer<Poppler::Document> &doc)
{
	document = doc;
	cachedNumPages = (document.isNull()) ? 0 : document->numPages();
}

void PDFRenderEngine::run()
{
	forever {
		bool priorityThread = queue->mPriorityLock.tryLock();
		RenderCommand command(-1);
		if (priorityThread) {
			forever {
				bool leave = false;
				queue->mCommandsAvailable.acquire();
                if (queue->stopped){
                    queue->mPriorityLock.unlock();
                    break;
                }
				// get Linedata
				queue->mQueueLock.lock();
				command = queue->mCommands.dequeue();
				if (command.priority) {
					leave = true;
				} else {
					queue->mCommands.prepend(command);
					queue->mCommandsAvailable.release();
				}
				queue->mQueueLock.unlock();
				if (leave) {
					queue->mPriorityLock.unlock();
					break;
				}
				msleep(1);
			}
		} else {
			//wait for enqueued lines
			queue->mCommandsAvailable.acquire();
			if (queue->stopped) break;
			// get Linedata
			queue->mQueueLock.lock();
			command = queue->mCommands.dequeue();
			queue->mQueueLock.unlock();
		}
		if (queue->stopped)
			break;

		// render Image
		if (!document.isNull() && command.pageNr >= 0 && command.pageNr < cachedNumPages) {
            std::unique_ptr<Poppler::Page> page(document->page(command.pageNr));
			if (page) {
				QImage image = page->renderToImage(command.xres, command.yres,
				                                   command.x, command.y, command.w, command.h, command.rotate);
				QSizeF pageSize = page->pageSizeF();

				QPainter p(&image);
                p.scale(command.xres * pageSize.width() / 72.0, command.yres * pageSize.height() / 72.0);
                QPen pen;
                pen.setWidthF(0.01);
                pen.setColor(Qt::blue);
                p.setPen(pen);
                if (command.x != -1 && command.y != -1) p.translate(command.x, command.y);
                if (command.rotate != Poppler::Page::Rotate0) {
                    if (command.rotate == Poppler::Page::Rotate90) p.rotate(90);
                    else if (command.rotate == Poppler::Page::Rotate180) p.rotate(180);
                    else if (command.rotate == Poppler::Page::Rotate270) p.rotate(270);
                }
                for (auto &annon: page->annotations())
                    if (annon->subType() == Poppler::Annotation::AMovie){
                        p.drawRect(annon->boundary() );
                    }

                //delete page;
				if (!queue->stopped) //qDebug() << command.ticket << " send from "<<QThread::currentThreadId(),
					emit sendImage(image, command.pageNr, command.ticket);
			}
			//qDebug() << this << " Render page " << command.pageNr << " at " << command.ticket << priorityThread << "x/y" << command.x << command.y << " res "<<command.xres << ", " << command.w << command.h;
		}
	}
	//queue->deref();
	deleteLater();
}

#endif
