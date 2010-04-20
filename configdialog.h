/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "mostQtHeaders.h"

#include "ui_configdialog.h"

#include "qformat.h"
#include "qformatconfig.h"


class ShortcutDelegate : public QItemDelegate {
	Q_OBJECT

public:
	ShortcutDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	                      const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
	                  const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
	                          const QStyleOptionViewItem &option, const QModelIndex &index) const;

	void drawDisplay(QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text) const;

	QTreeWidget * treeWidget; //tree widget to remove duplicates from, not necessary

	static const QString deleteRowButton;
	static const QString addRowButton;
public slots:
	void treeWidgetItemClicked(QTreeWidgetItem * item, int column);
};

class ConfigDialog : public QDialog {
	Q_OBJECT

public:
	ConfigDialog(QWidget* parent = 0);
	~ConfigDialog();
	Ui::ConfigDialog ui;

	QMap<QString,QFormat> editorFormats;
	QFormatConfig * fmConfig;
	QHash<QString,QVariant> * replacedIconsOnMenus;

	QObject* menuParent;
	QList<QStringList> customizableToolbars;
	QList<QMenu*> allMenus;
	QList<QMenu*> standardToolbarMenus;

	QStringList * environModes;
public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private slots:
	QListWidgetItem * createIcon(const QString &caption, const QIcon &icon, bool advancedOption=false);
	void lineEditAspellChanged(const QString& newText);
	void comboBoxWithPathEdited(const QString& newText);
	void browseAspell();
	void browseThesaurus();
	void browsePrecompiling();
	void advancedOptionsToggled(bool on);
	void toolbarChanged(int toolbar);
	void actionsChanged(int actionClass);
	void toToolbarClicked();
	void fromToolbarClicked();
	void customContextMenuRequested(const QPoint &p);
	void loadOtherIcon();
	void populatePossibleActions(QTreeWidgetItem* parent, const QMenu* menu,bool keepHierarchy);

	void custEnvAddLine();
	void custEnvRemoveLine();
};

Q_DECLARE_METATYPE(QAction*);

#endif
