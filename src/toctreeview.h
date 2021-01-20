#ifndef TOCTREEVIEW_H
#define TOCTREEVIEW_H

#include "mostQtHeaders.h"

class LatexDocument;
class ConfigManager;

class TocTreeView : public QTreeView
{
	Q_OBJECT
public:
	explicit TocTreeView(const ConfigManager &config, QWidget *parent = Q_NULLPTR);

	void refresh(LatexDocument* main);

signals:
	void gotoFileLine(QString section, QString file, int line);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* event);

private:
	const ConfigManager &configManager;

};

#endif // TOCTREEVIEW_H
