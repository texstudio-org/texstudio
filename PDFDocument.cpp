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
#include "universalinputdialog.h"

#include "smallUsefulFunctions.h"
#include "PDFDocument_config.h"
#include "configmanagerinterface.h"
//#include "GlobalParams.h"

#include "poppler-link.h"

#define SYNCTEX_GZ_EXT	".synctex.gz"
#define SYNCTEX_EXT		".synctex"

#define ROUND(x) floor((x)+0.5)

const qreal kMaxScaleFactor = 8.0;
const qreal kMinScaleFactor = 0.125;

// tool codes
const int kNone = 0;
const int kMagnifier = 1;
const int kScroll = 2;
const int kSelectText = 3;
const int kSelectImage = 4;
const int kPresentation = 5; //left-click: next, rclick: prev (for these presentation/mouse-pointer)

// duration of highlighting in PDF view (might make configurable?)
const int kPDFHighlightDuration = 2000;

static PDFDocumentConfig* globalConfig = 0;

static const int GridBorder = 5;
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
		foreach (QWidget * widget, QApplication::topLevelWidgets()) {
			if (!qobject_cast<QMainWindow*>(widget))
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
		r.setLeft(r.left() + r.right() / 2);
		window->move(r.left(), r.top());
		window->resize(r.width() - wDiff, r.height() - hDiff);
	}
	else {
		r.setRight(r.left() + r.right() / 2 - 1);
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

void tileWindowsInRect(const QWidgetList& windows, const QRect& bounds)
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
	foreach (QWidget* window, windows) {
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
		}
		else
			r.moveLeft(bounds.left() + (bounds.width() * x) / cols);
	}
}

void stackWindowsInRect(const QWidgetList& windows, const QRect& bounds)
{
	const int kStackingOffset = 20;
	QRect r(bounds);
	r.setWidth(r.width() / 2);
	int index = 0;
	foreach (QWidget* window, windows) {
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
		}
		else if (++index == 10) {
			r.setTop(bounds.top());
			index = 0;
		}
		else {
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
	, page(-1)
	, scaleFactor(kMagFactor)
	, parentDpi(inDpi)
	, imageDpi(0)
	, imagePage(-1)
{
}

void PDFMagnifier::setPage(int pageNr, qreal scale, const QRect& visibleRect)
{
	page = pageNr;
	scaleFactor = scale * kMagFactor;
	if (page <0) {
		imagePage=-1;
		image = QPixmap();
	}
	else {
		PDFWidget* parent = qobject_cast<PDFWidget*>(parentWidget());
		if (parent != NULL) {
			PDFDocument *doc=parent->getPDFDocument();
			QWidget* viewport = parent->parentWidget();
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
				if (page != imagePage || dpi != imageDpi || loc != imageLoc || size != imageSize){
					//don't cache in rendermanager in order to reduce memory consumption
					image = doc->renderManager.renderToImage(pageNr,this,"setImage",dpi, dpi, loc.x(), loc.y(), size.width(), size.height(),false,true);
				}
				imagePage = page;
				imageDpi = dpi;
				imageLoc = loc;
				mouseOffset = visibleRect.topLeft();
				imageSize = size;
			}
		}
	}
	update();
}
void PDFMagnifier::setImage(QPixmap img,int pageNr){
    if(pageNr==page)
	image=img;
    update();
}

void PDFMagnifier::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFrame(&painter);
	painter.drawPixmap(event->rect(), image,
		event->rect().translated(((x() - mouseOffset.x()) * kMagFactor - imageLoc.x()) + width() / 2  ,
						((y() - mouseOffset.y()) * kMagFactor - imageLoc.y()) + height() / 2));

	if (globalConfig->magnifierBorder) {
		painter.setPen(QPalette().mid().color());
		switch (globalConfig->magnifierShape) {
		case 1: { //circular
				int side = qMin(width(), height()) ;
				painter.drawEllipse(width() / 2 - side / 2 + 1, height() / 2 - side / 2 + 1, side-2, side-2);
				break;
			}
		default: painter.drawRect(0,0,width()-1,height()-1); //rectangular
		}
	}
}

void PDFMagnifier::resizeEvent(QResizeEvent * /*event*/)
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return;

	switch (globalConfig->magnifierShape) {
	case 1: { //circular
			int side = qMin(width(), height());
			QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side, side, QRegion::Ellipse);
			setMask(maskedRegion);
			break;
		}
	default:; //rectangular
	}
}

//#pragma mark === PDFWidget ===

QCursor *PDFWidget::magnifierCursor = NULL;
QCursor *PDFWidget::zoomInCursor = NULL;
QCursor *PDFWidget::zoomOutCursor = NULL;

PDFWidget::PDFWidget()
	: QLabel()
	, document(NULL)
	, clickedLink(NULL)
	, pageIndex(0), oldPageIndex(0)
	, scaleFactor(1.0)
	, dpi(72.0)
	, scaleOption(kFixedMag)
	, magnifier(NULL)
	, usingTool(kNone)
	, singlePageStep(true)
	, gridx(1), gridy(1)
	, forceUpdate(false)
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return;


	dpi = globalConfig->dpi;
	if (dpi<=0) dpi = 72; //it crashes if dpi=0
	
	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	setFocusPolicy(Qt::StrongFocus);
	setScaledContents(true);
	setMouseTracking(true);

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
	}

	if (magnifierCursor == NULL) {
		magnifierCursor = new QCursor(QPixmap(":/images/magnifiercursor.png"));
		zoomInCursor = new QCursor(QPixmap(":/images/zoomincursor.png"));
		zoomOutCursor = new QCursor(QPixmap(":/images/zoomoutcursor.png"));
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
	shortcutPageUp1 = new QShortcut(QKeySequence(Qt::Key_PageUp), this, SLOT(pageUpOrPrev()));
	//shortcutPageUp2 = new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Space), this, SLOT(pageUpOrPrev()));
	//shortcutPageUp3 = new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Enter), this, SLOT(pageUpOrPrev()));
	//shortcutPageUp4 = new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Return), this, SLOT(pageUpOrPrev()));
	shortcutPageDown1 = new QShortcut(QKeySequence(Qt::Key_PageDown), this, SLOT(pageDownOrNext()));
	//shortcutPageDown2 = new QShortcut(QKeySequence(Qt::Key_Space), this, SLOT(pageDownOrNext()));
	//shortcutPageDown3 = new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(pageDownOrNext()));
	//shortcutPageDown4 = new QShortcut(QKeySequence(Qt::Key_Return), this, SLOT(pageDownOrNext()));

	highlightRemover.setSingleShot(true);
	connect(&highlightRemover, SIGNAL(timeout()), this, SLOT(clearHighlight()));
}

PDFWidget::~PDFWidget()
{
}

void PDFWidget::setDocument(Poppler::Document *doc)
{
	pages.clear();
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
	PDFDocument *doc=getPDFDocument();
	if (pages.size() > 0 && (pages.first() != imagePage || newDpi != imageDpi || newRect != imageRect || forceUpdate)) {
		if (gridx<=1 && gridy<=1) {
			int pageNr=pages.first();
			image = doc->renderManager.renderToImage(pageNr,this,"setImage",dpi * scaleFactor, dpi * scaleFactor,
							rect().x(), rect().y(), rect().width(), rect().height(),true,true);
		} else {
			image = QPixmap(newRect.width(), newRect.height());
			image.fill(QApplication::palette().color(QPalette::Dark).rgb());
			QPainter p;
			p.begin(&image);
			for (int i=0;i<pages.size();i++){
				QRect drawTo = gridPageRect(i);
				int pageNr=pages[i];
				QPixmap temp = doc->renderManager.renderToImage(
							  pageNr,this,"setImage",
							  dpi * scaleFactor,
							  dpi * scaleFactor,
							  0,0,drawTo.width(), drawTo.height(),true,true);
				p.drawPixmap(drawTo.left(), drawTo.top(), temp);
			}
			p.end();
		}
	}

	imagePage = pages.isEmpty()?-1:pages.first();
	imageDpi = newDpi;
	imageRect = newRect;

	painter.drawPixmap(event->rect(), image, event->rect());

	if (!highlightPath.isEmpty()) {
		painter.setRenderHint(QPainter::Antialiasing);
		painter.scale(dpi / 72.0 * scaleFactor, dpi / 72.0 * scaleFactor);
		painter.setPen(QColor(0, 0, 0, 0));
		painter.setBrush(QColor(255, 255, 0, 63));
		painter.drawPath(highlightPath);
	}
}

void PDFWidget::setImage(QPixmap,int){
    forceUpdate=true;
    update();
}

void PDFWidget::useMagnifier(const QMouseEvent *inEvent)
{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return;
	int localPageIndex = gridPageIndex(inEvent->pos());
	if (localPageIndex < 0)
		return;
	if (!magnifier)
		magnifier = new PDFMagnifier(this, dpi);
	magnifier->setFixedSize(globalConfig->magnifierSize * 4 / 3, globalConfig->magnifierSize);
	//magnifier->setPage(pages[pageIndex], scaleFactor, gridPageRect(pageIndex));
	magnifier->setPage(pages[localPageIndex], scaleFactor, gridPageRect(localPageIndex));
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
	else if (currentTool != kPresentation){
		Poppler::Page *page;
		QPointF scaledPos;
		int pageNr;
		gridMapToScaledPosition(event->pos(), pageNr, scaledPos);
		if (pageNr>=0) {
			page=document->page(pageNr);
			// check for click in link
			foreach (Poppler::Link* link, page->links()) {
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
			delete page;
		}
	}
	event->accept();
}

void PDFWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (clickedLink != NULL) {
		int page;
		QPointF scaledPos;
		gridMapToScaledPosition(event->pos(), page, scaledPos);
		if (page>-1 && clickedLink->linkArea().contains(scaledPos)) {
			doLink(clickedLink);
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
						syncWindowClick(event->pos().x(), event->pos().y(), true);

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
		PDFScrollArea*	scrollArea = getScrollArea();
		if (scrollArea) {
			scrollArea->goToPage(dest.pageNumber() - 1);
			if (dest.isChangeZoom()) {
				// FIXME
			}
			QPoint p = gridMapFromScaledPosition(QPointF( dest.left(), dest.top()));
			if (dest.isChangeLeft())
				scrollArea->horizontalScrollBar()->setValue(p.x());

			if (dest.isChangeTop())
				scrollArea->verticalScrollBar()->setValue(p.y());
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
				if (!QDesktopServices::openUrl(url))
						QMessageBox::warning(this,tr("Error"),tr("Could not open browser"));
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
				QAbstractScrollArea*	scrollArea = getScrollArea();
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
	if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return ){
		if (event->modifiers() & Qt::SHIFT) pageUpOrPrev();
		else pageDownOrNext();
	}
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
		emit syncClick(pageIndex, pagePos, true);
	}
}

void PDFWidget::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers()==Qt::ControlModifier){
        int numDegrees = event->delta() / 8;
        if(numDegrees>0){
            doZoom(event->pos(), 1);
        }else{
            doZoom(event->pos(), -1);
        }
    }else{
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
}

void PDFWidget::setTool(int tool)
{
	currentTool = tool;
	updateCursor();
}


void PDFWidget::syncWindowClick(int x, int y, bool activate, int page){
	if (page == -1) {
		page = qMax(0,gridPageIndex(QPoint(x,y))); //page index in grid
		QPoint p = gridPagePosition(page);
		x -= p.x();
		y -= p.y();
		page +=  pageIndex;                        //page index in document
	}
	QPointF pagePos(x / scaleFactor * 72.0 / dpi,
			y / scaleFactor * 72.0 / dpi);
	emit syncClick(page, pagePos, activate);
}

void PDFWidget::syncCurrentPage(bool activate){
	//single page step mode: jump to center of first page in grid; multi page step: jump to center of grid
	int curPage = pageIndex + (pageStep()>1?pages.size()/2:0);
	QRect r = gridPageRect(curPage);
	syncWindowClick(r.width()/2, r.height()/2, activate, curPage);
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
	Poppler::Page* page;
	QPointF scaledPos;
	int pageNr;
	gridMapToScaledPosition(pos, pageNr, scaledPos);
	if (pageNr<0) return;
	// check for link
	page=document->page(pageNr);
	foreach (Poppler::Link* link, page->links()) {
		// poppler's linkArea is relative to the page rect
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
			delete page;
			return;
		}
	}
	delete page;
	updateCursor();
}

void PDFWidget::adjustSize()
{
	if (pages.empty()) return;
	QSize pageSize = (gridSizeF() * scaleFactor * dpi / 72.0).toSize();
	if (pageSize != size())
		resize(pageSize);
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

void PDFWidget::setHighlightPath(const int page, const QPainterPath& path)
{
	highlightRemover.stop();
	highlightPath = path;
	if (!path.isEmpty()) {
		if (gridx*gridy >= 1)
			highlightPath.translate(QPointF(gridPagePosition(page - pageIndex)) / dpi * 72 / scaleFactor);
		PDFScrollArea*	scrollArea = getScrollArea();
		if (scrollArea) {
			QRectF r = highlightPath.boundingRect();
			scrollArea->ensureVisible((int)((r.left() + r.right()) / 2 * dpi / 72 * scaleFactor),
										(int)((r.top() + r.bottom()) / 2 * dpi / 72 * scaleFactor));
		}
		if (kPDFHighlightDuration > 0)
			highlightRemover.start(kPDFHighlightDuration);
	}
}

int PDFWidget::getHighlightPage() const{
	return highlightPage;
}

void PDFWidget::clearHighlight()
{
	highlightPath = QPainterPath();
	update();
}

void PDFWidget::reloadPage(bool sync)
{
	QList<int> oldpages = pages;
	pages.clear();
	if (magnifier != NULL)
		magnifier->setPage(NULL, 0, QRect());
	imagePage = NULL;
	image = QPixmap();
	highlightPath = QPainterPath();
	if (document != NULL) {
		if (pageIndex >= document->numPages())
			pageIndex = document->numPages() - 1;
		if (pageIndex >= 0) {
			int pageCount = qMin(gridx*gridy, document->numPages() - pageIndex);
			//use old pages if available ([a<=b], [c<=d] find [x<=y] with a <= x, c <= x, y <= b, y <= d)
			int firstCommonPage = qMax(pageIndex, oldPageIndex);
			int lastCommonPage = qMin(pageIndex + pageCount - 1, oldPageIndex + oldpages.size() - 1);

			if (lastCommonPage < firstCommonPage) {
				for (int i=0; i < pageCount; i++)
					pages.append(pageIndex + i);
			} else {
				for (int i=pageIndex; i < firstCommonPage; i++) pages.append(i);
				for (int i=firstCommonPage; i <= lastCommonPage; i++) pages.append(oldpages[i-oldPageIndex]);
				for (int i=lastCommonPage + 1; i < pageIndex + pageCount; i++) pages.append(i);
			}
			oldPageIndex = pageIndex;
		}
	}

	adjustSize();
	update();
	updateStatusBar();
	emit changedPage(pageIndex, sync);
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
PDFDocument * PDFWidget::getPDFDocument(){
    QWidget *widget = window();
    PDFDocument *doc = qobject_cast<PDFDocument*>(widget);
    return doc;
}

void PDFWidget::setGridSize(int gx, int gy){
	if (gridx == gx && gridy == gy)
		return;
	gridx = gx;
	gridy = gy;
	int pi = pageIndex;
	getScrollArea()->goToPage(pageIndex);
	if (pi == pageIndex)
		reloadPage();
	//update();
}

int PDFWidget::visiblePages() const {
	return pages.size();
}

int PDFWidget::numPages() const{
	if (!document) return 0;
	return document->numPages();
}

int PDFWidget::pageStep() const {
	if (singlePageStep) return 1;
	return gridx*gridy;
}

int PDFWidget::gridCols() const{
	return gridx;
}
int PDFWidget::gridRowHeight() const{
	return gridPageRect(0).height() + GridBorder;
}


void PDFWidget::setSinglePageStep(bool step){
	if (singlePageStep == step)
		return;
	singlePageStep = step;
	getScrollArea()->goToPage(pageIndex);
}

void PDFWidget::goFirst()
{
	getScrollArea()->goToPage(0);
}

void PDFWidget::goPrev()
{
	getScrollArea()->goToPage(pageIndex - pageStep());
}

void PDFWidget::goNext()
{
	getScrollArea()->goToPage(pageIndex + pageStep());
}

void PDFWidget::goLast()
{
	if (!document) return;
	getScrollArea()->goToPage(document->numPages() - 1);
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


void PDFWidget::pageUpOrPrev()
{
	if (document == NULL)
		return;
	QScrollBar* scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() > scrollBar->minimum())
		scrollBar->triggerAction(QAbstractSlider::SliderPageStepSub);
	else {
		if (pageIndex > 0) {
			goPrev();
			scrollBar->triggerAction(QAbstractSlider::SliderToMaximum);
		}
	}
	//shortcutPageUp->setAutoRepeat(scrollBar->value() > scrollBar->minimum());
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

void PDFWidget::pageDownOrNext()
{
	if (document == NULL)
		return;
	QScrollBar*		scrollBar = getScrollArea()->verticalScrollBar();
	if (scrollBar->value() < scrollBar->maximum())
		scrollBar->triggerAction(QAbstractSlider::SliderPageStepAdd);
	else {
		if (pageIndex < document->numPages() - 1) {
			goNext();
			scrollBar->triggerAction(QAbstractSlider::SliderToMinimum);
		}
	}
	//shortcutPageDown->setAutoRepeat(scrollBar->value() < scrollBar->maximum());
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
		getScrollArea()->goToPage(pageNo - 1);
}

void PDFWidget::goToPageDirect(int p, bool sync)
{
	p -= p % pageStep();
	if (p != pageIndex && document != NULL) { //the first condition is important: it prevents a recursive sync crash
		if (p >= 0 && p < document->numPages()) {
			pageIndex = p;
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
		QAbstractScrollArea*	scrollArea = getScrollArea();
		if (scrollArea && !pages.isEmpty()) {
			qreal portWidth = scrollArea->viewport()->width();
			QSizeF	pageSize = gridSizeF(true) * dpi / 72.0;
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
		PDFScrollArea*	scrollArea = getScrollArea();
		if (scrollArea && !pages.isEmpty()) {
			qreal portWidth = scrollArea->viewport()->width();
			qreal portHeight = scrollArea->viewport()->height();
			QSizeF	pageSize = gridSizeF(true) * dpi / 72.0;
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
	QAbstractScrollArea*	scrollArea = getScrollArea();
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

//TODO: optimize?
QRect PDFWidget::gridPageRect(int pageIndex) const{
	if (gridx*gridy <= 1)
		return rect();
	int totalBorderX = (gridx-1)*GridBorder;
	int totalBorderY = (gridy-1)*GridBorder;
	int realPageSizeX = (rect().width()-totalBorderX) / gridx;
	int realPageSizeY = (rect().height()-totalBorderY) / gridy;

	QPoint p((realPageSizeX+GridBorder)*(pageIndex % gridx), (realPageSizeY+GridBorder)*(pageIndex / gridx));
	return QRect(p,QPoint(p.x()+realPageSizeX, p.y()+realPageSizeY));
}

QPoint PDFWidget::gridPagePosition(int pageIndex) const{
	return gridPageRect(pageIndex).topLeft();
}

int PDFWidget::gridPageIndex(const QPoint& position) const{
	if (pages.size()==0) return -1;
	if (pages.size()==1) return 0;
	for (int i=0;i<pages.size();i++)
		if (gridPageRect(i).contains(position))
			return i;
	return -1;
}

int PDFWidget::gridPage(const QPoint& position) const{
	int index = gridPageIndex(position);
	if (index<0) return 0;
	return pages[index];
}

void PDFWidget::gridMapToScaledPosition(const QPoint& position, int & page, QPointF& scaledPos) const{
	int pageIndex = gridPageIndex(position);
	page = -1;
	if (pageIndex<0) return;
	page = pages[pageIndex];
	QPoint rp = position - gridPagePosition(pageIndex);
	// poppler's pos is relative to the page rect
	Poppler::Page *popplerPage=document->page(page);
	scaledPos = QPointF(rp.x() / scaleFactor / dpi * 72.0 / popplerPage->pageSizeF().width(),
			      rp.y() / scaleFactor / dpi * 72.0 / popplerPage->pageSizeF().height());
	delete popplerPage;

}

QPoint PDFWidget::gridMapFromScaledPosition(const QPointF& scaledPos) const {
	if (pages.size() == 0) return QPoint();
	QRect r = gridPageRect(0);
	int i=pages.first();
	Poppler::Page *popplerPage=document->page(i);
	int w=popplerPage->pageSizeF().width();
	int h=popplerPage->pageSizeF().height();
	delete popplerPage;
	return (QPointF(scaledPos.x() * w, scaledPos.y() * h)   * scaleFactor * dpi / 72.0 ).toPoint();

}

QSizeF PDFWidget::maxPageSizeF() const{
	QSizeF maxPageSize;
	foreach (int page, pages) {
		Poppler::Page *popplerPage=document->page(page);
		if (popplerPage->pageSizeF().width() > maxPageSize.width()) maxPageSize.setWidth(popplerPage->pageSizeF().width());
		if (popplerPage->pageSizeF().height() > maxPageSize.height()) maxPageSize.setHeight(popplerPage->pageSizeF().height());
		delete popplerPage;
	}
	return maxPageSize;
}
QSizeF PDFWidget::gridSizeF(bool ignoreVerticalGrid) const{
	QSizeF maxPageSize = maxPageSizeF();
	int usedy = ignoreVerticalGrid?1:gridy;
	return QSizeF(maxPageSize.width()*gridx + GridBorder*(gridx-1),
			maxPageSize.height()*usedy + GridBorder*(usedy-1));
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

PDFScrollArea* PDFWidget::getScrollArea()
{
	QWidget* parent = parentWidget();
	if (parent != NULL)
		return qobject_cast<PDFScrollArea*>(parent->parentWidget());
	else
		return NULL;
}


//#pragma mark === PDFDocument ===

QList<PDFDocument*> PDFDocument::docList;

PDFDocument::PDFDocument(PDFDocumentConfig* const pdfConfig)
    : renderManager(this),exitFullscreen(0), watcher(NULL), reloadTimer(NULL),scanner(NULL),syncFromSourceBlock(false)
{
	Q_ASSERT(pdfConfig);
	Q_ASSERT(!globalConfig || (globalConfig == pdfConfig));
	globalConfig = pdfConfig,

	init();

	watcher = new QFileSystemWatcher(this);
	connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(reloadWhenIdle()));

	QRect screen = QApplication::desktop()->screenGeometry();
	while (globalConfig->windowLeft > screen.width() && screen.width() > 0)
		globalConfig->windowLeft-=screen.width();
	while (globalConfig->windowTop > screen.height() && screen.height() > 0)
		globalConfig->windowTop-=screen.height();

	setWindowState(Qt::WindowNoState);
	resize(globalConfig->windowWidth, globalConfig->windowHeight); //important to first resize then move
	move(globalConfig->windowLeft, globalConfig->windowTop);
	Q_ASSERT(x() == globalConfig->windowLeft);
	if (!globalConfig->windowState.isEmpty()) restoreState(globalConfig->windowState);
}

PDFDocument::~PDFDocument()
{
	renderManager.stopRendering();
	emit documentClosed();
	if (scanner != NULL)
		synctex_scanner_free(scanner);
	docList.removeAll(this);
	if (document)
		delete document;
}

void
PDFDocument::init()
{
	ConfigManagerInterface *conf = ConfigManagerInterface::getInstance();

	docList.append(this);

	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_MacNoClickThrough, true);

	//load icons
	setWindowIcon(QIcon(":/images/previewicon.png"));
	
	actionFirst_Page->setIcon(getRealIcon("go-first"));
	actionPrevious_Page->setIcon(getRealIcon("go-previous"));
	actionNext_Page->setIcon(getRealIcon("go-next"));
	actionLast_Page->setIcon(getRealIcon("go-last"));
	actionZoom_In->setIcon(getRealIcon("zoom-in"));
	actionZoom_Out->setIcon(getRealIcon("zoom-out"));
	actionFit_to_Window->setIcon(getRealIcon("zoom-fit-best"));
	actionActual_Size->setIcon(getRealIcon("zoom-original"));
	actionFit_to_Width->setIcon(getRealIcon("zoom-fit-width"));
	actionNew->setIcon(getRealIcon("filenew"));
	actionOpen->setIcon(getRealIcon("fileopen"));
	actionClose->setIcon(getRealIcon("fileclose"));
	actionUndo->setIcon(getRealIcon("undo"));
	actionRedo->setIcon(getRealIcon("redo"));
	actionCut->setIcon(getRealIcon("cut"));
	actionCopy->setIcon(getRealIcon("copy"));
	actionPaste->setIcon(getRealIcon("paste"));
	actionMagnify->setIcon(getRealIcon("zoom-in"));
	actionScroll->setIcon(getRealIcon("hand"));
	actionTypeset->setIcon(QIcon(":/images/quick.png"));
	actionExternalViewer->setIcon(QIcon(":/images/viewpdf.png"));

	setContextMenuPolicy(Qt::NoContextMenu);

	pdfWidget = new PDFWidget;

	toolButtonGroup = new QButtonGroup(toolBar);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionMagnify)), kMagnifier);
	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionScroll)), kScroll);
//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Text)), kSelectText);
//	toolButtonGroup->addButton(qobject_cast<QAbstractButton*>(toolBar->widgetForAction(actionSelect_Image)), kSelectImage);
	connect(toolButtonGroup, SIGNAL(buttonClicked(int)), pdfWidget, SLOT(setTool(int)));
	pdfWidget->setTool(kMagnifier);

	QStringList lst;
	lst << "25%" << "50%" << "75%" << "100%" << "150%" << "200%" << "300%" << "400%";
	QFontMetrics fontMetrics(font());
	comboZoom=createComboToolButton(toolBar,lst,0,fontMetrics,this,SLOT(setZoom()),"100%");
	toolBar->addWidget(comboZoom);
	addAction(toolBar->toggleViewAction());

	leCurrentPage=new QLineEdit(toolBar);
	leCurrentPage->setMaxLength(5);
	leCurrentPage->setFixedWidth(fontMetrics.width("#####"));
	leCurrentPageValidator=new QIntValidator(1,99999,leCurrentPage);
	leCurrentPage->setValidator(leCurrentPageValidator);
	leCurrentPage->setText("1");
	leCurrentPage->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	connect(leCurrentPage,SIGNAL(returnPressed()),this,SLOT(jumpToPage()));
	pageCountLabel=new QLabel(toolBar);
	pageCountLabel->setText(tr("of %1").arg(1));
	toolBar->insertWidget(actionNext_Page, leCurrentPage);
	toolBar->insertWidget(actionNext_Page, pageCountLabel);

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
	//scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setPDFWidget(pdfWidget);
	setCentralWidget(scrollArea);
	
	connect(scrollArea, SIGNAL(resized()), pdfWidget, SLOT(windowResized()));

	document = NULL;
	
	connect(actionAbout_TW, SIGNAL(triggered()), SIGNAL(triggeredAbout()));
	connect(actionUserManual, SIGNAL(triggered()), SIGNAL(triggeredManual()));


	connect(actionQuit_TeXworks, SIGNAL(triggered()), SIGNAL(triggeredQuit()));

	connect(actionFind_2, SIGNAL(triggered()), this, SLOT(doFindDialog()));
	connect(actionFind_again, SIGNAL(triggered()), this, SLOT(doFindAgain()));

	connect(actionFirst_Page, SIGNAL(triggered()), pdfWidget, SLOT(goFirst()));
	connect(actionPrevious_Page, SIGNAL(triggered()), pdfWidget, SLOT(goPrev()));
	connect(actionNext_Page, SIGNAL(triggered()), pdfWidget, SLOT(goNext()));
	connect(actionLast_Page, SIGNAL(triggered()), pdfWidget, SLOT(goLast()));
	connect(actionGo_to_Page, SIGNAL(triggered()), pdfWidget, SLOT(doPageDialog()));
	connect(pdfWidget, SIGNAL(changedPage(int,bool)), this, SLOT(enablePageActions(int,bool)));

	connect(actionActual_Size, SIGNAL(triggered()), pdfWidget, SLOT(fixedScale()));
	connect(actionFit_to_Width, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWidth(bool)));
	connect(actionFit_to_Window, SIGNAL(triggered(bool)), pdfWidget, SLOT(fitWindow(bool)));

	connect(actionGrid11, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid12, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid21, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid22, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid23, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionGrid33, SIGNAL(triggered()), SLOT(setGrid()));
	connect(actionCustom, SIGNAL(triggered()), SLOT(setGrid()));

	connect(actionSinglePageStep, SIGNAL(toggled(bool)), pdfWidget, SLOT(setSinglePageStep(bool)));
	conf->registerOption("Preview/Single Page Step", &globalConfig->singlepagestep, true);
	conf->linkOptionToObject(&globalConfig->singlepagestep, actionSinglePageStep, 0);
	connect(actionContinuous, SIGNAL(toggled(bool)), scrollArea, SLOT(setContinuous(bool)));
	conf->registerOption("Preview/Continuous", &globalConfig->continuous, true);
	conf->linkOptionToObject(&globalConfig->continuous, actionContinuous, 0);

	connect(actionZoom_In, SIGNAL(triggered()), pdfWidget, SLOT(zoomIn()));
	connect(actionZoom_Out, SIGNAL(triggered()), pdfWidget, SLOT(zoomOut()));
	connect(actionFull_Screen, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen(bool)));
	connect(actionPresentation, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen(bool)));
	connect(pdfWidget, SIGNAL(changedZoom(qreal)), this, SLOT(enableZoomActions(qreal)));
	connect(pdfWidget, SIGNAL(changedScaleOption(autoScaleOption)), this, SLOT(adjustScaleActions(autoScaleOption)));
	connect(pdfWidget, SIGNAL(syncClick(int, const QPointF&, bool)), this, SLOT(syncClick(int, const QPointF&, bool)));

	if (actionZoom_In->shortcut() == QKeySequence("Ctrl++"))
		new QShortcut(QKeySequence("Ctrl+="), pdfWidget, SLOT(zoomIn()));
	
	connect(actionTypeset, SIGNAL(triggered()), SIGNAL(triggeredQuickBuild()));

	connect(actionExternalViewer, SIGNAL(triggered()), SLOT(runExternalViewer()));

	connect(actionCloseSomething, SIGNAL(triggered()), SLOT(closeSomething()));
	connect(actionStack, SIGNAL(triggered()), SLOT(stackWindows()));
	connect(actionTile, SIGNAL(triggered()), SLOT(tileWindows()));
	connect(actionSide_by_Side, SIGNAL(triggered()), this, SLOT(sideBySide()));
	connect(actionGo_to_Source, SIGNAL(triggered()), this, SLOT(goToSource()));
	connect(actionNew_Window, SIGNAL(triggered()), SIGNAL(triggeredClone()));

	conf->registerOption("Preview/Scrolling Follows Cursor", &globalConfig->followFromCursor, false);
	conf->linkOptionToObject(&globalConfig->followFromCursor, actionScrolling_follows_cursor);
	conf->registerOption("Preview/Cursor Follows Scrolling", &globalConfig->followFromScroll, false);
	conf->linkOptionToObject(&globalConfig->followFromScroll, actionCursor_follows_scrolling);
	conf->registerOption("Preview/Sync Multiple Views", &globalConfig->syncViews, true);
	conf->linkOptionToObject(&globalConfig->syncViews, actionSynchronize_multiple_views);

	connect(actionPreferences, SIGNAL(triggered()), SIGNAL(triggeredConfigure()));

	menuShow->addAction(toolBar->toggleViewAction());
	menuShow->addSeparator();

	QDockWidget *dw = dwOutline = new PDFOutlineDock(this);
//	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int,bool)), dw, SLOT(pageChanged(int)));

	dw = dwInfo = new PDFInfoDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int,bool)), dw, SLOT(pageChanged(int)));

	dw = dwSearch = new PDFSearchDock(this);
	connect(dwSearch, SIGNAL(search(bool,bool)),  SLOT(search(bool,bool)));
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());

	dw = dwFonts = new PDFFontsDock(this);
	dw->hide();
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int,bool)), dw, SLOT(pageChanged(int)));

	dw = dwOverview = new PDFOverviewDock(this);
	dw->hide();
	addDockWidget(Qt::LeftDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(this, SIGNAL(reloaded()), dw, SLOT(documentLoaded()));
	connect(this, SIGNAL(documentClosed()), dw, SLOT(documentClosed()));
	connect(pdfWidget, SIGNAL(changedPage(int,bool)), dw, SLOT(pageChanged(int)));

	dw = dwClock = new PDFClockDock(this);
	dw->hide();
	addDockWidget(Qt::BottomDockWidgetArea, dw);
	menuShow->addAction(dw->toggleViewAction());
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(pageChanged(int)));
	connect(pdfWidget, SIGNAL(changedPage(int, bool)), dw, SLOT(update()));
}

bool PDFDocument::followCursor() const{
	Q_ASSERT(globalConfig);
	if (!globalConfig) return false;
	return globalConfig->followFromCursor;
}

void PDFDocument::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange) {
		QString title = windowTitle();
		retranslateUi(this);
		setWindowTitle(title);
		if (pdfWidget && pdfWidget->isVisible())
			pdfWidget->updateStatusBar();
	}
	else
		QMainWindow::changeEvent(event);
}


void PDFDocument::sideBySide()
{
	QWidget* mainWindow = 0;
	foreach (QWidget *widget, QApplication::topLevelWidgets())
		if (!widget->isHidden() && widget != this &&  qobject_cast<QMainWindow*>(widget) != 0){
			mainWindow = widget;
			break;
		}
	if (mainWindow){
		windowsSideBySide(mainWindow, this);
		windowsSideBySide(mainWindow, this); //???first call fails on linux with qt4.6.3???? (position is correct, but move doesn't move there, although it works in texworks)
	}
}

void PDFDocument::closeEvent(QCloseEvent *event)
{
	Q_ASSERT(globalConfig);
	if (isVisible()) {
		globalConfig->windowLeft = x();
		globalConfig->windowTop = y();
		globalConfig->windowWidth = width();
		globalConfig->windowHeight = height();
		globalConfig->windowState = saveState();
	}
	event->accept();
	deleteLater();
}

void PDFDocument::syncFromView(const QString& pdfFile, const QString& externalViewer, int page){
	if (!actionSynchronize_multiple_views->isChecked())
		return;
	if (pdfFile != curFile || externalViewerCmdLine != externalViewer)
		loadFile(pdfFile, externalViewer, false);
	if (page != widget()->getCurrentPageIndex())
		scrollArea->goToPage(page,false);
}

void PDFDocument::loadFile(const QString &fileName, const QString& externalViewer, bool alert)
{
	externalViewerCmdLine = externalViewer;
	setCurrentFile(fileName);
	reload();
	if (watcher) {
		const QStringList files = watcher->files();
		if (!files.isEmpty())
			watcher->removePaths(files); // in case we ever load different files into the same widget
		watcher->addPath(curFile);
	}
	if (alert) {
		raise();
		show();
		setFocus();
		if (scrollArea) scrollArea->setFocus();
	}

}

void PDFDocument::reload()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	if (scanner != NULL) {
		synctex_scanner_free(scanner);
		scanner = NULL;
	}


	emit documentClosed();
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
			//reinitialize rendermanager
			renderManager.setDocument(curFile);

			document->setRenderBackend(Poppler::Document::SplashBackend);
			document->setRenderHint(Poppler::Document::Antialiasing);
			document->setRenderHint(Poppler::Document::TextAntialiasing);
//			globalParams->setScreenType(screenDispersed);

			pdfWidget->setDocument(document);
			pdfWidget->show();
			pdfWidget->setFocus();

			// set page viewer only once
			QFontMetrics fontMetrics(font());
			QString placeHolder = "#";
			for (int i=0; i<=log10(document->numPages()); i++) {
				placeHolder.append("#");
			}
			leCurrentPage->setFixedWidth(fontMetrics.width(placeHolder));
			leCurrentPageValidator->setTop(document->numPages());

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

void PDFDocument::runExternalViewer(){
	emit runCommand(externalViewerCmdLine);
}

void PDFDocument::setGrid(){
	REQUIRE(pdfWidget && sender());
	QString gs = sender()->property("grid").toString();
	if (gs == "xx") {
		UniversalInputDialog d;
		int x=1,y=1;
		d.addVariable(&x ,"X-Grid:");
		d.addVariable(&y ,"Y-Grid:");
		if (d.exec())
			pdfWidget->setGridSize(x,y);
	} else {
		REQUIRE(gs.size()==2)
		pdfWidget->setGridSize(gs.at(0).toAscii()-'0', gs.at(1).toAscii()-'0');
	}
	pdfWidget->windowResized();
}

void PDFDocument::jumpToPage(){
    int index=leCurrentPage->text().toInt();
    scrollArea->goToPage(index-1);
}

void PDFDocument::closeSomething(){
	if(actionPresentation->isChecked()){
	    //restore state of docks
	    if(dwVisSearch)
		dwSearch->show();
	    if(dwVisFonts)
		dwFonts->show();
	    if(dwVisInfo)
		dwInfo->show();
	    if(dwVisOutline)
		dwOutline->show();
	    if(dwVisOverview)
		dwOverview->show();
	}
	if (actionFull_Screen->isChecked() || actionPresentation->isChecked()) toggleFullScreen(false);
	else if (dwFonts && dwFonts->isVisible()) dwFonts->hide();
	else if (dwSearch && dwSearch->isVisible()) dwSearch->hide();
	else if (dwInfo && dwInfo->isVisible()) dwInfo->hide();
	else if (dwClock && dwClock->isVisible()) dwClock->hide();
	else if (dwOutline && dwOutline->isVisible()) dwOutline->hide();
	else if (dwOverview && dwOverview->isVisible()) dwOverview->hide();
	else actionClose->trigger();
}

void PDFDocument::tileWindows(){
	arrangeWindows(true);
}

void PDFDocument::stackWindows(){
	arrangeWindows(false);
}

void PDFDocument::arrangeWindows(bool tile){
	QDesktopWidget *desktop = QApplication::desktop();
	for (int screenIndex = 0; screenIndex < desktop->numScreens(); ++screenIndex) {
		QWidgetList windows;
		foreach (QWidget* widget, QApplication::topLevelWidgets())
			if (!widget->isHidden() && qobject_cast<QMainWindow*>(widget))
				windows << widget;
		if (windows.size() > 0)
			(*(tile?&tileWindowsInRect:&stackWindowsInRect)) (windows, desktop->availableGeometry(screenIndex));
	}
}


void PDFDocument::search(bool backwards, bool incremental){
	if (!document)
		return;

	int pageIdx;
	Poppler::Page *page;
	Poppler::Page::SearchMode searchMode = Poppler::Page::CaseInsensitive;
	Poppler::Page::SearchDirection searchDir; // = Poppler::Page::FromTop;
	int deltaPage, firstPage, lastPage;
	int run, runs;

	QString	searchText = dwSearch->getSearchText();
	if (searchText.isEmpty())
		return;

	if (dwSearch->hasFlagCaseSensitive())
		searchMode = Poppler::Page::CaseSensitive;

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
		lastSearchResult.selRect.setLeft(lastSearchResult.selRect.left()-0.01);
		lastSearchResult.selRect.setRight(lastSearchResult.selRect.left());
	}

	int startPage = lastSearchResult.pageIdx;
	if (lastSearchResult.pageIdx != pdfWidget->getCurrentPageIndex()) {
		if (pdfWidget->pageStep() == 1 || pdfWidget->getCurrentPageIndex() != lastSearchResult.pageIdx - lastSearchResult.pageIdx % pdfWidget->pageStep() ){			
			startPage = pdfWidget->getCurrentPageIndex();
			lastSearchResult.selRect = backwards ? QRectF(0,100000,1,1) : QRectF();
		}
	}

	for (run = 0; run < runs; ++run) {
		switch (run) {
			case 0:
				// first run = normal search
				lastPage = (backwards ? -1 : document->numPages());
				firstPage = startPage;
				break;
			case 1:
				// second run = after wrap
				lastPage = (backwards ? -1 : document->numPages());
				firstPage = (backwards ? document->numPages() - 1 : 0);
				break;
			default:
				// should not happen
				Q_ASSERT(false);
				return;
		}

		for (pageIdx = firstPage; pageIdx != lastPage; pageIdx += deltaPage) {
			page = document->page(pageIdx);

			if (page->search(searchText, lastSearchResult.selRect, searchDir, searchMode)) {
				lastSearchResult.doc = this;
				lastSearchResult.pageIdx = pageIdx;
				QPainterPath p;
				p.addRect(lastSearchResult.selRect);

				if (hasSyncData() && dwSearch->hasFlagSync())
					emit syncClick(pageIdx, lastSearchResult.selRect.center(), false);


				scrollArea->goToPage(lastSearchResult.pageIdx);
				pdfWidget->setHighlightPath(lastSearchResult.pageIdx, p);
				pdfWidget->update();

				delete page;

				return;
			}

			lastSearchResult.selRect = backwards ? QRectF(0,100000,1,1) : QRectF();
			searchDir = (backwards ? Poppler::Page::PreviousResult : Poppler::Page::NextResult);

			delete page;
		}
	}
}

void PDFDocument::loadSyncData()
{
	scanner = synctex_scanner_new_with_output_file(curFile.toUtf8().data(), NULL, 1);
	if (scanner == NULL)
		statusBar()->showMessage(tr("No SyncTeX data available"), 3000);
	else {
		QString synctexName = QString::fromUtf8(synctex_scanner_get_synctex(scanner));
		statusBar()->showMessage(tr("SyncTeX: \"%1\"").arg(synctexName), 3000);
	}
}

void PDFDocument::syncClick(int pageIndex, const QPointF& pos, bool activate)
{
	if (scanner == NULL)
		return;
	pdfWidget->setHighlightPath(-1, QPainterPath());
	pdfWidget->update();
	if (synctex_edit_query(scanner, pageIndex + 1, pos.x(), pos.y()) > 0) {
		synctex_node_t node;
		while ((node = synctex_next_result(scanner)) != NULL) {
			QString filename = QString::fromUtf8(synctex_scanner_get_name(scanner, synctex_node_tag(node)));
			QDir curDir(QFileInfo(curFile).canonicalPath());
			QString fullName = QFileInfo(curDir, filename).canonicalFilePath();
			if (!globalConfig->syncFileMask.trimmed().isEmpty()) {
				bool found = false;
				foreach (const QString& s, globalConfig->syncFileMask.split(";"))
					if (QRegExp(s.trimmed(), Qt::CaseSensitive, QRegExp::Wildcard).exactMatch(fullName)) {
						found = true;
						break;
					}
				if (!found) continue;
			}
			syncFromSourceBlock = true;
			emit syncSource(fullName, synctex_node_line(node)-1, activate); //-1 because tmx is 0 based, but synctex seems to be 1 based
			syncFromSourceBlock = false;
			break; // FIXME: currently we just take the first hit
		}
	}
}

void PDFDocument::syncFromSource(const QString& sourceFile, int lineNo, bool activatePreview)
{
	if (scanner == NULL || syncFromSourceBlock)
		return;

	lineNo++; //input 0 based, synctex 1 based

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
			scrollArea->goToPage(page - 1, false);
			path.setFillRule(Qt::WindingFill);
			pdfWidget->setHighlightPath(page-1, path);
			pdfWidget->update();
			if (activatePreview) {
				show();
				raise();
				activateWindow();
				if (isMinimized()) showNormal();
			}
		}
	}
}

void PDFDocument::setCurrentFile(const QString &fileName)
{
	curFile = QFileInfo(fileName).canonicalFilePath();
	QString niceFile = QFileInfo(curFile).fileName();
	setWindowTitle(tr("%1[*] - %2").arg(niceFile).arg(tr("TexMakerX")));
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
	Q_ASSERT(document);
	if (!document) return;
	if (pdfWidget->visiblePages() <= 1) pageLabel->setText(tr("page %1 of %2").arg(page).arg(document->numPages()));
	else pageLabel->setText(tr("pages %1 to %2 of %3").arg(page).arg(page+pdfWidget->visiblePages()-1).arg(document->numPages()));
	pageCountLabel->setText(tr("of %1").arg(document->numPages()));
	leCurrentPage->setText(QString("%1").arg(page));

}

void PDFDocument::showScale(qreal scale)
{
	scaleLabel->setText(tr("%1%").arg(ROUND(scale * 10000.0) / 100.0));
}


void PDFDocument::goToSource()
{
	Q_ASSERT(pdfWidget);
	if (!pdfWidget) return;
	pdfWidget->syncCurrentPage(true);
}

void PDFDocument::enablePageActions(int pageIndex, bool sync)
{
	//current page has changed

//#ifndef Q_WS_MAC
// On Mac OS X, disabling these leads to a crash if we hit the end of document while auto-repeating a key
// (seems like a Qt bug, but needs further investigation)
// 2008-09-07: seems to no longer be a problem, probably thanks to Qt 4.4 update
	actionFirst_Page->setEnabled(pageIndex > 0);
	actionPrevious_Page->setEnabled(pageIndex > 0);
	actionNext_Page->setEnabled(pageIndex < document->numPages() - 1);
	actionLast_Page->setEnabled(pageIndex < document->numPages() - 1);
//#endif


	Q_ASSERT(pdfWidget && globalConfig);
	if (!pdfWidget || !globalConfig) return;
	if (globalConfig->followFromScroll && sync)
		pdfWidget->syncCurrentPage(false);
	if (actionSynchronize_multiple_views->isChecked() && sync)
		emit syncView(curFile, externalViewerCmdLine, widget()->getCurrentPageIndex());;
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
		wasMaximized=isMaximized();
		showFullScreen();
		pdfWidget->saveState();
		pdfWidget->fitWindow(true);
		dwVisOutline=dwOutline->isVisible();
		dwVisOverview=dwOverview->isVisible();
		dwVisFonts=dwFonts->isVisible();
		dwVisSearch=dwSearch->isVisible();
		dwVisInfo=dwInfo->isVisible();
		if (sender() == actionPresentation){
			menuBar()->hide();
			actionFull_Screen->setChecked(false);
			actionPresentation->setChecked(true);
			exitFullscreen = new QShortcut(Qt::Key_Escape, this, SLOT(closeSomething())); //hiding the menubar disables normal shortcut
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
			} else wasContinuous=false;
		} else
			actionFull_Screen->setChecked(true);

		//actionFull_Screen->setChecked(true);
	} else {
		// exiting full-screen mode		
		statusBar()->show();
		toolBar->show();
		if(wasMaximized)
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

void PDFDocument::setZoom(){
    QAction *action=qobject_cast<QAction *>(sender());
    QString text=action->text();
    text.chop(1);
    bool ok;
    int factor=text.toInt(&ok);
    if(ok){
	pdfWidget->fixedScale(0.01*factor);
    }
    comboZoom->setDefaultAction(action);
}

void PDFDocument::setResolution(int res)
{
	if (res > 0)
		pdfWidget->setResolution(res);
}

void PDFDocument::goToDestination(const QString& destName)
{
	if (pdfWidget)
		pdfWidget->goToDestination(destName);
}

void PDFDocument::goToPage(const int page)
{
	if (pdfWidget && scrollArea) {
		scrollArea->goToPage(page);
	}
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
		foreach (const QUrl& url, urls)
			if (url.scheme() == "file") {
				if (url.path().endsWith("pdf")) loadFile(url.toLocalFile(), externalViewerCmdLine);
				else emit fileDropped(url);
			}
		event->acceptProposedAction();
	}
}

void PDFDocument::doFindDialog()
{
	dwSearch->show();
	dwSearch->setFocus();
}

void PDFDocument::doFindAgain()
{
	search(false, false);
}


#endif
