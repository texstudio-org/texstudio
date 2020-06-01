#ifndef adwaitadialengine_h
#define adwaitadialengine_h

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

#include "adwaitadialdata.h"
#include "adwaitawidgetstateengine.h"

namespace Adwaita
{

    //* stores dial hovered action and timeLine
    class DialEngine: public WidgetStateEngine
    {

        Q_OBJECT

        public:

        //* constructor
        explicit DialEngine( QObject* parent ):
            WidgetStateEngine( parent )
        {}

        //* destructor
        virtual ~DialEngine( void )
        {}

        //* register dial
        virtual bool registerWidget( QWidget*, AnimationModes );

        //* control rect
        virtual void setHandleRect( const QObject* object, const QRect& rect )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            { static_cast<DialData*>(data.data())->setHandleRect( rect ); }
        }

        //* mouse position
        virtual QPoint position( const QObject* object )
        {
            if( DataMap<WidgetStateData>::Value data = this->data( object, AnimationHover ) )
            {

                return static_cast<const DialData*>(data.data())->position();

            } else return QPoint( -1, -1 );
        }

    };

}

#endif
