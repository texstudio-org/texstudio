#ifndef TOOLWIDGETS_H
#define TOOLWIDGETS_H

#include "mostQtHeaders.h"

#include "logeditor.h"
#include "latexlog.h"

class PreviewWidget : public QScrollArea
{
	Q_OBJECT
public:
    PreviewWidget(QWidget * parent = 0);

public slots:	
	void previewLatex(const QPixmap& previewImage);
	void fitImage();
	void scaleImage(double factor);
	void zoomOut();
	void zoomIn();
	void contextMenu(QPoint point);

private:
	QLabel *preViewer;
	double pvscaleFactor;
};

class OutputViewWidget: public QDockWidget{
	Q_OBJECT
public:
	OutputViewWidget(QWidget * parent = 0);
	

	LatexLogModel* getLogModel();
	void loadLogFile(const QString &logname, const QString & compiledFileName, const QString & overrideFileMName);
	bool logPresent();
	bool isPreviewPanelVisible();
	void setMessage(const QString &message); //set the message text (don't change page and no auto-show)
	void insertMessageLine(const QString &message); //inserts the message text (don't change page and no auto-show)
public slots:
	void resetMessages(bool noTabChange=false); //remove all messages and jumps to the message page (stays hidden if not visible)
	void resetMessagesAndLog(bool noTabChange=false);
	void resetLog(bool noTabChange=false);
	void selectLogEntry(int logEntryNumber, bool makeVisible=true);
	void showLogOrErrorList(bool noTabChange=false); //this will show the log unless the error list is open
	void showErrorListOrLog(); //this will show the error list unless log is open
	void showPreview();
	void gotoLogEntry(int logEntryNumber);
	void setTabbedLogView(bool tabbed);
	void previewLatex(const QPixmap& pixmap);
signals:
	void locationActivated(int line, QString fileName); //0-based line, absolute file name
	void logEntryActivated(int logEntryNumber);
	void tabChanged(int tab);
private:
	PreviewWidget *previewWidget;
	QTableView *OutputTable, *OutputTable2;
	LogEditor *OutputTextEdit,*OutputLogTextEdit;	
	QTabBar *logViewerTabBar; //header to select outp (if tabbedLogView, then it is OutputView's TitleBarWidget)
	QStackedWidget*	OutputLayout;
	//Latex errors
	LatexLogModel * logModel; 
	bool logpresent, tabbedLogView;
private slots:
	void clickedOnLogModelIndex(const QModelIndex& index);
	void gotoLogLine(int logLine);
};


#endif 
