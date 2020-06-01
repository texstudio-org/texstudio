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

#include "adwaitascrollbarengine.h"

#include <QEvent>

namespace Adwaita
{

    //____________________________________________________________
    bool ScrollBarEngine::registerWidget( QWidget* widget, AnimationModes mode )
    {

        // check widget
        if( !widget ) return false;

        // only handle hover and focus
        if( mode&AnimationHover && !dataMap(AnimationHover).contains( widget ) ) { dataMap(AnimationHover).insert( widget, new ScrollBarData( this, widget, duration() ), enabled() ); }
        if( mode&AnimationFocus && !dataMap(AnimationFocus).contains( widget ) ) { dataMap(AnimationFocus).insert( widget, new WidgetStateData( this, widget, duration() ), enabled() ); }

        // connect destruction signal
        connect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(unregisterWidget(QObject*)), Qt::UniqueConnection );

        return true;
    }

    //____________________________________________________________
    bool ScrollBarEngine::isAnimated( const QObject* object, AnimationMode mode, QStyle::SubControl control )
    {

        if( mode == AnimationHover )
        {

            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            {

                const ScrollBarData* scrollBarData( static_cast<const ScrollBarData*>( data.data() ) );
                Animation::Pointer animation = scrollBarData->animation( control );
                return animation.data()->isRunning();

            } else return false;

        } else if( control == QStyle::SC_ScrollBarSlider ) {

            return WidgetStateEngine::isAnimated( object, mode );

        } else return false;

    }

    //____________________________________________________________
    AnimationMode ScrollBarEngine::animationMode( const QObject* object, QStyle::SubControl control )
    {

        // enable state
        if( isAnimated( object, AnimationHover, control ) ) return AnimationHover;
        else if( isAnimated( object, AnimationFocus, control ) ) return AnimationFocus;
        else if( isAnimated( object, AnimationPressed, control ) ) return AnimationPressed;
        else return AnimationNone;

    }

    //____________________________________________________________
    qreal ScrollBarEngine::opacity( const QObject* object, QStyle::SubControl control )
    {

        if( isAnimated( object, AnimationHover, control ) ) return static_cast<const ScrollBarData*>(data( object, AnimationHover ).data())->opacity( control );
        else if( control == QStyle::SC_ScrollBarSlider ) return WidgetStateEngine::buttonOpacity( object );
        return AnimationData::OpacityInvalid;

    }

}
