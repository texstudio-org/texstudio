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

#ifndef TEMPLATESELECTOR_H
#define TEMPLATESELECTOR_H

#include "mostQtHeaders.h"

#include "ui_templateselector.h"

class templateselector : public QDialog  {
	Q_OBJECT
public:
	templateselector(QWidget *parent=0, QString name="");
	~templateselector();
	Ui::templateSelectorDialog ui;

};

#endif // TEMPLATESELECTOR_H
