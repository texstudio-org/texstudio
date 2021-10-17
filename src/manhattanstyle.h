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

#ifndef Header_ManhattenStyle
#define Header_ManhattenStyle
#include <QStyle>

#include <QProxyStyle>

QT_BEGIN_NAMESPACE
class QLinearGradient;
class QBrush;
QT_END_NAMESPACE

class ManhattanStylePrivate;

class ManhattanStyle : public QProxyStyle
{
	Q_OBJECT

public:
	ManhattanStyle(const QString &);

	~ManhattanStyle();

	bool isValid();

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const;

	QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const;
	QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const;
	QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const;

    SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option, const QPoint &pos, const QWidget *widget = nullptr) const;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt, const QWidget *widget = nullptr) const;
    int styleHint(StyleHint hint, const QStyleOption *option = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *returnData = nullptr) const;
	QRect itemRect(QPainter *p, const QRect &r, int flags, bool enabled, const QPixmap *pixmap, const QString &text, int len = -1) const;
	QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const;

	QPalette standardPalette() const;

	void polish(QWidget *widget);
	void polish(QPalette &pal);
	void polish(QApplication *app);

	void unpolish(QWidget *widget);
	void unpolish(QApplication *app);

protected:
	bool event(QEvent *e);

protected Q_SLOTS:
	QIcon standardIconImplementation(StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const;
	int layoutSpacingImplementation(QSizePolicy::ControlType control1,
	                                QSizePolicy::ControlType control2,
	                                Qt::Orientation orientation,
                                    const QStyleOption *option = nullptr,
                                    const QWidget *widget = nullptr) const;

private:
	ManhattanStylePrivate *d;
	Q_DISABLE_COPY(ManhattanStyle)
};
#endif // MANHATTANSTYLE_H
