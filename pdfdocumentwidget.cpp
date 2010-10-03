/****************************************************************************
**
**   copyright       : (C) 2003-2010 by Pascal Brachet                     
**   http://www.xm1math.net/texmaker/   
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include <QtGui>
#include <QDebug>
#include <QScrollArea>
#include <poppler-qt4.h>
#include "pdfdocumentwidget.h"

PdfDocumentWidget::PdfDocumentWidget(QWidget *parent)
    : QLabel(parent)
{
    currentPage = -1;
    doc = 0;
    scaleFactor = 1.0;
    setAlignment(Qt::AlignCenter);
    currentLink=0;
    setMouseTracking(true);
}

PdfDocumentWidget::~PdfDocumentWidget()
{
    delete doc;
}

Poppler::Document *PdfDocumentWidget::document()
{
    return doc;
}

QMatrix PdfDocumentWidget::matrix() const
{
    return QMatrix(scaleFactor * physicalDpiX() / 72.0, 0,
                   0, scaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}

void PdfDocumentWidget::mousePressEvent(QMouseEvent *event)
{
if (!doc) return;
currentLink=0;
setCursor(Qt::ArrowCursor);
setPage();
foreach (Poppler::Link* link, doc->page(currentPage)->links())
  {
  QPointF scaledPos((event->pos().x()- (width() - pixmap()->width()) / 2.0) / scaleFactor / physicalDpiX() * 72.0 / doc->page(currentPage)->pageSizeF().width(),(event->pos().y()- (height() - pixmap()->height()) / 2.0) / scaleFactor / physicalDpiY() * 72.0 / doc->page(currentPage)->pageSizeF().height());
  if (link->linkArea().contains(scaledPos)) 
    {
    currentLink = link;
    break;
    }
  }
}

void PdfDocumentWidget::mouseMoveEvent(QMouseEvent *event)
{
if (!doc) return;
setCursor(Qt::ArrowCursor);
foreach (Poppler::Link* link, doc->page(currentPage)->links())
  {
  QPointF scaledPos((event->pos().x()- (width() - pixmap()->width()) / 2.0) / scaleFactor / physicalDpiX() * 72.0 / doc->page(currentPage)->pageSizeF().width(),(event->pos().y()- (height() - pixmap()->height()) / 2.0) / scaleFactor / physicalDpiY() * 72.0 / doc->page(currentPage)->pageSizeF().height());
  if (link->linkArea().contains(scaledPos)) 
    {
    setCursor(Qt::PointingHandCursor);
    break;
    }
  }
event->accept();
}

void PdfDocumentWidget::mouseReleaseEvent(QMouseEvent *event)
{
if (!doc) return;
setCursor(Qt::ArrowCursor);
if (currentLink)
  {
   QPointF scaledPos((event->pos().x()- (width() - pixmap()->width()) / 2.0) / scaleFactor / physicalDpiX() * 72.0 / doc->page(currentPage)->pageSizeF().width(),(event->pos().y()- (height() - pixmap()->height()) / 2.0) / scaleFactor / physicalDpiY() * 72.0 / doc->page(currentPage)->pageSizeF().height());
    if ((currentLink->linkArea().contains(scaledPos)) && (currentLink->linkType()==Poppler::Link::Goto))
      {
      const Poppler::LinkGoto *gotoLink = dynamic_cast<const Poppler::LinkGoto*>(currentLink);
      if (gotoLink)
	{
	const Poppler::LinkDestination dest = gotoLink->destination();
	if ((dest.pageNumber() > 0)) showPage(dest.pageNumber());
	QScrollArea* container=qobject_cast<QScrollArea*>(parentWidget()->parentWidget());
	if (container)
	  {
	  if (dest.isChangeLeft()) 
	     {
	      int destLeft = (int)floor(dest.left() * scaleFactor * physicalDpiX() / 72.0 * doc->page(currentPage)->pageSizeF().width());
	      container->horizontalScrollBar()->setValue(destLeft);
	      }
	  if (dest.isChangeTop()) 
	      {
	      int destTop = (int)floor(dest.top() * scaleFactor * physicalDpiY() / 72.0 * doc->page(currentPage)->pageSizeF().height());
	      container->verticalScrollBar()->setValue(destTop);
	      }
	  }
	}
      }    
  }
currentLink=0;
}

qreal PdfDocumentWidget::scale() const
{
    return scaleFactor;
}

void PdfDocumentWidget::showPage(int page)
{
    if (page != -1 && page != currentPage + 1) {
        currentPage = page - 1;
        emit pageChanged(page);
    }

    QImage image = doc->page(currentPage)
                      ->renderToImage(scaleFactor * physicalDpiX(), scaleFactor * physicalDpiY());

    if (!searchLocation.isEmpty()) {
        QRect highlightRect = matrix().mapRect(searchLocation).toRect();
        highlightRect.adjust(-2, -2, 2, 2);
        QImage highlight = image.copy(highlightRect);
        QPainter painter;
        painter.begin(&image);
        painter.fillRect(image.rect(), QColor(0, 0, 0, 32));
        painter.drawImage(highlightRect, highlight);
        painter.end();
    }

    setPixmap(QPixmap::fromImage(image));
}

QRectF PdfDocumentWidget::searchBackwards(const QString &text)
{
    QRectF oldLocation = searchLocation;

    int page = currentPage;
    if (oldLocation.isNull())
        page -= 1;

    while (page > -1) {

        QList<QRectF> locations;
        searchLocation = QRectF();

        while (doc->page(page)->search(text, searchLocation,
            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

            if (searchLocation != oldLocation)
                locations.append(searchLocation);
            else
                break;
        }

        int index = locations.indexOf(oldLocation);
        if (index == -1 && !locations.isEmpty()) {
            searchLocation = locations.last();
            showPage(page + 1);
            return searchLocation;
        } else if (index > 0) {
            searchLocation = locations[index - 1];
            showPage(page + 1);
            return searchLocation;
        }

        oldLocation = QRectF();
        page -= 1;
    }

    if (currentPage == doc->numPages() - 1)
        return QRectF();

    oldLocation = QRectF();
    page = doc->numPages() - 1;

    while (page > currentPage) {

        QList<QRectF> locations;
        searchLocation = QRectF();

        while (doc->page(page)->search(text, searchLocation,
            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {

            locations.append(searchLocation);
        }

        if (!locations.isEmpty()) {
            searchLocation = locations.last();
            showPage(page + 1);
            return searchLocation;
        }
        page -= 1;
    }

    return QRectF();
}

QRectF PdfDocumentWidget::searchForwards(const QString &text)
{
    int page = currentPage;
    while (page < doc->numPages()) {

        if (doc->page(page)->search(text, searchLocation,
            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {
            if (!searchLocation.isNull()) {
                showPage(page + 1);
                return searchLocation;
            }
        }
        page += 1;
        searchLocation = QRectF();
    }

    page = 0;

    while (page < currentPage) {

        searchLocation = QRectF();

        if (doc->page(page)->search(text, searchLocation,
            Poppler::Page::NextResult, Poppler::Page::CaseInsensitive)) {
            if (!searchLocation.isNull()) {
                showPage(page + 1);
                return searchLocation;
            }
        }
        page += 1;
    }

    return QRectF();
}

bool PdfDocumentWidget::setDocument(const QString &filePath)
{
    Poppler::Document *oldDocument = doc;

    doc = Poppler::Document::load(filePath);
    if (doc) {
        delete oldDocument;
        doc->setRenderHint(Poppler::Document::Antialiasing);
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        searchLocation = QRectF();
        currentPage = -1;
        setPage(1);
    }
    return doc != 0;
}

void PdfDocumentWidget::setPage(int page)
{
    if (page != currentPage + 1) {
        searchLocation = QRectF();
        showPage(page);
    }
}

void PdfDocumentWidget::setScale(qreal scale)
{
    if (scaleFactor != scale) {
        scaleFactor = scale;
        showPage();
    }
}
