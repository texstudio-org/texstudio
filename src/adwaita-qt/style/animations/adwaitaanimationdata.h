#ifndef adwaita_animationdata_h
#define adwaita_animationdata_h

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

#include <QEvent>
#include <QObject>
#include <QWidget>

#include <cmath>

namespace Adwaita
{

    //* base class
    class AnimationData: public QObject
    {

        Q_OBJECT

        public:

        //* constructor
        AnimationData( QObject* parent, QWidget* target ):
        QObject( parent ),
        _target( target ),
        _enabled( true )
        { Q_ASSERT( _target ); }

        //* destructor
        virtual ~AnimationData( void )
        {}

        //* duration
        virtual void setDuration( int ) = 0;

        //* steps
        static void setSteps( int value )
        { _steps = value; }

        //* enability
        virtual bool enabled( void ) const
        { return _enabled; }

        //* enability
        virtual void setEnabled( bool value )
        { _enabled = value; }

        //* target
        const WeakPointer<QWidget>& target( void ) const
        { return _target; }

        //* invalid opacity
        static const qreal OpacityInvalid;

        protected:

        //* setup animation
        virtual void setupAnimation( const Animation::Pointer& animation, const QByteArray& property );

        //* apply step
        virtual qreal digitize( const qreal& value ) const
        {
            if( _steps > 0 ) return std::floor( value*_steps )/_steps;
            else return value;
        }

        //* trigger target update
        virtual void setDirty( void ) const
        { if( _target ) _target.data()->update(); }

        private:

        //* guarded target
        WeakPointer<QWidget> _target;

        //* enability
        bool _enabled;

        //* steps
        static int _steps;

    };

}

#endif
