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

#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include "mostQtHeaders.h"


class QAbstractItemModel;
class QObject;
class QPainter;

class IconDelegate : public QAbstractItemDelegate
{
	Q_OBJECT

public:
    IconDelegate(QObject *parent = nullptr)
		: QAbstractItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
	           const QModelIndex &index) const;

	QSize sizeHint(const QStyleOptionViewItem &option,
	               const QModelIndex &index) const;
protected:
	virtual void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
	                            const QRect &rect, const QPixmap &pixmap) const;
	virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
	                       const QRect &rect) const;
	virtual void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
	                       const QRect &rect, Qt::CheckState state) const;

	void doLayout(const QStyleOptionViewItem &option,
	              QRect *checkRect, QRect *iconRect, QRect *textRect, bool hint) const;
	QPixmap decoration(const QStyleOptionViewItem &option, const QVariant &variant) const;
	QPixmap *selected(const QPixmap &pixmap, const QPalette &palette, bool enabled) const;
	QRect check(const QStyleOptionViewItem &option, const QRect &bounding,
	            const QVariant &variant) const;
};

#endif
