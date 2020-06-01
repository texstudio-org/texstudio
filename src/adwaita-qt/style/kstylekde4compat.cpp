/*************************************************************************
 * Copyright (C) 2015 by David Edmundson <davidedmundson@kde.org>        *
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

#include "kstylekde4compat.h"
#include "adwaita.h"

#include <QToolBar>

static const QStyle::StyleHint SH_KCustomStyleElement = (QStyle::StyleHint)0xff000001;
static const int X_KdeBase = 0xff000000;

//_____________________________________________________________________
KStyleKDE4Compat::KStyleKDE4Compat()
{
    controlCounter = subElementCounter = X_KdeBase;
    hintCounter = X_KdeBase + 1; //sic! X_KdeBase is covered by SH_KCustomStyleElement
}

//_____________________________________________________________________
KStyleKDE4Compat::~KStyleKDE4Compat()
{}

//_____________________________________________________________________
static inline int newStyleElement(const QString &element, const char *check, int &counter, QHash<QString, int> *elements)
{
    if (!element.contains(check))
        return 0;

    int id = elements->value(element, 0);
    if (!id) {
        ++counter;
        id = counter;
        elements->insert(element, id);
    }
    return id;
}

//_____________________________________________________________________
QStyle::StyleHint KStyleKDE4Compat::newStyleHint(const QString &element)
{
    return (StyleHint)newStyleElement(element, "SH_", hintCounter, &styleElements);
}

//_____________________________________________________________________
QStyle::ControlElement KStyleKDE4Compat::newControlElement(const QString &element)
{
    return (ControlElement)newStyleElement(element, "CE_", controlCounter, &styleElements);
}

//_____________________________________________________________________
QStyle::SubElement KStyleKDE4Compat::newSubElement(const QString &element)
{
    return (SubElement)newStyleElement(element, "SE_", subElementCounter, &styleElements);
}

//_____________________________________________________________________
int KStyleKDE4Compat::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{

    if( hint == SH_KCustomStyleElement && widget ) {
        return styleElements.value(widget->objectName(), 0);
    }

    switch (hint) {
    case SH_ItemView_ActivateItemOnSingleClick:
        return Adwaita::Settings::SingleClick;
    case SH_DialogButtonBox_ButtonsHaveIcons:
        return Adwaita::Settings::ShowIconsOnPushButtons;
    case SH_ItemView_ArrowKeysNavigateIntoChildren:
        return true;
    case SH_ToolButtonStyle:
        return Adwaita::Settings::ToolButtonStyle;
    default:
        break;
    };

    return QCommonStyle::styleHint(hint, option, widget, returnData);
}
