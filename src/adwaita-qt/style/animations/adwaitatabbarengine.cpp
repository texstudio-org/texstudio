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

#include "adwaitatabbarengine.h"

#include <QEvent>

namespace Adwaita
{

    //____________________________________________________________
    bool TabBarEngine::registerWidget( QWidget* widget )
    {

        if( !widget ) return false;

        // create new data class
        if( !_hoverData.contains( widget ) ) _hoverData.insert( widget, new TabBarData( this, widget, duration() ), enabled() );
        if( !_focusData.contains( widget ) ) _focusData.insert( widget, new TabBarData( this, widget, duration() ), enabled() );

        // connect destruction signal
        connect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(unregisterWidget(QObject*)), Qt::UniqueConnection );
        return true;

    }

    //____________________________________________________________
    bool TabBarEngine::updateState( const QObject* object, const QPoint& position, AnimationMode mode, bool value )
    {
        DataMap<TabBarData>::Value data( TabBarEngine::data( object, mode ) );
        return ( data && data.data()->updateState( position, value ) );
    }

    //____________________________________________________________
    bool TabBarEngine::isAnimated( const QObject* object, const QPoint& position, AnimationMode mode )
    {

        DataMap<TabBarData>::Value data( TabBarEngine::data( object, mode ) );
        return ( data && data.data()->animation( position ) && data.data()->animation( position ).data()->isRunning() );

    }

    //____________________________________________________________
    DataMap<TabBarData>::Value TabBarEngine::data( const QObject* object, AnimationMode mode )
    {

        switch( mode )
        {
            case AnimationHover: return _hoverData.find( object ).data();
            case AnimationFocus: return _focusData.find( object ).data();
            default: return DataMap<TabBarData>::Value();
        }

    }

}
