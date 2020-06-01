#ifndef adwaitastyleplugin_h
#define adwaitastyleplugin_h

/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
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

#include <QStylePlugin>

namespace Adwaita
{

    class StylePlugin : public QStylePlugin
    {

        Q_OBJECT

        #if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "adwaita.json" )
        #endif

        public:

        //* constructor
        explicit StylePlugin(QObject *parent = 0):
            QStylePlugin(parent)
        {}

        //* destructor
        ~StylePlugin();

        //* returns list of valid keys
        QStringList keys() const;

        //* create style
        QStyle* create( const QString& );

    };

}

#endif
