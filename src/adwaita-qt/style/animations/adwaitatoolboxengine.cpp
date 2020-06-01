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


#include "adwaitatoolboxengine.h"

namespace Adwaita
{

    //____________________________________________________________
    bool ToolBoxEngine::registerWidget( QWidget* widget )
    {

        if( !widget ) return false;
        if( !_data.contains( widget ) ) { _data.insert( widget, new WidgetStateData( this, widget, duration() ), enabled() ); }

        // connect destruction signal
        connect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(unregisterWidget(QObject*)), Qt::UniqueConnection );
        return true;

    }

    //____________________________________________________________
    bool ToolBoxEngine::updateState( const QPaintDevice* object, bool value )
    {
        PaintDeviceDataMap<WidgetStateData>::Value data( ToolBoxEngine::data( object ) );
        return ( data && data.data()->updateState( value ) );
    }

    //____________________________________________________________
    bool ToolBoxEngine::isAnimated( const QPaintDevice* object )
    {

        PaintDeviceDataMap<WidgetStateData>::Value data( ToolBoxEngine::data( object ) );
        return ( data && data.data()->animation() && data.data()->animation().data()->isRunning() );

    }

}
