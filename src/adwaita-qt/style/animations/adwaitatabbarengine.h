#ifndef adwaitatabbarengine_h
#define adwaitatabbarengine_h

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
#include "adwaitabaseengine.h"
#include "adwaitadatamap.h"
#include "adwaitatabbardata.h"

namespace Adwaita
{

    //* stores tabbar hovered action and timeLine
    class TabBarEngine: public BaseEngine
    {

        Q_OBJECT

        public:

        //* constructor
        explicit TabBarEngine( QObject* parent ):
            BaseEngine( parent )
        {}

        //* destructor
        virtual ~TabBarEngine( void )
        {}

        //* register tabbar
        virtual bool registerWidget( QWidget* );

        //* true if widget hover state is changed
        virtual bool updateState( const QObject*, const QPoint&, AnimationMode, bool );

        //* true if widget is animated
        virtual bool isAnimated( const QObject* object, const QPoint& point, AnimationMode );

        //* animation opacity
        virtual qreal opacity( const QObject* object, const QPoint& point, AnimationMode mode )
        { return isAnimated( object, point, mode ) ? data( object, mode ).data()->opacity( point ) : AnimationData::OpacityInvalid; }

        //* enability
        virtual void setEnabled( bool value )
        {
            BaseEngine::setEnabled( value );
            _hoverData.setEnabled( value );
            _focusData.setEnabled( value );
        }

        //* duration
        virtual void setDuration( int value )
        {
            BaseEngine::setDuration( value );
            _hoverData.setDuration( value );
            _focusData.setDuration( value );
        }

        public Q_SLOTS:

        //* remove widget from map
        virtual bool unregisterWidget( QObject* object )
        {
            if( !object ) return false;
            bool found = false;
            if( _hoverData.unregisterWidget( object ) ) found = true;
            if( _focusData.unregisterWidget( object ) ) found = true;
            return found;
        }

        private:

        //* returns data associated to widget
        DataMap<TabBarData>::Value data( const QObject*, AnimationMode );

        //* data map
        DataMap<TabBarData> _hoverData;
        DataMap<TabBarData> _focusData;

    };

}

#endif
