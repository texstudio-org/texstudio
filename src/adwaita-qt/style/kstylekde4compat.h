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

/**
 * This class copies the features of KF5's KStyle for use in KDE4 only
 *
 * kdelibs4 also has a KStyle class but this isn't a 1-1 mapping and
 * provides a lot of features we do not want
 */

#ifndef KSTYLE_KDE4_COMPAT_H
#define KSTYLE_KDE4_COMPAT_H

#include <QCommonStyle>
#include <QHash>

class KStyleKDE4Compat : public QCommonStyle
{
    Q_OBJECT

public:
    KStyleKDE4Compat();
    ~KStyleKDE4Compat();
    virtual int styleHint(StyleHint hint, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *returnData) const;

protected:
    StyleHint newStyleHint(const QString &element);
    ControlElement newControlElement(const QString &element);
    SubElement newSubElement(const QString &element);

private:
    QHash<QString, int> styleElements;
    int hintCounter;
    int controlCounter;
    int subElementCounter;

};

#endif
