#ifndef Header_Latex_Log_Widget
#define Header_Latex_Log_Widget

#include "logeditor.h"
#include "latexlog.h"

#include <QSortFilterProxyModel>

#include "mostQtHeaders.h"

class LatexLogWidget : public QWidget
{
	Q_OBJECT

public:
	explicit LatexLogWidget(QWidget *parent = 0);

	bool loadLogFile(const QString &logname, const QString &compiledFileName, QTextCodec* fallbackCodec);
	LatexLogModel *getLogModel() { return logModel; }

	bool logEntryNumberValid(int logEntryNumber);
	bool logPresent();
	void resetLog();
	void selectLogEntry(int logEntryNumber);

	void copy();

	bool childHasFocus() const { return log->hasFocus() || errorTable->hasFocus(); }
	QList<QAction *> displayActions();

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
	void setWidgetVisibleFromAction(bool visible);
	void setInfo(const QString &message);
	void filterChanged(bool);

private:
	LatexLogModel *logModel;
	QSortFilterProxyModel *proxyModel;
	bool logpresent;

	QTableView *errorTable;
	LogEditor *log;
	QLabel *infoLabel;
	QAction *displayTableAction, *displayLogAction, *filterErrorAction, *filterWarningAction, *filterBadBoxAction;
};

#endif // LATEXLOGWIDGET_H
