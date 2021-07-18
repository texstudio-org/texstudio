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
#include "configmanagerinterface.h"
#include <QtCore/qmath.h>

const int kMaxPageZoom = 1000000;

// maximal resolution for rendering
// example: 192dpi with 4x magnification requires 768dpi rendering resolution
// rendering at high resolutions may be slow. On the other hand, we expect
// that users with high resolution screens have reasonable cpu power.
const qreal kMaxDpiForFullPage = 1000.0;


SetImageForwarder::SetImageForwarder(QObject *parent, QObject *obj, const char *rec, QPixmap img, int pageNr):
    QObject(parent), obj(obj), rec(rec), img(img), pageNr(pageNr)
{
}

void SetImageForwarder::setImage() {
    QMetaObject::invokeMethod(obj, rec, Q_ARG(QPixmap, img), Q_ARG(int, pageNr));
    deleteLater();
}

void SetImageForwarder::forward(int delay) {
    QTimer::singleShot(delay, this, SLOT(setImage()));
}

PDFQueue::PDFQueue(QObject *parent): QObject(parent), stopped(true), num_renderQueues(1)
{
	m_ref = 1;
}

void PDFQueue::deref()
{
	if ( !m_ref.deref() ) {
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

void CachePixmap::setRes(qreal res, int x, int y)
{
	this->x = x;
	this->y = y;
	this->resolution = res;
}
/*!
 * \brief PDFRenderManager::PDFRenderManager
 * \param parent
 * \param limitQueues limit the number of parallel threads to render pdf.
 * Negative number means limit number to abs() if that number is smaler than cores, positive number sets it to the given value.
 *
 */
PDFRenderManager::PDFRenderManager(QObject *parent, int limitQueues) :
	QObject(parent), cachedNumPages(0), loadStrategy(HybridLoad)
{
	queueAdministration = new PDFQueue();
	if (limitQueues > 0) {
		queueAdministration->num_renderQueues = limitQueues;
	} else {
		queueAdministration->num_renderQueues = 2;
		if (QThread::idealThreadCount() > 2)
			queueAdministration->num_renderQueues = QThread::idealThreadCount();
        if(limitQueues < 0 && queueAdministration->num_renderQueues>-limitQueues){
            queueAdministration->num_renderQueues = -limitQueues;
        }
	}
	for (int i = 0; i < queueAdministration->num_renderQueues; i++) {
        auto *renderQueue = new PDFRenderEngine(nullptr, queueAdministration);
        connect(renderQueue, SIGNAL(sendImage(QImage,int,int)), this, SLOT(addToCache(QImage,int,int)));
		queueAdministration->renderQueues.append(renderQueue);
	}
	currentTicket = 0;
	queueAdministration->stopped = false;
	renderedPages.setMaxCost(512); // will be overwritten by config
	mFillCacheMode = true;
}

PDFRenderManager::~PDFRenderManager()
{
	stopRendering();
	queueAdministration->deref();
}

void PDFRenderManager::stopRendering()
{
	lstOfReceivers.clear();
	for (int i = 0; i < queueAdministration->num_renderQueues; i++) {
		if (queueAdministration->renderQueues[i] && !queueAdministration->renderQueues[i]->isRunning())
			delete queueAdministration->renderQueues[i];
		queueAdministration->renderQueues[i] = 0;
	}
	queueAdministration->stopped = true;
	queueAdministration->mCommandsAvailable.release(queueAdministration->num_renderQueues);
    document.reset();
	cachedNumPages = 0;
}

void PDFRenderManager::setCacheSize(int megabyte)
{
	renderedPages.setMaxCost(megabyte);
}

void PDFRenderManager::setLoadStrategy(int strategy)
{
	loadStrategy = strategy;
}

class HiddenByteArray: public QByteArray
{
public:
	HiddenByteArray(): QByteArray() {}
    explicit HiddenByteArray(const QString &s): QByteArray(s.toLatin1()) {}
	~HiddenByteArray()
	{
		for (int i = 0; i < length(); i++)
			(*this)[i] = '\0';
	}
};

QSharedPointer<Poppler::Document> PDFRenderManager::loadDocument(const QString &fileName, Error &error, const QString &userPasswordStr, bool foreceLoad)
{
	renderedPages.clear();
	QFile f(fileName);
	if (!f.open(QFile::ReadOnly)) {
		error = FileOpenFailed;
        return QSharedPointer<Poppler::Document>();
	}

    std::unique_ptr<Poppler::Document> docPtr;

	HiddenByteArray ownerPassword; //for permission settings (not needed?)
	HiddenByteArray userPassword(userPasswordStr);

	try {

		if (loadStrategy == DirectLoad) {
#if POPPLER_VERSION_MAJOR>=21 && POPPLER_VERSION_MINOR>=6 && QT_VERSION_MAJOR>5
            docPtr = Poppler::Document::load(fileName, ownerPassword, userPassword);
#else
            docPtr = std::unique_ptr<Poppler::Document>(Poppler::Document::load(fileName, ownerPassword, userPassword));
#endif
		} else {
			// load data into buffer and check for completeness
			queueAdministration->documentData = f.readAll();
			if (!queueAdministration->documentData.mid(qMax(0, queueAdministration->documentData.size() - 1024)).trimmed().endsWith("%%EOF") &&
			        !foreceLoad) {
				error = FileIncomplete;
                return QSharedPointer<Poppler::Document>();
			}
			// create document
			if (loadStrategy == BufferedLoad || (loadStrategy == HybridLoad && queueAdministration->documentData.size() < 50000000)) {
				if (queueAdministration->documentData.size() < 1024)
					queueAdministration->documentData.append(QByteArray(1024 - queueAdministration->documentData.size(), (char) 0));
#if POPPLER_VERSION_MAJOR>=21 && POPPLER_VERSION_MINOR>=6 && QT_VERSION_MAJOR>5
				docPtr = Poppler::Document::loadFromData(queueAdministration->documentData, ownerPassword, userPassword);
#else
                docPtr = std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(queueAdministration->documentData, ownerPassword, userPassword));
#endif
			} else {
#if POPPLER_VERSION_MAJOR>=21 && POPPLER_VERSION_MINOR>=6 && QT_VERSION_MAJOR>5
				docPtr = Poppler::Document::load(fileName, ownerPassword, userPassword);
#else
                docPtr = std::unique_ptr<Poppler::Document>(Poppler::Document::load(fileName, ownerPassword, userPassword));
#endif
			}
		}
	} catch (std::bad_alloc &) {
		error = PopplerErrorBadAlloc;
        return QSharedPointer<Poppler::Document>();
	} catch (...) {
		error = PopplerErrorException;
        return QSharedPointer<Poppler::Document>();
	}

	if (!docPtr) {
		error = PopplerError;
        return QSharedPointer<Poppler::Document>();
	}

	if (docPtr->isLocked()) {
        //delete docPtr;
        docPtr = nullptr;
		error = FileLocked;
        return QSharedPointer<Poppler::Document>();
	}

	cachedNumPages = docPtr->numPages();

	Poppler::Document::RenderBackend backend = Poppler::Document::SplashBackend;
	if (ConfigManagerInterface::getInstance()->getOption("Preview/RenderBackend").toInt() == 1) {
#if QT_VERSION_MAJOR>5
        backend = Poppler::Document::QPainterBackend;
#else
		backend = Poppler::Document::ArthurBackend;
#endif
	}
	
	docPtr->setRenderBackend(backend);
	docPtr->setRenderHint(Poppler::Document::Antialiasing);
	docPtr->setRenderHint(Poppler::Document::TextAntialiasing);

	QColor paperColor = QColor(ConfigManagerInterface::getInstance()->getOption("Preview/PaperColor").toString());
	if (paperColor.isValid()) {
		docPtr->setPaperColor(paperColor);
	}

    document = QSharedPointer<Poppler::Document>(docPtr.release());

	for (int i = 0; i < queueAdministration->num_renderQueues; i++) {

		queueAdministration->renderQueues[i]->setDocument(document);


		if (!queueAdministration->renderQueues[i]->isRunning())
			queueAdministration->renderQueues[i]->start();
	}
	mFillCacheMode = true;

	queueAdministration->documentData.clear(); // remove file, as poppler made a copy of its own

	error = NoError;

    return document;
}

QPixmap PDFRenderManager::renderToImage(int pageNr, QObject *obj, const char *rec, double xres, double yres, int x, int y, int w, int h, bool cache, bool priority, int delayTimeout, Poppler::Page::Rotation rotate)
{
    if (document.isNull()) return QPixmap();
	if (pageNr < 0 || pageNr >= cachedNumPages) return QPixmap();
	RecInfo info;
	info.obj = obj;
	info.slot = rec;
	info.x = x;
	info.y = y;
	info.w = w;
	info.h = h;
	info.pageNr = pageNr;
	info.cache = cache;
	info.xres = xres;
	info.priority = priority;
	currentTicket++;
	int mCurrentTicket = currentTicket;
	bool enqueueCmd = !checkDuplicate(mCurrentTicket, info);
	if (!enqueueCmd) // already queued fillcache
		return QPixmap();
	if (!priority && renderedPages.contains(pageNr))
		enqueueCmd = false;
	// return best guess/cached at once, refine later
    std::unique_ptr<Poppler::Page> page(document->page(pageNr));
	if (!page)
		return QPixmap();
	CachePixmap img;
	qreal scale = 10;
	bool partialImage = false;
	if (renderedPages.contains(pageNr + kMaxPageZoom) && xres > kMaxDpiForFullPage) { // try cache first
		CachePixmap *cachedPix = renderedPages[pageNr + kMaxPageZoom];
		if (cachedPix->getCoord() == QPoint(x, y) && cachedPix->getRes() < 1.01 * xres && cachedPix->getRes() > 0.99 * xres && cachedPix->width() == w && cachedPix->height() == h) {
			img = *cachedPix;
			partialImage = true;
			enqueueCmd = false;
		}
	}
	if (img.isNull() && renderedPages.contains(pageNr)) { // try cache first
		img = *renderedPages[pageNr];
	}

    // delayTimeout = -1 means it's NOT been called by delayedUpdate
    // delayTimeout >= 0 means it's been called called by delayedUpdate and delayedUpdate wants to force an update after delayTimeout
    // Note that when delayTimeout >= 0 is used, and there's no cache, the slot can be called with null img.
    if (delayTimeout >= 0) {
        if (!img.isNull())
            QMetaObject::invokeMethod(info.obj, info.slot, Q_ARG(QPixmap, img), Q_ARG(int, pageNr));
        else
            (new SetImageForwarder(this, obj, rec, img, pageNr))->forward(delayTimeout);
    }

	//if(img.isNull()) // not cached, thumbnail present ? (fix crash?)
	//	img=QPixmap::fromImage(page->thumbnail());
	if (!img.isNull() && !partialImage) { // if a image was found, scale it apropriately
		QSize sz = page->pageSize();
		scale = sz.width() * xres / (72.0 * img.width());
		if (scale < 0)
			scale = 1.0;
        if(w==img.width())
            scale = 1.0;
		int sx = qRound(img.width() * scale);
		int sy = qRound(img.height() * scale);
		if (scale > 1.01 || scale < 0.99) {
			img = img.scaled(QSize(sx, sy), Qt::KeepAspectRatio, Qt::FastTransformation);
			if (cache) {
				if (xres > kMaxDpiForFullPage)
					pageNr = pageNr + kMaxPageZoom;
				CachePixmap *image = new CachePixmap(img);
				image->setRes(xres, x, y);
				int sizeInMB = qCeil(image->width() * image->height() * image->depth() / 8388608.0);  // 8(bits depth -> bytes) * 1024**2 (bytes -> MB)
				renderedPages.insert(pageNr, image, sizeInMB);
			}
		}
		if (!cache && x > -1 && y > -1 && w > -1 && h > -1) {
			img = img.copy(x, y, w, h);
		}
	}
	if (xres < 0) {
		if (mFillCacheMode) {
			scale = 1.0; //don't render thumbnails
			enqueueCmd = false;
			if (img.isNull())
				lstForThumbs.insert(pageNr, info);
		} else {
			info.xres = 20;
			xres = 20.0;
			yres = 20.0;
		}
	}
	if (img.isNull()) {
		// generate deafult empty, to be rendered image
		if (w < 0 || h < 0) {
			QSize sz;
			sz = page->pageSize();
			w = sz.width();
			h = sz.height();
		}
		img = QPixmap(w, h);
		img.fill(QApplication::palette().color(QPalette::Light).rgb());
		// paint something (rendering ... or similar)
	}
	if (enqueueCmd) {
		if (scale > 1.01 || scale < 0.99) { // always rerender, only not if it is already equivalent
#if QT_VERSION>QT_VERSION_CHECK(6,0,0)
            QMutableMultiMapIterator<int, RecInfo> i(lstOfReceivers);
#else
            QMutableMapIterator<int, RecInfo> i(lstOfReceivers);
#endif
			while (i.hasNext()) {
				i.next();
				if (mCurrentTicket != i.key()) {
					RecInfo elem = i.value();
					if (elem.pageNr == info.pageNr
					        && elem.obj == info.obj
					        && elem.slot == info.slot
					   ) {
						qreal rel = elem.xres / info.xres;
						if (rel > 1.01 || rel < 0.99 || elem.x != info.x || elem.y != info.y || elem.w != info.w || elem.h != info.h) {
							i.remove();
						} else {
							info.pageNr = -1;
							break;
						}
					}
				}
			}
			if (info.pageNr >= 0) {
				RenderCommand cmd(pageNr, xres, yres);
				if (xres > kMaxDpiForFullPage) {
					cmd.x = x;
					cmd.y = y;
					cmd.w = w;
					cmd.h = h;
				}
				cmd.rotate = rotate;
				cmd.ticket = mCurrentTicket;
				cmd.priority = priority;
				lstOfReceivers.insert(mCurrentTicket, info);
				enqueue(cmd, priority);
			}
		}
	}//else{
	//	lstOfReceivers.insert(mCurrentTicket,info);
	//}
    return std::move(img);
}

void PDFRenderManager::addToCache(QImage img, int pageNr, int ticket)
{
	//qDebug() << ticket << " rec at "<<QThread::currentThreadId();
	if (lstOfReceivers.contains(ticket)) {
		QList<RecInfo> infos = lstOfReceivers.values(ticket);
		lstOfReceivers.remove(ticket);
		foreach (RecInfo info, infos) {
			if (info.cache) {
				if (info.xres > kMaxDpiForFullPage)
					pageNr = pageNr + kMaxPageZoom;
				CachePixmap *image = new CachePixmap(QPixmap::fromImage(img));
				image->setRes(info.xres, info.x, info.y);
				int sizeInMB = qCeil(image->width() * image->height() * image->depth() / 8388608.0);  // 8(bits depth -> bytes) * 1024**2 (bytes -> MB)
				renderedPages.insert(pageNr, image, sizeInMB);
			}
			if (info.obj) {
				if (info.x > -1 && info.y > -1 && info.w > -1 && info.h > -1 && !(info.xres > kMaxDpiForFullPage))
					img = img.copy(info.x, info.y, info.w, info.h);

				QMetaObject::invokeMethod(info.obj, info.slot, Q_ARG(QPixmap, QPixmap::fromImage(img)), Q_ARG(int, pageNr));
			}
		}
		if (lstForThumbs.contains(pageNr)) {
			RecInfo info = lstForThumbs.take(pageNr);
			QMetaObject::invokeMethod(info.obj, info.slot, Q_ARG(QPixmap, QPixmap::fromImage(img)), Q_ARG(int, pageNr));
		}
	}
}

qreal PDFRenderManager::getResLimit()
{
	return kMaxDpiForFullPage;
}

void PDFRenderManager::fillCache(int pg)
{
	if (document.isNull()) return;
	QSet<int> renderedPage;
	foreach (RecInfo elem, lstOfReceivers) {
		if (elem.cache)
			renderedPage.insert(elem.pageNr);
	}
	foreach (int elem, renderedPages.keys()) {
		renderedPage.insert(elem);
	}
	int i = pg - 1;
	int j = pg;
	if (j < 0)
		j = -1;
	const int MAX_CACHE_OFFSET = 20; // disables filling of overview dock ...
	int max = qMin(cachedNumPages, pg + MAX_CACHE_OFFSET);
	int min = qMax(0, pg - MAX_CACHE_OFFSET);
	while (i >= min || j < max) {
		j++;
		if (i >= min && i < max && !renderedPage.contains(i)) // don't rerender page
            renderToImage(i, nullptr, "");
		if (j >= min && j < max && !renderedPage.contains(j)) // don't rerender page
            renderToImage(j, nullptr, "");
		i--;
	}
	mFillCacheMode = false;
}

bool PDFRenderManager::checkDuplicate(int &, RecInfo &info)
{
	//check if a similar picture is not already in the renderqueue
	QMultiMap<int, RecInfo>::const_iterator i = lstOfReceivers.constBegin();
	for (; i != lstOfReceivers.constEnd(); ++i) {
		if (i.value().pageNr != info.pageNr)
			continue;
		if (i.value().x < 0 && i.value().y < 0 && i.value().w < 0 && i.value().h < 0
		        && info.x < 0 && info.y < 0 && info.w < 0 && info.h < 0) {
			if (info.priority) {
				//qDebug()<<"duplicate";
				return true;
			}
		}
	}
	return false;
}

void PDFRenderManager::enqueue(RenderCommand cmd, bool priority)
{
	queueAdministration->mQueueLock.lock();
	if (priority) {
		queueAdministration->mCommands.prepend(cmd);
	} else {
		queueAdministration->mCommands.enqueue(cmd);
	}
	queueAdministration->mQueueLock.unlock();
	queueAdministration->mCommandsAvailable.release();
}

void PDFRenderManager::reduceCacheFilling(double fraction)
{
	int targetCost = renderedPages.totalCost() * fraction;

	foreach (int key, renderedPages.keys()) {
		if (renderedPages.totalCost() < targetCost)
			break;
		renderedPages.remove(key);
	}
}

#endif
