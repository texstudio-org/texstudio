/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 * Copyright (C) 2014-2018 Martin Bříza <m@rtinbriza.cz>                 *
 * Copyright (C) 2019 Jan Grulich <jgrulich@redhat.com>                  *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

#ifndef Header_Adwaita_Helper
#define Header_Adwaita_Helper

#include "adwaita.h"
#include "adwaitaanimationdata.h"
#include "config-adwaita.h"

#include <QPainterPath>
#include <QStyle>
#include <QWidget>

#if QT_VERSION > 0x050000
#include <QWindow>
#endif

#if ADWAITA_HAVE_X11
#include <QX11Info>
#include <xcb/xcb.h>
#endif

#include <cmath>
#if QT_VERSION_MAJOR<6
typedef qreal color_real;
#else
typedef float color_real;
#endif

namespace Adwaita
{

//* adwaita style helper class.
/** contains utility functions used at multiple places in both adwaita style and adwaita window decoration */
class Helper
{
public:

    //* constructor
    explicit Helper();

#if ADWAITA_USE_KDE4
    //* constructor
    explicit Helper(const QByteArray &);
#endif

    //* destructor
    virtual ~Helper()
    {}

#if QT_VERSION > 0x050000
    static bool isWindowActive(const QWidget *widget)
    {
        const QWindow *win = widget ? widget->window()->windowHandle() : nullptr;
        if (win) {
            return win->isActive();
        }
        return false;
    }
#endif

    //*@name color utilities
    //@{

    // Borrowed from the KColorUtils code
    static QColor mix(const QColor &c1, const QColor &c2, qreal bias = 0.5)
    {
        auto mixQreal = [](qreal a, qreal b, qreal bias) {
            return a + (b - a) * bias;
        };

        if (bias <= 0.0)
            return c1;
        if (bias >= 1.0)
            return c2;
        if (std::isnan(bias))
            return c1;

        qreal r = mixQreal(c1.redF(),   c2.redF(),   bias);
        qreal g = mixQreal(c1.greenF(), c2.greenF(), bias);
        qreal b = mixQreal(c1.blueF(),  c2.blueF(),  bias);
        qreal a = mixQreal(c1.alphaF(), c2.alphaF(), bias);

        return QColor::fromRgbF(r, g, b, a);
    }

    static QColor lighten(const QColor &color, color_real amount = 0.1)
    {
        color_real h, s, l, a;
        color.getHslF(&h, &s, &l, &a);

        color_real lightness = l + amount;
        if (lightness > 1)
            lightness = 1;
        return QColor::fromHslF(h, s, lightness, a);
    }

    static QColor darken(const QColor &color, color_real amount = 0.1)
    {
        color_real h, s, l, a;
        color.getHslF(&h, &s, &l, &a);

        color_real lightness = l - amount;
        if (lightness < 0)
            lightness = 0;

        return QColor::fromHslF(h, s, lightness, a);
    }

    static QColor desaturate(const QColor &color, color_real amount = 0.1)
    {
        color_real h, s, l, a;
        color.getHslF(&h, &s, &l, &a);

        color_real saturation = s - amount;
        if (saturation < 0)
            saturation = 0;
        return QColor::fromHslF(h, saturation, l, a);
    }

    static QColor transparentize(const QColor &color, color_real amount = 0.1)
    {
        color_real h, s, l, a;
        color.getHslF(&h, &s, &l, &a);

        color_real alpha = a - amount;
        if (alpha < 0)
            alpha = 0;
        return QColor::fromHslF(h, s, l, alpha);
    }

    //* returns adwaita color palette
    QPalette palette(bool dark) const;

    //* add alpha channel multiplier to color
    QColor alphaColor(QColor color, qreal alpha) const;

    //* mouse over color
    QColor hoverColor(const QPalette &palette) const
    {
        return palette.highlight().color();
    }

    //* focus color
    QColor focusColor(const QPalette &palette) const
    {
        return palette.highlight().color();
    }

    //* negative text color (used for close button)
    QColor negativeText(const QPalette &palette) const
    // { return _viewNegativeTextBrush.brush( palette ).color(); }
    {
        Q_UNUSED(palette);
        return Qt::red;
    }

    //* shadow
    QColor shadowColor(const QPalette &palette) const
    {
        return alphaColor(palette.color(QPalette::Shadow), 0.15);
    }

    //* titlebar color
    QColor titleBarColor(const QPalette &palette, bool active) const
    {
        return palette.color(active ? QPalette::Active : QPalette::Inactive, QPalette::Window);
    }

    //* titlebar text color
    QColor titleBarTextColor(const QPalette &palette, bool active) const
    {
        return palette.color(active ? QPalette::Active : QPalette::Inactive, QPalette::WindowText);
    }

    //* indicator outline color
    QColor indicatorOutlineColor(const QPalette &palette, bool mouseOver = false, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, CheckBoxState state = CheckOff, bool darkMode = false, bool inMenu = false) const;

    //* frame outline color, using animations
    QColor frameOutlineColor(const QPalette &palette, bool mouseOver = false, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false) const;

    //* input outline color, using animations
    QColor inputOutlineColor(const QPalette &palette, bool mouseOver = false, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false) const;

    //* side panel outline color, using animations
    QColor sidePanelOutlineColor(const QPalette &palette, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone) const;

    //* frame background color
    QColor frameBackgroundColor(const QPalette &palette) const
    {
        return frameBackgroundColor(palette, palette.currentColorGroup());
    }

    //* frame background color
    QColor frameBackgroundColor(const QPalette &palette, QPalette::ColorGroup) const;

    //* arrow outline color
    QColor arrowColor(const QPalette &palette, QPalette::ColorGroup, QPalette::ColorRole) const;

    //* arrow outline color
    QColor arrowColor(const QPalette &palette, QPalette::ColorRole role) const
    {
        return arrowColor(palette, palette.currentColorGroup(), role);
    }

    //* arrow outline color, using animations
    QColor arrowColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone) const;

    //* button outline color, using animations
    QColor buttonOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false) const;

    //* button panel color, using animations
    QColor buttonBackgroundColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false) const;

    //* checkbox/radiobutton color, using animations
    QColor indicatorBackgroundColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, CheckBoxState state = CheckOff, bool darkMode = false, bool inMenu = false) const;

    //* tool button color
    QColor toolButtonColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone) const;

    //* slider outline color, using animations
    QColor sliderOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone) const;

    //* scrollbar handle color, using animations
    QColor scrollBarHandleColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false) const;

    //* checkbox indicator, using animations
    QColor checkBoxIndicatorColor(const QPalette &palette, bool mouseOver, bool active, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone, bool darkMode = false, bool inMenu = false) const;

    //* separator color
    QColor separatorColor(const QPalette &palette, bool darkMode = false) const;

    //* TreeView header text color
    QColor headerTextColor(const QPalette &palette, const QStyle::State state) const;

    //* TabBar background color
    QColor tabBarColor(const QPalette &palette, const QStyle::State state) const;

    //* merge active and inactive palettes based on ratio, for smooth enable state change transition
    QPalette disabledPalette(const QPalette &palette, qreal ratio) const;

    //@}

    //*@name rendering utilities
    //@{

    //* debug frame
    void renderDebugFrame(QPainter *painter, const QRect &) const;

    //* focus rect
    void renderFocusRect(QPainter *painter, const QRect &rect, const QColor &, const QColor &outline = QColor(), Sides = Side::SideNone) const;

    //* focus line
    void renderFocusLine(QPainter *painter, const QRect &rect, const QColor &) const;

    //* generic frame
    void renderFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline = QColor(), bool hasFocus = false) const;

    //* square frame
    void renderSquareFrame(QPainter *painter, const QRect &rect, QColor color, bool hasFocus) const;

    //* generic frame flat on right side
    void renderFlatFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline = QColor(), bool hasFocus = false) const;

    //* side panel frame
    void renderSidePanelFrame(QPainter *painter, const QRect &rect, const QColor &outline, Side) const;

    //* menu frame
    void renderMenuFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool roundCorners = true) const;

    //* button frame
    void renderButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow, bool focus, bool sunken, bool mouseOver, bool active, bool darkMode = false) const;

    //* checkbox frame
    void renderCheckBoxFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow, bool focus, bool sunken, bool mouseOver, bool active, CheckBoxState state = CheckOff, bool darkMode = false, bool inMenu = false) const;

    //* button frame
    void renderFlatButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow, bool focus, bool sunken, bool mouseOver, bool active) const;

    //* toolbutton frame
    void renderToolButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, bool sunken) const;

    //* toolbutton frame
    void renderToolBoxFrame(QPainter *painter, const QRect &rect, int tabWidth, const QColor &color) const;

    //* tab widget frame
    void renderTabWidgetFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, Corners) const;

    //* selection frame
    void renderSelection(QPainter *painter, const QRect &rect, const QColor &) const;

    //* separator
    void renderSeparator(QPainter *painter, const QRect &rect, const QColor &, bool vertical = false) const;

    //* checkbox
    void renderCheckBoxBackground(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool sunken) const;

    //* checkbox
    void renderCheckBox(QPainter *painter, const QRect &rect, const QColor &background, const QColor &outline, const QColor &tickColor, bool sunken, CheckBoxState state, bool mouseOver, qreal animation = AnimationData::OpacityInvalid, bool active = true, bool darkMode = false, bool inMenu = false) const;

    //* radio button
    void renderRadioButtonBackground(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool sunken) const;

    //* radio button
    void renderRadioButton(QPainter *painter, const QRect &rect, const QColor &background, const QColor &outline, const QColor &tickColor, bool sunken, bool enabled, RadioButtonState state, qreal animation = AnimationData::OpacityInvalid, bool mouseOver = false, bool darkMode = false, bool inMenu = false) const;

    //* slider groove
    void renderSliderGroove(QPainter *painter, const QRect &rect, const QColor &) const;

    //* slider handle
    void renderSliderHandle(QPainter *painter, const QRect &rect, const QColor &, const QColor &outline, const QColor &shadow, bool sunken, bool enabled, Side ticks, qreal angle = 0.0, bool darkMode = false) const;

    //* dial groove
    void renderDialGroove(QPainter *painter, const QRect &rect, const QColor &) const;

    //* dial groove
    void renderDialContents(QPainter *painter, const QRect &rect, const QColor &, qreal first, qreal second) const;

    //* progress bar groove
    void renderProgressBarGroove(QPainter *painter, const QRect &rect, const QColor &, const QColor &) const;

    //* progress bar contents
    void renderProgressBarContents(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline) const
    {
        return renderProgressBarGroove(painter, rect, color, outline);
    }

    //* progress bar contents (animated)
    void renderProgressBarBusyContents(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool horizontal, bool reverse, int progress) const;

    //* scrollbar groove
    void renderScrollBarGroove(QPainter *painter, const QRect &rect, const QColor &color) const
    {
        return renderScrollBarHandle(painter, rect, color);
    }

    //* scrollbar handle
    void renderScrollBarHandle(QPainter *painter, const QRect &rect, const QColor &) const;

    //* toolbar handle
    void renderToolBarHandle(QPainter *painter, const QRect &rect, const QColor &color) const
    {
        return renderProgressBarGroove(painter, rect, color, Qt::transparent);
    }

    //* tabbar tab
    void renderTabBarTab(QPainter *painter, const QRect &rect, const QColor &background, const QColor &color, const QColor &outline, Corners, bool renderFrame) const;

    //* generic arrow
    void renderArrow(QPainter *painter, const QRect &rect, const QColor &, ArrowOrientation) const;

    //* generic sign (+-)
    void renderSign(QPainter *painter, const QRect &rect, const QColor &color, bool orientation) const;

    //* generic button (for mdi decorations, tabs and dock widgets)
    void renderDecorationButton(QPainter *painter, const QRect &rect, const QColor &, ButtonType, bool inverted) const;

    //@}

    //*@name compositing utilities
    //@{

    //* true if style was compiled for and is running on X11
    static bool isX11(void);

    //* true if running on platform Wayland
    static bool isWayland(void);

    //* returns true if compositing is active
    bool compositingActive(void) const;

    //* returns true if a given widget supports alpha channel
    bool hasAlphaChannel(const QWidget *) const;

    //@}

    //@name high dpi utility functions
    //@{

    //* return dpi-aware pixmap of given size
    virtual QPixmap highDpiPixmap(const QSize &size) const
    {
        return highDpiPixmap(size.width(), size.height());
    }

    //* return dpi-aware pixmap of given size
    virtual QPixmap highDpiPixmap(int width) const
    {
        return highDpiPixmap(width, width);
    }

    //* return dpi-aware pixmap of given size
    virtual QPixmap highDpiPixmap(int width, int height) const;

    //* return device pixel ratio for a given pixmap
    virtual qreal devicePixelRatio(const QPixmap &) const;

    //@}

    //*@name X11 utilities
    //@{

#if ADWAITA_HAVE_X11

    //* get xcb connection
    static xcb_connection_t *connection(void);

    //* create xcb atom
    xcb_atom_t createAtom(const QString &) const;

#endif

    //@}

    //* frame radius
    qreal frameRadius(qreal bias = 0) const
    {
        return qMax(qreal(Metrics::Frame_FrameRadius) - 0.5 + bias, 0.0);
    }

    void setVariant(QWidget *widget, const QByteArray &variant);

protected:

    //* initialize
    void init(void);

    //* return rectangle for widgets shadow, offset depending on light source
    QRectF shadowRect(const QRectF &) const;

    //* return rounded path in a given rect, with only selected corners rounded, and for a given radius
    QPainterPath roundedPath(const QRectF &, Corners, qreal) const;

private:

#if ADWAITA_HAVE_X11

    //* atom used for compositing manager
    xcb_atom_t _compositingManagerAtom;

#endif

};

}

#endif
