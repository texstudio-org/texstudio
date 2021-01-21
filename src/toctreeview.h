#ifndef TOCTREEVIEW_H
#define TOCTREEVIEW_H

#include "mostQtHeaders.h"
#include "tocitemstruct.h"

class ConfigManager;
class LatexDocuments;

class TocTreeView : public QTreeView
{
	Q_OBJECT
public:
	explicit TocTreeView(const ConfigManager &config, LatexDocuments* docs, QWidget *parent = Q_NULLPTR);

	void updateTOC();

	void updateData();

private:
	QList<TocItem> buildToc(QString file);

signals:
	void gotoFileLine(QString section, QString file, int line);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* event);

public slots:
	void parentDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles = QVector<int>());

private:
	QMap<QString, QList<TocItem>> openDocs;
	QMap<QString, QList<TocItem>> closedDocs;
	LatexDocuments* documents;
};

#endif // TOCTREEVIEW_H
