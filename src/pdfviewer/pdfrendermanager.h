#ifndef Header_PDF_RenderManager
#define Header_PDF_RenderManager

#include "mostQtHeaders.h"

#ifndef NO_POPPLER_PREVIEW

#include <QCache>
#include <QImage>

#include "pdfrenderengine.h"

class RecInfo
{
public:
	QObject *obj;
	const char *slot;
	int x, y, w, h;
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
	void setRes(qreal res, int x, int y);
	qreal getRes()
	{
		return resolution;
	}
	QPoint getCoord()
	{
		return QPoint(x, y);
	}

private:
	qreal resolution;
	int x, y;
};


class PDFQueue : public QObject
{
public:
	explicit PDFQueue(QObject *parent = nullptr);

	inline void ref()
	{
		m_ref.ref();
	}
	void deref();
	int getRef()
	{
		return m_ref.fetchAndAddRelaxed(0);
	}

	QQueue<RenderCommand> mCommands;
	QSemaphore mCommandsAvailable;
	QMutex mQueueLock;
	bool stopped;

	QMutex mPriorityLock;

	int num_renderQueues;

	QList<PDFRenderEngine *>renderQueues;

	QByteArray documentData;

private:
	QAtomicInt m_ref;
};

class SetImageForwarder : public QObject
{
    Q_OBJECT

public:
    explicit SetImageForwarder(QObject *parent, QObject *obj, const char *rec, QPixmap img, int pageNr);
    QObject *obj;
    const char *rec;
    QPixmap img;
    int pageNr;

    void forward(int delay);

public slots:
    void setImage();
};

class PDFRenderManager : public QObject
{
	Q_OBJECT

public:
    explicit PDFRenderManager(QObject *parent, int limitQueues = 0);
	~PDFRenderManager();

	static const int BufferedLoad = 0;
	static const int DirectLoad = 1;
	static const int HybridLoad = 2;
	enum Error {NoError, FileOpenFailed, PopplerError, PopplerErrorBadAlloc, PopplerErrorException, FileLocked, FileIncomplete };

    QPixmap renderToImage(int pageNr, QObject *obj, const char *rec, double xres = 72.0, double yres = 72.0, int x = -1, int y = -1, int w = -1, int h = -1, bool cache = true, bool priority = false, int delayTimeout = -1, Poppler::Page::Rotation rotate = Poppler::Page::Rotate0);
    QSharedPointer<Poppler::Document> loadDocument(const QString &fileName, Error &error, const QString &userPasswordStr,  bool foreceLoad = false);
	void stopRendering();
	void setCacheSize(int megabyte);
	void fillCache(int pg = -1);
	qreal getResLimit();
	void setLoadStrategy(int strategy);

public slots:
	void addToCache(QImage img, int pageNr, int ticket);

private:
	friend class PDFRenderEngine;
	bool checkDuplicate(int &ticket, RecInfo &info);
	void enqueue(RenderCommand cmd, bool priority);

	void reduceCacheFilling(double fraction);

    QSharedPointer<Poppler::Document> document;
	int cachedNumPages;

	QCache<int, CachePixmap> renderedPages;
	QMultiMap<int, RecInfo> lstOfReceivers;
	int currentTicket;

	QMap<int, RecInfo> lstForThumbs;
	PDFQueue *queueAdministration;
	bool mFillCacheMode;

	int loadStrategy;
};

#endif // PDFRENDERMANAGER_H

#endif
