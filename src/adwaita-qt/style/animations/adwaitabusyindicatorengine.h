#ifndef adwaitabusyindicatorengine_h
#define adwaitabusyindicatorengine_h

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

#include "adwaitaanimation.h"
#include "adwaitabaseengine.h"
#include "adwaitabusyindicatordata.h"
#include "adwaitadatamap.h"

namespace Adwaita
{

    //* handles progress bar animations
    class BusyIndicatorEngine: public BaseEngine
    {

        Q_OBJECT

        //* declare opacity property
        Q_PROPERTY( int value READ value WRITE setValue )

        public:

        //* constructor
        explicit BusyIndicatorEngine( QObject* );

        //* destructor
        virtual ~BusyIndicatorEngine( void )
        {}

        //*@name accessors
        //@{

        //* true if widget is animated
        virtual bool isAnimated( const QObject* );

        //* value
        virtual int value( void ) const
        { return _value; }

        //@}

        //*@name modifiers
        //@{

        //* register progressbar
        virtual bool registerWidget( QObject* );

        //* duration
        virtual void setDuration( int );

        //* set object as animated
        virtual void setAnimated( const QObject*, bool );

        //* opacity
        virtual void setValue( int value );

        //@}

        public Q_SLOTS:

        //* remove widget from map
        virtual bool unregisterWidget( QObject* );

        protected:

        //* returns data associated to widget
        DataMap<BusyIndicatorData>::Value data( const QObject* );

        private:

        //* map widgets to progressbar data
        DataMap<BusyIndicatorData> _data;

        //* animation
        Animation::Pointer _animation;

        //* value
        int _value = 0;

    };

}

#endif
