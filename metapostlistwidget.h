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

#ifndef METAPOSTLISTWIDGET_H
#define METAPOSTLISTWIDGET_H

#include <QListWidget>


class MetapostListWidget : public QListWidget  {
  Q_OBJECT
public:
	MetapostListWidget(QWidget *parent=0);
	~MetapostListWidget();
};

#endif
