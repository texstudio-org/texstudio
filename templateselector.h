/***************************************************************************
 *   copyright       : (C) 2009 by Jan Sundermeyer                         *
 *   http://texstudio.sourceforge.net/                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TEMPLATESELECTOR_H
#define TEMPLATESELECTOR_H

#include "mostQtHeaders.h"

#include "ui_templateselector.h"

class TemplateSelector : public QDialog  {
	Q_OBJECT
public:
	TemplateSelector(QString filter, QString name="", QWidget *parent=0, QStringList additionalSearchPaths = QStringList());
	~TemplateSelector();
	QString selectedTemplateFile() const;
	Ui::templateSelectorDialog ui;
signals:
	void editTemplateRequest(const QString &fname);

private slots:
	void addTemplateFiles();
	void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
	void showInfo(QListWidgetItem *currentItem, QListWidgetItem *previousItem);
	void editTemplate();
	void removeTemplate();

private:
	bool getTemplateMetaData(const QString &file, QHash<QString, QString> &metaData) const;
	QString mFilter;
	QStringList mAdditonalSearchPaths;

	static const int FileNameRole;
};

#endif // TEMPLATESELECTOR_H
