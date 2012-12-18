#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include "mostQtHeaders.h"

class FileSelector : public QWidget
{
	Q_OBJECT
public:
	explicit FileSelector(QWidget *parent = 0);
	void init(const QStringList& files, int current);
signals:
	void fileChoosen(const QString& name, int duplicate, int lineNr, int column);
private slots:
	void filterChanged(const QString& newFilter);
protected:
	virtual bool eventFilter(QObject * obj, QEvent * event);
	void emitChoosen();
private:
	QListWidget *list;
	QLineEdit	*filter;
	QStringList rawFiles;
	QPair<QString, int> currentFile();
};

#endif // FILESELECTOR_H
