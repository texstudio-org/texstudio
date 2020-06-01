#ifndef adwaitabaseengine_h
#define adwaitabaseengine_h

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

#include "adwaita.h"

#include <QObject>
#include <QSet>

namespace Adwaita
{

    //* base class for all animation engines
    /** it is used to store configuration values used by all animations stored in the engine */
    class BaseEngine: public QObject
    {

        Q_OBJECT

        public:

        using Pointer = WeakPointer<BaseEngine>;

        //* constructor
        explicit BaseEngine( QObject* parent ):
            QObject( parent ),
            _enabled( true ),
            _duration( 200 )
        {}

        //* destructor
        virtual ~BaseEngine( void )
        {}

        //* enability
        virtual void setEnabled( bool value )
        { _enabled = value; }

        //* enability
        virtual bool enabled( void ) const
        { return _enabled; }

        //* duration
        virtual void setDuration( int value )
        { _duration = value; }

        //* duration
        virtual int duration( void ) const
        { return _duration; }

        //* unregister widget
        virtual bool unregisterWidget( QObject* object ) = 0;

        //* list of widgets
        using WidgetList = QSet<QWidget*>;

        //* returns registered widgets
        virtual WidgetList registeredWidgets( void ) const
        { return WidgetList(); }

        private:

        //* engine enability
        bool _enabled;

        //* animation duration
        int _duration;

    };

}

#endif
