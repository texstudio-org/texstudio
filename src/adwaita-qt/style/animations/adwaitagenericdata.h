#ifndef adwaitageneric_data_h
#define adwaitageneric_data_h

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

#include "adwaitaanimationdata.h"
#include "adwaitaanimation.h"

#include <QObject>
#include <QTextStream>
namespace Adwaita
{


    //* generic data
    class GenericData: public AnimationData
    {

        Q_OBJECT

        //* declare opacity property
        Q_PROPERTY( qreal opacity READ opacity WRITE setOpacity )

        public:

        //* constructor
        GenericData( QObject* parent, QWidget* widget, int duration );

        //* destructor
        virtual ~GenericData( void )
        {}

        //* return animation object
        virtual const Animation::Pointer& animation() const
        { return _animation; }

        //* duration
        virtual void setDuration( int duration )
        { _animation.data()->setDuration( duration ); }

        //* opacity
        virtual qreal opacity( void ) const
        { return _opacity; }

        //* opacity
        virtual void setOpacity( qreal value )
        {

            value = digitize( value );
            if( _opacity == value ) return;

            _opacity = value;
            setDirty();

        }

        private:

        //* animation handling
        Animation::Pointer _animation;

        //* opacity variable
        qreal _opacity;

    };

}

#endif
