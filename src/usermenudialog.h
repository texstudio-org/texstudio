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

#ifndef Header_UserMenu_Dialog
#define Header_UserMenu_Dialog

#include "mostQtHeaders.h"
#include "ui_usermenudialog.h"
#include "usermacro.h"

class QCodeEdit;
class QLanguageFactory;
class QSearchReplacePanel;

class UserMenuDialog : public QDialog
{
	Q_OBJECT

public:
    UserMenuDialog(QWidget *parent, QString name, QLanguageFactory *languageFactory);
	~UserMenuDialog();
	Ui::UserMenuDialog ui;

    void addMacro(const Macro &m,bool insertRow=false);
    QList<Macro> getMacros() const;
    QList<Macro> getMacros(QTreeWidgetItem *item,const QString &path) const;

    void selectFirst();
    void setLineWrap(bool wrap);
    bool getLineWrap();

private:
	void setLanguageFromText(void);
    QTreeWidgetItem* findCreateFolder(const QString &menu);
    QTreeWidgetItem* findCreateFolder(QTreeWidgetItem *parent, QStringList folders);

	QCodeEdit *codeedit;
	QLanguageFactory *languages;
	QSearchReplacePanel *searchReplacePanel;

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;

signals:
	void runScript(const QString &script);

private slots:
    void change(QTreeWidgetItem *current,QTreeWidgetItem *previous);
	void slotOk();
	void slotRunScript();
	void slotAdd();
	void slotRemove();
    void slotAddFolder();
	void slotMoveUp();
	void slotMoveDown();
    void importMacro();
    void exportMacro();
    void browseMacrosOnRepository();
	void textChanged();
	void nameChanged();
    void descriptionChanged();
    void shortcutChanged();
	void abbrevChanged();
	void triggerChanged();
	void showTooltip();
	void changeTypeToNormal();
	void changeTypeToEnvironment();
	void changeTypeToScript();
};

#endif // USERMENUDIALOG_H
