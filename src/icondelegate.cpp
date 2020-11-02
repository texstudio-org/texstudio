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

#include "mostQtHeaders.h"

#include "icondelegate.h"
#include "utilsSystem.h"

static const int textMargin = 2;

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
	Q_ASSERT(index.isValid());
	const QAbstractItemModel *model = index.model();
	Q_ASSERT(model);

	QStyleOptionViewItem opt = option;

	// set font
	QVariant value = model->data(index, Qt::FontRole);
	if (value.isValid())
		opt.font = qvariant_cast<QFont>(value);

	// set text alignment
	value = model->data(index, Qt::TextAlignmentRole);
	if (value.isValid())
		opt.displayAlignment = QFlag(value.toInt());

	// set text color
    value = model->data(index, Qt::ForegroundRole);
	if (value.isValid() && qvariant_cast<QColor>(value).isValid())
		opt.palette.setColor(QPalette::Text, qvariant_cast<QColor>(value));

	// do layout
	value = model->data(index, Qt::DecorationRole);
	QPixmap pixmap = decoration(opt, value);
    /*
	 * pixmap size is fixed and it is determined at start-up
	 * so, it can't handle change of devicePixelratio during run time when changing to normal res screen
	    int overScale= painter->device()->devicePixelRatio();
    */
	int overScale = isRetinaMac() ? 2 : 1;

	QSize pixmapSize = pixmap.size() / overScale;
	QRect pixmapRect(QPoint(0, 0), pixmapSize);
	//QRect pixmapRect=pixmap.rect();

	QFontMetrics fontMetrics(opt.font);
	QString text = model->data(index, Qt::DisplayRole).toString();
	QRect textRect(0, 0, 0, 0);

	value = model->data(index, Qt::CheckStateRole);
	QRect checkRect = check(opt, opt.rect, value);

	doLayout(opt, &checkRect, &pixmapRect, &textRect, false);

	// draw the background color
	if (option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
		painter->fillRect(option.rect, QColor("#cdd2d8"));
	} else {
        value = model->data(index, Qt::BackgroundRole);
		if (value.isValid() && qvariant_cast<QColor>(value).isValid())
			painter->fillRect(option.rect, qvariant_cast<QColor>(value));
	}

	// draw the item

	drawDecoration(painter, opt, pixmapRect, pixmap);
}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
	Q_ASSERT(index.isValid());
	const QAbstractItemModel *model = index.model();
	Q_ASSERT(model);

	QVariant value = model->data(index, Qt::FontRole);
	QFont fnt = value.isValid() ? qvariant_cast<QFont>(value) : option.font;
	QString text = model->data(index, Qt::DisplayRole).toString();
	QRect pixmapRect;
	if (model->data(index, Qt::DecorationRole).isValid())
		pixmapRect = QRect(0, 0, option.decorationSize.width(),
		                   option.decorationSize.height());

	QFontMetrics fontMetrics(fnt);
	QRect textRect(0, 0, 0, 0);
	//QRect textRect(0, 0, fontMetrics.width(text), fontMetrics.lineSpacing());
	QRect checkRect = check(option, textRect, model->data(index, Qt::CheckStateRole));
	doLayout(option, &checkRect, &pixmapRect, &textRect, true);

	return (pixmapRect | textRect | checkRect).size();
}


/*!
    Renders the decoration \a pixmap within the rectangle specified by
    \a rect using the given \a painter and style \a option.
*/
void IconDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QRect &rect, const QPixmap &pixmap) const
{
	if (!pixmap.isNull() && !rect.isEmpty()) {
		if (option.state & QStyle::State_Selected) {
			bool enabled = option.state & QStyle::State_Enabled;
			QPixmap *pm = selected(pixmap, option.palette, enabled);
			painter->drawPixmap(rect, *pm);
		} else {
			painter->drawPixmap(rect, pixmap);
		}
	}
}

/*!
    Renders the region within the rectangle specified by \a rect, indicating
    that it has the focus, using the given \a painter and style \a option.
*/
void IconDelegate::drawFocus(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QRect &rect) const
{
	if (option.state & QStyle::State_HasFocus) {
		QStyleOptionFocusRect o;
		o.QStyleOption::operator=(option);
		o.rect = rect;
		QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled)
		                          ? QPalette::Normal : QPalette::Disabled;
		o.backgroundColor = option.palette.color(cg, (option.state & QStyle::State_Selected)
                            ? QPalette::Highlight : QPalette::Window);
		QApplication::style()->drawPrimitive(QStyle::PE_FrameFocusRect, &o, painter);
	}
}

/*!
    Renders a check indicator within the rectangle specified by \a
    rect, using the given \a painter and style \a option, using the
    given \a state.
*/
void IconDelegate::drawCheck(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QRect &rect, Qt::CheckState state) const
{
	if (!rect.isValid())
		return;

	QStyleOptionViewItem opt;
	opt.QStyleOption::operator=(option);
	opt.rect = rect;
	opt.state = opt.state & ~QStyle::State_HasFocus;

	switch (state) {
	case Qt::Unchecked:
		opt.state |= QStyle::State_Off;
		break;
	case Qt::PartiallyChecked:
		opt.state |= QStyle::State_NoChange;
		break;
	case Qt::Checked:
		opt.state |= QStyle::State_On;
		break;
	}

    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &opt, painter);
}

void IconDelegate::doLayout(const QStyleOptionViewItem &option,
                            QRect *checkRect, QRect *pixmapRect, QRect *textRect,
                            bool hint) const
{
	Q_ASSERT(checkRect && pixmapRect && textRect);
	int x = option.rect.left();
	int y = option.rect.top();
	int w, h;

	textRect->adjust(-textMargin, 0, textMargin, 0); // add width padding

	QSize pm(0, 0);
	if (pixmapRect->isValid())
		pm = option.decorationSize;
	if (hint) {
		w = qMax(textRect->width(), pm.width());
		h = qMax(textRect->height(), pm.height());
	} else {
		w = option.rect.width();
		h = option.rect.height();
	}

	int cw = 0;
	QRect check;
	if (checkRect->isValid()) {
		check.setRect(x, y, checkRect->width() + textMargin * 2, h);
		cw = check.width();
		if (option.direction == Qt::LeftToRight)
			x += cw;
	}

	QRect display;
	QRect decoration;
	QStyleOptionViewItem::Position position = option.decorationPosition;
	if (option.direction == Qt::RightToLeft) {
		if (position == QStyleOptionViewItem::Right)
			position = QStyleOptionViewItem::Left;
		else if (position == QStyleOptionViewItem::Left)
			position = QStyleOptionViewItem::Right;
	}
	switch (position) {
	case QStyleOptionViewItem::Top: {
		if (!pm.isEmpty())
			pm.setHeight(pm.height() + textMargin); // add space
		decoration.setRect(x, y, w, pm.height());
		h = hint ? textRect->height() : h - pm.height();
		display.setRect(x, y + pm.height(), w, h);
		break;
	}
	case QStyleOptionViewItem::Bottom: {
		if (!textRect->isEmpty())
			textRect->setHeight(textRect->height() + textMargin); // add space
		h = hint ? textRect->height() + pm.height() : h;
		decoration.setRect(x, y + h - pm.height(), w, pm.height());
		h = hint ? textRect->height() : h - pm.height();
		display.setRect(x, y, w, h);
		break;
	}
	case QStyleOptionViewItem::Left: {
		if (!pm.isEmpty())
			pm.setWidth(pm.width() + textMargin); // add space
		decoration.setRect(x, y, pm.width(), h);
		w = hint ? textRect->width() : w - pm.width() - cw;
		display.setRect(x + pm.width(), y, w, h);
		break;
	}
	case QStyleOptionViewItem::Right: {
		if (!textRect->isEmpty())
			textRect->setWidth(textRect->width() + textMargin); // add space
		w = hint ? textRect->width() + pm.width() : w;
		decoration.setRect(x + w - pm.width() - cw, y, pm.width(), h);
		w = hint ? textRect->width() : w - pm.width() - cw;
		display.setRect(x, y, w, h);
		break;
	}
	default:
		qWarning("doLayout: decoration positon is invalid");
		decoration = *pixmapRect;
		break;
	}

	if (!hint) { // we only need to do the internal layout if we are going to paint
		*checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
		                                 checkRect->size(), check);
		*pixmapRect = QStyle::alignedRect(option.direction, option.decorationAlignment,
		                                  pixmapRect->size(), decoration);
	} else {
		*checkRect = check;
		*pixmapRect = decoration;
	}
	*textRect = display;
}

QPixmap IconDelegate::decoration(const QStyleOptionViewItem &option, const QVariant &variant) const
{
	const int overScale = isRetinaMac() ? 2 : 1;
	switch (variant.type()) {
	case QVariant::Icon:
		return qvariant_cast<QIcon>(variant).pixmap(option.decorationSize * overScale,
                (option.state & QStyle::State_Enabled)
		        ? QIcon::Normal : QIcon::Disabled,
                (option.state & QStyle::State_Open)
		        ? QIcon::On : QIcon::Off);
	case QVariant::Color: {
		static QPixmap pixmap(20, 20);
		pixmap.fill(qvariant_cast<QColor>(variant));
		return pixmap;
	}
	default:
		break;
	}
	return qvariant_cast<QPixmap>(variant);
}

/*!
  \internal
*/
QPixmap *IconDelegate::selected(const QPixmap &pixmap, const QPalette &palette, bool enabled) const
{
	QString key = QString("%1-%2").arg(pixmap.cacheKey()).arg(enabled);
	//key.sprintf("%d-%d", pixmap.cacheKey(), boolKey);
    QPixmap *pm=nullptr;
    if (QPixmapCache::find(key,pm)) {
		QImage img = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);

		QColor color = palette.color(enabled ? QPalette::Normal : QPalette::Disabled, QPalette::Highlight);

		color.setAlphaF(0.3);

		QPainter painter(&img);
		painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
		painter.fillRect(0, 0, img.width(), img.height(), color);
		painter.end();

		pm = new QPixmap(QPixmap::fromImage(img));
		QPixmapCache::insert(key, *pm);
	}
	return pm;
}

/*!
  \internal
*/
QRect IconDelegate::check(const QStyleOptionViewItem &option,
                          const QRect &bounding, const QVariant &value) const
{
	if (value.isValid()) {
		QStyleOptionButton opt;
		opt.QStyleOption::operator=(option);
		opt.rect = bounding;
        return QApplication::style()->subElementRect(QStyle::SE_ItemViewItemCheckIndicator, &opt);
	}
	return QRect();
}
