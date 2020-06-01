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

#include "adwaitamnemonics.h"
#include "adwaita.h"

#include <QKeyEvent>
#include <QWidget>

namespace Adwaita
{

    //____________________________________________________
    void Mnemonics::setMode( int mode )
    {

        switch( mode )
        {
            case Adwaita::MN_NEVER:
            qApp->removeEventFilter( this );
            setEnabled( false );
            break;

            default:
            case Adwaita::MN_ALWAYS:
            qApp->removeEventFilter( this );
            setEnabled( true );
            break;

            case Adwaita::MN_AUTO:
            qApp->removeEventFilter( this );
            qApp->installEventFilter( this );
            setEnabled( false );
            break;

        }

        return;

    }

    //____________________________________________________
    bool Mnemonics::eventFilter( QObject*, QEvent* event )
    {

        switch( event->type() )
        {

            case QEvent::KeyPress:
            if( static_cast<QKeyEvent*>(event)->key() == Qt::Key_Alt )
            { setEnabled( true ); }
            break;

            case QEvent::KeyRelease:
            if( static_cast<QKeyEvent*>(event)->key() == Qt::Key_Alt )
            { setEnabled( false ); }
            break;

            #if QT_VERSION >= 0x050000
            case QEvent::ApplicationStateChange:
            { setEnabled( false ); }
            break;
            #endif

            default: break;

        }

        return false;

    }

    //____________________________________________________
    void Mnemonics::setEnabled( bool value )
    {
        if( _enabled == value ) return;

        _enabled = value;

        // update all top level widgets
        foreach( QWidget* widget, qApp->topLevelWidgets() )
        { widget->update(); }

    }

}
