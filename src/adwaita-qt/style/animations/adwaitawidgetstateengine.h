#ifndef adwaitawidgetstateengine_h
#define adwaitawidgetstateengine_h

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
#include "adwaitawidgetstatedata.h"

namespace Adwaita
{

    //* used for simple widgets
    class WidgetStateEngine: public BaseEngine
    {

        Q_OBJECT

        public:

        //* constructor
        explicit WidgetStateEngine( QObject* parent ):
            BaseEngine( parent )
        {}

        //* destructor
        virtual ~WidgetStateEngine( void )
        {}

        //* register widget
        virtual bool registerWidget( QWidget*, AnimationModes );

        //* returns registered widgets
        virtual WidgetList registeredWidgets( AnimationModes ) const;

        using BaseEngine::registeredWidgets;

        //* true if widget hover state is changed
        virtual bool updateState( const QObject*, AnimationMode, bool );

        //* true if widget is animated
        virtual bool isAnimated( const QObject*, AnimationMode );

        //* animation opacity
        virtual qreal opacity( const QObject* object, AnimationMode mode )
        { return isAnimated( object, mode ) ? data( object, mode ).data()->opacity(): AnimationData::OpacityInvalid; }

        //* animation mode
        /** precedence on focus */
        virtual AnimationMode frameAnimationMode( const QObject* object )
        {
            if( isAnimated( object, AnimationEnable ) ) return AnimationEnable;
            else if( isAnimated( object, AnimationFocus ) ) return AnimationFocus;
            else if( isAnimated( object, AnimationHover ) ) return AnimationHover;
            else return AnimationNone;
        }

        //* animation opacity
        /** precedence on focus */
        virtual qreal frameOpacity( const QObject* object )
        {
            if( isAnimated( object, AnimationEnable ) ) return data( object, AnimationEnable ).data()->opacity();
            else if( isAnimated( object, AnimationFocus ) ) return data( object, AnimationFocus ).data()->opacity();
            else if( isAnimated( object, AnimationHover ) ) return data( object, AnimationHover ).data()->opacity();
            else return AnimationData::OpacityInvalid;
        }

        //* animation mode
        /** precedence on mouseOver */
        virtual AnimationMode buttonAnimationMode( const QObject* object )
        {
            if( isAnimated( object, AnimationEnable ) ) return AnimationEnable;
            else if( isAnimated( object, AnimationPressed ) ) return AnimationPressed;
            else if( isAnimated( object, AnimationHover ) ) return AnimationHover;
            else if( isAnimated( object, AnimationFocus ) ) return AnimationFocus;
            else return AnimationNone;
        }

        //* animation opacity
        /** precedence on mouseOver */
        virtual qreal buttonOpacity( const QObject* object )
        {
            if( isAnimated( object, AnimationEnable ) ) return data( object, AnimationEnable ).data()->opacity();
            else if( isAnimated( object, AnimationPressed ) ) return data( object, AnimationPressed ).data()->opacity();
            else if( isAnimated( object, AnimationHover ) ) return data( object, AnimationHover ).data()->opacity();
            else if( isAnimated( object, AnimationFocus ) ) return data( object, AnimationFocus ).data()->opacity();
            else return AnimationData::OpacityInvalid;
        }

        //* duration
        virtual void setEnabled( bool value )
        {
            BaseEngine::setEnabled( value );
            _hoverData.setEnabled( value );
            _focusData.setEnabled( value );
            _enableData.setEnabled( value );
            _pressedData.setEnabled( value );
        }

        //* duration
        virtual void setDuration( int value )
        {
            BaseEngine::setDuration( value );
            _hoverData.setDuration( value );
            _focusData.setDuration( value );
            _enableData.setDuration( value );
            _pressedData.setDuration( value/2 );
        }

        public Q_SLOTS:

        //* remove widget from map
        virtual bool unregisterWidget( QObject* object )
        {
            if( !object ) return false;
            bool found = false;
            if( _hoverData.unregisterWidget( object ) ) found = true;
            if( _focusData.unregisterWidget( object ) ) found = true;
            if( _enableData.unregisterWidget( object ) ) found = true;
            if( _pressedData.unregisterWidget( object ) ) found = true;
            return found;
        }

        protected:

        //* returns data associated to widget
        DataMap<WidgetStateData>::Value data( const QObject*, AnimationMode );

        //* returns data map associated to animation mode
        DataMap<WidgetStateData>& dataMap( AnimationMode );

        private:

        //* maps
        DataMap<WidgetStateData> _hoverData;
        DataMap<WidgetStateData> _focusData;
        DataMap<WidgetStateData> _enableData;
        DataMap<WidgetStateData> _pressedData;

    };

}

#endif
