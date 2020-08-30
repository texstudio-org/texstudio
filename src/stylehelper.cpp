/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
**************************************************************************/

#include "stylehelper.h"

#include <QPixmapCache>
#include <QWidget>

// Clamps float color values within (0, 255)
static int clamp(float x)
{
    const int val = x > 255 ? 255 : static_cast<int>(x);
    return val < 0 ? 0 : val;
}

// Clamps float color values within (0, 255)
/*
static int range(float x, int min, int max)
{
    int val = x > max ? max : x;
    return val < min ? min : val;
}
*/

qreal StyleHelper::sidebarFontSize()
{
#if defined(Q_OS_MAC)
    return 9;
#else
    return 7.5;
#endif
}

QPalette StyleHelper::sidebarFontPalette(const QPalette &original)
{
    QPalette palette = original;
    palette.setColor(QPalette::Active, QPalette::Text, panelTextColor());
    palette.setColor(QPalette::Active, QPalette::WindowText, panelTextColor());
    palette.setColor(QPalette::Inactive, QPalette::Text, panelTextColor().darker());
    palette.setColor(QPalette::Inactive, QPalette::WindowText, panelTextColor().darker());
    return palette;
}

QColor StyleHelper::panelTextColor()
{
    //qApp->palette().highlightedText().color();
    return Qt::white;
}

QColor StyleHelper::m_baseColor(0x606060);

QColor StyleHelper::baseColor()
{
    return m_baseColor;
}

QColor StyleHelper::highlightColor()
{
    QColor result = baseColor();
    result.setHsv(result.hue(),
                  clamp(result.saturation()),
                  clamp(result.value() * 1.16));
    return result;
}

QColor StyleHelper::shadowColor()
{
    QColor result = baseColor();
    result.setHsv(result.hue(),
                  clamp(result.saturation() * 1.1),
                  clamp(result.value() * 0.70));
    return result;
}

QColor StyleHelper::borderColor()
{
    QColor result = baseColor();
    result.setHsv(result.hue(),
                  result.saturation(),
                  result.value() / 2);
    return result;
}

void StyleHelper::setBaseColor(const QColor &color)
{
    if (color.isValid() && color != m_baseColor) {
        m_baseColor = color;
        foreach (QWidget *w, QApplication::topLevelWidgets())
            w->update();
    }
}

static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50)
{
    const int maxFactor = 100;
    QColor tmp = colorA;
    tmp.setRed((tmp.red() * factor) / maxFactor + (colorB.red() * (maxFactor - factor)) / maxFactor);
    tmp.setGreen((tmp.green() * factor) / maxFactor + (colorB.green() * (maxFactor - factor)) / maxFactor);
    tmp.setBlue((tmp.blue() * factor) / maxFactor + (colorB.blue() * (maxFactor - factor)) / maxFactor);
    return tmp;
}

void StyleHelper::verticalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect)
{
    QString key=QString("mh_toolbar %1 %2 %3 %4 %5").arg(spanRect.width()).arg(spanRect.height()).arg(clipRect.width())
                                             .arg(clipRect.height()).arg(StyleHelper::baseColor().rgb());
    QPixmap pixmap;
    QPainter *p = painter;
    QRect rect = clipRect;
    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        pixmap = QPixmap(clipRect.size());
        p = new QPainter(&pixmap);
        rect = QRect(0, 0, clipRect.width(), clipRect.height());
    }

    QColor base = StyleHelper::baseColor();
    QLinearGradient grad(spanRect.topRight(), spanRect.topLeft());

    grad.setColorAt(0, highlightColor().lighter(120));
    grad.setColorAt(0.9, highlightColor());
    grad.setColorAt(0.901, base);
    grad.setColorAt(1, shadowColor());

/*    grad.setColorAt(0, highlightColor());
    grad.setColorAt(0.301, base);
    grad.setColorAt(1, shadowColor());*/


    QColor light(255, 255, 255, 80);
    p->fillRect(rect,base);
    p->setPen(light);
    p->drawLine(rect.topRight() - QPoint(1, 0), rect.bottomRight() - QPoint(1, 0));

    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        painter->drawPixmap(clipRect.topLeft(), pixmap);
        p->end();
        delete p;
        QPixmapCache::insert(key, pixmap);
    }

}

void StyleHelper::horizontalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect)
{
    QString key=QString("mh_toolbar %1 %2 %3 %4 %5").arg(spanRect.width()).arg(spanRect.height())
                .arg(clipRect.width()).arg(clipRect.height()).arg(StyleHelper::baseColor().rgb());
    QPixmap pixmap;
    QPainter *p = painter;
    QRect rect = clipRect;
    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        pixmap = QPixmap(clipRect.size());
        p = new QPainter(&pixmap);
        rect = QRect(0, 0, clipRect.width(), clipRect.height());
    }

    QColor base = StyleHelper::baseColor();
    QLinearGradient grad(rect.topLeft(), rect.bottomLeft());

    grad.setColorAt(0, highlightColor().lighter(120));
	grad.setColorAt(0.2, highlightColor());
	grad.setColorAt(0.301, base);
    grad.setColorAt(1, shadowColor());
    p->fillRect(rect, grad);

/*    QLinearGradient shadowGradient(spanRect.topLeft(), spanRect.topRight());
    shadowGradient.setColorAt(0, QColor(0, 0, 0, 30));
    QColor highlight = highlightColor().lighter(130);
    highlight.setAlpha(100);
    shadowGradient.setColorAt(0.7, highlight);
    shadowGradient.setColorAt(1, QColor(0, 0, 0, 40));
    p->fillRect(rect, shadowGradient);*/

    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        painter->drawPixmap(clipRect.topLeft(), pixmap);
        p->end();
        delete p;
        QPixmapCache::insert(key, pixmap);
    }
}

void StyleHelper::menuGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect)
{
    QString key=QString("mh_toolbar %1 %2 %3 %4 %5").arg(spanRect.width()).arg(spanRect.height())
                .arg(clipRect.width()).arg(clipRect.height()).arg(StyleHelper::baseColor().rgb());
    QPixmap pixmap;
    QPainter *p = painter;
    QRect rect = clipRect;
    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        pixmap = QPixmap(clipRect.size());
        p = new QPainter(&pixmap);
        rect = QRect(0, 0, clipRect.width(), clipRect.height());
    }

    QLinearGradient grad(spanRect.topLeft(), spanRect.bottomLeft());
    QColor menuColor = mergedColors(StyleHelper::baseColor(), QColor(240, 240, 240), 25);
    grad.setColorAt(0, menuColor.lighter(112));
    grad.setColorAt(1, menuColor);
    p->fillRect(rect, grad);

    if (StyleHelper::usePixmapCache() && !QPixmapCache::find(key, &pixmap)) {
        painter->drawPixmap(clipRect.topLeft(), pixmap);
        p->end();
        delete p;
        QPixmapCache::insert(key, pixmap);
    }
}
