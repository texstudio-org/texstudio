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

#include "adwaitadialdata.h"

#include <QHoverEvent>
#include <QDial>

namespace Adwaita
{

    //______________________________________________
    DialData::DialData( QObject* parent, QWidget* target, int duration ):
        WidgetStateData( parent, target, duration ),
        _position( -1, -1 )
    { target->installEventFilter( this ); }

    //______________________________________________
    bool DialData::eventFilter( QObject* object, QEvent* event )
    {

        if( object != target().data() )
        { return WidgetStateData::eventFilter( object, event ); }

        // check event type
        switch( event->type() )
        {

            case QEvent::HoverEnter:
            case QEvent::HoverMove:
            hoverMoveEvent( object, event );
            break;

            case QEvent::HoverLeave:
            hoverLeaveEvent( object, event );
            break;

            default: break;

        }

        return WidgetStateData::eventFilter( object, event );

    }

    //______________________________________________
    void DialData::hoverMoveEvent(  QObject* object, QEvent* event )
    {

        // try cast object to dial
        QDial* scrollBar( qobject_cast<QDial*>( object ) );
        if( !scrollBar || scrollBar->isSliderDown() ) return;

        // cast event
        QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(event);

        // store position
        _position = hoverEvent->pos();

        // trigger animation if position match handle rect
        updateState( _handleRect.contains( _position ) );

    }


    //______________________________________________
    void DialData::hoverLeaveEvent(  QObject*, QEvent* )
    {

        // reset hover state
        updateState( false );

        // reset mouse position
        _position = QPoint( -1, -1 );
    }

}
