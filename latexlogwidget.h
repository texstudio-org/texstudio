#ifndef LATEXLOGWIDGET_H
#define LATEXLOGWIDGET_H

#include "logeditor.h"
#include "latexlog.h"

#include "mostQtHeaders.h"

class LatexLogWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LatexLogWidget(QWidget *parent = 0);
	
	bool loadLogFile(const QString &logname, const QString &compiledFileName);
	LatexLogModel* getLogModel() {return logModel;}

	bool logEntryNumberValid(int logEntryNumber);
	bool logPresent();
	void resetLog();
	void selectLogEntry(int logEntryNumber);

	void copy();

	enum DisplayParts {DisplayTable, DisplayLog, DisplayLogAndTable};
	void setDisplayParts(DisplayParts parts);

	bool childHasFocus() const {return log->hasFocus() || errorTable->hasFocus();}
	QList<QAction *> displayActions() const {return displayPartsActions->actions();}
signals:
	void logEntryActivated(int);
	void logLoaded();
	void logResetted();
public slots:

private slots:
	void clickedOnLogModelIndex(const QModelIndex &index);
	void gotoLogEntry(int logEntryNumber);
	void gotoLogLine(int logLine);
	void copyMessage();
	void copyAllMessages();
	void copyAllMessagesWithLineNumbers();
	void changeDisplay(QAction *act);
	void setInfo(const QString &message);
private:
	QTableView *errorTable;
	LogEditor *log;
	QLabel *infoLabel;
	
	LatexLogModel *logModel;

	QActionGroup *displayPartsActions;
	QAction *displayTableAction, *displayLogAction, *displayLogAndTableAction;

	bool logpresent;
};

Q_DECLARE_METATYPE(LatexLogWidget::DisplayParts)

#endif // LATEXLOGWIDGET_H
