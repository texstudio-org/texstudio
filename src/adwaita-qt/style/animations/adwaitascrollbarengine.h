#ifndef adwaitascrollbarengine_h
#define adwaitascrollbarengine_h

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

#include "adwaitascrollbardata.h"
#include "adwaitawidgetstateengine.h"

namespace Adwaita
{

    //* stores scrollbar hovered action and timeLine
    class ScrollBarEngine: public WidgetStateEngine
    {

        Q_OBJECT

        public:

        //* constructor
        explicit ScrollBarEngine( QObject* parent ):
            WidgetStateEngine( parent )
        {}

        //* destructor
        virtual ~ScrollBarEngine( void )
        {}

        //* register scrollbar
        virtual bool registerWidget( QWidget*, AnimationModes );

        //*@name accessors
        //@{

        using WidgetStateEngine::isAnimated;
        using WidgetStateEngine::opacity;

        //* true if widget is animated
        virtual bool isAnimated( const QObject*, AnimationMode, QStyle::SubControl control );

        //* true if widget is animated
        virtual AnimationMode animationMode( const QObject* object, QStyle::SubControl control );

        //* animation opacity
        virtual qreal opacity( const QObject* object, QStyle::SubControl control );

        //* return true if given subcontrol is hovered
        virtual bool isHovered( const QObject* object, QStyle::SubControl control )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            {

                return static_cast<const ScrollBarData*>( data.data() )->isHovered( control );

            } else return false;
        }

        //* control rect associated to object
        virtual QRect subControlRect( const QObject* object, QStyle::SubControl control )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            {

                return static_cast<const ScrollBarData*>( data.data() )->subControlRect( control );

            } else return QRect();
        }

        //* mouse position
        virtual QPoint position( const QObject* object )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            {

                return static_cast<const ScrollBarData*>( data.data() )->position();

            } else return QPoint( -1, -1 );
        }

        //@}

        //*@name modifiers
        //@{

        //* control rect
        virtual void setSubControlRect( const QObject* object, QStyle::SubControl control, const QRect& rect )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            { static_cast<ScrollBarData*>( data.data() )->setSubControlRect( control, rect ); }
        }

        //@}

    };

}

#endif
