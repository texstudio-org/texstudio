/*
	This is part of TeXworks, an environment for working with TeX documents
	Copyright (C) 2007-2010  Jonathan Kew

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	For links to further information, or to contact the author,
	see <http://texworks.org/>.
*/

#ifndef NO_POPPLER_PREVIEW

#include "PDFDocument.h"
#include "PDFDocks.h"
//#include "FindDialog.h"

#include <QPaintEngine>
#include <QRegion>
#include <QUrl>
#include <QShortcut>
#include <QtCore/qnumeric.h>
#include <QtCore/qmath.h>

#include "universalinputdialog.h"

#include "configmanager.h"
#include "smallUsefulFunctions.h"
#include "PDFDocument_config.h"
#include "configmanagerinterface.h"
#include "pdfannotationdlg.h"
#include "pdfannotation.h"
#include "minisplitter.h"
#include "titledpanel.h"

#include "pdfsplittool.h"
#include "filedialog.h"

//#include "GlobalParams.h"

#include "poppler-link.h"

#define SYNCTEX_GZ_EXT	".synctex.gz"
#define SYNCTEX_EXT		".synctex"

const qreal kMaxScaleFactor = 4.0;
const qreal kMinScaleFactor = 0.125;

// tool codes
const int kNone = 0;
const int kMagnifier = 1;
const int kScroll = 2;
const int kSelectText = 3;
const int kSelectImage = 4;
const int kPresentation = 5; //left-click: next, rclick: prev (for these presentation/mouse-pointer)

static PDFDocumentConfig *globalConfig = 0;
bool PDFDocument::isCompiling = false;
bool PDFDocument::isMaybeCompiling = false;

static const int GridBorder = 5;


QPixmap convertImage(const QPixmap &pixmap, bool invertColors, bool convertToGray)
{
	if (pixmap.isNull()) return pixmap;

	QImage img = pixmap.toImage();
	if (invertColors)
		img.invertPixels();
	if (convertToGray) {
		QImage retImg(img.width(), img.height(), QImage::Format_Indexed8);
		QVector<QRgb> table(256);
		for ( int i = 0; i < 256; ++i) {
			table[i] = qRgb(i, i, i);
		}
		retImg.setColorTable(table);
		for (int i = 0; i < img.width(); i++) {
			for (int j = 0; j < img.height(); j++) {
				QRgb value = img.pixel(i, j);
				retImg.setPixel(i, j, qGray(value));
			}
		}
		return QPixmap::fromImage(retImg);
	}
	return QPixmap::fromImage(img);
}

//====================Zoom utils==========================

void zoomToScreen(QWidget *window)
{
	QDesktopWidget *desktop = QApplication::desktop();
	QRect screenRect = desktop->availableGeometry(window);
	screenRect.setTop(screenRect.top() + window->geometry().y() - window->y());
	window->setGeometry(screenRect);
}

void zoomToHalfScreen(QWidget *window, bool rhs)
{
	QDesktopWidget *desktop = QApplication::desktop();
	QRect r = desktop->availableGeometry(window);
	int wDiff = window->frameGeometry().width() - window->width();
	int hDiff = window->frameGeometry().height() - window->height();

	if (hDiff == 0 && wDiff == 0) {
		// window may not be decorated yet, so we don't know how large
		// the title bar etc. is. Try to extrapolate from other top-level
		// windows (if some are available). We assume that if either
		// hDiff or wDiff is non-zero, we have found a decorated window
		// and can use its values.
		foreach (QWidget *widget, QApplication::topLevelWidgets()) {
			if (!qobject_cast<QMainWindow *>(widget))
				continue;
			hDiff = widget->frameGeometry().height() - widget->height();
			wDiff = widget->frameGeometry().width() - widget->width();
			if (hDiff != 0 || wDiff != 0)
				break;
		}
		// If we still have no valid value for hDiff/wDiff, just guess (on some
		// platforms)
		if (hDiff == 0 && wDiff == 0) {
			// (these values were determined on WinXP with default theme)
			hDiff = 34;
			wDiff = 8;
		}
	}

	if (rhs) {
		r.setLeft(r.left() + r.width() / 2);
		window->move(r.left(), r.top());
		window->resize(r.width() - wDiff, r.height() - hDiff);
	} else {
		r.setWidth(r.width() / 2);
		window->move(r.left(), r.top());
		window->resize(r.width() - wDiff, r.height() - hDiff);
	}
}

void windowsSideBySide(QWidget *window1, QWidget *window2)
{
	QDesktopWidget *desktop = QApplication::desktop();

	// if the windows reside on the same screen zoom each so that it occupies
	// half of that screen
	if (desktop->screenNumber(window1) == desktop->screenNumber(window2)) {
		int window1left = window1->pos().x() <= window2->pos().x();
		zoomToHalfScreen(window1, !window1left);
		zoomToHalfScreen(window2, window1left);
	}
	// if the windows reside on different screens zoom each so that it uses
	// its whole screen
	else {
		zoomToScreen(window1);
		zoomToScreen(window2);
	}
}

void tileWindowsInRect(const QWidgetList &windows, const QRect &bounds)
{
	int numWindows = windows.count();
	int rows = 1, cols = 1;
	while (rows * cols < numWindows)
		if (rows == cols)
			++cols;
		else
			++rows;
	QRect r;
	r.setWidth(bounds.width() / cols);
	r.setHeight(bounds.height() / rows);
	r.moveLeft(bounds.left());
	r.moveTop(bounds.top());
	int x = 0, y = 0;
	foreach (QWidget *window, windows) {
		int wDiff = window->frameGeometry().width() - window->width();
		int hDiff = window->frameGeometry().height() - window->height();
		window->move(r.left(), r.top());
		window->resize(r.width() - wDiff, r.height() - hDiff);
		if (window->isMinimized())
			window->showNormal();
		if (++x == cols) {
			x = 0;
			++y;
			r.moveLeft(bounds.left());
			r.moveTop(bounds.top() + (bounds.height() * y) / rows);
		} else
			r.moveLeft(bounds.left() + (bounds.width() * x) / cols);
	}
}

void stackWindowsInRect(const QWidgetList &windows, const QRect &bounds)
{
	const int kStackingOffset = 20;
	QRect r(bounds);
	r.setWidth(r.width() / 2);
	int index = 0;
	foreach (QWidget *window, windows) {
		int wDiff = window->frameGeometry().width() - window->width();
		int hDiff = window->frameGeometry().height() - window->height();
		window->move(r.left(), r.top());
		window->resize(r.width() - wDiff, r.height() - hDiff);
		if (window->isMinimized())
			window->showNormal();
		r.moveLeft(r.left() + kStackingOffset);
		if (r.right() > bounds.right()) {
			r = bounds;
			r.setWidth(r.width() / 2);
			index = 0;
		} else if (++index == 10) {
			r.setTop(bounds.top());
			index = 0;
		} else {
			r.setTop(r.top() + kStackingOffset);
			if (r.height() < bounds.height() / 2) {
				r.setTop(bounds.top());
				index = 0;
			}
		}
	}
}


//================== PDFMagnifier ========================

const int kMagFactor = 2;

PDFMagnifier::PDFMagnifier(QWidget *parent, qreal inDpi)
	: QLabel(parent)
	, oldshape(-2)
	, page(-1)
	, overScale(1)
	, scaleFactor(kMagFactor)
	, parentDpi(inDpi)
	, convertedImageIsGrayscale(false)
	, convertedImageIsColorInverted(false)
	, imageDpi(0)
	, imagePage(-1)
{
}

void PDFMagnifier::setPage(int pageNr, qreal scale, const QRect &visibleRect)
{
	page = pageNr;
#if QT_VERSION >= 0x050000
	overScale = this->devicePixelRatio();
#else
	overScale = isRetinaMac() ? 2 : 1;
#endif
	scaleFactor = scale * kMagFactor;
	if (page < 0) {
		imagePage = -1;
		image = QPixmap();
		convertedImage = QPixmap();
		convertedImageIsGrayscale = false;
		convertedImageIsColorInverted = false;
	} else {
		PDFWidget *parent = qobject_cast<PDFWidget *>(parentWidget());
		if (parent != NULL) {
			PDFDocument *doc = parent->getPDFDocument();
			QWidget *viewport = parent->parentWidget();
			if (viewport != NULL && viewport->parentWidget() != NULL) {
				qreal dpi = parentDpi * scaleFactor;
				QPoint tl = parent->mapFromParent(viewport->rect().topLeft());
				QPoint br = parent->mapFromParent(viewport->rect().bottomRight());
				tl -= visibleRect.topLeft();
				br -= visibleRect.topLeft();
				if (tl.x() < 0) tl.setX(0);
				if (tl.y() < 0) tl.setY(0);
				if (br.x() > visibleRect.width()) br.setX(visibleRect.width());
				if (br.y() > visibleRect.height()) br.setY(visibleRect.height());
				QSize  size = QSize(br.x() - tl.x(), br.y() - tl.y()) * kMagFactor;
				QPoint loc = tl * kMagFactor;
				if (page != imagePage || dpi != imageDpi || loc != imageLoc || size != imageSize) {
					//don't cache in rendermanager in order to reduce memory consumption
					image = doc->renderManager->renderToImage(pageNr, this, "setImage", dpi * overScale , dpi * overScale, loc.x() * overScale, loc.y() * overScale, size.width() * overScale, size.height() * overScale, false, true);
				}
				imagePage = page;
				imageDpi = dpi;
				imageLoc = loc;
				imageSize = size;

				mouseTranslate = rect().center() - imageLoc  - (visibleRect.topLeft() /*- offset*/) * kMagFactor;

			}
		}
	}
	update();
}

void PDFMagnifier::reshape()
{
	Q_ASSERT(globalConfig);
	if (!globalConfig || globalConfig->magnifierShape == oldshape) return;

	switch (globalConfig->magnifierShape) {
	case 2: ;
	case 1: { //circular
	        int side = qMin(width(), height());
		QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side, side, QRegion::Ellipse);
		setMask(maskedRegion);
		break;
	}
	default:
		setMask(QRect(0, 0, width(), height())); //rectangular
	}
}

void PDFMagnifier::setImage(const QPixmap &img, int pageNr)
{
	if (pageNr == page) {
		image = img;
		convertedImage = QPixmap();
		convertedImageIsGrayscale = false;
		convertedImageIsColorInverted = false;
	}
	update();
}

void PDFMagnifier::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFrame(&painter);
	QRect tmpRect(event->rect().x()*overScale, event->rect().y()*overScale, event->rect().width()*overScale, event->rect().height()*overScale);
	int side = qMin(width(), height()) ;
	QRect outline(width() / 2 - side / 2 + 1, height() / 2 - side / 2 + 1, side - 2, side - 2);

	if(globalConfig->magnifierShape==1){
	    // circular magnifier, add transparent shadow
	    const int padding=10;

	    QRadialGradient gradient(outline.center(), outline.width() / 2.0 , outline.center());
	    QColor color(Qt::black);
	    color.setAlpha(0);
	    gradient.setColorAt(1.0, color);
	    color.setAlpha(64);
	    gradient.setColorAt(1.0 - padding * 2.0 / (outline.width()), color);

	    painter.fillRect(outline, gradient);
	    outline.adjust(padding,padding,-padding,-padding);
	    QRegion maskedRegion(outline, QRegion::Ellipse);
	    painter.setClipRegion(maskedRegion);
	}

	// draw highlight if necessary

	painter.drawPixmap(event->rect(), getConvertedImage(), tmpRect.translated(kMagFactor * overScale * pos() + mouseTranslate * overScale));

	// draw highlight if necessary
	{
	    PDFWidget *parent = qobject_cast<PDFWidget *>(parentWidget());
	    if (parent != NULL) {
		if(page == parent->highlightPage){
		    if (!parent->highlightPath.isEmpty()) {
			    painter.save();
			    painter.setRenderHint(QPainter::Antialiasing);
			    painter.translate(-kMagFactor  * pos()- mouseTranslate -imageLoc );
			    painter.scale(imageDpi/72.0, imageDpi/72.0);
			    painter.setPen(QColor(0, 0, 0, 0));
			    painter.setBrush(UtilsUi::colorFromRGBAstr(globalConfig->highlightColor, QColor(255, 255, 0, 63)));
			    //QPainterPath path=highlightPath;
			    //path.translate(drawTo.left()*72.0/dpi/scaleFactor, drawTo.top()*72.0/dpi/scaleFactor);
			    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
			    painter.drawPath(parent->highlightPath);
			    painter.restore();
		    }
		}
	    }
	}

	if (globalConfig->magnifierBorder) {
		painter.setPen(QPalette().mid().color());
		switch (globalConfig->magnifierShape) {
		case 1: { //circular
		        //int side = qMin(width(), height()) ;
		        //painter.drawEllipse(width() / 2 - side / 2 + 1, height() / 2 - side / 2 + 1, side - 2, side - 2);
		        painter.drawEllipse(outline);
			break;
		}
		case 2: { //circular without shadow
		        int side = qMin(width(), height()) ;
			painter.drawEllipse(width() / 2 - side / 2 + 1, height() / 2 - side / 2 + 1, side - 2, side - 2);
			break;
		}
		default:
			painter.drawRect(0, 0, width() - 1, height() - 1); //rectangular
		}
	}
}

/* lazy evaluation of image convertion */
QPixmap &PDFMagnifier::getConvertedImage()
{
	if (!globalConfig->invertColors && !globalConfig->grayscale) {  // no processing needed
		return image;
	}
	if (globalConfig->invertColors == convertedImageIsColorInverted && globalConfig->grayscale == convertedImageIsGrayscale) {  // conversion already done
		return convertedImage;
	}
	convertedImage = convertImage(image, globalConfig->invertColors, globalConfig->grayscale);
	return convertedImage;
}

#ifdef PHONON
PDFMovie::PDFMovie(PDFWidget *parent, QSharedPointer<Poppler::MovieAnnotation> annot, int page): VideoPlayer(parent), page(page)
{
	REQUIRE(parent && annot && parent->getPDFDocument());
	REQUIRE(annot->subType() == Poppler::Annotation::AMovie);
	REQUIRE(annot->movie());
	boundary = annot->boundary();
	QString url = annot->movie()->url();
	url = QFileInfo(parent->getPDFDocument()->fileName()).dir().absoluteFilePath(url);
	if (!QFileInfo(url).exists()) {
		QMessageBox::warning(this, "", tr("File %1 does not exists").arg(url));
		return;
	}
	this->load(url);

	popup = new QMenu(this);
	popup->addAction(tr("&Play"), this, SLOT(realPlay()));
	popup->addAction(tr("P&ause"), this, SLOT(pause()));
	popup->addAction(tr("&Stop"), this, SLOT(stop()));
	popup->addSeparator();
	popup->addAction(tr("S&eek"), this, SLOT(seekDialog()));
	popup->addAction(tr("Set &volume"), this, SLOT(setVolumeDialog()));

	setCursor(Qt::PointingHandCursor);
}

void PDFMovie::place()
{
	PDFWidget *pdf = qobject_cast<PDFWidget *>(parent());
	REQUIRE(pdf);
	QPointF tl = pdf->mapFromScaledPosition(page, boundary.topLeft());
	QPointF br = pdf->mapFromScaledPosition(page, boundary.bottomRight());
	setFixedSize(br.x() - tl.x(), br.y() - tl.y());
	move(tl.toPoint());
}

void PDFMovie::contextMenuEvent(QContextMenuEvent *e)
{
	popup->popup(e->globalPos());
	e->accept();
}

void PDFMovie::mouseReleaseEvent(QMouseEvent *e)
{
	//qDebug() << "click: "<<isPaused() << " == !" << isPlaying() << " " << currentTime() << " / " << totalTime();
	if (isPlaying()) pause();
	else realPlay();
	e->accept();
}

void PDFMovie::realPlay()
{
	if (isPlaying()) return;
	if (isPaused() && currentTime() < totalTime()) play();
	else {
		seek(0);
		QTimer::singleShot(500, this, SLOT(play()));
	}
}

void PDFMovie::setVolumeDialog()
{
	float vol = volume();
	UniversalInputDialog uid;
	uid.addVariable(&vol, tr("Volume:"));
	if (!uid.exec()) return;
	setVolume(vol);
}

void PDFMovie::seekDialog()
{
	float pos = currentTime() * 0.001;
	UniversalInputDialog uid;
	uid.addVariable(&pos, tr("Time:"));
	if (!uid.exec()) return;
	seek(pos * 1000LL);
}
#endif

//#pragma mark === PDFWidget ===

QCursor *PDFWidget::magnifierCursor = NULL;
QCursor *PDFWidget::zoomInCursor = NULL;
QCursor *PDFWidget::zoomOutCursor = NULL;

PDFWidget::PDFWidget(bool embedded)
	: QLabel()
	, realPageIndex(0), oldRealPageIndex(0)
	, scaleFactor(1.0)
	, dpi(72.0)
	, scaleOption(kFixedMag)
	, inhibitNextContextMenuEvent(false)
	, summedWheelDegrees(0)
	, docPages(0)
	, saveScaleFactor(1.0)
	, saveScaleOption(kFitWidth)
	, ctxZoomInAction(0)
	, ctxZoomOutAction(0)
	, shortcutUp(0)
	, shortcutLeft(0)
	, shortcutDown(0)
	, shortcutRight(0)

	, imageDpi(0)
	, imagePage(-1)
	, magnifier(NULL)
	, currentTool(kNone)
	, usingTool(kNone)
	, singlePageStep(true)
	, gridx(1), gridy(1)
	, forceUpdate(false)
	, highlightPage(-1)
	, pdfdocument(0)
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return;

#ifdef PHONON
	movie = 0;
#endif
	maxPageSize.setHeight(-1.0);
	maxPageSize.setWidth(-1.0);
	horizontalTextRange.setWidth(-1.0);

	dpi = globalConfig->dpi;
	if (dpi <= 0) dpi = 72; //it crashes if dpi=0

	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setFocusPolicy(embedded ? Qt::NoFocus : Qt::StrongFocus);
	setScaledContents(true);
	setMouseTracking(true);
	grabGesture(Qt::PinchGesture);
	grabGesture(Qt::TapGesture);

	switch (globalConfig->scaleOption) {
	default:
		fixedScale(1.0);
		break;
	case 1:
		fitWidth(true);
		break;
	case 2:
		fitWindow(true);
		break;
	case 3:
		fixedScale(globalConfig->scale / 100.0);
		break;
	case 4:
		fitTextWidth(true);
		break;
	}

	if (magnifierCursor == NULL) {
		magnifierCursor = new QCursor(QPixmap(getRealIconFile("magnifier")).scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		zoomInCursor = new QCursor(QPixmap(getRealIconFile("zoom-in")).scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		zoomOutCursor = new QCursor(QPixmap(getRealIconFile("zoom-out")).scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}

	ctxZoomInAction = new QAction(tr("Zoom In"), this);
	addAction(ctxZoomInAction);
	ctxZoomOutAction = new QAction(tr("Zoom Out"), this);
	addAction(ctxZoomOutAction);

	QAction *action = new QAction(tr("Actual Size"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(fixedScale()));
	addAction(action);
	action = new QAction(tr("Fit to Width"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(fitWidth()));
	addAction(action);
	action = new QAction(tr("Fit to Window"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(fitWindow()));
	addAction(action);

	Qt::ShortcutContext context = embedded ? Qt::WidgetWithChildrenShortcut : Qt::WindowShortcut;
	shortcutUp = new QShortcut(QKeySequence("Up"), this, SLOT(upOrPrev()), 0, context);
	shortcutLeft = new QShortcut(QKeySequence("Left"), this, SLOT(leftOrPrev()), 0, context);
	shortcutDown = new QShortcut(QKeySequence("Down"), this, SLOT(downOrNext()), 0, context);
	shortcutRight = new QShortcut(QKeySequence("Right"), this, SLOT(rightOrNext()), 0, context);

	highlightRemover.setSingleShot(true);
	highlightPage = -1;
	connect(&highlightRemover, SIGNAL(timeout()), this, SLOT(clearHighlight()));
	docPages = 0;
	pageHistoryIndex = -1;
}

PDFWidget::~PDFWidget()
{
}

void PDFWidget::setPDFDocument(PDFDocument *docu)
{
	pdfdocument = docu;
}

void PDFWidget::setDocument(const QSharedPointer<Poppler::Document> &doc)
{
	pages.clear();
	document = doc;
	maxPageSize.setHeight(-1.0);
	maxPageSize.setWidth(-1.0);

	if (!document.isNull()) {
		docPages = document->numPages();
		setSinglePageStep(globalConfig->singlepagestep);
	} else
		docPages = 0;
#ifdef PHONON
	if (movie) {
		delete movie;
		movie = 0;
	}
#endif
	reloadPage();
	windowResized();
}

void PDFWidget::windowResized()
{
	switch (scaleOption) {
	case kFixedMag:
		break;
	case kFitWidth:
		fitWidth(true);
		break;
	case kFitTextWidth:
		fitTextWidth(true);
		break;
	case kFitWindow:
		fitWindow(true);
		break;
	}
	update();
}

void fillRectBorder(QPainter &painter, const QRect &inner, const QRect &outer)
{
	painter.drawRect(outer.x(),     outer.y(), inner.x()     - outer.x(),     outer.height());
	painter.drawRect(inner.right(), outer.y(), outer.right() - inner.right(), outer.height());

	painter.drawRect(inner.x(), outer.y(),      inner.width(), inner.y()      - outer.y());
	painter.drawRect(inner.x(), inner.bottom(), inner.width(), outer.bottom() - inner.bottom());
}

void PDFWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFrame(&painter);

	qreal newDpi = dpi * scaleFactor;
#if QT_VERSION >= 0x050000
	int overScale = painter.device()->devicePixelRatio();
#else
	int overScale = isRetinaMac() ? 2 : 1;
#endif

	QRect newRect = rect();
	PDFDocument *doc = getPDFDocument();
	if (!doc || !doc->renderManager)
		return;
	if (pages.size() > 0 && (realPageIndex != imagePage || newDpi != imageDpi || newRect != imageRect || forceUpdate)) {
		painter.setBrush(QApplication::palette().color(QPalette::Dark));
		painter.setPen(QApplication::palette().color(QPalette::Dark));
		if (gridx <= 1 && gridy <= 1) {
			int pageNr = pages.first();
			QRect drawTo = pageRect(pageNr);
			image = doc->renderManager->renderToImage(pageNr, this, "setImage", dpi * scaleFactor * overScale, dpi * scaleFactor * overScale,
			        0, 0, newRect.width() * overScale, newRect.height() * overScale, true, true);
			if (globalConfig->invertColors || globalConfig->grayscale)
				image = convertImage(image, globalConfig->invertColors, globalConfig->grayscale);
			fillRectBorder(painter, drawTo, newRect);
			QRect source = event->rect().translated(-drawTo.topLeft());
			painter.drawPixmap(event->rect(), image, QRect(source.left() * overScale, source.top() * overScale, source.width() * overScale, source.height() * overScale));
			if (pageNr == highlightPage && !highlightPath.isEmpty() ) {
				painter.setRenderHint(QPainter::Antialiasing);
				painter.setCompositionMode(QPainter::CompositionMode_Multiply);
				painter.scale(totalScaleFactor(), totalScaleFactor());
				painter.setPen(QColor(0, 0, 0, 0));
				painter.setBrush(UtilsUi::colorFromRGBAstr(globalConfig->highlightColor, QColor(255, 255, 0, 63)));
				painter.drawPath(highlightPath);
			}
			if (currentTool == kPresentation)
				doc->renderManager->renderToImage(pageNr + 1, this, "", dpi * scaleFactor * overScale, dpi * scaleFactor * overScale, 0, 0, newRect.width() * overScale, newRect.height()*overScale, true, true);
		} else {
			QRect visRect = visibleRegion().boundingRect();
			//image = QPixmap(newRect.width(), newRect.height());
			//image.fill(QApplication::palette().color(QPalette::Dark).rgb());

			//QPainter p;
			//p.begin(&image);
			// paint border betweend pages
			QSizeF realPageSize = maxPageSizeFDpiAdjusted() * scaleFactor;

			int realPageSizeX = qRound(realPageSize.width());
			int realPageSizeY = qRound(realPageSize.height());

			//painter.save();
			for (int i = 1; i < gridx; i++) {
				QRect rec((realPageSizeX + GridBorder)*i, 0, -GridBorder, newRect.height());
				if (rec.intersects(visRect))
					painter.drawRect(rec);
			}
			for (int i = 1; i < gridy; i++) {
				QRect rec(0, (realPageSizeY + GridBorder)*i, newRect.width(), -GridBorder);
				if (rec.intersects(visRect))
					painter.drawRect(rec);
			}

			int curGrid = 0;
			if (getPageOffset() && realPageIndex == 0) {
				painter.drawRect(gridPageRect(0));
				curGrid++;
			}
			foreach (int pageNr, pages) {
				QRect basicGrid = gridPageRect(curGrid++);
				QRect drawGrid = pageRect(pageNr);
				if (!drawGrid.intersects(visRect)) { // don't draw invisible pages
					painter.drawRect(basicGrid);
					continue;
				}
				QPixmap temp = doc->renderManager->renderToImage(
				                   pageNr, this, "setImage",
				                   dpi * scaleFactor * overScale,
				                   dpi * scaleFactor * overScale,
				                   0, 0, drawGrid.width() * overScale, drawGrid.height() * overScale, true, true);
				if (globalConfig->invertColors || globalConfig->grayscale)
					temp = convertImage(temp, globalConfig->invertColors, globalConfig->grayscale);
				if (drawGrid != basicGrid)
					fillRectBorder(painter, drawGrid, basicGrid);
				painter.drawPixmap(QRect(drawGrid.left(), drawGrid.top(), temp.width() / overScale, temp.height() / overScale), temp);
				if (pageNr == highlightPage) {
					if (!highlightPath.isEmpty()) {
						painter.save();
						painter.setRenderHint(QPainter::Antialiasing);
						painter.translate(drawGrid.left(), drawGrid.top());
						painter.scale(totalScaleFactor(), totalScaleFactor());
						painter.setPen(QColor(0, 0, 0, 0));
						painter.setBrush(UtilsUi::colorFromRGBAstr(globalConfig->highlightColor, QColor(255, 255, 0, 63)));
						//QPainterPath path=highlightPath;
						//path.translate(drawTo.left()*72.0/dpi/scaleFactor, drawTo.top()*72.0/dpi/scaleFactor);
						painter.setCompositionMode(QPainter::CompositionMode_Multiply);
						painter.drawPath(highlightPath);
						painter.restore();
					}
				}
			}
			for (; curGrid < gridx * gridy; curGrid++)
				painter.drawRect(gridPageRect(curGrid));
			//p.end();
			//painter.restore();
		}
	}

	imagePage = pages.isEmpty() ? -1 : realPageIndex;
	imageDpi = newDpi;
	imageRect = newRect;
}

void PDFWidget::setImage(QPixmap, int)
{
	forceUpdate = true;
    update();
}

void PDFWidget::useMagnifier(const QMouseEvent *inEvent)
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return;
	int page = pageFromPos(inEvent->pos());
	if (page < 0) return;
	if (!magnifier) magnifier = new PDFMagnifier(this, dpi);
	magnifier->setFixedSize(globalConfig->magnifierSize * 4 / 3, globalConfig->magnifierSize);
	magnifier->setPage(page, scaleFactor, pageRect(page));
	magnifier->reshape();
	// this was in the hope that if the mouse is released before the image is ready,
	// the magnifier wouldn't actually get shown. but it doesn't seem to work that way -
	// the MouseMove event that we're posting must end up ahead of the mouseUp
	QMouseEvent *event = new QMouseEvent(QEvent::MouseMove, inEvent->pos(), inEvent->globalPos(), inEvent->button(), inEvent->buttons(), inEvent->modifiers());
	QCoreApplication::postEvent(this, event);
	usingTool = kMagnifier;
}

// Mouse control for the various tools:
// * magnifier
//   - ctrl-click to sync
//   - click to use magnifier
//   - shift-click to zoom in
//   - shift-click and drag to zoom to selected area
//   - alt-click to zoom out
// * scroll (hand)
//   - ctrl-click to sync
//   - click and drag to scroll
//   - double-click to use magnifier
// * select area (crosshair)
//   - ctrl-click to sync
//   - click and drag to select area
//   - double-click to use magnifier
// * select text (I-beam)
//   - ctrl-click to sync
//   - click and drag to select text
//   - double-click to use magnifier

static QPoint scrollClickPos;
static Qt::KeyboardModifiers mouseDownModifiers;

void PDFWidget::mousePressEvent(QMouseEvent *event)
{
	clickedLink.clear();
	clickedAnnotation.clear();

	switch (event->button()) {
	case Qt::LeftButton:
		break; // all cases handled below
	case Qt::XButton1:
		goBack();
		return;
	case Qt::XButton2:
		goForward();
		return;
	default:
		return;
	}

	if (event->button() == Qt::XButton1) {
		goBack();
		return;
	}

	if (event->button() != Qt::LeftButton) {
		QWidget::mousePressEvent(event);
		return;
	}

	mouseDownModifiers = event->modifiers();
	if (mouseDownModifiers & Qt::ControlModifier) {
		// ctrl key - this is a sync click, don't handle the mouseDown here
	} else if (currentTool != kPresentation) {
		QPointF scaledPos;
		int pageNr;
		mapToScaledPosition(event->pos(), pageNr, scaledPos);
		if (pageNr >= 0 && pageNr < realNumPages()) {
			QScopedPointer<Poppler::Page> page(document->page(pageNr));
			if (page) {
				// check for click in link
				foreach (Poppler::Link *link, page->links()) {
					if (link->linkArea().contains(scaledPos)) {
						clickedLink = QSharedPointer<Poppler::Link>(link);
						continue;  // no break because we have to delete all other links
					}
					delete link;
				}
				if (!clickedLink) {
					foreach (Poppler::Annotation *annon, page->annotations()) {
						if (annon->boundary().contains(scaledPos)) {
							clickedAnnotation = QSharedPointer<Poppler::Annotation>(annon);
							continue;  // no break because we have to delete all other links
						}
						delete annon;
					}
				}
				if (!clickedLink && !clickedAnnotation) {
					switch (currentTool) {
					case kMagnifier:
						if (mouseDownModifiers & (Qt::ShiftModifier | Qt::AltModifier))
							; // do nothing - zoom in or out (on mouseUp)
						else
							useMagnifier(event);
						break;

					case kScroll:
						setCursor(Qt::ClosedHandCursor);
						scrollClickPos = event->globalPos();
						usingTool = kScroll;
						break;
					}
				}
			}
		}
	} else {
		QPointF scaledPos;
		int pageNr;
		mapToScaledPosition(event->pos(), pageNr, scaledPos);
		if (pageNr >= 0 && pageNr < realNumPages()) {
			QScopedPointer<Poppler::Page> page(document->page(pageNr));
			if (page) {
				foreach (Poppler::Annotation *annon, page->annotations()) {
					if (annon->boundary().contains(scaledPos)) {
						clickedAnnotation = QSharedPointer<Poppler::Annotation>(annon);
						continue; // no break because we have to delete all other links
					}
					delete annon;
				}
			}
		}
	}
	event->accept();
}

void PDFWidget::annotationClicked(QSharedPointer<Poppler::Annotation> annotation, int page)
{
	switch (annotation->subType()) {
	case Poppler::Annotation::AMovie: {
#ifdef PHONON
		if (movie) delete movie;
		movie = new PDFMovie(this, qSharedPointerDynamicCast<Poppler::MovieAnnotation>(annotation), page);
		movie->place();
		movie->show();
		movie->play();
#else
		Q_UNUSED(page)
		UtilsUi::txsWarning("You clicked on a video, but the video playing mode was disabled by you or the package creator.\nRecompile TeXstudio with the option PHONON=true");
#endif
		break;
	}

	case Poppler::Annotation::AText:
	case Poppler::Annotation::ACaret:
	case Poppler::Annotation::AHighlight: {
		PDFAnnotationDlg *dlg = new PDFAnnotationDlg(annotation, this);
		dlg->show();
		break;
	}
	default:
		;
	}
}

void PDFWidget::openAnnotationDialog(const PDFAnnotation *annon)
{
	PDFAnnotationDlg *dlg = new PDFAnnotationDlg(annon->popplerAnnotation(), this);
	//qDebug() << annon->popplerAnnotation()->revisionType() << annon->popplerAnnotation()->revisions().count();
	dlg->show();
}

void PDFWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (pdfdocument && pdfdocument->embeddedMode)
		setFocus();
	updateCurrentPageHistoryOffset();
	if (clickedLink) {
		int page;
		QPointF scaledPos;
		mapToScaledPosition(event->pos(), page, scaledPos);
		if (page > -1 && clickedLink->linkArea().contains(scaledPos)) {
			doLink(clickedLink);
		}
	} else if (clickedAnnotation) {
		int page;
		QPointF scaledPos;
		mapToScaledPosition(event->pos(), page, scaledPos);
		if (page > -1 && clickedAnnotation->boundary().contains(scaledPos)) {
			annotationClicked(clickedAnnotation, page);
		}
	} else if (currentTool == kPresentation) {
		if (event->button() == Qt::LeftButton) goNext();
		else if (event->button() == Qt::RightButton) goPrev();
	} else {
		switch (usingTool) {
		case kNone:
			// Ctrl-click to sync
			if (mouseDownModifiers & Qt::ControlModifier) {
				if (event->modifiers() & Qt::ControlModifier)
					syncWindowClick(event->pos(), true);

				break;
			}
			// check whether to zoom
			if (currentTool == kMagnifier) {
				Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();
				if (mods & Qt::AltModifier)
					doZoom(event->pos(), -1);
				else if (mods & Qt::ShiftModifier)
					doZoom(event->pos(), 1);
			}
			break;
		case kMagnifier:
			// Ensure we stop using the tool before hiding the magnifier.
			// Otherwise other events in the queue may be processed between
			// "close()" and "usingTool=" that could show the magnifier
			// again
			usingTool = kNone;
			magnifier->close();
			break;
		}
	}
	clickedLink.clear();
	clickedAnnotation.clear();
	usingTool = kNone;
	updateCursor(event->pos());
	event->accept();
}

void PDFWidget::goToDestination(const Poppler::LinkDestination &dest)
{
	if (dest.pageNumber() > 0)
		goToPageRelativePosition(dest.pageNumber() - 1, dest.isChangeLeft() ? dest.left() : qQNaN(), dest.isChangeTop() ? dest.top() : qQNaN());

	/*if (dest.isChangeZoom()) {
		// FIXME
	}*/
}

void PDFWidget::goToDestination(const QString &destName)
{
	if (document.isNull()) return;
	const Poppler::LinkDestination *dest = document->linkDestination(destName);
	if (dest)
		goToDestination(*dest);
}

void PDFWidget::goToPageRelativePosition(int page, float xinpdf, float yinpdf)
{
	PDFScrollArea *scrollArea = getScrollArea();
	if (!scrollArea) return;

	scrollArea->goToPage(page);

	if (qIsNaN(xinpdf)) xinpdf = 0;
	xinpdf = qBound<float>(0, xinpdf, 1);
	if (qIsNaN(yinpdf)) yinpdf = 0;
	yinpdf = qBound<float>(0, yinpdf, 1);

	QPoint p = mapFromScaledPosition(page, QPointF( xinpdf, yinpdf));

	if (!qIsNaN(xinpdf))
		scrollArea->horizontalScrollBar()->setValue(p.x());

	if (!qIsNaN(yinpdf)) {
		int val = 0;
		if (scrollArea->getContinuous())
			val = scrollArea->verticalScrollBar()->value();
		scrollArea->verticalScrollBar()->setValue(p.y() + val);
	}
}

void PDFWidget::doLink(const QSharedPointer<Poppler::Link> link)
{
	switch (link->linkType()) {
	case Poppler::Link::None:
		break;
	case Poppler::Link::Goto: {
		const Poppler::LinkGoto *go = dynamic_cast<const Poppler::LinkGoto *>(link.data());
		Q_ASSERT(go != NULL);
		if (go->isExternal()) {
			QString filename = go->fileName();
			if (filename.endsWith(".pdf")) {
				QFileInfo fi(filename);
				if (fi.isRelative()) {
					filename = QDir(QFileInfo(pdfdocument->fileName()).absolutePath()).filePath(filename);
				}
				pdfdocument->loadFile(filename);
			} else {
				UtilsUi::txsInformation(tr("Opening external files is currently only supported for PDFs."));
			}
		} else {
			goToDestination(go->destination());
		}
	}
	break;
	case Poppler::Link::Browse: {
		const Poppler::LinkBrowse *browse = dynamic_cast<const Poppler::LinkBrowse *>(link.data());
		Q_ASSERT(browse != NULL);
		QUrl url = QUrl::fromEncoded(browse->url().toLatin1());
		if (url.scheme() == "file" || url.scheme().isEmpty() /*i.e. is relative */) {
			PDFDocument *doc = getPDFDocument();
			if (doc) {
				QFileInfo fi(QFileInfo(doc->fileName()).canonicalPath(), url.toLocalFile());
				url = QUrl::fromLocalFile(fi.absoluteFilePath());
			}
		}
		if (!QDesktopServices::openUrl(url))
			QMessageBox::warning(this, tr("Error"), tr("Could not open link:") + "\n" + url.toString());
	}
	break;
	// unsupported link types:
	//		case Poppler::Link::Execute:
	//			break;
	//		case Poppler::Link::JavaScript:
	//			break;
	//		case Poppler::Link::Action:
	//			break;
	//		case Poppler::Link::Sound:
	//			break;
	//		case Poppler::Link::Movie:
	//			break;
	default:
		break;
	}
}

void PDFWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		QWidget::mouseDoubleClickEvent(event);
		return;
	}
	if (!(mouseDownModifiers & Qt::ControlModifier))
		useMagnifier(event);
	event->accept();
}

void PDFWidget::mouseMoveEvent(QMouseEvent *event)
{
	updateCursor(event->pos());
	switch (usingTool) {
	case kMagnifier: {
		QRect viewportClip(mapFromParent(parentWidget()->rect().topLeft()),
		                   mapFromParent(parentWidget()->rect().bottomRight() - QPoint(1, 1)));
		QPoint constrainedLoc = event->pos();
		if (constrainedLoc.x() < viewportClip.left())
			constrainedLoc.setX(viewportClip.left());
		else if (constrainedLoc.x() > viewportClip.right())
			constrainedLoc.setX(viewportClip.right());
		if (constrainedLoc.y() < viewportClip.top())
			constrainedLoc.setY(viewportClip.top());
		else if (constrainedLoc.y() > viewportClip.bottom())
			constrainedLoc.setY(viewportClip.bottom());
		magnifier->move(constrainedLoc.x() - magnifier->width() / 2, constrainedLoc.y() - magnifier->height() / 2);
		if (magnifier->isHidden()) {
			magnifier->show();
			setCursor(Qt::BlankCursor);
		}
	}
	event->accept();
	break;
	case kScroll: {
		QPoint delta = event->globalPos() - scrollClickPos;
		scrollClickPos = event->globalPos();
		QAbstractScrollArea	*scrollArea = getScrollArea();
		if (scrollArea) {
			if (scaleOption != kFitTextWidth || !globalConfig->disableHorizontalScrollingForFitToTextWidth) {
				int oldX = scrollArea->horizontalScrollBar()->value();
				scrollArea->horizontalScrollBar()->setValue(oldX - delta.x());
			}
			int oldY = scrollArea->verticalScrollBar()->value();
			scrollArea->verticalScrollBar()->setValue(oldY - delta.y());
		}
	}
	event->accept();
	break;
	default:
		event->ignore();
	}
}

void PDFWidget::keyPressEvent(QKeyEvent *event)
{
	updateCursor(mapFromGlobal(QCursor::pos()));
	if (event->key() == Qt::Key_Home)
		goFirst();
	if (event->key() == Qt::Key_End)
		goLast();
	if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return ) {
		if (event->modifiers() & Qt::SHIFT) pageUpOrPrev();
		else pageDownOrNext();
	}
	event->ignore();
}

void PDFWidget::keyReleaseEvent(QKeyEvent *event)
{
	updateCursor(mapFromGlobal(QCursor::pos()));
	event->ignore();
}

void PDFWidget::focusInEvent(QFocusEvent *event)
{
	updateCursor(mapFromGlobal(QCursor::pos()));
	event->ignore();
}

void PDFWidget::contextMenuEvent(QContextMenuEvent *event)
{
	if (inhibitNextContextMenuEvent) {
		inhibitNextContextMenuEvent = false;
		return;
	}

	QMenu	menu(this);

	PDFDocument *pdfDoc = getPDFDocument();
	if (pdfDoc && pdfDoc->hasSyncData()) {
		QAction *act = new QAction(tr("Go to Source"), &menu);
		act->setData(QVariant(event->pos()));
		connect(act, SIGNAL(triggered()), this, SLOT(jumpToSource()));
		menu.addAction(act);
		menu.addSeparator();
	}

	menu.addActions(actions());

	ctxZoomInAction->setEnabled(scaleFactor < kMaxScaleFactor);
	ctxZoomOutAction->setEnabled(scaleFactor > kMinScaleFactor);

	if (usingTool == kMagnifier && magnifier) {
		magnifier->close();
		usingTool = kNone;
	}

	if (pdfDoc && pdfDoc->menuShow) {
		menu.addSeparator();
		menu.addMenu(pdfDoc->menuShow);
	}

	QAction *action = menu.exec(event->globalPos());

	if (action == ctxZoomInAction)
		doZoom(event->pos(), 1);
	else if (action == ctxZoomOutAction)
		doZoom(event->pos(), -1);

}

bool PDFWidget::event(QEvent *event)
{
	if (event->type() == QEvent::Gesture)
		return gestureEvent(static_cast<QGestureEvent *>(event));
	return QLabel::event(event);
}

bool PDFWidget::gestureEvent(QGestureEvent *event)
{
	if (QGesture *gesture = event->gesture(Qt::PinchGesture))
		pinchEvent(static_cast<QPinchGesture *>(gesture));
	if (QGesture *gesture = event->gesture(Qt::TapGesture))
		tapEvent(static_cast<QTapGesture *>(gesture));
	return true;
}

void PDFWidget::pinchEvent(QPinchGesture *gesture)
{
	doZoom(mapFromGlobal(gesture->centerPoint().toPoint()), 0, gesture->scaleFactor()*scaleFactor);
}

void PDFWidget::tapEvent(QTapGesture *gesture)
{
	if (gesture->state() == Qt::GestureFinished) {
		syncWindowClick(gesture->position().toPoint(), true);
	}
}

void PDFWidget::jumpToSource()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act != NULL) {
		QPoint eventPos = act->data().toPoint();
		syncWindowClick(eventPos, true);
		/*
		QPointF pagePos(eventPos.x() / scaleFactor * 72.0 / dpi,
				  eventPos.y() / scaleFactor * 72.0 / dpi);
		emit syncClick(pageIndex, pagePos, true);
		*/
	}
}

void PDFWidget::wheelEvent(QWheelEvent *event)
{
	if (event->delta() == 0) return;
	float numDegrees = event->delta() / 8.0;
	if ((summedWheelDegrees < 0) != (numDegrees < 0)) summedWheelDegrees = 0;
	// we may accumulate rotation and handle it in larger chunks
	summedWheelDegrees += numDegrees;
	const int degreesPerStep = 15; // for a typical mouse (some may have finer resolution, but that's k with the co

	if (event->modifiers() == Qt::ControlModifier || event->buttons() == Qt::RightButton) {
		if (event->buttons() == Qt::RightButton) {
			inhibitNextContextMenuEvent = true;
		}
		if (qFabs(summedWheelDegrees) >= degreesPerStep ) { //avoid small zoom changes, as they use a lot of memory
			doZoom(event->pos(), (summedWheelDegrees > 0) ? 1 : -1);
			summedWheelDegrees = 0;
		}
		event->accept();
	} else	{
		static QTime lastScrollTime = QTime::currentTime();
		QScrollBar *scrollBar = (event->orientation() == Qt::Horizontal)
		                        ? getScrollArea()->horizontalScrollBar()
		                        : getScrollArea()->verticalScrollBar();
		bool mayChangePage = !getScrollArea()->getContinuous();
		if (scrollBar->minimum() < scrollBar->maximum()) { //if scrollbar visible
			int oldValue = scrollBar->value();
			const int scrollPerWheelStep = scrollBar->singleStep() * QApplication::wheelScrollLines();
			scrollBar->setValue(scrollBar->value() - qRound(scrollPerWheelStep * summedWheelDegrees / degreesPerStep));
			int delta = oldValue - scrollBar->value();
			if (delta != 0) {
				lastScrollTime = QTime::currentTime();
				summedWheelDegrees -= delta * degreesPerStep / scrollPerWheelStep;
				mayChangePage = false;
			} else
				mayChangePage &= (scrollBar->value() == scrollBar->minimum()) || (scrollBar->value() == scrollBar->maximum());
			if (QTime::currentTime() < lastScrollTime.addMSecs(500) && qAbs(summedWheelDegrees) < 180)
				mayChangePage = false;
		}
		if (mayChangePage) {
			if (event->delta() > 0 && realPageIndex > 0) {
				goPrev();
				scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
			} else if (event->delta() < 0 && realPageIndex < realNumPages() - 1) {
				goNext();
				scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
			}
			lastScrollTime = QTime::currentTime();
			summedWheelDegrees = 0;
		}
		event->accept();
	}
}

void PDFWidget::setTool(int tool)
{
	currentTool = tool;
	globalConfig->editTool = tool;
	PDFScrollArea *scrollArea = getScrollArea();
	if (scrollArea) UtilsUi::enableTouchScrolling(scrollArea, tool == kScroll);
	updateCursor();
}

void PDFWidget::syncWindowClick(const QPoint &p, bool activate)
{
	int page = pageFromPos(p);
	if (page < 0) return;
	QRect r = pageRect(page);
	emit syncClick(page, QPointF(p - r.topLeft()) / totalScaleFactor(), activate);

}

void PDFWidget::syncCurrentPage(bool activate)
{
	if (pages.isEmpty()) return;
	//single page step mode: jump to center of first page in grid; multi page step: jump to center of grid
	int midPage = pageStep() > 1 ? pages[pages.size() / 2] : pages.first();
	QSize s = pageRect(midPage).size();
	emit syncClick(midPage, QPointF(s.width(), s.height()) / totalScaleFactor(), activate);
}

void PDFWidget::updateCursor()
{
	if (usingTool != kNone)
		return;

	switch (currentTool) {
	case kScroll:
		setCursor(Qt::OpenHandCursor);
		break;
	case kMagnifier: {
		Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();
		if (mods & Qt::AltModifier)
			setCursor(*zoomOutCursor);
		else if (mods & Qt::ShiftModifier)
			setCursor(*zoomInCursor);
		else
			setCursor(*magnifierCursor);
	}
	break;
	case kSelectText:
		setCursor(Qt::IBeamCursor);
		break;
	case kSelectImage:
		setCursor(Qt::CrossCursor);
		break;
	}
}

QRect PDFWidget::mapPopplerRectToWidget(QRectF r, const QSizeF &pageSize) const
{
	r.setWidth(r.width() * scaleFactor * dpi / 72.0 * pageSize.width());
	r.setHeight(r.height() * scaleFactor * dpi / 72.0 * pageSize.height());
	r.moveLeft(r.left() * scaleFactor * dpi / 72.0 * pageSize.width());
	r.moveTop(r.top() * scaleFactor * dpi / 72.0 * pageSize.height());
	QRect rr = r.toRect().normalized();
	rr.setTopLeft(mapToGlobal(rr.topLeft()));
	return rr;
}

#if 0
//only used for testing
void listAnnotationDetails(const Poppler::Annotation *an)
{
	qDebug() << "*** Poppler Annotation ***";
	qDebug() << "subtype       " << an->subType();
	qDebug() << "author        " << an->author();
	qDebug() << "contents      " << an->contents();
	qDebug() << "uniqueName    " << an->uniqueName();
	qDebug() << "modifDate     " << an->modificationDate();
	qDebug() << "creationDate  " << an->creationDate();
	qDebug() << "flags         " << an->flags();
	qDebug() << "boundary      " << an->boundary();
	//qDebug() << "revisions     " << an->revisions();
}
#endif

void PDFWidget::updateCursor(const QPoint &pos)
{
	if (document.isNull()) return;

	QPointF scaledPos;
	int pageNr;
	mapToScaledPosition(pos, pageNr, scaledPos);
	if (pageNr < 0 || pageNr >= realNumPages()) return;
	QScopedPointer<Poppler::Page> page(document->page(pageNr));
	if (!page)
		return;

	// check for link
	bool done = false;
	QList<Poppler::Link *> links = page->links();
	foreach (Poppler::Link *link, links) {
		// poppler's linkArea is relative to the page rect
		if (link->linkArea().contains(scaledPos)) {
			setCursor(Qt::PointingHandCursor);
			QString tooltip;
			if (link->linkType() == Poppler::Link::Browse) {
				const Poppler::LinkBrowse *browse = dynamic_cast<const Poppler::LinkBrowse *>(link);
				Q_ASSERT(browse != NULL);
				tooltip = browse->url();
			} else if (link->linkType() == Poppler::Link::Goto) {
				const Poppler::LinkGoto *go = dynamic_cast<const Poppler::LinkGoto *>(link);
				Q_ASSERT(UtilsUi::browse != NULL);
				if (go->isExternal()) {
					tooltip = go->fileName();
				}
			}
			if (!tooltip.isEmpty()) {
				QRect r = mapPopplerRectToWidget(link->linkArea(), page->pageSizeF());
				QToolTip::showText(mapToGlobal(pos), tooltip, this, r);
			}
			done = true;
			break;
		}
	}
	while (!links.isEmpty()) delete links.takeFirst();
	if (done) return;

	QList<Poppler::Annotation *> annotations = page->annotations();
	foreach (Poppler::Annotation *annot, annotations) {
		if (annot->boundary().contains(scaledPos)) {
			switch (annot->subType()) {
			case Poppler::Annotation::AMovie:
				setCursor(Qt::PointingHandCursor);
				break;
			case Poppler::Annotation::AText:
			case Poppler::Annotation::ACaret:
			case Poppler::Annotation::AHighlight: {
				setCursor(Qt::PointingHandCursor);
				QString text = QString("<b>%1</b><hr>%2").arg(annot->author(), annot->contents());
				QRect r = mapPopplerRectToWidget(annot->boundary(), page->pageSizeF());
				QToolTip::showText(mapToGlobal(pos), text, this, r);
				break;
			}
			default:
				;
			}
			done = true;
		}
	}
	while (!annotations.isEmpty()) delete annotations.takeFirst();
	if (done) return;

	updateCursor();
}

void PDFWidget::adjustSize()
{
	if (pages.empty()) return;
	QSize pageSize = (maxPageSizeFDpiAdjusted() * scaleFactor).toSize();
	pageSize.rwidth() = pageSize.rwidth() * gridx + (gridx - 1) * GridBorder;
	pageSize.rheight() = pageSize.rheight() * gridy + (gridy - 1) * GridBorder;
	if (pageSize != size()) {
		PDFScrollArea *scrollArea = getScrollArea();
		if (!scrollArea) return;
		qreal jumpTo = -1;

		QSize p = scrollArea->viewport()->size();

		if (scrollArea->getContinuous() && scrollArea->verticalScrollBar()->maximum() > 0) {
			jumpTo = 1.0 * scrollArea->verticalScrollBar()->value() / (scrollArea->verticalScrollBar()->maximum() + p.height());
		}
		resize(pageSize);
		if (jumpTo >= 0) {
			scrollArea->verticalScrollBar()->setValue(qRound(jumpTo * (scrollArea->verticalScrollBar()->maximum() + p.height()))); // correct position after resize
		}
	}
}

void PDFWidget::resetMagnifier()
{
	if (magnifier) {
		delete magnifier;
		magnifier = NULL;
	}
}

void PDFWidget::setResolution(int res)
{
	dpi = res;
	adjustSize();
	resetMagnifier();
}

void PDFWidget::setHighlightPath(const int page, const QPainterPath &path, const bool dontRemove)
{
	highlightRemover.stop();

	highlightPath = path;
	highlightPage = page;
	if (path.isEmpty()) return;


	PDFScrollArea *scrollArea = getScrollArea();
	if (scrollArea)
	    scrollArea->ensureVisiblePageAbsolutePos(page, highlightPath.boundingRect().center());
	if (globalConfig->highlightDuration > 0 && !dontRemove)
	    highlightRemover.start(globalConfig->highlightDuration);
}

double PDFWidget::totalScaleFactor() const
{
	return dpi / 72 * scaleFactor;
}

int PDFWidget::currentPageHistoryIndex() const
{
	return pageHistoryIndex;
}

const QList<PDFPageHistoryItem> PDFWidget::currentPageHistory() const
{
	return pageHistory;
}

int PDFWidget::getHighlightPage() const
{
	return highlightPage;
}

void PDFWidget::clearHighlight()
{
	highlightPath = QPainterPath();
	highlightPage = -1;
	update();
}

int PDFWidget::getPageIndex()
{
	return realPageIndex;
}

void PDFWidget::reloadPage(bool sync)
{
	QList<int> oldpages = pages;
	pages.clear();
	if (magnifier != NULL)
		magnifier->setPage(-1, 0, QRect());
	imagePage = -1;
	image = QPixmap();
	//highlightPath = QPainterPath();
	if (!document.isNull()) {
		if (realPageIndex >= realNumPages())
			realPageIndex = realNumPages() - 1;
		if (realPageIndex >= 0) {
			int visiblePageCount = qMin(gridx * gridy, realNumPages() - realPageIndex);
			for (int i = 0; i < visiblePageCount; i++)
				pages << i + realPageIndex;
			/*/use old pages if available ([a<=b], [c<=d] find [x<=y] with a <= x, c <= x, y <= b, y <= d)
			int firstCommonPage = qMax(pageIndex, oldPageIndex);
			int lastCommonPage = qMin(pageIndex + pageCount - 1, oldPageIndex + oldpages.size() - 1);

			if (lastCommonPage < firstCommonPage) {
				for (int i=0; i < pageCount; i++)
					pages.append(pageIndex + i);
			} else {
				for (int i=pageIndex; i < firstCommonPage; i++) pages.append(i);
				for (int i=firstCommonPage; i <= lastCommonPage; i++) pages.append(oldpages[i-oldPageIndex]);
				for (int i=lastCommonPage + 1; i < pageIndex + pageCount; i++) pages.append(i);
			}*/
			//oldPageIndex = pageIndex;
			oldRealPageIndex = realPageIndex;
		}
	}

	adjustSize();
	update();
	updateStatusBar();

	if (0 <= pageHistoryIndex && pageHistoryIndex < pageHistory.size() && pageHistory[pageHistoryIndex].page == realPageIndex ) ;
	else if (0 <= pageHistoryIndex - 1 && pageHistoryIndex - 1 < pageHistory.size() && pageHistory[pageHistoryIndex - 1].page == realPageIndex ) pageHistoryIndex--;
	else if (0 <= pageHistoryIndex + 1 && pageHistoryIndex + 1 < pageHistory.size() && pageHistory[pageHistoryIndex + 1].page == realPageIndex ) pageHistoryIndex++;
	else {
		while (pageHistory.size() > pageHistoryIndex + 1) pageHistory.removeLast();
		pageHistory.append(PDFPageHistoryItem(realPageIndex, 0, 0));
		while (pageHistory.size() > 50) pageHistory.removeFirst();
		pageHistoryIndex = pageHistory.size() - 1;
	}

	emit changedPage(realPageIndex, sync);
}

void PDFWidget::updateStatusBar()
{
	PDFDocument *doc = getPDFDocument();
	if (doc) {
		doc->showPage(realPageIndex + 1);
		doc->showScale(scaleFactor);
	}
#ifdef PHONON
	if (movie) movie->place();
#endif
}

void PDFWidget::updateCurrentPageHistoryOffset(){
	if (pageHistoryIndex < 0 || pageHistoryIndex >= pageHistory.size()) return;
	if (realPageIndex != pageHistory[pageHistoryIndex].page) return;
	QPointF out;
	int page;
	mapToScaledPosition(mapFromParent(QPoint()), page, out);
	if (page != realPageIndex) return;
	pageHistory[pageHistoryIndex].x = out.x();
	pageHistory[pageHistoryIndex].y = out.y();
}

PDFDocument *PDFWidget::getPDFDocument()
{
	if (pdfdocument)
		return pdfdocument;
	QWidget *widget = window();
	PDFDocument *doc = qobject_cast<PDFDocument *>(widget);
	return doc;
}

int PDFWidget::getPageOffset() const
{
	int pageOffset = (!singlePageStep) && (gridCols() == 2) ? 1 : 0;
	return pageOffset;
}

void PDFWidget::setGridSize(int gx, int gy, bool setAsDefault)
{
	if (gridx == gx && gridy == gy)
		return;
	gridx = gx;
	gridy = gy;
	if (setAsDefault)
		return;
	int pi = realPageIndex;
	getScrollArea()->goToPage(realPageIndex);
	if (pi == realPageIndex)
		reloadPage();
	//update();
}

int PDFWidget::visiblePages() const
{
	return pages.size();
}

int PDFWidget::pseudoNumPages()  const
{
	if (document.isNull()) return 0;
	int pageOffset = getPageOffset();
	return docPages + pageOffset;
	//return document->numPages();
}

int PDFWidget::realNumPages() const
{
	if (document.isNull()) return 0;
	return docPages;
}

int PDFWidget::pageStep()
{
	bool cont = getScrollArea()->getContinuous();
	int result = 1;
	if (singlePageStep && !cont) return 1;
	if (cont) {
		result = gridx;
	} else {
		if (!singlePageStep)
			result = gridx * gridy;
	}
	return result;
}

int PDFWidget::gridCols() const
{
	return gridx;
}

int PDFWidget::gridRowHeight() const
{
	return maxPageSizeF().height() * scaleFactor * dpi / 72.0 + GridBorder;
}

int PDFWidget::gridBorder() const
{
	return GridBorder;
}

void PDFWidget::setSinglePageStep(bool step)
{
	if (singlePageStep == step)
		return;
	singlePageStep = step;
	getScrollArea()->goToPage(realPageIndex);
	update();
}

void PDFWidget::goFirst()
{
	if (document.isNull()) return;
	getScrollArea()->goToPage(0);
}

void PDFWidget::goPrev()
{
	if (document.isNull()) return;
	getScrollArea()->goToPage(realPageIndex + getPageOffset() - pageStep());
}

void PDFWidget::goNext()
{
	if (document.isNull()) return;
	int pageOffset = getPageOffset();
	if (realPageIndex == 0 && pageOffset == 1)
		pageOffset = -1;
	getScrollArea()->goToPage(realPageIndex + pageOffset + pageStep());
}

void PDFWidget::goLast()
{
	if (document.isNull()) return;
	getScrollArea()->goToPage(realNumPages() - 1);
}

void PDFWidget::goForward()
{
	if (pageHistoryIndex + 1 < pageHistory.size()) {
		pageHistoryIndex++;
		REQUIRE(!document.isNull() && getScrollArea());
		goToPageRelativePosition(pageHistory[pageHistoryIndex].page, pageHistory[pageHistoryIndex].x, pageHistory[pageHistoryIndex].y);
	}
}

void PDFWidget::goBack()
{
	if (pageHistoryIndex > 0) {
		pageHistoryIndex--;
		REQUIRE(!document.isNull() && getScrollArea());
		goToPageRelativePosition(pageHistory[pageHistoryIndex].page, pageHistory[pageHistoryIndex].x, pageHistory[pageHistoryIndex].y);
	}
}

void PDFWidget::upOrPrev()
{
	if (document.isNull()) return;
	QScrollBar		*scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepSub);
	else {
		if (realPageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	shortcutUp->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
}

void PDFWidget::leftOrPrev()
{
	if (document.isNull()) return;
	QScrollBar		*scrollBar = getScrollArea()->horizontalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepSub);
	else {
		if (realPageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	shortcutLeft->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
}

void PDFWidget::pageUpOrPrev()
{
	if (document.isNull()) return;
	QScrollBar *scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderPageStepSub);
	else {
		if (realPageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	//shortcutPageUp->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
}

void PDFWidget::downOrNext()
{
	if (document.isNull()) return;
	QScrollBar		*scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
	else {
		if (realPageIndex < realNumPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	shortcutDown->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
}

void PDFWidget::rightOrNext()
{
	if (document.isNull()) return;
	QScrollBar		*scrollBar = getScrollArea()->horizontalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
	else {
		if (realPageIndex < realNumPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	shortcutRight->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
}

void PDFWidget::pageDownOrNext()
{
	if (document.isNull()) return;
	QScrollBar		*scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderPageStepAdd);
	else {
		if (realPageIndex < realNumPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	//shortcutPageDown->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
}

void PDFWidget::doPageDialog()
{
	if (document.isNull()) return;
	bool ok;
	setCursor(Qt::ArrowCursor);
	int pageNo = QInputDialog::getInt(this, tr("Go to Page"),
	                                  tr("Page number:"), realPageIndex + 1,
	                                  1, realNumPages(), 1, &ok);
	if (ok)
		getScrollArea()->goToPage(pageNo - 1);
}

int PDFWidget::normalizedPageIndex(int p)
{
	if (p > 0) return  p - (p - getPageOffset())  % pageStep();
	else return p;
}

void PDFWidget::goToPageDirect(int p, bool sync)
{
	if (p < 0) p = 0;
	if (p >= realNumPages()) p = realNumPages() - 1;
	p = normalizedPageIndex(p);
	if (p != realPageIndex && !document.isNull()) { //the first condition is important: it prevents a recursive sync crash
		if (p >= 0 && p < realNumPages()) {
			realPageIndex = p;
			reloadPage(sync);
			update();
		}
	}
}

void PDFWidget::fixedScale(qreal scale)
{
	scaleOption = kFixedMag;
	if (scaleFactor != scale) {
		scaleFactor = scale;
		adjustSize();
		update();
		updateStatusBar();
		emit changedZoom(scaleFactor);
	}
	emit changedScaleOption(scaleOption);
}

void PDFWidget::fitWidth(bool checked)
{
	if (checked) {
		scaleOption = kFitWidth;
		QAbstractScrollArea	*scrollArea = getScrollArea();
		if (scrollArea && !pages.isEmpty()) {
			qreal portWidth = scrollArea->viewport()->width() - gridBorder() * (gridx - 1);
			QSizeF	pageSize = maxPageSizeFDpiAdjusted() * gridx;
			scaleFactor = portWidth / pageSize.width();
			if (scaleFactor < kMinScaleFactor)
				scaleFactor = kMinScaleFactor;
			else if (scaleFactor > kMaxScaleFactor)
				scaleFactor = kMaxScaleFactor;
			adjustSize();
			update();
			updateStatusBar();
			emit changedZoom(scaleFactor);
		}
	} else
		scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);
}

void PDFWidget::fitTextWidth(bool checked)
{
	if (checked) {
		scaleOption = kFitTextWidth;
		QAbstractScrollArea	*scrollArea = getScrollArea();
		if (scrollArea && !pages.isEmpty()) {
			int margin = 8;
			qreal portWidth = scrollArea->viewport()->width() - GridBorder * (gridx - 1);

			QRectF textRect = horizontalTextRangeF();
			if (!textRect.isValid()) return;
			qreal targetWidth = maxPageSizeFDpiAdjusted().width() * (gridx - 1) + textRect.width() * dpi / 72.0;
			//qreal targetWidth = textRect.width() * dpi / 72.0;
			// total with of all pages in the grid - textMargin of a single page
			// for a 1x grid, targetWith is the same as textRect.width()
			scaleFactor = portWidth / ((targetWidth ) + 2 * margin);
			if (scaleFactor < kMinScaleFactor)
				scaleFactor = kMinScaleFactor;
			else if (scaleFactor > kMaxScaleFactor)
				scaleFactor = kMaxScaleFactor;
			adjustSize();
			scrollArea->horizontalScrollBar()->setValue((qRound(textRect.left() * dpi / 72.0) - margin) *scaleFactor);
			update();
			updateStatusBar();
			emit changedZoom(scaleFactor);
		}
	} else
		scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);
}

void PDFWidget::fitWindow(bool checked)
{
	if (checked) {
		scaleOption = kFitWindow;
		PDFScrollArea	*scrollArea = getScrollArea();
		if (scrollArea && !pages.isEmpty()) {
			qreal portWidth = scrollArea->viewport()->width() - GridBorder * (gridx - 1);
			qreal portHeight = scrollArea->viewport()->height() - GridBorder * (gridy - 1);
			QSizeF	pageSize = maxPageSizeFDpiAdjusted();
			qreal sfh = portWidth / pageSize.width();
			qreal sfv = portHeight / pageSize.height();
			scaleFactor = sfh < sfv ? sfh : sfv;
			if (scaleFactor < kMinScaleFactor)
				scaleFactor = kMinScaleFactor;
			else if (scaleFactor > kMaxScaleFactor)
				scaleFactor = kMaxScaleFactor;
			adjustSize();
			update();
			updateStatusBar();
			emit changedZoom(scaleFactor);
		}
	} else
		scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);
}

void PDFWidget::doZoom(const QPoint &clickPos, int dir, qreal newScaleFactor) // dir = 1 for in, -1 for out, 0 to use newScaleFactor
{
	QPointF pagePos(clickPos.x() / scaleFactor * 72.0 / dpi,
	                clickPos.y() / scaleFactor * 72.0 / dpi);
	scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);

	double zoomStepFactor = globalConfig->zoomStepFactor;
	if (zoomStepFactor > 10) zoomStepFactor = 10;
	if (zoomStepFactor < 1.001) zoomStepFactor = 1.001;


	QPoint globalPos = mapToGlobal(clickPos);
	if (dir > 0 && scaleFactor < kMaxScaleFactor) {
		scaleFactor *= zoomStepFactor;
		if (qFabs(scaleFactor - qRound(scaleFactor)) < 0.01)
			scaleFactor = qRound(scaleFactor);
		if (scaleFactor > kMaxScaleFactor)
			scaleFactor = kMaxScaleFactor;
	} else if (dir < 0 && scaleFactor > kMinScaleFactor) {
		scaleFactor /= zoomStepFactor;
		if (qFabs(scaleFactor - qRound(scaleFactor)) < 0.01)
			scaleFactor = qRound(scaleFactor);
		if (scaleFactor < kMinScaleFactor)
			scaleFactor = kMinScaleFactor;
	} else if (dir == 0) {
		if (newScaleFactor < kMinScaleFactor) {
			newScaleFactor = kMinScaleFactor;
		} else if (newScaleFactor > kMaxScaleFactor) {
			newScaleFactor = kMaxScaleFactor;
		}
		if (newScaleFactor == scaleFactor) {
			return;
		}
		scaleFactor = newScaleFactor;
	}

	adjustSize();
	update();
	updateStatusBar();
	emit changedZoom(scaleFactor);
	QPoint localPos = mapFromGlobal(globalPos);
	QPoint pageToLocal(int(pagePos.x() * scaleFactor / 72.0 * dpi),
	                   int(pagePos.y() * scaleFactor / 72.0 * dpi));
	QAbstractScrollArea	*scrollArea = getScrollArea();
	if (scrollArea) {
		QScrollBar *hs = scrollArea->horizontalScrollBar();
		if (hs != NULL)
			hs->setValue(hs->value() + pageToLocal.x() - localPos.x());
		QScrollBar *vs = scrollArea->verticalScrollBar();
		if (vs != NULL)
			vs->setValue(vs->value() + pageToLocal.y() - localPos.y());
	}
}

void PDFWidget::zoomIn()
{
	QWidget *parent = parentWidget();
	if (parent != NULL) {
		QPoint ctr = mapFromParent(QPoint(parent->width() / 2, parent->height() / 2));
		doZoom(ctr, 1);
	}
}

void PDFWidget::zoomOut()
{
	QWidget *parent = parentWidget();
	if (parent != NULL) {
		QPoint ctr = mapFromParent(QPoint(parent->width() / 2, parent->height() / 2));
		doZoom(ctr, -1);
	}
}

void PDFWidget::zoom(qreal scale)
{
	QWidget *parent = parentWidget();
	if (parent != NULL) {
		QPoint ctr = mapFromParent(QPoint(parent->width() / 2, parent->height() / 2));
		doZoom(ctr, 0, scale);
	}
}

//TODO: optimize?
QRect PDFWidget::gridPageRect(int pageIndex) const
{
	if (gridx * gridy <= 1)
		return rect();

	QSizeF realPageSize = maxPageSizeFDpiAdjusted() * scaleFactor;

	int realPageSizeX = qRound(realPageSize.width());
	int realPageSizeY = qRound(realPageSize.height());

	QPoint p((realPageSizeX + GridBorder) * (pageIndex % gridx), (realPageSizeY + GridBorder) * (pageIndex / gridx));
	return QRect(p, QPoint(p.x() + realPageSizeX, p.y() + realPageSizeY));
}

QPoint PDFWidget::gridPagePosition(int pageIndex) const
{
	return gridPageRect(pageIndex).topLeft();
}

int PDFWidget::gridPageIndex(const QPoint &position) const
{
	if (pages.size() == 0) return -1;
	if (gridx * gridy == 1) return 0;
	for (int i = 0; i < gridx * gridy; i++)
		if (gridPageRect(i).contains(position))
			return i;
	return -1;
}

void PDFWidget::mapToScaledPosition(const QPoint &position, int &page, QPointF &scaledPos) const
{
	if (document.isNull()) return;
	page = pageFromPos(position);
	QRect r = pageRect(page);
	if (r.isNull()) return;
	// poppler's pos is relative to the page rect
	QPoint temp = position - r.topLeft();
	scaledPos.setX(temp.x() * 1.0 / r.width());
	scaledPos.setY(temp.y() * 1.0 / r.height());
}

QPoint PDFWidget::mapFromScaledPosition(int page, const QPointF &scaledPos) const
{
	if (document.isNull() || pages.size() == 0) return QPoint();
	QRect r = pageRect(page);
	if (r.isNull()) return QPoint();
	return r.topLeft() + QPoint( scaledPos.x() * r.width(), scaledPos.y() * r.height() );
	/*	if (rpage < 0 || rpage >= realNumPages()) return QPoint();
		QPoint p = pageRect(rpage).topLeft();
		Poppler::Page *popplerPage=document->page(rpage);
		if(!popplerPage)
			return QPoint();
		int w=popplerPage->pageSizeF().width();
		int h=popplerPage->pageSizeF().height();
		delete popplerPage;
		return (QPointF(scaledPos.x() * w, scaledPos.y() * h)   * scaleFactor * dpi / 72.0 ).toPoint() + p;*/
}

int PDFWidget::pageFromPos(const QPoint &pos) const
{
	int page = gridPageIndex(pos) + realPageIndex;
	if (realPageIndex == 0) page -= getPageOffset();
	if (pageRect(page).contains(pos)) return page;
	else return -1;
}

QRect PDFWidget::pageRect(int page) const
{
	if (document.isNull())
		return QRect();
	if (page < pages.first() || page > pages.last())
		return QRect();
	QRect grect;
	if (realPageIndex == 0) grect = gridPageRect(page + getPageOffset());
	else grect = gridPageRect(page - realPageIndex);
	QScopedPointer<Poppler::Page> popplerPage(document->page(page));
	if (!popplerPage)
		return grect;
	int realSizeW =  dpi * scaleFactor / 72.0 * popplerPage->pageSizeF().width();
	int realSizeH =  dpi * scaleFactor / 72.0 * popplerPage->pageSizeF().height();
	int xOffset = (grect.width() - realSizeW) / 2;
	int yOffset = (grect.height() - realSizeH) / 2;
	if (gridx == 2 && getPageOffset() == 1) {
		if (page & 1) xOffset *= 2;
		else xOffset = 0;
	}
	return QRect(grect.left() + xOffset, grect.top() + yOffset, realSizeW, realSizeH);
}

QSizeF PDFWidget::maxPageSizeF() const
{
	if (document.isNull()) return QSizeF();
	//QSizeF maxPageSize;
	//foreach (int page, pages) {
	if (!maxPageSize.isValid()) {
		for (int page = 0; page < docPages; page++) {
			//if (page < 0 || page >= numPages()) continue;
			QScopedPointer<Poppler::Page> popplerPage(document->page(page));
			if (!popplerPage) break;
			if (popplerPage->pageSizeF().width() > maxPageSize.width()) maxPageSize.setWidth(popplerPage->pageSizeF().width());
			if (popplerPage->pageSizeF().height() > maxPageSize.height()) maxPageSize.setHeight(popplerPage->pageSizeF().height());
		}
	}
	return maxPageSize;
}

QSizeF PDFWidget::maxPageSizeFDpiAdjusted() const
{
	return maxPageSizeF() * dpi / 72.0;
}

// calculates the maximal horizontal text range (xmin, xmax) over the total document.
// Note: this may be slow on large documents because each TextBox (~word) is analyzed.
// Therefore the value is cached.
// TODO: Replace TextBoxes with the ArtBox of the page once this becomes available via the poppler-qt interface.
// Only the horizontal values of the returned QRectF have meaning.
QRectF PDFWidget::horizontalTextRangeF()
{
	REQUIRE_RET(document && pdfdocument, QRectF());

	qreal textXmin = +1.e99;
	qreal textXmax = -1.e99;
	if (!horizontalTextRange.isValid()) {
		// horitontalTextRangeF() may be called concurrently, in particular during startup
		// see e.g. https://sourceforge.net/p/texstudio/bugs/1292/
		// The crash therein is probably caused by a simultaneous access to poppler, so one
		// could limit the access there. However, since textWidth calculation is currently
		// quite expensive, we do not want to do it multiple times. I assume that the call
		// which locks the calculation will finally lead to an update of the displayed width.
		// This justifies to discard all width requests in between.
		if (!textwidthCalculationMutex.tryLock()) {
			return QRectF();
		}
		QProgressDialog progress(tr("Calculating text width"), tr("Cancel"), 0, docPages);
		progress.setWindowModality(Qt::WindowModal);
		progress.setMinimumDuration(500);

		for (int page = 0; page < docPages; page++) {
			progress.setValue(page); //this is like the fire nation
			if (horizontalTextRange.isValid()) return horizontalTextRange;
			if (progress.wasCanceled() || !document || !pdfdocument) break;
			Poppler::Page *popplerPage = document->page(page);

			if (!popplerPage) break;
			foreach (Poppler::TextBox *textbox, popplerPage->textList()) {
				QRectF bb = textbox->boundingBox();
				if (textXmin > bb.left()) textXmin = bb.left();
				if (textXmax < bb.right()) textXmax = bb.right();
				delete textbox;
			}
			delete popplerPage;
		}
		if (textXmax > textXmin) {
			horizontalTextRange = QRectF(textXmin, 0, textXmax - textXmin, 1);
		}
		textwidthCalculationMutex.unlock();
	}
	return horizontalTextRange;
}


void PDFWidget::saveState()
{
	saveScaleFactor = scaleFactor;
	saveScaleOption = scaleOption;
}

void PDFWidget::restoreState()
{
	if (scaleFactor != saveScaleFactor) {
		scaleFactor = saveScaleFactor;
		adjustSize();
		update();
		updateStatusBar();
		emit changedZoom(scaleFactor);
	}
	scaleOption = saveScaleOption;
	emit changedScaleOption(scaleOption);
}

PDFScrollArea *PDFWidget::getScrollArea()
{
	QWidget *parent = parentWidget();
	if (parent != NULL)
		return qobject_cast<PDFScrollArea *>(parent->parentWidget());
	else
		return NULL;
}


//#pragma mark === PDFDocument ===

QList<PDFDocument *> PDFDocument::docList;

PDFDocument::PDFDocument(PDFDocumentConfig *const pdfConfig, bool embedded)
    : renderManager(0), curFileSize(0), menubar(NULL), exitFullscreen(0), watcher(NULL), reloadTimer(NULL), dwClock(0), dwOutline(0), dwFonts(0), dwInfo(0), dwOverview(0), dwSearch(0),
      syncFromSourceBlocked(false), syncToSourceBlocked(false)
{
	REQUIRE(pdfConfig);
	Q_ASSERT(!globalConfig || (globalConfig == pdfConfig));
	globalConfig = pdfConfig;

	embeddedMode = embedded;
	init(embedded);


	watcher = new QFileSystemWatcher(this);
	connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(reloadWhenIdle()));

	if (!embedded) {
		int &x = globalConfig->windowLeft;
		int &y = globalConfig->windowTop;
		int &w = globalConfig->windowWidth;
		int &h = globalConfig->windowHeight;
		int screenNumber = QApplication::desktop()->screenNumber(QPoint(x, y));
		QRect screen = QApplication::desktop()->availableGeometry(screenNumber);
		// add some tolerance, as fullscreen seems to have negative coordinate (KDE, Win7 ...)
		screen.adjust(-8, -8, +8, +8);
		if (!screen.contains(x, y)) {
			// top left is not on screen
			x = screen.x() + screen.width() * 2 / 3;
			y = screen.y() + 10;
			if (x + w > screen.right()) w = screen.width() / 3 - 26;
			if (y + h > screen.height()) h = screen.height() - 100;
		}
		if (globalConfig->windowMaximized)
			showMaximized();
		else
			setWindowState(Qt::WindowNoState);

		resize(w, h); //important to first resize then move
		move(x, y);
		if (!globalConfig->windowState.isEmpty()) restoreState(globalConfig->windowState);
		toolBar->setVisible(globalConfig->toolbarVisible);
		statusbar->setVisible(true);
	}
	if (embeddedMode && globalConfig->autoHideToolbars) {
		setAutoHideToolbars(true);
	}

	//batch test:
	/*QString test = QProcessEnvironment::systemEnvironment().value("TEST");
	if (!test.isEmpty())
	for (int i=test.toInt();i<13960;i++) {
		qDebug() << ("/tmp/test"+QString::number(i)+".pdf");
		//Poppler::Document* doc = Poppler::Document::load("/tmp/test"+QString::number(i)+".pdf");
		QFile f("/tmp/test"+QString::number(i)+".pdf");
		if (!f.open(QFile::ReadOnly)) qDebug() << "file open failed";
		Poppler::Document* doc = Poppler::Document::loadFromData(f.readAll());

		if (doc) {
		qDebug() << " => "<<doc->numPages();
		if (doc->numPages() > 0) {
			Poppler::Page *p = doc->page(0);
			qDebug() << p;
			if (p) delete p;
		}
		delete doc;
		}

	}*/
}

PDFDocument::~PDFDocument()
{
	globalConfig->windowMaximized = isMaximized();

    ConfigManager *configManager=dynamic_cast<ConfigManager *>(ConfigManager::getInstance());

#if (QT_VERSION > 0x050000) && (QT_VERSION <= 0x050700) && (defined(Q_OS_MAC))
    QList<QKeySequence> keys=configManager->specialShortcuts.keys();
    foreach(QKeySequence key,keys){
	QList<QAction *>acts=configManager->specialShortcuts.values(key);
	foreach(QAction *act,acts){
	    if(act->objectName().startsWith("pdf")){
		configManager->specialShortcuts.remove(key,act);
	    }
	}
    }
#endif

    configManager->menuParents.removeAll(menuroot);
    foreach (QMenu *menu, menus) {
        configManager->managedMenus.removeAll(menu);
    }

	docList.removeAll(this);
	emit documentClosed();
	if (renderManager)
		delete renderManager;

    delete menubar;
}

void PDFDocument::setupToolBar(){
    toolBar = new QToolBar(this);
    toolBar->setWindowTitle(tr("Toolbar"));
    toolBar->setObjectName(QString("toolBar"));
    toolBar->setIconSize(QSize(24, 24));
    addToolBar(Qt::TopToolBarArea, toolBar);
    toolBarTimer = new QTimer(this);
    toolBarTimer->setSingleShot(true);
    connect(toolBarTimer, SIGNAL(timeout()), this, SLOT(showToolbars()));

    toolBar->addAction(actionTypeset);
    toolBar->addSeparator();
    toolBar->addAction(actionExternalViewer);
    toolBar->addSeparator();
    toolBar->addAction(actionMagnify);
    toolBar->addAction(actionScroll);
    toolBar->addSeparator();
    toolBar->addAction(actionBack);
    toolBar->addAction(actionForward);
    toolBar->addSeparator();
    toolBar->addAction(actionFirst_Page);
    toolBar->addAction(actionPrevious_Page);
    toolBar->addAction(actionNext_Page);
    toolBar->addAction(actionLast_Page);
    toolBar->addSeparator();
    toolBar->addAction(actionActual_Size);
    toolBar->addAction(actionFit_to_Width);
    toolBar->addAction(actionFit_to_Text_Width);
    toolBar->addAction(actionFit_to_Window);
    toolBar->addSeparator();
	toolBar->addAction(actionAutoHideToolbars);
    toolBar->addAction(actionEnlargeViewer);
    toolBar->addAction(actionShrinkViewer);
    toolBar->addAction(actionToggleEmbedded);
    toolBar->addAction(actionClose);

    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString("statusbar"));
    setStatusBar(statusbar);
}

void PDFDocument::setupMenus(bool embedded)
{
    ConfigManager *configManager=dynamic_cast<ConfigManager *>(ConfigManager::getInstance());
    menuroot=new QMenu(this);

    menubar = new QMenuBar(0);
	menubar->setObjectName(QString::fromUtf8("menubar"));
	menubar->setGeometry(QRect(0, 0, 1197, 21));



    menuFile=configManager->newManagedMenu(menuroot,menubar,"pdf/file",QApplication::translate("PDFDocument", "&File"));
    menuEdit_2=configManager->newManagedMenu(menuroot,menubar,"pdf/edit",QApplication::translate("PDFDocument", "&Edit"));
    menuView=configManager->newManagedMenu(menuroot,menubar,"pdf/view",QApplication::translate("PDFDocument", "&View"));
    menuGrid=configManager->newManagedMenu(menuView,NULL,"pdf/view/grid",QApplication::translate("PDFDocument", "Grid"));
    menuWindow=configManager->newManagedMenu(menuroot,menubar,"pdf/window",QApplication::translate("PDFDocument", "&Window"));
    menuEdit=configManager->newManagedMenu(menuroot,menubar,"pdf/config",QApplication::translate("PDFDocument", "&Configure"));
    menuHelp=configManager->newManagedMenu(menuroot,menubar,"pdf/help",QApplication::translate("PDFDocument", "&Help"));
    menus<<menuFile<<menuEdit<<menuEdit_2<<menuGrid<<menuHelp<<menuWindow<<menuView; // housekeeping for later removal

    if(!embedded)
        setMenuBar(menubar);

    actionUserManual=configManager->newManagedAction(menuroot,menuHelp, "help", tr("User &Manual..."), this,SIGNAL(triggeredManual()), QList<QKeySequence>());
	menuHelp->addSeparator();

    configManager->newManagedAction(menuroot,menuHelp, "about", tr("About"), this,SIGNAL(triggeredAbout()), QList<QKeySequence>() << Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_A);
    configManager->newManagedAction(menuroot,menuFile, "open", tr("&Open..."), this,SLOT(fileOpen()), QList<QKeySequence>(),"document-open" );
    configManager->newManagedAction(menuroot,menuFile, "split", tr("Split && Merge..."), this,SLOT(splitMergeTool()), QList<QKeySequence>() );
    actionClose=configManager->newManagedAction(menuroot,menuFile, "close", tr("&Close"), this,SLOT(close()), QList<QKeySequence>()<< Qt::CTRL + Qt::Key_W ,"close");
	menuFile->addSeparator();
    configManager->newManagedAction(menuroot,menuFile, "quit", tr("&Quit TeXstudio"), this,SIGNAL(triggeredQuit()), QList<QKeySequence>());
    actionPreferences=configManager->newManagedAction(menuroot,menuEdit, "preferences", tr("&Configure TeXstudio"), this, SIGNAL(triggeredConfigure()), QList<QKeySequence>());
	menuEdit->addSeparator();
    actionScrolling_follows_cursor=configManager->newManagedAction(menuroot,menuEdit, "followCursor", tr("Scrolling follows cursor"), this, "", QList<QKeySequence>());
    actionScrolling_follows_cursor->setCheckable(true);
    actionCursor_follows_scrolling=configManager->newManagedAction(menuroot,menuEdit, "followScroll", tr("Cursor follows scrolling"), this, "", QList<QKeySequence>());
    actionCursor_follows_scrolling->setCheckable(true);
    actionSynchronize_multiple_views=configManager->newManagedAction(menuroot,menuEdit, "syncViews", tr("Synchronize multiple views"), this, "", QList<QKeySequence>());
    actionSynchronize_multiple_views->setCheckable(true);
	menuEdit->addSeparator();
    actionInvertColors=configManager->newManagedAction(menuroot,menuEdit, "invertColors", tr("Invert Colors"), pdfWidget, SLOT(update()), QList<QKeySequence>());
    actionInvertColors->setCheckable(true);
    actionGrayscale=configManager->newManagedAction(menuroot,menuEdit, "grayscale", tr("Grayscale"), pdfWidget, SLOT(update()), QList<QKeySequence>());
    actionGrayscale->setCheckable(true);

    actionMagnify=configManager->newManagedAction(menuroot,menuView, "magnify", tr("&Magnify"), this, "", QList<QKeySequence>(),"magnifier-button");
    actionScroll=configManager->newManagedAction(menuroot,menuView, "scroll", tr("&Scroll"), this, "", QList<QKeySequence>(),"hand");
    menuView->addSeparator();
    actionFirst_Page=configManager->newManagedAction(menuroot,menuView, "firstPage", tr("&First Page"), pdfWidget, SLOT(goFirst()), QList<QKeySequence>()<<Qt::Key_Home,"go-first");
    actionBack=configManager->newManagedAction(menuroot,menuView, "back", tr("Back"), pdfWidget, SLOT(goBack()), QList<QKeySequence>()<< Qt::AltModifier + Qt::Key_L,"back");
    actionPrevious_Page=configManager->newManagedAction(menuroot,menuView, "previous", tr("&Previous Page"), pdfWidget, SLOT(goPrev()), QList<QKeySequence>(),"go-previous");
    actionNext_Page=configManager->newManagedAction(menuroot,menuView, "next", tr("&Next Page"), pdfWidget, SLOT(goNext()), QList<QKeySequence>(),"go-next");
    actionForward=configManager->newManagedAction(menuroot,menuView, "forward", tr("Forward"), pdfWidget, SLOT(goForward()), QList<QKeySequence>()<< Qt::AltModifier + Qt::Key_R,"forward");
    actionLast_Page=configManager->newManagedAction(menuroot,menuView, "last", tr("&Last Page"), pdfWidget, SLOT(goLast()), QList<QKeySequence>()<< Qt::Key_End,"go-last");
	menuView->addSeparator();
    actionGo_to_Page=configManager->newManagedAction(menuroot,menuView, "goto", tr("&Go to Page..."), pdfWidget, SLOT(doPageDialog()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_J);
	menuView->addSeparator();
    actionZoom_In=configManager->newManagedAction(menuroot,menuView, "zoomIn", tr("Zoom &In"), pdfWidget, SLOT(zoomIn()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_Plus,"zoom-in");
    actionZoom_Out=configManager->newManagedAction(menuroot,menuView, "zoomOut", tr("Zoom &Out"), pdfWidget, SLOT(zoomOut()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_Minus,"zoom-out");
    actionActual_Size=configManager->newManagedAction(menuroot,menuView, "actualSize", tr("&Actual Size"), pdfWidget, SLOT(fixedScale()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_1,"zoom-original");
    actionFit_to_Width=configManager->newManagedAction(menuroot,menuView, "fitToWidth", tr("Fit to Wi&dth"), this, "", QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_2,"zoom-fit-width");
    actionFit_to_Width->setCheckable(true);
    actionFit_to_Text_Width=configManager->newManagedAction(menuroot,menuView, "fitToTextWidth", tr("Fit to &Text Width"), this, "", QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_4,"zoom-fit-text-width");
    actionFit_to_Text_Width->setCheckable(true);
    actionFit_to_Window=configManager->newManagedAction(menuroot,menuView, "fitToWindow", tr("Fit to &Window"), this, "", QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_3,"zoom-fit-best");
    actionFit_to_Window->setCheckable(true);
    actionContinuous=configManager->newManagedAction(menuroot,menuView, "continuous", tr("&Continuous"), this, "", QList<QKeySequence>());
    actionContinuous->setCheckable(true);
    actionContinuous->setChecked(true);
	menuView->addAction(menuGrid->menuAction());
	menuView->addSeparator();
    actionFull_Screen=configManager->newManagedAction(menuroot,menuView, "fullscreen", tr("Full &Screen"), this, SLOT(toggleFullScreen(bool)), QList<QKeySequence>()<<Qt::ControlModifier+Qt::ShiftModifier+Qt::Key_F);
    actionPresentation=configManager->newManagedAction(menuroot,menuView, "presentation", tr("Presentation"), this, SLOT(toggleFullScreen(bool)), QList<QKeySequence>()<<Qt::Key_F5);
    actionExternalViewer=configManager->newManagedAction(menuroot,menuView, "external", tr("External Viewer"), this, SLOT(runExternalViewer()), QList<QKeySequence>()<<QKeySequence("CTRL+ALT+X"),"acroread");
    actionEnlargeViewer=configManager->newManagedAction(menuroot,menuView, "enlarge", tr("Enlarge Viewer"), this, SLOT(enlarge()), QList<QKeySequence>(),"enlarge-viewer");
    actionShrinkViewer=configManager->newManagedAction(menuroot,menuView, "shrink", tr("Shrink Viewer"), this, SLOT(shrink()), QList<QKeySequence>(),"shrink-viewer");
    actionToggleEmbedded=configManager->newManagedAction(menuroot,menuView, "toggle", tr("Windowed/Embedded"), this, SLOT(toggleEmbedded()), QList<QKeySequence>());
	actionAutoHideToolbars=configManager->newManagedAction(menuroot,menuView, "autoHideToolbar", tr("Auto-hide Toolbar"), this, SLOT(toggleAutoHideToolbars()), QList<QKeySequence>(),"hide-toolbars");
	actionAutoHideToolbars->setCheckable(true);
	actionAutoHideToolbars->setChecked(globalConfig->autoHideToolbars);

    /*actionGrid11=configManager->newManagedAction(menuroot,menuGrid, "grid11", tr("1x1"), this, SLOT(setGrid()), QList<QKeySequence>());
    actionGrid11->setProperty("grid","1x1");
    actionGrid21=configManager->newManagedAction(menuroot,menuGrid, "grid21", tr("2x1"), this, SLOT(setGrid()), QList<QKeySequence>());
    actionGrid21->setProperty("grid","2x1");
    actionGrid12=configManager->newManagedAction(menuroot,menuGrid, "grid12", tr("1x2"), this, SLOT(setGrid()), QList<QKeySequence>());
    actionGrid12->setProperty("grid","1x2");
    actionGrid22=configManager->newManagedAction(menuroot,menuGrid, "grid22", tr("2x2"), this, SLOT(setGrid()), QList<QKeySequence>());
    actionGrid22->setProperty("grid","2x2");*/
    static QStringList sl;
    configManager->registerOption("Preview/Possible Grid Sizes", &sl, QStringList() << "1x1" << "2x1" << "1x2" << "2x2" << "3x1" << "3x2" << "3x3");
    foreach (const QString &gs, sl) {
        QAction *a = configManager->newManagedAction(menuroot,menuGrid, "grid"+gs, gs, this, SLOT(setGrid()), QList<QKeySequence>());
        a->setProperty("grid", gs);
    }
    actionCustom=configManager->newManagedAction(menuroot,menuGrid, "gridCustom", tr("Custom..."), this, SLOT(setGrid()), QList<QKeySequence>());
    actionCustom->setProperty("grid","xx");
	menuGrid->addSeparator();
    actionSinglePageStep=configManager->newManagedAction(menuroot,menuGrid, "singlePageStep", tr("Single Page Step"), pdfWidget, SLOT(setSinglePageStep(bool)), QList<QKeySequence>());
	menuWindow->addAction(menuShow->menuAction());
    actionCloseElement=configManager->newManagedAction(menuroot,menuWindow, "closeElement", tr("&Close something"), this, SLOT(closeElement()), QList<QKeySequence>()<<Qt::Key_Escape);
	menuWindow->addSeparator();
    actionSide_by_Side=configManager->newManagedAction(menuroot,menuWindow, "stack", tr("Stac&k"), this, SLOT(stackWindows()), QList<QKeySequence>());
    actionTile=configManager->newManagedAction(menuroot,menuWindow, "tile", tr("&Tile"), this, SLOT(tileWindows()), QList<QKeySequence>());
    actionSide_by_Side=configManager->newManagedAction(menuroot,menuWindow, "sideBySide", tr("&Side by Side"), this, SLOT(sideBySide()), QList<QKeySequence>());
	menuWindow->addSeparator();
    actionGo_to_Source=configManager->newManagedAction(menuroot,menuWindow, "gotoSource", tr("&Go to Source"), this, SLOT(goToSource()), QList<QKeySequence>()<<Qt::ControlModifier+Qt::Key_Apostrophe);
    actionFocus_Editor=configManager->newManagedAction(menuroot,menuWindow, "focusEditor", tr("Focus Editor"), this, SIGNAL(focusEditor()), QList<QKeySequence>()<<Qt::ControlModifier+Qt::AltModifier+Qt::Key_Left);
	menuWindow->addSeparator();
    actionNew_Window=configManager->newManagedAction(menuroot,menuWindow, "newWindow", tr("New Window"), this, SIGNAL(triggeredClone()), QList<QKeySequence>());
    actionFind=configManager->newManagedAction(menuroot,menuEdit_2, "find", tr("&Find"), this, SLOT(doFindDialog()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_F);
    actionFind_Again=configManager->newManagedAction(menuroot,menuEdit_2, "findAgain", tr("Find &again"), this, SLOT(doFindAgain()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_M<< Qt::Key_F3);
    menuEdit_2->addSeparator();
    actionTypeset=configManager->newManagedAction(menuroot,menuEdit_2, "build", tr("Quick Build"), this, SLOT(runQuickBuild()), QList<QKeySequence>()<< Qt::ControlModifier + Qt::Key_T,"build");

    configManager->modifyManagedShortcuts("pdf");
}

// the shortcuts will only be triggered if this widget has focus (used in embedded mode)
void PDFDocument::shortcutOnlyIfFocused(const QList<QAction *> &actions)
{
	foreach (QAction *act, actions) {
		act->setParent(this);
		act->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	}
}

void PDFDocument::reloadSettings()
{
	if (embeddedMode) setAutoHideToolbars(globalConfig->autoHideToolbars);
}

void PDFDocument::init(bool embedded)
{
	ConfigManagerInterface *conf = ConfigManagerInterface::getInstance();

	docList.append(this);

    //setupUi(this);

	menuShow = new QMenu(this);
	menuShow->setObjectName(QString::fromUtf8("menuShow"));
	menuShow->setTitle(QApplication::translate("PDFDocument", "Show"));

    pdfWidget = new PDFWidget(embedded); // needs to be initialized before setup menu
    pdfWidget->setPDFDocument(this);

    //if (!embedded)
    setupMenus(embedded);

    setupToolBar();


	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_MacNoClickThrough, true);

	//load icons
	setWindowIcon(QIcon(":/images/previewicon.png"));

    //actionBack->setIcon(getRealIcon("back"));
    //actionForward->setIcon(getRealIcon("forward"));
    //actionFirst_Page->setIcon(getRealIcon("go-first"));
    //actionPrevious_Page->setIcon(getRealIcon("go-previous"));
    //actionNext_Page->setIcon(getRealIcon("go-next"));
    //actionLast_Page->setIcon(getRealIcon("go-last"));
    //actionZoom_In->setIcon(getRealIcon("zoom-in"));
    //actionZoom_Out->setIcon(getRealIcon("zoom-out"));
    //actionFit_to_Window->setIcon(getRealIcon("zoom-fit-best"));
    //actionActual_Size->setIcon(getRealIcon("zoom-original"));
    //actionFit_to_Width->setIcon(getRealIcon("zoom-fit-width"));
    //actionFit_to_Text_Width->setIcon(getRealIcon("zoom-fit-text-width"));
    //actionNew->setIcon(getRealIcon("docuemtn-new"));
    //actionFileOpen->setIcon(getRealIcon("document-open"));
    //actionClose->setIcon(getRealIcon("close"));
    //action_Print->setIcon(getRealIcon("fileprint"));
#ifdef Q_OS_WIN32
	//action_Print->setVisible(false);
#endif
    /*actionUndo->setIcon(getRealIcon("edit-undo"));
	actionRedo->setIcon(getRealIcon("edit-redo"));
	actionCut->setIcon(getRealIcon("edit-cut"));
    actionCopy->setIcon(getRealIcon("edit-copy"));
    actionPaste->setIcon(getRealIcon("edit-paste"));*/
    //actionMagnify->setIcon(getRealIcon("magnifier-button"));
    //actionScroll->setIcon(getRealIcon("hand"));
    //actionTypeset->setIcon(getRealIcon("build"));
    //actionEnlargeViewer->setIcon(getRealIcon("enlarge-viewer"));
    //actionShrinkViewer->setIcon(getRealIcon("shrink-viewer"));

	QIcon icon = getRealIcon("syncSource-off");
	icon.addFile(getRealIconFile("syncSource"), QSize(), QIcon::Normal, QIcon::On);
	actionCursor_follows_scrolling->setIcon(icon);
	icon = getRealIcon("syncViewer-off");
	icon.addFile(getRealIconFile("syncViewer"), QSize(), QIcon::Normal, QIcon::On);
	actionScrolling_follows_cursor->setIcon(icon);

	if (embedded) {
		actionToggleEmbedded->setIcon(getRealIcon("windowed-viewer"));
		actionToggleEmbedded->setToolTip(tr("Windowed Viewer"));
	} else {
		actionToggleEmbedded->setIcon(getRealIcon("embedded-viewer"));
		actionToggleEmbedded->setToolTip(tr("Embedded Viewer"));
	}

	actionExternalViewer->setIcon(getRealIcon("acroread"));
	if (embedded) {
		actionTypeset->setVisible(false);
		actionShrinkViewer->setVisible(false);
	} else {
		actionClose->setVisible(false);
		actionAutoHideToolbars->setVisible(false);
		actionEnlargeViewer->setVisible(false);
		actionShrinkViewer->setVisible(false);
	}

	setContextMenuPolicy(Qt::NoContextMenu);

	toolButtonGroup = new QButtonGroup(toolBar);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton *>(toolBar->widgetForAction(actionMagnify)), kMagnifier);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton *>(toolBar->widgetForAction(actionScroll)), kScroll);
	//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Text)), kSelectText);
	//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Image)), kSelectImage);
	connect(toolButtonGroup, SIGNAL(buttonClicked(int)), pdfWidget, SLOT(setTool(int)));
	conf->registerOption("Preview/EditTool", &globalConfig->editTool, kMagnifier);
	QAbstractButton *bt = toolButtonGroup->button(globalConfig->editTool);
	if (bt) bt->setChecked(true);
	pdfWidget->setTool(globalConfig->editTool);

	comboZoom = 0;

	int sz = qMax(16, ConfigManager::getInstance()->getOption("GUI/SecondaryToobarIconSize").toInt());
	toolBar->setIconSize(QSize(sz, sz));
	QWidget *spacer = new QWidget(toolBar);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->insertWidget(actionAutoHideToolbars, spacer);
	addAction(toolBar->toggleViewAction());

	leCurrentPage = new QLineEdit(toolBar);
	leCurrentPage->setMaxLength(5);
	leCurrentPage->setFixedWidth(fontMetrics().width("#####"));
	leCurrentPageValidator = new QIntValidator(1, 99999, leCurrentPage);
	leCurrentPage->setValidator(leCurrentPageValidator);
	leCurrentPage->setText("1");
	leCurrentPage->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	// TODO: hack to adjust color of the line edit for modern style. Should be done properly in style itself (manhattanstyle.cpp)
	bool modernStyle = ConfigManager::getInstance()->getOption("GUI/Style").toBool();
	if (modernStyle) {
		leCurrentPage->setStyleSheet("QLineEdit{ color: white; padding-top: -1px; margin-right: 2px; }");
	} else {
		leCurrentPage->setStyleSheet("QLineEdit{ padding-top: -1px; margin-right: 2px; }");
	}
	connect(leCurrentPage, SIGNAL(returnPressed()), this, SLOT(jumpToPage()));
	pageCountLabel = new QLabel("1", toolBar);
	pageCountLabel->setAlignment(Qt::AlignCenter);
	pageCountSeparator = new QLabel(tr("of", "separator for page number: 1 of 3"), toolBar);
	pageCountSeparator->setAlignment(Qt::AlignCenter);
	toolBar->insertWidget(actionNext_Page, leCurrentPage);
	toolBar->insertWidget(actionNext_Page, pageCountSeparator);
	toolBar->insertWidget(actionNext_Page, pageCountLabel);
	connect(toolBar, SIGNAL(orientationChanged(Qt::Orientation)), this, SLOT(updateToolBarForOrientation(Qt::Orientation)));
	updateToolBarForOrientation(toolBar->orientation());

	QToolButton *tbCursorFollowsScrolling = UtilsUi::createToolButtonForAction(actionCursor_follows_scrolling);
	statusBar()->addPermanentWidget(tbCursorFollowsScrolling);
	QToolButton *tbScrollingFollowsCursor = UtilsUi::createToolButtonForAction(actionScrolling_follows_cursor);
	statusBar()->addPermanentWidget(tbScrollingFollowsCursor);

	QLabel *lbMessage = new QLabel();
	lbMessage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
	connect(statusBar(), SIGNAL(messageChanged(QString)), lbMessage, SLOT(setText(QString)));
	statusBar()->addPermanentWidget(lbMessage, 1);


	pageLabel = new QLabel(statusBar());
	statusBar()->addPermanentWidget(pageLabel);

	scaleButton = new QToolButton(toolBar);
	scaleButton->setToolTip(tr("Scale"));
	scaleButton->setPopupMode(QToolButton::InstantPopup);
	scaleButton->setAutoRaise(true);
	scaleButton->setMinimumWidth(statusBar()->fontMetrics().width("OOOOOO"));
	scaleButton->setText("100%");
	statusBar()->addPermanentWidget(scaleButton);
	QList<int> levels = QList<int>() << 25 << 50 << 75 << 100 << 150 << 200 << 300 << 400;
	QActionGroup *scaleActions = new QActionGroup(scaleButton);
	foreach (int level, levels) {
		QAction *act = new QAction(scaleActions);
		act->setText(QString("%1\%").arg(level));
		act->setData(QVariant(level));
		connect(act, SIGNAL(triggered()), this, SLOT(zoomFromAction()));
	}
	scaleButton->addActions(scaleActions->actions());

	QToolButton *buttonZoomOut = new QToolButton(statusBar());
	buttonZoomOut->setIcon(getRealIcon("zoom-out"));
	buttonZoomOut->setToolTip(tr("Zoom Out"));
	statusBar()->addPermanentWidget(buttonZoomOut);
	connect(buttonZoomOut, SIGNAL(clicked(bool)), actionZoom_Out, SLOT(trigger()));

	zoomSlider = new QSlider(toolBar);
	zoomSlider->setOrientation(Qt::Horizontal);
	zoomSlider->setSingleStep(25);
	zoomSlider->setMinimum(-100);
	zoomSlider->setMaximum(100);
	zoomSlider->setFixedWidth(100);
	zoomSlider->setToolTip(tr("Zoom"));
	//zoomSlider->setTickInterval(100);
	//zoomSlider->setTickPosition(QSlider::TicksBelow);
	statusBar()->addPermanentWidget(zoomSlider);

	connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomSliderChange(int)));

	QToolButton *buttonZoomIn = new QToolButton(statusBar());
	buttonZoomIn->setIcon(getRealIcon("zoom-in"));
	buttonZoomIn->setToolTip(tr("Zoom In"));
	statusBar()->addPermanentWidget(buttonZoomIn);
	connect(buttonZoomIn, SIGNAL(clicked()), actionZoom_In, SLOT(trigger()));

	QSplitter *vSplitter = new MiniSplitter(Qt::Vertical);

	// TODO: Make Frame around Label and Scroll area
	scrollArea = new PDFScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	//scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setPDFWidget(pdfWidget);
	if (embedded) {
		scrollArea->setFrameStyle(QFrame::NoFrame);
	}

	QWidget *container = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout;
	container->setLayout(layout);
	messageFrame = new MessageFrame;
	layout->addWidget(messageFrame);
	layout->addWidget(scrollArea);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	vSplitter->addWidget(container);

	annotationPanel = new TitledPanel();
	annotationPanel->setFrameShape(QFrame::NoFrame);
	annotationPanel->toggleViewAction()->setText(tr("Annotations"));
	annotationPanel->setVisible(globalConfig->annotationPanelVisible);
	annotationTable = new PDFAnnotationTableView();
	TitledPanelPage *annotationPage = new TitledPanelPage(annotationTable, "pdfannotations", tr("Annotations"));
	annotationPanel->appendPage(annotationPage);
	vSplitter->setStretchFactor(0, 2);
	vSplitter->setStretchFactor(1, 1);
	vSplitter->addWidget(annotationPanel);
	setCentralWidget(vSplitter);

	connect(scrollArea, SIGNAL(resized()), pdfWidget, SLOT(windowResized()));

    //connect(actionAbout_TW, SIGNAL(triggered()), SIGNAL(triggeredAbout()));
    //connect(actionUserManual, SIGNAL(triggered()), SIGNAL(triggeredManual()));
	connect(actionEnlargeViewer, SIGNAL(triggered()), this , SLOT(enlarge()));
	connect(actionShrinkViewer, SIGNAL(triggered()), this , SLOT(shrink()));

    //connect(actionQuit_TeXworks, SIGNAL(triggered()), SIGNAL(triggeredQuit()));

    //connect(actionFind_2, SIGNAL(triggered()), this, SLOT(doFindDialog()));
    //connect(actionFind_again, SIGNAL(triggered()), this, SLOT(doFindAgain()));

    //connect(actionFirst_Page, SIGNAL(triggered()), pdfWidget, SLOT(goFirst()));
    //connect(actionBack, SIGNAL(triggered()), pdfWidget, SLOT(goBack()));
    /*connect(actionPrevious_Page, SIGNAL(triggered()), pdfWidget, SLOT(goPrev()));
	connect(actionForward, SIGNAL(triggered()), pdfWidget, SLOT(goForward()));
	connect(actionNext_Page, SIGNAL(triggered()), pdfWidget, SLOT(goNext()));
	connect(actionLast_Page, SIGNAL(triggered()), pdfWidget, SLOT(goLast()));
	connect(actionGo_to_Page, SIGNAL(triggered()), pdfWidget, SLOT(doPageDialog()));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), this, SLOT(enablePageActions(int, bool)));
	connect(actionFileOpen, SIGNAL(triggered()), SLOT(fileOpen()));
	connect(actionSplitMerge, SIGNAL(triggered()), SLOT(splitMergeTool()));
	connect(action_Print, SIGNAL(triggered()), this, SLOT(printPDF()));

	connect(actionActual_Size, SIGNAL(triggered()), pdfWidget, SLOT(fixedScale()));
    */
	connect(actionFit_to_Width, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWidth(bool)));
	connect(actionFit_to_Text_Width, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitTextWidth(bool)));
	connect(actionFit_to_Window, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWindow(bool)));


    /*connect(actionGrid11, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid12, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid21, SIGNAL(triggered()), SLOT(setGrid()));
    connect(actionGrid22, SIGNAL(triggered()), SLOT(setGrid()));*/


	if (!embedded) {
		conf->registerOption("Preview/GridX", &globalConfig->gridx, 1);
		conf->registerOption("Preview/GridY", &globalConfig->gridy, 1);
		pdfWidget->setGridSize(globalConfig->gridx, globalConfig->gridy, true);

        //connect(actionSinglePageStep, SIGNAL(toggled(bool)), pdfWidget, SLOT(setSinglePageStep(bool)));
		conf->registerOption("Preview/Single Page Step", &globalConfig->singlepagestep, true);
		conf->linkOptionToObject(&globalConfig->singlepagestep, actionSinglePageStep, 0);
        connect(actionContinuous, SIGNAL(toggled(bool)), scrollArea, SLOT(setContinuous(bool)));
		conf->registerOption("Preview/Continuous", &globalConfig->continuous, true);
		conf->linkOptionToObject(&globalConfig->continuous, actionContinuous, 0);
	} else {
		pdfWidget->setGridSize(1, 1, true);
		pdfWidget->setSinglePageStep(true);
		scrollArea->setContinuous(true);
	}

    //connect(actionZoom_In, SIGNAL(triggered()), pdfWidget, SLOT(zoomIn()));
    //connect(actionZoom_Out, SIGNAL(triggered()), pdfWidget, SLOT(zoomOut()));
    //connect(actionFull_Screen, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen(bool)));
    //connect(actionPresentation, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen(bool)));
	connect(pdfWidget, SIGNAL(changedZoom(qreal)), this, SLOT(enableZoomActions(qreal)));
	connect(pdfWidget, SIGNAL(changedScaleOption(autoScaleOption)), this, SLOT(adjustScaleActions(autoScaleOption)));
	connect(pdfWidget, SIGNAL(syncClick(int, const QPointF &, bool)), this, SLOT(syncClick(int, const QPointF &, bool)));

	if (actionZoom_In->shortcut() == QKeySequence("Ctrl++"))
		new QShortcut(QKeySequence("Ctrl+="), pdfWidget, SLOT(zoomIn()), Q_NULLPTR, Qt::WidgetShortcut);
	if (!actionActual_Size->shortcut().isEmpty())
		new QShortcut(QKeySequence("Ctrl+0"), pdfWidget, SLOT(fixedScale()), Q_NULLPTR, Qt::WidgetShortcut);


    /*connect(actionTypeset, SIGNAL(triggered()), SLOT(runQuickBuild()));

	connect(actionExternalViewer, SIGNAL(triggered()), SLOT(runExternalViewer()));
	connect(actionToggleEmbedded, SIGNAL(triggered()), SLOT(toggleEmbedded()));

	connect(actionCloseElement, SIGNAL(triggered()), SLOT(closeElement()));
	connect(actionStack, SIGNAL(triggered()), SLOT(stackWindows()));
	connect(actionTile, SIGNAL(triggered()), SLOT(tileWindows()));
	connect(actionSide_by_Side, SIGNAL(triggered()), this, SLOT(sideBySide()));
	connect(actionGo_to_Source, SIGNAL(triggered()), this, SLOT(goToSource()));
	connect(actionFocus_Editor, SIGNAL(triggered()), this, SIGNAL(focusEditor()));
	connect(actionNew_Window, SIGNAL(triggered()), SIGNAL(triggeredClone()));
    */

	conf->registerOption("Preview/Scrolling Follows Cursor", &globalConfig->followFromCursor, false);
	conf->linkOptionToObject(&globalConfig->followFromCursor, actionScrolling_follows_cursor);
	conf->registerOption("Preview/Cursor Follows Scrolling", &globalConfig->followFromScroll, false);
	conf->linkOptionToObject(&globalConfig->followFromScroll, actionCursor_follows_scrolling);
	conf->registerOption("Preview/Sync Multiple Views", &globalConfig->syncViews, true);
	conf->linkOptionToObject(&globalConfig->syncViews, actionSynchronize_multiple_views);
	conf->registerOption("Preview/Invert Colors", &globalConfig->invertColors, false);
	conf->linkOptionToObject(&globalConfig->invertColors, actionInvertColors);
    //connect(actionInvertColors, SIGNAL(triggered()), pdfWidget, SLOT(update()));
	conf->registerOption("Preview/Grayscale", &globalConfig->grayscale, false);
	conf->linkOptionToObject(&globalConfig->grayscale, actionGrayscale);
    //connect(actionGrayscale, SIGNAL(triggered()), pdfWidget, SLOT(update()));

    //connect(actionPreferences, SIGNAL(triggered()), SIGNAL(triggeredConfigure()));
    if(!embedded){
        menuShow->addAction(toolBar->toggleViewAction());
        menuShow->addSeparator();
    }

	menuShow->addAction(annotationPanel->toggleViewAction());

	QDockWidget *dw = dwOutline = new PDFOutlineDock(this);
	if (embedded)
		dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(documentLoaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));

	dw = dwInfo = new PDFInfoDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(documentLoaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));

	dw = dwSearch = new PDFSearchDock(this);
	if (embedded)
		dw->hide();
	connect(dwSearch, SIGNAL(search(bool, bool)),  SLOT(search(bool, bool)));
    connect(dwSearch, SIGNAL(visibilityChanged(bool)),  SLOT(clearHightlight(bool)));
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());

	dw = dwFonts = new PDFFontsDock(this);
	dw->hide();
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(documentLoaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));

	dw = dwOverview = new PDFOverviewDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(documentLoaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));

	dw = dwClock = new PDFClockDock(this);
	dw->hide();
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(update()));

	actionPage_Down = new QAction(tr("Page Down"), this);
	actionPage_Down->setShortcut(QKeySequence::MoveToNextPage);
	addAction(actionPage_Down);
	connect(actionPage_Down, SIGNAL(triggered()), pdfWidget, SLOT(pageDownOrNext()));
	actionPage_Up = new QAction(tr("Page Up"), this);
	actionPage_Up->setShortcut(QKeySequence::MoveToPreviousPage);
	connect(actionPage_Up, SIGNAL(triggered()), pdfWidget, SLOT(pageUpOrPrev()));
	addAction(actionPage_Up);
	//disable all action shortcuts when embedded
	if (embedded) {
		shortcutOnlyIfFocused(QList<QAction *>()
		                      << actionNext_Page
		                      << actionPrevious_Page
		                      << actionLast_Page
		                      << actionFirst_Page
		                      << actionForward
		                      << actionBack
		                      << actionPage_Down
		                      << actionPage_Up
		                      << actionGo_to_Page
		                      << actionZoom_In
		                      << actionZoom_Out
		                      << actionFit_to_Window
		                      << actionActual_Size
		                      << actionFit_to_Width
		                      << actionFit_to_Text_Width
		                      << actionClose
		                      << actionGo_to_Source
                              << actionFind
                              << actionFind_Again
		                     );
        /*actionNew->setShortcut(QKeySequence());
		actionOpen->setShortcut(QKeySequence());
		actionTypeset->setShortcut(QKeySequence());
		actionNew_from_Template->setShortcut(QKeySequence());
		actionFull_Screen->setShortcut(QKeySequence());
		actionQuit_TeXworks->setShortcut(QKeySequence());
		actionCloseElement->setShortcut(QKeySequence());
		actionPresentation->setShortcut(QKeySequence());
        actionFileOpen->setShortcut(QKeySequence());*/
	}
}

bool PDFDocument::followCursor() const
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return false;
	return globalConfig->followFromCursor;
}

void PDFDocument::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange) {
		QString title = windowTitle();
        //retranslateUi(this);
		setWindowTitle(title);
		if (pdfWidget && pdfWidget->isVisible())
			pdfWidget->updateStatusBar();
	} else
		QMainWindow::changeEvent(event);
}

void PDFDocument::sideBySide()
{
	QWidget *mainWindow = 0;
	foreach (QWidget *widget, QApplication::topLevelWidgets())
		if (!widget->isHidden() && widget != this &&  qobject_cast<QMainWindow *>(widget) != 0) {
			mainWindow = widget;
			break;
		}
	if (mainWindow) {
		windowsSideBySide(mainWindow, this);
		windowsSideBySide(mainWindow, this); //???first call fails on linux with qt4.6.3???? (position is correct, but move doesn't move there, although it works in texworks)
	}
}

void PDFDocument::closeEvent(QCloseEvent *event)
{
	Q_ASSERT(globalConfig);
	if (isVisible() && !embeddedMode) {
		saveGeometryToConfig();
	}
	event->accept();
	deleteLater();
}

void PDFDocument::syncFromView(const QString &pdfFile, const QFileInfo &masterFile, int page)
{
	if (!actionSynchronize_multiple_views->isChecked())
		return;
	if (pdfFile != curFile || this->masterFile != masterFile)
		loadFile(pdfFile, masterFile, NoDisplayFlags);
	if (page != widget()->getPageIndex())
		scrollArea->goToPage(page, false);
}

/*!
 * \brief PDFDocument::loadFile
 * \param fileName  the file to load
 * \param masterFile  tex corresponding .tex source file. If not given, assume it's identical to fileName but
 *        with extension .tex
 * \param displayFlags
 */
void PDFDocument::loadFile(const QString &fileName, QFileInfo masterFile, DisplayFlags displayFlags)
{
	if (masterFile.fileName().isEmpty()) {
		masterFile.setFile(replaceFileExtension(fileName, ".tex"));
	}

	// check if the file is already loaded
	bool fileAlreadyLoaded = (this->masterFile == masterFile);
	fileAlreadyLoaded = fileAlreadyLoaded && (curFileUnnormalized == fileName);
	if (fileAlreadyLoaded) {
		// check size and modifcation date
		QFileInfo fi(curFile);
		QDateTime lastModified = fi.lastModified();
		qint64 filesize = fi.size();
		fileAlreadyLoaded = fileAlreadyLoaded && (lastModified == curFileLastModified);
		fileAlreadyLoaded = fileAlreadyLoaded && (filesize == curFileSize);
		fileAlreadyLoaded = fileAlreadyLoaded && fi.exists();
	}
	if (!fileAlreadyLoaded) {
		this->masterFile = masterFile;
		setCurrentFile(fileName);
		loadCurrentFile(false);
	}

	if (watcher) {
		const QStringList files = watcher->files();
		if (!files.isEmpty())
			watcher->removePaths(files); // in case we ever load different files into the same widget
		if (curFile != "")
			watcher->addPath(curFile);
	}
	updateDisplayState(displayFlags);
}

void PDFDocument::fillRenderCache(int pg)
{
	if (renderManager)
		renderManager->fillCache(pg);
}

void PDFDocument::loadCurrentFile(bool fillCache)
{
	if (reloadTimer) reloadTimer->stop();
	messageFrame->hide();
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		QVariant fc = act->property("fillCache");
		if (fc.isValid())
			fillCache = fc.toBool();
	}

	static bool isReloading = false;
	if (isReloading) return;
	isReloading = true;
	QApplication::setOverrideCursor(Qt::WaitCursor);

	scanner.clear();

	QString password;

retryNow:

	if (renderManager) {
		renderManager->stopRendering();
		renderManager->deleteLater();
		renderManager = 0;
	}

	renderManager = new PDFRenderManager(this);
	renderManager->setCacheSize(globalConfig->cacheSizeMB);
	renderManager->setLoadStrategy(int(globalConfig->loadStrategy));
	PDFRenderManager::Error error = PDFRenderManager::NoError;
	QFileInfo fi(curFile);
	QDateTime lastModified = fi.lastModified();
	qint64 filesize = fi.size();
	document = renderManager->loadDocument(curFile, error, password);
	if (error == PDFRenderManager::FileIncomplete) {
		QAction *retryAction = new QAction(tr("Retry"), this);
		retryAction->setProperty("fillCache", fillCache);
		connect(retryAction, SIGNAL(triggered()), this, SLOT(loadCurrentFile()));
		QAction *closeAction = new QAction(tr("Close"), this);
		connect(closeAction, SIGNAL(triggered()), this, SLOT(stopReloadTimer()));
		connect(closeAction, SIGNAL(triggered()), messageFrame, SLOT(hide()));
		messageFrame->showText(tr("%1\ndoes not look like a valid PDF document. Either the file is corrupt or it is in the process of creation. Retrying every two seconds.").arg(curFile),
		                       QList<QAction *>() << retryAction << closeAction);
	}

	curFileSize = filesize; // store size and modification time to check whether reloaded file has been changed meanwhile
	curFileLastModified = lastModified;

	if (document.isNull()) {
		delete renderManager;
		renderManager = 0;
		switch (error) {
		case PDFRenderManager::NoError:
			break;
		case PDFRenderManager::FileOpenFailed:
			statusBar()->showMessage(tr("Failed to find file \"%1\"; perhaps it has been deleted.").arg(curFileUnnormalized));
			break;
		case PDFRenderManager::PopplerError:
			statusBar()->showMessage(tr("Failed to load file \"%1\"; perhaps it is not a valid PDF document.").arg(curFile));
			break;
		case PDFRenderManager::PopplerErrorBadAlloc:
			statusBar()->showMessage(tr("Failed to load file \"%1\" due to a bad alloc; perhaps it is not a valid PDF document.").arg(curFile));
			break;
		case PDFRenderManager::PopplerErrorException:
			statusBar()->showMessage(tr("Failed to load file \"%1\" due to an exception; perhaps it is not a valid PDF document.").arg(curFile));
			break;
		case PDFRenderManager::FileLocked: {
			statusBar()->showMessage(tr("PDF file \"%1\" is locked.").arg(curFile));
			bool ok;
			password = QInputDialog::getText(0, tr("PDF password"), tr("PDF file \"%1\" is locked.\nYou can now enter the password:").arg(curFile), QLineEdit::Password, password, &ok );
			if (ok) goto retryNow;
			break;
		}
		case PDFRenderManager::FileIncomplete:
			break; // message is handled via messageFrame
		}
		pdfWidget->hide();
		pdfWidget->setDocument(document);
		if (error == PDFRenderManager::FileIncomplete)
			reloadWhenIdle();
	} else {
		pdfWidget->setDocument(document);
		pdfWidget->show();

		annotations = new PDFAnnotations(this);
		annotationTable->setModel(annotations->createModel());
		annotationTable->resizeColumnsToContents();
		annotationTable->resizeRowsToContents();
		connect(annotationTable, SIGNAL(annotationClicked(const PDFAnnotation *)), SLOT(gotoAnnotation(const PDFAnnotation *)));
		connect(annotationTable, SIGNAL(annotationDoubleClicked(const PDFAnnotation *)), pdfWidget, SLOT(openAnnotationDialog(const PDFAnnotation *)));

		if (!embeddedMode)
			pdfWidget->setFocus();

		// set page viewer only once
                int maxDigits = 1 + qFloor(log10(pdfWidget->realNumPages()));
		//if (maxDigits < 2) maxDigits = 2;
		leCurrentPage->setMaxLength(maxDigits);
		leCurrentPage->setFixedWidth(fontMetrics().width(QString(maxDigits + 1, '#')));
		leCurrentPageValidator->setTop(pdfWidget->realNumPages());
		//qDebug() << pdfWidget->realNumPages() << maxDigits << fontMetrics().width(QString(maxDigits+1, '#'));

		loadSyncData();
		if (fillCache) {
			renderManager->fillCache();
		}
		scrollArea->updateScrollBars();

		emit documentLoaded();
	}
	for (int i = 0; i < password.length(); i++)
		password[i] = '\0';

	QApplication::restoreOverrideCursor();
	isReloading = false;
}

void PDFDocument::stopReloadTimer()
{
	if (reloadTimer)
		reloadTimer->stop();
}

void PDFDocument::reloadWhenIdle()
{
	if (reloadTimer)
		reloadTimer->stop();
	else {
		reloadTimer = new QTimer(this);
		reloadTimer->setSingleShot(true);
		reloadTimer->setInterval(500);
		connect(reloadTimer, SIGNAL(timeout()), this, SLOT(idleReload()));
	}
	reloadTimer->start();
}

void PDFDocument::idleReload()
{
	if (isCompiling) reloadWhenIdle();
	else loadCurrentFile();
}

void PDFDocument::runExternalViewer()
{
	emit runCommand("txs:///view-pdf-external", masterFile, QFileInfo(lastSyncPoint.filename), lastSyncPoint.line);
}

void PDFDocument::runInternalViewer()
{
	emit runCommand("txs:///view-pdf-internal --windowed --close-embedded", masterFile, QFileInfo(lastSyncPoint.filename), lastSyncPoint.line);
}

void PDFDocument::toggleEmbedded()
{
	if (embeddedMode)
		emit runCommand("txs:///view-pdf-internal --windowed --close-embedded", masterFile, QFileInfo(lastSyncPoint.filename), lastSyncPoint.line);
	else
		emit runCommand("txs:///view-pdf-internal --embedded --close-windowed", masterFile, QFileInfo(lastSyncPoint.filename), lastSyncPoint.line);
}

void PDFDocument::toggleAutoHideToolbars()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		globalConfig->autoHideToolbars = act->isChecked();
	}
}

void PDFDocument::runQuickBuild()
{
	emit runCommand("txs:///quick", masterFile, QFileInfo(lastSyncPoint.filename), lastSyncPoint.line);
}

void PDFDocument::setGrid()
{
	REQUIRE(pdfWidget && sender());
	QString gs = sender()->property("grid").toString();
	if (gs == "xx") {
		UniversalInputDialog d;
		int x = 1, y = 1;
		d.addVariable(&x , "X-Grid:");
		d.addVariable(&y , "Y-Grid:");
		if (d.exec()) {
			pdfWidget->setGridSize(x, y);
			globalConfig->gridx = x;
			globalConfig->gridy = y;
		}
	} else {
		int p = gs.indexOf("x");
		globalConfig->gridx = gs.left(p).toInt();
		globalConfig->gridy = gs.mid(p + 1).toInt();
		pdfWidget->setGridSize(globalConfig->gridx, globalConfig->gridy);
	}
	pdfWidget->windowResized();
}

void PDFDocument::jumpToPage()
{
	int index = leCurrentPage->text().toInt();
	//scrollArea->goToPage(index-1);
	goToPage(index - 1);
}

void PDFDocument::shrink()
{
	setStateEnlarged(false);
	emit triggeredShrink();
}

void PDFDocument::enlarge()
{
	setStateEnlarged(true);
	emit triggeredEnlarge();
}

void PDFDocument::setStateEnlarged(bool state)
{
	actionEnlargeViewer->setVisible(!state);
	actionShrinkViewer->setVisible(state);
}

/*!
 * \return true if the document itself is closed, otherwise false
 */
bool PDFDocument::closeElement()
{
	ConfigManager *configManager=dynamic_cast<ConfigManager *>(ConfigManager::getInstance());

	if (actionPresentation->isChecked()) {
		//restore state of docks
		if (dwVisSearch)
			dwSearch->show();
		if (dwVisFonts)
			dwFonts->show();
		if (dwVisInfo)
			dwInfo->show();
		if (dwVisOutline)
			dwOutline->show();
		if (dwVisOverview)
			dwOverview->show();
		toggleFullScreen(false);
	} else if (configManager->useEscForClosingFullscreen && actionFull_Screen->isChecked()) {
		toggleFullScreen(false);
	} else if (dwFonts && dwFonts->isVisible()) dwFonts->hide();
	else if (dwSearch && dwSearch->isVisible()) dwSearch->hide();
	else if (dwInfo && dwInfo->isVisible()) dwInfo->hide();
	else if (dwClock && dwClock->isVisible()) dwClock->hide();
	else if (dwOutline && dwOutline->isVisible()) dwOutline->hide();
	else if (dwOverview && dwOverview->isVisible()) dwOverview->hide();
	else if (configManager->useEscForClosingEmbeddedViewer && isVisible()) {
		// Note: avoid crash on osx where esc key is passed to hidden window
		actionClose->trigger();
	} else {
		return false;  // nothing to close
	}
	return true;
}

void PDFDocument::tileWindows()
{
	arrangeWindows(true);
}

void PDFDocument::stackWindows()
{
	arrangeWindows(false);
}

void PDFDocument::unminimize()
{
	if (isMinimized()) {
		if (globalConfig->windowMaximized) {
			showMaximized();
		} else {
			showNormal();
		}
	} else {
		show();
	}
}

void PDFDocument::updateDisplayState(DisplayFlags displayFlags)
{
	displayFlags &= (embeddedMode) ? FilterEmbedded : FilterWindowed;
	QWidget *activeWindow = QApplication::activeWindow();
	unminimize();
	if (displayFlags & Raise) {
		raise();
	} else if (activeWindow) {  // unminimize() may have brought the viewer to Front
		activeWindow->raise();
	}
	if (displayFlags & Focus) {
		if (embeddedMode) {
			setFocus();
		} else {
			activateWindow();
		}
		if (scrollArea) scrollArea->setFocus();
	} else if (activeWindow) {  // unminimize may have made the viewer active
		activeWindow->activateWindow();
	}

}

void PDFDocument::arrangeWindows(bool tile)
{
	QDesktopWidget *desktop = QApplication::desktop();
	for (int screenIndex = 0; screenIndex < desktop->numScreens(); ++screenIndex) {
		QWidgetList windows;
		foreach (QWidget *widget, QApplication::topLevelWidgets())
			if (!widget->isHidden() && qobject_cast<QMainWindow *>(widget))
				windows << widget;
		if (windows.size() > 0)
			(*(tile ? &tileWindowsInRect : &stackWindowsInRect)) (windows, desktop->availableGeometry(screenIndex));
	}
}

void PDFDocument::updateToolBarForOrientation(Qt::Orientation orientation)
{
	if (orientation == Qt::Horizontal) {
		leCurrentPage->setAlignment(Qt::AlignRight);
		pageCountSeparator->setText(pageCountSeparator->text() + " ");
	} else {
		leCurrentPage->setAlignment(Qt::AlignCenter);
		pageCountSeparator->setText(pageCountSeparator->text().trimmed());
	}
}

void PDFDocument::clearHightlight(bool ){
    pdfWidget->setHighlightPath(-1, QPainterPath());
}

void PDFDocument::search(bool backwards, bool incremental)
{
	if (!dwSearch) return;
	search(dwSearch->getSearchText(), backwards, incremental, dwSearch->hasFlagCaseSensitive(), dwSearch->hasFlagWholeWords(), dwSearch->hasFlagSync());
}
//better use flags for this
void PDFDocument::search(const QString &searchText, bool backwards, bool incremental, bool caseSensitive, bool wholeWords, bool sync)
{
	if (document.isNull())
		return;

	int pageIdx;
#ifdef HAS_POPPLER_31
    Poppler::Page::SearchFlags searchFlags = 0;
#else
    Poppler::Page::SearchMode searchMode = Poppler::Page::CaseInsensitive;
#endif
	Poppler::Page::SearchDirection searchDir; // = Poppler::Page::FromTop;
	int deltaPage, firstPage, lastPage;
	int run, runs;

	if (searchText.isEmpty())
		return;

#ifdef HAS_POPPLER_31
	if (!caseSensitive)
		searchFlags |= Poppler::Page::IgnoreCase;
	if (wholeWords)
		searchFlags |= Poppler::Page::WholeWords;
#else
    if (caseSensitive)
            searchMode = Poppler::Page::CaseSensitive;
#endif

	deltaPage = (backwards ? -1 : +1);

	//	if (!incremental) { //TODO
	//		lastSearchResult.selRect = QRectF();
	//		firstSearchPage = pdfWidget->getCurrentPageIndex();
	//	}
	searchDir = (backwards ? Poppler::Page::PreviousResult : Poppler::Page::NextResult);

	runs = (true ? 2 : 1); //true = always wrap around

	Q_ASSERT(!backwards || !incremental);
	if (incremental) {
		//make sure that we find the current match again
		lastSearchResult.selRect.setLeft(lastSearchResult.selRect.left() - 0.01);
		lastSearchResult.selRect.setRight(lastSearchResult.selRect.left());
	}

	int startPage = lastSearchResult.pageIdx;
	if (lastSearchResult.pageIdx != pdfWidget->getPageIndex()) {
        // function to check that lastSearchResult is visible is missing
        // quick workaround is that the at least the page is shown, even partially
        // visible pages
        int visPages=pdfWidget->visiblePages(); // function return too large a number, buggy
        if (((pdfWidget->getPageIndex()+visPages-1) < pdfWidget->normalizedPageIndex(lastSearchResult.pageIdx)) || (pdfWidget->getPageIndex() > pdfWidget->normalizedPageIndex(lastSearchResult.pageIdx))) {
			startPage = pdfWidget->getPageIndex();
			lastSearchResult.selRect = backwards ? QRectF(0, 100000, 1, 1) : QRectF();
		}
	}

	for (run = 0; run < runs; ++run) {
		switch (run) {
		case 0:
			// first run = normal search
			lastPage = (backwards ? -1 : pdfWidget->realNumPages());
			firstPage = startPage;
			break;
		case 1:
			// second run = after wrap
			lastPage = (backwards ? -1 : pdfWidget->realNumPages());
			firstPage = (backwards ? pdfWidget->realNumPages() - 1 : 0);
			break;
		default:
			// should not happen
			Q_ASSERT(false);
			return;
		}

		for (pageIdx = firstPage; pageIdx != lastPage; pageIdx += deltaPage) {
			if (pageIdx < 0 || pageIdx >= pdfWidget->realNumPages())
				return;

			statusBar()->showMessage(tr("Searching for") + QString(" '%1' (Page %2)").arg(searchText).arg(pageIdx), 1000);

			QScopedPointer<Poppler::Page> page(document->page(pageIdx));
			if (!page)
				return;



#ifdef HAS_POPPLER_31
			double rectLeft, rectTop, rectRight, rectBottom;
			rectLeft = lastSearchResult.selRect.left();
			rectTop = lastSearchResult.selRect.top();
			rectRight = lastSearchResult.selRect.right();
			rectBottom = lastSearchResult.selRect.bottom();
			if (page->search(searchText, rectLeft, rectTop, rectRight, rectBottom , searchDir, searchFlags)) {
			        lastSearchResult.selRect = QRectF(rectLeft, rectTop, rectRight - rectLeft, rectBottom - rectTop);
#else
#if QT_VERSION >= 0x050000
			double rectLeft, rectTop, rectRight, rectBottom;
			rectLeft = lastSearchResult.selRect.left();
			rectTop = lastSearchResult.selRect.top();
			rectRight = lastSearchResult.selRect.right();
			rectBottom = lastSearchResult.selRect.bottom();
			if (page->search(searchText, rectLeft, rectTop, rectRight, rectBottom , searchDir, searchMode)) {
			        lastSearchResult.selRect = QRectF(rectLeft, rectTop, rectRight - rectLeft, rectBottom - rectTop);
#else
			if (page->search(searchText, lastSearchResult.selRect, searchDir, searchMode)) {
#endif

#endif
				lastSearchResult.doc = this;
				lastSearchResult.pageIdx = pageIdx;
				QPainterPath p;
				p.addRect(lastSearchResult.selRect);

				if (hasSyncData() && sync)
					emit syncClick(pageIdx, lastSearchResult.selRect.center(), false);


				pdfWidget->setHighlightPath(lastSearchResult.pageIdx, p,true);
				//scroll horizontally
				//scrollArea->ensureVisiblePageAbsolutePos(lastSearchResult.pageIdx, lastSearchResult.selRect.topLeft());
				pdfWidget->update();
				return;
			}

			lastSearchResult.selRect = backwards ? QRectF(0, 100000, 1, 1) : QRectF();
			searchDir = (backwards ? Poppler::Page::PreviousResult : Poppler::Page::NextResult);
		}
	}
}

void PDFDocument::search()
{
	if (!dwSearch) return;
	dwSearch->show();
	dwSearch->setFocus();
}



QString PDFDocument::debugSyncTeX(const QString &filename)
{
	int pos = filename.indexOf(SYNCTEX_EXT);
	QString baseName = pos < 0 ? filename : filename.left(pos);
	QString pdfFile;
	foreach (PDFDocument *pdf, documentList()) {
		if (pdf->fileName().startsWith(baseName)) {
			pdfFile = pdf->fileName();
			break;
		}
	}
	if (pdfFile.isEmpty() && QFile::exists(baseName + ".pdf")) pdfFile = baseName + ".pdf";
	else pdfFile = filename;

	QSynctex::Scanner sc(pdfFile);
	if (!sc.isValid()) return "Failed to load file";

	QStringList result;

	sc.display();

	result.append("Inputs:");
	QSynctex::Node node = sc.inputNode();
	while (node.isValid()) {
		int tag = node.tag();
		QString filename = tag >= 0 ? sc.fileName(tag) : "N/A";
		result.append(QString("Input:%1:%2").arg(tag).arg(filename));
		node = node.sibling();
	}

	result.append("");
	result.append("Sheets:");
	node = sc.sheet(1);
	while (node.isValid()) {
		QSynctex::Node cur = node.child();
		int page = cur.page();
		QSet<int> inputs;
		while (cur.isValid()) {
			inputs.insert(cur.tag());
			cur = cur.next();
		}
		node = node.sibling();

		QString x = QString("Page:%1:").arg(page);
		foreach (int i, inputs)
			x.append(QString("%1 ").arg(i));
		result.append(x);
	}

	return result.join("\n");
}

void PDFDocument::gotoAnnotation(const PDFAnnotation *ann)
{
	if (!pdfWidget) return;
	QPoint topLeft = pdfWidget->mapFromScaledPosition(ann->pageNum(), ann->popplerAnnotation()->boundary().topLeft()) / pdfWidget->totalScaleFactor();
	QPoint bottomRight = pdfWidget->mapFromScaledPosition(ann->pageNum(), ann->popplerAnnotation()->boundary().bottomRight() / pdfWidget->totalScaleFactor());
	QPainterPath p;
	p.addRect(QRect(topLeft, bottomRight));
	pdfWidget->setHighlightPath(ann->pageNum(), p);
	pdfWidget->update();
}

void PDFDocument::loadSyncData()
{
	scanner.load(curFileUnnormalized);
	if (!scanner.isValid())
		statusBar()->showMessage(tr("No SyncTeX data available"), 3000);
	else {
		statusBar()->showMessage(tr("SyncTeX: \"%1\"").arg(QDir::toNativeSeparators(scanner.synctexFilename())), 3000);
	}
}

void PDFDocument::syncClick(int pageIndex, const QPointF &pos, bool activate)
{
	if (!scanner.isValid())
		return;
	pdfWidget->setHighlightPath(-1, QPainterPath());
	pdfWidget->update();
	QDir curDir(QFileInfo(curFile).canonicalPath());
	QSynctex::NodeIterator iter = scanner.editQuery(pageIndex + 1, pos.x(), pos.y());
	while (iter.hasNext()) {
		QSynctex::Node node = iter.next();
		QString fullName = scanner.getNameFileInfo(curDir, node).canonicalFilePath();
		if (!globalConfig->syncFileMask.trimmed().isEmpty()) {
			bool found = false;
			foreach (const QString & s, globalConfig->syncFileMask.split(";"))
			if (QRegExp(s.trimmed(), Qt::CaseSensitive, QRegExp::Wildcard).exactMatch(fullName)) {
				found = true;
				break;
			}
			if (!found) continue;
		}

		QString word;
		if (!document.isNull() && pageIndex >= 0 && pageIndex < pdfWidget->realNumPages()) {
			QScopedPointer<Poppler::Page> popplerPage(document->page(pageIndex));
			if (popplerPage) {
				word = popplerPage->text(QRectF(pos, pos).adjusted(-35, -10, 35, 10));
				if (word.contains("\n")) word = word.split("\n")[word.split("\n").size() / 2];
				// replace ligatures
				word.replace(QChar(L'\xFB00'), QString("ff"));
				word.replace(QChar(L'\xFB01'), QString("fi"));
				word.replace(QChar(L'\xFB02'), QString("fl"));
				word.replace(QChar(L'\xFB03'), QString("ffi"));
				word.replace(QChar(L'\xFB04'), QString("ffl"));
				word.replace(QChar(L'\xFB05'), QString("ft"));
				word.replace(QChar(L'\xFB06'), QString("st"));
			}
		}

		syncFromSourceBlocked = true;
		emit syncSource(fullName, node.line() - 1, activate, word.trimmed()); //-1 because txs is 0 based, but synctex seems to be 1 based
		syncFromSourceBlocked = false;
		break; // FIXME: currently we just take the first hit
	}
}

/*!
 * \brief PDFDocument::syncFromSource
 * \param sourceFile
 * \param lineNo
 * \param column
 * \param displayFlags  window and widget actions such as changing focus, and raising a window.
 * \return 0-based page number or -1 if the syncing was not successful.
 */
int PDFDocument::syncFromSource(const QString &sourceFile, int lineNo, int column, DisplayFlags displayFlags)
{
	QSynctex::TeXSyncPoint sourcePoint(sourceFile, lineNo + 1, column + 1);  // synctex uses 1-based line and column
	lastSyncPoint = sourcePoint;

	if (!scanner.isValid() || syncFromSourceBlocked)
		return -1;

	QSynctex::PDFSyncPoint pdfPoint = scanner.syncFromTeX(sourcePoint, curFile);
	if (pdfPoint.page <= 0)
		return -1;

	pdfWidget->updateCurrentPageHistoryOffset();

	QPainterPath path;
	foreach (const QRectF &r, pdfPoint.rects) {
		path.addRect(r);
	}
	syncToSourceBlocked = true;
	path.setFillRule(Qt::WindingFill);
	if (path.isEmpty()) scrollArea->goToPage(pdfPoint.page - 1, false);  // otherwise scrolling is performed in setHighlightPath.
	pdfWidget->setHighlightPath(pdfPoint.page - 1, path);
	pdfWidget->update();
	updateDisplayState(displayFlags);
	syncToSourceBlocked = false;
	//pdfWidget->repaint();
	return pdfPoint.page - 1;
}

void PDFDocument::setCurrentFile(const QString &fileName)
{
	curFileUnnormalized = fileName;
	curFile = QFileInfo(fileName).canonicalFilePath();
	QString niceFile = QFileInfo(curFile).fileName();
	setWindowTitle(tr("%1[*] - %2").arg(niceFile).arg(tr(TEXSTUDIO)));
}

PDFDocument *PDFDocument::findDocument(const QString &fileName)
{
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

	foreach (QWidget *widget, qApp->topLevelWidgets()) {
		PDFDocument *theDoc = qobject_cast<PDFDocument *>(widget);
		if (theDoc && theDoc->curFile == canonicalFilePath)
			return theDoc;
	}
	return NULL;
}

void PDFDocument::saveGeometryToConfig()
{
	globalConfig->windowLeft = x();
	globalConfig->windowTop = y();
	globalConfig->windowWidth = width();
	globalConfig->windowHeight = height();
	globalConfig->windowMaximized = isMaximized();
	globalConfig->windowState = saveState();
	globalConfig->toolbarVisible = toolBar->isVisible();
	globalConfig->annotationPanelVisible = annotationPanel->isVisible();
}

void PDFDocument::zoomToRight(QWidget *otherWindow)
{
	QDesktopWidget *desktop = QApplication::desktop();
	QRect screenRect = desktop->availableGeometry(otherWindow == NULL ? this : otherWindow);
	screenRect.setTop(screenRect.top() + 22);
	screenRect.setLeft((screenRect.left() + screenRect.right()) / 2 + 1);
	screenRect.setBottom(screenRect.bottom() - 1);
	screenRect.setRight(screenRect.right() - 1);
	setGeometry(screenRect);
}

qreal PDFDocument::zoomSliderPosToScale(int pos)
{
	if (pos == 0)
		return 1.0;
	if (pos < 0) {
		return (1 - kMinScaleFactor) / abs(zoomSlider->minimum() + 10) * (pos + 10) + 1;
	} else {
		return (kMaxScaleFactor - 1) / (zoomSlider->maximum() - 10) * (pos - 10) + 1;
	}
}

int PDFDocument::scaleToZoomSliderPos(qreal scale)
{
	if (scale < 1.01 && scale > 0.99)
		return 0;
	if (scale < 1) {
		return (scale - 1) / (1 - kMinScaleFactor) * abs(zoomSlider->minimum() + 10) - 10;
	} else {
		return (scale - 1) / (kMaxScaleFactor - 1) * (zoomSlider->maximum() - 10) + 10;
	}
}

void PDFDocument::zoomSliderChange(int pos)
{
	if (pos > -10 && pos < 10) {
		pos = 0;
		zoomSlider->setValue(pos);
	}
	widget()->zoom(zoomSliderPosToScale(pos));
}


void PDFDocument::showPage(int page)
{
	//Q_ASSERT(document);
	if (document.isNull()) return;
	int p = page; //-pdfWidget->getPageOffset();
	if (p < 1)
		p = 1;
	int p2 = page + pdfWidget->visiblePages() - 1 - pdfWidget->getPageOffset();
	if (pdfWidget->visiblePages() <= 1) pageLabel->setText(tr("Page %1 of %2").arg(p).arg(pdfWidget->realNumPages()));
	else pageLabel->setText(tr("Pages %1 to %2 of %3").arg(p).arg(p2).arg(pdfWidget->realNumPages()));
	pageCountLabel->setText(QString("%1").arg(pdfWidget->realNumPages()));

	leCurrentPage->setText(QString("%1").arg(p));
}

void PDFDocument::showScale(qreal scale)
{
	QString scaleString = QString("%1%").arg(qRound(scale * 100.0));
	scaleButton->setText(scaleString);
	zoomSlider->blockSignals(true);
	// don't emit value changed: This is only used to update the value. It does not initiate changes
	zoomSlider->setValue(scaleToZoomSliderPos(scale));
	zoomSlider->blockSignals(false);
}

void PDFDocument::goToSource()
{
	Q_ASSERT(pdfWidget);
	if (!pdfWidget) return;
	pdfWidget->syncCurrentPage(true);
}

void PDFDocument::fileOpen()
{
	QString newFile = FileDialog::getOpenFileName(this, tr("Open PDF"), curFile, "PDF (*.pdf);;All files (*)");
	if (newFile.isEmpty()) return;
	loadFile(newFile, QFileInfo(), NoDisplayFlags);
}

void PDFDocument::enablePageActions(int pageIndex, bool sync)
{
	//current page has changed
	if (document.isNull())
		return;

	Q_ASSERT(pdfWidget && globalConfig);
	if (!pdfWidget || !globalConfig) return;

	//#ifndef Q_OS_MAC
	// On Mac OS X, disabling these leads to a crash if we hit the end of document while auto-repeating a key
	// (seems like a Qt bug, but needs further investigation)
	// 2008-09-07: seems to no longer be a problem, probably thanks to Qt 4.4 update
	actionFirst_Page->setEnabled(pageIndex > 0);
	actionPrevious_Page->setEnabled(pageIndex > 0);
	actionNext_Page->setEnabled(pageIndex < pdfWidget->realNumPages() - 1);
	actionLast_Page->setEnabled(pageIndex < pdfWidget->realNumPages() - 1);

	actionBack->setEnabled(pdfWidget->currentPageHistoryIndex() > 0);
	actionForward->setEnabled(pdfWidget->currentPageHistoryIndex() < pdfWidget->currentPageHistory().size() - 1);

	//#endif

	sync = sync && !syncToSourceBlocked;
	if (globalConfig->followFromScroll && sync)
		pdfWidget->syncCurrentPage(false);
	if (actionSynchronize_multiple_views->isChecked() && sync)
		emit syncView(curFile, masterFile, widget()->getPageIndex());;
}

void PDFDocument::enableZoomActions(qreal scaleFactor)
{
	actionZoom_In->setEnabled(scaleFactor < kMaxScaleFactor);
	actionZoom_Out->setEnabled(scaleFactor > kMinScaleFactor);
}

void PDFDocument::adjustScaleActions(autoScaleOption scaleOption)
{
	actionFit_to_Window->setChecked(scaleOption == kFitWindow);
	actionFit_to_Width->setChecked(scaleOption == kFitWidth);
	actionFit_to_Text_Width->setChecked(scaleOption == kFitTextWidth);
	Q_ASSERT(scrollArea);
	if (scaleOption == kFitWidth) {
		if (scrollArea->horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
			scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		int minheight = scrollArea->viewport()->height();
		int maxheight = scrollArea->viewport()->height();
		if (scrollArea->horizontalScrollBar()->isVisible())
			maxheight += scrollArea->horizontalScrollBar()->height() + 5;
		else
			minheight -= scrollArea->horizontalScrollBar()->height() + 5;
		if (pdfWidget->height() < minheight) {
			if (scrollArea->verticalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
				scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		} else if (pdfWidget->height() > maxheight) {
			if (scrollArea->verticalScrollBarPolicy() != Qt::ScrollBarAlwaysOn)
				scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		}
	} else if (scaleOption == kFitWindow) {
		if (scrollArea->horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
			scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		if (scrollArea->verticalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
			scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	} else {
		if (scrollArea->horizontalScrollBarPolicy() != Qt::ScrollBarAsNeeded)
			scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		if (scrollArea->verticalScrollBarPolicy() != Qt::ScrollBarAsNeeded)
			scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	}
}

void PDFDocument::toggleFullScreen(bool fullscreen)
{
	bool presentation = false;
	if (fullscreen) {
		// entering full-screen mode
		statusBar()->hide();
		toolBar->hide();
		globalConfig->windowMaximized = isMaximized();
		showFullScreen();
		pdfWidget->saveState();
		pdfWidget->fitWindow(true);
		dwVisOutline = dwOutline->isVisible();
		dwVisOverview = dwOverview->isVisible();
		dwVisFonts = dwFonts->isVisible();
		dwVisSearch = dwSearch->isVisible();
		dwVisInfo = dwInfo->isVisible();
		if (sender() == actionPresentation) {
			menuBar()->hide();
			actionFull_Screen->setChecked(false);
			actionPresentation->setChecked(true);
			exitFullscreen = new QShortcut(Qt::Key_Escape, this, SLOT(closeElement())); //hiding the menubar disables normal shortcut
			pdfWidget->setTool(kPresentation);
			pdfWidget->setContextMenuPolicy(Qt::NoContextMenu);
			dwOutline->hide();
			dwFonts->hide();
			dwSearch->hide();
			dwInfo->hide();
			dwOverview->hide();
			presentation = true;
			if (actionContinuous->isChecked()) {
				actionContinuous->setChecked(false);
				wasContinuous = true;
			} else wasContinuous = false;
		} else
			actionFull_Screen->setChecked(true);

		//actionFull_Screen->setChecked(true);
	} else {
		// exiting full-screen mode
		statusBar()->show();
		toolBar->show();
		if (globalConfig->windowMaximized)
			showMaximized();
		else
			showNormal();
		pdfWidget->restoreState();
		actionFull_Screen->setChecked(false);
	}
	if (!presentation) { //disable presentation things that are neither used in fullscreen nor normal mode
		menuBar()->show();
		actionPresentation->setChecked(false);
		pdfWidget->setTool(toolButtonGroup->checkedId());
		pdfWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
		if (exitFullscreen) {
			delete exitFullscreen;
			exitFullscreen = 0;
		}
		if (wasContinuous) actionContinuous->setChecked(true);
	}
}

void PDFDocument::resetMagnifier()
{
	pdfWidget->resetMagnifier();
}

void PDFDocument::zoomFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;

	bool ok;
	int factor = act->data().toInt(&ok);
	if (!ok) { // old combobox
		QString text = act->text();
		text.chop(1);
		factor = text.toInt(&ok);
	}
	if (ok) {
		pdfWidget->fixedScale(0.01 * factor);
	}

	if (comboZoom)
		comboZoom->setDefaultAction(act);
}

void PDFDocument::setResolution(int res)
{
	if (res > 0)
		pdfWidget->setResolution(res);
}

void PDFDocument::goToDestination(const QString &destName)
{
	if (pdfWidget)
		pdfWidget->goToDestination(destName);
}

void PDFDocument::goToPage(const int page)
{
	if (pdfWidget && scrollArea)
		scrollArea->goToPage(page);
}

void PDFDocument::focus()
{
	widget()->setFocus();
	if (!embeddedMode) {
		raise();
		activateWindow();
	}
}

void PDFDocument::dragEnterEvent(QDragEnterEvent *event)
{
	// Only accept files for now
	event->ignore();
	if (event->mimeData()->hasUrls()) {
		const QList<QUrl> urls = event->mimeData()->urls();
		foreach (const QUrl &url, urls) {
			if (url.scheme() == "file") {
				event->acceptProposedAction();
				break;
			}
		}
	}
}

void PDFDocument::dropEvent(QDropEvent *event)
{
	event->ignore();
	if (event->mimeData()->hasUrls()) {
		const QList<QUrl> urls = event->mimeData()->urls();
		foreach (const QUrl &url, urls)
			if (url.scheme() == "file") {
				if (url.path().endsWith("pdf")) loadFile(url.toLocalFile());
				else emit fileDropped(url);
			}
		event->acceptProposedAction();
	}
}

void PDFDocument::enterEvent(QEvent *event)
{
	if (event->type() == QEvent::Enter
	        && embeddedMode
	        && globalConfig->autoHideToolbars) {
		showToolbarsDelayed();
	}
}

void PDFDocument::leaveEvent(QEvent *event)
{
	if (event->type() == QEvent::Leave
	        && embeddedMode
	        && globalConfig->autoHideToolbars) {
		hideToolbars();
	}
}

void PDFDocument::mouseMoveEvent(QMouseEvent *event)
{
	if (embeddedMode && globalConfig->autoHideToolbars) {
		int h = toolBar->height() + 5;
		if (event->pos().y() < h || event->pos().y() > this->height() - h) {
			showToolbarsDelayed();
		} else {
			hideToolbars();
		}
	}
}

void PDFDocument::doFindDialog(const QString command)
{
	if (!dwSearch) return;
	dwSearch->show();
	dwSearch->setFocus();
	if (!command.isEmpty())
		dwSearch->setSearchText(command);
}

void PDFDocument::doFindAgain()
{
	search(false, false);
}

void PDFDocument::printPDF()
{
	if (document.isNull())
		return;

	QString command;
	// texmaker 3.0.1 solution
	unsigned int firstPage, lastPage;
	QPrinter printer(QPrinter::HighResolution);
	QPrintDialog printDlg(&printer, this);
	printer.setDocName(fileName());
	printDlg.setMinMax(1, pdfWidget->realNumPages());
	printDlg.setFromTo(1, pdfWidget->realNumPages());
	printDlg.setOption(QAbstractPrintDialog::PrintToFile, false);
	printDlg.setOption(QAbstractPrintDialog::PrintSelection, false);
	printDlg.setOption(QAbstractPrintDialog::PrintPageRange, true);
	printDlg.setOption(QAbstractPrintDialog::PrintCollateCopies, false);

	printDlg.setWindowTitle(tr("Print"));
	if (printDlg.exec() != QDialog::Accepted) return;
	switch (printDlg.printRange()) {
	case QAbstractPrintDialog::PageRange:
		firstPage = printDlg.fromPage();
		lastPage = printDlg.toPage();
		break;
	default:
		firstPage = 1;
		lastPage = pdfWidget->realNumPages();
	}

	if (!printer.printerName().isEmpty()) {
#ifdef Q_OS_WIN32
		QString paper;
		switch (printer.paperSize()) {
		case QPrinter::A0:
			paper = "a0";
			break;
		case QPrinter::A1:
			paper = "a1";
			break;
		case QPrinter::A2:
			paper = "a2";
			break;
		case QPrinter::A3:
			paper = "a3";
			break;
		case QPrinter::A4:
			paper = "a4";
			break;
		case QPrinter::A5:
			paper = "a5";
			break;
		case QPrinter::A6:
			paper = "a6";
			break;
		case QPrinter::B0:
			paper = "isob0";
			break;
		case QPrinter::B1:
			paper = "isob1";
			break;
		case QPrinter::B2:
			paper = "isob2";
			break;
		case QPrinter::B3:
			paper = "isob3";
			break;
		case QPrinter::B4:
			paper = "isob4";
			break;
		case QPrinter::B5:
			paper = "isob5";
			break;
		case QPrinter::B6:
			paper = "isob6";
			break;
		case QPrinter::Letter:
			paper = "letter";
			break;
		case QPrinter::Ledger:
			paper = "ledger";
			break;
		case QPrinter::Legal:
			paper = "legal";
			break;
		default:
			paper = "a4";
		}

		QStringList args;
		args << "txs:///gs";
		args << "-sDEVICE=mswinpr2";
		args << QString("-sOutputFile=\"\%printer\%%1\"").arg(printer.printerName().replace(" ", "_"));
		args << "-dBATCH";
		args << "-dNOPAUSE";
		args << "-dQUIET";
		args << "-dNoCancel";
		args << "-sPAPERSIZE=" + paper;
		args << "-dFirstPage=" + QString::number(firstPage);
		args << "-dLastPage=" + QString::number(lastPage);
#else
		QStringList args;
		args << "lp";
		args << QString("-d %1").arg(printer.printerName().replace(" ", "_"));
		//args << QString("-n %1").arg(printer.numCopies());
		//  args << QString("-t \"%1\"").arg(printer.docName());
		args << QString("-P %1-%2").arg(firstPage).arg(lastPage);
		switch (printer.duplex()) {
		case QPrinter::DuplexNone:
			args << "-o sides=one-sided";
			break;
		case QPrinter::DuplexShortSide:
			args << "-o sides=two-sided-short-edge";
			break;
		case QPrinter::DuplexLongSide:
			args << "-o sides=two-sided-long-edge";
			break;
		default:
			break;
		}
		args << "--";
#endif
		args << "\"?am.pdf\"";
		command = args.join(" ");
	} else return;

	for (int i = 0; i < printer.numCopies(); i++)
		emit runCommand(command, masterFile, masterFile, 0);
}

void PDFDocument::setAutoHideToolbars(bool enabled)
{
	setToolbarsVisible(!enabled);
	actionAutoHideToolbars->setChecked(enabled);
	// since we want to have the MouseMoveEvent down at the pdfWidget (internally e.g. for magnifier) up to
	// the window (for toolbar hiding) all widgets in between seem to need MouseTracking enabled. Otherwise
	// they will swallow the move event.
	QWidget *w = pdfWidget;
	while (w) {
		w->setMouseTracking(enabled);
		w = w->parentWidget();
	}
}

// hide toolbars while preserving the position of the PDF content on screen
//   we have to compensate the change of scrollArea position by scrolling its content
void PDFDocument::hideToolbars()
{
	toolBarTimer->stop();
	if (toolBar->isVisible()) {
		setToolbarsVisible(false);
		// workaround: the method of checking the change in globalPos of the scrollArea (as in enterEvent)
		// does not work here (positions are not yet updated after hiding the toolbars)
		if (!toolBar->isFloating() && toolBar->orientation() == Qt::Horizontal) {
			scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->value() - toolBar->height());
		}
	}
}

// hide toolbars while preserving the position of the PDF content on screen
//   we have to compensate the change of scrollArea position by scrolling its content
void PDFDocument::showToolbars()
{
	if (!toolBar->isVisible()) {
		QPoint widgetPos = scrollArea->mapToGlobal(QPoint(0, 0));
		setToolbarsVisible(true);
		QPoint posChange = scrollArea->mapToGlobal(QPoint(0, 0)) - widgetPos;
		scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->value() + posChange.y());
	}
}

void PDFDocument::showToolbarsDelayed()
{
	if (!toolBarTimer->isActive())
		toolBarTimer->start(200);
}

void PDFDocument::setToolbarIconSize(int sz)
{
	toolBar->setIconSize(QSize(sz, sz));
	// statusbar
	foreach (QObject *c, statusbar->children()) {
		QAbstractButton *bt = qobject_cast<QAbstractButton *>(c);
		if (bt) {
			bt->setIconSize(QSize(sz, sz));
		}
	}
}

void PDFDocument::showMessage(const QString &text)
{
	QAction *closeAction = new QAction(tr("Close"), this);
	closeAction->setToolTip(tr("Close Message"));
	connect(closeAction, SIGNAL(triggered()), messageFrame, SLOT(hide()));
	messageFrame->showText(text, QList<QAction *>() << closeAction);
}

void PDFDocument::setToolbarsVisible(bool visible)
{
	toolBar->setVisible(visible);
	statusbar->setVisible(visible);
}

void PDFDocument::splitMergeTool()
{
	PDFSplitMergeTool *psmt = new PDFSplitMergeTool(0, fileName());
	connect(psmt, SIGNAL(runCommand(QString, QFileInfo, QFileInfo, int)), SIGNAL(runCommand(QString, QFileInfo, QFileInfo, int)));
	psmt->show();
}

#endif  // ndef NO_POPPLER_PREVIEW
