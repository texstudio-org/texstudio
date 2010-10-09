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

#ifndef PDFDOCKS_H
#define PDFDOCKS_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QScrollArea>

#include "poppler-qt4.h"

class PDFDocument;
class QListWidget;
class QTableWidget;
class QTreeWidgetItem;

class PDFDock : public QDockWidget
{
	Q_OBJECT

public:
	PDFDock(PDFDocument *doc = 0);
	virtual ~PDFDock();

	void setPage(int page);

public slots:
	virtual void documentLoaded();
	virtual void documentClosed();
	virtual void pageChanged(int page);

protected:
	virtual void fillInfo() = 0;
	virtual QString getTitle() = 0;

	PDFDocument *document;
	bool filled;

private slots:
	void myVisibilityChanged(bool visible);

protected slots:
	virtual void changeLanguage();
};


class PDFOutlineDock : public PDFDock
{
	Q_OBJECT

public:
	PDFOutlineDock(PDFDocument *doc = 0);
	virtual ~PDFOutlineDock();

public slots:
	virtual void documentClosed();

protected:
	virtual void fillInfo();
	virtual QString getTitle() { return tr("Contents"); }

protected slots:
	virtual void changeLanguage();
	
private slots:
	void followTocSelection();

private:
	QTreeWidget *tree;
};

class PDFDockTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	PDFDockTreeWidget(QWidget* parent);
	virtual ~PDFDockTreeWidget();

	virtual QSize sizeHint() const;
};


class PDFInfoDock : public PDFDock
{
	Q_OBJECT

public:
	PDFInfoDock(PDFDocument *doc = 0);
	~PDFInfoDock();

public slots:
	virtual void documentClosed();

protected:
	virtual void fillInfo();
	virtual QString getTitle() { return tr("PDF Info"); }

private:
	QListWidget *list;
};

class PDFDockListWidget : public QListWidget
{
	Q_OBJECT

public:
	PDFDockListWidget(QWidget* parent);
	virtual ~PDFDockListWidget();

	virtual QSize sizeHint() const;
};


class PDFFontsDock : public PDFDock
{
	Q_OBJECT

public:
	PDFFontsDock(PDFDocument *doc = 0);
	~PDFFontsDock();

public slots:
	virtual void documentClosed();
	virtual void documentLoaded();

protected:
	virtual void fillInfo();
	virtual QString getTitle() { return tr("Fonts"); }
	void setHorizontalHeaderLabels();

protected slots:
	virtual void changeLanguage();

private:
	QTableWidget *table;
	QList<Poppler::FontInfo> fonts;
	bool scannedFonts;
};


class PDFScrollArea : public QScrollArea
{
	Q_OBJECT

public:
	PDFScrollArea(QWidget *parent = NULL);
	virtual ~PDFScrollArea();

protected:
	virtual void resizeEvent(QResizeEvent *event);

signals:
	void resized();
};

#endif
