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

#ifndef PDFDocument_H
#define PDFDocument_H

#ifndef NO_POPPLER_PREVIEW


#include "mostQtHeaders.h"

//#include "FindDialog.h"
#include "poppler-qt4.h"
#include "synctex_parser.h"

#include "ui_PDFDocument.h"
#include <QMutex>

const int kPDFWindowStateVersion = 1;

class QAction;
class QMenu;
class QToolBar;
class QScrollArea;
class QShortcut;
class QFileSystemWatcher;
class ConfigManagerInterface;

class PDFMagnifier : public QLabel
{
	Q_OBJECT

public:
	PDFMagnifier(QWidget *parent, qreal inDpi);
	void setPage(Poppler::Page *p, qreal scale, const QPoint& offset);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private:
	Poppler::Page	*page;
	qreal	scaleFactor;
	qreal	parentDpi;
	QImage	image;
	
	QPoint	imageLoc;
	QSize	imageSize;
	qreal	imageDpi;
	Poppler::Page	*imagePage;
};

typedef enum {
	kFixedMag,
	kFitWidth,
	kFitWindow
} autoScaleOption;

class PDFScrollArea;
class PDFWidget : public QLabel
{
	Q_OBJECT

public:
	PDFWidget();
	virtual ~PDFWidget();
	
	void setDocument(Poppler::Document *doc);

	void saveState(); // used when toggling full screen mode
	void restoreState();
	void setResolution(int res);
	void resetMagnifier();
	void goToPage(int pageIndex, bool sync = true);
	void setHighlightPath(const int pageIndex, const QPainterPath& path);
	int getHighlightPage() const;
	void goToDestination(const QString& destName);
	int getCurrentPageIndex() { return pageIndex; }
	void reloadPage(bool sync = true);
	void updateStatusBar();
	void setGridSize(int gx, int gy);
	int visiblePages() const;
	int numPages() const;
	int pageStep() const;
	int gridCols() const;
	int gridRowHeight() const;

	QMutex renderMutex;

private slots:
	void goFirst();
	void goPrev();
	void goNext();
	void goLast();
	void doPageDialog();
	
	void fitWidth(bool checked = true);
	void zoomIn();
	void zoomOut();
	void jumpToSource();
	
	void upOrPrev();
	void leftOrPrev();
	void pageUpOrPrev();

	void downOrNext();
	void rightOrNext();
	void pageDownOrNext();

	void clearHighlight();
	
public slots:
	void setSinglePageStep(bool step);
	void windowResized();
	void fitWindow(bool checked = true);
	void setTool(int tool);	
	void syncWindowClick(int x, int y, bool activate, int page = -1);
	void syncCurrentPage(bool activate);
	void fixedScale(qreal scale = 1.0);

signals:
	void changedPage(int, bool);
	void changedZoom(qreal);
	void changedScaleOption(autoScaleOption);
	void syncClick(int, const QPointF&, bool activate); //page position in page coordinates

protected:
	virtual void paintEvent(QPaintEvent *event);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

	virtual void focusInEvent(QFocusEvent *event);

	virtual void contextMenuEvent(QContextMenuEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	void init();
	void adjustSize();
	void updateCursor();
	void updateCursor(const QPoint& pos);
	void useMagnifier(const QMouseEvent *inEvent);
	void goToDestination(const Poppler::LinkDestination& dest);
	void doLink(const Poppler::Link *link);
	void doZoom(const QPoint& clickPos, int dir);

	QPoint gridPagePosition(int pageIndex) const;
	QRect gridPageRect(int pageIndex) const;
	int gridPageIndex(const QPoint& position) const;
	Poppler::Page* gridPage(const QPoint& position) const;
	void gridMapToScaledPosition(const QPoint& position, Poppler::Page*& page, QPointF& scaledPos) const;
	QPoint gridMapFromScaledPosition(const QPointF& scaledPos) const;
	QSizeF maxPageSizeF() const;
	QSizeF gridSizeF() const;

	PDFScrollArea* getScrollArea();
	
	Poppler::Document	*document;
	QList<Poppler::Page*> pages;
	Poppler::Link		*clickedLink;

	int pageIndex, oldPageIndex;
	qreal	scaleFactor;
	qreal	dpi;
	autoScaleOption scaleOption;

	qreal			saveScaleFactor;
	autoScaleOption	saveScaleOption;

	QAction	*ctxZoomInAction;
	QAction	*ctxZoomOutAction;
	QShortcut *shortcutUp;
	QShortcut *shortcutLeft;
	QShortcut *shortcutDown;
	QShortcut *shortcutRight;
	QShortcut *shortcutPageUp1;
	QShortcut *shortcutPageUp2;
	QShortcut *shortcutPageUp3;
	QShortcut *shortcutPageUp4;
	QShortcut *shortcutPageDown1;
	QShortcut *shortcutPageDown2;
	QShortcut *shortcutPageDown3;
	QShortcut *shortcutPageDown4;

	QImage	image;
	QRect	imageRect;
	qreal	imageDpi;
	Poppler::Page	*imagePage;

	PDFMagnifier	*magnifier;
	int		currentTool;	// the current tool selected in the toolbar
	int		usingTool;	// the tool actually being used in an ongoing mouse drag
	bool		singlePageStep;

	int gridx, gridy;

	QPainterPath	highlightPath;
	int highlightPage;
	QTimer highlightRemover;
	
	static QCursor	*magnifierCursor;
	static QCursor	*zoomInCursor;
	static QCursor	*zoomOutCursor;
};


class PDFDocument;
class PDFSearchResult {
public:
	PDFSearchResult(const PDFDocument* pdfdoc = NULL, int page = -1, QRectF rect = QRectF())
		: doc(pdfdoc), pageIdx(page), selRect(rect)
		{ }

	const PDFDocument* doc;
	int pageIdx;
	QRectF selRect;
};



class PDFDocumentConfig;
class PDFDock;
class PDFSearchDock;
class PDFScrollArea;
class PDFDocument : public QMainWindow, private Ui::PDFDocument
{
	Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName)

public:
	PDFDocument(PDFDocumentConfig* const pdfConfig );
	virtual ~PDFDocument();

	static PDFDocument *findDocument(const QString &fileName);
	static QList<PDFDocument*> documentList()
		{
			return docList;
		}

	QString fileName() const { return curFile; }
	QString externalViewer() const { return externalViewerCmdLine; }

	void zoomToRight(QWidget *otherWindow);
	void showScale(qreal scale);
	void showPage(int page);
	void setResolution(int res);
	void resetMagnifier();
	void goToDestination(const QString& destName);
	void goToPage(const int page);
	bool hasSyncData()
		{
			return scanner != NULL;
		}

	Poppler::Document *popplerDoc()
		{
			return document;
		}
	
	PDFWidget *widget()
		{
			return pdfWidget;
		}

	bool followCursor() const;

protected:
	virtual void changeEvent(QEvent *event);
	virtual void closeEvent(QCloseEvent *event);
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);

public slots:
	void reload();
	void sideBySide();
	void doFindDialog();
	void doFindAgain();
	void goToSource();
	void toggleFullScreen(const bool fullscreen);
	void syncFromSource(const QString& sourceFile, int lineNo, bool activatePreview); //lineNo 0 based
	void syncFromView(const QString& pdfFile, const QString& externalViewer, int page);
	void loadFile(const QString &fileName, const QString& externalViewer, bool alert = true);

private slots:
	void enablePageActions(int, bool);
	void enableZoomActions(qreal);
	void adjustScaleActions(autoScaleOption);
	void syncClick(int page, const QPointF& pos, bool activate);
	void reloadWhenIdle();

	void runExternalViewer();

	void setGrid();

	void closeSomething();
	void tileWindows();
	void stackWindows();
	void arrangeWindows(bool tile);

	void followingToggled();

	void jumpToPage();

	void search(bool backward, bool incremental);
	void setZoom();
signals:
	void documentClosed();
	void reloaded();
	void syncSource(const QString& sourceFile, int line, bool activate); //view -> source
	void syncView(const QString& pdfFile, const QString& externalViewer, int page); //view -> other view
	void fileDropped(const QUrl& url);

	void runCommand(const QString& command);

	void triggeredAbout();
	void triggeredManual();
	void triggeredQuit();
	void triggeredPlaceOnLeft();
	void triggeredConfigure();
	void triggeredQuickBuild();

	void triggeredClone();

private:
	void init();
	void setCurrentFile(const QString &fileName);
	void loadSyncData();

	QString curFile;
	QString externalViewerCmdLine;

	Poppler::Document	*document;
	
	PDFWidget	*pdfWidget;
	PDFScrollArea	*scrollArea;
	QButtonGroup	*toolButtonGroup;
	QToolButton *comboZoom;
	QLineEdit *leCurrentPage;
	QLabel *pageCountLabel;
	QIntValidator *leCurrentPageValidator;

	QLabel *pageLabel;
	QLabel *scaleLabel;
	QList<QAction*> recentFileActions;
	QShortcut* exitFullscreen;

	QFileSystemWatcher *watcher;
	QTimer *reloadTimer;
	
	synctex_scanner_t scanner;
	
	static QList<PDFDocument*> docList;
	
	PDFDock *dwClock, *dwOutline, *dwFonts, *dwInfo, *dwOverview;
	bool dwVisOutline,dwVisFonts,dwVisInfo,dwVisSearch,dwVisOverview;
	PDFSearchDock *dwSearch;

	PDFSearchResult lastSearchResult;
	// stores the page idx a search was started on
	// after wrapping the search will continue only up to this page
	int firstSearchPage;

	bool wasMaximized;
	bool syncFromSourceBlock;  //temporary disable sync from source
};

#endif

#endif
