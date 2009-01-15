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

#ifndef GOTOLINEDIALOG_H
#define GOTOLINEDIALOG_H

#include "ui_gotolinedialog.h"
#include "latexeditor.h"

class GotoLineDialog : public QDialog
{ 
    Q_OBJECT

public:
    GotoLineDialog(QWidget* parent = 0, const char* name = 0,Qt::WFlags fl = 0 );
    ~GotoLineDialog();
    Ui::GotoLineDialog ui;

public slots:
    virtual void gotoLine();
    void SetEditor(LatexEditor *ed);

protected:
    LatexEditor *editor;
};

#endif // GOTOLINEDIALOG_H
