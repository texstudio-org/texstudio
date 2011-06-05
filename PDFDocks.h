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

#ifndef NO_POPPLER_PREVIEW


#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QScrollArea>
#include <QDateTime>

#include "poppler-qt4.h"
#include "pdfrendermanager.h"

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


class QToolButton;
class QGridLayout;
class QCheckBox;
class PDFBaseSearchDock : public QDockWidget{
	Q_OBJECT
	//TODO: some how merge this with the qce search panel
public:
	PDFBaseSearchDock(PDFDocument* doc = 0);

	QString getSearchText() const;
	bool hasFlagCaseSensitive() const;

	virtual void setFocus();

signals:
	void search(bool backward, bool incremental);
protected:
	virtual void resizeEvent(QResizeEvent *e);
	virtual bool eventFilter(QObject *o, QEvent *e);

	QList<QWidget*> listOfWidget;
	QGridLayout *gridLayout1;

private slots:
	void on_leFind_textEdited(const QString& text);
	void on_bNext_clicked();
	void on_bPrevious_clicked();
private:
	PDFDocument *document;

	int minimum_width;
	//QToolButton *bClose;
	QLineEdit *leFind;
	QToolButton *bNext, *bPrevious, *bCount;
	QCheckBox *cbCase;
	/*QCheckBox *cbWords;
	QCheckBox *cbRegExp;*/
/*	QCheckBox *cbHighlight;
	QCheckBox *cbCursor;
	QCheckBox *cbSelection;*/
};

class PDFSearchDock : public PDFBaseSearchDock {
	Q_OBJECT
public:
	PDFSearchDock(PDFDocument* doc = 0);

	bool hasFlagSync() const;
private:
	QCheckBox *cbSync;
};

class PDFWidget;
class PDFScrollArea : public QAbstractScrollArea
{
	Q_OBJECT

public:
	PDFScrollArea(QWidget *parent = NULL);
	void setPDFWidget(PDFWidget* widget);
	void ensureVisible(int x, int y, int xmargin=50, int ymargin=50);
	void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy);
	bool getContinuous(){
	    return continuous;
	}

	virtual ~PDFScrollArea();

public slots:
	void setContinuous(bool cont);
	void goToPage(int page, bool sync=true);
	void ensureVisiblePageAbsolutePos(int page, const QPointF& pos, int xmargin=50, int ymargin=50);

protected:
	bool event(QEvent *);
	bool eventFilter(QObject *, QEvent *);
	void wheelEvent(QWheelEvent *);
	void resizeEvent(QResizeEvent *event);
	void scrollContentsBy(int dx, int dy);

signals:
	void resized();

private:
	void updateWidgetPosition();
	void updateScrollBars();
	bool continuous;
	PDFWidget* pdf;
	int updateWidgetPositionStackWatch, onResizeStackWatch;
};

class PDFOverviewDock : public PDFDock
{
	Q_OBJECT

public:
	PDFOverviewDock(PDFDocument *doc = 0);
	virtual ~PDFOverviewDock();

public slots:
	virtual void documentClosed();
	virtual void pageChanged(int page);
	void insertImage(QPixmap image,int page);

protected:
	virtual void fillInfo();
	virtual QString getTitle() { return tr("Overview"); }

protected slots:
	virtual void changeLanguage();

private slots:
	void followTocSelection();
	void showImage();

private:
	QListWidget *list;
        int toGenerate;
	bool dontFollow;
};


class PDFClockDock: public PDFDock
{
	Q_OBJECT

public:
	PDFClockDock(PDFDocument *parent = NULL);
	virtual ~PDFClockDock();

private slots:
	void onTimer();
	void restart();
	void setInterval();
protected:
	//virtual void pageChanged(int page);
	virtual void fillInfo();
	virtual QString getTitle();
	virtual void paintEvent(QPaintEvent *event);

	QDateTime start, end;
	QTimer* timer;
};


#endif

#endif
