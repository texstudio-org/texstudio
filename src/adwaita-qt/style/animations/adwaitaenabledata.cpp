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

#include "adwaitaenabledata.h"

namespace Adwaita
{

    //______________________________________________
    bool EnableData::eventFilter( QObject* object, QEvent* event )
    {

        if( !enabled() ) return WidgetStateData::eventFilter( object, event );

        // check event type
        switch( event->type() )
        {

            // enter event
            case QEvent::EnabledChange:
            {
                if( QWidget* widget = qobject_cast<QWidget*>( object ) )
                { updateState( widget->isEnabled() ); }
                break;
            }

            default: break;

        }

        return WidgetStateData::eventFilter( object, event );

    }

}
