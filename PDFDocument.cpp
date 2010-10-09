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

#include "PDFDocument.h"
//#include "TeXDocument.h"
#include "PDFDocks.h"
//#include "FindDialog.h"

#include <QDockWidget>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QPainter>
#include <QPaintEngine>
#include <QLabel>
#include <QScrollArea>
#include <QStyle>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QRegion>
#include <QVector>
#include <QList>
#include <QStack>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QShortcut>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QToolTip>

#include <math.h>

//#include "GlobalParams.h"

#include "poppler-link.h"

#define SYNCTEX_GZ_EXT	".synctex.gz"
#define SYNCTEX_EXT		".synctex"

#define ROUND(x) floor((x)+0.5)

const qreal kMaxScaleFactor = 8.0;
const qreal kMinScaleFactor = 0.125;

const int magSizes[] = { 200, 300, 400 };

// tool codes
const int kNone = 0;
const int kMagnifier = 1;
const int kScroll = 2;
const int kSelectText = 3;
const int kSelectImage = 4;

// duration of highlighting in PDF view (might make configurable?)
const int kPDFHighlightDuration = 2000;

#pragma mark === PDFMagnifier ===

const int kMagFactor = 2;

PDFMagnifier::PDFMagnifier(QWidget *parent, qreal inDpi)
	: QLabel(parent)
	, page(NULL)
	, scaleFactor(kMagFactor)
	, parentDpi(inDpi)
	, imageDpi(0)
	, imagePage(NULL)
{
}

void PDFMagnifier::setPage(Poppler::Page *p, qreal scale)
{
	page = p;
	scaleFactor = scale * kMagFactor;
	if (page == NULL) {
		imagePage = NULL;
		image = QImage();
	}
	else {
		PDFWidget* parent = qobject_cast<PDFWidget*>(parentWidget());
		if (parent != NULL) {
			QWidget* viewport = parent->parentWidget();
			if (viewport != NULL) {
				qreal dpi = parentDpi * scaleFactor;
				QPoint tl = parent->mapFromParent(viewport->rect().topLeft());
				QPoint br = parent->mapFromParent(viewport->rect().bottomRight());
				QSize  size = QSize(br.x() - tl.x(), br.y() - tl.y()) * kMagFactor;
				QPoint loc = tl * kMagFactor;
				if (page != imagePage || dpi != imageDpi || loc != imageLoc || size != imageSize)
					image = page->renderToImage(dpi, dpi, loc.x(), loc.y(), size.width(), size.height());
				imagePage = page;
				imageDpi = dpi;
				imageLoc = loc;
				imageSize = size;
			}
		}
	}
	update();
}

void PDFMagnifier::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFrame(&painter);
	painter.drawImage(event->rect(), image,
		event->rect().translated((x() * kMagFactor - imageLoc.x()) + width() / 2,
								 (y() * kMagFactor - imageLoc.y()) + height() / 2));
}

void PDFMagnifier::resizeEvent(QResizeEvent * /*event*/)
{
/*TODO	QSETTINGS_OBJECT(settings);
	if (settings.value("circularMagnifier", kDefault_CircularMagnifier).toBool()) {
		int side = qMin(width(), height());
		QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side, side, QRegion::Ellipse);
		setMask(maskedRegion);
	}*/
}

#pragma mark === PDFWidget ===

QCursor *PDFWidget::magnifierCursor = NULL;
QCursor *PDFWidget::zoomInCursor = NULL;
QCursor *PDFWidget::zoomOutCursor = NULL;

PDFWidget::PDFWidget()
	: QLabel()
	, document(NULL)
	, page(NULL)
	, clickedLink(NULL)
	, pageIndex(0)
	, scaleFactor(1.0)
	, dpi(72.0)
	, scaleOption(kFixedMag)
	, magnifier(NULL)
	, usingTool(kNone)
{
/*TODO	QSETTINGS_OBJECT(settings);
	dpi = settings.value("previewResolution", QApplication::desktop()->logicalDpiX()).toInt();
	
	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setFocusPolicy(Qt::StrongFocus);
	setScaledContents(true);
	setMouseTracking(true);

	switch (settings.value("scaleOption", kDefault_PreviewScaleOption).toInt()) {
		default:
			fixedScale(1.0);
			break;
		case 2:
			fitWidth(true);
			break;
		case 3:
			fitWindow(true);
			break;
		case 4:
			fixedScale(settings.value("previewScale", kDefault_PreviewScale).toInt() / 100.0);
			break;
	}*/
fixedScale(1.0);
	if (magnifierCursor == NULL) {
		magnifierCursor = new QCursor(QPixmap(":/images/images/magnifiercursor.png"));
		zoomInCursor = new QCursor(QPixmap(":/images/images/zoomincursor.png"));
		zoomOutCursor = new QCursor(QPixmap(":/images/images/zoomoutcursor.png"));
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
	
	shortcutUp = new QShortcut(QKeySequence("Up"), this, SLOT(upOrPrev()));
	shortcutLeft = new QShortcut(QKeySequence("Left"), this, SLOT(leftOrPrev()));
	shortcutDown = new QShortcut(QKeySequence("Down"), this, SLOT(downOrNext()));
	shortcutRight = new QShortcut(QKeySequence("Right"), this, SLOT(rightOrNext()));

	highlightRemover.setSingleShot(true);
	connect(&highlightRemover, SIGNAL(timeout()), this, SLOT(clearHighlight()));
}

PDFWidget::~PDFWidget()
{
	if (page)
		delete page;
}

void PDFWidget::setDocument(Poppler::Document *doc)
{
	document = doc;
	reloadPage();
}

void PDFWidget::windowResized()
{
	switch (scaleOption) {
		case kFixedMag:
			break;
		case kFitWidth:
			fitWidth(true);
			break;
		case kFitWindow:
			fitWindow(true);
			break;
	}
	update();
}

void PDFWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFrame(&painter);

	qreal newDpi = dpi * scaleFactor;
	QRect newRect = rect();
	if (page != imagePage || newDpi != imageDpi || newRect != imageRect)
		if (page != NULL)
			image = page->renderToImage(dpi * scaleFactor, dpi * scaleFactor,
						rect().x(), rect().y(), rect().width(), rect().height());
	imagePage = page;
	imageDpi = newDpi;
	imageRect = newRect;

	painter.drawImage(event->rect(), image, event->rect());

	if (!highlightPath.isEmpty()) {
		painter.setRenderHint(QPainter::Antialiasing);
		painter.scale(dpi / 72.0 * scaleFactor, dpi / 72.0 * scaleFactor);
		painter.setPen(QColor(0, 0, 0, 0));
		painter.setBrush(QColor(255, 255, 0, 63));
		painter.drawPath(highlightPath);
	}
}

void PDFWidget::useMagnifier(const QMouseEvent *inEvent)
{
	if (!magnifier) {
		magnifier = new PDFMagnifier(this, dpi);
		/*TODOQSETTINGS_OBJECT(settings);
		int magnifierSize = settings.value("magnifierSize", kDefault_MagnifierSize).toInt();
		if (magnifierSize <= 0 || magnifierSize > (int)(sizeof(magSizes) / sizeof(int)))
			magnifierSize = kDefault_MagnifierSize;
		magnifierSize = magSizes[magnifierSize - 1];
		magnifier->setFixedSize(magnifierSize * 4 / 3, magnifierSize);*/
	}
	magnifier->setPage(page, scaleFactor);
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
	clickedLink = NULL;
	
	if (event->button() != Qt::LeftButton) {
		QWidget::mousePressEvent(event);
		return;
	}

	mouseDownModifiers = event->modifiers();
	if (mouseDownModifiers & Qt::ControlModifier) {
		// ctrl key - this is a sync click, don't handle the mouseDown here
	}
	else {
		// check for click in link
		foreach (Poppler::Link* link, page->links()) {
			// poppler's linkArea is relative to the page rect, it seems
			QPointF scaledPos(event->pos().x() / scaleFactor / dpi * 72.0 / page->pageSizeF().width(),
								event->pos().y() / scaleFactor / dpi * 72.0 / page->pageSizeF().height());
			if (link->linkArea().contains(scaledPos)) {
				clickedLink = link;
				break;
			}
		}
		if (clickedLink == NULL) {
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
	event->accept();
}

void PDFWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (clickedLink != NULL) {
		QPointF scaledPos(event->pos().x() / scaleFactor / dpi * 72.0 / page->pageSizeF().width(),
							event->pos().y() / scaleFactor / dpi * 72.0 / page->pageSizeF().height());
		if (clickedLink->linkArea().contains(scaledPos)) {
			doLink(clickedLink);
		}
	}
	else {
		switch (usingTool) {
			case kNone:
				// Ctrl-click to sync
				if (mouseDownModifiers & Qt::ControlModifier) {
					if (event->modifiers() & Qt::ControlModifier) {
						QPointF pagePos(event->pos().x() / scaleFactor * 72.0 / dpi,
										event->pos().y() / scaleFactor * 72.0 / dpi);
						emit syncClick(pageIndex, pagePos);
					}
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
	clickedLink = NULL;
	usingTool = kNone;
	updateCursor(event->pos());
	event->accept();
}

void PDFWidget::goToDestination(const Poppler::LinkDestination& dest)
{
	if (dest.pageNumber() > 0) {
		goToPage(dest.pageNumber() - 1);
		if (dest.isChangeZoom()) {
			// FIXME
		}
		QScrollArea*	scrollArea = getScrollArea();
		if (scrollArea) {
			if (dest.isChangeLeft()) {
				int destLeft = (int)floor(dest.left() * scaleFactor * dpi / 72.0 * page->pageSizeF().width());
				scrollArea->horizontalScrollBar()->setValue(destLeft);
			}
			if (dest.isChangeTop()) {
				int destTop = (int)floor(dest.top() * scaleFactor * dpi / 72.0 * page->pageSizeF().height());
				scrollArea->verticalScrollBar()->setValue(destTop);
			}
		}
	}
}

void PDFWidget::goToDestination(const QString& destName)
{
	const Poppler::LinkDestination *dest = document->linkDestination(destName);
	if (dest)
		goToDestination(*dest);
}

void PDFWidget::doLink(const Poppler::Link *link)
{
	switch (link->linkType()) {
		case Poppler::Link::None:
			break;
		case Poppler::Link::Goto:
			{
				const Poppler::LinkGoto *go = dynamic_cast<const Poppler::LinkGoto*>(link);
				Q_ASSERT(go != NULL);
				if (go->isExternal()) {
					QString file = go->fileName();
					break; // FIXME -- we don't handle this yet!
				}
				goToDestination(go->destination());
			}
			break;
		case Poppler::Link::Browse:
			{
				const Poppler::LinkBrowse *browse = dynamic_cast<const Poppler::LinkBrowse*>(link);
				Q_ASSERT(browse != NULL);
				QUrl url = QUrl::fromEncoded(browse->url().toAscii());
				if (url.scheme() == "file") {
					PDFDocument *doc = qobject_cast<PDFDocument*>(window());
					if (doc) {
						QFileInfo fi(QFileInfo(doc->fileName()).canonicalPath(), url.toLocalFile());
						url = QUrl::fromLocalFile(fi.canonicalFilePath());
					}
				}
				//TODO TWApp::instance()->openUrl(url);
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
		case kMagnifier:
			{
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
			break;

		case kScroll:
			{
				QPoint delta = event->globalPos() - scrollClickPos;
				scrollClickPos = event->globalPos();
				QScrollArea*	scrollArea = getScrollArea();
				if (scrollArea) {
					int oldX = scrollArea->horizontalScrollBar()->value();
					scrollArea->horizontalScrollBar()->setValue(oldX - delta.x());
					int oldY = scrollArea->verticalScrollBar()->value();
					scrollArea->verticalScrollBar()->setValue(oldY - delta.y());
				}
			}
			break;
		
		default:
			break;
	}
	event->accept();
}

void PDFWidget::keyPressEvent(QKeyEvent *event)
{
	updateCursor(mapFromGlobal(QCursor::pos()));
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
	QMenu	menu(this);

	PDFDocument *pdfDoc = qobject_cast<PDFDocument*>(window());
	if (pdfDoc && pdfDoc->hasSyncData()) {
		QAction *act = new QAction(tr("Jump to Source"), &menu);
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

	QAction *action = menu.exec(event->globalPos());

	if (action == ctxZoomInAction)
		doZoom(event->pos(), 1);
	else if (action == ctxZoomOutAction)
		doZoom(event->pos(), -1);
}

void PDFWidget::jumpToSource()
{
	QAction *act = qobject_cast<QAction*>(sender());
	if (act != NULL) {
		QPoint eventPos = act->data().toPoint();
		QPointF pagePos(eventPos.x() / scaleFactor * 72.0 / dpi,
						eventPos.y() / scaleFactor * 72.0 / dpi);
		emit syncClick(pageIndex, pagePos);
	}
}

void PDFWidget::wheelEvent(QWheelEvent *event)
{
	static QTime lastScrollTime = QTime::currentTime();
	bool mayChangePage = true;
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;
	QScrollBar *scrollBar = (event->orientation() == Qt::Horizontal)
				? getScrollArea()->horizontalScrollBar()
				: getScrollArea()->verticalScrollBar();
	if (scrollBar->minimum() < scrollBar->maximum()) {
		int oldValue = scrollBar->value();
		scrollBar->setValue(scrollBar->value() - numSteps * scrollBar->singleStep());
		if (scrollBar->value() != oldValue) {
			lastScrollTime = QTime::currentTime();
			mayChangePage = false;
		}
		if (QTime::currentTime() < lastScrollTime.addMSecs(500))
			mayChangePage = false;
	}
	if (mayChangePage) {
		if (event->delta() > 0 && pageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
		else if (event->delta() < 0 && pageIndex < document->numPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
		lastScrollTime = QTime::currentTime();
	}
	event->accept();
}

void PDFWidget::setTool(int tool)
{
	currentTool = tool;
	updateCursor();
}

void PDFWidget::updateCursor()
{
	if (usingTool != kNone)
		return;

	switch (currentTool) {
		case kScroll:
			setCursor(Qt::OpenHandCursor);
			break;
		case kMagnifier:
			{
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

void PDFWidget::updateCursor(const QPoint& pos)
{
	// check for link
	foreach (Poppler::Link* link, page->links()) {
		// poppler's linkArea is relative to the page rect
		QPointF scaledPos(pos.x() / scaleFactor / dpi * 72.0 / page->pageSizeF().width(),
							pos.y() / scaleFactor / dpi * 72.0 / page->pageSizeF().height());
		if (link->linkArea().contains(scaledPos)) {
			setCursor(Qt::PointingHandCursor);
			if (link->linkType() == Poppler::Link::Browse) {
				QPoint globalPos = mapToGlobal(pos);
				const Poppler::LinkBrowse *browse = dynamic_cast<const Poppler::LinkBrowse*>(link);
				Q_ASSERT(browse != NULL);
				QRectF r = link->linkArea();
				r.setWidth(r.width() * scaleFactor * dpi / 72.0 * page->pageSizeF().width());
				r.setHeight(r.height() * scaleFactor * dpi / 72.0 * page->pageSizeF().height());
				r.moveLeft(r.left() * scaleFactor * dpi / 72.0 * page->pageSizeF().width());
				r.moveTop(r.top() * scaleFactor * dpi / 72.0 * page->pageSizeF().height());
				QRect rr = r.toRect().normalized();
				rr.setTopLeft(mapToGlobal(rr.topLeft()));
				QToolTip::showText(globalPos, browse->url(), this, rr);
			}
			return;
		}
	}
	updateCursor();
}

void PDFWidget::adjustSize()
{
	if (page) {
		QSize	pageSize = (page->pageSizeF() * scaleFactor * dpi / 72.0).toSize();
		if (pageSize != size())
			resize(pageSize);
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

void PDFWidget::setHighlightPath(const QPainterPath& path)
{
	highlightRemover.stop();
	highlightPath = path;
	if (!path.isEmpty()) {
		QScrollArea*	scrollArea = getScrollArea();
		if (scrollArea) {
			QRectF r = path.boundingRect();
			scrollArea->ensureVisible((int)((r.left() + r.right()) / 2 * dpi / 72 * scaleFactor),
										(int)((r.top() + r.bottom()) / 2 * dpi / 72 * scaleFactor));
		}
		if (kPDFHighlightDuration > 0)
			highlightRemover.start(kPDFHighlightDuration);
	}
}

void PDFWidget::clearHighlight()
{
	highlightPath = QPainterPath();
	update();
}

void PDFWidget::reloadPage()
{
	if (page != NULL)
		delete page;
	page = NULL;
	if (magnifier != NULL)
		magnifier->setPage(NULL, 0);
	imagePage = NULL;
	image = QImage();
	highlightPath = QPainterPath();
	if (document != NULL) {
		if (pageIndex >= document->numPages())
			pageIndex = document->numPages() - 1;
		if (pageIndex >= 0)
			page = document->page(pageIndex);
	}
	adjustSize();
	update();
	updateStatusBar();
	emit changedPage(pageIndex);
}

void PDFWidget::updateStatusBar()
{
	QWidget *widget = window();
	PDFDocument *doc = qobject_cast<PDFDocument*>(widget);
	if (doc) {
		doc->showPage(pageIndex + 1);
		doc->showScale(scaleFactor);
	}
}

void PDFWidget::goFirst()
{
	if (pageIndex != 0) {
		pageIndex = 0;
		reloadPage();
		update();
	}
}

void PDFWidget::goPrev()
{
	if (pageIndex > 0) {
		--pageIndex;
		reloadPage();
		update();
	}
}

void PDFWidget::goNext()
{
	if (document != NULL && pageIndex < document->numPages() - 1) {
		++pageIndex;
		reloadPage();
		update();
	}
}

void PDFWidget::goLast()
{
	if (document != NULL && pageIndex != document->numPages() - 1) {
		pageIndex = document->numPages() - 1;
		reloadPage();
		update();
	}
}

void PDFWidget::upOrPrev()
{
	if (document == NULL)
		return;
	QScrollBar*		scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepSub);
	else {
		if (pageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	shortcutUp->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
}

void PDFWidget::leftOrPrev()
{
	if (document == NULL)
		return;
	QScrollBar*		scrollBar = getScrollArea()->horizontalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepSub);
	else {
		if (pageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	shortcutLeft->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
}

void PDFWidget::downOrNext()
{
	if (document == NULL)
		return;
	QScrollBar*		scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
	else {
		if (pageIndex < document->numPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	shortcutDown->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
}

void PDFWidget::rightOrNext()
{
	if (document == NULL)
		return;
	QScrollBar*		scrollBar = getScrollArea()->horizontalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
	else {
		if (pageIndex < document->numPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	shortcutRight->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
}

void PDFWidget::doPageDialog()
{
	if (document == NULL)
		return;
	bool ok;
	setCursor(Qt::ArrowCursor);
	int pageNo = QInputDialog::getInteger(this, tr("Go to Page"),
									tr("Page number:"), pageIndex + 1,
									1, document->numPages(), 1, &ok);
	if (ok)
		goToPage(pageNo - 1);
}

void PDFWidget::goToPage(int p)
{
	if (p != pageIndex && document != NULL) {
		if (p >= 0 && p < document->numPages()) {
			pageIndex = p;
			reloadPage();
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
		QScrollArea*	scrollArea = getScrollArea();
		if (scrollArea && page != NULL) {
			qreal portWidth = scrollArea->viewport()->width();
			QSizeF	pageSize = page->pageSizeF() * dpi / 72.0;
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
	}
	else
		scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);
}

void PDFWidget::fitWindow(bool checked)
{
	if (checked) {
		scaleOption = kFitWindow;
		QScrollArea*	scrollArea = getScrollArea();
		if (scrollArea && page != NULL) {
			qreal portWidth = scrollArea->viewport()->width();
			qreal portHeight = scrollArea->viewport()->height();
			QSizeF	pageSize = page->pageSizeF() * dpi / 72.0;
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
	}
	else
		scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);
}

void PDFWidget::doZoom(const QPoint& clickPos, int dir) // dir = 1 for in, -1 for out
{
	QPointF pagePos(clickPos.x() / scaleFactor * 72.0 / dpi,
					clickPos.y() / scaleFactor * 72.0 / dpi);
	scaleOption = kFixedMag;
	emit changedScaleOption(scaleOption);

	QPoint globalPos = mapToGlobal(clickPos);
	if (dir > 0 && scaleFactor < kMaxScaleFactor) {
		scaleFactor *= sqrt(2.0);
		if (fabs(scaleFactor - ROUND(scaleFactor)) < 0.01)
			scaleFactor = ROUND(scaleFactor);
		if (scaleFactor > kMaxScaleFactor)
			scaleFactor = kMaxScaleFactor;
	}
	else if (dir < 0 && scaleFactor > kMinScaleFactor) {
		scaleFactor /= sqrt(2.0);
		if (fabs(scaleFactor - ROUND(scaleFactor)) < 0.01)
			scaleFactor = ROUND(scaleFactor);
		if (scaleFactor < kMinScaleFactor)
			scaleFactor = kMinScaleFactor;
	}
	else
		return;

	adjustSize();
	update();
	updateStatusBar();
	emit changedZoom(scaleFactor);
	QPoint localPos = mapFromGlobal(globalPos);
	QPoint pageToLocal(int(pagePos.x() * scaleFactor / 72.0 * dpi),
						int(pagePos.y() * scaleFactor / 72.0 * dpi));
	QScrollArea*	scrollArea = getScrollArea();
	if (scrollArea) {
		QScrollBar* hs = scrollArea->horizontalScrollBar();
		if (hs != NULL)
			hs->setValue(hs->value() + pageToLocal.x() - localPos.x());
		QScrollBar* vs = scrollArea->verticalScrollBar();
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

QScrollArea* PDFWidget::getScrollArea()
{
	QWidget* parent = parentWidget();
	if (parent != NULL)
		return qobject_cast<QScrollArea*>(parent->parentWidget());
	else
		return NULL;
}


#pragma mark === PDFDocument ===

QList<PDFDocument*> PDFDocument::docList;

PDFDocument::PDFDocument(const QString &fileName, TeXDocument *texDoc)
	: watcher(NULL), reloadTimer(NULL), scanner(NULL), openedManually(false)
{
	init();

	if (texDoc == NULL) {
		openedManually = true;
/*TODO		watcher = new QFileSystemWatcher(this);
		connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(reloadWhenIdle()));*/
	}

	loadFile(fileName);

/*TODO	QMap<QString,QVariant> properties = TWApp::instance()->getFileProperties(curFile);
	if (properties.contains("geometry"))
		restoreGeometry(properties.value("geometry").toByteArray());
	else
		TWUtils::zoomToHalfScreen(this, true);

	if (properties.contains("state"))
		restoreState(properties.value("state").toByteArray(), kPDFWindowStateVersion);
*/
	if (texDoc != NULL) {
		//TODO stackUnder((QWidget*)texDoc);
		actionSide_by_Side->setEnabled(true);
		actionGo_to_Source->setEnabled(true);
		sourceDocList.append(texDoc);
	}
}

PDFDocument::~PDFDocument()
{
	if (scanner != NULL)
		synctex_scanner_free(scanner);
	docList.removeAll(this);
	if (document)
		delete document;
}

void
PDFDocument::init()
{
	docList.append(this);

	setupUi(this);
#ifdef Q_WS_WIN
	TWApp::instance()->createMessageTarget(this);
#endif

	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_MacNoClickThrough, true);
	setWindowIcon(QIcon(":/images/images/TeXworks-doc.png"));
	
	setContextMenuPolicy(Qt::NoContextMenu);

	pdfWidget = new PDFWidget;

	toolButtonGroup = new QButtonGroup(toolBar);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionMagnify)), kMagnifier);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionScroll)), kScroll);
//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Text)), kSelectText);
//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Image)), kSelectImage);
	connect(toolButtonGroup, SIGNAL(buttonClicked(int)), pdfWidget, SLOT(setTool(int)));
	pdfWidget->setTool(kMagnifier);

	scaleLabel = new QLabel();
	statusBar()->addPermanentWidget(scaleLabel);
	scaleLabel->setFrameStyle(QFrame::StyledPanel);
	scaleLabel->setFont(statusBar()->font());
	
	pageLabel = new QLabel();
	statusBar()->addPermanentWidget(pageLabel);
	pageLabel->setFrameStyle(QFrame::StyledPanel);
	pageLabel->setFont(statusBar()->font());

	scrollArea = new PDFScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidget(pdfWidget);
	setCentralWidget(scrollArea);
	
	connect(scrollArea, SIGNAL(resized()), pdfWidget, SLOT(windowResized()));

	document = NULL;
	
	connect(actionAbout_TW, SIGNAL(triggered()), qApp, SLOT(about()));
	connect(actionGoToHomePage, SIGNAL(triggered()), qApp, SLOT(goToHomePage()));
	connect(actionWriteToMailingList, SIGNAL(triggered()), qApp, SLOT(writeToMailingList()));

	connect(actionNew, SIGNAL(triggered()), qApp, SLOT(newFile()));
	connect(actionNew_from_Template, SIGNAL(triggered()), qApp, SLOT(newFromTemplate()));
	connect(actionOpen, SIGNAL(triggered()), qApp, SLOT(open()));

//TODO	connect(actionQuit_TeXworks, SIGNAL(triggered()), TWApp::instance(), SLOT(maybeQuit()));

	connect(actionFind, SIGNAL(triggered()), this, SLOT(doFindDialog()));

	connect(actionFirst_Page, SIGNAL(triggered()), pdfWidget, SLOT(goFirst()));
	connect(actionPrevious_Page, SIGNAL(triggered()), pdfWidget, SLOT(goPrev()));
	connect(actionNext_Page, SIGNAL(triggered()), pdfWidget, SLOT(goNext()));
	connect(actionLast_Page, SIGNAL(triggered()), pdfWidget, SLOT(goLast()));
	connect(actionGo_to_Page, SIGNAL(triggered()), pdfWidget, SLOT(doPageDialog()));
	connect(pdfWidget, SIGNAL(changedPage(int)), this, SLOT(enablePageActions(int)));

	connect(actionActual_Size, SIGNAL(triggered()), pdfWidget, SLOT(fixedScale()));
	connect(actionFit_to_Width, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWidth(bool)));
	connect(actionFit_to_Window, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWindow(bool)));
	connect(actionZoom_In, SIGNAL(triggered()), pdfWidget, SLOT(zoomIn()));
	connect(actionZoom_Out, SIGNAL(triggered()), pdfWidget, SLOT(zoomOut()));
	connect(actionFull_Screen, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
	connect(pdfWidget, SIGNAL(changedZoom(qreal)), this, SLOT(enableZoomActions(qreal)));
	connect(pdfWidget, SIGNAL(changedScaleOption(autoScaleOption)), this, SLOT(adjustScaleActions(autoScaleOption)));
	connect(pdfWidget, SIGNAL(syncClick(int, const QPointF&)), this, SLOT(syncClick(int, const QPointF&)));

	if (actionZoom_In->shortcut() == QKeySequence("Ctrl++"))
		new QShortcut(QKeySequence("Ctrl+="), pdfWidget, SLOT(zoomIn()));
	
	connect(actionTypeset, SIGNAL(triggered()), this, SLOT(retypeset()));
	
	connect(actionStack, SIGNAL(triggered()), qApp, SLOT(stackWindows()));
	connect(actionTile, SIGNAL(triggered()), qApp, SLOT(tileWindows()));
	connect(actionSide_by_Side, SIGNAL(triggered()), this, SLOT(sideBySide()));
	connect(actionPlace_on_Left, SIGNAL(triggered()), this, SLOT(placeOnLeft()));
	connect(actionPlace_on_Right, SIGNAL(triggered()), this, SLOT(placeOnRight()));
	connect(actionGo_to_Source, SIGNAL(triggered()), this, SLOT(goToSource()));
	
	connect(actionFind_Again, SIGNAL(triggered()), this, SLOT(doFindAgain()));

	menuRecent = new QMenu(tr("Open Recent"), this);
	updateRecentFileActions();
	menuFile->insertMenu(actionOpen_Recent, menuRecent);
	menuFile->removeAction(actionOpen_Recent);

	connect(qApp, SIGNAL(recentFileActionsChanged()), this, SLOT(updateRecentFileActions()));
	connect(qApp, SIGNAL(windowListChanged()), this, SLOT(updateWindowMenu()));

	connect(qApp, SIGNAL(hideFloatersExcept(QWidget*)), this, SLOT(hideFloatersUnlessThis(QWidget*)));
	connect(this, SIGNAL(activatedWindow(QWidget*)), qApp, SLOT(activatedWindow(QWidget*)));

	connect(actionPreferences, SIGNAL(triggered()), qApp, SLOT(preferences()));

	connect(this, SIGNAL(destroyed()), qApp, SLOT(updateWindowMenus()));

	connect(qApp, SIGNAL(syncPdf(const QString&, int, bool)), this, SLOT(syncFromSource(const QString&, int, bool)));

	menuShow->addAction(toolBar->toggleViewAction());
	menuShow->addSeparator();

	QDockWidget *dw = new PDFOutlineDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(pdfWidget, SIGNAL(changedPage(int)), dw, SLOT(pageChanged(int)));

	dw = new PDFInfoDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(pdfWidget, SIGNAL(changedPage(int)), dw, SLOT(pageChanged(int)));

	dw = new PDFFontsDock(this);
	dw->hide();
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(pdfWidget, SIGNAL(changedPage(int)), dw, SLOT(pageChanged(int)));

	exitFullscreen = NULL;
	
/*TODO	QSETTINGS_OBJECT(settings);
	TWUtils::applyToolbarOptions(this, settings.value("toolBarIconSize", 2).toInt(), settings.value("toolBarShowText", false).toBool());

	TWApp::instance()->updateWindowMenus();
	
	initScriptable(menuScripts, actionAbout_Scripts, actionManage_Scripts,
				   actionUpdate_Scripts, actionShow_Scripts_Folder);
	
	TWUtils::insertHelpMenuItems(menuHelp);
	TWUtils::installCustomShortcuts(this);*/
}

void PDFDocument::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange) {
		QString title = windowTitle();
		retranslateUi(this);
		menuRecent->setTitle(tr("Open Recent"));
//TODO		TWUtils::insertHelpMenuItems(menuHelp);
		setWindowTitle(title);
		if (pdfWidget)
			pdfWidget->updateStatusBar();
	}
	else
		QMainWindow::changeEvent(event);
}

void PDFDocument::linkToSource(TeXDocument *texDoc)
{
	if (texDoc != NULL) {
		if (!sourceDocList.contains(texDoc))
			sourceDocList.append(texDoc);
		actionGo_to_Source->setEnabled(true);
	}
}

void PDFDocument::texClosed(QObject *obj)
{
	TeXDocument *texDoc = reinterpret_cast<TeXDocument*>(obj);
		// can't use qobject_cast here as the object's metadata is already gone!
	if (texDoc != 0) {
		sourceDocList.removeAll(texDoc);
		if (sourceDocList.count() == 0)
			close();
	}
}

void PDFDocument::updateRecentFileActions()
{
//TODO	TWUtils::updateRecentFileActions(this, recentFileActions, menuRecent);
}

void PDFDocument::updateWindowMenu()
{
//TODO	TWUtils::updateWindowMenu(this, menuWindow);
}

void PDFDocument::sideBySide()
{
/*	if (sourceDocList.count() > 0) {
//TODO		TWUtils::sideBySide(sourceDocList[0], this);
//TODO		sourceDocList[0]->selectWindow(false);
//TODO		selectWindow();
	}
	else
		placeOnRight();*/
}

bool PDFDocument::event(QEvent *event)
{
	switch (event->type()) {
		case QEvent::WindowActivate:
//TODO			showFloaters();
			emit activatedWindow(this);
			break;
		default:
			break;
	}
	return QMainWindow::event(event);
}

void PDFDocument::closeEvent(QCloseEvent *event)
{
	event->accept();
	if (openedManually) {
		saveRecentFileInfo();
	}
	deleteLater();
}

void PDFDocument::saveRecentFileInfo()
{
	QMap<QString,QVariant> fileProperties;
	fileProperties.insert("path", curFile);
	fileProperties.insert("geometry", saveGeometry());
	fileProperties.insert("state", saveState(kPDFWindowStateVersion));
//TODO	TWApp::instance()->addToRecentFiles(fileProperties);
}

void PDFDocument::loadFile(const QString &fileName)
{
	setCurrentFile(fileName);
	reload();
	if (watcher) {
		const QStringList files = watcher->files();
		if (files.isEmpty())
			watcher->removePaths(files); // in case we ever load different files into the same widget
		watcher->addPath(curFile);
	}
}

void PDFDocument::reload()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	if (scanner != NULL) {
		synctex_scanner_free(scanner);
		scanner = NULL;
	}

	if (document != NULL)
		delete document;

	document = Poppler::Document::load(curFile);
	if (document != NULL) {
		if (document->isLocked()) {
			delete document;
			document = NULL;
			statusBar()->showMessage(tr("PDF file \"%1\" is locked; this is not currently supported.").arg(curFile));
									 //.arg(TWUtils::strippedName(curFile)));
			pdfWidget->hide();
		}
		else {
			document->setRenderBackend(Poppler::Document::SplashBackend);
			document->setRenderHint(Poppler::Document::Antialiasing);
			document->setRenderHint(Poppler::Document::TextAntialiasing);
//			globalParams->setScreenType(screenDispersed);

			pdfWidget->setDocument(document);
			pdfWidget->show();
			pdfWidget->setFocus();

			loadSyncData();
			emit reloaded();
		}
	}
	else {
		statusBar()->showMessage(tr("Failed to load file \"%1\"; perhaps it is not a valid PDF document.").arg(curFile));
//									.arg(TWUtils::strippedName(curFile)));
		pdfWidget->hide();
	}
	QApplication::restoreOverrideCursor();
}

void PDFDocument::reloadWhenIdle()
{
	if (reloadTimer)
		reloadTimer->stop();
	else {
		reloadTimer = new QTimer(this);
		reloadTimer->setSingleShot(true);
		reloadTimer->setInterval(1000);
		connect(reloadTimer, SIGNAL(timeout()), this, SLOT(reload()));
	}
	reloadTimer->start();
}

void PDFDocument::loadSyncData()
{
	scanner = synctex_scanner_new_with_output_file(curFile.toUtf8().data(), NULL, 1);
	if (scanner == NULL)
		statusBar()->showMessage(tr("No SyncTeX data available")/*TODO, kStatusMessageDuration*/);
	else {
		QString synctexName = QString::fromUtf8(synctex_scanner_get_synctex(scanner));
		statusBar()->showMessage(tr("SyncTeX: \"%1\"").arg(synctexName) /*TODO, kStatusMessageDuration*/);
	}
}

void PDFDocument::syncClick(int pageIndex, const QPointF& pos)
{
	if (scanner == NULL)
		return;
	pdfWidget->setHighlightPath(QPainterPath());
	pdfWidget->update();
	if (synctex_edit_query(scanner, pageIndex + 1, pos.x(), pos.y()) > 0) {
		synctex_node_t node;
		while ((node = synctex_next_result(scanner)) != NULL) {
			QString filename = QString::fromUtf8(synctex_scanner_get_name(scanner, synctex_node_tag(node)));
			QDir curDir(QFileInfo(curFile).canonicalPath());
			//TODO:			TeXDocument::openDocument(QFileInfo(curDir, filename).canonicalFilePath(), true, true, synctex_node_line(node));
			break; // FIXME: currently we just take the first hit
		}
	}
}

void PDFDocument::syncFromSource(const QString& sourceFile, int lineNo, bool activatePreview)
{
	if (scanner == NULL)
		return;

	// find the name synctex is using for this source file...
	const QFileInfo sourceFileInfo(sourceFile);
	QDir curDir(QFileInfo(curFile).canonicalPath());
	synctex_node_t node = synctex_scanner_input(scanner);
	QString name;
	bool found = false;
	while (node != NULL) {
		name = QString::fromUtf8(synctex_scanner_get_name(scanner, synctex_node_tag(node)));
		const QFileInfo fi(curDir, name);
		if (fi == sourceFileInfo) {
			found = true;
			break;
		}
		node = synctex_node_sibling(node);
	}
	if (!found)
		return;

	if (synctex_display_query(scanner, name.toUtf8().data(), lineNo, 0) > 0) {
		int page = -1;
		QPainterPath path;
		while ((node = synctex_next_result(scanner)) != NULL) {
			if (page == -1)
				page = synctex_node_page(node);
			if (synctex_node_page(node) != page)
				continue;
			QRectF nodeRect(synctex_node_box_visible_h(node),
							synctex_node_box_visible_v(node) - synctex_node_box_visible_height(node),
							synctex_node_box_visible_width(node),
							synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node));
			path.addRect(nodeRect);
		}
		if (page > 0) {
			pdfWidget->goToPage(page - 1);
			path.setFillRule(Qt::WindingFill);
			pdfWidget->setHighlightPath(path);
			pdfWidget->update();
//TODO			if (activatePreview)
//				selectWindow();
		}
	}
}

void PDFDocument::setCurrentFile(const QString &fileName)
{
	curFile = QFileInfo(fileName).canonicalFilePath();
	setWindowTitle(tr("%1[*] - %2").arg(/*TODOTWUtils::strippedName*/(curFile)).arg(tr("TexMakerX")));
//TODO	TWApp::instance()->updateWindowMenus();
}
 
PDFDocument *PDFDocument::findDocument(const QString &fileName)
{
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

	foreach (QWidget *widget, qApp->topLevelWidgets()) {
		PDFDocument *theDoc = qobject_cast<PDFDocument*>(widget);
		if (theDoc && theDoc->curFile == canonicalFilePath)
			return theDoc;
	}
	return NULL;
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

void PDFDocument::showPage(int page)
{
	pageLabel->setText(tr("page %1 of %2").arg(page).arg(document->numPages()));
}

void PDFDocument::showScale(qreal scale)
{
	scaleLabel->setText(tr("%1%").arg(ROUND(scale * 10000.0) / 100.0));
}

void PDFDocument::retypeset()
{
//TODO	if (sourceDocList.count() > 0)
//TODO		sourceDocList[0]->typeset();
}

void PDFDocument::interrupt()
{
//TODO	if (sourceDocList.count() > 0)
//TODO		sourceDocList[0]->interrupt();
}

void PDFDocument::goToSource()
{
/*TODO	if (sourceDocList.count() > 0)
		sourceDocList[0]->selectWindow();
	else
		// should not occur, the action is supposed to be disabled
		actionGo_to_Source->setEnabled(false);*/
}

void PDFDocument::enablePageActions(int pageIndex)
{
//#ifndef Q_WS_MAC
// On Mac OS X, disabling these leads to a crash if we hit the end of document while auto-repeating a key
// (seems like a Qt bug, but needs further investigation)
// 2008-09-07: seems to no longer be a problem, probably thanks to Qt 4.4 update
	actionFirst_Page->setEnabled(pageIndex > 0);
	actionPrevious_Page->setEnabled(pageIndex > 0);
	actionNext_Page->setEnabled(pageIndex < document->numPages() - 1);
	actionLast_Page->setEnabled(pageIndex < document->numPages() - 1);
//#endif
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
}

void PDFDocument::toggleFullScreen()
{
	if (windowState() & Qt::WindowFullScreen) {
		// exiting full-screen mode
		statusBar()->show();
		toolBar->show();
		showNormal();
		pdfWidget->restoreState();
		actionFull_Screen->setChecked(false);
		delete exitFullscreen;
	}
	else {
		// entering full-screen mode
		statusBar()->hide();
		toolBar->hide();
		showFullScreen();
		pdfWidget->saveState();
		pdfWidget->fitWindow(true);
		actionFull_Screen->setChecked(true);
		exitFullscreen = new QShortcut(Qt::Key_Escape, this, SLOT(toggleFullScreen()));
	}
}

void PDFDocument::resetMagnifier()
{
	pdfWidget->resetMagnifier();
}

void PDFDocument::setResolution(int res)
{
	if (res > 0)
		pdfWidget->setResolution(res);
}

void PDFDocument::enableTypesetAction(bool enabled)
{
	actionTypeset->setEnabled(enabled);
}

void PDFDocument::updateTypesettingAction(bool processRunning)
{
	if (processRunning) {
		disconnect(actionTypeset, SIGNAL(triggered()), this, SLOT(retypeset()));
		actionTypeset->setIcon(QIcon(":/images/tango/process-stop.png"));
		actionTypeset->setText(tr("Abort typesetting"));
		connect(actionTypeset, SIGNAL(triggered()), this, SLOT(interrupt()));
		enableTypesetAction(true);
	}
	else {
		disconnect(actionTypeset, SIGNAL(triggered()), this, SLOT(interrupt()));
		actionTypeset->setIcon(QIcon(":/images/images/runtool.png"));
		actionTypeset->setText(tr("Typeset"));
		connect(actionTypeset, SIGNAL(triggered()), this, SLOT(retypeset()));
	}
}

void PDFDocument::goToDestination(const QString& destName)
{
	if (pdfWidget)
		pdfWidget->goToDestination(destName);
}

void PDFDocument::dragEnterEvent(QDragEnterEvent *event)
{
	// Only accept files for now
	event->ignore();
	if (event->mimeData()->hasUrls()) {
		const QList<QUrl> urls = event->mimeData()->urls();
		foreach (const QUrl& url, urls) {
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
/*TODO		foreach (const QUrl& url, urls)
			if (url.scheme() == "file")
				TWApp::instance()->openFile(url.toLocalFile());*/
		event->acceptProposedAction();
	}
}

void PDFDocument::doFindDialog()
{
/*TODO	if (PDFFindDialog::doFindDialog(this) == QDialog::Accepted)
		doFindAgain(true);*/
}

void PDFDocument::doFindAgain(bool newSearch /*= false*/)
{
/*TODO	QSETTINGS_OBJECT(settings);
	int pageIdx;
	Poppler::Page *page;
	Poppler::Page::SearchMode searchMode = Poppler::Page::CaseInsensitive;
	Poppler::Page::SearchDirection searchDir; // = Poppler::Page::FromTop;
	int deltaPage, firstPage, lastPage;
	int run, runs;
	bool backwards = false;

	if (!document)
		return;
	
	QString	searchText = settings.value("searchText").toString();
	if (searchText.isEmpty())
		return;

	QTextDocument::FindFlags flags = (QTextDocument::FindFlags)settings.value("searchFlags").toInt();

	if ((flags & QTextDocument::FindCaseSensitively) != 0)
		searchMode = Poppler::Page::CaseSensitive;
	if ((flags & QTextDocument::FindBackward) != 0)
		backwards = true;

	deltaPage = (backwards ? -1 : +1);

	if (newSearch) {
		lastSearchResult.selRect = QRectF();
		firstSearchPage = pdfWidget->getCurrentPageIndex();
	}
	searchDir = (backwards ? Poppler::Page::PreviousResult : Poppler::Page::NextResult);
	
	runs = (settings.value("searchWrap").toBool() ? 2 : 1);

	for (run = 0; run < runs; ++run) {
		switch (run) {
			case 0:
				// first run = normal search
				lastPage = (backwards ? -1 : document->numPages());
				firstPage = pdfWidget->getCurrentPageIndex();
				break;
			case 1:
				// second run = after wrap
				lastPage = (backwards ? -1 : document->numPages());
				firstPage = (backwards ? document->numPages() - 1 : 0);
				break;
			default:
				// should not happen
				return;
		}
		
		for (pageIdx = firstPage; pageIdx != lastPage; pageIdx += deltaPage) {
			page = document->page(pageIdx);

			if (page->search(searchText, lastSearchResult.selRect, searchDir, searchMode)) {
				lastSearchResult.doc = this;
				lastSearchResult.pageIdx = pageIdx;
				QPainterPath p;
				p.addRect(lastSearchResult.selRect);

				if (hasSyncData() && settings.value("searchPdfSync").toBool()) {
					emit syncClick(pageIdx, lastSearchResult.selRect.center());
				}

				pdfWidget->goToPage(lastSearchResult.pageIdx);
				pdfWidget->setHighlightPath(p);
				pdfWidget->update();
				selectWindow();
				return;
			}
			lastSearchResult.selRect = QRectF();
			searchDir = (backwards ? Poppler::Page::PreviousResult : Poppler::Page::NextResult);
		}
	}*/
}

