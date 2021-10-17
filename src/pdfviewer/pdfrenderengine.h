#ifndef Header_PDF_RenderEngine
#define Header_PDF_RenderEngine

#ifndef NO_POPPLER_PREVIEW

#include "smallUsefulFunctions.h"

#if QT_VERSION_MAJOR>5
#include "poppler-qt6.h"
#else
#include "poppler-qt5.h"
#endif
#include "poppler-version.h"

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>
#include <QImage>


class PDFQueue;

class RenderCommand
{
public:
	explicit RenderCommand(int p, double xr = 72.0, double yr = 72.0, int x = -1, int y = -1, int w = -1, int h = -1);
	int pageNr;
	double xres;
	double yres;
	int x;
	int y;
	int w;
	int h;
	Poppler::Page::Rotation rotate;
	int ticket;
	bool priority;
};

class PDFRenderEngine : public SafeThread
{
	Q_OBJECT

public:
	explicit PDFRenderEngine(QObject *parent, PDFQueue *mQueue);
	~PDFRenderEngine();

	QByteArray tempData;
	void setDocument(const QSharedPointer<Poppler::Document> &doc);

signals:
	void sendImage(QImage image, int page, int ticket);

public slots:

protected:
	void run();

private:
	QSharedPointer<Poppler::Document> document;
	int cachedNumPages;
	PDFQueue *queue;
};

#endif // PDFRENDERENGINE_H

#endif
