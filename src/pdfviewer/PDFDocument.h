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

#ifndef Header_PDF_Document
#define Header_PDF_Document

#ifndef NO_POPPLER_PREVIEW


#include "mostQtHeaders.h"

#include <QGestureEvent>
#include <QPinchGesture>
#include <QTapGesture>
#include <QTouchEvent>
#include <QProgressDialog>
#include <QPainterPath>
#if QT_VERSION_MAJOR>5
#include "poppler-qt6.h"
#else
#include "poppler-qt5.h"
#endif
#include "poppler-version.h"
#include "qsynctex.h"

#include "pdfrendermanager.h"


const int kPDFWindowStateVersion = 1;

class QAction;
class QMenu;
class QToolBar;
class QScrollArea;
class QShortcut;
class QFileSystemWatcher;
class ConfigManagerInterface;
class PDFDocument;
class PDFWidget;

class TitledPanel;
class PDFAnnotations;
class PDFAnnotation;
class PDFAnnotationTableView;
class MessageFrame;

class PDFDraggableTool : public QLabel
{
public:
	PDFDraggableTool(QWidget* parent): QLabel(parent) {}
	virtual void reshape() = 0;
	void drawGradient(QPainter& painter, const QRect& outline, QColor color, int padding, int magnifierShape);
};

class PDFMagnifier : public PDFDraggableTool
{
	Q_OBJECT

public:
	PDFMagnifier(QWidget *parent, qreal inDpi);
	void setPage(int p, qreal scale, const QRect &visibleRect);
	void reshape();

public slots:
	void setImage(const QPixmap &img, int pageNr);

protected:
	virtual void paintEvent(QPaintEvent *event);
	QPixmap &getConvertedImage();

private:
	int oldshape;
	int page;
    qreal   overScale;
	qreal	scaleFactor;
	qreal	parentDpi;
	QPixmap	image;
	QPixmap	convertedImage;
	bool	convertedImageIsGrayscale;
	bool	convertedImageIsColorInverted;

	QPoint mouseTranslate;

	QPoint	imageLoc, mouseOffset;
	QSize	imageSize;
	qreal	imageDpi;
	int imagePage;
};

class PDFLaserPointer : public PDFDraggableTool {
	Q_OBJECT

public:
	PDFLaserPointer(QWidget *parent);
	void reshape();
protected:
	virtual void paintEvent(QPaintEvent *event);

};

#ifdef MEDIAPLAYER
#include <QtMultimedia>
#include <QtMultimediaWidgets>

class PDFMovie;

class PDFVideoWidget: public QVideoWidget
{
	Q_OBJECT
public:
	PDFVideoWidget(PDFWidget *parent, PDFMovie *movie);
	~PDFVideoWidget();
protected:
	void contextMenuEvent(QContextMenuEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	QMenu *popup = nullptr;
	PDFMovie *movie = nullptr;
};

class PDFMovie: public QMediaPlayer
{
	Q_OBJECT
public:
	PDFMovie(PDFWidget *parent, QSharedPointer<Poppler::MovieAnnotation> annot, int page);
	~PDFMovie();
	void place();
	void show();
//protected:
//	void contextMenuEvent(QContextMenuEvent *);
//	void mouseReleaseEvent(QMouseEvent *e);
public slots:
	void realPlay();
	void setVolumeDialog();
	void seekDialog();
private:
	QRectF boundary;
	int page;
	PDFVideoWidget *videoWidget = nullptr;
    QAudioOutput *audioOutput = nullptr;
};
#endif

typedef enum {
	kFixedMag,
	kFitWidth,
	kFitWindow,
	kFitTextWidth
} autoScaleOption;

struct PDFPageHistoryItem{
	int page;
    double x, y;
	PDFPageHistoryItem():page(0),x(0),y(0){}
    PDFPageHistoryItem(int page, double x, double y):page(page),x(x),y(y){}
};

class PDFScrollArea;
class PDFWidget : public QLabel
{
	Q_OBJECT

public:
	explicit PDFWidget(bool embedded = false);
	virtual ~PDFWidget();

	void setDocument(const QSharedPointer<Poppler::Document> &doc);
	void setPDFDocument(PDFDocument *docu);

	void saveState(); // used when toggling full screen mode
	void restoreState();
	void setResolution(int res);
	void resetDraggableTools();
	Q_INVOKABLE int normalizedPageIndex(int pageIndex);
	Q_INVOKABLE void goToPageDirect(int pageIndex, bool sync);
    Q_INVOKABLE void setHighlightPath(const int pageIndex, const QPainterPath &path, const bool dontRemove=false);
	Q_INVOKABLE int getHighlightPage() const;
	Q_INVOKABLE void goToDestination(const QString &destName);
    Q_INVOKABLE void goToPageRelativePosition(int page, double xinpage, double yinpage);
	Q_INVOKABLE int getPageIndex();
    Q_INVOKABLE void reloadPage(bool sync = true);
	void updateStatusBar();
	void setGridSize(int gx, int gy, bool setAsDefault = false);
	void setPageOffset(int offset, bool setAsDefault = false, bool refresh = false);
	void setPageOffsetClick(const QPoint &p);
	Q_INVOKABLE int visiblePages() const;
	Q_INVOKABLE int pseudoNumPages() const;
	Q_INVOKABLE int realNumPages() const;
	Q_INVOKABLE int pageStep();
    Q_INVOKABLE int gridCols(bool fromConfig=false) const;
    Q_INVOKABLE int gridRows(bool fromConfig=false) const;
	Q_INVOKABLE int gridRowHeight() const;
	Q_INVOKABLE int gridBorder() const;
	Q_INVOKABLE PDFDocument *getPDFDocument();
	Q_INVOKABLE int getPageOffset() const;
	autoScaleOption getScaleOption() { return scaleOption; }
	double totalScaleFactor() const;

	int currentPageHistoryIndex() const;
	const QList<PDFPageHistoryItem> currentPageHistory() const;
	void updateCurrentPageHistoryOffset();

	QPoint gridPagePosition(int pageIndex) const;
	QRect gridPageRect(int pageIndex) const;
	int gridPageIndex(const QPoint &position) const;
	void mapToScaledPosition(const QPoint &position, int &page, QPointF &scaledPos) const;
	QPoint mapFromScaledPosition(int page, const QPointF &scaledPos) const;
	int pageFromPos(const QPoint &pos) const;
	QRect pageRect(int page) const;
	QSizeF maxPageSizeF() const;
	QSizeF maxPageSizeFDpiAdjusted() const;
	QRectF horizontalTextRangeF();

	Q_INVOKABLE void zoom(qreal scale);

	virtual void wheelEvent(QWheelEvent *event);

protected slots: //not private, so scripts have access
	void goFirst();
	void goPrev();
	void goNext();
	void goLast();
	void goForward();
	void goBack();
	void doPageDialog();

	void fitWidth(bool checked = true);
	void fitTextWidth(bool checked = true);
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
	void openAnnotationDialog(const PDFAnnotation *annon);

public slots:
	void setSinglePageStep(bool step);
	void windowResized();
	void fitWindow(bool checked = true);
	void setTool(int tool);
	void syncWindowClick(const QPoint &p, bool activate);
	void getPosFromClick(const QPoint &p);
	void syncCurrentPage(bool activate);
	void fixedScale(qreal scale = 1.0);
	void setImage(QPixmap img, int pageNr);
    void delayedUpdate();

signals:
	void changedPage(int, bool);
	void changedZoom(qreal);
	void changedScaleOption(autoScaleOption);
	void syncClick(int, const QPointF &, bool activate); //page position in page coordinates

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

	virtual bool event(QEvent *event);

	bool gestureEvent(QGestureEvent *event);
	bool touchEvent(QTouchEvent *event);
	void pinchEvent(QPinchGesture *gesture);
	void tapEvent(QTapGesture *gesture);

private:
    friend class PDFMagnifier;

	void init();
	void adjustSize();
	void updateCursor();
	void updateCursor(const QPoint &pos);
	QRect mapPopplerRectToWidget(QRectF rect, const QSizeF &pageSize) const;
	void useMagnifier(const QMouseEvent *inEvent);
	void useLaserPointer(const QMouseEvent *inEvent);
	void useDraggableTool(PDFDraggableTool* tool, const QMouseEvent *inEvent);
	void goToDestination(const Poppler::LinkDestination &dest);
	void doLink(const QSharedPointer<Poppler::Link> link);
	void annotationClicked(QSharedPointer<Poppler::Annotation> annotation, int page);
	void doZoom(const QPoint &clickPos, int dir, qreal newScaleFactor = 1.0);
    void doZoom(const QPointF &clickPos, int dir, qreal newScaleFactor = 1.0);

	PDFScrollArea *getScrollArea() const;

	QSharedPointer<Poppler::Document> document;
	QMutex textwidthCalculationMutex;

	//QList<int> pages;
	QSharedPointer<Poppler::Link> clickedLink;
	QSharedPointer<Poppler::Annotation> clickedAnnotation;

	int realPageIndex, oldRealPageIndex;
	QList<int> pages;
	qreal	scaleFactor;
	qreal	dpi;
	autoScaleOption scaleOption;

	bool inhibitNextContextMenuEvent;
    double summedWheelDegrees;

	int docPages;
	qreal			saveScaleFactor;
	autoScaleOption	saveScaleOption;
	
	qreal pinchZoomXPos;
	qreal pinchZoomYPos;

	QAction	*ctxZoomInAction;
	QAction	*ctxZoomOutAction;
	QShortcut *shortcutUp;
	QShortcut *shortcutLeft;
	QShortcut *shortcutDown;
	QShortcut *shortcutRight;

	QPixmap image;
	QRect	imageRect;
	qreal	imageDpi;
	int	imagePage;

	PDFMagnifier	*magnifier;
	PDFLaserPointer	*laserPointer;
#ifdef MEDIAPLAYER
	PDFMovie	*movie;
#endif
	int		currentTool;	// the current tool selected in the toolbar
	int		usingTool;	// the tool actually being used in an ongoing mouse drag
	bool		singlePageStep;

	int gridx, gridy, pageOffset;

	bool forceUpdate;

	QPainterPath	highlightPath;
	int highlightPage;
	QTimer highlightRemover;

	static QCursor	*magnifierCursor;
	static QCursor	*zoomInCursor;
	static QCursor	*zoomOutCursor;
	static QCursor	*focusedHandCursor;

	mutable QSizeF maxPageSize; //cache pageSize
	mutable QRectF horizontalTextRange;

	QList<PDFPageHistoryItem> pageHistory;
	int pageHistoryIndex;

	PDFDocument *pdfdocument;
};

class PDFSearchResult
{
public:
    explicit PDFSearchResult(const PDFDocument *pdfdoc = nullptr, int page = -1, QRectF rect = QRectF())
		: doc(pdfdoc), pageIdx(page), selRect(rect)
	{ }

	const PDFDocument *doc;
	int pageIdx;
	QRectF selRect;
};



struct PDFDocumentConfig;
class PDFDock;
class PDFSearchDock;
class PDFScrollArea;
class PDFDocument : public QMainWindow
{
	Q_OBJECT

	Q_PROPERTY(QString fileName READ fileName)

public:
	explicit PDFDocument(PDFDocumentConfig *const pdfConfig, bool embedded = false);
	virtual ~PDFDocument();

	enum DisplayFlagsEnum {
		NoDisplayFlags = 0x0000,
		FocusEmbedded = 0x0001,
		FocusWindowed = 0x0010,
		Raise = 0x0100,

		// window state independent combinations
		Focus = FocusEmbedded | FocusWindowed,
		// filter
		FilterEmbedded = 0xFF0F,
		FilterWindowed = 0xFFF0,
	};
	Q_DECLARE_FLAGS(DisplayFlags, DisplayFlagsEnum)

	static PDFDocument *findDocument(const QString &fileName);
	static QList<PDFDocument *> documentList() { return docList; }

	Q_INVOKABLE QString fileName() const { return curFile; }
	Q_INVOKABLE QFileInfo getMasterFile() const { return masterFile; }

	void saveGeometryToConfig();

	Q_INVOKABLE void zoomToRight(QWidget *otherWindow);
	void showScale(qreal scale);
	Q_INVOKABLE void showPage(int page);
	Q_INVOKABLE void setResolution(int res);
	Q_INVOKABLE void goToDestination(const QString &destName);
	Q_INVOKABLE void goToPage(const int page);
	Q_INVOKABLE void focus();
	bool hasSyncData() { return scanner.isValid(); }

	const QSharedPointer<Poppler::Document> &popplerDoc() const { return document; }

	Q_INVOKABLE PDFWidget *widget() { return pdfWidget; }
	const PDFWidget *widget() const { return pdfWidget; }

	bool followCursor() const;
	bool ignoreSynchronization() const;
	PDFRenderManager *renderManager;

	static bool isCompiling, isMaybeCompiling;
	bool embeddedMode;
	bool autoClose;

	void setStateEnlarged(bool state);

protected:
	virtual void changeEvent(QEvent *event);
	virtual void closeEvent(QCloseEvent *event);
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	void setToolbarsVisible(bool visible);
	void shortcutOnlyIfFocused(const QList<QAction *> &actions);

public slots:
	void reloadSettings();
	void loadCurrentFile(bool fillCache = true);
	void fillRenderCache(int pg = -1);
	void sideBySide();
	void doFindDialog(const QString command = "");
	void doFindAgain();
	void goToSource();
	void toggleFullScreen(const bool fullscreen);
    int syncFromSource(const QString &sourceFile, int lineNo, int column, PDFDocument::DisplayFlags displayFlags);  // lineNo, column are 0-based
	void syncFromView(const QString &pdfFile, const QFileInfo &masterFile, int page);
    void loadFile(const QString &fileName, QFileInfo masterFile = QFileInfo(), PDFDocument::DisplayFlags displayFlags = DisplayFlagsEnum(Raise | Focus));
	void printPDF();
	void setAutoHideToolbars(bool enabled);
	void hideToolbars();
	void showToolbars();
	void showToolbarsDelayed();
	void setToolbarIconSize(int sz);
	void showMessage(const QString &text);

	void splitMergeTool();
private slots:
	void fileOpen();

	void enablePageActions(int, bool);
	void enableZoomActions(qreal);
	void adjustScaleActions(autoScaleOption);
	void syncClick(int page, const QPointF &pos, bool activate);
	void stopReloadTimer();
	void reloadWhenIdle();
	void idleReload();

	void runExternalViewer();
	void runInternalViewer();
	void toggleEmbedded();
	void toggleAutoHideToolbars();
	void runQuickBuild();

	void setGrid();

public slots:
	bool closeElement();
private slots:
	void tileWindows();
	void stackWindows();
	void unminimize();
    void updateDisplayState(PDFDocument::DisplayFlags displayFlags);
	void arrangeWindows(bool tile);
	void updateToolBarForOrientation(Qt::Orientation orientation);

	void jumpToPage();

	void search(bool backward, bool incremental);
    void clearHightlight(bool visible);
public:
	void search(const QString &searchText, bool backward, bool incremental, bool caseSensitive, bool wholeWords, bool sync);
	void search();
	static QString debugSyncTeX(const QString &filename);
private slots:
	void gotoAnnotation(const PDFAnnotation *ann);

	void zoomFromAction();
	void zoomSliderChange(int pos = 0);
	void enlarge();
	void shrink();
signals:
	void documentClosed();
	void documentLoaded();
	void syncSource(const QString &sourceFile, int line, bool activate, const QString &guessedWord); //view -> source
	void syncView(const QString &pdfFile, const QFileInfo &masterFile, int page); //view -> other view
	void focusEditor();
	void fileDropped(const QUrl &url);

	void runCommand(const QString &command, const QFileInfo &masterFile, const QFileInfo &currentFile, int linenr);

	void triggeredAbout();
	void triggeredManual();
	void triggeredQuit();
	void triggeredPlaceOnLeft();
	void triggeredConfigure();
	void triggeredEnlarge();
	void triggeredShrink();

	void triggeredClone();

private:
	void init(bool embedded = false);
    void setupMenus(bool embedded);
    void setupToolBar();
	void setCurrentFile(const QString &fileName);
	void loadSyncData();

	qreal zoomSliderPosToScale(int pos);
	int scaleToZoomSliderPos(qreal scale);

	QString curFile, curFileUnnormalized;
	qint64 curFileSize;
	QDateTime curFileLastModified;
	QFileInfo masterFile;
	QSynctex::TeXSyncPoint lastSyncPoint;

	QSharedPointer<Poppler::Document> document;

	PDFWidget	*pdfWidget;
	PDFScrollArea	*scrollArea;
	MessageFrame *messageFrame;
	TitledPanel *annotationPanel;
	PDFAnnotations *annotations;
	PDFAnnotationTableView *annotationTable;

	QMenuBar *menubar;
    QMenu *menuroot;
	QMenu *menuHelp;
	QMenu *menuFile;
	QMenu *menuEdit;
	QMenu *menuView;
	QMenu *menuGrid;
	QMenu *menuWindow;
    QList<QMenu *>menus;

    QAction *actionAbout_TW;
    QAction *actionFirst_Page;
    QAction *actionPrevious_Page;
    QAction *actionNext_Page;
    QAction *actionLast_Page;
    QAction *actionGo_to_Page;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionFit_to_Window;
    QAction *actionActual_Size;
    QAction *actionFit_to_Width;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpen_Recent;
    QAction *actionClose;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionTypeset;
    QAction *actionExternalViewer;
    QAction *actionPreferences;
    QAction *actionStack;
    QAction *actionTile;
    QAction *actionGo_to_Source;
    QAction *actionNew_from_Template;
    QAction *actionFull_Screen;
    QAction *actionMagnify;
    QAction *actionScroll;
    QAction *actionSelect_Text;
    QAction *actionSelect_Image;
    QAction *actionUserManual;
    QAction *actionWriteToMailingList;
    QAction *actionSide_by_Side;
    QAction *actionPlace_on_Left;
    QAction *actionPlace_on_Right;
    QAction *actionQuit_TeXworks;
    QAction *actionFind;
    QAction *actionFind_Again;
    QAction *actionUpdate_Scripts;
    QAction *actionManage_Scripts;
    QAction *actionShow_Scripts_Folder;
    QAction *actionAbout_Scripts;
    QAction *actionS;
    QAction *actionCloseElement;
    QAction *actionScrolling_follows_cursor;
    QAction *actionCursor_follows_scrolling;
    QAction *actionFind_2;
    QAction *actionFind_again;
    QAction *actionNew_Window;
    QAction *actionGrid11;
    QAction *actionGrid21;
    QAction *actionGrid12;
    QAction *actionGrid22;
    QAction *actionGrid23;
    QAction *actionGrid33;
    QAction *actionCustom;
    QAction *actionSinglePageStep;
    QAction *actionSynchronize_multiple_views, *actionNoSynchronization;
    QAction *actionPresentation;
    QAction *actionContinuous;
    QAction *action_Print;
    QAction *actionFileOpen;
    QAction *actionBack;
    QAction *actionForward;
    QAction *actionToggleEmbedded;
    QAction *actionEnlargeViewer;
    QAction *actionShrinkViewer;
	QAction *actionAutoHideToolbars;
    QAction *actionInvertColors;
    QAction *actionFocus_Editor;
    QAction *actionFit_to_Text_Width;
    QAction *actionGrayscale;
    QAction *actionSplitMerge;
    QActionGroup *actionGroupGrid;

    QStatusBar *statusbar;
    QToolBar *toolBar;
    QTimer *toolBarTimer;
public:
	QMenu *menuShow;
private:
	QMenu *menuEdit_2;

	QAction *actionPage_Up;
	QAction *actionPage_Down;

	QButtonGroup	*toolButtonGroup;
	QToolButton *comboZoom;
	QLineEdit *leCurrentPage;
	QLabel *pageCountSeparator;
	QLabel *pageCountLabel;
	QIntValidator *leCurrentPageValidator;

	QLabel *pageLabel;
	QToolButton *scaleButton;
	QSlider *zoomSlider;
	QList<QAction *> recentFileActions;
	QShortcut *exitFullscreen;

	QFileSystemWatcher *watcher;
	QTimer *reloadTimer;

	QSynctex::Scanner scanner;

	static QList<PDFDocument *> docList;

	PDFDock *dwClock, *dwOutline, *dwFonts, *dwInfo, *dwOverview;
	bool dwVisOutline, dwVisFonts, dwVisInfo, dwVisSearch, dwVisOverview;
	bool wasContinuous;
	PDFSearchDock *dwSearch;

	PDFSearchResult lastSearchResult;
	// stores the page idx a search was started on
	// after wrapping the search will continue only up to this page
	int firstSearchPage;

	bool wasMaximized;
	bool syncFromSourceBlocked;  //temporary disable sync from source
	bool syncToSourceBlocked;    //temporary disable sync to source (only for continuous scrolling)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(PDFDocument::DisplayFlags)

#endif

#endif
