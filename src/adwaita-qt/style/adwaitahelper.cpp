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

#include "adwaitahelper.h"

#include "adwaita.h"

#include <QApplication>
#include <QPainter>
#include <QLibrary>

#if ADWAITA_HAVE_X11 && QT_VERSION < 0x050000
#include <X11/Xlib-xcb.h>
#endif

namespace Adwaita
{

//* contrast for arrow and treeline rendering
static const qreal arrowShade = 0.15;

//____________________________________________________________________
Helper::Helper()
{
    init();
}

//____________________________________________________________________
#if ADWAITA_USE_KDE4
Helper::Helper(const QByteArray &name)
{
    init();
}
#endif

//
QPalette Helper::palette(bool dark) const
{
    QPalette palette;

    if (dark) {
        // Colors defined in GTK adwaita style in _colors.scss
        QColor base_color = lighten(desaturate(QColor("#241f31"), 1.0), 0.02);
        QColor text_color = QColor("white");
        QColor bg_color = darken(desaturate(QColor("#3d3846"), 1.0), 0.04);
        QColor fg_color = QColor("#eeeeec");
        QColor selected_bg_color = darken(QColor("#3584e4"), 0.2);
        QColor selected_fg_color = QColor("white");
        QColor osd_text_color = QColor("white");
        QColor osd_bg_color = QColor("black");
        QColor shadow = transparentize(QColor("black"), 0.9);

        QColor backdrop_fg_color = mix(fg_color, bg_color);
        QColor backdrop_base_color = lighten(base_color, 0.01);
        QColor backdrop_selected_fg_color = mix(text_color, backdrop_base_color, 0.2);

        // This is the color we use as initial color for the gradient in normal state
        // Defined in _drawing.scss button(normal)
        QColor button_base_color = darken(bg_color, 0.01);

        QColor link_color = lighten(selected_bg_color, 0.2);
        QColor link_visited_color = lighten(selected_bg_color, 0.1);

        palette.setColor(QPalette::All,      QPalette::Window,          bg_color);
        palette.setColor(QPalette::All,      QPalette::WindowText,      fg_color);
        palette.setColor(QPalette::All,      QPalette::Base,            base_color);
        palette.setColor(QPalette::All,      QPalette::AlternateBase,   base_color);
        palette.setColor(QPalette::All,      QPalette::ToolTipBase,     osd_bg_color);
        palette.setColor(QPalette::All,      QPalette::ToolTipText,     osd_text_color);
        palette.setColor(QPalette::All,      QPalette::Text,            fg_color);
        palette.setColor(QPalette::All,      QPalette::Button,          button_base_color);
        palette.setColor(QPalette::All,      QPalette::ButtonText,      fg_color);
        palette.setColor(QPalette::All,      QPalette::BrightText,      text_color);

        palette.setColor(QPalette::All,      QPalette::Light,           lighten(button_base_color));
        palette.setColor(QPalette::All,      QPalette::Midlight,        mix(lighten(button_base_color), button_base_color));
        palette.setColor(QPalette::All,      QPalette::Mid,             mix(darken(button_base_color), button_base_color));
        palette.setColor(QPalette::All,      QPalette::Dark,            darken(button_base_color));
        palette.setColor(QPalette::All,      QPalette::Shadow,          shadow);

        palette.setColor(QPalette::All,      QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::All,      QPalette::HighlightedText, selected_fg_color);

        palette.setColor(QPalette::All,      QPalette::Link,            link_color);
        palette.setColor(QPalette::All,      QPalette::LinkVisited,     link_visited_color);


        QColor insensitive_fg_color = mix(fg_color, bg_color);
        QColor insensitive_bg_color = mix(bg_color, base_color, 0.4);

        palette.setColor(QPalette::Disabled, QPalette::Window,          insensitive_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::WindowText,      insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::Base,            base_color);
        palette.setColor(QPalette::Disabled, QPalette::AlternateBase,   base_color);
        palette.setColor(QPalette::Disabled, QPalette::Text,            insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::Button,          insensitive_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::ButtonText,      insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::BrightText,      text_color);

        palette.setColor(QPalette::Disabled, QPalette::Light,           lighten(insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Midlight,        mix(lighten(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Mid,             mix(darken(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Dark,            darken(insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Shadow,          shadow);

        palette.setColor(QPalette::Disabled, QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::HighlightedText, selected_fg_color);

        palette.setColor(QPalette::Disabled, QPalette::Link,            link_color);
        palette.setColor(QPalette::Disabled, QPalette::LinkVisited,     link_visited_color);


        palette.setColor(QPalette::Inactive, QPalette::Window,          bg_color);
        palette.setColor(QPalette::Inactive, QPalette::WindowText,      backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::Base,            backdrop_base_color);
        palette.setColor(QPalette::Inactive, QPalette::AlternateBase,   backdrop_base_color);
        palette.setColor(QPalette::Inactive, QPalette::Text,            backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::Button,          button_base_color);
        palette.setColor(QPalette::Inactive, QPalette::ButtonText,      backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::BrightText,      text_color);

        palette.setColor(QPalette::Inactive, QPalette::Light,           lighten(insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Midlight,        mix(lighten(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Mid,             mix(darken(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Dark,            darken(insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Shadow,          shadow);

        palette.setColor(QPalette::Inactive, QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::Inactive, QPalette::HighlightedText, backdrop_selected_fg_color);

        palette.setColor(QPalette::Inactive, QPalette::Link,            link_color);
        palette.setColor(QPalette::Inactive, QPalette::LinkVisited,     link_visited_color);
    } else {
        // Colors defined in GTK adwaita style in _colors.scss
        QColor base_color = QColor("white");
        QColor text_color = QColor("black");
        QColor bg_color = QColor("#f6f5f4");
        QColor fg_color = QColor("#2e3436");
        QColor selected_bg_color = QColor("#3584e4");
        QColor selected_fg_color = QColor("white");
        QColor osd_text_color = QColor("white");
        QColor osd_bg_color = QColor("black");
        QColor shadow = transparentize(QColor("black"), 0.9);

        QColor backdrop_fg_color = mix(fg_color, bg_color);
        QColor backdrop_base_color = darken(base_color, 0.01);
        QColor backdrop_selected_fg_color = backdrop_base_color;

        // This is the color we use as initial color for the gradient in normal state
        // Defined in _drawing.scss button(normal)
        QColor button_base_color = darken(bg_color, 0.04);

        QColor link_color = darken(selected_bg_color, 0.1);
        QColor link_visited_color = darken(selected_bg_color, 0.2);

        palette.setColor(QPalette::All,      QPalette::Window,          bg_color);
        palette.setColor(QPalette::All,      QPalette::WindowText,      fg_color);
        palette.setColor(QPalette::All,      QPalette::Base,            base_color);
        palette.setColor(QPalette::All,      QPalette::AlternateBase,   base_color);
        palette.setColor(QPalette::All,      QPalette::ToolTipBase,     osd_bg_color);
        palette.setColor(QPalette::All,      QPalette::ToolTipText,     osd_text_color);
        palette.setColor(QPalette::All,      QPalette::Text,            fg_color);
        palette.setColor(QPalette::All,      QPalette::Button,          button_base_color);
        palette.setColor(QPalette::All,      QPalette::ButtonText,      fg_color);
        palette.setColor(QPalette::All,      QPalette::BrightText,      text_color);

        palette.setColor(QPalette::All,      QPalette::Light,           lighten(button_base_color));
        palette.setColor(QPalette::All,      QPalette::Midlight,        mix(lighten(button_base_color), button_base_color));
        palette.setColor(QPalette::All,      QPalette::Mid,             mix(darken(button_base_color), button_base_color));
        palette.setColor(QPalette::All,      QPalette::Dark,            darken(button_base_color));
        palette.setColor(QPalette::All,      QPalette::Shadow,          shadow);

        palette.setColor(QPalette::All,      QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::All,      QPalette::HighlightedText, selected_fg_color);

        palette.setColor(QPalette::All,      QPalette::Link,            link_color);
        palette.setColor(QPalette::All,      QPalette::LinkVisited,     link_visited_color);

        QColor insensitive_fg_color = mix(fg_color, bg_color);
        QColor insensitive_bg_color = mix(bg_color, base_color, 0.4);

        palette.setColor(QPalette::Disabled, QPalette::Window,          insensitive_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::WindowText,      insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::Base,            base_color);
        palette.setColor(QPalette::Disabled, QPalette::AlternateBase,   base_color);
        palette.setColor(QPalette::Disabled, QPalette::Text,            insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::Button,          insensitive_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::ButtonText,      insensitive_fg_color);
        palette.setColor(QPalette::Disabled, QPalette::BrightText,      text_color);

        palette.setColor(QPalette::Disabled, QPalette::Light,           lighten(insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Midlight,        mix(lighten(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Mid,             mix(darken(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Dark,            darken(insensitive_bg_color));
        palette.setColor(QPalette::Disabled, QPalette::Shadow,          shadow);

        palette.setColor(QPalette::Disabled, QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::Disabled, QPalette::HighlightedText, selected_fg_color);

        palette.setColor(QPalette::Disabled, QPalette::Link,            link_color);
        palette.setColor(QPalette::Disabled, QPalette::LinkVisited,     link_visited_color);


        palette.setColor(QPalette::Inactive, QPalette::Window,          bg_color);
        palette.setColor(QPalette::Inactive, QPalette::WindowText,      backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::Base,            backdrop_base_color);
        palette.setColor(QPalette::Inactive, QPalette::AlternateBase,   backdrop_base_color);
        palette.setColor(QPalette::Inactive, QPalette::Text,            backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::Button,          button_base_color);
        palette.setColor(QPalette::Inactive, QPalette::ButtonText,      backdrop_fg_color);
        palette.setColor(QPalette::Inactive, QPalette::BrightText,      text_color);

        palette.setColor(QPalette::Inactive, QPalette::Light,           lighten(insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Midlight,        mix(lighten(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Mid,             mix(darken(insensitive_bg_color), insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Dark,            darken(insensitive_bg_color));
        palette.setColor(QPalette::Inactive, QPalette::Shadow,          shadow);

        palette.setColor(QPalette::Inactive, QPalette::Highlight,       selected_bg_color);
        palette.setColor(QPalette::Inactive, QPalette::HighlightedText, backdrop_selected_fg_color);

        palette.setColor(QPalette::Inactive, QPalette::Link,            link_color);
        palette.setColor(QPalette::Inactive, QPalette::LinkVisited,     link_visited_color);
    }

    return palette;
}

//____________________________________________________________________
QColor Helper::indicatorOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode, CheckBoxState state, bool darkMode, bool inMenu) const
{
    bool isDisabled = palette.currentColorGroup() == QPalette::Disabled;
    if (inMenu || state == CheckBoxState::CheckOff) {

        if (isDisabled) {
            return buttonOutlineColor(palette, mouseOver, hasFocus, opacity, mode, darkMode);
        }

        if (darkMode) {
            return darken(palette.color(QPalette::Window), 0.18);
        } else {
            return darken(palette.color(QPalette::Window), 0.24);
        }
    } else {
        return palette.color(QPalette::Highlight);
    }
}

QColor Helper::frameOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode, bool darkMode) const
{
    // I really can't remember why we have differed these two cases. This seems right.
    return inputOutlineColor(palette, mouseOver, hasFocus, opacity, mode, darkMode);
}

QColor Helper::inputOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode, bool darkMode) const
{
    QColor outline(buttonOutlineColor(palette, mouseOver, false, opacity, mode, darkMode));

    // focus takes precedence over hover
    if (mode == AnimationFocus) {
        outline = mix(outline, focusColor(palette), opacity);
    } else if (hasFocus) {
        outline = focusColor(palette);
    }

    return outline;
}

//____________________________________________________________________
QColor Helper::sidePanelOutlineColor(const QPalette &palette, bool hasFocus, qreal opacity, AnimationMode mode) const
{
    QColor outline(palette.color(QPalette::Inactive, QPalette::Highlight));
    QColor focus(palette.color(QPalette::Active, QPalette::Highlight));

    if (mode == AnimationFocus) {
        outline = mix(outline, focus, opacity);
    } else if (hasFocus) {
        outline = focus;
    }

    return outline;
}

//____________________________________________________________________
QColor Helper::frameBackgroundColor(const QPalette &palette, QPalette::ColorGroup group) const
{
    return mix(palette.color(group, QPalette::Window), palette.color(group, QPalette::Base), 0.3);
}

//____________________________________________________________________
QColor Helper::arrowColor(const QPalette &palette, QPalette::ColorGroup group, QPalette::ColorRole role) const
{
    switch (role) {
    case QPalette::Text:
        return mix(palette.color(group, QPalette::Text), palette.color(group, QPalette::Base), arrowShade);
    case QPalette::WindowText:
        return mix(palette.color(group, QPalette::WindowText), palette.color(group, QPalette::Window), arrowShade);
    case QPalette::ButtonText:
        return mix(palette.color(group, QPalette::ButtonText), palette.color(group, QPalette::Button), arrowShade);
    default:
        return palette.color(group, role);
    }
}

//____________________________________________________________________
QColor Helper::arrowColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode) const
{
    Q_UNUSED(mouseOver);
    Q_UNUSED(hasFocus);
    Q_UNUSED(opacity);
    Q_UNUSED(mode);
    return palette.text().color();
}

//____________________________________________________________________
QColor Helper::buttonOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode, bool darkMode) const
{
    if (darkMode) {
        return darken(palette.color(QPalette::Window), 0.1);
    } else {
        return darken(palette.color(QPalette::Window), 0.18);
    }
}

//____________________________________________________________________
QColor Helper::buttonBackgroundColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity, AnimationMode mode, bool darkMode) const
{
    bool isDisabled = palette.currentColorGroup() == QPalette::Disabled;
    QColor buttonBackground(palette.color(QPalette::Button));
    QColor background(palette.color(QPalette::Window));

    if (isDisabled && (mode == AnimationPressed || sunken)) {
        // Defined in drawing.css - insensitive-active button
        // if($variant == 'light', darken(mix($c, $base_color, 85%), 8%), darken(mix($c, $base_color, 85%), 6%));
        // FIXME: doesn't seem to be correct color
        return darkMode ? darken(mix(palette.color(QPalette::Active, QPalette::Window), palette.color(QPalette::Active, QPalette::Base), 0.15), 0.06) :
                          darken(mix(palette.color(QPalette::Active, QPalette::Window), palette.color(QPalette::Active, QPalette::Base), 0.15), 0.08);
    }

    if (mode == AnimationPressed) {
        if (darkMode) {
            // Active button for dark mode is darken(bg_color, 0.09)
            return mix(darken(background, 0.01), darken(background, 0.09), opacity);
        } else {
            // Active button for normal mode is darken(bg_color, 0.14)
            return mix(buttonBackground, darken(background, 0.14), opacity);
        }
    } else if (sunken) {
        if (darkMode) {
            // Active button for dark mode is darken(bg_color, 0.09)
            return darken(background, 0.09);
        } else {
            // Active button for normal mode is darken(bg_color, 0.14)
            return darken(background, 0.14);
        }
    } else if (mode == AnimationHover) {
        if (darkMode) {
            // Hovered button for dark mode is darken(bg_color, 0.01)
            return mix(buttonBackground, darken(background, 0.01), opacity);
        } else {
            // Hovered button for normal mode is bg_color
            return mix(buttonBackground, background, opacity);
        }
    } else if (mouseOver) {
        if (darkMode) {
            // Hovered button for dark mode is darken(bg_color, 0.01)
            return darken(background, 0.01);
        } else {
            // Hovered button for normal mode is bg_color
            return background;
        }
    }

    return buttonBackground;
}

//
QColor Helper::indicatorBackgroundColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity, AnimationMode mode, CheckBoxState state, bool darkMode, bool inMenu) const
{
    bool isDisabled = palette.currentColorGroup() == QPalette::Disabled;
    QColor background(palette.color(QPalette::Window));
    // Normal-alt button for dark mode is darken(bg_color, 0.03)
    // Normal-alt button for normal mode is lighten(bg_color, 0.05)
    QColor indicatorColor(darkMode ? darken(background, 0.03) : lighten(background, 0.05));

    if (inMenu || state == CheckOff) {
        if (isDisabled) {
            // Defined in drawing.css - insensitive button
            // $insensitive_bg_color: mix($bg_color, $base_color, 60%);
            return mix(palette.color(QPalette::Active, QPalette::Window), palette.color(QPalette::Active, QPalette::Base), 0.6);
        }

        if (mode == AnimationPressed) {
            if (darkMode) {
                // Active button for dark mode is darken(bg_color, 0.09)
                return mix(background, darken(background, 0.09), opacity);
            } else {
                // Active button for normal mode is darken(bg_color, 0.14)
                return mix(lighten(background, 0.0), darken(background, 0.14), opacity);
            }
        } else if (sunken) {
            if (darkMode) {
                // Active button for dark mode is darken(bg_color, 0.09)
                return darken(background, 0.09);
            } else {
                // Active button for normal mode is darken(bg_color, 0.14)
                return darken(background, 0.14);
            }
        } else if (mode == AnimationHover) {
            if (darkMode) {
                // Hovered-alt button for dark mode is bg_color
                return mix(indicatorColor, background, opacity);
            } else {
                // Hovered-alt button for normal mode is lighten(bg_color, 0.09)
                return mix(indicatorColor, lighten(background, 0.09), opacity);
            }
        } else if (mouseOver) {
            if (darkMode) {
                // Hovered-alt button for dark mode is bg_color
                return background;
            } else {
                // Hovered-alt button for normal mode is lighten(bg_color, 0.09)
                return lighten(background, 0.09);
            }
        }
    } else {
        if (darkMode) {
            return lighten(palette.color(QPalette::Highlight));
        } else {
            return palette.color(QPalette::Highlight);
        }
    }

    return indicatorColor;
}

//____________________________________________________________________
QColor Helper::toolButtonColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity, AnimationMode mode) const
{
    if (sunken || (mode != AnimationNone && mode != AnimationHover))
        return buttonBackgroundColor(palette, mouseOver, hasFocus, sunken, opacity, mode);
    return Qt::transparent;
}

//____________________________________________________________________
QColor Helper::sliderOutlineColor(const QPalette &palette, bool mouseOver, bool hasFocus, qreal opacity, AnimationMode mode) const
{
    QColor outline(mix(palette.color(QPalette::Window), palette.color(QPalette::Shadow), 0.5));

    // hover takes precedence over focus
    if (mode == AnimationHover) {
        QColor hover(hoverColor(palette));
        QColor focus(focusColor(palette));
        if (hasFocus)
            outline = mix(focus, hover, opacity);
        else
            outline = mix(outline, hover, opacity);
    } else if (mouseOver) {
        outline = hoverColor(palette);
    } else if (mode == AnimationFocus) {
        QColor focus(focusColor(palette));
        outline = mix(outline, focus, opacity);
    } else if (hasFocus) {
        outline = focusColor(palette);
    }

    return outline;
}

//____________________________________________________________________
QColor Helper::scrollBarHandleColor(const QPalette &palette, bool mouseOver, bool hasFocus, bool sunken, qreal opacity, AnimationMode mode, bool darkMode) const
{
    QColor fgColor = palette.color(QPalette::Text);
    QColor bgColor = palette.color(QPalette::Window);
    QColor selectedBgColor = palette.color(QPalette::Highlight);

    QColor color(mix(fgColor, bgColor, 0.4));
    QColor hoverColor(mix(fgColor, bgColor, 0.2));
    QColor activeColor(darkMode ? lighten(selectedBgColor, 0.1) : darken(selectedBgColor, 0.1));

    // hover takes precedence over focus
    if (mode == AnimationPressed) {
        if (mouseOver)
            color = mix(hoverColor, activeColor, opacity);
        else
            color = mix(color, activeColor, opacity);
    } else if (sunken) {
        color = activeColor;
    } else if (mode == AnimationHover) {
        color = mix(color, hoverColor, opacity);
    } else if (mouseOver) {
        color = hoverColor;
    }

    return color;
}

//______________________________________________________________________________
QColor Helper::checkBoxIndicatorColor(const QPalette &palette, bool mouseOver, bool active, qreal opacity, AnimationMode mode, bool darkMode, bool inMenu) const
{
    Q_UNUSED(mouseOver);
    Q_UNUSED(active);
    Q_UNUSED(opacity);
    Q_UNUSED(mode);

    if (inMenu) {
        return palette.color(QPalette::Text);
    } else {
        if (active) {
            return palette.color(QPalette::HighlightedText);
        } else {
            return transparentize(palette.color(QPalette::ToolTipText), 0.2);
        }
    }
}

//______________________________________________________________________________
QColor Helper::separatorColor(const QPalette &palette, bool darkMode) const
{
    return buttonOutlineColor(palette, false, false, AnimationData::OpacityInvalid, AnimationNone, darkMode);
}

//____________________________________________________________________
QColor Helper::headerTextColor(const QPalette &palette, const QStyle::State state) const
{
    QColor col(palette.color(QPalette::WindowText));

    if (state & QStyle::State_Enabled) {
        if (state & QStyle::State_Sunken)
            return alphaColor(col, 0.9);
        else if (state & QStyle::State_MouseOver)
            return alphaColor(col, 0.7);
    }
    return alphaColor(col, 0.5);
}

QColor Helper::tabBarColor(const QPalette &palette, const QStyle::State state) const
{
    QColor background(mix(palette.window().color(), palette.shadow().color(), 0.15));
    if (!(state & QStyle::State_Enabled))
        background = background.lighter(115);
    if (!(state & QStyle::State_Active))
        background = background.lighter(115);
    return background;
}

//______________________________________________________________________________
QPalette Helper::disabledPalette(const QPalette &source, qreal ratio) const
{
    QPalette copy(source);

    const QList<QPalette::ColorRole> roles = { QPalette::Base, QPalette::Highlight, QPalette::WindowText, QPalette::ButtonText, QPalette::Text, QPalette::Button };
    foreach (const QPalette::ColorRole &role, roles) {
        copy.setColor(role, mix(source.color(QPalette::Active, role), source.color(QPalette::Disabled, role), 1.0 - ratio));
    }

    return copy;
}

//____________________________________________________________________
QColor Helper::alphaColor(QColor color, qreal alpha) const
{
    if (alpha >= 0 && alpha < 1.0) {
        color.setAlphaF(alpha * color.alphaF());
    }
    return color;
}

//______________________________________________________________________________
void Helper::renderDebugFrame(QPainter *painter, const QRect &rect) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::red);
    painter->drawRect(QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5));
    painter->restore();
}

//______________________________________________________________________________
void Helper::renderFocusRect(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, Sides sides) const
{
    if (!color.isValid())
        return;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(color);

    if (!(outline.isValid() && sides)) {
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect);
    } else {
        painter->setClipRect(rect);

        QRectF copy(rect);
        copy.adjust(0.5, 0.5, -0.5, -0.5);

        qreal radius(frameRadius(-1.0));
        if (!(sides & SideTop))
            copy.adjust(0, -radius, 0, 0);
        if (!(sides & SideBottom))
            copy.adjust(0, 0, 0, radius);
        if (!(sides & SideLeft))
            copy.adjust(-radius, 0, 0, 0);
        if (!(sides & SideRight))
            copy.adjust(0, 0, radius, 0);

        painter->setPen(outline);
        // painter->setBrush( Qt::NoBrush );
        painter->drawRoundedRect(copy, radius, radius);
    }

    painter->restore();
    return;
}

//______________________________________________________________________________
void Helper::renderFocusLine(QPainter *painter, const QRect &rect, const QColor &color) const
{
    if (!color.isValid())
        return;

    painter->save();

    QPen pen(color, 1);
    pen.setStyle(Qt::DotLine);

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    painter->drawRoundedRect(rect, 1, 1);

    painter->restore();
}

//______________________________________________________________________________
void Helper::renderFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool hasFocus) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF frameRect(rect.adjusted(1, 1, -1, -1));
    qreal radius(frameRadius());

    // set pen
    if (outline.isValid()) {
        if (hasFocus) {
            painter->setPen(QPen(outline, 2));
            frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        } else {
            painter->setPen(outline);
        }
        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));

    } else {
        painter->setPen(Qt::NoPen);
    }

    // set brush
    if (color.isValid())
        painter->setBrush(color);
    else
        painter->setBrush(Qt::NoBrush);

    // render
    painter->drawRoundedRect(frameRect, radius, radius);
}

//______________________________________________________________________________
void Helper::renderSquareFrame(QPainter *painter, const QRect &rect, QColor color, bool hasFocus) const
{
    painter->setPen(color);
    painter->drawRect(rect.adjusted(1, 1, -2, -2));
    if (hasFocus) {
        color.setAlphaF(0.5);
        painter->setPen(color);
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
}

//______________________________________________________________________________
void Helper::renderFlatFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool hasFocus) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF frameRect(rect.adjusted(1, 1, -1, -1));
    qreal radius(frameRadius());

    // set pen
    if (outline.isValid()) {
        if (hasFocus) {
            painter->setPen(QPen(outline, 2));
            frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        } else {
            painter->setPen(outline);
        }
        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));
    } else {
        painter->setPen(Qt::NoPen);
    }

    // set brush
    if (color.isValid())
        painter->setBrush(color);
    else
        painter->setBrush(Qt::NoBrush);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(frameRect.adjusted(2 * radius, 0, 0, 0));
    path.addRoundedRect(frameRect.adjusted(0, 0, - 2 * radius, 0), radius, radius);

    painter->drawPath(path.simplified());

    // render
    //painter->drawRoundedRect( frameRect, radius, radius );
}

//______________________________________________________________________________
void Helper::renderSidePanelFrame(QPainter *painter, const QRect &rect, const QColor &outline, Side side) const
{
    // check color
    if (!outline.isValid())
        return;

    // adjust rect
    QRectF frameRect(rect.adjusted(1, 1, -1, -1));
    frameRect.adjust(0.5, 0.5, -0.5, -0.5);

    // setup painter
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(outline);

    // render
    switch (side) {
    case SideLeft:
        frameRect.adjust(0, 1, 0, -1);
        painter->drawLine(frameRect.topRight(), frameRect.bottomRight());
        break;
    case SideTop:
        frameRect.adjust(1, 0, -1, 0);
        painter->drawLine(frameRect.topLeft(), frameRect.topRight());
        break;
    case SideRight:
        frameRect.adjust(0, 1, 0, -1);
        painter->drawLine(frameRect.topLeft(), frameRect.bottomLeft());
        break;
    case SideBottom:
        frameRect.adjust(1, 0, -1, 0);
        painter->drawLine(frameRect.bottomLeft(), frameRect.bottomRight());
        break;
    case AllSides: {
        qreal radius(frameRadius(-1.0));
        painter->drawRoundedRect(frameRect, radius, radius);
        break;
    }
    default:
        break;
    }
}

//______________________________________________________________________________
void Helper::renderMenuFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool roundCorners) const
{
    // set brush
    if (color.isValid())
        painter->setBrush(color);
    else
        painter->setBrush(Qt::NoBrush);

    painter->setRenderHint(QPainter::Antialiasing, false);
    QRectF frameRect(rect);
    if (outline.isValid()) {
        painter->setPen(outline);
        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
    } else
        painter->setPen(Qt::NoPen);

    painter->drawRect(frameRect);
}

//______________________________________________________________________________
void Helper::renderButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow,
                               bool hasFocus, bool sunken, bool mouseOver, bool active, bool darkMode) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(1, 1, -1, -1);
    qreal radius(frameRadius());

    if (outline.isValid()) {
        painter->setPen(QPen(outline, 1.0));

        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));
    } else
        painter->setPen(Qt::NoPen);

    // content
    if (color.isValid() && active) {
        QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
        if (sunken) {
            // Pressed button in normal and dark mode is not a gradient, just an image consting from same $color
            gradient.setColorAt(0, color);
            gradient.setColorAt(1, color);
        } else if (mouseOver) {
            if (darkMode) {
                QColor baseColor = lighten(color, 0.01);
                // Hovered button in dark mode is a gradient from $color to lighten(bg_color, 0.01)
                gradient.setColorAt(0, lighten(baseColor, 0.01)); // FIXME not correct according to adwaita's _drawing.scss file, but looks more close than before
                gradient.setColorAt(1, lighten(baseColor, 0.01));
            } else {
                QColor baseColor = color;
                // Hovered button in normal mode is a gradient from $color to lighten(bg_color, 0.01)
                gradient.setColorAt(0, color);
                gradient.setColorAt(1, lighten(baseColor, 0.01));
            }
        } else {
            if (darkMode) {
                QColor baseColor = lighten(color, 0.01);
                // Normal button in dark mode is a gradient from $color to bg_color
                gradient.setColorAt(0, color);
                gradient.setColorAt(1, baseColor);
            } else {
                QColor baseColor = lighten(color, 0.04);
                // Normal button in normal mode is a gradient from $color to bg_color
                gradient.setColorAt(0, color);
                gradient.setColorAt(1, baseColor);
            }
        }
        painter->setBrush(gradient);
    } else if (!active) {
        painter->setBrush(color);
    } else {
        painter->setBrush(Qt::NoBrush);
    }

    // render
    painter->drawRoundedRect(frameRect, radius, radius);

    if (!sunken && active && color.isValid()) {
        painter->setPen(color.lighter(140));
        painter->drawLine(frameRect.topLeft() + QPoint(3, 1), frameRect.topRight() + QPoint(-3, 1));
        painter->setPen(outline.darker(114));
        painter->drawLine(frameRect.bottomLeft() + QPointF(2.7, 0), frameRect.bottomRight() + QPointF(-2.7, 0));
    }
}

//______________________________________________________________________________
void Helper::renderCheckBoxFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow,
                               bool hasFocus, bool sunken, bool mouseOver, bool active, CheckBoxState state, bool darkMode, bool inMenu) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(1, 1, -1, -1);
    qreal radius(frameRadius());

    if (outline.isValid()) {
        painter->setPen(QPen(outline, 1.0));

        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));
    } else
        painter->setPen(Qt::NoPen);

    if (inMenu || state == CheckOff) {
        // content
        if (color.isValid() && active) {
            QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
            if (sunken) {
                    // Pressed-alt button in dark mode is not a gradient, just an image consting from same $color
                if (darkMode) {
                    gradient.setColorAt(0, color);
                    gradient.setColorAt(1, color);
                } else {
                    // Pressed-alt button in normal mode is not a gradient, just an image consting from same $color
                    gradient.setColorAt(0, color);
                    gradient.setColorAt(1, color);
                }
            } else if (mouseOver) {
                if (darkMode) {
                    QColor baseColor = color;
                    // Hovered-alt button in dark mode is a gradient from $color to darken(bg_color, 0.04)
                    gradient.setColorAt(0, darken(baseColor, 0.04));
                    gradient.setColorAt(1, color);
                } else {
                    QColor baseColor = darken(color, 0.09);
                    // Hovered-alt button in normal mode is a gradient from $color to lighten(bg_color, 0.04)
                    gradient.setColorAt(0, color);                      // FIXME:
                    gradient.setColorAt(1, lighten(baseColor, 0.04));   // should be vice-versa, but this way it seems to be more accurate
                }
            } else {
                if (darkMode) {
                    QColor baseColor = lighten(color, 0.03);
                    // Normal-alt button in dark mode is a gradient from $color to darken(bg_color, 0.06)
                    gradient.setColorAt(0, darken(baseColor, 0.06));
                    gradient.setColorAt(1, color);
                } else {
                    QColor baseColor = darken(color, 0.05);
                    // Normal-alt button in normal mode is a gradient from $color to bg_color
                    gradient.setColorAt(0, baseColor);
                    gradient.setColorAt(1, color);
                }
            }
            painter->setBrush(gradient);
        } else if (!active) {
            painter->setBrush(color);
        } else {
            painter->setBrush(Qt::NoBrush);
        }
    } else {
        if (color.isValid()) {
            QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
            gradient.setColorAt(0, color);
            gradient.setColorAt(1, lighten(color, 0.04));
            painter->setBrush(gradient);
        } else {
            painter->setBrush(Qt::NoBrush);
        }
    }

    // render
    painter->drawRoundedRect(frameRect, radius, radius);
}

//______________________________________________________________________________
void Helper::renderFlatButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow,
                                   bool hasFocus, bool sunken, bool mouseOver, bool active) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(1, 1, -1, -1);
    qreal radius(frameRadius());

    if (outline.isValid()) {
        painter->setPen(QPen(outline, 1.0));

        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));
    } else
        painter->setPen(Qt::NoPen);

    // content
    if (color.isValid()) {
        QLinearGradient gradient(frameRect.topLeft(), frameRect.bottomLeft());
        //gradient.setColorAt( 0, color.darker( sunken ? 110 : (hasFocus|mouseOver) ? 85 : 100 ) );
        //gradient.setColorAt( 1, color.darker( sunken ? 130 : (hasFocus|mouseOver) ? 95 : 110 ) );

        if (!active) {
            gradient.setColorAt(0, color);
        } else if (sunken) {
            gradient.setColorAt(0, color);
        } else {
            gradient.setColorAt(0, mix(color, Qt::white, 0.07));
            gradient.setColorAt(1, mix(color, Qt::black, 0.1));
        }
        painter->setBrush(gradient);
    } else
        painter->setBrush(Qt::NoBrush);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(frameRect.adjusted(2 * radius, 0, 0, 0), radius, radius);
    path.addRect(frameRect.adjusted(0, 0, -2 * radius, 0));
    painter->drawPath(path.simplified());

    if (!sunken && active) {
        painter->setPen(color.lighter(140));
        painter->drawLine(frameRect.topLeft() + QPoint(1, 1), frameRect.topRight() + QPoint(-3, 1));
        painter->setPen(outline.darker(114));
        painter->drawLine(frameRect.bottomLeft() + QPointF(0.7, 0), frameRect.bottomRight() + QPointF(-2.7, 0));
    }

    // render
    //painter->drawRoundedRect( frameRect, radius, radius );
}

//______________________________________________________________________________
void Helper::renderToolButtonFrame(QPainter *painter, const QRect &rect, const QColor &color, bool sunken) const
{
    // do nothing for invalid color
    if (!color.isValid())
        return;

    // setup painter
    painter->setRenderHints(QPainter::Antialiasing);

    QRectF baseRect(rect);

    if (sunken) {
        qreal radius(frameRadius());

        painter->setPen(Qt::NoPen);
        painter->setBrush(color);

        QRectF contentRect(baseRect.adjusted(1, 1, -1, -1));
        painter->drawRoundedRect(contentRect, radius, radius);
    } else {
        qreal radius(frameRadius(-0.5));

        painter->setPen(color);
        painter->setBrush(Qt::NoBrush);
        QRectF outlineRect(baseRect.adjusted(1.5, 1.5, -1.5, -1.5));
        painter->drawRoundedRect(outlineRect, radius, radius);
    }
}

//______________________________________________________________________________
void Helper::renderToolBoxFrame(QPainter *painter, const QRect &rect, int tabWidth, const QColor &outline) const
{
    if (!outline.isValid())
        return;

    // round radius
    qreal radius(frameRadius());
    QSizeF cornerSize(2 * radius, 2 * radius);

    // if rect - tabwidth is even, need to increase tabWidth by 1 unit
    // for anti aliasing
    if (!((rect.width() - tabWidth) % 2))
        ++tabWidth;

    // adjust rect for antialiasing
    QRectF baseRect(rect);
    baseRect.adjust(0.5, 0.5, -0.5, -0.5);

    // create path
    QPainterPath path;
    path.moveTo(0, baseRect.height() - 1);
    path.lineTo((baseRect.width() - tabWidth) / 2 - radius, baseRect.height() - 1);
    path.arcTo(QRectF(QPointF((baseRect.width() - tabWidth) / 2 - 2 * radius, baseRect.height() - 1 - 2 * radius), cornerSize), 270, 90);
    path.lineTo((baseRect.width() - tabWidth) / 2, radius);
    path.arcTo(QRectF(QPointF((baseRect.width() - tabWidth) / 2, 0), cornerSize), 180, -90);
    path.lineTo((baseRect.width() + tabWidth) / 2 - 1 - radius, 0);
    path.arcTo(QRectF(QPointF((baseRect.width() + tabWidth) / 2  - 1 - 2 * radius, 0), cornerSize), 90, -90);
    path.lineTo((baseRect.width() + tabWidth) / 2 - 1, baseRect.height() - 1 - radius);
    path.arcTo(QRectF(QPointF((baseRect.width() + tabWidth) / 2 - 1, baseRect.height() - 1 - 2 * radius), cornerSize), 180, 90);
    path.lineTo(baseRect.width() - 1, baseRect.height() - 1);

    // render
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(outline);
    painter->translate(baseRect.topLeft());
    painter->drawPath(path);
    painter->restore();

    return;
}

//______________________________________________________________________________
void Helper::renderTabWidgetFrame(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, Corners corners) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF frameRect(rect.adjusted(1, 1, -1, -1));
    qreal radius(frameRadius());

    // set pen
    if (outline.isValid()) {
        painter->setPen(outline);
        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
        radius = qMax(radius - 1, qreal(0.0));
    } else
        painter->setPen(Qt::NoPen);

    // set brush
    if (color.isValid())
        painter->setBrush(color);
    else
        painter->setBrush(Qt::NoBrush);

    // render
    QPainterPath path(roundedPath(frameRect, corners, radius));
    painter->drawPath(path);
}

//______________________________________________________________________________
void Helper::renderSelection(QPainter *painter, const QRect &rect, const QColor &color) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawRect(rect);
}

//______________________________________________________________________________
void Helper::renderSeparator(QPainter *painter, const QRect &rect, const QColor &color, bool vertical) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(color);

    if (vertical) {
        painter->translate(rect.width() / 2, 0);
        painter->drawLine(rect.topLeft(), rect.bottomLeft());
    } else {
        painter->translate(0, rect.height() / 2);
        painter->drawLine(rect.topLeft(), rect.topRight());
    }

    painter->restore();

    return;
}

//______________________________________________________________________________
void Helper::renderCheckBoxBackground(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool sunken) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect and radius
    QRectF frameRect(rect);
    frameRect.adjust(3, 3, -3, -3);

    painter->setPen(outline);
    painter->setBrush(color);
    painter->drawRect(frameRect);
}

//______________________________________________________________________________
void Helper::renderCheckBox(QPainter *painter, const QRect &rect, const QColor &background, const QColor &outline, const QColor &tickColor,
                            bool sunken, CheckBoxState state, bool mouseOver, qreal animation, bool active, bool darkMode, bool inMenu) const
{
    // setup painter
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect and radius
    QRectF frameRect(rect);
    frameRect.adjust(2, 2, -2, -2);
    qreal radius(frameRadius());

    // content
    {
        renderCheckBoxFrame(painter, rect, background, outline, Qt::transparent, false, sunken, mouseOver, active, state, darkMode, inMenu);
    }

    // mark
    if (state == CheckOn) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::NoBrush);
        QPen pen(tickColor, 3);
        pen.setJoinStyle(Qt::MiterJoin);
        painter->setPen(pen);

        QRectF markerRect(frameRect);

        QPainterPath path;
        path.moveTo(markerRect.right() - markerRect.width() / 4, markerRect.top() + markerRect.height() / 3);
        path.lineTo(markerRect.center().x(), markerRect.bottom() - markerRect.height() / 3.0);
        path.lineTo(markerRect.left() + markerRect.width() / 4, markerRect.center().y());

        painter->setClipRect(markerRect);
        painter->drawPath(path);
        painter->restore();
    } else if (state == CheckPartial) {
        QPen pen(tickColor, 4);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);

        QRectF markerRect(frameRect.adjusted(4, 4, -4, -4));

        painter->drawLine(markerRect.center() - QPoint(3, 0), markerRect.center() + QPoint(3, 0));
    } else if (state == CheckAnimated) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::NoBrush);
        QPen pen(tickColor, 3);
        pen.setJoinStyle(Qt::MiterJoin);
        painter->setPen(pen);

        QRectF markerRect(frameRect);

        QPainterPath path;
        path.moveTo(markerRect.right() - markerRect.width() / 4, markerRect.top() + markerRect.height() / 3);
        path.lineTo(markerRect.center().x(), markerRect.bottom() - markerRect.height() / 3.0);
        path.lineTo(markerRect.left() + markerRect.width() / 4, markerRect.center().y());
        path.translate(-markerRect.right(), -markerRect.top());

        painter->setClipRect(markerRect.adjusted(1, 1, -1, -1));
        painter->translate(markerRect.right(), markerRect.top());
        painter->scale(animation, 0.5 + 0.5 * animation);
        painter->drawPath(path);
        painter->restore();
    }

    painter->restore();
}

//______________________________________________________________________________
void Helper::renderRadioButtonBackground(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, bool sunken) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(3, 3, -3, -3);
    if (sunken)
        frameRect.translate(1, 1);

    painter->setPen(outline);
    painter->setBrush(color);
    painter->drawEllipse(frameRect);
}

//______________________________________________________________________________
void Helper::renderRadioButton(QPainter *painter, const QRect &rect, const QColor &background, const QColor &outline, const QColor &tickColor,
                               bool sunken, bool enabled, RadioButtonState state, qreal animation, bool mouseOver, bool darkMode, bool inMenu) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(2, 2, -2, -2);

    if (inMenu || state == RadioOff) {
        if (background.isValid() && enabled) {
            QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
            if (sunken) {
                // Pressed-alt button in normal and dark mode is not a gradient, just an image consting from same $background
                gradient.setColorAt(0, background);
                gradient.setColorAt(1, background);
            } else if (mouseOver) {
                if (darkMode) {
                    QColor baseColor = background;
                    // Hovered-alt button in dark mode is a gradient from $background to darken(bg_background, 0.04)
                    gradient.setColorAt(0, darken(baseColor, 0.04));
                    gradient.setColorAt(1, background);
                } else {
                    QColor baseColor = darken(background, 0.09);
                    // Hovered-alt button in normal mode is a gradient from $background to lighten(bg_background, 0.04)
                    gradient.setColorAt(0, background);                 // FIXME:
                    gradient.setColorAt(1, lighten(baseColor, 0.04));   // should be vice-versa, but this way it seems to be more accurate
                }
            } else {
                if (darkMode) {
                    QColor baseColor = lighten(background, 0.03);
                    // Normal-alt button in dark mode is a gradient from $background to darken(bg_background, 0.06)
                    gradient.setColorAt(0, darken(baseColor, 0.06));
                    gradient.setColorAt(1, background);
                } else {
                    QColor baseColor = darken(background, 0.05);
                    // Normal-alt button in normal mode is a gradient from $background to bg_background
                    gradient.setColorAt(0, baseColor);
                    gradient.setColorAt(1, background);
                }
            }
            painter->setBrush(gradient);
        } else if (!enabled) {
            painter->setBrush(background);
        } else {
            painter->setBrush(Qt::NoBrush);
        }

        painter->setPen(QPen(outline, 1));

        QRectF contentRect(frameRect.adjusted(0.5, 0.5, -0.5, -0.5));
        painter->drawEllipse(contentRect);
    } else {
        if (background.isValid()) {
            QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
            gradient.setColorAt(0, background);
            gradient.setColorAt(1, lighten(background, 0.04));
            painter->setBrush(gradient);
        } else {
            painter->setBrush(Qt::NoBrush);
        }

        painter->setPen(QPen(outline, 1));

        QRectF contentRect(frameRect.adjusted(0.5, 0.5, -0.5, -0.5));
        painter->drawEllipse(contentRect);
    }

    // mark
    if (state == RadioOn) {
        painter->setBrush(tickColor);
        painter->setPen(Qt::NoPen);

        QRectF markerRect(frameRect.adjusted(5, 5, -5, -5));
        painter->drawEllipse(markerRect);
    } else if (state == RadioAnimated) {
        painter->setBrush(tickColor);
        painter->setPen(Qt::NoPen);
        QRectF markerRect(frameRect.adjusted(5, 5, -5, -5));
        qreal remaining = markerRect.width() / 2.0 * (1.0 - animation);
        markerRect.adjust(remaining, remaining, -remaining, -remaining);

        painter->drawEllipse(markerRect);
    }
}

//______________________________________________________________________________
void Helper::renderSliderGroove(QPainter *painter, const QRect &rect, const QColor &color) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF baseRect(rect);
    qreal radius(0.5 * Metrics::Slider_GrooveThickness);

    // content
    if (color.isValid()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawRoundedRect(baseRect, radius, radius);
    }

    return;
}

//______________________________________________________________________________
void Helper::renderDialGroove(QPainter *painter, const QRect &rect, const QColor &color) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF baseRect(rect);

    // content
    if (color.isValid()) {
        qreal penWidth(Metrics::Slider_GrooveThickness);
        QRectF grooveRect(rect.adjusted(penWidth / 2, penWidth / 2, -penWidth / 2, -penWidth / 2));

        painter->setPen(QPen(color, penWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(grooveRect);
    }

    return;
}

//______________________________________________________________________________
void Helper::renderDialContents(QPainter *painter, const QRect &rect, const QColor &color, qreal first, qreal second) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF baseRect(rect);

    // content
    if (color.isValid()) {
        // setup groove rect
        qreal penWidth(Metrics::Slider_GrooveThickness);
        QRectF grooveRect(rect.adjusted(penWidth / 2, penWidth / 2, -penWidth / 2, -penWidth / 2));

        // setup angles
        int angleStart(first * 180 * 16 / M_PI);
        int angleSpan((second - first) * 180 * 16 / M_PI);

        // setup pen
        if (angleSpan != 0) {
            QPen pen(color, penWidth);
            pen.setCapStyle(Qt::RoundCap);
            painter->setPen(pen);
            painter->setBrush(Qt::NoBrush);
            painter->drawArc(grooveRect, angleStart, angleSpan);
        }
    }

    return;
}

//______________________________________________________________________________
void Helper::renderSliderHandle(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline, const QColor &shadow,
                                bool sunken, bool enabled, Side ticks, qreal angle, bool darkMode) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    // copy rect
    QRectF frameRect(rect);
    frameRect.adjust(1, 1, -1, -1);

    // set pen
    if (outline.isValid()) {
        QPen pen(outline);
        pen.setCapStyle(Qt::FlatCap);
        pen.setJoinStyle(Qt::MiterJoin);
        painter->setPen(pen);

        frameRect.adjust(0.5, 0.5, -0.5, -0.5);
    } else
        painter->setPen(Qt::NoPen);

    // set brush
    if (color.isValid() && enabled) {
        QLinearGradient gradient(frameRect.bottomLeft(), frameRect.topLeft());
        if (sunken) {
            // Pressed-alt button in normal and dark mode is not a gradient, just an image consting from same $background
            gradient.setColorAt(0, color);
            gradient.setColorAt(1, color);
        } else {
            if (darkMode) {
                QColor baseColor = lighten(color, 0.03);
                // Normal-alt button in dark mode is a gradient from $color to darken(bg_background, 0.06)
                gradient.setColorAt(0, darken(baseColor, 0.06));
                gradient.setColorAt(1, color);
            } else {
                QColor baseColor = darken(color, 0.05);
                // Normal-alt button in normal mode is a gradient from $color to bg_background
                gradient.setColorAt(0, baseColor);
                gradient.setColorAt(1, color);
            }
        }
        painter->setBrush(gradient);
    }  else if (!enabled) {
        painter->setBrush(color);
    } else {
        painter->setBrush(Qt::NoBrush);
    }

    QRect r(rect.right() - rect.height(), rect.top(), rect.height(), rect.height());
    r.adjust(4.5, 3.5, -2.5, -3.5);

    QPainterPath circle;
    circle.addEllipse(r);
    circle.closeSubpath();

    if (ticks & SideBottom) {
        QPainterPath triangle(r.center());
        triangle.moveTo(r.left() + 1.5, r.center().y() + 5.5);
        triangle.lineTo(r.center().x() + 1, r.bottom() + 4.5);
        triangle.lineTo(r.right() - 0.5, r.center().y() + 5.5);
        triangle.closeSubpath();
        circle = circle.united(triangle);
    } else if (ticks & SideTop) {
        QPainterPath triangle(r.center());
        triangle.moveTo(r.left() + 1.5, r.center().y() - 3.5);
        triangle.lineTo(r.center().x() + 1, r.top() - 2.5);
        triangle.lineTo(r.right() - 0.5, r.center().y() - 3.5);
        triangle.closeSubpath();
        circle = circle.united(triangle);
    } else if (ticks & SideLeft) {
        QPainterPath triangle(r.center());
        triangle.moveTo(r.center().x() - 3.5, r.top() + 1.5);
        triangle.lineTo(r.left() - 2.5, r.center().y() + 1);
        triangle.lineTo(r.center().x() - 3.5, r.bottom() - 0.5);
        triangle.closeSubpath();
        circle = circle.united(triangle);
    } else if (ticks & SideRight) {
        QPainterPath triangle(r.center());
        triangle.moveTo(r.center().x() + 3.5, r.top() + 1.5);
        triangle.lineTo(r.right() + 2.5, r.center().y() + 1);
        triangle.lineTo(r.center().x() + 3.5, r.bottom() - 0.5);
        triangle.closeSubpath();
        circle = circle.united(triangle);
    }

    QTransform rotate;
    rotate.translate(frameRect.center().x(), frameRect.center().y());
    rotate.rotate(angle);
    rotate.translate(-frameRect.center().x(), -frameRect.center().y());
    painter->drawPolygon(circle.toFillPolygon(rotate));
}

//______________________________________________________________________________
void Helper::renderProgressBarGroove(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    QRectF baseRect(rect);
    qreal radius(0.5);

    // content
    if (color.isValid()) {
        painter->setPen(outline);
        painter->setBrush(color);
        painter->drawRoundedRect(baseRect.translated(0.5, 0.5), radius, radius);
    }

    return;
}


//______________________________________________________________________________
void Helper::renderProgressBarBusyContents(QPainter *painter, const QRect &rect, const QColor &color, const QColor &outline,
                                           bool horizontal, bool reverse, int progress) const
{
    Q_UNUSED(reverse);

    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF baseRect(rect);
    qreal radius(0.25 * Metrics::ProgressBar_Thickness);
    QRectF contentRect;
    if (horizontal) {
        contentRect = QRect(baseRect.left(), baseRect.top(), Metrics::ProgressBar_BusyIndicatorSize, baseRect.height());
        contentRect.translate(fabs(progress - 50) / 50.0 * (baseRect.width() - contentRect.width()), 0);
    } else {
        contentRect = QRect(baseRect.left(), baseRect.top(), baseRect.width(), Metrics::ProgressBar_BusyIndicatorSize);
        contentRect.translate(0, fabs(progress - 50) / 50.0 * (baseRect.height() - contentRect.height()));
    }

    painter->setBrush(color);
    painter->setPen(outline);
    painter->drawRoundedRect(contentRect.translated(0.5, 0.5), radius, radius);

    return;
}

//______________________________________________________________________________
void Helper::renderScrollBarHandle(QPainter *painter, const QRect &rect, const QColor &color) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF baseRect(rect);
    qreal metric(rect.width() < rect.height() ? rect.width() : rect.height());
    qreal radius(0.5 * metric);

    // content
    if (color.isValid()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawRoundedRect(baseRect, radius, radius);
    }

    return;
}

//______________________________________________________________________________
void Helper::renderTabBarTab(QPainter *painter, const QRect &rect, const QColor &background, const QColor &color, const QColor &outline, Corners corners, bool renderFrame) const
{
    // setup painter
    painter->setRenderHint(QPainter::Antialiasing, false);

    QRectF frameRect(rect);
    qreal adjustment = 0;

    // pen
    if (outline.isValid()) {
        painter->setPen(outline);
        frameRect.adjust(1.0, 1.0, -1.0, -1.0);
        adjustment = 0;

        painter->setBrush(background);

        // render
        painter->drawRect(frameRect);
    } else if (!renderFrame) {
        adjustment = 9;
    }

    painter->setPen(QPen(color, 6));

    switch (corners) {
    case CornersTop:
        painter->drawLine(frameRect.left() + adjustment, frameRect.bottom(), frameRect.right() - adjustment, frameRect.bottom());
        break;
    case CornersBottom:
        painter->drawLine(frameRect.left() + adjustment, frameRect.top(), frameRect.right() - adjustment, frameRect.top());
        break;
    case CornersLeft:
        painter->drawLine(frameRect.right(), frameRect.top() + adjustment, frameRect.right(), frameRect.bottom() - adjustment);
        break;
    case CornersRight:
        painter->drawLine(frameRect.left(), frameRect.top() + adjustment, frameRect.left(), frameRect.bottom() - adjustment);
        break;
    }
}

//______________________________________________________________________________
// TODO blurry edges
void Helper::renderArrow(QPainter *painter, const QRect &rect, const QColor &color, ArrowOrientation orientation) const
{
    // define polygon
    QPolygonF arrow;
    switch (orientation) {
    case ArrowUp:
        arrow << QPointF(-4, 2) << QPointF(0, -2) << QPointF(4, 2);
        break;
    case ArrowDown:
        arrow << QPointF(-4, -2) << QPointF(0, 2) << QPointF(4, -2);
        break;
    case ArrowLeft:
        arrow << QPointF(2, -4) << QPointF(-2, 0) << QPointF(2, 4);
        break;
    case ArrowRight:
        arrow << QPointF(-2, -4) << QPointF(2, 0) << QPointF(-2, 4);
        break;
    default:
        break;
    }

    QPen pen(color, 1.2);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->translate(QRectF(rect).center());
    painter->setBrush(color);
    painter->setPen(pen);
    painter->drawPolygon(arrow);

    painter->restore();

    return;
}

void Helper::renderSign(QPainter *painter, const QRect &rect, const QColor &color, bool orientation) const
{
    QPen pen(color, 2);
    pen.setCapStyle(Qt::FlatCap);

    QRect r = rect.adjusted(1, 2, 0, 0);

    painter->setPen(pen);
    painter->drawLine(r.center() - QPointF(5, 0), r.center() + QPointF(5, 0));
    if (orientation)
        painter->drawLine(r.center() - QPointF(0, 5), r.center() + QPointF(0, 5));
}

//______________________________________________________________________________
void Helper::renderDecorationButton(QPainter *painter, const QRect &rect, const QColor &color, ButtonType buttonType, bool inverted) const
{
    painter->save();
    painter->setViewport(rect);
    painter->setWindow(0, 0, 18, 18);
    painter->setRenderHints(QPainter::Antialiasing, false);

    // initialize pen
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter->setBrush(Qt::NoBrush);

    pen.setColor(color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(2.0 * qMax(1.0, 18.0 / rect.width()));
    painter->setPen(pen);

    switch (buttonType) {
    case ButtonClose: {
        painter->setRenderHints(QPainter::Antialiasing, true);
        painter->drawLine(QPointF(5, 5), QPointF(13, 13));
        painter->drawLine(13, 5, 5, 13);
        break;
    }
    case ButtonMaximize: {
        painter->drawPolyline(QPolygonF()
                              << QPointF(4, 4)
                              << QPointF(4, 14)
                              << QPointF(14, 14)
                              << QPointF(14, 4));
        break;
    }
    case ButtonMinimize: {

        painter->drawPolyline(QPolygonF()
                              << QPointF(4, 14)
                              << QPointF(14, 14));
        break;
    }
    case ButtonRestore: {
        painter->setPen(pen);
        QPolygonF rect = QPolygonF() << QPointF(0, 0) << QPointF(8, 0) << QPointF(8, 8) << QPointF(0, 8);
        painter->drawPolygon(rect.translated(7, 3));
        painter->drawPolygon(rect.translated(3, 7));
        break;
    }
    default:
        break;
    }

    painter->restore();
    return;
}

//______________________________________________________________________________
bool Helper::isX11(void)
{
#if QT_VERSION >= 0x050000
    static const bool s_isX11 = qApp->platformName() == QLatin1String("xcb");
    return s_isX11;
#else
    return false;
#endif
}

bool Helper::isWayland(void)
{
#if QT_VERSION >= 0x050000
    static const bool s_isWayland = qApp->platformName().startsWith(QLatin1String("wayland"));
    return s_isWayland;
#else
    return false;
#endif
}

//______________________________________________________________________________
QRectF Helper::shadowRect(const QRectF &rect) const
{
    return rect;
}

//______________________________________________________________________________
QPainterPath Helper::roundedPath(const QRectF &rect, Corners corners, qreal radius) const
{
    QPainterPath path;

    // simple cases
    if (corners == 0) {
        path.addRect(rect);
        return path;
    }

    if (corners == AllCorners) {
        path.addRoundedRect(rect, radius, radius);
        return path;
    }

    QSizeF cornerSize(2 * radius, 2 * radius);

    // rotate counterclockwise
    // top left corner
    if (corners & CornerTopLeft) {
        path.moveTo(rect.topLeft() + QPointF(radius, 0));
        path.arcTo(QRectF(rect.topLeft(), cornerSize), 90, 90);
    } else
        path.moveTo(rect.topLeft());

    // bottom left corner
    if (corners & CornerBottomLeft) {
        path.lineTo(rect.bottomLeft() - QPointF(0, radius));
        path.arcTo(QRectF(rect.bottomLeft() - QPointF(0, 2 * radius), cornerSize), 180, 90);
    } else
        path.lineTo(rect.bottomLeft());

    // bottom right corner
    if (corners & CornerBottomRight) {
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.arcTo(QRectF(rect.bottomRight() - QPointF(2 * radius, 2 * radius), cornerSize), 270, 90);
    } else
        path.lineTo(rect.bottomRight());

    // top right corner
    if (corners & CornerTopRight) {
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.arcTo(QRectF(rect.topRight() - QPointF(2 * radius, 0), cornerSize), 0, 90);
    } else
        path.lineTo(rect.topRight());
    path.closeSubpath();
    return path;
}

//________________________________________________________________________________________________________
bool Helper::compositingActive(void) const
{
#if ADWAITA_HAVE_X11
    if (isX11()) {
        // direct call to X
        xcb_get_selection_owner_cookie_t cookie(xcb_get_selection_owner(connection(), _compositingManagerAtom));
        ScopedPointer<xcb_get_selection_owner_reply_t> reply(xcb_get_selection_owner_reply(connection(), cookie, nullptr));
        return reply && reply->owner;

    }
#endif

    // use KWindowSystem
    //return KWindowSystem::compositingActive();
    return false;

}

//____________________________________________________________________
bool Helper::hasAlphaChannel(const QWidget *widget) const
{
    return compositingActive() && widget && widget->testAttribute(Qt::WA_TranslucentBackground);
}

//______________________________________________________________________________________
QPixmap Helper::highDpiPixmap(int width, int height) const
{
#if QT_VERSION >= 0x050300
    qreal dpiRatio(qApp->devicePixelRatio());
    QPixmap pixmap(width * dpiRatio, height * dpiRatio);
    pixmap.setDevicePixelRatio(dpiRatio);
    return pixmap;
#else
    return QPixmap(width, height);
#endif
}

//______________________________________________________________________________________
qreal Helper::devicePixelRatio(const QPixmap &pixmap) const
{
#if QT_VERSION >= 0x050300
    return pixmap.devicePixelRatio();
#else
    Q_UNUSED(pixmap);
    return 1;
#endif
}

#if ADWAITA_HAVE_X11

//____________________________________________________________________
xcb_connection_t *Helper::connection(void)
{

#if QT_VERSION >= 0x050000
    return QX11Info::connection();
#else
    static xcb_connection_t *connection = nullptr;
    if (!connection) {
        Display *display = QX11Info::display();
        if (display) connection = XGetXCBConnection(display);
    }
    return connection;
#endif
}

//____________________________________________________________________
xcb_atom_t Helper::createAtom(const QString &name) const
{
    if (isX11()) {
        xcb_connection_t *connection(Helper::connection());
        xcb_intern_atom_cookie_t cookie(xcb_intern_atom(connection, false, name.size(), qPrintable(name)));
        ScopedPointer<xcb_intern_atom_reply_t> reply(xcb_intern_atom_reply(connection, cookie, nullptr));
        return reply ? reply->atom : 0;
    } else
        return 0;
}

#endif

//____________________________________________________________________
void Helper::init(void)
{
#if ADWAITA_HAVE_X11
    if (isX11()) {
        // create compositing screen
        QString atomName(QStringLiteral("_NET_WM_CM_S%1").arg(QX11Info::appScreen()));
        _compositingManagerAtom = createAtom(atomName);
    }
#endif
}

//____________________________________________________________________
void Helper::setVariant(QWidget *widget, const QByteArray &variant)
{
    if (isX11() && widget) { //  && !widget->testAttribute(Qt::WA_)) {
        static const char *_GTK_THEME_VARIANT = "_GTK_THEME_VARIANT";

        // Check if already set
        QVariant var = widget->property("_GTK_THEME_VARIANT");
        if (var.isValid() && var.toByteArray() == variant) {
            return;
        }

        // Typedef's from xcb/xcb.h - copied so that there is no
        // direct xcb dependency
        typedef quint32 XcbAtom;

        struct XcbInternAtomCookie {
            unsigned int sequence;
        };

        struct XcbInternAtomReply {
            quint8  response_type;
            quint8  pad0;
            quint16 sequence;
            quint32 length;
            XcbAtom atom;
        };

        struct XcbVoidCookie {
            unsigned int sequence;
        };

        typedef void *(*XcbConnectFn)(const char *, int *);
        typedef XcbInternAtomCookie(*XcbInternAtomFn)(void *, quint8, quint16, const char *);
        typedef XcbInternAtomReply * (*XcbInternAtomReplyFn)(void *, XcbInternAtomCookie, void *);
        typedef XcbVoidCookie (*XcbChangePropertyFn)(void *, quint8, quint32, XcbAtom, XcbAtom, quint8, quint32, const void *);
        typedef int (*XcbFlushFn)(void *);

        static QLibrary *lib = 0;
        static XcbAtom variantAtom = 0;
        static XcbAtom utf8TypeAtom = 0;
        static void *xcbConn = 0;
        static XcbChangePropertyFn XcbChangePropertyFnPtr = 0;
        static XcbFlushFn XcbFlushFnPtr = 0;

        if (!lib) {
            lib = new QLibrary("libxcb", qApp);

            if (lib->load()) {
                XcbConnectFn XcbConnectFnPtr = (XcbConnectFn)lib->resolve("xcb_connect");
                XcbInternAtomFn XcbInternAtomFnPtr = (XcbInternAtomFn)lib->resolve("xcb_intern_atom");
                XcbInternAtomReplyFn XcbInternAtomReplyFnPtr = (XcbInternAtomReplyFn)lib->resolve("xcb_intern_atom_reply");

                XcbChangePropertyFnPtr = (XcbChangePropertyFn)lib->resolve("xcb_change_property");
                XcbFlushFnPtr = (XcbFlushFn)lib->resolve("xcb_flush");
                if (XcbConnectFnPtr && XcbInternAtomFnPtr && XcbInternAtomReplyFnPtr && XcbChangePropertyFnPtr && XcbFlushFnPtr) {
                    xcbConn = (*XcbConnectFnPtr)(0, 0);
                    if (xcbConn) {
                        XcbInternAtomReply *typeReply = (*XcbInternAtomReplyFnPtr)(xcbConn, (*XcbInternAtomFnPtr)(xcbConn, 0, 11, "UTF8_STRING"), 0);

                        if (typeReply) {
                            XcbInternAtomReply *gtkVarReply = (*XcbInternAtomReplyFnPtr)(xcbConn,
                                                              (*XcbInternAtomFnPtr)(xcbConn, 0, strlen(_GTK_THEME_VARIANT),
                                                                      _GTK_THEME_VARIANT), 0);
                            if (gtkVarReply) {
                                utf8TypeAtom = typeReply->atom;
                                variantAtom = gtkVarReply->atom;
                                free(gtkVarReply);
                            }
                            free(typeReply);
                        }
                    }
                }
            }
        }

        if (0 != variantAtom) {
            (*XcbChangePropertyFnPtr)(xcbConn, 0, widget->effectiveWinId(), variantAtom, utf8TypeAtom, 8,
                                      variant.length(), (const void *)variant.constData());
            (*XcbFlushFnPtr)(xcbConn);
            widget->setProperty(_GTK_THEME_VARIANT, variant);
        }
    }
}

}
