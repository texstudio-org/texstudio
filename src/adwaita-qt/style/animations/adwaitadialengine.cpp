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

#include "adwaitadialengine.h"

#include <QEvent>

namespace Adwaita
{

    //____________________________________________________________
    bool DialEngine::registerWidget( QWidget* widget, AnimationModes mode )
    {

        // check widget
        if( !widget ) return false;

        // only handle hover and focus
        if( mode&AnimationHover && !dataMap(AnimationHover).contains( widget ) ) { dataMap(AnimationHover).insert( widget, new DialData( this, widget, duration() ), enabled() ); }
        if( mode&AnimationFocus && !dataMap(AnimationFocus).contains( widget ) ) { dataMap(AnimationFocus).insert( widget, new WidgetStateData( this, widget, duration() ), enabled() ); }

        // connect destruction signal
        connect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(unregisterWidget(QObject*)), Qt::UniqueConnection );

        return true;
    }

}
