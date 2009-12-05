/***************************************************************************
 *   copyright       : (C) 2009 by Jan Sundermeyer                         *
 *   http://texmakerx.sourceforgw.net/                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "templateselector.h"

templateselector::templateselector(QWidget *parent, QString name)
		: QDialog(parent) {
	setModal(true);
	ui.setupUi(this);
	setWindowTitle(name);
	ui.listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

}

templateselector::~templateselector() {
}

void templateselector::on_listWidget_itemDoubleClicked(QListWidgetItem* /*item*/)
{
	accept();
}
