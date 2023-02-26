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

#ifndef Header_Config_Dialog
#define Header_Config_Dialog

#include "mostQtHeaders.h"

#include "ui_configdialog.h"

#include "qformat.h"
#include "buildmanager.h"



//TODO: perhaps move each class in its own file?
class ShortcutComboBox: public QComboBox
{
	Q_OBJECT

public:
    ShortcutComboBox(QWidget *parent = nullptr);
protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void focusInEvent(QFocusEvent *e);
};

class ShortcutDelegate : public QItemDelegate
{
	Q_OBJECT

public:
    ShortcutDelegate(QObject *parent = nullptr);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	                      const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
	                  const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
	                          const QStyleOptionViewItem &option, const QModelIndex &index) const;

	void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

	bool isBasicEditorKey(const QModelIndex &index) const;

	QTreeWidget *treeWidget;  //tree widget to remove duplicates from, not necessary

	static const QString deleteRowButton;
	static const QString addRowButton;
public slots:
	void treeWidgetItemClicked(QTreeWidgetItem *item, int column);
};

class ComboBoxDelegate : public QItemDelegate
{
public:
    ComboBoxDelegate(QObject *parent = nullptr);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	                      const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
	                  const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
	                          const QStyleOptionViewItem &option, const QModelIndex &index) const;

	QStringList defaultItems;
	int activeColumn;
};

class QFormatConfig;
class ConfigDialog : public QDialog
{
	Q_OBJECT

public:
    ConfigDialog(QWidget *parent = nullptr);
	~ConfigDialog();
	Ui::ConfigDialog ui;
	QRadioButton *checkboxInternalPDFViewer;

	QMap<QString, QFormat> editorFormats;
	QFormatConfig *fmConfig;
	QMap<QString, QVariant> *replacedIconsOnMenus;

	QObject *menuParent;
	QList<QStringList> customizableToolbars;
	QList<QMenu *> allMenus;
	QList<QMenu *> standardToolbarMenus;

	void setBuildManger(BuildManager *buildManager) { mBuildManager = buildManager; }
	void showAndLimitSize();
	
	bool riddled;
public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private slots:
	void comboBoxWithPathEdited(const QString &newText);
	void comboBoxWithPathHighlighted(const QString &newText);
	void browseThesaurus();
	void browseGrammarLTPath();
	void browseGrammarLTJavaPath();
	void browseGrammarWordListsDir();
    void resetLTURL();
    void resetLTArgs();
	void browseDictDir();
	void updateDefaultDictSelection(const QString &dictPaths, const QString &newDefault = QString());
	void browsePathLog();
	void browsePathBib();
	void browsePathImages();
	void browsePathPdf();
	void browsePathCommands();
	void advancedOptionsToggled(bool on);
	void advancedOptionsClicked(bool on);
	void metaFilterChanged(const QString &filter);
	void toolbarChanged(int toolbar);
	void actionsChanged(int actionClass);
	void toToolbarClicked();
	void fromToolbarClicked();
	void checkToolbarMoved();
    void customContextMenu(const QPoint &p);
	void loadOtherIcon();
	void insertSeparator();
	void populatePossibleActions(QTreeWidgetItem *parent, const QMenu *menu, bool keepHierarchy);

	void importDictionary();
	void updateCheckNow();
	void refreshLastUpdateTime();

    void filterCompletionList(const QString &text);

	void revertClicked();

	void populateComboBoxFont(bool onlyMonospaced);
private:
#ifdef INTERNAL_TERMINAL
	void populateTerminalColorSchemes();
	void populateTerminalComboBoxFont(bool onlyMonospaced);
#endif
protected:
    bool eventFilter(QObject *obj,QEvent *event);
private:
	enum ContentsType {CONTENTS_BASIC, CONTENTS_ADVANCED, CONTENTS_DISABLED};

	QListWidgetItem *createIcon(const QString &caption, const QIcon &icon, ContentsType contentsType = CONTENTS_BASIC);
	bool askRiddle();
	void hideShowAdvancedOptions(QWidget *w, bool on);
    void tweakFocusSettings(QObjectList objList);
	static bool metaFilterRecurseWidget(const QString &filter, QWidget *widget);
	static bool metaFilterRecurseLayout(const QString &filter, QLayout *layout);
	static int lastUsedPage;
	static QPoint lastSize;
	int oldToolbarIndex;
	BuildManager *mBuildManager;
};

Q_DECLARE_METATYPE(QAction *)

#endif
