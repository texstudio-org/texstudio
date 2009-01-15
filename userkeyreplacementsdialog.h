/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef USERKEYREPLACEMENTSDIALOG_H
#define USERKEYREPLACEMENTSDIALOG_H

#include <QString>
#include "ui_userkeyreplacements.h"

class UserKeyReplacementsDialog : public QDialog
{
    Q_OBJECT

public:
    UserKeyReplacementsDialog( QWidget* parent = 0, QString name="");
    ~UserKeyReplacementsDialog();
    Ui::UserKeyReplaceDialog ui;

    QVector<QString> UserKeyReplace, UserKeyReplaceAfterWord, UserKeyReplaceBeforeWord;


private slots:
    void slotOk();
    void slotCancel();
    void slotAddRow();
    void slotRemoveRow();

public slots:
    void init();
/*
private slots:
    void change(int index);
    void slotOk();*/
};

#endif // USERMENUDIALOG_H


